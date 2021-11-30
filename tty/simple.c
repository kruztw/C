#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main()
{
   int fd;
   char * file = "/dev/tty";
   fd = open(file, O_RDONLY);
   if(isatty(fd))
      printf("ttyname = %s \n", ttyname(fd));

   close(fd);
}
