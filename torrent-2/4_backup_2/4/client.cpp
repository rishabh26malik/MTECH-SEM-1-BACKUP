#include "header.h" 
#define PORT 8080 
using namespace std;
CLIENT client[10];
int k=0;
map <int, int> sock2idx;


string server_ip;
int server_port;
string shareHASH;
int client_port;
string client_ip;
//CLIENT client[10];
//int k=0;
//map <int, int> sock2idx;
int myPort;


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


void * client1(void *temp){
    int port=*(int*)temp;
    //free(temp);
    int client_socket;
    client_socket=socket(AF_INET,SOCK_STREAM,0);
    if(client_socket==-1){
        printf("Socket creation error %d\n",errno);
        return 0;
    }
    struct sockaddr_in server_address;
    //int addrlen=sizeof(address);
    char buffer[1024]={0};
    
    //setsockopt(client_socket,)
    if(inet_pton(AF_INET,"127.0.0.1",&server_address.sin_addr)==-1){
        printf("Invalid Address:%d\n",errno);
    }
    server_address.sin_family=AF_INET;
    server_address.sin_port=htons(port);
    int addrlen=sizeof(server_address);

    int socket=connect(client_socket,(struct sockaddr*)&server_address,addrlen);
    if(socket==-1){
        printf("Connect error:%d\n",errno);
        return 0;
    }
    printf("Connected\n");
    string to_send="text.txt";
    write(client_socket,to_send.c_str(),to_send.length());
    //while(1){
        int valread=read(client_socket,buffer,1024);
        printf("%d %d %s\n",getpid(),valread,buffer);
        memset(buffer,'\0',1024);
        //if(valread<1024) break;
    //}
    close(client_socket);
    cout<<"coming out of client thread...\n";
    return NULL;
}


void download_file(string command, vector <string> cmd, int sock){
    //pthread_t thread_id;

    int len=command.length();
    char send_cmd[len];
    strcpy(send_cmd, command.c_str());
    fflush(stdout);
    send(sock , send_cmd , strlen(send_cmd) , 0 );
    char buffer[1024] = {0};
    int valread = read( sock , buffer, 1024);
    string replyStr(buffer);
    printf("%s\n",buffer ); 
    // TILL HERE, GOT INFO OF SEEDS
    ////////////////
    int i;
    len=replyStr.length();
    vector <string> seeds_ip;
    vector <int> seeds_port;
    string tmp="";
    for(i=0;i<len;i++){
        if(replyStr[i]==','){
            seeds_ip.push_back(tmp);
            tmp="";
        } 
        else if(replyStr[i]=='|'){
            cout<<"----\n";
            seeds_port.push_back(stoi(tmp));
            tmp="";
        }
        else
            tmp+=replyStr[i];
    }
    len=seeds_port.size();
    pthread_t thread_id[len];
    for(i=0;i<len;i++){
        cout<<seeds_port[i]<<"   "<<seeds_ip[i]<<endl;
        pthread_create(&thread_id[i],NULL,client1,&seeds_port[i]);
        //pthread_join(t2,NULL);
        /*string str=seeds_ip[i]+" "+to_string(seeds_port[i]);
        char passIP_port[20];
        strcpy(passIP_port, str.c_str());
        if (pthread_create(&thread_id[i], NULL, downloader_thread , (void *)passIP_port) < 0)
        {
            perror("\ncould not create thread in download_file\n");
        }*/
    }
    for(i=0;i<len;i++)
        pthread_join(thread_id[i],NULL);
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
    else if(cmd[0]=="download_file"){
        download_file(command, cmd, sock);
    }
    else{
        cout<<cmd[0]<<","<<cmd[1]<<","<<cmd[2]<<endl;
        cout<<"invalid command\n";
    }
}








void * acceptCon(void * client_socket1){
    int client_socket=*(int*)client_socket1;
    //struct sockaddr_in client=*client1;
    free(client_socket1);
    //free(client1);
    char buffer[1024]={0};
    //printf("Accepted from %lld:%d\n",client.sin_addr,client.sin_port);
    int valread=read(client_socket,buffer,1024);
    //printf("%s\n",buffer);
    cout<<buffer<<endl;
    //string to_send="Hi from server";
    char send_buffer[1024]="Hi from server";
    send(client_socket , send_buffer , strlen(send_buffer) , 0 );

    close(client_socket);
    return NULL;
}


