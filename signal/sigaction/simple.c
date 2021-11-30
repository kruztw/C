#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

void handler(int signum)
{
    printf("signal: %d\n", signum);
    kill(getpid(), SIGALRM);
    sleep(3);
}

void my_alarm(int signum)
{
    printf("my_alarm: %d\n", signum);
}

int main()
{
    struct sigaction sa = {
        .sa_handler = handler,
    };

    signal(SIGALRM, my_alarm);

    sigemptyset(&sa.sa_mask);
    sigaddset(&sa.sa_mask, SIGALRM);      // 會在 sleep 後, 才會看到 SIGALRM 被處理, 註解掉會立即看到 my_alarm, 因為 handler sleep, 所以 handler2 被執行
    sigaction(SIGINT, &sa, 0);            // 當收到 SIGINT 後, 會執行 .sa_handler, 過程中會屏蔽 .sa_mask, 待 .sa_handler 執行完才會執行

    kill(getpid(), SIGINT);
}

