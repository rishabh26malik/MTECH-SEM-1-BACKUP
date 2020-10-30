#include "header.h"
#define PORT 8080 
using namespace std;

map <string, vector <string>> file2key;
map <string, vector< vector<string> > > shared_files;
int seedFileFD;
char seedFile[]="seedFile.txt";

void tokenize(string command, vector <string> &cmds){
    //cout<<"in tokenize...\n";
    
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

void update_Seed_File(string info){
	ofstream outfile;
	outfile.open(seedFile, std::ios_base::app | std::ios_base::out);
    outfile << info;
    outfile.close();
}

void make_new_Seed_File(){
	string info;
	cout<<"in func...\n";
	ofstream outfile;
	outfile.open(seedFile, std::ios_base::app);
	for(auto it=shared_files.begin(); it!=shared_files.end(); it++){
		cout<<"in loop\n";	
		info=((it->second)[0][0]) + " " + ((it->second)[1][0]) + " " + ((it->second)[2][0]) + " " + ((it->second)[3][0]) + "\n";
		cout<<info<<endl;
		cout<<"last line of loop\n";
		outfile << info;
	}
	cout<<"func out...\n";
    //outfile.close();

}

string removeCmd( CLIENT *Client, vector <string> cmd ){
	string key, file_name, info="", status="";
	for(auto x : cmd)
		cout<<x<<" ";
	cout<<endl;
	int i=cmd[1].length()-1;
	while(cmd[1][i]!='.')
		i--;
	file_name=cmd[1].substr(0,i);
	
	key=file_name + "__" + (*Client).ip + "__" + to_string((*Client).portNo);
	cout<<key<<endl;
	if(shared_files.find(key)==shared_files.end()){
		status="FILE NOT SHARED PREVIOUSLY";
	}
	else{
		shared_files.erase(key);
		make_new_Seed_File();
		status="FILE REMOVED";
	}
	return status;
}

string shareCmd( CLIENT *Client, vector <string> cmd ){
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
	key=file_name + "__" + (*Client).ip + "__" + to_string((*Client).portNo);	//key = file_path + ip + portNo
	if(shared_files.find(key) == shared_files.end()){
		file2key[file_name].push_back(key);
		//push_back filename
		tmp.push_back(file_name);
		shared_files[key].push_back(tmp);
		tmp.clear();
		//push_back client IP
		tmp.push_back((*Client).ip);
		shared_files[key].push_back(tmp);
		tmp.clear();
		//push_back client PORT
		tmp.push_back(to_string((*Client).portNo));
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
		string info=file_name + " " + (*Client).ip + " " + to_string((*Client).portNo) + " " + cmd[1] + "\n";
		update_Seed_File(info);
	}
	else{
		if(shared_files[key][4][0]=="AVAILABLE")
			status="FILE ALREADY SHARED";
		else{
			shared_files[key][0][0]=file_name;
			shared_files[key][1][0]=(*Client).ip;
			shared_files[key][2][0]=to_string((*Client).portNo);
			shared_files[key][3][0]=cmd[3];
			shared_files[key][4][0]="AVAILABLE";
			status="FILE SHARED AGAIN";
		}

	}
	    	
	display_shared_files();
	return status;
}

string getCmd( CLIENT *Client, vector <string> cmd ){
	cout<<"in getCmd()...\n";
	string file_name="", status="";	
	//key=cmd[1] + "__" + (*Client).ip + "__" + to_string((*Client).portNo);
	//cout<<key<<endl;
	if(file2key.find(cmd[1])!=file2key.end()){
		for(auto i : file2key[cmd[1]]){
			status += shared_files[i][0][0] + " " + shared_files[i][1][0] + " " + shared_files[i][2][0] + "|";//  (*Client).ip + " " + to_string((*Client).portNo) + "|";
		}
/*		for(auto it=shared_files.begin(); it!=shared_files.end(); it++){
			if(it->first == key){
				status += (*Client).ip + " " + to_string((*Client).portNo) + "|";
			}
		}*/
	}
	else{
		status="NOT FOUND";
	}
	return status;
}

void *serverservice(void *client){	//sockFd
	//int sock_fd = *(int *)sockFd;
	CLIENT *Client = (CLIENT*)client;
	string status;
	cout<<"server in thread.....\n";
	while(1){
		char buffer[1024] = {0}; 
    	char hello[1024] = "server - received";
		//int valread = read( sock_fd , buffer, 1024);
		int valread = read( (*Client).sock , buffer, 1024); 
	    //printf("%s\n",buffer ); 
	    //send(sock_fd , hello , strlen(hello) , 0 ); 
	    //send((*Client).sock , hello , strlen(hello) , 0 ); 
	    
	    vector<string> cmd;
	    string command(buffer);
	    tokenize(command, cmd);
	    cout<<command<<endl;
	    if(cmd[0]=="share"){
	    	cout<<"in share...\n";
	    	status="share reply";
	    	//status=shareCmd(Client, cmd);
	    	/*char Status[status.length()];
	    	strcpy(Status, status.c_str());
	    	send((*Client).sock , Status , strlen(Status) , 0 );*/
	    }
	    else if(cmd[0]=="remove"){
	    	cout<<"remove...\n";
	    	status="remove reply";
	    	//status = removeCmd(Client, cmd);
	    	/*char Status[status.length()];
	    	strcpy(Status, status.c_str());
	    	send((*Client).sock , Status , strlen(Status) , 0 );*/
	    }
	    else if(cmd[0]=="get"){
	    	cout<<"in get...\n";
	    	status="get reply";
	    	//status = getCmd(Client, cmd);
	    	//cout<<status<<endl;
	    }
	    char Status[status.length()];
	    strcpy(Status, status.c_str());
	    send((*Client).sock , Status , strlen(Status) , 0 );
	}
}

int main(int argc, char const *argv[]) 
{ 
	if(argc!=3){
		cout<<"Invalid no. of args\n";
		exit(0);
	}
	int tracker_port=atoi(argv[2]);
	string tracker_ip(argv[1]);
	cout<<tracker_ip<<"  "<<tracker_port<<endl;
	//return 0;

    int server_fd, new_socket; 
    struct sockaddr_in address; 
    int opt = 1; 
    int addrlen = sizeof(address); 
    pthread_t thread_id; 
       
    // Creating socket file descriptor 
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) 
    { 
        perror("socket failed"); 
        exit(EXIT_FAILURE); 
    } 
    cout<<"after socket()...\n";   
    // Forcefully attaching socket to the port 8080 
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, 
                                                  &opt, sizeof(opt))) 
    { 
        perror("setsockopt"); 
        exit(EXIT_FAILURE); 
    } 
    address.sin_family = AF_INET; 
    address.sin_addr.s_addr = inet_addr(argv[1]);//INADDR_ANY; 
    address.sin_port = htons( tracker_port ); 
       
    // Forcefully attaching socket to the port 8080 
    if (bind(server_fd, (struct sockaddr *)&address,  
                                 sizeof(address))<0) 
    { 
        perror("bind failed"); 
        exit(EXIT_FAILURE); 
    } 
    cout<<"after bind()...\n";
    if (listen(server_fd, 10) < 0) 
    { 
        perror("listen"); 
        exit(EXIT_FAILURE); 
    } 
    cout<<"after listen()...\n";
    while(1){
	    if ((new_socket = accept(server_fd, (struct sockaddr *)&address,  
	                       (socklen_t*)&addrlen))<0) 
	    { 
	        perror("accept"); 
	        exit(EXIT_FAILURE); 
	    } 
	    CLIENT client;
	    client.ip=inet_ntoa(address.sin_addr);
	    //printf("%d\n",(int) ntohs(serv_addr.sin_port));
	    client.portNo=(int) ntohs(address.sin_port);
	    //cout << "tracker :" << clsource << endl;
	    client.sock=new_socket;

	    cout<<"connected\n";
	 	if (pthread_create(&thread_id, NULL, serverservice, (void *)&client) < 0)
        {
            perror("\ncould not create thread\n");
        }
	    cout<<"after pthread_create()...\n";
	}
    return 0; 
} 

