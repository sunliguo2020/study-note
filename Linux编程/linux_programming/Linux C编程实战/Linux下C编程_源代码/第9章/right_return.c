#include <stdio.h>
#include <setjmp.h>
#include <signal.h>
#include <unistd.h>

#define	ENV_UNSAVE	0
#define	ENV_SAVED	1

int	flag_saveenv = ENV_UNSAVE;
jmp_buf	env;	  // �������תλ�õ�ջ��Ϣ

/*�ź�SIGRTMIN+15�Ĵ�����*/
void handler_sigrtmin15(int signo)
{
	if (flag_saveenv == ENV_UNSAVE) {
		return;
	}
	printf("recv SIGRTMIN+15\n");
	sleep(10);
	printf("in handler_sigrtmin15, after sleep\n");
	siglongjmp(env, 1);  // ���ص�env����ע��ڶ���������ֵ
}

int main()
{
	/*���÷��ص�*/
	switch (sigsetjmp(env, 1)) {	// sigsetjmp�ĵڶ�������ֻҪ��0����
		case 0:
			printf("return 0\n");
			flag_saveenv = ENV_SAVED;
			break;
		case 1:
			printf("return from SIGRTMIN+15\n");
			break;
		default:
			printf("return else\n");
			break;
	}

	/*��׽�źţ���װ�źŴ�����*/
	signal(SIGRTMIN+15, handler_sigrtmin15);

	while (1)
		;

	return 0;
}
