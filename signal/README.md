# Signal

## What is signal ?

[Wiki](https://zh.wikipedia.org/wiki/Unix%E4%BF%A1%E5%8F%B7)

## POSIX

### How to list all signals ?

```shell=
BASH$ kill -L
```

[document](https://man7.org/linux/man-pages/man7/signal.7.html)


### How to send a signal ?

```C=
int kill(pid_t pid, int sig);
```

For more info, see send_signal.c

[kill document](https://man7.org/linux/man-pages/man2/kill.2.html)


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

1. signal will be received by the first created thread which doesn't block the signal.

2. threads will inheritate the sigmask from its parent thread (the thread called pthread_create)

3. using sigprocmask in threads is unspecified exclude main thread.


[sigemptyset document](https://man7.org/linux/man-pages/man3/sigemptyset.3p.html)

[sigaddset document](https://pubs.opengroup.org/onlinepubs/7908799/xsh/sigaddset.html)

[sigprocmask document](https://man7.org/linux/man-pages/man2/sigprocmask.2.html)

[pthread_sigmask document](https://man7.org/linux/man-pages/man3/pthread_sigmask.3.html)


### Reference

https://jyhshin.pixnet.net/blog/post/27826709
