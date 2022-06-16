#include<stdio.h>

int a = 3;

void f( )
{
    int a = 1,i;
    printf("%d\n",a);

    for(i=0;i<1;i++)
    {
        int a = 2;
        printf("%d\n",a);
    }
}

int main( )
{
    f( );
    printf("%d\n",a);
}
