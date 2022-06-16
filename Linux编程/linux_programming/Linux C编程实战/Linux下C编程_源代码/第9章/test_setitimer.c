#include <stdio.h>
#include <signal.h>
#include <sys/time.h>
#include <unistd.h>

/*�źŴ������*/
void handler_sigtime(int signo)
{
	switch (signo) {
		case SIGALRM:
			printf("recv SIGALRM\n");
			break;
		case SIGPROF:
			printf("recv SIGPROF\n");
			break;
		default:
			break;
	}
}

int main()
{
	struct itimerval value;

	/*��װ�źŴ�����*/
	signal(SIGALRM, handler_sigtime);
	signal(SIGPROF, handler_sigtime);

	/*��ʼ��value�ṹ*/
	value.it_value.tv_sec = 1;			// ��һ��1�봥���ź�
	value.it_value.tv_usec = 0;
	value.it_interval.tv_sec = 5;		// �ڶ��ο�ʼÿ5�봥���ź�
	value.it_interval.tv_usec = 0;

	/*���ö�ʱ��*/
	setitimer(ITIMER_REAL, &value, NULL);
	setitimer(ITIMER_PROF, &value, NULL);

	while(1)
		;

	return 0;
}
