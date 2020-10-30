#include "header.h"
#define PORT 8080 
using namespace std;

map <int, int> sock2idx;
//map <string, vector <string>> file2key;
//map <string, vector< vector<string> > > shared_files;
//int seedFileFD;
//char seedFile[]="seedFile.txt";

vector<int> sock_n( 10, 0); 
CLIENT client[10];
int n=0;
map <string, string> login_cred;
map <string, set<int>> groupMembers;
map <string, set<int>> pendingJoinReq;
map <string, int> grpOwner;
map <string, int> usrName2Idx;
map <string, vector<FILES>> shared_files;	// key = filename
map <string, vector<FILES>> leeches;	// key = filename
map <string, set<string>> grpID2file;
map <string, vector<FILES_HASH>> file2hash;

void tokenize(string command, vector <string> &cmds){
    command+=" ";
    string str="";
    int i,n=command.length();
    for(i=0;i<n;i++){
        if(command[i]!=' '){
            str+=command[i];
        }
        else{
            cmds.push_back(str);
            str="";
        }
    }
}

void showLoginDetails(){
	for(auto it : login_cred){
		cout<<it.first<<" - "<<it.second<<endl;
	}
}

/*
void update_Seed_File(string info){
	ofstream outfile;
	outfile.open(seedFile, std::ios_base::app | std::ios_base::out);
    outfile << info;
    outfile.close();
}


void display_shared_files(){
	for(auto it=shared_files.begin(); it!=shared_files.end(); it++){
		cout<<"***"<<(it->first)<<"***"<<endl;
		cout<<((it->second)[0][0])<<endl;
		cout<<((it->second)[1][0])<<endl;
		cout<<((it->second)[2][0])<<endl;
		cout<<((it->second)[3][0])<<endl;
		cout<<"----------------------"<<endl;
	}
}

string shareCmd( int idx, vector <string> cmd ){
	string key, file_name="", status="";
	int i=cmd[1].length()-1;
	vector <string> tmp;
	while(cmd[1][i]!='/'){
	    file_name=cmd[1][i]+file_name;
	    i--;
	}
	//void *PORTT=*(void*)client.portNo;
	//cout<<(*Client).portNo<<endl;
	//string IP;//=client.ip;
	//IP=(*Client).ip;
	key=file_name + "__" + client[idx].ip + "__" + to_string(client[idx].portNo)+"__"+to_string(client[idx].sock);	//key = file_path + ip + portNo
	if(shared_files.find(key) == shared_files.end()){
		file2key[file_name].push_back(key);
		//push_back filename
		tmp.push_back(file_name);
		shared_files[key].push_back(tmp);
		tmp.clear();
		//push_back client IP
		tmp.push_back(client[idx].ip);
		shared_files[key].push_back(tmp);
		tmp.clear();
		//push_back client PORT
		tmp.push_back(to_string(client[idx].portNo));
		shared_files[key].push_back(tmp);
		tmp.clear();
		//push_back SHA HASH of file
		tmp.push_back(cmd[3]);
	    shared_files[key].push_back(tmp);
		tmp.clear();
		// availablity status
		tmp.push_back("AVAILABLE");
	    shared_files[key].push_back(tmp);
		tmp.clear();
		status="FILE SHARED";
		string info=file_name + " " + client[idx].ip + " " + to_string(client[idx].portNo) + " " + cmd[1] + "\n";
		update_Seed_File(info);
	}
	else{
		if(shared_files[key][4][0]=="AVAILABLE")
			status="FILE ALREADY SHARED";
		else{
			shared_files[key][0][0]=file_name;
			shared_files[key][1][0]=client[idx].ip;
			shared_files[key][2][0]=to_string(client[idx].portNo);
			shared_files[key][3][0]=cmd[3];
			shared_files[key][4][0]="AVAILABLE";
			status="FILE SHARED AGAIN";
		}

	}
	    	
	display_shared_files();
	return status;
}
*/

string create_user(int idx, vector<string> cmd){
	string status;
	/*if(client[idx].isUser==1){
		status="ALREADY LOGGED IN";
	}
	else */if(login_cred.find(cmd[1])!=login_cred.end()){
		status="USER NAME ALREADY IN USE";
	}
	else{
		client[idx].userName=cmd[1];
		client[idx].psw=cmd[2];
		status="USER MADE";
		login_cred[cmd[1]]=cmd[2];
		usrName2Idx[cmd[1]]=idx;
	}
	return status;
}

