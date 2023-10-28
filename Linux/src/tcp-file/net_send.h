#ifndef NET_SEND_H
#define NET_SEND_H

#define MAX_FILE_NAME 255
#define BUF_SIZE 512
#define FD_NOT_SET 0
#define FAILED -1
#define SUCCESS 0

typedef struct net_file{
	int file_name_size;
	unsigned long file_data_size;
	int fd;
	int fd_stat;
	char file_to_send[MAX_FILE_NAME];
	char buf[BUF_SIZE];
}netfile_t;

int open_net_file(netfile_t *netfile,char *filename);
int send_net_file(netfile_t *netfile,char *server_ip,short server_port);
void close_net_file(netfile_t *netfile);
#endif /* net_send_h*/
