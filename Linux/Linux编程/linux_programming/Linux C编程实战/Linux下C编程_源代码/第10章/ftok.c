#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
	
int main( void )
{
	int i;
	for ( i = 1; i <= 5; i++ )
		printf( "key[%d] =  %ul \n", i, ftok( ".", i) );
 	exit(0);
}
	