// ʾ��inet�������ʹ��
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main()
{
	char		buffer[32];
	int		ret = 0;
	int		host = 0;
	int		network = 0;
	unsigned int	address = 0;
	struct in_addr	in;
	
	in.s_addr = 0;

	/*����һ����"."�ָ����ַ�����ʽ��IP��ַ*/
	printf("please input your ip address:");
    	fgets(buffer, 31, stdin);
	buffer[31] = '\0';

	/*ʾ��ʹ��inet_aton()����*/
	if ((ret = inet_aton(buffer, &in)) == 0) {
		printf("inet_aton: \t invalid address\n");
	} else {
		printf("inet_aton:\t0x%x\n", in.s_addr);
	}
	
	/*ʾ��ʹ��inet_addr()����*/
	if ((address = inet_addr(buffer)) == INADDR_NONE) {
		printf("inet_addr: \t invalid address\n");
	} else {
		printf("inet_addr:\t0x%lx\n", address);
	}

	/*ʾ��ʹ��inet_network()����*/
	if ((address = inet_network(buffer)) == -1) {
		printf("inet_network: \t invalid address\n");
	} else {
		printf("inet_network:\t0x%lx\n", address);
	}
	
	/*ʾ��ʹ��inet_ntoa()����*/
	if (inet_ntoa(in) == NULL) {
		printf("inet_ntoa: \t invalid address\n");
	} else {
		printf("inet_ntoa:\t%s\n", inet_ntoa(in));
	}

	/*ʾ��ʹ��inet_lnaof()��inet_netof()����*/
	host = inet_lnaof(in);
	network =  inet_netof(in);
	printf("inet_lnaof:\t0x%x\n", host);
	printf("inet_netof:\t0x%x\n", network);

	in = inet_makeaddr(network, host);
	printf("inet_makeaddr:0x%x\n", in.s_addr);

	return 0;
}
