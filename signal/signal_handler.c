#include <stdio.h>
#include <signal.h>
#include <unistd.h>


void handler(int signum)
{
  printf("received signal: %d\n", signum);
}

int main()
{
  signal(SIGINT, handler);
  kill(getpid(), SIGINT);
  return 0;
}
