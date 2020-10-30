#include "header.h"
#define PORT 8080 
using namespace std;

map <string, vector< vector<string> > > shared_files;
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

string shareCmd( CLIENT *Client, vector <string> cmd ){
	string key, file_name="", status;
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
	    	key=cmd[1] + "__" + (*Client).ip + "__" + to_string((*Client).portNo);	//key = file_path + ip + portNo
	    if(shared_files.find(key) == shared_files.end()){
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
	    if(cmd[0]=="share"){
	    	status = shareCmd(Client, cmd);
	    	//display_shared_files();
	    	
	    }
	    char reply2client[status.length()];
	    strcpy(reply2client, status.c_str());
	    send((*Client).sock , reply2client , strlen(reply2client) , 0 );
	}
}

int main(int argc, char const *argv[]) 
{ 
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
       
    // Forcefully attaching socket to the port 8080 
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, 
                                                  &opt, sizeof(opt))) 
    { 
        perror("setsockopt"); 
        exit(EXIT_FAILURE); 
    } 
    address.sin_family = AF_INET; 
    address.sin_addr.s_addr = INADDR_ANY; 
    address.sin_port = htons( PORT ); 
       
    // Forcefully attaching socket to the port 8080 
    if (bind(server_fd, (struct sockaddr *)&address,  
                                 sizeof(address))<0) 
    { 
        perror("bind failed"); 
        exit(EXIT_FAILURE); 
    } 
    if (listen(server_fd, 10) < 0) 
    { 
        perror("listen"); 
        exit(EXIT_FAILURE); 
    } 
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
	    
	}
    return 0; 
} 

