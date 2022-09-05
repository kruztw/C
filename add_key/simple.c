// document: https://man7.org/linux/man-pages/man2/add_key.2.html

#include <sys/types.h>
#include <keyutils.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    key_serial_t key;

    char *type = "user";
    char *description = "mykey";
    char *payload = "some payload";

    key = add_key(type, description, payload, strlen(payload), KEY_SPEC_SESSION_KEYRING);

    if (key == -1) {
        perror("add_key");
        exit(EXIT_FAILURE);
    }

    printf("Key ID is %jx\n", (uintmax_t) key);

    exit(EXIT_SUCCESS);
}

