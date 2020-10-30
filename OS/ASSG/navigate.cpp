
							// LATEST BACKUP
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
//int start=0,end;
struct winsize size;
/*
dir_len = # of dir/files in DirList
*/

void Clear(stack <string> &S){
	while(!S.empty())
		S.pop();
}

int File_OR_Dir(string path){			// 2-file , 1-dir
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
    cout<<file<<endl;
}

void display(int start, int end){
	cout<<"\033c";//clear screen
	while(start < end){
		printDetails(allDirList[idx-1][start]);
		//printDetails(DirList[start]);
		//cout<<DirList[start]<<endl;
		start++;
	}
} 


void openDir(char path[], string newpath){
	//cout<<"int open dir func\n";
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
	//cout<<"\033c";//clear screen
	//for(auto i : allDirList[idx-1])
	//	cout<<i<<endl;
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
	//dir_len=allDirList[idx-1].size();		//   uncomment -----------
	dir_len=allDirList[curr_idx].size();

	pwd=newPath;
	start=0;
	row_len=size.ws_row-4;
	cursor_pos=(dir_len > row_len) ? row_len : dir_len;
	end=cursor_pos;
	//end=(dir_len > row_len) ? row_len-1 : dir_len;
	cursor_pos=0;
	display(start,end);
	cout << "\033[H";
}



void navigate(){
	int flag=0;
	int start=0,end;
	char key;
	//struct winsize size;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
	row_len=size.ws_row-4;
	cursor_pos=(dir_len > row_len) ? row_len : dir_len;
	
	end=cursor_pos;
	cursor_pos=0;
	display(start, end);
	cout << "\033[H";
	while(1){
		ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
		row_len=size.ws_row-4;
		if(mode==1)		// normal mode
		{
			key=getch();
			if(key==27){
				key=getch();
				key=getch();
				if(key=='A'){
					//if(cursor_pos==start  && start==0)
					//	continue;
					if(cursor_pos > start){
						//flag=0;
						cursor_pos--;
						printf("\033[1A");
					}
					else if(cursor_pos == start && start > 0){
						flag=0;
						start--;
						cursor_pos--;
						end--;
						display(start,end);
						int tmp=row_len;
						while(tmp--){
							cout<<"\033[1A";	
						}
						
					}
					
				}
				else if(key=='B'){
					
					if(cursor_pos < end){
						//if(start>0)
							flag=0;
						cursor_pos++;
						printf("\033[1B");
					}
					else if(cursor_pos == end && end < dir_len){
						flag=1;
						end++;
						cursor_pos++;
						start++;
						display(start,end);
						cout<<"\033[1A";
					}
					
				}	
				else if(key=='C'){		// right
					flag=0;
					if(!frwd_track.empty()){
						back_track.push(pwd);
						string newPath=frwd_track.top();
						frwd_track.pop();
						pwd=newPath;
						changeDirectory(newPath, start, end);
					
					}
				}
				else if(key=='D'){		// left
					flag=0;
					if(!back_track.empty()){
						frwd_track.push(pwd);
						string newPath=back_track.top();
						back_track.pop();
						pwd=newPath;
						changeDirectory(newPath, start, end);
					
					}
				}
				
			}
			else if (key==127 || key==8){		// backspace
				//cout<<"in backspace....\n";
				flag=0;
				if(pwd!="/home/rishabh/"){
					Clear(frwd_track);
					int i=pwd.length()-2;
					while(i>=0 && pwd[i]!='/')
						i--;

					string parent=pwd.substr(0,i+1);
					cout<<pwd<<"   "<<parent<<endl;
					//string newPath=back_track.top();
					//back_track.pop();
					changeDirectory(parent, start, end);
					pwd=parent;
				}
			}
			else if (/*key==104 || key==72*/ key=='h'){		// home
				cout<<"in home....\n";
				flag=0;
				if(pwd!="/home/rishabh/"){
					Clear(frwd_track);
					string newPath=pwd;
					back_track.push(pwd);
					changeDirectory("/home/rishabh/", start, end);
					pwd="/home/rishabh/";
				}
			}
			else if( key==10 ){								//  ENTER KEY
				int toEnter=(flag==1) ? cursor_pos-1:cursor_pos;
				cout<<"in enter block ---- "<<allDirList[idx-1][toEnter]<<" "<<flag<<endl;
				cout<<pwd+allDirList[idx-1][toEnter]<<endl;
				
				if(File_OR_Dir(pwd+allDirList[idx-1][toEnter])==2){		//FILE opening
					cout<<"in enter FILE block\n";
				}
				else{											// directory change
					cout<<"in enter DIR block\n";
					char NewDirPath[200];
					string newPath=pwd+allDirList[idx-1][toEnter]+'/';
					strcpy(NewDirPath, newPath.c_str());
					if(chdir(NewDirPath)<0){
						cout<<"error"<<endl;
						exit(0);
					}
					cout<<"entering.....  "<<NewDirPath<<endl;
					back_track.push(pwd);
					//openDir(NewDirPath,newPath);  //   uncomment it ----------
					changeDirectory(newPath, start, end);
					//back_track.push(newPath);

					cout << "\033[H";
					/*
					dir_len=allDirList[idx-1].size();
					pwd=newPath;
					start=0;
					row_len=size.ws_row-4;
					cursor_pos=(dir_len > row_len) ? row_len : dir_len;
					end=cursor_pos;
					cursor_pos=0;*/
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

/**************************************************
1.) correct navigation of /home
2.) open files using vi
3.) escape key
4.) stat printing
5.) copying mp4 file
6.) maintaining files permissions on copying & moving
7.) search implmentation
8.) open correct dir in /home/subDir (one above wali open hori)
9.) update vector if a new file is copied or deleted in previously visited folder
10.) remove vector entry if a folder is deleted - just delete its entry from map not from vector
11.) mp3 file copied but is locked

delete_dir function complete krr
-----------------------
		DONE
for deleted file -> its vector entry is deleted
for deleted DIR -> its MAP ENTRY is deleted

**************************************************/