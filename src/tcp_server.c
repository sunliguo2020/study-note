#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <stdio.h>

int main(int argc,char **argv)
{
	int size,listensd,recvsd;
	char s[100];
	struct sockaddr_in servaddr,clientaddr;
	if(argc !=2 )
	{
		printf("usage: server TCPPORT\n");
		return -1;
	}
	listensd = socket(PF_INET,SOCK_STREAM,IPPROTO_TCP);
	if(listensd == -1)
	{
		printf("socket error\n");
		return -1;
	}

	servaddr.sin_family=AF_INET;
	servaddr.sin_port=htons(atoi(argv[1]));
	servaddr.sin_addr.s_addr=INADDR_ANY;

	if (bind(listensd,&servaddr,sizeof(servaddr)) ==-1)
	{
		printf("can not bind\n",argv[1]);
		close(listensd);
		return -1;
	
	}
	if(listen(listensd,2) == -1)
	{
		printf("listen failed");
		close(listensd);
		return -1;
	}
	while(1)
	{

	size=sizeof(clientaddr);
	recvsd = accept(listensd,&clientaddr,&size);
	if(recvsd == -1)
	{
		printf("can nt accept connection\n");
		close(listensd);
		return -1;
	}
	close(listensd);
	while(1)
	{
		if((size=recv(recvsd,s,100,0))>0)
			printf("i received %d bytes:%s",size,s);
	}
	}
}
