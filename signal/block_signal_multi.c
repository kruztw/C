#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <pthread.h>


void handler(int signum)
{
  printf("trigger tid: %ld\n", pthread_self());
  printf("received signal: %d\n", signum);            // should be unblock_handler thread
}


void *block_handler(void *arg)
{
  printf("block_handler tid: %ld\n", pthread_self());
  while (1) continue;
}

void *unblock_handler(void *arg)
{
  printf("unblock_handler tid: %ld\n", pthread_self());

  // unblock
  sigset_t mask;
  sigemptyset(&mask);
  sigaddset(&mask, SIGINT);
  sigprocmask(SIG_UNBLOCK, &mask, NULL);
  
  while (1) continue;
}

int main()
{ 
  printf("main thread tid: %ld\n", pthread_self());

  // block 
  sigset_t mask;
  sigemptyset(&mask);
  sigaddset(&mask, SIGINT);
  sigprocmask(SIG_BLOCK, &mask, NULL);

  signal(SIGINT, handler);
 
  pthread_t t1, t2;
  pthread_create(&t1, NULL, block_handler, NULL);
  pthread_create(&t2, NULL, unblock_handler, NULL);
 
  scanf("%*c");              // wait threads create
  kill(getpid(), SIGINT);
  scanf("%*c");              // wait handler print info

  return 0;
}
