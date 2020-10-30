#include "header.h"

extern string HOME, HOME_without_slash;
extern struct stat orig_file;
extern int refresh;		
extern stack <string> back_track, frwd_track;
extern int curr_idx;
extern unordered_map <string,int> path2list;
extern vector <vector<string>> allDirList;
extern vector <string> DirList;
extern int mode, cursor_pos;			
extern int row_len, dir_len,idx;
extern string pwd;
extern struct winsize size;


/*void move(vector <string> cmds){
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
}*/


void copyFile(string src, string dest, string filename){
	dest+=filename;
	char source[100],destn[100];
	strcpy(destn, dest.c_str());
	strcpy(source, src.c_str());
	int fd1 = open(source, O_RDONLY, 0);
	int fd2 = open(destn, O_WRONLY| O_CREAT, 0);
	char c;
	while(read(fd1, &c, 1) != 0){
		write(fd2, &c, 1);
	}
	close(fd1);
	close(fd2);
	chmod(destn,S_IRUSR|S_IWUSR);
	if (stat(source, &orig_file) == -1) {
        perror("stat");
        exit(EXIT_FAILURE);
    }
    updatePermissions(source,destn);
}

void copyDirectory(string src, char SRC[], string dest, char DEST[]){
	int fd=mkdir(DEST, S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP |S_IROTH|S_IXUSR);
	if(fd == -1)
	 {
	 	cout<<"error in creating dir.. "<<DEST<<endl;
	 	exit(0);
	 }
	DIR *directory;
	dirent *fileInDir;
	directory=opendir(SRC);
	if(directory){
		while((fileInDir=readdir(directory))!=NULL){
			string fileName(fileInDir->d_name);
			if(fileName[0]!='.'){	
				string copyTO=dest+fileName;
				string copyFROM=src+fileName;
				char newSrc[200], newDest[200];
				strcpy(newSrc, copyFROM.c_str() );
				strcpy(newDest, copyTO.c_str() );
				if(File_OR_Dir(copyFROM)==2){	//file
					copyFile(copyFROM, copyTO, fileName);
				}
				else{
					copyTO+='/';
					copyFROM+='/';
					strcpy(newSrc, copyFROM.c_str() );
					strcpy(newDest, copyTO.c_str() );
					copyDirectory(copyFROM, newSrc, copyTO, newDest);
				}
			}
		}
		closedir(directory);
	}
}

void copyCmd(vector <string> cmds){
	int i,n=cmds.size();
	i=1;
	string path="";
	string dest=getPath(cmds[n-1]);
	while(i<n-1){
		path=pwd+cmds[i];
		if(File_OR_Dir(path)==2){	//file copy
			string src=pwd+cmds[i];
			copyFile(src,dest,cmds[i]);
		}
		else{						// dir copy -    DO WE HAVE TO COPY ALL CONTENTS OF DIR RECURSIVELY
			char SRC[200], DEST[200];
			dest+=cmds[i];
			strcpy(SRC, path.c_str());
			strcpy(DEST, dest.c_str());
			copyDirectory(path, SRC, dest, DEST);
		}
		i++;
	}
}


void removeFileEntry(string path){
	int index, flag=0;
	string filename="";
	vector<string>::iterator it;
	int i=path.size()-1;
	while(path[i]!='/'){
		filename=path[i]+filename;
		i--;
	}
	string parent=path.substr(0,i+1);
	index=path2list[parent];

	for(it=allDirList[index].begin(); it!=allDirList[index].end(); it++){
		if(*it == filename){
			flag=1;
			cout<<*it<<"  found file to be deleted....\n";
			break;
		}
	}
	if(flag==1)
		allDirList[index].erase(it);

	if(pwd==parent){
		refresh=1;
	}
}

