#include <stdio.h>
int main()
{
  int a;
  a=10;
  printf("Hello,World!\n");
  printf("print a:%d\n",a);
  printf("print a:%5d#%-3d#%d\n",a,a,a); //#为分隔符
  float b = 3.1416;

  printf("print b float: %f %.3f\n",b,b);
  printf("print b exp:%e %E\n",b,b);

  char c[]="HELLO,WORLD!,STATIC STRING";
  printf("print c:%s\n",c);
  return 0; 
}
