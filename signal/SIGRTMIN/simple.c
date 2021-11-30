// https://zhuanlan.zhihu.com/p/227924915

#include <stdio.h>
#include <signal.h>


void MinPlus2Handler(int signum)
{
    printf(" Got a SIGRTMIN + 2 signal %d\n", signum);
}

int main(int argc, char* argv[]) {
    signal(SIGRTMIN+2, MinPlus2Handler);     // SIGRTMIN ~ SIGRTMAX 間的 signal linux 未定義, 由使用者自行定義, Real Time 的功用在於抵達順序與發送一致
    kill(0, SIGRTMIN+2);
    return 0;
}
