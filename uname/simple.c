#include <sys/utsname.h>
#include <stdio.h>

int main() {
    struct utsname u;
    if (uname(&u)) {
        puts("uname failed");
        return -1;
    }                   
    
    printf("OS sysname: %s\n", u.sysname);

    return 0;
}