string login(int idx, vector<string> cmd){
	string status;
	if(client[idx].isLoggedIn==1){
		status="ALREADY LOGGED IN";
	}
	else if(login_cred.find(cmd[1])==login_cred.end() || login_cred[cmd[1]]!=cmd[2]){
		status="USERNAME OR PSW IS WRONG";
	}
	else{
		client[idx].isLoggedIn=1;
		status="LOGGED IN";
	}
	return status;
}

string create_group(int idx, vector<string> cmd){
	string status;
	if(groupMembers.find(cmd[1])!=groupMembers.end()){
		status="GROUP ID NOT UNIQUE";
	}
	else{
		groupMembers[cmd[1]].insert(idx);
		grpOwner[cmd[1]]=idx;
		status="NEW GROUP MADE";
		client[idx].grpID.insert(cmd[1]);
	}
	return status;
}

string join_group(int idx, vector<string> cmd){
	string status;
	if(groupMembers.find(cmd[1])==groupMembers.end()){
		status="NO SUCH GROUP";
	}
	else{
		int GrpOwn=grpOwner[cmd[1]];
		pendingJoinReq[cmd[1]].insert(idx);
		status="JOIN REQ SENT";
	}
	return status;
}

string list_requests(int idx, vector<string> cmd){
	//cout<<"in list_requests server...\n";
	string status="";
	if(pendingJoinReq.find(cmd[1])==pendingJoinReq.end()){
		status="NO PENDING REQUESTS";
	}
	else{
		status="REQUESTS - \n";
		//cout<<status;
		for(auto it : pendingJoinReq[cmd[1]]){
			//status+=to_string(it)+"  -  "+usrName2Idx[it]+"\n";
			status+=client[it].userName+" - "+to_string(it)+"\n";
		}
	}
	return status;
}

string leave_group(int idx, vector<string> cmd){
	string status;
	if(groupMembers.find(cmd[1])==groupMembers.end()){
		status="NO SUCH GROUP";
	}
	else if(client[idx].grpID.find(cmd[1])==client[idx].grpID.end()){
		status="ALREADY NOT A MEMBER";	
	}
	else{
		status="GROUP LEFT";
		if(grpOwner[cmd[1]]!=idx){						// IF NON-OWNER LEAVES
			client[idx].grpID.erase(cmd[1]);
			groupMembers[cmd[1]].erase(idx);
			if(groupMembers[cmd[1]].size()==0){
				groupMembers.erase(cmd[1]);
				status="GROUP NO MORE EXISTS";
			}
		}
		else{											// IF GROUP OWNER LEAVES
			for(auto member : groupMembers[cmd[1]]){
				client[member].grpID.erase(cmd[1]);
			}
			groupMembers.erase(cmd[1]);
			grpOwner.erase(cmd[1]);
			status="GROUP NO MORE EXISTS";
		}
		
	}
	// update delete uploaded files in the grp left by respective peer
	return status;
}

string accept_request(int idx, vector<string> cmd){
	cout<<"in acc req if() server...\n";
	string status;
	int id=stoi(cmd[2]);
	if(groupMembers.find(cmd[1])==groupMembers.end()){
		status="NO SUCH GROUP";
	}
	else if(grpOwner[cmd[1]]==idx){		// CAN ACCEPT ONLY IF U ARE GRP OWNER
		if(pendingJoinReq[cmd[1]].find(id)==pendingJoinReq[cmd[1]].end()){
			status="NO SUCH PENDING REQUEST FOUND";
		}
		else{
			client[id].grpID.insert(cmd[1]);
			groupMembers[cmd[1]].insert(id);
			pendingJoinReq[cmd[1]].erase(id);
			status="REQUEST ACCEPTED";
		}
	}
	else{
		status="CANNOT ACCEPT. U R NOT GRP OWNER";
	}
	return status;
}

