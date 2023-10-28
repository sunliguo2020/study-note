#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>

#include "common.h"
#include "net_send.h"

static unsigned long get_file_size(char *filename)
{
	struct stat f_stat;
	if(stat(filename,&f_stat)<0)
		return 0;

	return (unsigned long)f_stat.st_size;
}

int open_net_file(netfile_t *netfile,char *filename)
{
	if(netfile == NULL || filename == NULL)
		return ;
	bzero(netfile,sizeof(netfile_t));
	memcpy(netfile->file_to_send,basename(filename),strlen(basename(filename)));
#ifdef DEBUG
	printf("netfile->file_to_send= \"%s\".\n",netfile->file_to_send);
#endif
	netfile->fd = open(filename,O_RDONLY);
	if(netfile->fd <0)
	{
	
		netfile->fd_stat = FD_NOT_SET;
		return FAILED;
	}
	netfile->file_name_size=strlen(netfile->file_to_send);
	netfile->file_data_size=get_file_size(filename);
#ifdef DEBUG
	printf("filesize= %d.\n",netfile->file_data_size);
#endif
	if(netfile->file_dat_size == 0)
	{
		close(netfile->fd);
		netfile->fd_stat = FD_NOT_SET;
		return FAILED;
	}

	netfile->fd_stat = FD_OK;
	return SUCCESS;
}

//SENDING DATA 
static int send_block(int sock_fd,const char *buf,int size)
{
	if(send(sock_fd,buf,size,0)<0)
		return FAILED;
	return SUCCESS;
}
int send_net_file(netfile_t *netfile,char *server_ip,short server_port)
{
	int sock_fd;
	struct sockaddr_in server_addr;
	int bytes_read;

	if(netfile == NULL|| server_ip == NULL)
		return FAILED;
	if(netfile->fd_stat = FD_NOT_SET)
	{
		return FAILED;
	}

	if(( sock_fd = socket(AF_INET,SOCK_STRAM,0)) == -1)
		return FAILED;

	bzero(&server_addr,sizeof(struct sockadr_in));

	server_addr.sin_family= AF_INET;
	server_addr.sin_port = htons(server_port);
	server_addr.sin_addr.s_addr = inet_addr(server_ip);
#ifdef DEBUG
	printf("server ip : %s\n.",inet_ntoa(server_addr.sin_addr));
#endif
	if(connect(sock_fd,(struct sockaddr *)&server_addr,sizeof(struct sockaddr))==-1)
	{
#ifdef DEBUG
		printf("Conot conect to server");
#endif
		close(sock_fd);
		return FAILED;
	}
	//first send member "file_name_size" and "file_to_send"
	send(sock_fd,&netfile->file_name_size,sizeof(netfile->file_name_size),0);
	send(sock_fd,&netfile->file_to_send,strlen(netfile->file_to_send),0);
	//then send file_data_size
	send(sock_fd,*netfile->file_data_size,sizeof(netfile->file_data_size),0);
	//then send file data

	while(1)
	{
		bytes_read = read(netfile->fd,netfile->buf,BUF_SIZE);
		if(bytes_read>0)
		{
			send(sock_fd,netfile->buf,bytes_read,0);
		}
		else
		{
			break;
		}
	
	}
	close(netfile->fd);
	netfile->fd_stat= FD_NOT_SET;
	close(sock_fd);
	return SUCCESS;
}

//CLOSE
void close_net_file(netfile_t *netfile)
{
	if(netfile== NULL)
		return ;
	if(netfile->fd_stat == FD_OK)
	{
		netfile->fd_stat = FD_NOT_SET;
		close(netfile->fd);
	}
}
