#include<string.h>
#include<stdio.h>
void my_printf(int i);

int main()
{
//  int i=3;
  char a,c;
  char *str;
  a='a';
  str="abc"
	"efg"
	"hij";
  c='\x64';
//my_printf(i);
printf("%c%s\n",a,str,c);


/* char astr[20];
strcpy(astr,"this is a cat\n");
printf(astr);

*/


return 0;

}

void my_printf(int i)
{
printf("This is a functinon test\n");
printf("helloworld!\n");
printf("This is my %d program!\n",i);
printf("OK?\n\n");


}
