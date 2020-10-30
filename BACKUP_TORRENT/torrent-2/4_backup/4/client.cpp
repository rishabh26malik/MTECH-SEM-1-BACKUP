#include "header.h" 
#define PORT 8080 
using namespace std;
CLIENT client[10];
int k=0;
map <int, int> sock2idx;

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

        //continuously listening to client for his entring command
        
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
		}

    }

    return 0;
}
