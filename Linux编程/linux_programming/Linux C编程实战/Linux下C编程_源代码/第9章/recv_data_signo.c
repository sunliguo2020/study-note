// ʾ�������źŴ������ݣ��������������
#include <signal.h>
#include <stdio.h>

/*���������źŴ������*/
void handler_sigint(int signo, siginfo_t *siginfo, void * pvoid)
{
	printf("recv SIGINT, the data value is:%d\n", siginfo->si_int);
}

int main()
{
	struct sigaction act;
	
	/*��ֵact�ṹ*/
	act.sa_sigaction = handler_sigint;
	act.sa_flags = SA_SIGINFO;		// ָ��ʹ�����������źŴ�����
	/*��װ�źŴ�����*/
	sigaction(SIGINT, &act, NULL);
	
	while(1)
		;

	return 0;
}
