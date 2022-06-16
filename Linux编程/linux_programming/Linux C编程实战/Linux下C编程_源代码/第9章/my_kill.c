// 为简化实现，本程序只支持按信号的编号而不是信号名发送信号
// 感兴趣的读者可以按照自己的系统下的signal.h增加名字到编号的映射表
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/types.h>

int main(int argc, char ** argv)
{
	int	i, j;
	int	signum = SIGTERM;	// 默认发送SIGTERM
	pid_t	pid;

	/*首先检查参数个数*/;
	if (argc != 2 && argc != 4) {
		printf("Usage: ./my_kill <-s signum> [PID]\n");
		exit(0);
	}
	
	/*从命令行参数解析出信号编号*/
	for (i=1; i<argc; i++) {
		if (!strcmp(argv[i], "-s")) {
			signum = atoi(argv[i+1]);
			break;
		}
	}

	/*解析出进程号*/
	if (argc == 2) {
		pid = atoi(argv[1]);
	} else {
		for (j=1; j<argc; j++) {
			if (j != i && j != i+1) {
				pid = atoi(argv[j]);
				break;
			}
		}
	}

	if (kill(pid, signum) < 0) {
		perror("kill");
		exit(1);
	}

	return 0;
} 
