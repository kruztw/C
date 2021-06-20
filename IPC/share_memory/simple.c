// https://www.itread01.com/content/1550515697.html

#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

#define ASSERT(res) if((res)<0){perror(__FUNCTION__);exit(-1);}
#define key  (8888)
#define size (0x1000)


void create()
{
    int id = shmget(key, 0x1000, IPC_CREAT | IPC_EXCL | 0664);
}

void show()
{
  int id = shmget(key, 0, 0); 
  struct shmid_ds shmid;
  shmctl(id, IPC_STAT, &shmid);
  printf("euid of owner = %d\n", shmid.shm_perm.uid);
  printf("egid of owner = %d\n", shmid.shm_perm.gid);
  printf("euid of creator = %d\n", shmid.shm_perm.cuid);
  printf("egid of creator = %d\n", shmid.shm_perm.cgid);
  printf("mode = 0%o\n", shmid.shm_perm.mode);
  printf("segment size = %ld\n", shmid.shm_segsz);
  printf("last attach time = %s", ctime(&shmid.shm_atime));
  printf("last detach time = %s", ctime(&shmid.shm_dtime));
  printf("last change time = %s", ctime(&shmid.shm_ctime));
  printf("pid of creator = %d\n", shmid.shm_cpid);
  printf("pid of last shmat/shmdt = %d\n", shmid.shm_lpid);
  printf("No. of current attaches = %ld\n", shmid.shm_nattch);
}

void set()
{
  int id = shmget(key, size, IPC_CREAT | 0664);
  struct shmid_ds shmid;
  shmctl(id, IPC_STAT, &shmid);
  shmid.shm_perm.mode = 0600;
  shmctl(id, IPC_SET, &shmid);
  printf("set %d\n", id);
}

void rm()
{
  int id = shmget(key, size, IPC_CREAT | 0664);
  shmctl(id, IPC_RMID, NULL);
  printf("remove %d\n", id);
}

void attach_and_detach()
{
  int id = shmget(key, size, IPC_CREAT | 0664);
  char *buf = shmat(id, NULL, 0);
  printf("shmat %p\n", buf);
  shmdt(buf);
  printf("shmdt %p\n", buf);
}



int main(int argc, char *argv[]) {

  if (argc < 2) {
    printf("usage: %s <option -c -v -s -d -a>\n", argv[0]);
    return -1;
  }

  if (!strcmp(argv[1], "-c"))
    create();
  else if (!strcmp(argv[1], "-v"))
    show();
  else if (!strcmp(argv[1], "-s"))
    set();
  else if (!strcmp(argv[1], "-d"))
    rm();
  else if (!strcmp(argv[1], "-a"))
    attach_and_detach();

  return 0;
}
