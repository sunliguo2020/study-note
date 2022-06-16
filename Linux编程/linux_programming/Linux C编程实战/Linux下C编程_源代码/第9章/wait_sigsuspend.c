// ʾ��ʹ��sigsuspend��������ȴ��¼��ķ���
#include <stdio.h>
#include <signal.h>

#define	UNHAPPEN	0	// δ����
#define	HAPPENED	1	// �ѷ���

/*����ȫ�ֱ����Ա�ʶ�¼��Ƿ���*/
int		flag_happen;

/*�Զ���Ĵ�������*/
void my_err(const char * err_string, int line)
{
	fprintf(stderr, "line:%d  ", line);
	perror(err_string);
	exit(1);
}

void handler_sigint(int signo)
{
	flag_happen = HAPPENED;
}

int main()
{
	sigset_t	newmask, oldmask, zeromask;

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

	while (flag_happen == UNHAPPEN)
		sigsuspend(&zeromask);

	printf("after event happened\n");
	/*... do something else...*/
	
	/*���ź������ָֻ�*/
	if (sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0) {
		my_err("sigprocmask", __LINE__);
	}

	return 0;
}
