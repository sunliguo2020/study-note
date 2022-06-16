#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define BUF_SIZE	256
#define PROJ_ID		32
#define PATH_NAME	"."

int main(void)
{
	/*�û��Զ�����Ϣ������*/
	struct mymsgbuf{
		long msgtype;
		char ctrlstring[BUF_SIZE];
	} msgbuffer;
	int		qid;     /*��Ϣ���б�ʶ��*/
	int		msglen;
	key_t	msgkey;

	/*��ȡ��ֵ*/
	if((msgkey = ftok(PATH_NAME, PROJ_ID)) == -1)
	{
		perror("ftok error!\n");
		exit(1);
	}

	/*��ȡ��Ϣ���б�ʶ��*/
	if((qid = msgget(msgkey, IPC_CREAT|0660)) == -1)
	{
		perror ("msgget error!\n");
		exit (1);
	}

	msglen = sizeof(struct mymsgbuf) - 4;
	if (msgrcv(qid, &msgbuffer, msglen, 3, 0) == -1)  /*��ȡ����*/
	{
		perror ("msgrcv error!\n");
		exit (1);
	}
	printf("Get message %s\n", msgbuffer.ctrlstring);

	exit(0);
}
