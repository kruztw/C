#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<fcntl.h>
#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<string.h>
#include<signal.h>

int main( int argc,  char *argv[])
{
    mkfifo( "tp",  0644);
    int fd_in  = open("Makefile", O_RDONLY);
    int fd_out = open("tp", O_WRONLY);
    char buf[ 1024];
    int n;

    while ((n = read(fd_in, buf,  1024)) >  0)
        write(fd_out, buf, n);

    close(fd_in);
    close(fd_out);

    return  0;
}
