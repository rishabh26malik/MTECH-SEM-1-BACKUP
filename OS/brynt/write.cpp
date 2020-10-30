#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include<bits/stdc++.h>
#include <unistd.h>
using namespace std;

int main()
{
	int fd1,fd2;
	fd1 = open("foo.txt", O_RDONLY, 0);
	fd2 = open("boo.txt", O_WRONLY| O_CREAT, 0);
	char c;
	while(read(fd1, &c, 1) != 0){
		//cout<<c;
		write(fd2, &c, 1);
	}
	exit(0);

}
