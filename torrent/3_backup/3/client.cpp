#include "header.h" 
#define PORT 8080 
using namespace std;
string server_ip;
int server_port;
string shareHASH;
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

void execute_cmd(string command, vector <string> cmd, int sock){
	if(cmd[0]=="share"){
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
}

int main(int argc, char const *argv[]) 
{ 
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
   
    serv_addr.sin_family = AF_INET; 
    serv_addr.sin_port = htons(PORT); 
       
    // Convert IPv4 and IPv6 addresses from text to binary form 
    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0)  
    { 
        printf("\nInvalid address/ Address not supported \n"); 
        return -1; 
    } 
   
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
