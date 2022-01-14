// ref: https://man7.org/linux/man-pages/man3/pthread_cancel.3.html

#include <pthread.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>

#define handle_error_en(en, msg) \
        do { errno = en; perror(msg); exit(EXIT_FAILURE); } while (0)

void * thread_func(void *ignored_argument)
{
    int s;
    
    s = pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, NULL);
    if (s != 0)
        handle_error_en(s, "pthread_setcancelstate");

    printf("thread_func(): started; cancellation disabled\n");
    sleep(5);
    printf("thread_func(): about to enable cancellation\n");

    s = pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
    if (s != 0)
        handle_error_en(s, "pthread_setcancelstate");

    sleep(1000);        

    printf("thread_func(): not canceled!\n");
    return NULL;
}

int main()
{
    pthread_t t;
    void *res;
    int s;

    s = pthread_create(&t, NULL, &thread_func, NULL);
    if (s != 0)
        handle_error_en(s, "pthread_create");

    sleep(2);

    s = pthread_cancel(t);
    if (s != 0)
        handle_error_en(s, "pthread_cancel");

    s = pthread_join(t, &res);
    if (s != 0)
        handle_error_en(s, "pthread_join");

    if (res == PTHREAD_CANCELED) {
        printf("main(): thread was canceled\n");
    } else {
        printf("main(): thread wasn't canceled (shouldn't happen!)\n");
    }

    return 0;
}
