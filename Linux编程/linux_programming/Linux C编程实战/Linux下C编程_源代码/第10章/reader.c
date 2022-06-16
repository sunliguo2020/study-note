#include "sharemem.h"

int main()
{
	int	semid, shmid;
	char	*shmaddr;
	
	if ((shmid = createshm(".", 'm', SHM_SIZE)) == -1)
	{
		exit (1);
	}
	
	if((shmaddr = shmat (shmid, (char *)0, 0)) == (char *)-1)
	{
		perror ("attach shared memory error!\n");
		exit (1);
	}
	
	if((semid = opensem("." ,'s')) == -1)
	{
		exit (1);
	}
	
	while(1)
	{
		printf("reader: ");
		wait_sem(semid,0);		/* �ȴ��ź�ֵΪ1 */
		sem_p(semid,0);			/* P���� */
		
		printf("%s\n", shmaddr);
		sleep(10);			/* ʹwriter��������״̬ */
		
		sem_v(semid,0);			/* V���� */
		sleep(10);			/* �ȴ�writer����д���� */
	}
}
