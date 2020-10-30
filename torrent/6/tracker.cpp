#include "header.h"

//#define PORT 7000

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
void *serverservice(void *socket_desc)
{
    int new_socket = *(int *)socket_desc;
    while (1)
    {
        int closeflag = 0;
        char buffer[1024] = {0};
        int rc = read(new_socket, buffer, 1024);
        if (rc == 0)
        {
            close(new_socket);
            return socket_desc;
        }
        writelog("Tracker get Data from Client : " + string(buffer));
        string clientreplymsg;

        string data = string(buffer);
        //vector<string> tokens1=stringProcessing(data,'#');
        

        // stringstream check2(data);
        // string intermediate1;
        // // Tokenizing w.r.t. space '#'
        // while (getline(check2, intermediate1, '#'))
        // {
        //     tokens1.push_back(intermediate1);
        // }

        if (tokens1[0] == "share")
        {
            clientreplymsg = executeshare(tokens1, data, seederfilep);
        }
        else if (tokens1[0] == "get")
        {
            clientreplymsg = executeget(tokens1);
        }
        else if (tokens1[0] == "remove")
        {
            clientreplymsg = executeremove(tokens1, data, seederfilep);
        }
        

    return socket_desc;
}
*/
int main(int argc, char *argv[])
{
    //socketclass trackersocket1;
    //socketclass trackersocket2;
    pthread_t thread_id;
    if (argc != 3)
    {
        cout << "Invalid Argument !!!" << endl;
    }
    else
    {
        
        /*trackersocket1.setsocketdata(string(argv[1]));
        trackersocket2.setsocketdata(string(argv[2]));
        seederfilep = argv[3];
        trackerlogpath = argv[4];
        ofstream myfile(trackerlogpath, std::ios_base::out);
        myfile.close();
*/
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
        address.sin_addr.s_addr = inet_addr(argv[1]);
        address.sin_port = htons(atoi(argv[2]));

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
            if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen)) < 0)
            {
                perror("Error in accept connection");
                exit(EXIT_FAILURE);
            }
            cout<<"connected\n";
            /*if (pthread_create(&thread_id, NULL, serverservice, (void *)&new_socket) < 0)
            {
                perror("\ncould not create thread\n");
            }*/

            //Now join the thread , so that we dont terminate before the thread
            //pthread_join( thread_id , NULL);
            // cout<<"New Client created assigned"<<endl;

            // if (new_socket < 0)
            // {
            //     perror("accept failed");
            //     //return 1;
            // }
        }
    }
}