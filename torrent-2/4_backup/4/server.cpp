#include "header.h"
#define PORT 8080 
using namespace std;

map <int, int> sock2idx;
vector<int> sock_n( 10, 0); 
CLIENT client[10];
int n=0;


void *serverservice(void *socket_desc)	//socket_desc
{
	int new_socket = *(int *)socket_desc;
	int idx=sock2idx[new_socket];
	cout<<client[idx].ip<<"\n"<<client[idx].IP<<"\n"<<client[idx].portNo<<"\n"<<client[idx].sock<<endl;
	/*
    char serverreply[1000]={0};
    strcpy(serverreply, clientreplymsg.c_str());
    //cout<<"serverreply : "<<serverreply<<endl;
    send(new_socket, serverreply, strlen(serverreply), 0);	
    */
    while(1){
    	char buffer[1024]={0};
		int valread = read( new_socket , buffer, 1024); 
		char send_cmd[1024]="bye" ;
		send(new_socket , send_cmd , strlen(send_cmd) , 0 );
		printf("%s\n",buffer );
	}
}

int main(int argc, char *argv[])
{
	int args[2];
    pthread_t thread_id;
    if (argc != 3)
    {
        cout << "Invalid Argument !!!" << endl;
    }
    else
    {
    	int tracker_port=atoi(argv[2]);
        int server_fd, new_socket;
        struct sockaddr_in address;
        int opt = 1;
        int addrlen = sizeof(address);

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
        address.sin_addr.s_addr = inet_addr(argv[1]);	//trackersocket1.ip
        address.sin_port = htons(tracker_port);			//trackersocket1.port

        // Forcefully attaching socket to the port 8080
        if (bind(server_fd, (struct sockaddr *)&address,
                 sizeof(address)) < 0)
        {
            perror("bind failed");
            exit(EXIT_FAILURE);
        }
        if (listen(server_fd, 10) < 0)
        {
            perror("listen");
            exit(EXIT_FAILURE);
        }
        n=0;
        while (1)
        {
        	cout<<"listening...\n";								/*client[n].clientAddr*/
            if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen)) < 0)
            {
                perror("Error in accept connection");
                exit(EXIT_FAILURE);
            }
            cout<<"connected  "<<new_socket<<endl;
            client[n].ip=inet_ntoa(address.sin_addr);
            //cout<<"1\n";
            strcpy( client[n].IP , (client[n].ip).c_str());
		    //cout<<"2\n";
		    client[n].portNo=(int) ntohs(address.sin_port);
		    //client[n].portNo=;//(int) ntohs(address.sin_port);
		    
		    //cout<<"3\n";
		    client[n].sock=new_socket;
		    //cout<<"4\n";
		    //cout<<client[n].ip<<"\n"<<client[n].IP<<"\n"<<client[n].portNo<<"\n"<<client[n].sock<<endl;
		    sock2idx[new_socket]=n;
		    if (pthread_create(&thread_id, NULL, serverservice, (void *)&new_socket) < 0)
            {
                perror("\ncould not create thread\n");
            }
            n++;
        }
    }
}