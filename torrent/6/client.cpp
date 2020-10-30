#include "header.h"

#define CSIZE 512 * 1024


int main(int argc, char const *argv[])
{

    
    if (argc != 5)
    {
        cout << "Invalid Argument in client!!!" << endl;
    }
    else
    {
        
        
        pthread_t cserverid;
        /*if (pthread_create(&cserverid, NULL, seederserverservice, (void *)&clientsocketstr) < 0)
        {
            perror("\ncould not create thread in client side\n");
        }*/

        //socket programming on client side
        int sock = 0;
        struct sockaddr_in serv_addr;
        if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        {
            printf("\n Socket creation error in client side\n");
            return -1;
        }

        memset(&serv_addr, '0', sizeof(serv_addr));
        serv_addr.sin_family = AF_INET;
        serv_addr.sin_port = htons(atoi(argv[4]));

        //Convert IPv4 and IPv6 addresses from text to binary form
        if (inet_pton(AF_INET, argv[3], &serv_addr.sin_addr) <= 0)
        {
            printf("\nClient File  : Invalid address/ Address not supported \n");
            return -1;
        }

        if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
        {
            printf("\nConnection Failed in client side\n");
            return -1;
        }

                  
            
            
        cout<<"connected\n";
    }

    return 0;
}