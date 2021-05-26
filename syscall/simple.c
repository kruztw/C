#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/syscall.h>


void make_a_syscall()
{
    unsigned long long rax, rdi, rsi, rdx;
    scanf("%llu %llu %llu %llu", &rax, &rdi, &rsi, &rdx);
    syscall(rax, rdi, rsi, rdx);
}

int main()
{
    puts("Input: [rax] [rdi] [rsi] [rdx]");
    make_a_syscall();
    return 0;
}
