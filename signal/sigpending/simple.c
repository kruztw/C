#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

void block_all_signals()
{
    sigset_t signals;
    sigfillset(&signals);
    sigprocmask(SIG_BLOCK, &signals, NULL); 
}



int main()
{
    int counter = 1;

    block_all_signals();

    // 每隔1s獲取一次記憶體的未決訊號集
    while(1) {                                                                                                                      
        sigset_t pend;
        sigpending(&pend); // 獲取[當前程序]的未決訊號集，存放在pendset集合中
  
        // 判斷訊號i是否在pendset中，
        for(int i = 1; i <= 31; i++)
            printf("%d: %d\n", i, sigismember(&pend, i));

        printf("\n");
        sleep(1);
        
        if (counter == SIGINT || counter == SIGKILL || counter == SIGSTOP)
            counter++;

        kill(getpid(), counter);

        if (++counter > 32)
            break;
    }

  return 0;                                                                                                                      
}  
