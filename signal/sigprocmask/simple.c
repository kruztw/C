#include <stdio.h>
#include <signal.h>
#include <unistd.h>

int main()
{                                                                                                                      
  sigset_t myset;

  sigemptyset(&myset);
  sigaddset(&myset, SIGINT);  /*   ctrl+C   */
  sigaddset(&myset, SIGQUIT); /*   ctrl+\   */
  sigaddset(&myset, SIGKILL);
                                                                                                   
  //將 myset 集合中的訊號設為[阻塞]
  sigprocmask(SIG_BLOCK, &myset, NULL);
  
  kill(getpid(), SIGINT);
  kill(getpid(), SIGQUIT);

  printf("safe\n");
  return 0;
}   
