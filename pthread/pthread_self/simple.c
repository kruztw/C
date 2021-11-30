#include <stdio.h>
#include <sys/signal.h>
#include <pthread.h>

int main()
{
  pthread_t tid;
  pthread_kill(pthread_self(), SIGINT);  // pthread_self 會回傳本身
  while(1);

  return 0;
}
