#define _GNU_SOURCE

#include <dlfcn.h>
#include <stdio.h>

int rand(void) {
    int (*original_rand)(void);
    original_rand = dlsym(RTLD_NEXT, "rand");
    int out = original_rand();
    printf("rand: %d\n", out);
    return out;
}
