#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include<bits/stdc++.h>
#include <unistd.h>
using namespace std;

int main()
{
	int fd1;
	fd1 = open("foo.txt", O_RDONLY, 0);
	char c;
	while(read(fd1, &c, 1) != 0)
		cout<<c;
	exit(0);

}
