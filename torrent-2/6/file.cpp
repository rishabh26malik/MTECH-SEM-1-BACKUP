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

int main()
{
	string str="";
	/*ofstream stream;
    //stream.open("filename.mtorrent");
    stream.open("saveName.mp4");
    if( !stream ){
        cout << "Opening file failed" << endl;
        exit(0);
    }*/
    string destpath="dest.mp4";
    char *d_path = new char[destpath.length() + 1];
    strcpy(d_path, destpath.c_str());
    ofstream myfile(d_path, ofstream::binary);


	ifstream file1("video2.mp4", ifstream::binary);

    if (!file1)
    {
        cout << "Can't Open file1  : "<< endl;
        //return "-1";
    }
	struct stat fstatus;
    stat("video2.mp4", &fstatus);

    // Logic for deviding file1 into chunks
    long int total_size = fstatus.st_size;
    cout<<total_size<<endl;
    long int chunk_size = 512*1024;

    int total_chunks = total_size / chunk_size;
    int last_chunk_size = total_size % chunk_size;

    if (last_chunk_size != 0) // if file1 is not exactly divisible by chunks size
    {
        ++total_chunks; // add last chunk to count
    }
    else //when file1 is completely divisible by chunk size
    {
        last_chunk_size = chunk_size;
    }
    cout<<total_chunks<<" "<<last_chunk_size<<endl;
    char *chunk_data1 = new char[524288];
    char *chunk_data2 = new char[414514];
        //cout<<strlen(chunk_data)<<endl;

        file1.read(chunk_data1,    
                   524288);
        string a(chunk_data1);
        char ch1[524288];
        strcpy(ch1,a.c_str());
        cout<<strlen(ch1)<<endl;
        myfile.write(ch1, 524288);
        file1.read(chunk_data1,    
                   524288);  
        string b(chunk_data1);
        char ch2[2524288];
        strcpy(ch2,b.c_str()); 
        cout<<strlen(ch2)<<endl;
        myfile.write(ch2, 524288);                   
        file1.read(chunk_data2,    
                   414514);
        string c(chunk_data2);
        char ch3[414514];
        strcpy(ch3,c.c_str()); 
        cout<<strlen(ch3)<<endl;  
        myfile.write(ch3, 414514);                   
        
    // loop to getting each chunk
    /*for (int chunk = 0; chunk < total_chunks; ++chunk)
    {
        int cur_cnk_size;
        if (chunk == total_chunks - 1)
            cur_cnk_size = last_chunk_size;
        else
            cur_cnk_size = chunk_size;
        //cout<<cur_cnk_size<<endl;
        char *chunk_data = new char[cur_cnk_size];
        //cout<<strlen(chunk_data)<<endl;
        file1.read(chunk_data,    
                   cur_cnk_size); 
        string tmp(chunk_data);
        cout<<strlen(chunk_data)<<" "<<tmp.length()<<endl;
        //string tmp(chunk_data);
        //cout<<"------\n";
        str+=tmp;
        //myfile.write(chunk_data, cur_cnk_size);

        //cout<<chunk_data<<endl;
        //stream << chunk_data;
        //cout<<"----------------\n";

    }
    cout<<str.length();
    char out[str.length()]={0};
    strcpy(out, str.c_str());
    myfile.write(out, total_size);*/
    //cout<<str.length()<<endl<<str<<endl;
    /*char destn[20]="destn111.mp3";
    int fd2 = open(destn, O_WRONLY| O_CREAT, 0);
    char out[str.length()];
    strcpy(out, str.c_str());
    long int i=0;
    while( out[i]!= 0){
		write(fd2, &out[i], 1);
		i++;
	}
	close(fd2);
	chmod(destn,S_IRUSR|S_IWUSR);*/
	
    myfile.close();

/*
	unsigned char data[1024];
	FILE *fp1;
	FILE *fp2;
	fp1 = fopen("bb.pdf","r");
	//fp2 = fopen("save.js","w");
	if( fp1 == NULL )
    {
        printf("\n File can not be opened : \n");
        return -1;
    }
    if( fp2 == NULL )
    {
        printf("\n File can not be opened\n");
        return -1;
    }
    //fseek(fp1,0,SEEK_SET);
    //fread(data,100,1,fp1);
    //cout<<data<<endl;
    
    ofstream stream;
    //stream.open("filename.mtorrent");
    stream.open("saveName.pdf");
    if( !stream ){
        cout << "Opening file failed" << endl;
        exit(0);
    }

	int i=0, n=15;
    char A[20]={0};
    memset(data, '\0', sizeof(data));
    while(n--){
    	memset(data, '\0', sizeof(data));
    	fseek(fp1,i,SEEK_SET);
    	fread(data,20,1,fp1);
    	//fwrite(data,20,1,fp2);
   	 	cout<<data;
   	 	stream<<data;
		//myFile.seekg(i); //, ios::beg
		i+=20; 
		//myFile.read(A, 20);
		//string str(A);
		//cout << A << endl;
		//stream << A;
		//cout<<"----------\n";
	}    
	//memset(data, '\0', sizeof(data));
	//fseek(fp1,i,SEEK_SET);
    //fread(data,20,1,fp1);
    //cout<<data; 
	//cout<<endl;
	fclose(fp1);
	//fclose(fp2);
	*/
	return 0;
}