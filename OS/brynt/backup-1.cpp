


						//   BACKUP-1



/*#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include<bits/stdc++.h>
#include <unistd.h>
*/
#include<iostream>
#include <sys/ioctl.h> //ioctl() and TIOCGWINSZ
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

vector <string> DirList;
int mode, cursor_pos;
int row_len, dir_len;
/*
dir_len = # of dir/files in DirList
*/

int getch(void)
{
	int ch;
	struct termios oldt;
	struct termios newt;
	tcgetattr(STDIN_FILENO, &oldt); 
	newt = oldt;  
	newt.c_lflag &= ~(ICANON | ECHO); 
	tcsetattr(STDIN_FILENO, TCSANOW, &newt);
	ch = getchar(); 
	tcsetattr(STDIN_FILENO, TCSANOW, &oldt); 
	return ch; 
}

void display(int start, int end){
	cout<<"\033c";//clear screen
	while(start < end){
		cout<<DirList[start]<<endl;
		start++;
	}
} 

/*
void navigate(){
	
		
		if(key == '.') {
            exit(0);
        }
}
*/
int main()
{
	int start=0,end;
	char key;
	mode=1;		// 1-normal mode
	char path[500]="/home/rishabh/";
	if(chdir(path)<0){
		cout<<"error"<<endl;
		exit(0);
	}
	
	DIR *directory;
	dirent *fileInDir;
	directory=opendir(path);
	while((fileInDir=readdir(directory))!=NULL){
		string fileName(fileInDir->d_name);
		if(fileName[0]!='.')
			DirList.push_back(fileName);
	}
	dir_len=DirList.size();
	/*for(auto i : DirList){
		cout<<i<<endl;
	}*/
	char buffer[256];
	cout<<getcwd(buffer, 256)<<endl;

	struct winsize size;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
	row_len=size.ws_row-4;
	cursor_pos=(dir_len > row_len) ? row_len : dir_len;
	
	end=cursor_pos;
	
	display(start, cursor_pos);

	while(1){
		//struct winsize size;
		//ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
		//cout<<size.ws_row<<" "<<size.ws_row<<endl;
		row_len=size.ws_row-4;
		//cursor_pos=(dir_len > row_len) ? row_len : dir_len;
	
		//end=cursor_pos+row_len;
		//if(start>=0 && end<dir_len)
		//	display(cursor_pos, cursor_pos+row_len);
		if(mode==1)		// normal mode
		{
			key=getch();
			if(key==27){
				key=getch();
				key=getch();
				if(key=='A'){
					//cursor_pos--;
					if(cursor_pos==start  && start==0)
						continue;
					else if(cursor_pos > start){
						cursor_pos--;
						printf("\033[1A");
					}
					else if(cursor_pos == start && start > 0){
						start--;
						cursor_pos--;
						end--;
						//if(end < dir_len){
							display(start,end);
						//}
						/*if(dir_len-start > row_len)
							display(start,start+row_len);*/
						
					}
					
				}
				else if(key=='B'){
					//cursor_pos++;
					if(cursor_pos==end && end==dir_len){
						continue;
					}
					else if(cursor_pos < end){
						cursor_pos++;
						printf("\033[1B");
					}
					else if(cursor_pos == end && end < dir_len){
						end++;
						cursor_pos++;
						start++;
						display(start,end);
					}
					/*
					if(cursor_pos+1 > row_len && cursor_pos+1 < dir_len){
						start++;
						cursor_pos++;
						display(start,cursor_pos);
					}
					else if( cursor_pos+1 >= dir_len ){
						continue;
						//printf("\033[1B");	do nothing
					}
					else{
						if(dir_len <= row_len && cursor_pos < dir_len)
							printf("\033[1B");
						else if(dir_len > row_len && cursor_pos-start+1 < row_len)
							printf("\033[1B");
					}	*/
					/*else if(cursor_pos < dir_len-1 && cursor_pos-start < row_len){
						printf("\033[1B");
					}*/
					//}
				}	
		
			}	
		}
		//cout << "\033[2J\033[1;1H";	// to clear screen
		//cout<<"\033c";//clear screen
	}
	//cout<<"\u001b[1A";
	//cout<<"\u001b["<<56-12+2<<"A";
	//cout<<"\033c";//clear screen
	//cout<<path<<endl<<endl;
	return 0;
}