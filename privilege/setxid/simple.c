#define _GNU_SOURCE

#include <grp.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    setgid(1);
    setgroups(0, NULL);
    setuid(1);
    execl("/bin/sh", "sh", NULL);
}
