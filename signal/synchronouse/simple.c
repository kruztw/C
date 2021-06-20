// https://zhuanlan.zhihu.com/p/227924915

#define _POSIX_C_SOURCE  200809L
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>

static inline const char *signal_name(const int signum)
{
    switch (signum) {
    case SIGINT:  return "SIGINT";
    case SIGHUP:  return "SIGHUP";
    case SIGTERM: return "SIGTERM";
    case SIGQUIT: return "SIGQUIT";
    case SIGUSR1: return "SIGUSR1";
    case SIGUSR2: return "SIGUSR2";
    default:      return "(unnamed)";
    }    
}

int main(void)
{
    sigset_t  mask;
    siginfo_t info;
    pid_t     child, p;
    int       signum;    

    sigemptyset(&mask);
    sigaddset(&mask, SIGINT);
    sigaddset(&mask, SIGHUP);
    sigaddset(&mask, SIGTERM);
    sigaddset(&mask, SIGQUIT);
    sigaddset(&mask, SIGUSR1);
    sigaddset(&mask, SIGUSR2);
    if (sigprocmask(SIG_BLOCK, &mask, NULL) == -1) {                              // SIG_BLOCK 應該是指會接收, 如果換成 SIG_UNBLOCK 或把 SIGUSR1 拿掉, parent 會收到 SIGHUP (child 已經結束)
        fprintf(stderr, "Cannot block SIGUSR1: %s.\n", strerror(errno));
        return EXIT_FAILURE;
    }

    child = fork();
    if (!child) {  // child
        printf("Child process %d sleeping for 3 seconds ...\n", (int)getpid());
        sleep(3);

        printf("Child process %d sending SIGUSR1 to parent process (%d) ...\n", (int)getpid(), (int)getppid());
        kill(getppid(), SIGUSR1);

        printf("Child process %d exiting.\n", (int)getpid());
        return EXIT_SUCCESS;
    }

    printf("Parent process %d is waiting for signals.\n", (int)getpid());
    while (1) {

        signum = sigwaitinfo(&mask, &info);          // 與 sigwait 類似, 差別在 sigwait 第二個參數用來接收 signum, sigtimedwait 則是多一個 timeout 的參數
        if (info.si_pid == child)
            printf("Parent process: Received signal %d (%s) from child process %d.\n", signum, signal_name(signum), (int)child);
        else if (info.si_pid)
            printf("Parent process: Received signal %d (%s) from process %d.\n", signum, signal_name(signum), (int)info.si_pid);
        else
            printf("Parent process: Received signal %d (%s).\n", signum, signal_name(signum));

        /* Exit when SIGUSR1 received from child process. */
        if (signum == SIGUSR1 && info.si_pid == child) {
            printf("Parent process: Received SIGUSR1 from child.\n");
            break;
        }

        /* Also exit if Ctrl+C pressed in terminal (SIGINT). */
        if (signum == SIGINT && !info.si_pid) {
            printf("Parent process: Ctrl+C pressed.\n");
            break;
        }
    }

    while ((p = waitpid(child, NULL, 0)) != child)
    return EXIT_SUCCESS;
}
