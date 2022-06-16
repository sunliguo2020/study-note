#include<stdio.h>

int main()
{
	struct student
	{
		int  number;
		char name[20];
		char sex;
		int  age;
		char addr[30];
	};
	struct student s[3] = { {10000,"Zhang",'m',21,"Shang Hai"},
		                {10001,"Li",'f',20,"Bei Jing"}, 
	                        {10002,"Liu",'m',22,"Guang Dong"} };
	struct student *p; 
	for(p=s; p<s+3; p++)
		printf("%d,%s,%c,%d,%s\n",p->number,p->name,p->sex,p->age,p->addr); 

	return 0;
}
