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
