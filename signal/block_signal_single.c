#include <stdio.h>
#include <signal.h>
#include <unistd.h>


void handler(int signum)
{
  printf("received signal: %d\n", signum);
}

int main()
{ 
  sigset_t mask;
  sigemptyset(&mask);
  sigaddset(&mask, SIGINT);
  sigprocmask(SIG_BLOCK, &mask, NULL);

  signal(SIGINT, handler);
  kill(getpid(), SIGINT);
  return 0;
}