void removeDirEntry(string path){
	int index, flag=0;
	string DIRname="";
	vector<string>::iterator it;
	int i=path.size()-1;
	while(path[i]!='/'){
		DIRname=path[i]+DIRname;
		i--;
	}
	string parent=path.substr(0,i+1);
	index=path2list[parent];

	for(it=allDirList[index].begin(); it!=allDirList[index].end(); it++){
		cout<<*it<<endl;
		if(*it == DIRname){
			flag=1;
			cout<<*it<<"  found DIR to be deleted....\n";
			break;
		}
	}
	if(flag==1)
		allDirList[index].erase(it);
	if(pwd==parent){
		cout<<pwd<<"   "<<parent<<endl;
		refresh=1;
	}
}

void delete_one_dir(char *path, string Path){
	cout<<"delete_one_dir..."<<Path<<endl;
	DIR *directory;
	dirent *fileInDir;
	directory=opendir(path);
	if(directory){
		while((fileInDir=readdir(directory))!=NULL){
			string fileName(fileInDir->d_name);
			string subPath=Path+fileName;
			string DirName=subPath+'/';
			char subpath[100];
			strcpy(subpath, subPath.c_str());
			if(fileName[0]!='.'){
				if(File_OR_Dir(subPath)==2){	//file
					int fd=remove(subpath);
					if(fd==-1){
						cout<<"error in deleting file "<<endl;
						exit(0);
					}
					removeFileEntry(subPath);
				}
				else{
					strcpy(subpath, DirName.c_str());
					delete_one_dir(subpath, DirName);
				}
			}
		}
		closedir(directory);
		int fd=rmdir(path);
		if(fd==-1){
			cout<<"error in deleting dir "<<endl;
			exit(0);
		}
	}
}

void deleteFile(vector <string> cmds){
	int i,n=cmds.size();
	string path=getPath(cmds[n-1]);
	i=1;
	while(i<n){
		//string path=dest+cmds[i];				// CORRECT IT-------NO NEED NOW-----------full path can also be given
		cout<<"delete file path - "<<path<<endl;
		char Path[100];
		strcpy(Path, path.c_str());
		int fd=remove(Path);
		if(fd==-1){
			cout<<"error in deleting file "<<cmds[i]<<endl;
			exit(0);
		}
		removeFileEntry(path);			// removes file's entru from its folder's vector
		i++;
	}
}


void deleteDir(vector <string> cmds, int &start, int &end ){
	string path,parent="";
	int i,n=cmds.size();
	i=1;
	while(i<n){
		path=getPath(cmds[i]);
		cout<<"delete Dir SOURCE path - "<<path<<endl;
		char Path[100];
		strcpy(Path, path.c_str());
		delete_one_dir(Path,path);
		removeDirEntry(path);
		i++;
	}
	i=path.length()-2;
	while(path[i]!='/'){
		i--;
	}
	parent=path.substr(0,i+1);
	if(pwd==parent){
		refresh=1;
	}
}




