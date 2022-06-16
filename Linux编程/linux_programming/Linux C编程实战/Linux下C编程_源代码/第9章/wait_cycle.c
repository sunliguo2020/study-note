// ʾ������ѭ��������ж��¼�����
#include <stdio.h>
#include <signal.h>

#define	UNHAPPEN	0	// δ����
#define	HAPPENED	1	// �ѷ���

/*����ȫ�ֱ����Ա�ʶ�¼��Ƿ���*/
int		flag_happen;

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

	while (1) {
		if (flag_happen == HAPPENED) {
			printf("event happened\n");
			/*... you can do something else here...*/
			break;
		}
	}
	
	return 0;
}
