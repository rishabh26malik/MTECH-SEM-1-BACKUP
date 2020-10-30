#include "header.h" 
#define PORT 8080 
using namespace std;
string server_ip;
int server_port;
string shareHASH;
int client_port;
string client_ip;

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

void create_user(string command, vector <string> cmd, int sock){
	int len;
	char buffer[1024] = {0};
	while(1){
		len=command.length();
		char send_cmd[len];
		strcpy(send_cmd, command.c_str());
		send(sock , send_cmd , strlen(send_cmd) , 0 );
		int valread = read( sock , buffer, 1024);
		string replyStr(buffer);
		printf("%s\n",buffer );
		if(replyStr=="USER NAME ALREADY IN USE"){
			string usrname;
			cout<<"enter username again : ";
			cin>>usrname;
			cmd[1]=usrname;
			command="create_user "+usrname+" "+cmd[2];
			cout<<"updated cmd --  "<<command<<endl;
			//reply=create_user(cmd[0]+" "+usrname+" ",cmd[2], cmd, sock);
		}
		else
			break; 
	}
	//printf("%s\n",buffer );
}

void login(string command, vector <string> cmd, int sock){
	int len,attempts=4;
	//char buffer[1024] = {0};
	while(1){
		if(attempts==0){
			cout<<"all attempts exhausted...!!! so awk....!!!\n";
			break;
		}
		len=command.length();
		char send_cmd[len];
		strcpy(send_cmd, command.c_str());
		fflush(stdout);
		send(sock , send_cmd , strlen(send_cmd) , 0 );
		char buffer[1024] = {0};
		int valread = read( sock , buffer, 1024);
		string replyStr(buffer);
		printf("%s\n",buffer );
		if(replyStr=="USERNAME OR PSW IS WRONG"){
			string usr_psw;
			//cout<<"U HAVE "+to_string(attempts)+" ATTEMPTS REMAINING\n";
			cout<<"enter usrname password again : ";
			getline(cin,usr_psw);
			command="login "+usr_psw;
			cout<<"updated cmd --  "<<command<<endl;
			//reply=create_user(cmd[0]+" "+usrname+" ",cmd[2], cmd, sock);
		}
		else
			break; 
		attempts--;
	}
	//printf("%s\n",buffer );
}

void create_group(string command, vector <string> cmd, int sock){
	int len,attempts=4;
	while(1){
		if(attempts==0){
			cout<<"all attempts exhausted...!!! so awk....!!!\n";
			break;
		}
		len=command.length();
		char send_cmd[len];
		strcpy(send_cmd, command.c_str());
		fflush(stdout);
		send(sock , send_cmd , strlen(send_cmd) , 0 );
		char buffer[1024] = {0};
		int valread = read( sock , buffer, 1024);
		string replyStr(buffer);
		printf("%s\n",buffer );
		if(replyStr=="GROUP ID NOT UNIQUE"){
			string grpId;
			//cout<<"U HAVE "+to_string(attempts)+" ATTEMPTS REMAINING\n";
			cout<<"enter group id again : ";
			getline(cin,grpId);
			command="create_group "+grpId;
			cout<<"updated cmd --  "<<command<<endl;
			//reply=create_user(cmd[0]+" "+usrname+" ",cmd[2], cmd, sock);
		}
		else
			break; 
		attempts--;
	}
}



void join_group(string command, vector <string> cmd, int sock){
	int len,attempts=4;
	while(1){
		if(attempts==0){
			cout<<"all attempts exhausted...!!! so awk....!!!\n";
			break;
		}
		len=command.length();
		char send_cmd[len];
		strcpy(send_cmd, command.c_str());
		fflush(stdout);
		send(sock , send_cmd , strlen(send_cmd) , 0 );
		char buffer[1024] = {0};
		int valread = read( sock , buffer, 1024);
		string replyStr(buffer);
		printf("%s\n",buffer );
		if(replyStr=="NO SUCH GROUP"){
			string grpId;
			//cout<<"U HAVE "+to_string(attempts)+" ATTEMPTS REMAINING\n";
			cout<<"enter group id again : ";
			getline(cin,grpId);
			command="join_group "+grpId;
			cout<<"updated cmd --  "<<command<<endl;
			//reply=create_user(cmd[0]+" "+usrname+" ",cmd[2], cmd, sock);
		}
		else
			break; 
		attempts--;
	}
}

