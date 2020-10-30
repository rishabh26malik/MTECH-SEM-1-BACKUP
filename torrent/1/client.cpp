#include "header.h" 
#define PORT 8080 
using namespace std;
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
int main(int argc, char const *argv[]) 
{ 
	pthread_t thread_id;
    int sock = 0, valread; 
    struct sockaddr_in serv_addr; 
    char *hello = "Hello from client"; 
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
    send(sock , hello , strlen(hello) , 0 ); 
	printf("Hello message sent\n"); 
	valread = read( sock , buffer, 1024); 
	printf("%s\n",buffer ); 
    return 0; 
} 
