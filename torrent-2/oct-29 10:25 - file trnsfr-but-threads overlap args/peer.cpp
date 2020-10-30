#include<stdio.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<errno.h>
#include<bits/stdc++.h>
#include<fcntl.h>
#include<pthread.h>
#include <arpa/inet.h> 

using namespace std;

void * client(void *temp){
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
    while(1){
        int valread=read(client_socket,buffer,1024);
        printf("%d %d %s\n",getpid(),valread,buffer);
        memset(buffer,'\0',1024);
        if(valread<1024) break;
    }
    close(client_socket);
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
    printf("%s\n",buffer);
    //string to_send="Hi from server";
    char send_buffer[1024]={0};
    char actual_path[1024]={0};
    if(realpath(buffer,actual_path)==NULL){
        printf("Path not found\n");
        close(client_socket);
        return NULL;
    }
    printf("actual path:%s %s\n",buffer,actual_path);
    int fd=open(buffer,S_IRUSR);
    printf("%d",fd);
    if(fd<0){
        printf("File open error %d",errno);
        close(client_socket);
        return NULL;
    }
    int bytes_read;
    printf("reading file\n");
    while((bytes_read=read(fd,send_buffer,1024))>0){
        //printf("%d %s",bytes_read,send_buffer);
        write(client_socket,send_buffer,strlen(send_buffer));
        memset(send_buffer,'\0',1024);
        if(bytes_read<1024) {
            //strcpy(send_buffer,"quit");
            break;
        }
    }
    printf("FIle sent, con closed\n");
    close(fd);
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
        printf("Socket creation error %d\n",errno);
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

int main(int argc,char *argv[]){
    pthread_t t1,t2;
    //printf("%d\n",argc);
    if(argc!=2){
        printf("No Port\n");
        return 0;
    }
    int port=atoi(argv[1]);
    pthread_create(&t1,NULL,server,&port);
    int input_port;
    scanf("%d",&input_port);
    pthread_create(&t2,NULL,client,&input_port);
    pthread_join(t1,NULL);
    pthread_join(t2,NULL);
}