// https://yayaya6d.pixnet.net/blog/post/350095123-linus%E5%90%84%E7%A8%AE%E9%9B%9C%E8%AB%87--process%E9%96%93%E7%9A%84%E6%BA%9D%E9%80%9A%EF%BC%9Amsg-queue

#include <stdio.h>
#include <stdlib.h>
#include <sys/msg.h>

#define MSG_FILE "/etc/passwd"
#define MSG_TYPE_SERVER (0x5408)
#define MSG_TYPE_CLIENT (0x9588)

struct msg_form {
	long mtype;
	char mtext[256];
};

int main()
{
	int msqid;
	key_t key;
	struct msg_form msg;
	
	key = ftok(MSG_FILE,'z');
	printf("Message Queue - Server key is: %d.\n", key);

    msqid = msgget(key, IPC_CREAT|0777);

	printf("My msqid is: %d.\n", msqid);

	for(;;) 
	{
		msgrcv(msqid, &msg, 256, MSG_TYPE_SERVER, 0);
		printf("Server: receive msg.mtext is: %s.\n", msg.mtext);
		printf("Server: receive msg.mtype is: %ld.\n", msg.mtype);
		
        msg.mtype = MSG_TYPE_CLIENT;
		sprintf(msg.mtext, "hello, I'm server\n");
		msgsnd(msqid, &msg, sizeof(msg.mtext), 0);
	}
}
