#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#define FIFO_NAME	"myfifo"
#define BUF_SIZE	1024

int main(void)
{
	int     fd;
	char	buf[BUF_SIZE] = "Hello procwrite, I come from process named procread!";

	umask(0);
	if (mkfifo (FIFO_NAME, S_IFIFO | 0666) == -1)
	{
		perror ("mkfifo error!");
		exit (1);
	}

	if((fd = open (FIFO_NAME, O_WRONLY) ) == -1)/*��д��ʽ��FIFO*/
	{
		perror ("fopen error!");
		exit (1);
	}
	write (fd, buf, strlen(buf)+1); /*��FIFOд����*/

	close (fd);
	exit (0);
}
