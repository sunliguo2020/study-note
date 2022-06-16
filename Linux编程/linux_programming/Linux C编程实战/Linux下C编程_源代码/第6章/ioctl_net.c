// ʾ��ioctl��ʹ��
// �������޸��������ϵĳ��򣬰�Ȩ��ԭ��������
#include <stdio.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <net/if.h>

unsigned char	g_eth_name[16];
unsigned char	g_macaddr[6];
unsigned int	g_subnetmask;
unsigned int	g_ipaddr;
unsigned int	g_broadcast_ipaddr;

/*��ʼ�����磬��ȡ��ǰ�����豸����Ϣ*/
void init_net(void)
{
	int i;
	int sock;
	struct sockaddr_in sin;
	struct ifreq ifr;

	sock = socket(AF_INET, SOCK_DGRAM, 0);
	if (sock == -1) {
		perror("socket");
	}
    
	strcpy(g_eth_name, "eth0");
    	strcpy(ifr.ifr_name, g_eth_name);
	printf("eth name:\t%s\n", g_eth_name);


	// ��ȡ����ӡ������ַ
	if (ioctl(sock, SIOCGIFHWADDR, &ifr) < 0) {
		perror("ioctl");
	}
	memcpy(g_macaddr, ifr.ifr_hwaddr.sa_data, 6);

	printf("local mac:\t");
	for(i=0;i<5;i++) {
		printf("%.2x:", g_macaddr[i]);
	}
	printf("%.2x\n",g_macaddr[i]);

	// ��ȡ����ӡIP��ַ
	if (ioctl(sock, SIOCGIFADDR, &ifr) < 0) {
		perror("ioctl");
	}
	memcpy(&sin, &ifr.ifr_addr, sizeof(sin));
	g_ipaddr = sin.sin_addr.s_addr;
	printf("local eth0:\t%s\n", inet_ntoa(sin.sin_addr));

	// ��ȡ����ӡ�㲥��ַ
	if (ioctl(sock, SIOCGIFBRDADDR, &ifr) < 0) {
		perror("ioctl");
	}
	memcpy(&sin, &ifr.ifr_addr, sizeof(sin));
	g_broadcast_ipaddr = sin.sin_addr.s_addr;
	printf("broadcast:\t%s\n", inet_ntoa(sin.sin_addr));

	// ��ȡ����ӡ��������
	if (ioctl(sock, SIOCGIFNETMASK, &ifr) < 0) {
		perror("ioctl");
	}
	memcpy(&sin, &ifr.ifr_addr, sizeof(sin));
	g_subnetmask = sin.sin_addr.s_addr;
	printf("subnetmask:\t%s\n", inet_ntoa(sin.sin_addr));

	close(sock);
}

int main()
{
	/*initialize...*/
	init_net();

	/*do something*/

	return 0;
}
