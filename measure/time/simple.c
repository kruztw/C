#include <stdio.h>
#include <stdint.h>
#include <x86intrin.h> // __rdtsc

int main()
{
    uint64_t time1 = __rdtsc();
    printf("time1 = %lu\n", time1);
}