void list_requests(string command, vector <string> cmd, int sock){
	cout<<"in list_requests client...\n";
	int len,attempts=4;
	while(1){
		if(attempts==0){
			cout<<"all attempts exhausted...!!! so awk....!!!\n";
			break;
		}
		len=command.length();
		char send_cmd[len];
		strcpy(send_cmd, command.c_str());
		fflush(stdout);
		send(sock , send_cmd , strlen(send_cmd) , 0 );
		char buffer[1024] = {0};
		int valread = read( sock , buffer, 1024);
		string replyStr(buffer);
		printf("%s\n",buffer );
		if(replyStr=="NO SUCH GROUP"){
			string grpId;
			//cout<<"U HAVE "+to_string(attempts)+" ATTEMPTS REMAINING\n";
			cout<<"enter group id again : ";
			getline(cin,grpId);
			command="list_requests "+grpId;
			cout<<"updated cmd --  "<<command<<endl;
			//reply=create_user(cmd[0]+" "+usrname+" ",cmd[2], cmd, sock);
		}
		else
			break; 
		attempts--;
	}
}

void leave_group(string command, vector <string> cmd, int sock){
	int len,attempts=4;
	while(1){
		if(attempts==0){
			cout<<"all attempts exhausted...!!! so awk....!!!\n";
			break;
		}
		len=command.length();
		char send_cmd[len];
		strcpy(send_cmd, command.c_str());
		fflush(stdout);
		send(sock , send_cmd , strlen(send_cmd) , 0 );
		char buffer[1024] = {0};
		int valread = read( sock , buffer, 1024);
		string replyStr(buffer);
		printf("%s\n",buffer );
		if(replyStr=="NO SUCH GROUP"){
			string grpId;
			//cout<<"U HAVE "+to_string(attempts)+" ATTEMPTS REMAINING\n";
			cout<<"enter group id again : ";
			getline(cin,grpId);
			command="leave_group "+grpId;
			cout<<"updated cmd --  "<<command<<endl;
			//reply=create_user(cmd[0]+" "+usrname+" ",cmd[2], cmd, sock);
		}
		else
			break; 
		attempts--;
	}
}

void accept_request(string command, vector <string> cmd, int sock){
	cout<<"in accept_request() client...\n";
	int len,attempts=4;
	while(1){
		if(attempts==0){
			cout<<"all attempts exhausted...!!! so awk....!!!\n";
			break;
		}
		len=command.length();
		char send_cmd[len];
		strcpy(send_cmd, command.c_str());
		fflush(stdout);
		send(sock , send_cmd , strlen(send_cmd) , 0 );
		char buffer[1024] = {0};
		int valread = read( sock , buffer, 1024);
		string replyStr(buffer);
		printf("%s\n",buffer );
		if(replyStr=="INVALID GROUP OR USER ID"){
			string grp_usr_Id;
			//cout<<"U HAVE "+to_string(attempts)+" ATTEMPTS REMAINING\n";
			cout<<"enter group_id and user_id again : ";
			getline(cin,grp_usr_Id);
			command="accept_request "+grp_usr_Id;
			cout<<"updated cmd --  "<<command<<endl;
			//reply=create_user(cmd[0]+" "+usrname+" ",cmd[2], cmd, sock);
		}
		else
			break; 
		attempts--;
	}
}

void list_groups(string command, vector <string> cmd, int sock){
	int len=command.length();
	char send_cmd[len];
	strcpy(send_cmd, command.c_str());
	fflush(stdout);
	send(sock , send_cmd , strlen(send_cmd) , 0 );
	char buffer[1024] = {0};
	int valread = read( sock , buffer, 1024);
	string replyStr(buffer);
	printf("%s\n",buffer );
}

string getSHA_Hash(vector <string> cmd/*, vector <string> &pieces*/){
	char filepath[100];
	strcpy(filepath, cmd[1].c_str());
	string hash="", piece_wise="";
	struct stat sb;
	int piece_size=512*1024, total_pieces, size, last_piece;
	int no_of_pieces;
	if (stat(filepath, &sb) == -1) {
        perror("stat : no such file or wrong path\n");
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
   	no_of_pieces=total_pieces;
   	cout<<size<<" "<<total_pieces<<" "<<last_piece<<endl;
   	ifstream input_file;
	input_file.open(filepath);
	unsigned char input[piece_size], SHA_hash[20*total_pieces];
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
		//pieces.push_back(piece);
		piece_wise += piece+" ";		
	}
	return hash;
	//cout<<hash<<endl<<endl<<piece_wise<<endl;
	//return to_string(no_of_pieces)+" "+hash+" "+piece_wise;
}

