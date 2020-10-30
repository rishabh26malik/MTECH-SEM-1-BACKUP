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

using namespace std;

struct SOCKET{
	string ip;
	int portNo;
	int group;
	int index;
	int sockID;
	struct sockaddr_in clientAddr;
	int len;
};
typedef struct SOCKET SOCKET;
