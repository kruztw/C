#include <signal.h>      // kill
#include <unistd.h>      // getpid

int main()
{
  kill(getpid(), SIGINT);
  while (1) continue;
  return 0;
}
