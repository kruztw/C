// 參考 : https://szlin.me/2017/08/23/kernel_seccomp/
// filter mode : https://github.com/gebi/teach-seccomp/blob/master/step-2/example.c

#include <stdio.h>

// seccomp
#include <seccomp.h>
#include <sys/prctl.h>

// filter_mode
#include <linux/filter.h>
#include "seccomp-bpf.h"

int strict_mode()
{
    return prctl(PR_SET_SECCOMP, SECCOMP_MODE_STRICT); // read write exit sigreturn
}

int self_defined()
{
    scmp_filter_ctx ctx = seccomp_init(SCMP_ACT_KILL);
    seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(exit), 0);
    return seccomp_load(ctx);
}

int filter_mode()
{
    struct sock_filter filter[] = {
        /* Validate architecture. */
        VALIDATE_ARCHITECTURE,
        /* Grab the system call number. */
        EXAMINE_SYSCALL,
        ALLOW_SYSCALL(exit),
        KILL_PROCESS,
    };

    struct sock_fprog prog = {
        .len = (unsigned short)(sizeof(filter)/sizeof(filter[0])),
	.filter = filter,
    };

    // 需要 CAP_SYS_ADMIN 或設定 NO_NEW_PRIVS  https://elixir.bootlin.com/linux/v5.13/source/kernel/seccomp.c#L654
    prctl(PR_SET_NO_NEW_PRIVS, 1, 0, 0, 0); 
    return prctl(PR_SET_SECCOMP, SECCOMP_MODE_FILTER, &prog);
}

int main()
{
    filter_mode();
    //while (1); // cat /proc/<pid>/status => seccomp 0: disable 1: strict 2: filter
    printf("hello world\n");
}
