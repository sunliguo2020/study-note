#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main()
{
	pid_t	pid;
	char  	*msg;
	int   	k;
	int   	exit_code;

	printf("Study how to get exit code\n");
	pid = fork();
	switch(pid) {
		case 0:
			msg = "Child process is running";
			k = 5;
			exit_code = 37;
			break;
		case -1:
			perror("Process creation failed\n");
			exit(1);
		default:
			exit_code = 0;
			break;
	}

	/* ���ӽ��̶���ִ��������δ����ӽ�����pidֵΪ0��������pidֵΪ�ӽ��̵�ID  */
	if(pid != 0) {  // �����̵ȴ��ӽ��̽���
		int 	stat_val;
		pid_t 	child_pid;
		
		child_pid = wait(&stat_val);
		
		printf("Child procee has exited, pid = %d\n",child_pid);
		if(WIFEXITED(stat_val))
         		printf("Child exited with code %d\n",WEXITSTATUS(stat_val));
       		else
        		printf("Child exited abnormally\n");
	}
	else {   // �ӽ�����ͣ5�룬����������п�����������ps aux�鿴������״̬
		while(k-->0) {
			puts(msg);
			sleep(1);
		}
	}

	exit(exit_code);
}
