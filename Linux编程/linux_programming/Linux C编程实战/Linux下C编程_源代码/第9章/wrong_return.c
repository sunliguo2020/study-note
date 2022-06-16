#include <stdio.h>
#include <setjmp.h>
#include <signal.h>

jmp_buf	env;	 // �������תλ�õ�ջ��Ϣ

/*�ź�SIGRTMIN+15�Ĵ�����*/
void handler_sigrtmin15(int signo)
{
	printf("recv SIGRTMIN+15\n");
	longjmp(env, 1);	// ���ص�env����ע��ڶ���������ֵ
}

/*�ź�SIGRTMAX-15�Ĵ�����*/
void handler_sigrtmax15(int signo)
{
	printf("recv SIGRTMAX-15\n");
	longjmp(env, 2);	// ���ص�env����ע��ڶ���������ֵ
}

int main()
{
	/*���÷��ص�*/
	switch (setjmp(env)) {
		case 0:
			break;
		case 1:
			printf("return from SIGRTMIN+15\n");
			break;
		case 2:
			printf("return from SIGRTMAX-15\n");
			break;
		default:
			break;
	}

	/*��׽�źţ���װ�źŴ�����*/
	signal(SIGRTMIN+15, handler_sigrtmin15);
	signal(SIGRTMAX-15, handler_sigrtmax15);

	while (1)
		;

	return 0;
}
