// 用 htop 觀察是否有將程序綁到該 CPU

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define __USE_GNU
#include <sched.h>

int main() {
    int cpu_num = sysconf(_SC_NPROCESSORS_CONF);
    int target_cpu = 1;

    cpu_set_t mask;
    CPU_ZERO(&mask);
    CPU_SET(target_cpu, &mask);
    if(sched_setaffinity(0, sizeof(mask), &mask)) {
       printf("warning ! set affinity failed! \n");
       return -1;
    }
    
    printf("total cpu: %d\n", cpu_num);
    for (int i = 0; i < cpu_num; i++)
        if (CPU_ISSET(i, &mask))
            printf("this thread %d is running processor : %d\n", i,i);

    while (1);
    return 0;
}
