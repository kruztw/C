#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <error.h>
#include <string.h>
#include <unistd.h>

void sig_handler(int signum)
{
    printf("in handler\n");
}

int main(int argc, char **argv)
{
    char buf[100] = {};
    int ret;
    struct sigaction action, old_action;

    action.sa_handler = sig_handler;
    sigemptyset(&action.sa_mask);
    action.sa_flags = SA_RESTART;     // SA_RESTART 會讓被中斷的 syscal 重新執行
                                      // e.g. 在 read 中斷, 可以重新 read
                                      // 去掉這行, 在 read 中斷, 就不能 read 了

    sigaction(SIGINT, &action, NULL);

    ret = read(0, buf, 100);
    if (ret == -1)
        perror("read");

    printf("read %d bytes:\n", ret);
    printf("%s\n", buf);

    return 0;
}
