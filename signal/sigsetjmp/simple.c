#include <stdio.h>
#include <stdlib.h>
#include <setjmp.h>
#include <time.h>
#include <unistd.h>
#include <sys/signal.h>

static sigjmp_buf jmpbuf;
static volatile sig_atomic_t canjump;

static void sig_usr1(int signo)
{    
    time_t starttime;

    if (canjump == 0)           // 避免 sigsetjmp 還沒執行完就進來 (雖然這個範例不會這樣)
        return;

    printf("starting sig_usr1: \n");
    alarm(3);       

    starttime = time(NULL);
    while(time(NULL) < starttime + 5);

    printf("finishing sig_usr1: \n");
    
    siglongjmp(jmpbuf, 1);       // jump back to main
    printf("end of sig_usr1\n"); // not execute
}


static void sig_alrm(int signo)
{
    printf("sig_alrm: \n");
}

int main()
{
    signal(SIGUSR1, sig_usr1);
    signal(SIGALRM, sig_alrm);
    
    printf("starting main: \n");
    if (sigsetjmp(jmpbuf, 1)) {
        printf("ending main: ");
        exit(0);
    }

    canjump = 1;
    kill(getpid(), SIGUSR1);
}
