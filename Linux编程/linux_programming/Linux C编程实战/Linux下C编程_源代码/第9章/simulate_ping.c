// ��ģ��ping����Ŀ��
#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void send_ip()
{
	/*���ͻ��������ģ�����ֻ�Ǵ�ӡ��Ϣ*/
	printf("send a icmp echo request packet\n");
}

void recv_ip()
{
	/*�������׽����ϵȴ����ݲ��������ģ�����ֻ��ʹ����ѭ��*/
	while(1)
		;
}

void handler_sigalarm(int signo)
{
	send_ip();
	alarm(2);
}

int main()
{
	/*��װ�źŴ������*/
	signal(SIGALRM, handler_sigalarm);

	/*����һ��SIGALRM�źŸ�������*/
	raise(SIGALRM);
	recv_ip();

	return 0;
}
