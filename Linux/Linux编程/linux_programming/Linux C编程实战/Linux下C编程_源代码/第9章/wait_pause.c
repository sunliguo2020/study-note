// ʾ��pause����ȴ��¼��ķ���
#include <stdio.h>
#include <signal.h>
#include <unistd.h>

#define	UNHAPPEN	0	// δ����
#define	HAPPENED	1	// �ѷ���

/*����ȫ�ֱ����Ա�ʶ�¼��Ƿ���*/
int	flag_happen;

void handler_sigint(int signo)
{
	flag_happen = HAPPENED;
}

int main()
{
	/*��װ�źŴ�����*/
	if (signal(SIGINT, handler_sigint) == SIG_ERR) {
		perror("signal");
		exit(1);
	}

	while (flag_happen == UNHAPPEN)
		pause();

	printf("after event happened\n");
	/*... you can do something else here ...*/

	return 0;
}
