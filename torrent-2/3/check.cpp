#include "header.h"
#define PORT 8080 
using namespace std;


int main(int argc, char *argv[])
{
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

        while (1)
        {
        	cout<<"listening...\n";
            if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen)) < 0)
            {
                perror("Error in accept connection");
                exit(EXIT_FAILURE);
            }
            cout<<"connected\n";
            if (pthread_create(&thread_id, NULL, serverservice, (void *)&new_socket) < 0)
            {
                perror("\ncould not create thread\n");
            }
        }
    }
}