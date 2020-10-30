
							// backup - 3

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

vector <string> DirList;
int mode=1, cursor_pos;			// 1-normal mode
int row_len, dir_len;
string pwd;
/*
dir_len = # of dir/files in DirList
*/

int File_OR_Dir(){			// 1-file , 2-dir

}

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

void printDetails(string file){
	struct stat sb;
	char curr_path[200];
	string file_path=pwd+file;
	strcpy(curr_path, file_path.c_str());
	if (stat(curr_path, &sb) == -1) {
        perror("stat");
        exit(EXIT_FAILURE);
    }
    printf((sb.st_mode & S_IRUSR)? "r":"-");
  printf((sb.st_mode & S_IWUSR)? "w":"-");
  printf((sb.st_mode & S_IXUSR)? "x":"-");
  printf(" ");
  printf((sb.st_mode & S_IRGRP)? "r":"-");
  printf((sb.st_mode & S_IWGRP)? "w":"-");
  printf((sb.st_mode & S_IXGRP)? "x":"-");
  printf(" ");
  printf((sb.st_mode & S_IROTH)? "r":"-");
  printf((sb.st_mode & S_IWOTH)? "w":"-");
  printf((sb.st_mode & S_IXOTH)? "x":"-");

	cout<<"        "<<file<<"          "<<sb.st_size<<"   "<<ctime(&sb.st_mtime);
	//cout << "\033[F";
	//cout<<"   "<<file<<endl;
	//cout<<"   "<<sb.st_size<<"   "<<file<<endl;
    //string modTime (ctime(&sb.st_mtime)); 
	//printf("    %lld B    %s    %s \n",(long long) sb.st_size, ctime(&sb.st_mtime), file);
}

void display(int start, int end){
	cout<<"\033c";//clear screen
	while(start < end){
		printDetails(DirList[start]);
		//cout<<DirList[start]<<endl;
		start++;
	}
} 


void navigate(){
	int start=0,end;
	char key;
	struct winsize size;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
	row_len=size.ws_row-4;
	cursor_pos=(dir_len > row_len) ? row_len : dir_len;
	
	end=cursor_pos;

	display(start, cursor_pos);

	while(1){
		row_len=size.ws_row-4;
		if(mode==1)		// normal mode
		{
			key=getch();
			if(key==27){
				key=getch();
				key=getch();
				if(key=='A'){
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
						display(start,end);
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
					
				}	
		
			}	
		}
		else if( key=='\n' ){								// ON PRESSIN ENTER KEY
			if(File_OR_Dir(DirList[cursor_pos])==1){		//FILE opening

			}
			else{											// directory change
				char NewDirPath[200];
				string newPath=pwd+DirList[cursor_pos]+'/';
				strcpy(NewDirPath, newPath.c_str());
				if(chdir(NewDirPath)<0){
					cout<<"error"<<endl;
					exit(0);
				}
				
			}
		}
	}
			
}

int main()
{
	char path[500]="/home/rishabh/";
	string tmp_path(path);
	pwd=tmp_path;
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
	char buffer[256];
	cout<<getcwd(buffer, 256)<<endl;
	navigate();
	return 0;
}