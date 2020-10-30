#include "header.h"
SOCKET tracker;
SOCKET clients[10];
int total_clients=0;
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
void SetupServer(SOCKET &server, int i){
	
	
}
*/

int main(int argc, char *argv[]){
	int n=0;
	processArgs(tracker, argv[1]);
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
    while (1 )
    { 
		socklen_t len = sizeof(client_address);
		//cout << "Listening On Port " << port << endl;
		// Accept Incoming Connections
		clients[n].sockID = accept(server_sock, (struct sockaddr*) &clients[n].clientAddr,&len/*&client[n].len*/);
		clients[n].index = n;
		total_clients++;
        if (clients[n].sockID < 0 )
        {
            cerr << "Cannot accept connection" << endl;
            return 0;
        }
        else
        {
        	clsource=inet_ntoa(client[n].clientAddr.sin_addr);
        	client_port=(int) ntohs(clients[n].clientAddr.sin_port);
        	clients[n].ip=clsource;
        	clients[n].port=client_port;
        }	
		//name=get_name(n);
        //client[n].name=name;
        //AddClient(client_sock,name,clsource,client_port);
        cout<<name<<" "<<clsource<<" "<<client_port<<" "<<client[n].index<<endl;
   		//pthread_create(&thread[n], NULL, chat, (void *) &client[n]);
        n++;
    }


	return 0;
}