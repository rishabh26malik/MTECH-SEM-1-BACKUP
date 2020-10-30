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

string create_user(){
	
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
        cout<<buffer<<endl;
        string clientreplymsg="bye";
        //string data = string(buffer);
        
        //vector<string> cmd;
	    //string command(buffer);
	    //tokenize(command, cmd);
	    //cout<<command<<endl;
	    if(cmd[0]=="create_user"){
	    	cout<<"in create_user...\n";
	    	//status="share reply";
	    	status=create_user(idx, cmd);
	    	clientreplymsg=status;
			//cout<<"serverreply : "<<string(serverreply)<<endl;
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
		    if (pthread_create(&thread_id, NULL, serverservice, (void *)&new_socket) < 0)
            {
                perror("\ncould not create thread\n");
            }
            n++;
        }
    }
}