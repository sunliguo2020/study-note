// 端口扫描程序，只支持扫描TCP端口
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

// 定义一个端口区间信息
typedef struct _port_segment {
	struct in_addr		dest_ip;	// 目标IP
	unsigned short int	min_port;	// 起始端口
	unsigned short int	max_port;	// 最大端口
} port_segment;

/*自定义的错误处理函数*/
void my_err(const char * err_string, int line)
{
	fprintf(stderr, "line:%d  ", line);
	perror(err_string);
	exit(1);
}

/*
 * 描  述：扫描某一IP地址上的某一个端口的函数
 * 返回值： -1  	出错
 *	    0  	目标端口未打开
 *	    1	目标端口已打开
 */
int do_scan(struct sockaddr_in serv_addr)
{
	int		conn_fd;
	int		ret;
	
	// 创建一个TCP套接字
	conn_fd = socket(AF_INET, SOCK_STREAM,0);
	if (conn_fd < 0) {
		my_err("socket", __LINE__);
	}
	
	// 向服务器端发送连接请求
	if ( (ret = connect(conn_fd, (struct sockaddr *)&serv_addr, 
				sizeof (struct sockaddr))) < 0 ) {
		if (errno == ECONNREFUSED) {	// 目标端口未打开
			close(conn_fd);
			return 0;
		} else {	// 其他错误
			close(conn_fd);
			return -1;
		}
	} else if (ret == 0){
		printf("port %d found in %s\n", ntohs(serv_addr.sin_port), 
				inet_ntoa(serv_addr.sin_addr));
		close(conn_fd);
		return 1;
	}
	
	return -1;	// 实际执行不到这里，只是为了消除编译程序时产生的警告
}

// 执行扫描的线程，扫描某一区间的端口
void * scaner(void *arg)
{
	unsigned short int	i;
	struct sockaddr_in	serv_addr;
	port_segment		portinfo;	  // 端口信息
	
	// 读取端口区间信息
	memcpy(&portinfo, arg, sizeof(struct _port_segment));
	
	// 初始化服务器端地址结构
	memset(&serv_addr, 0, sizeof (struct sockaddr_in));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = portinfo.dest_ip.s_addr;
	
	for (i=portinfo.min_port; i<=portinfo.max_port; i++) {
		serv_addr.sin_port = htons(i);
		if (do_scan(serv_addr) < 0) {
			continue;	// 出错则退出进程
		}
	}
	return NULL;
}

/*
 * 命令行参数：-m 最大端口， -a 目标主机的IP地址,  -n 最大线程数
 */
int main(int argc, char **argv)
{
	pthread_t*	thread;			// 指向所有的线程ID
	int		max_port;		// 最大端口号
	int		thread_num;		// 最大线程数
	int		seg_len;		// 端口区间长度
	struct in_addr	dest_ip;		// 目标主机IP
	int		i;

	// 检查参数个数
	if (argc != 7) {
		printf("Usage: [-m] [max_port] [-a] [serv_address] [-n] [thread_number]\n");
		exit(1);
	}

	// 解析命令行参数
	for (i=1; i<argc; i++) {
		if (strcmp("-m", argv[i]) == 0) {
			max_port = atoi(argv[i+1]);   // 将字符串转化为对应的整数
			if (max_port < 0 || max_port > 65535) {
				printf("Usage:invalid max dest port\n");
				exit(1);
			}
			continue;
		}

		if (strcmp("-a", argv[i]) == 0) {
			if (inet_aton(argv[i+1], &dest_ip) == 0) {
				printf("Usage:invalid dest ip address\n");
				exit(1);
			}
			continue;
		}

		if (strcmp("-n", argv[i]) == 0) {
			thread_num = atoi(argv[i+1]);
			if (thread_num <= 0) {
				printf("Usage:invalid thread_number\n");
				exit(1);
			}
			continue;
		}
	}
	// 如果输入的最大端口号小于线程数，则将线程数设为最大端口号
	if (max_port < thread_num) {
		thread_num = max_port;
	}

	seg_len = max_port / thread_num;
	if ( (max_port%thread_num) != 0 ) {
		thread_num += 1;
	}
	// 分配存储所有线程ID的内存空间
	thread = (pthread_t*)malloc(thread_num*sizeof(pthread_t));

	// 创建线程，根据最大端口号和线程数分配每个线程扫描的端口区间
	for (i=0; i<thread_num; i++) {
		port_segment	portinfo;	
		portinfo.dest_ip = dest_ip;
		portinfo.min_port = i*seg_len + 1;
		if (i == thread_num-1) {
			portinfo.max_port = max_port;
		} else {
			portinfo.max_port = portinfo.min_port + seg_len - 1;
		}
		// 创建线程
		if (pthread_create(&thread[i], NULL, scaner, (void *)&portinfo) != 0) {
			my_err("pthread_create", __LINE__);
		}
		// 主线程等待子线程结束
		pthread_join(thread[i],NULL);
	}
	
	return 0;
}
