#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

pthread_cond_t cv = PTHREAD_COND_INITIALIZER;
pthread_mutex_t mtx[2] = {PTHREAD_MUTEX_INITIALIZER};

void *worker_proc(void* args)
{
    intptr_t id = (intptr_t)args;  // our id
    pthread_cond_wait(&cv, &mtx[id]);
    printf("%ld\n", id);
    return NULL;
}


int main()
{
    pthread_t threads[2];

    intptr_t id = 0;
    pthread_create(&threads[0], NULL, worker_proc, (void*)(++id));
    pthread_create(&threads[1], NULL, worker_proc, (void*)(++id));
    sleep(1);
    pthread_cond_broadcast(&cv);

    pthread_join(threads[0], NULL);
    pthread_join(threads[1], NULL);

    return 0;
}