void * server(void *temp){
    int server_socket;
    int port=*(int*)temp;
    //free(temp);
    struct sockaddr_in address;
    //int addrlen=sizeof(address);
    char buffer[1024]={0};
    int opt=1;
    
    server_socket=socket(AF_INET,SOCK_STREAM,0);
    if(server_socket==-1){
    	cout<<"Socket creation error "<<errno<<endl;
        //printf("Socket creation error %d\n",errno);
        return 0;
    }

    if (setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) 
    { 
        perror("setsockopt"); 
        exit(EXIT_FAILURE); 
    } 
    //setsockopt(server_socket,)
    address.sin_addr.s_addr=INADDR_ANY;
    address.sin_family=AF_INET;
    address.sin_port=htons(port);
    int addrlen=sizeof(address);
    if(bind(server_socket,(const struct sockaddr *)&address,addrlen)==-1){
        printf("bind error:%d\n",errno);
        return 0;
    }
    if(listen(server_socket,4)==-1){
        printf("Listen error:%d\n",errno);
        return 0;
    }

    printf("Listening\n");
    while(1){
        struct sockaddr_in client;
        socklen_t client_len=sizeof(client);
        int client_socket=accept(server_socket,(struct sockaddr*)&client,&client_len);
        if(client_socket==-1){
            printf("Accept error:%d\n",errno);
            return 0;
        }
        cout<<ntohs(client.sin_port)<<"  "<<inet_ntoa(client.sin_addr)<<endl;
        pthread_t t;
        struct sockaddr_in *temp=(struct sockaddr_in *)malloc(sizeof(client));
        *temp=client;
        int *client_soc=(int*)malloc(sizeof(int));
        *client_soc=client_socket;
        pthread_create(&t,NULL,acceptCon,client_soc);
        //acceptCon(client_socket,client);
    }
    close(server_socket);
    return 0;
}


int main(int argc, char const *argv[])
{
	pthread_t t1,t2;
    if (argc != 5)
    {
        cout << "Invalid Argument in client!!!" << endl;
    }
    else
    {  
    	pthread_t thread_id;
    	string ip1(argv[1]);
    	string port1(argv[2]);
    	int myPort=stoi(port1);
    	ip1=ip1+" "+port1;
    	char passIP_port[ip1.length()];
    	strcpy(passIP_port, ip1.c_str());
    	pthread_create(&t1,NULL,server,&myPort);
        /*if (pthread_create(&thread_id, NULL, PeerASServer , (void *)passIP_port) < 0)
        {
            perror("\ncould not create thread\n");
        }*/
        //socket programming on client side
        int sock = 0;
        struct sockaddr_in serv_addr, my_addr;
        if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        {
            printf("\n Socket creation error in client side\n");
            return -1;
        }

        /*my_addr.sin_family = AF_INET; 
	    my_addr.sin_addr.s_addr = INADDR_ANY; 
	    my_addr.sin_port = htons(atoi(argv[2]));

	    if (bind(sock, (struct sockaddr*) &my_addr, sizeof(struct sockaddr_in)) == 0) 
	        printf("Binded Correctly\n"); 
	    else
	        printf("Unable to bind\n");*/

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
        send(sock , argv[2] , strlen(argv[2]) , 0 );    //send client's server is running sock port no
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
        /*
        while(1){
        	string command="";
        	cout<<"enter : ";
			getline(cin, command);
			//char ch;
			//while(ch=getchar()!='\n'){
			//	command+=ch;
			//}
			if(command=="abc"){
				int input_port;
			    cout<<"enter port : ";
			    string line;
			    getline(cin, line);
			    stringstream linestream(line);
			    linestream>>input_port;
			    //cin>>input_port;
				pthread_create(&t2,NULL,client1,&input_port);
				pthread_join(t2,NULL);
				cout<<"below join()...\n";
			}
			else{
				cout<<"in else...\n";
				char send_cmd[1024], buffer[1024];
				strcpy(send_cmd, command.c_str());
				cout<<"below strcpy()...\n";
				send(sock , send_cmd , strlen(send_cmd) , 0 );
				cout<<"below send()...\n";
				int valread = read( sock , buffer, 1024);
				cout<<"below read()...\n"; 
				//printf("%s\n",buffer );
				cout<<buffer<<endl;
				//fflush(STDOUT);	
			}
			cout<<"below else...\n";
		}*/

    }

    return 0;
}
