#include <sys/signalfd.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    sigset_t mask;
    int sfd;
    struct signalfd_siginfo fdsi;
    ssize_t s;

    sigemptyset(&mask);
    sigaddset(&mask, SIGINT);
    sigaddset(&mask, SIGQUIT);

    sigprocmask(SIG_BLOCK, &mask, NULL);

    sfd = signalfd(-1, &mask, 0);
    for (;;) {
        s = read(sfd, &fdsi, sizeof(struct signalfd_siginfo));
        if (fdsi.ssi_signo == SIGINT)
            printf("Got SIGINT\n");
        else if (fdsi.ssi_signo == SIGQUIT)
            printf("Got SIGQUIT\n");
        else
            printf("Read unexpected signal\n");
    }
}
