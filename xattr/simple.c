#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/xattr.h>

int main(int argc, char *argv[])
{
    ssize_t buflen, keylen, vallen;
    char *buf, *key, *val;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s path\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    char *value = "hello world";
    if (setxattr(argv[1], "user.x", value, strlen(value), 0) == -1)
        return 0;

    if (setxattr(argv[1], "user.y", "", 0, 0) == -1)
        return 0;

    buflen = listxattr(argv[1], NULL, 0);
    if (buflen == -1) {
        perror("listxattr");
        return -1;
    }

    if (buflen == 0) {
        printf("%s has no attributes.\n", argv[1]);
        return 0;
    }

    buf = malloc(buflen);
    buflen = listxattr(argv[1], buf, buflen);
    if (buflen == -1) {
        perror("listxattr");
        return -1;
    }

    key = buf;
    while (buflen > 0) {
        printf("%s: ", key);
        vallen = getxattr(argv[1], key, NULL, 0);
        if (vallen == -1) {
            perror("getxattr");
            return -1;
        }

        if (vallen > 0) {
            val = malloc(vallen + 1);
            vallen = getxattr(argv[1], key, val, vallen);
            if (vallen == -1) {
                perror("getxattr");
                return -1;
            }

            val[vallen] = 0;
            printf("%s", val);
            free(val);
        } else if (vallen == 0) {
            printf("<no value>");
        }

        printf("\n");

        keylen = strlen(key) + 1;
        buflen -= keylen;
        key += keylen;
    }

    removexattr(argv[1], "user.x");
    removexattr(argv[1], "user.y");

    free(buf);
    exit(EXIT_SUCCESS);
}