string list_groups(){
	string status="";
	for(auto grp : groupMembers){
		//cout<<grp.first<<" -  ";
		status+=grp.first+" -  ";
		for(auto member : grp.second){
			status+=to_string(member)+" ";
			//cout<<member<<" ";
		}
		status+="\n";
		//cout<<endl;
	}
	if(status=="")
		status="NO GROUPS AVAILABLE";
	return status;
}

string upload_file(int idx, vector<string> cmd, string command){
	//cout<<command<<endl;
	//return command;
	string status;
	int total_pieces=stoi(cmd[3]);
	if(groupMembers.find(cmd[2])==groupMembers.end()){
		status="NO SUCH GROUP";
	}
	else{
		if(file2hash.find(cmd[1])==file2hash.end()){	// update only when file is shared for first time
			FILES_HASH fh;
			
			total_pieces/=20;
			fh.no_of_pieces=total_pieces/20;
			int pos=15+cmd[1].length()+cmd[2].length()+cmd[3].length();
			string remStr=command.substr(pos);
			fh.combinedHash=remStr;
			int i=0;
			for( int j=1;j<=total_pieces;j++){		// STORE HASH OF ALL CHUNKS
				string tmp=remStr.substr(i,20);
				i+=20;
				fh.pieces.push_back(tmp);
			}
			file2hash[cmd[1]].push_back(fh);
		}
		
		FILES f;
				
		f.grpID.insert(cmd[2]);
		f.index=idx;
		shared_files[cmd[1]].push_back(f);
		grpID2file[cmd[2]].insert(cmd[1]);
		status="FILE SHARED. U R A SEED OF IT.";
	}
	return status;
}

string list_files(int idx, vector<string> cmd){
	string status="";
	if(groupMembers.find(cmd[1])==groupMembers.end()){
		status="NO SUCH GROUP";
	}
	else{
		if(grpID2file.find(cmd[1])==grpID2file.end()){
			status="NO FILES SHARED IN THIS GROUP";
		}
		else{
			status="FILES -  ";
			for(auto file : grpID2file[cmd[1]]){
				status+=file+" ";
			}
		}
	}
	return status;
}

string download_file(int idx, vector<string> cmd){
	string status="";
	if(shared_files.find(cmd[2])==shared_files.end()){
		status="FILE NOT AVAILABLE";
	}
	else{
		int i;
		string srcIP, srcPort;
		for(auto f : shared_files[cmd[2]]){
			if(f.grpID.find(cmd[1])!=f.grpID.end()){
				i=f.index;
				srcIP=client[i].ip;
				srcPort=to_string(client[i].server_port);
				status+=srcIP+","+srcPort+"|";
			}
		}
	}
	return status;
}

void *serverservice(void *socket_desc)	//socket_desc
{
	//int *m=(int*)args;
	//int new_socket=sock_n[*m];
	//int *arr = (int*)args;
	//int idx=arr[0], new_socket=arr[1];
	int new_socket = *(int *)socket_desc;
	int idx=sock2idx[new_socket];
	cout<<client[idx].ip<<"\n"<<client[idx].IP<<"\n"<<client[idx].portNo<<"\n"<<client[idx].sock<<endl;
	//for(auto it : sock2idx)
	//	cout<<it.first<<"-"<<it.second<<",  ";
	//cout<<endl;
	//cout<<"in thread...\n";
    string status;
    while (1)
    {

        int closeflag = 0;
        char buffer[1024] = {0};
        int rc = read(new_socket, buffer, 1024);
        //cout<<buffer<<endl;
        string clientreplymsg="bye";
        //string data = string(buffer);
        
        vector<string> cmd;
	    string command(buffer);
	    tokenize(command, cmd);
	    cout<<command<<endl;
	    for(auto i : cmd){
	    	cout<<i<<endl;
	    }
	    //cout<<"after tokenize...\n";
	    if(cmd[0]=="create_user"){
	    	//cout<<"in create_user...\n";
	    	//status="share reply";
	    	status=create_user(idx, cmd);
	    	clientreplymsg=status;
	    	showLoginDetails();
			//cout<<"serverreply : "<<string(serverreply)<<endl;
	    }
	    else if(cmd[0]=="login"){
	    	status=login(idx, cmd);
	    	clientreplymsg=status;
	    }
	    else if(cmd[0]=="create_group"){
	    	status=create_group(idx, cmd);
	    	clientreplymsg=status;
	    }
	    else if(cmd[0]=="join_group"){
	    	status=join_group(idx, cmd);
	    	clientreplymsg=status;
	    }
	    else if(cmd[0]=="list_requests"){
	    	status=list_requests(idx, cmd);
	    	clientreplymsg=status;
	    }
	    else if(cmd[0]=="leave_group"){
	    	status=leave_group(idx, cmd);
	    	clientreplymsg=status;
	    }
	    else if(cmd[0]=="accept_request"){
	    	//cout<<"in acc req if() server...\n";
	    	status=accept_request(idx, cmd);
	    	clientreplymsg=status;
	    }
	    else if(cmd[0]=="list_groups"){
	    	status=list_groups();
	    	clientreplymsg=status;
	    }
	    else if(cmd[0]=="upload_file"){
	    	status=upload_file(idx, cmd, command);
	    	clientreplymsg=status;
	    }
	    else if(cmd[0]=="list_files"){
	    	status=list_files(idx, cmd);
	    	clientreplymsg=status;
	    }
	    else if(cmd[0]=="download_file"){
	    	status=download_file(idx, cmd);
	    	clientreplymsg=status;
	    }
	    

	        char *serverreply = new char[clientreplymsg.length() + 1];
	        strcpy(serverreply, clientreplymsg.c_str());
	        //cout<<"serverreply : "<<serverreply<<endl;
	        send(new_socket, serverreply, strlen(serverreply), 0);	



        

    }

    //return socket_desc;
}

