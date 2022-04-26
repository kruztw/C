#include <rpc/rpc.h>
#include <stdio.h>

#include "math.h"

int main (argc, argv)
int argc;
char *argv[];
{
    CLIENT *cl;
    vars numbers;
    int *result;

    char *server_ip = "127.0.0.1";  // change by yourself
    cl = clnt_create(server_ip, MATHPROG, MATHVERS, "tcp");
    
    if (cl == NULL) {
        clnt_pcreateerror(argv[1]);
        exit(1);
    }
    
    numbers.a = 1;
    numbers.b = 2;

    result = add_2(&numbers, cl);
    if (result == NULL) {
        clnt_perror(cl, "add_2");
        exit(1);
    }

    printf("a + b =  %d\n", *result);
    exit(0);
}
