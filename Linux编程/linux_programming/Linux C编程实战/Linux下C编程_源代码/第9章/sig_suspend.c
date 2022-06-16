#include <stdio.h>
#include <signal.h>
#include <unistd.h>

/*�Զ���Ĵ�������*/
void my_err(const char * err_string, int line)
{
	fprintf(stderr, "line:%d  ", line);
	perror(err_string);
	exit(1);
}

/*SIGINT�Ĵ�����*/
void handler_sigint(int signo)
{
	printf("recv SIGINT\n");
}

int main()
{
	sigset_t	newmask, oldmask, zeromask;	// �����źż�

	/*��װ�źŴ�����*/
	if (signal(SIGINT, handler_sigint) == SIG_ERR) {
		my_err("signal", __LINE__);
	}

	sigemptyset(&newmask);
	sigemptyset(&zeromask);
	sigaddset(&newmask, SIGINT);

	/*�����ź�SIGINT*/
	if (sigprocmask(SIG_BLOCK, &newmask, &oldmask) < 0) {
		my_err("sigprocmask", __LINE__);
	} else {
		printf("SIGINT blocked\n");
	}

	/*�ٽ���*/
	
	/*ʹ��sigsuspendȡ�������źŵ����β��ȴ��źŵĴ���*/
	if (sigsuspend(&zeromask) != -1) {  // sigsuspend���Ƿ���-1
		my_err("sigsuspend", __LINE__);
	} else {
		printf("recv a signo, return from sigsuspend\n");
	}

/*-----------------------------------------
// ���ʹ��sigprocmask ���� pause���ܻ���ִ���
	if (sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0) {
		my_err("sigprocmask", __LINE__);
	}
	pause();
-----------------------------------------*/

	/*���ź������ָֻ�*/
	if (sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0) {
		my_err("sigprocmask", __LINE__);
	}
	
	while (1)
		;

	return 0;
}
