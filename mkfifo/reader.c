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
    mkfifo("tp",  0644);
    int fd_in  = open("tp", O_RDONLY);
    int fd_out = open("copy_file", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    char buf[ 1024];
    int n;

    while ((n = read(fd_in, buf,  1024)) >  0)
        write(fd_out, buf, n);

    close(fd_in);
    close(fd_out);

    unlink("tp");

    return  0;
}
