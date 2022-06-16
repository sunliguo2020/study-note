#include <stdio.h>
#include <string.h>
#include <pthread.h>

pthread_key_t key;

void destructor (char * str)
{
	printf ("thread %d ends, param = %s\n", pthread_self(), str);
	free (str);
	str = NULL;
}
void * thread1(void *arg)
{
	char *selfstr = (char *) malloc(20);

	memset (selfstr, 0, 20);
	strcpy (selfstr, "this is thread1");
	printf ("thread %d is running\n", pthread_self());
	pthread_setspecific (key, (void *) selfstr);
	sleep (3);
	printf ("thread %d returns %s\n", pthread_self(), pthread_getspecific(key));
	sleep (4);
}

void * thread2(void *arg)
{

	char * selfstr = (char *)malloc(20);

	memset (selfstr,0,20);
	strcpy (selfstr, "this is thread2");
	printf ("thread %d is running\n", pthread_self());
	pthread_setspecific (key, (void *) selfstr);
	sleep (1);
	printf ("thread %d returns %s\n", pthread_self(), pthread_getspecific(key));
	sleep (6);
}

int main(void)
{
	pthread_t thid1, thid2;

	printf ("main thread begins running\n");
	pthread_key_create (&key, (void *)destructor);
	pthread_create (&thid1, NULL, thread1, NULL);
	pthread_create (&thid2, NULL, thread2, NULL);
	sleep (8);
	pthread_key_delete (key);
 	printf ("main thread exit\n");
	return 0;
}