void createFile(vector <string> cmds){
	int i,n=cmds.size();
	i=1;
	string dest=getPath(cmds[n-1]);
	while(i<n-1){
		string path=dest+cmds[i];
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


void createDir(vector <string> cmds, int &start, int &end){
	int i,n=cmds.size(), idx;
	i=1;
	string path, dest=getPath(cmds[n-1]);
	idx=path2list[dest];
	i=dest.size()-1;
	while(dest[i]!='/'){
		i--;
	}
	string parent=dest.substr(0,i+1);
	int index=path2list[parent];
	i=1;
	for(auto x : allDirList[index])
		cout<<x<<endl;
	while(i<n-1){
		path=dest+cmds[i];
		char Path[100];
		strcpy(Path, path.c_str());
		int fd=mkdir(Path,S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP |S_IROTH|S_IXUSR);
		if(fd==-1)
			cout<<"error in creating directory "<<cmds[i]<<endl;
		if(pwd==parent){
			allDirList[index].push_back(cmds[i]);	
		}
		i++;
	}
	if(pwd==parent){
		dir_len=allDirList[index].size();
		start=0;
		row_len=size.ws_row-4;
		cursor_pos=(dir_len > row_len) ? row_len : dir_len;
		end=cursor_pos;
		cursor_pos=0;
		refresh=1;
	}
}


void move(vector <string> cmds){
	int i,n=cmds.size();
	i=1;
	string dest=getPath(cmds[n-1]);
	while(i<n-1){
		string path=pwd+cmds[i];
		char Path[100];
		if(File_OR_Dir(path)==2){	//file copy
			strcpy(Path, path.c_str());
			copyFile(path, dest, cmds[i]);
			int fd=remove(Path);
			if(fd==-1)
				cout<<"error in deleting FILE "<<cmds[i]<<endl;
			removeFileEntry(path);
		}
		else{
			char SRC[200], DEST[200];
			strcpy(SRC, path.c_str());
			dest+=cmds[i];
			strcpy(DEST, dest.c_str());
			copyDirectory(path, SRC, dest, DEST);
			delete_one_dir(SRC, path);
			removeDirEntry(path);
		}
		i++;
	}
}

void searchRecusively(string Path, string name, bool isfile, bool &found){
	if(found)
		return;
	DIR *directory;
	dirent *fileInDir;
	char path[200];
	strcpy(path, Path.c_str());
	directory=opendir(path);
	if(directory){
		while((fileInDir=readdir(directory))!=NULL){
			string fileName(fileInDir->d_name);
			string subPath=Path+fileName;
			string DirPath=subPath+'/';
			char subpath[100];
			strcpy(subpath, subPath.c_str());
			if(fileName[0]!='.'){
				if(File_OR_Dir(subPath)==2){	//file
					if(isfile && fileName==name){
						found=true;
						cout<<"  ***FILE FOUND************************";
						return;
					}
				}
				else if(File_OR_Dir(DirPath)==1){
					if(!isfile && fileName==name){
						found=true;
						cout<<"  ***DIR FOUND****************";
						return;		
					}
					searchRecusively(DirPath, name , isfile, found);
				}
			}
		}
		closedir(directory);
	}
}

string search(vector <string> cmds){
	bool file, found=false;
	string searchName=cmds[1];
	string path=pwd;
	if(searchName[searchName.length()-1]=='/'){
		searchName.pop_back();
	}
	if(cmds[1][cmds[1].length()-1]!='/'/*File_OR_Dir(path)==2*/){		// file
		file=true;
	}		
	else{
		file=false;
	}
	searchRecusively(pwd,searchName,file, found);
	if(!found)
		cout<<"  ***NOT FOUND************************";
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

void goto_(vector <string> cmds, int &start, int &end){
	string dest=getPath(cmds[1]);
	char Path[100];
	strcpy(Path, dest.c_str());
	if(chdir(Path)<0){
		cout<<"error"<<endl;
		exit(0);
	}
	changeDirectory(dest,start,end);
	Clear(frwd_track);			/// <<<<<<<------- CHECK THIS
	back_track.push(pwd);
	dir_len=allDirList[idx-1].size();
	pwd=dest;
	start=0;
	row_len=size.ws_row-4;
	cursor_pos=(dir_len > row_len) ? row_len : dir_len;
	end=cursor_pos;
	cursor_pos=0;
}

string execute_cmd(string command, int &start, int &end){
	vector <string> cmds;
	tokenize(command,cmds); 
	if(cmds[0]=="copy"){
		copyCmd(cmds);
		return "copy";
	}
	else if(cmds[0]=="move"){
		move(cmds);
		return "move";
	}
	else if(cmds[0]=="create_file"){
		createFile(cmds);
		return "create_file";
	}
	else if(cmds[0]=="create_dir"){
		createDir(cmds, start, end);
		return "create_dir";
	}
	else if(cmds[0]=="delete_file"){
		deleteFile(cmds);
		return "delete_file";
	}
	else if(cmds[0]=="delete_dir"){
		deleteDir(cmds, start, end);
		return "delete_dir";
	}
	else if(cmds[0]=="goto"){
		goto_(cmds, start, end);
		return "goto";
	}
	else if(cmds[0]=="rename"){
		rename(cmds);
		return "rename";
	}
	else if(cmds[0]=="search"){
		search(cmds);
		return "search";
	}
}
