

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

string getPath(string path){
	//cout<<"in get path...\n";
	string dest="";
	if(path[0]=='~'){
		dest="/home/rishabh"+path.substr(1,path.length());
	}
	else if(path[0]=='/'){
		dest="/home/rishabh"+path;	
	}
	else if(path[0]=='.'){
		dest=pwd+path.substr(1,path.length());
	}
	else{
		dest=pwd+path.substr(1,path.length());
	}
	return dest;
}

void copyFile(string src, string dest, string filename){
	dest+=filename;
	char source[100],destn[100];
	strcpy(destn, dest.c_str());
	strcpy(source, src.c_str());
	int fd1 = open(source, O_RDONLY, 0);
	int fd2 = open(destn, O_WRONLY| O_CREAT, 0);
	char c;
	cout<<endl;
	while(read(fd1, &c, 1) != 0){
		write(fd2, &c, 1);
	}
	close(fd1);
	close(fd2);
	chmod(destn,S_IRUSR|S_IWUSR);
	
}

void copyCmd(vector <string> cmds){
	//cout<<"in copy cmd...\n";
	int i,n=cmds.size();
	i=1;
	string dest=getPath(cmds[n-1]);
	while(i<n-1){
		string path=pwd+cmds[i];
		cout<<path<<endl;
		if(File_OR_Dir(path)==2){	//file copy
			string src=pwd+cmds[i];
			cout<<src<<" "<<dest<<endl;
			copyFile(src,dest,cmds[i]);
		}
		else{						// dir copy -    DO WE HAVE TO COPY ALL CONTENTS OF DIR RECURSIVELY

		}
		i++;
	}
}

void move(vector <string> cmds){
	int i,n=cmds.size();
	i=1;
	string dest=getPath(cmds[n-1]);
	while(i<n-1){
		string path=pwd+cmds[i];
		char Path[100];
		strcpy(Path, path.c_str());
		copyFile(path, dest, cmds[i]);
		int fd=remove(Path);
		if(fd==-1)
			cout<<"error in deleting FILE "<<cmds[i]<<endl;
		
		i++;
	}
}

void createFile(vector <string> cmds){
	int i,n=cmds.size();
	i=1;
	string dest=getPath(cmds[n-1]);
	while(i<n-1){
		string path=pwd+cmds[i];
		cout<<path<<endl;
		char Path[100];
		strcpy(Path, path.c_str());
		int fd=open(Path,O_RDONLY | O_CREAT| O_WRONLY);
		if(fd==-1)
			cout<<"error in creating file "<<cmds[i]<<endl;
		i++;
		close(fd);
		chmod(Path,S_IRUSR|S_IWUSR);
	}
}

void createDir(vector <string> cmds){
	int i,n=cmds.size();
	i=1;
	string dest=getPath(cmds[n-1]);
	while(i<n-1){
		string path=pwd+cmds[i];
		char Path[100];
		strcpy(Path, path.c_str());
		int fd=mkdir(Path,S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP |S_IROTH|S_IXUSR);
		if(fd==-1)
			cout<<"error in creating directory "<<cmds[i]<<endl;
		i++;
	}
}

void deleteFile(vector <string> cmds){
	int i,n=cmds.size();
	i=1;
	string dest=getPath(cmds[n-1]);
	while(i<n){
		string path=pwd+cmds[i];
		char Path[100];
		strcpy(Path, path.c_str());
		int fd=remove(Path);
		if(fd==-1)
			cout<<"error in deleting file "<<cmds[i]<<endl;
		i++;
	}
}

void deleteDir(vector <string> cmds){
	int i,n=cmds.size();
	i=1;
	string dest=getPath(cmds[n-1]);
	while(i<n){
		string path=pwd+cmds[i];
		char Path[100];
		strcpy(Path, path.c_str());
		int fd=rmdir(Path);
		if(fd==-1)
			cout<<"error in deleting directory "<<cmds[i]<<endl;
		i++;
	}
}

void goto_(vector <string> cmds, int &start, int &end){
	string dest=cmds[1];
	char Path[100];
	strcpy(Path, dest.c_str());

	//char NewDirPath[200];
	//strcpy(NewDirPath, newPath.c_str());
	if(chdir(Path)<0){
		cout<<"error"<<endl;
		exit(0);
	}
	openDir(Path,cmds[1]);
	//back_track.push(newPath);
	Clear(frwd_track);			/// <<<<<<<------- CHECK THIS
	back_track.push(pwd);
	dir_len=allDirList[idx-1].size();
	pwd=cmds[1];
	start=0;
	row_len=size.ws_row-4;
	cursor_pos=(dir_len > row_len) ? row_len : dir_len;
	end=cursor_pos;
}

void rename(vector <string> cmds){
	char src[100],dest[100];
	cmds[1]=pwd+cmds[1];
	cmds[2]=pwd+cmds[2];
	strcpy(src, cmds[1].c_str());
	strcpy(dest, cmds[2].c_str());
	int fd=rename(src,dest);
	if(fd==-1)
			cout<<"error in renaming file "<<cmds[1]<<endl;
}

void execute_cmd(string command, int &start, int &end){
	//cout<<"in execute cmd...\n";
	vector <string> cmds;
	tokenize(command,cmds); 
	if(cmds[0]=="copy"){
		copyCmd(cmds);
	}
	else if(cmds[0]=="move"){
		move(cmds);
	}
	else if(cmds[0]=="create_file"){
		createFile(cmds);
	}
	else if(cmds[0]=="create_dir"){
		createDir(cmds);
	}
	else if(cmds[0]=="delete_file"){
		deleteFile(cmds);
	}
	else if(cmds[0]=="delete_dir"){
		deleteDir(cmds);
	}
	else if(cmds[0]=="goto"){
		goto_(cmds, start, end);
	}
	else if(cmds[0]=="rename"){
		rename(cmds);
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
				//cout<<"in backspace....\n";
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
			else if(key==':'){
				int goDown=size.ws_row-2, cursor=cursor_pos;
				while(cursor<goDown){
					printf("\033[1B");
					cursor++;	
				}
				/*printf("\033[1B");
				printf("\033[1B");
				printf("\033[1B");
				printf("\033[1B");
				printf("\033[1B");
				printf("\033[1B");
				printf("\033[1B");
				printf("\033[1B");*/
				cout<<": ";
				mode=2;					// mode = 2 -->> command mode
				string command="";
				char ch;
				int store[3];
				store[0]=start;
				store[1]=end;
				store[2]=cursor_pos;
				while(ch=getchar()){
					if(ch!=27 && ch!=10){
						command.push_back(ch);	
					}
					else if(ch==127){
						command.pop_back();	
					}
					else if(ch==10){
						cout<<"in enter else block b4 exe_cmd...\n";
						execute_cmd(command,start,end);
						break;
					}
					
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