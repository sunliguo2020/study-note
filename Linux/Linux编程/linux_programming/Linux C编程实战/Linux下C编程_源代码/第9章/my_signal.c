#include <stdio.h>
#include <signal.h>

/*�źŴ�����*/
void handler_sigint(int signo)
{
	printf("recv SIGINT\n");
}

int main()
{
	/*��װ�źŴ�����*/
	signal(SIGINT, handler_sigint);
	
	while(1)
		;

	return 0;
}
