// ref: https://www.cntofu.com/book/46/linux_system/pthreadsigmask_kong_zhi_xian_cheng_de_xin_hao_yan_.md

#include <stdio.h>
#include <sys/signal.h>
#include <pthread.h>
#include <unistd.h>

void handler(int signum) {
    printf("signal: %d\n", signum);
}

void *child(void *args) {
    // signal(SIGINT, handler); // 會影響到其他 thread 

    // 正確作法
    sigset_t mask;
    sigemptyset(&mask);
    sigaddset(&mask, SIGINT);
    pthread_sigmask(SIG_BLOCK, &mask, NULL);             // 屏蔽 SIG_INT, 去掉這行會發現 main thread 也被 kill 掉, 因為 child 收到 SIGINT 會連帶 main thread 被砍掉
    sleep(3);

    return NULL;
}

int main()
{
  pthread_t tid;

  pthread_create(&tid, NULL, child, NULL);
  sleep(1);                                             // 等待 child 屏蔽 SIGINT
  pthread_kill(tid, SIGINT);                            // 被屏蔽了
  pthread_join(tid, NULL);

  printf("main sleep...\n");
  sleep(3);                                             // 按 ctrl C 會發現直接離開, 代表 main thread 的 SIG_INT 沒被屏蔽
  return 0;
}
