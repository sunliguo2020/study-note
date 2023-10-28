#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(int arg, char *argv[],char ** environ)
{
	int	fd[2];
	pid_t	pid;
	int	stat_val;
	
	if (arg < 2)
	{
		printf("wrong parameters \n");
		exit(0);
	}
	if (pipe(fd))
	{
		perror("pipe failed");
		exit(1);
	}

	pid = fork();
	switch (pid)
	{
		case -1:
			perror ("fork failed!\n");
			exit(1);
		case 0:
			close (0);
			dup (fd[0]);
			execve ("ctrlprocess",(void *)argv,environ);
			exit (0);
		default:
			close(fd[0]);
			/*将命令行第一个参数写进管道*/
			write (fd[1], argv[1], strlen(argv[1]));
			break;
	}
	wait (&stat_val);
	exit (0);
}
