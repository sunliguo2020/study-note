// ʾ�������źŴ������ݣ�������������
// ѡ��-d ��������ݵ����ݣ�ѡ��-s ��������͵��źţ�ѡ��-p ���Ŀ�Ľ���ID
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char ** argv)
{
	union sigval	value;
	int		signum = SIGTERM;	// Ĭ�Ϸ���SIGTERM
	pid_t		pid;
	int		i;

	/*��ʼ��*/
	value.sival_int = 0;	

	/*�������ĸ���*/
	if (argc != 3 && argc != 5 && argc != 7) {
		printf("./send_data_signo <-d data> <-s signum> [-p][data]\n");
		exit(1);
	}

	/*�������в����������źű�š�PID�Լ������ݵ�����*/
	for (i=1; i<argc; i++) {
		if (!strcmp(argv[i], "-d")) {
			value.sival_int = atoi(argv[i+1]);
			continue;
		}
		if (!strcmp(argv[i], "-s")) {
			signum = atoi(argv[i+1]);
			continue;
		}
		if (!strcmp(argv[i], "-p")) {
			pid = atoi(argv[i+1]);
			continue;
		}
	}

	/*����sigqueue��pid�����ź�signum����Я������value*/
	if (sigqueue(pid, signum, value) < 0) {
		perror("sigqueue");
		exit(1);
	}

	return 0;
}
