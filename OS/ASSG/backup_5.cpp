

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

stack <string> back_track, frwd_track;
int curr_idx=0;
unordered_map <string,int> path2list;
vector <vector<string>> allDirList;
vector <string> DirList;
int mode=1, cursor_pos;			// 1-normal mode
int row_len, dir_len,idx=0;
string pwd;
struct winsize size;
/*
dir_len = # of dir/files in DirList
*/

void Clear(stack <string> &S){
	while(!S.empty())
		S.pop();
}

int File_OR_Dir(string path){			// 1-file , 2-dir
	struct stat sb;
	char curr_path[200];
	//string file_path=pwd+file;
	strcpy(curr_path, path.c_str());
	if (stat(curr_path, &sb) == -1) {
        perror("stat");
        exit(EXIT_FAILURE);
    }
    switch (sb.st_mode & S_IFMT) {
    case S_IFDIR:  return 1;
    		        break;
    case S_IFREG:  return 2;
                    break;
    }
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
    /*printf((sb.st_mode & S_IRUSR)? "r":"-");
  printf((sb.st_mode & S_IWUSR)? "w":"-");
  printf((sb.st_mode & S_IXUSR)? "x":"-");
  printf(" ");
  printf((sb.st_mode & S_IRGRP)? "r":"-");
  printf((sb.st_mode & S_IWGRP)? "w":"-");
  printf((sb.st_mode & S_IXGRP)? "x":"-");
  printf(" ");
  printf((sb.st_mode & S_IROTH)? "r":"-");
  printf((sb.st_mode & S_IWOTH)? "w":"-");
  printf((sb.st_mode & S_IXOTH)? "x":"-");*/
    cout<<file<<endl;
//	cout<<"        "<<file<<"          "<<sb.st_size<<"   "<<ctime(&sb.st_mtime);
	//cout << "\033[F";
	//cout<<"   "<<file<<endl;
	//cout<<"   "<<sb.st_size<<"   "<<file<<endl;
    //string modTime (ctime(&sb.st_mtime)); 
	//printf("    %lld B    %s    %s \n",(long long) sb.st_size, ctime(&sb.st_mtime), file);
}

void openDir(char path[], string newpath){
	cout<<"int open dir func\n";
	DIR *directory;
	dirent *fileInDir;
	directory=opendir(path);
	vector <string> tmp;
	while((fileInDir=readdir(directory))!=NULL){
		string fileName(fileInDir->d_name);
		if(fileName[0]!='.')
			tmp.push_back(fileName);
	}
	allDirList.push_back(tmp);
	tmp.clear();
	path2list[newpath]=idx;
	curr_idx=idx;
	idx++;
	cout<<"\033c";//clear screen
	for(auto i : allDirList[idx-1])
		cout<<i<<endl;
}

void changeDirectory(string newPath, int &start, int &end){
	char NewDirPath[200];
	//string newPath=pwd+allDirList[idx-1][cursor_pos]+'/';
	strcpy(NewDirPath, newPath.c_str());
	if(chdir(NewDirPath)<0){
		cout<<"error"<<endl;
		exit(0);
	}
	openDir(NewDirPath,newPath);
	//back_track.push(newPath);
	dir_len=allDirList[idx-1].size();
	pwd=newPath;
	start=0;
	row_len=size.ws_row-4;
	cursor_pos=(dir_len > row_len) ? row_len : dir_len;
	end=cursor_pos;
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
	//struct winsize size;
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
				else if(key=='C'){		// right
					if(!frwd_track.empty()){
						back_track.push(pwd);
						string newPath=frwd_track.top();
						frwd_track.pop();
						pwd=newPath;
						changeDirectory(newPath, start, end);
					/*	char NewDirPath[200];
						//string newPath=pwd+allDirList[idx-1][cursor_pos]+'/';
						strcpy(NewDirPath, newPath.c_str());
						if(chdir(NewDirPath)<0){
							cout<<"error"<<endl;
							exit(0);
						}
						openDir(NewDirPath,newPath);
						//back_track.push(newPath);
						dir_len=allDirList[idx-1].size();
						pwd=newPath;
						start=0;
						row_len=size.ws_row-4;
						cursor_pos=(dir_len > row_len) ? row_len : dir_len;
						end=cursor_pos;*/
					}
				}
				else if(key=='D'){		// left
					/*frwd_track.push(path2list.find(curr_idx)->first);*/
					//curr_idx=path2list[];
					//cout<<"in LEFT block ---- "<<endl;
					if(!back_track.empty()){
						frwd_track.push(pwd);
						string newPath=back_track.top();
						back_track.pop();
						pwd=newPath;
						changeDirectory(newPath, start, end);
					/*	char NewDirPath[200];
						//string newPath=pwd+allDirList[idx-1][cursor_pos]+'/';
						strcpy(NewDirPath, newPath.c_str());
						if(chdir(NewDirPath)<0){
							cout<<"error"<<endl;
							exit(0);
						}
						openDir(NewDirPath,newPath);
						//back_track.push(newPath);
						dir_len=allDirList[idx-1].size();
						pwd=newPath;
						start=0;
						row_len=size.ws_row-4;
						cursor_pos=(dir_len > row_len) ? row_len : dir_len;
						end=cursor_pos;*/
					}
				}
				
			}
			else if (key==127 || key==8){		// backspace
				cout<<"in backspace....\n";
				if(pwd!="/home/rishabh/"){
					Clear(frwd_track);
					string newPath=back_track.top();
					back_track.pop();
					changeDirectory(newPath, start, end);
					pwd=newPath;
				}
			}
			else if (/*key==104 || key==72*/ key=='h'){		// home
				cout<<"in home....\n";
				if(pwd!="/home/rishabh/"){
					Clear(frwd_track);
					string newPath=pwd;
					back_track.push(pwd);
					changeDirectory("/home/rishabh/", start, end);
					pwd="/home/rishabh/";
				}
			}
			else if( key==10 ){								//  ENTER KEY
				cout<<"in enter block ---- "<<allDirList[idx-1][cursor_pos]<<endl;
				if(File_OR_Dir(pwd+'/'+allDirList[idx-1][cursor_pos])==2){		//FILE opening
					cout<<"in enter FILE block\n";
				}
				else{											// directory change
					cout<<"in enter DIR block\n";
					char NewDirPath[200];
					string newPath=pwd+allDirList[idx-1][cursor_pos]+'/';
					strcpy(NewDirPath, newPath.c_str());
					if(chdir(NewDirPath)<0){
						cout<<"error"<<endl;
						exit(0);
					}
					cout<<"entering.....  "<<NewDirPath<<endl;
					back_track.push(pwd);
					openDir(NewDirPath,newPath);
					//back_track.push(newPath);
					dir_len=allDirList[idx-1].size();
					pwd=newPath;
					start=0;
					row_len=size.ws_row-4;
					cursor_pos=(dir_len > row_len) ? row_len : dir_len;
					end=cursor_pos;
					//cout<<"pwd/..... "<<pwd<<endl;
				}
			}	
		}
		
	}
			
}

int main()
{
	char path[500]="/home/rishabh/F/";
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
	allDirList.push_back(DirList);
	if(path2list.find(tmp_path)==path2list.end()){
		path2list[tmp_path]=idx;
		idx++;
	}
	curr_idx=idx;
	dir_len=DirList.size();
	char buffer[256];
	cout<<getcwd(buffer, 256)<<endl;
	navigate();
	return 0;
}