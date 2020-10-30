#include <iostream>
#include <sys/types.h>
#include <dirent.h>
#include <bits/stdc++.h>
#include <termios.h>
#include <unistd.h>

using namespace std;
void scrolling();
vector <string> lists;
stack <string> dirfwd, dirbcw;
void listFiles(string str1)
{
    //string str1=dirfwd.top();
    const char *path = str1.c_str();
    //string *path=dirs.top();
    struct dirent *dp;
    DIR *dir = opendir(path);
    lists.clear();
    vector <string> dirr, files;
    if (!dir) 
        return; 

    while ((dp = readdir(dir)) != NULL)
    {
        if(dp->d_name[0]!='.')
        {
            string str1=dp->d_name;
            if(str1.find('.')==str1.npos)
            {
                dirr.push_back(str1);      
            }
            else
            {
                files.push_back(str1);
            }

        }
    }
    sort(dirr.begin(),dirr.end());
    sort(files.begin(),files.end());
    for(int i=0;i<dirr.size();i++)
    {
        //cout<<dirr[i]<<endl;
        string str1=dirr[i]+'/';
        lists.push_back(str1);
    }
     for(int i=0;i<files.size();i++)
    {
        //cout<<files[i]<<endl;
        lists.push_back(files[i]);
    }

    closedir(dir);
    scrolling();
}

#define cursorright(x) cout<<"\033[1D"
#define cursorleft(x) cout<<"\033[1C"
#define cursorup(x) cout<<"\033[1A"
#define cursordown(x) cout<<"\033[1B"


#define KEY_ESCAPE  0x001b
#define KEY_ENTER   0x000a
#define KEY_UP      0x0105
#define KEY_DOWN    0x0106
#define KEY_LEFT    0x0107
#define KEY_RIGHT   0x0108


static struct termios term, oterm;

static int getch(void);
static int kbhit(void);
static int kbesc(void);
static int kbget(void);

static int getch(void)
{
    int c = 0;

    tcgetattr(0, &oterm);
    memcpy(&term, &oterm, sizeof(term));
    term.c_lflag &= ~(ICANON | ECHO);
    term.c_cc[VMIN] = 1;
    term.c_cc[VTIME] = 0;
    tcsetattr(0, TCSANOW, &term);
    c = getchar();
    tcsetattr(0, TCSANOW, &oterm);
    return c;
}

static int kbhit(void)
{
    int c = 0;

    tcgetattr(0, &oterm);
    memcpy(&term, &oterm, sizeof(term));
    term.c_lflag &= ~(ICANON | ECHO);
    term.c_cc[VMIN] = 0;
    term.c_cc[VTIME] = 1;
    tcsetattr(0, TCSANOW, &term);
    c = getchar();
    tcsetattr(0, TCSANOW, &oterm);
    if (c != -1) ungetc(c, stdin);
    return ((c != -1) ? 1 : 0);
}

static int kbesc(void)
{
    int c;

    if (!kbhit()) return KEY_ESCAPE;
    c = getch();
    if (c == '[') 
    {
        switch (getch()) 
        {
            case 'A':
                c = KEY_UP;
                break;
            case 'B':
                c = KEY_DOWN;
                break;
            case 'C':
                c = KEY_RIGHT;
                break;
            case 'D':
                c = KEY_LEFT;
                break;
            default:
                c = 0;
                break;
        }
    } 
    else 
    {
        c = 0;
    }
    if (c == 0) while (kbhit()) getch();
    return c;
}

static int kbget(void)
{
    int c;

    c = getch();
    return (c == KEY_ESCAPE) ? kbesc() : c;
}

void printlist(int start1, int end1)
{
    cout << "\e[8;50;60t";
    cout<<"\033c";
    int i;
    for(i=start1;i<=end1;i++)
    {
        cout<<lists[i]<<endl;
    } 
}

void scrolling()
{
    int start1=0,i;
    int listend=lists.size()-1;
    int end1=19<=listend?19:listend;
    int pos=0;
    printlist(start1,end1);
    cout << "\033[H";
    int c;
     while (1) {
        int flag=0;
        c = kbget();
        if ( c == KEY_ESCAPE) {
            break;
        } 
        else if (c == KEY_ENTER)
        {
            string str1=dirfwd.top()+lists[pos];
            cout<<str1;
            dirfwd.push(str1);
            listFiles(dirfwd.top());    
        }
        else if (c == KEY_LEFT)
        {
            string str1=dirfwd.top(); 
            if(str1!="/home/")
            {
                dirbcw.push(str1);
                dirfwd.pop();
                listFiles(dirfwd.top());
            }
        }
        else if (c == KEY_RIGHT)
        {
            if(dirbcw.empty()!=1)
            {
            string str1=dirbcw.top(); 
            cout<<str1;
            dirbcw.pop();
            dirfwd.push(str1);
            listFiles(dirfwd.top());   
            }
        }

        else if (c == KEY_UP) 
        {
            if(pos>start1)
            {
                pos--;
                cout<<"\033[1A";
            }
            else if(pos==start1 && start1>0)
            {
                pos--;
                start1--;
                end1--;
                printlist(start1, end1);
                cout<<"\033[20A";
            }
            
        } 
        else if (c == KEY_DOWN) {
            if(pos<end1)
            {
                flag=1;
                pos++;
                cout<<"\033[1B";
            }
            else if(pos==end1 && end1<listend)
            {
                pos++;
                start1++;
                end1++;
                printlist(start1, end1);
                cout<<"\033[1A";
            }   
        }
    }
    cout<<endl;
}
int main()
{
    dirfwd.push("/home/");
    dirfwd.push("/home/rishabh/");
    listFiles(dirfwd.top());
    return 0;
}