int main(int argc, char *argv[])
{
	int args[2];
    pthread_t thread_id;
    if (argc != 3)
    {
        cout << "Invalid Argument !!!" << endl;
    }
    else
    {
    	int tracker_port=atoi(argv[2]);
        int server_fd, new_socket;
        struct sockaddr_in address;
        int opt = 1;
        int addrlen = sizeof(address);

        // Creating socket file descriptor
        if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
        {
            perror("socket failed");
            exit(EXIT_FAILURE);
        }

        // Forcefully attaching socket to the port 8080
        if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
                       &opt, sizeof(opt)))
        {
            perror("setsockopt");
            exit(EXIT_FAILURE);
        }
        address.sin_family = AF_INET;
        address.sin_addr.s_addr = inet_addr(argv[1]);	//trackersocket1.ip
        address.sin_port = htons(tracker_port);			//trackersocket1.port

        // Forcefully attaching socket to the port 8080
        if (bind(server_fd, (struct sockaddr *)&address,
                 sizeof(address)) < 0)
        {
            perror("bind failed");
            exit(EXIT_FAILURE);
        }
        if (listen(server_fd, 10) < 0)
        {
            perror("listen");
            exit(EXIT_FAILURE);
        }
        n=0;
        while (1)
        {
        	cout<<"listening...\n";								/*client[n].clientAddr*/
            if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen)) < 0)
            {
                perror("Error in accept connection");
                exit(EXIT_FAILURE);
            }
            cout<<"connected  "<<new_socket<<endl;
            client[n].ip=inet_ntoa(address.sin_addr);
            //cout<<"1\n";
            strcpy( client[n].IP , (client[n].ip).c_str());
		    //cout<<"2\n";
		    client[n].portNo=(int) ntohs(address.sin_port);
		    //client[n].portNo=;//(int) ntohs(address.sin_port);
		    
		    //cout<<"3\n";
		    client[n].sock=new_socket;
		    //cout<<"4\n";
		    //cout<<client[n].ip<<"\n"<<client[n].IP<<"\n"<<client[n].portNo<<"\n"<<client[n].sock<<endl;
		    sock2idx[new_socket]=n;
		    
		    //READ CLIENT'S SERVER PORT
		    char buffer[1024];
		    int valread = read( sock , buffer, 1024); 
		    string tmp(buffer);
		    client[n].server_port=stoi(tmp);
		    cout<<client[n].ip<<"\n"<<client[n].IP<<"\n"<<client[n].portNo<<"\n"<<client[n].sock<<endl<<"\n"<<client[n].server_port<<endl;

		    if (pthread_create(&thread_id, NULL, serverservice, (void *)&new_socket) < 0)
            {
                perror("\ncould not create thread\n");
            }
            n++;
        }
    }
}