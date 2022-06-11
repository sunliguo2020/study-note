#include <stdio.h>
#include <stdlib.h>

#include "common.h"

int main(int argc,char ** argv)
{
	int sock_fd;
	int new_fd;
	int fd_out;
	pid_t pid;
	socklen_t optval;
	struct sockaddr_in local_addr;
	struct sockaddr_in remote_addr;
	int sin_size;
	int filename_size;
	int cur_byts_received;
	int bytes_received;
	int total_bytes;
	unsigned long filedata_size;

	sock_fd  = socket(AF_INET,SOCK_STREAM,0);
	

}
