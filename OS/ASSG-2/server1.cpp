#include "header.h"

int serverSkt;
struct sockaddr_in server_address;
struct sockaddr_in client_address;

map <string, string> login_details;
pthread_t thread[10];

void processArgs(SOCKET &server, char *args ){
	int i, port=0, len=strlen(args);
	string IP="";
	for(i=0;i<len;i++){
		if(args[i]==':')
			break;
		IP+=args[i];
	}
	server.ip=IP;
	i++;
	for(;i<len;i++){
		port = port*10 + (args[i]-'0');
	}
	server.portNo=port;
}
/*
void SetupServer(SOCKET server){
	int s_addrlen = sizeof(server_address);
	int opt = 1;
	if((server.portNo > 65535) || (server.portNo < 1024))
    {
        cerr << "Please enter a port number between 1024 - 65535" << endl;
        exit(EXIT_FAILURE);
    }
    
    //create socket
    serverSkt = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    
    if(serverSkt < 0)
    {
        cerr << "Cannot open socket" << endl;
        exit(EXIT_FAILURE);
    }

    // Forcefully attaching socket to the port 5000
    if (setsockopt(serverSkt, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,&opt, sizeof(opt)))
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    bzero((char*) &server_address, sizeof(server_address));
    
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY;
    server_address.sin_port = htons(server.portNo);
    
    //bind socket
    if(bind(serverSkt, (struct sockaddr *)&server_address, sizeof(server_address)) < 0)
    {
        cerr << "Cannot bind to port " << server.portNo << endl;
        exit(EXIT_FAILURE);
    }
    
    //listen on binded socket 
    if(listen(serverSkt, 10)<0)
    {
        cerr << "Cannot listen " << endl;
        exit(EXIT_FAILURE);
    }

}
*/

void SetupServer(SOCKET server){
	int s_addrlen = sizeof(server_address);
	int opt = 1;
	if((server.portNo > 65535) || (server.portNo < 1024))
    {
        cerr << "Please enter a port number between 1024 - 65535" << endl;
        exit(EXIT_FAILURE);
    }
    serverSkt = socket(AF_INET, SOCK_STREAM, 0);
    if(serverSkt <= 0)
    {
        cerr << "Cannot open socket" << endl;
        exit(EXIT_FAILURE);
    }
    if (setsockopt(serverSkt, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,&opt, sizeof(opt)))
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    //bzero((char*) &server_address, sizeof(server_address));
    
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY;
    server_address.sin_port = htons(server.portNo);
    
    //bind socket
    if(bind(serverSkt, (struct sockaddr *)&server_address, sizeof(server_address)) < 0)
    {
        cerr << "Cannot bind to port " << server.portNo << endl;
        exit(EXIT_FAILURE);
    }
   
    //listen on binded socket 
    if(listen(serverSkt, 10)<0)
    {
        cerr << "Cannot listen " << endl;
        exit(EXIT_FAILURE);
    }
}


int main(int argc, char *argv[])
{
	SOCKET server;
	int client_skt;
	socklen_t len;
	//for (int i = 0; i < argc; ++i) 
    //    cout << argv[i] << "\n"; 
	if(argc != 2){
		cout<<"Invalid no. of args\n";
		exit(0);
	}
	processArgs(server, argv[1]);
	cout<<server.ip<<" "<<server.portNo<<endl;
	SetupServer(server);
	while(1){
		len = sizeof(client_address);
		cout<<"B4 ACCEPT\n";
		client_skt = accept(serverSkt, (struct sockaddr *)&server_address, &len);
		cout<<"AFER ACCEPT\n";
		if(client_skt < 0){
			cerr << "Cannot accept connection " << endl;
        	exit(EXIT_FAILURE);
		}
		string clsource=inet_ntoa(client_address.sin_addr);
 		printf("%d\n",(int) ntohs(client_address.sin_port));
  		int client_port=(int) ntohs(client_address.sin_port);
        cout << "Accepted Connection From:" << clsource << endl;
        /*char msg[300]; 
        bzero(msg, 301);
        read_size=read(client_sock, msg, 300);
    
        string rcvmsg (msg);       
        cout<<rcvmsg<<endl;*/
	}
	return 1;
}
