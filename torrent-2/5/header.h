#include<bits/stdc++.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>
#include <fstream>
#include <strings.h>
#include <stdlib.h>
#include <string>
#include <pthread.h>
#include <openssl/sha.h>
#include <sys/stat.h>
#include <fcntl.h>
using namespace std;

struct SOCKET{
	string ip;
	int portNo;
};
typedef struct SOCKET SOCKET;

struct CLIENT{
	string ip;
	char IP[15];
	int portNo;
	int server_port;
	int sock;
	struct sockaddr_in clientAddr; 
	set <string> grpID;
	int isUser=0;
	string userName, psw;
	int isLoggedIn=0;
};
typedef struct CLIENT CLIENT;

struct FILES_HASH{
	string combinedHash;
	vector <string> pieces;
	int no_of_pieces;
};
typedef struct FILES_HASH FILES_HASH;

struct FILES{
	set <string> grpID;
	int index;
};
typedef struct FILES FILES;