#include <stdio.h>
#include <unistd.h>
#include <signal.h>

/*�Զ���Ĵ�������*/
void my_err(const char * err_string, int line)
{
	fprintf(stderr, "line:%d  ", line);
	perror(err_string);
	exit(1);
}

/*SIGINT�Ĵ�����*/
void hander_sigint(int signo)
{
	printf("recv SIGINT\n");
}

int main()
{
	sigset_t	newmask, oldmask, pendmask;	// �����źż�

	/*��װ�źŴ�����*/
	if (signal(SIGINT, hander_sigint) == SIG_ERR) {
		my_err("signal", __LINE__);
	}
	
	/*˯��10��*/
	sleep(10); 

	/*��ʼ���źż�newmask����SIGINT��ӽ�ȥ*/
	sigemptyset(&newmask);
	sigaddset(&newmask, SIGINT);

	/*�����ź�SIGINT*/
	if (sigprocmask(SIG_BLOCK, &newmask, &oldmask) < 0) {
		my_err("sigprocmask", __LINE__);
	} else {
		printf("SIGINT blocked\n");
	}

	sleep(10);

	/*��ȡδ���źŶ���*/
	if (sigpending(&pendmask) < 0) {
		my_err("sigpending", __LINE__);
	}
	/*���δ���źŶ��������Ƿ���SIGINT*/
	switch (sigismember(&pendmask, SIGINT)) {
		case 0:
			printf("SIGINT is not in pending queue\n");
			break;
		case 1:
			printf("SIGINT is in pending queue\n");
			break;
		case -1:
			my_err("sigismember", __LINE__);
			break;
		default:
			break;
	}
	
	/*�����SIGINT������*/
	if (sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0) {
		my_err("sigprocmask", __LINE__);
	} else {
		printf("SIGINT unblocked\n");
	}

	while(1)
		;

	return 0;
}
