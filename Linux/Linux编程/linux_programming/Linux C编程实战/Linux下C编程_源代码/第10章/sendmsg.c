#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define BUF_SIZE	256
#define PROJ_ID		32
#define PATH_NAME	"."

int main(void)
{
	/*�û��Զ�����Ϣ����*/
	struct mymsgbuf {
		long msgtype;
		char ctrlstring[BUF_SIZE];
	} msgbuffer;
	int		qid;    /*��Ϣ���б�ʶ��*/
	int		msglen;
	key_t	msgkey;

	/*��ȡ��ֵ*/
	if((msgkey = ftok (PATH_NAME, PROJ_ID)) == -1)
	{
		perror ("ftok error!\n");
		exit (1);
	}

	/*������Ϣ����*/
	if((qid = msgget (msgkey, IPC_CREAT|0660)) == -1)
	{
		perror ("msgget error!\n");
		exit (1);
	}
	/*�����Ϣ�ṹ�����͵���Ϣ����*/
	msgbuffer. msgtype = 3;
	strcpy (msgbuffer.ctrlstring , "Hello,message queue");
	msglen = sizeof(msgbuffer) - 4;
	if(msgsnd (qid, &msgbuffer, msglen, 0) == -1)
	{
		perror ("msgget error!\n");
		exit (1);
	}

	exit(0);
}
