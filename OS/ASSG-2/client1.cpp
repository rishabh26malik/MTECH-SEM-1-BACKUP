#include "header.h"

int clientSkt;
struct sockaddr_in server_address;
struct sockaddr_in client_address;
struct hostent *server;
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
/*
void setupClient(SOCKET client){
	int s_addrlen = sizeof(server_address);
	if((client.portNo > 65535) || (client.portNo < 1024))
    {
        cerr << "Please enter a port number between 1024 - 65535" << endl;
        exit(EXIT_FAILURE);
    }
    //create socket
    clientSkt = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    
    if(clientSkt < 0)
    {
        cerr << "Cannot open client socket" << endl;
        exit(EXIT_FAILURE);
    }
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY;
    server_address.sin_port = htons(5000);
    int connection = connect(clientSkt,(struct sockaddr *) &server_address, sizeof(server_address));
    
    if (connection < 0)
    {
        cerr << "Cannot Connect!" << endl;
        exit(EXIT_FAILURE);
    }

    string clsource=inet_ntoa(server_address.sin_addr);
    printf("%d\n",(int) ntohs(server_address.sin_port));
    int client_port=(int) ntohs(server_address.sin_port);
    cout << "tracker :" << clsource << endl;

    printf("connection made\n");
}
*/
void setupClient(SOCKET client){
    int s_addrlen = sizeof(server_address);
    if((client.portNo > 65535) || (client.portNo < 1024))
    {
        cerr << "Please enter a port number between 1024 - 65535" << endl;
        exit(EXIT_FAILURE);
    }
    clientSkt = socket(AF_INET, SOCK_STREAM, 0);
    
    if(clientSkt < 0)
    {
        cerr << "Cannot open socket" << endl;
        exit(EXIT_FAILURE);
    }
    
    /*server = gethostbyname(client.ip);//char array as arg
    
    if(server == NULL)
    {
        cerr << "Host does not exist" << endl;
        return 0;
    }*/
    

    //getsockname(clientSkt, (struct sockaddr*) &server_address, (socklen_t*) &s_addrlen);  //****
    //printf("Start Server on: %s:%d\n", inet_ntoa(server_address.sin_addr), ntohs(server_address.sin_port));//*****

    if(inet_pton(AF_INET, "127.0.0.1", &server_address.sin_addr)<=0)  
    { 
        printf("\nInvalid address/ Address not supported \n"); 
        exit(EXIT_FAILURE); 
    } 

    //bzero((char *) &server_address, sizeof(server_address));
    server_address.sin_family = AF_INET;
    
    //bcopy((char *) server -> h_addr, (char *) &server_address.sin_addr.s_addr, server -> h_length);
    
    server_address.sin_port = htons(5000);
    
    int connection = connect(clientSkt,(struct sockaddr *) &server_address, sizeof(server_address));
    
    if (connection < 0)
    {
        cerr << "Cannot Connect!" << endl;
        exit(EXIT_FAILURE);
    }
    string clsource=inet_ntoa(server_address.sin_addr);
    printf("%d\n",(int) ntohs(server_address.sin_port));
    int client_port=(int) ntohs(server_address.sin_port);
    cout << "tracker :" << clsource << endl;

    printf("connection made\n");
}


int main(int argc, char *argv[])
{
	SOCKET client;
	string command;
	if(argc != 2){
		cout<<"Invalid no. of args\n";
		exit(0);
	}
	processArgs(client, argv[1]);
	cout<<client.ip<<" "<<client.portNo<<endl;
	setupClient(client);
	while(1){
		getline(cin, command);
		vector <string> cmd;
		tokenize(command, cmd);
		for(auto i : cmd)
			cout<<i<<"  ";
		cout<<endl;
		/*char message[300];
        cout << "\rMe:";
        bzero(message, 301);
        cin.getline(message, 300);
     
        send(clientSkt, message, strlen(message),0);*/	
	}
	return 1;
}
