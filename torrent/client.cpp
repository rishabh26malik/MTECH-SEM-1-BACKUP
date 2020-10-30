#include "header.h" 
#define PORT 8080 
using namespace std;
string server_ip;
int server_port;
string shareHASH;
int client_port;
string client_ip;

/*
void *clientservice(void *sockFd){
	int sock_fd = *(int *)sockFd;
	while(1){
		char buffer[1024] = {0}; 
    	char *hello = "Hello from server";

    	send(sock_fd , hello , strlen(hello) , 0 ); 
	    printf("Hello message sent\n"); 
	    int valread = read( sock_fd , buffer, 1024); 
	    printf("%s\n",buffer ); 
	}
}
*/

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

void create_mtorrent_file(vector <string> cmd){
	string tracker_info = server_ip + " " + to_string(server_port);
	char filepath[100], saveName[100];
	//string save_name=cmd[1]+".mtorrent";
	strcpy(filepath, cmd[1].c_str());
	strcpy(saveName, cmd[2].c_str());
	struct stat sb;
	//char curr_path[200];//="foo.txt";
	//strcpy(curr_path, cmd[2].c_str());
	int piece_size=512*1024, total_pieces, size, last_piece;
	string hash="";
	
	if (stat(filepath, &sb) == -1) {
        perror("stat");
        exit(EXIT_FAILURE);
    }
    size=sb.st_size;
    
    total_pieces = size/piece_size;
    if(size % piece_size == 0)
   		last_piece = 512*1024;
   	else{
   		total_pieces++;
   		last_piece = size % piece_size;
   	}
    
	ifstream input_file;
	//input_file.open("foo.txt");
	input_file.open(filepath);
	unsigned char input[piece_size], SHA_hash[40];
	//cout<<total_pieces<<" "<<last_piece<<" "<<size<<endl;
	ofstream stream;
	//stream.open("filename.mtorrent");
	stream.open(saveName);
	if( !stream ){
        cout << "Opening file failed" << endl;
        exit(0);
	}
	//stream << "filename.pdf" << endl;
	stream << tracker_info << endl;
	stream << filepath << endl;
	stream << size << endl;

	while(total_pieces--){
		input_file.read((char*)input, piece_size);
		if(total_pieces > 1){
			SHA1(input, piece_size , SHA_hash);
		}
		else{
			//cout<<"last\n";
			SHA1(input, last_piece , SHA_hash);
		}
		//cout<<SHA_hash;
		string piece((char*)SHA_hash);
		//stream << SHA_hash << endl;
		hash += piece;		
	}
	stream << hash << endl;
    //string path="/home/rishabh/F/torrent/foo.txt";
    //stream << curr_path << endl;
    shareHASH=hash;
}

void shareCmd(string command, vector <string> cmd, int sock){
	int len;
	char buffer[1024] = {0};
	create_mtorrent_file(cmd);
	command = command + " " + shareHASH;
	len=command.length();
	char send_cmd[len];
	strcpy(send_cmd, command.c_str());
	send(sock , send_cmd , strlen(send_cmd) , 0 );
	int valread = read( sock , buffer, 1024); 
	printf("%s\n",buffer );
}

void removeCmd(string command, vector <string> cmd, int sock){
	int len;
	char buffer[1024] = {0};
	len=command.length();
	char send_cmd[len];
	strcpy(send_cmd, command.c_str());
	send(sock , send_cmd , strlen(send_cmd) , 0 );
	int valread = read( sock , buffer, 1024); 
	printf("%s\n",buffer );
}

void getCmd(string command, vector <string> cmd, int sock){
	cout<<"in client getCmd()...\n";
	cout<<command<<endl;
	int i=cmd[1].length()-1, len;
	string tmp;
	while(cmd[1][i]!='.')
		i--;
	tmp="get " + cmd[1].substr(0,i);
	cout<<"in client - "<<tmp<<endl;
	char buffer[1024] = {0};
	len=tmp.length();
	char send_cmd[len];
	strcpy(send_cmd, tmp.c_str());
	
	send(sock , send_cmd , strlen(send_cmd) , 0 );
	int valread = read( sock , buffer, 1024); 
	printf("%s\n",buffer );
}

void execute_cmd(string command, vector <string> cmd, int sock){
	if(cmd[0]=="share"){
		shareCmd(command, cmd, sock);
	}
	else if(cmd[0]=="remove"){
		removeCmd(command, cmd, sock);
	}
	else if(cmd[0]=="get"){
		cout<<"in client get if()...\n";
		getCmd(command, cmd, sock);
	}
}



void *Client_AS_Seed(void *client_IP){
    char *client_IP_ADDR = (char*)client_IP;
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
    address.sin_addr.s_addr = inet_addr(client_IP_ADDR);//INADDR_ANY; 
    address.sin_port = htons( client_port ); 
       
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
    cout<<"client as seed is listening...\n";
    while(1){
    	if ((new_socket = accept(server_fd, (struct sockaddr *)&address,  
	                       (socklen_t*)&addrlen))<0) 
	    { 
	        perror("accept"); 
	        exit(EXIT_FAILURE); 
	    } 
    }
}



int main(int argc, char const *argv[]) 
{ 
	pthread_t thread_id; 
	if(argc!=5){
		cout<<"Invalid no. of args\n";
		exit(0);
	}
	client_port=atoi(argv[2]);
	string ip(argv[1]);
	client_ip=ip;
	cout<<client_ip<<"  "<<client_port<<endl;
	int tracker_port=atoi(argv[4]);
	string tracker_ip(argv[3]);
	cout<<tracker_ip<<"  "<<tracker_port<<endl;
	//return 0;
	/*if (pthread_create(&thread_id, NULL, Client_AS_Seed, (void *)&argv[1]) < 0)
    {
        perror("\ncould not create thread\n");
    }*/

	string command;
	//pthread_t thread_id;
    int sock = 0, valread; 
    struct sockaddr_in serv_addr; 
    //char *hello = "Hello from client"; 
    char buffer[1024] = {0}; 
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
    { 
        printf("\n Socket creation error \n"); 
        return -1; 
    } 
    cout<<"after socket()...\n";
    memset(&serv_addr, '0', sizeof(serv_addr));
    serv_addr.sin_family = AF_INET; 
    serv_addr.sin_port = htons(tracker_port); 
       
    // Convert IPv4 and IPv6 addresses from text to binary form 
    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0)  
    { 
        printf("\nInvalid address/ Address not supported \n"); 
        return -1; 
    } 
    cout<<"after inet_pton()...\n";
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) 
    { 
        printf("\nConnection Failed \n"); 
        return -1; 
    } 
    cout<<"connected\n";
  /*  if (pthread_create(&thread_id, NULL, clientservice, (void *)&sock) < 0)
        {
            perror("\ncould not create thread\n");
        }*/
	
	server_ip=inet_ntoa(serv_addr.sin_addr);
    //printf("%d\n",(int) ntohs(serv_addr.sin_port));
    server_port=(int) ntohs(serv_addr.sin_port);
    //cout << "tracker :" << clsource << endl;

    //Client_AS_Seed(argv[1], client_port);
    


	while(1){
		getline(cin, command);
		vector <string> cmd;
		tokenize(command, cmd);
		//for(auto i : cmd)
		//	cout<<i<<" ";
		//cout<<endl;
		execute_cmd(command, cmd, sock);
		/*char send_cmd[1024];
		strcpy(send_cmd, command.c_str());
		send(sock , send_cmd , strlen(send_cmd) , 0 );
		valread = read( sock , buffer, 1024); 
		printf("%s\n",buffer );*/ 
	}

	
    return 0; 
} 
