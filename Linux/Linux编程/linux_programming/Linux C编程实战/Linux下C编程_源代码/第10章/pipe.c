#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

/*���ܵ�*/
void read_from_pipe (int fd)
{
        char message[100];
        read (fd,message,100);
        printf("read from pipe:%s",message);
}

/*д�ܵ�*/
void write_to_pipe (int fd)
{
        char *message = "Hello, pipe!\n";
        write (fd, message,strlen(message)+1);
}

int main(void)
{
        int     fd[2];
        pid_t   pid;
        int     stat_val;

        if (pipe (fd))
        {
                printf ("create pipe failed!\n");
                exit (1);
        }

        pid = fork();
        switch (pid)
        {
                case -1:
                        printf ("fork error!\n");
                        exit (1);
                case 0:
                        /*�ӽ��̹ر�fd1*/
                        close (fd[1]);
                        read_from_pipe (fd[0]);
                        exit (0);
                default:
                        /*�����̹ر�fd0*/
                        close (fd[0]);
                        write_to_pipe (fd[1]);
                        wait (&stat_val);
                        exit (0);
        }

        return 0;
}