void upload_file(string command, vector <string> cmd, int sock){
	//vector <string> pieces;
	string SHA_hash=getSHA_Hash(cmd);
	//cout<<SHA_hash<<endl;
	//cout<<endl<<endl;
	//cout<<"----------------\n";
	/*for(auto i : pieces){
		cout<<i.length()<<"   "<<i<<endl<<endl;;
	}*/
	string filename="";
	int i=cmd[1].length()-1;
	while(cmd[1][i]!='/'){
		filename=cmd[1][i]+filename;
		i--;
	}

	command="upload_file "+filename+" "+cmd[2]+" "+to_string(SHA_hash.length())+" "+SHA_hash;
	int len=command.length();
	char send_cmd[len];
	strcpy(send_cmd, command.c_str());
	fflush(stdout);
	send(sock , send_cmd , strlen(send_cmd) , 0 );
	char buffer[1024] = {0};
	int valread = read( sock , buffer, 1024);
	string replyStr(buffer);
	printf("%s\n",buffer );

}

void list_files(string command, vector <string> cmd, int sock){
	int len=command.length();
	char send_cmd[len];
	strcpy(send_cmd, command.c_str());
	fflush(stdout);
	send(sock , send_cmd , strlen(send_cmd) , 0 );
	char buffer[1024] = {0};
	int valread = read( sock , buffer, 1024);
	string replyStr(buffer);
	printf("%s\n",buffer );	
}

void execute_cmd(string command, vector <string> cmd, int sock){
	string reply;
	if(cmd[0]=="create_user"){
		create_user(command, cmd, sock);
	}
	else if(cmd[0]=="login"){
		login(command, cmd, sock);	
	}
	else if(cmd[0]=="create_group"){
		create_group(command, cmd, sock);	
	}
	else if(cmd[0]=="join_group"){
		join_group(command, cmd, sock);	
	}
	else if(cmd[0]=="list_requests"){
		list_requests(command, cmd, sock);	
	}
	else if(cmd[0]=="leave_group"){
		leave_group(command, cmd, sock);	
	}
	else if(cmd[0]=="list_groups"){
		list_groups(command, cmd, sock);	
	}
	else if(cmd[0]=="accept_request"){
		accept_request(command, cmd, sock);
	}
	else if(cmd[0]=="upload_file"){
		upload_file(command, cmd, sock);
	}
	else if(cmd[0]=="list_files"){
		list_files(command, cmd, sock);
	}
	else{
		cout<<cmd[0]<<","<<cmd[1]<<","<<cmd[2]<<endl;
		cout<<"invalid command\n";
	}
}

int main(int argc, char const *argv[])
{

    if (argc != 5)
    {
        cout << "Invalid Argument in client!!!" << endl;
    }
    else
    {  
        
        //socket programming on client side
        int sock = 0;
        struct sockaddr_in serv_addr, my_addr;
        if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        {
            printf("\n Socket creation error in client side\n");
            return -1;
        }

        my_addr.sin_family = AF_INET; 
	    my_addr.sin_addr.s_addr = INADDR_ANY; 
	    my_addr.sin_port = htons(atoi(argv[2]));

	    if (bind(sock, (struct sockaddr*) &my_addr, sizeof(struct sockaddr_in)) == 0) 
	        printf("Binded Correctly\n"); 
	    else
	        printf("Unable to bind\n");

        memset(&serv_addr, '0', sizeof(serv_addr));
        serv_addr.sin_family = AF_INET;
        serv_addr.sin_port = htons(atoi(argv[4]));		//trackersocket1.port

        //Convert IPv4 and IPv6 addresses from text to binary form
        if (inet_pton(AF_INET, argv[3] , &serv_addr.sin_addr) <= 0)			//trackersocket1.ip
        {
            printf("\nClient File  : Invalid address/ Address not supported \n");
            return -1;
        }
        cout<<"b4 connected\n";
        if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
        {
            printf("\nConnection Failed in client side\n");
            return -1;
        }
        cout<<"connected\n";

        //continuously listening to client for his entring command
        
        while(1){
        	string command;
			getline(cin, command);
			vector <string> cmd;
			tokenize(command, cmd);
			for(auto i : cmd)
				cout<<i<<" ";
			cout<<endl;
			execute_cmd(command, cmd, sock);
			/*char send_cmd[1024], buffer[1024];
			strcpy(send_cmd, command.c_str());
			send(sock , send_cmd , strlen(send_cmd) , 0 );
			int valread = read( sock , buffer, 1024); 
			printf("%s\n",buffer );*/
		}

        /*while (1)
        {
            string msg;

            getline(cin, msg);



            char *clientreply = new char[1024];
            strcpy(clientreply, msg.c_str());
            //cout<<"clientreply : "<<clientreply<<endl;

            //to send client request to tracker
            send(sock, clientreply, strlen(clientreply), 0);


            //to recieve tracker responce
            char buffer[1024] = {0};
            read(sock, buffer, 1024);
            cout<<buffer<<endl;
                       
        }*/
    }

    return 0;
}
