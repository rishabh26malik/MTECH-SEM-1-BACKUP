
//#include<bits/stdc++.h>
#include "csapp.h"

ssize_t rio_readn(int fd, void *usrbuf, size_t n)
{
    size_t nleft = n;
    ssize_t nread;
    char *bufp = usrbuf;

    while (nleft > 0) {
        if ((nread = read(fd, bufp, nleft)) < 0) {
            if (errno == EINTR) /* Interrupted by sig handler return */
            nread = 0;
            /* and call read() again */
            else
            return -1;
            /* errno set by read() */
        }
        else if (nread == 0)
            break;
        /* EOF */
        nleft -= nread;
        bufp += nread;
    }
    return (n - nleft);
    /* Return >= 0 */
}

ssize_t rio_writen(int fd, void *usrbuf, size_t n)
{
    size_t nleft = n;
    ssize_t nwritten;
    char *bufp = usrbuf;

    while (nleft > 0) {
        if ((nwritten = write(fd, bufp, nleft)) <= 0) {
            if (errno == EINTR) /* Interrupted by sig handler return */
            nwritten = 0;
            /* and call write() again */
            else
            return -1;
            /* errno set by write() */
        }
        nleft -= nwritten;
        bufp += nwritten;
    }
    return n;
}

int main()
{
	int fd1,fd2;
	fd1 = open("foo.txt", O_RDONLY, 0);
	fd2 = open("boo.txt", O_WRONLY, 0);
	char c;
	while(rio_readn(fd1, &c, 1) != 0){
		//cout<<c;
		rio_writen(fd2, &c, 1);
	}
	exit(0);

}
