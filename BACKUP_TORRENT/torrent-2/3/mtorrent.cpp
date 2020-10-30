#include "header.h"
#include<iostream>
#include <sys/ioctl.h> 
#include<bits/stdc++.h>
#include<stdlib.h>
#include<fstream>
#include<iostream>
#include<dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <pwd.h>
#include <grp.h>
#include <stdio.h>
#include <unistd.h>
#include <termios.h>
#include<string>
#include<stdlib.h>
#include <sys/types.h>
#include <unistd.h> 
#include <errno.h>  
#include <sys/wait.h>
using namespace std;
int main(){
	struct stat sb;
	char curr_path[]="foo.txt";
	int piece_size=512*1024, total_pieces, size, last_piece;
	string hash="";
	
	if (stat(curr_path, &sb) == -1) {
        perror("stat");
        exit(EXIT_FAILURE);
    }
    size=sb.st_size;
    
    total_pieces = size/piece_size;
    if(size % piece_size == 0)
   		last_piece = 512*1024;
   	else{
   		total_pieces++;
   		last_piece = size % piece_size;
   	}
    
	ifstream input_file;
	input_file.open("foo.txt");
	unsigned char input[piece_size], SHA_hash[40];
	//cout<<total_pieces<<" "<<last_piece<<" "<<size<<endl;
	ofstream stream;
	stream.open("filename.mtorrent");
	if( !stream ){
        cout << "Opening file failed" << endl;
        exit(0);
	}
	stream << "filename.pdf" << endl;
	stream << size << endl;

	while(total_pieces--){
		input_file.read((char*)input, piece_size);
		if(total_pieces > 1){
			SHA1(input, piece_size , SHA_hash);
		}
		else{
			//cout<<"last\n";
			SHA1(input, last_piece , SHA_hash);
		}
		//cout<<SHA_hash;
		string piece((char*)SHA_hash);
		//stream << SHA_hash << endl;
		hash += piece;		
	}
	stream << hash << endl;
    //cout<<hash<<endl;
    //cout<<hash.length()<<endl;
    //cout<<size<<"B"<<endl;
	return 0;
}
