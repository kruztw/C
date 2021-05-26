// 參考: https://stackoverflow.com/questions/51818655/clflush-to-invalidate-cache-line-via-c-function

#include <stdint.h>
#include <x86intrin.h>
#include <stdio.h>

int main()
{
    int array[100];
    int tmp;

    for (int i = 0; i < 100; i++)
        array[i] = i;

    _mm_mfence();
    _mm_clflush(&array[0]);
    uint64_t time1, time2, msl, hsl, osl;

    for (int i = 0; i < 2; i++) {
        _mm_mfence();
        _mm_lfence();
        time1 = __rdtsc();
        _mm_lfence();

        tmp = array[0];

        _mm_lfence();
        time2 = __rdtsc();
        _mm_lfence();

        if (i == 0) {
            msl = time2 - time1;
            printf( "miss section latency = %lu \n", msl );
        }
        else {
            hsl = time2 - time1;
            printf( "hit section latency = %lu \n", hsl );
        }
    }
  
  
    _mm_mfence();
    _mm_lfence();
    time1 = __rdtsc();
    _mm_lfence();
    _mm_lfence();
    time2 = __rdtsc();
    _mm_lfence();
    osl = time2 - time1;
  
    printf( "overhead latency = %lu \n", osl );
    printf( "Measured L1 hit latency = %lu TSC cycles\n", hsl - osl );
    printf( "Measured main memory latency = %lu TSC cycles\n", msl - osl );
  
    return 0;
}
