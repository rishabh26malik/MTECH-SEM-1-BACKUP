#include "header.h"
#define PORT 8080 
using namespace std;

void *serverservice(void *sockFd){
	int sock_fd = *(int *)sockFd;
	cout<<"server in thread.....\n";
	while(1){
		char buffer[1024] = {0}; 
    	char hello[1024] = "server - received";
		int valread = read( sock_fd , buffer, 1024); 
	    printf("%s\n",buffer ); 
	    send(sock_fd , hello , strlen(hello) , 0 ); 
	    //printf("\n");
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
	    cout<<"connected\n";
	 	if (pthread_create(&thread_id, NULL, serverservice, (void *)&new_socket) < 0)
        {
            perror("\ncould not create thread\n");
        }
	    
	}
    return 0; 
} 

