# Signal

## How to run ?
```
make
./<elf>
make clean
```

## What is signal ?

[Wiki](https://zh.wikipedia.org/wiki/Unix%E4%BF%A1%E5%8F%B7)

[linux](https://man7.org/linux/man-pages/man7/signal.7.html)


## POSIX

### How to list all signals ?

```shell=
BASH$ kill -L
```

[document](https://man7.org/linux/man-pages/man7/signal.7.html)


### How to send a signal ?

```C=
# process directed
int kill(pid_t pid, int sig);

# thread directed
int pthread_kill(pthread_t thread, int sig);

```

For more info, see send_signal_single.c send_signal_multi.c

[kill document](https://man7.org/linux/man-pages/man2/kill.2.html)

[pthread_kill](https://man7.org/linux/man-pages/man3/pthread_kill.3.html)


### How to set signal handler ?

```C=
void (*signal(int sig, void (*func)(int)))(int)
```

For more info, see signal_handler.c

[signal document](https://man7.org/linux/man-pages/man2/signal.2.html)

### How to block/unblock signals ?

```C=
int sigemptyset(sigset_t *set); 
int sigaddset(sigset_t *set, int signo);

# single thread version
int sigprocmask(int how, const sigset_t *restrict set, sigset_t *restrict oldset);

# multithread version
pthread_sigmask(SIG_BLOCK, &mask, NULL);
```

#### note

1. signal will be received by an arbitrary thread which doesn't block the signal. (according to linux signal document)
```
A process-directed signal may be delivered to any one of the
threads that does not currently have the signal blocked.  If more
than one of the threads has the signal unblocked, then the kernel
chooses an arbitrary thread to which to deliver the signal.
```

2. threads will inheritate the sigmask from its parent thread (the thread called pthread_create)

3. using sigprocmask in threads is unspecified exclude main thread.


For more info, see block_signal_single.c block_signal_multi.c

[sigemptyset document](https://man7.org/linux/man-pages/man3/sigemptyset.3p.html)

[sigaddset document](https://pubs.opengroup.org/onlinepubs/7908799/xsh/sigaddset.html)

[sigprocmask document](https://man7.org/linux/man-pages/man2/sigprocmask.2.html)

[pthread_sigmask document](https://man7.org/linux/man-pages/man3/pthread_sigmask.3.html)


### How to shutdown thread gracefully ?

```C=
int pthread_cancel(pthread_t thread);
```

For more info, see pthread_cancel.c

[pthread_cancel document](https://man7.org/linux/man-pages/man3/pthread_cancel.3.html)


### Reference

https://jyhshin.pixnet.net/blog/post/27826709
