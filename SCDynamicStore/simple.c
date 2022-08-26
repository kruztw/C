#include <stdio.h>
#include <SystemConfiguration/SystemConfiguration.h>

int main(int argc, char **argv) {
    SCDynamicStoreRef store;
    CFStringRef name;
    uid_t uid;
    char username[256];

    store = SCDynamicStoreCreate(NULL, CFSTR("GetConsoleUser"), NULL, NULL);
    name = SCDynamicStoreCopyConsoleUser(store, &uid, NULL);
    CFRelease(store);

    if (name != NULL) {
        if (CFStringGetCString(name, username, sizeof(username)-1, kCFStringEncodingUTF8) == false) {
            printf("CFStringGetCString failed\n");
            exit(-1);
        }

        CFRelease(name);
    } else {
        strcpy(username, "<none>");
    }

    printf("%d %s\n", uid, username);

    return 0;
}
