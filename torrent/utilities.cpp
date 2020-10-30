#include "header.h"

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