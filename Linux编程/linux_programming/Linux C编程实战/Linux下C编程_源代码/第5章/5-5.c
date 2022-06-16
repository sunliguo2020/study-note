#include<stdio.h>

struct student
{
	int  number;
	char name[20];
	char sex;
	int  age;
	char addr[30];
};

void print_struct(struct student *p)
{
	p->age ++;
	printf("%d,%s,%c,%d,%s\n",p->number,p->name,p->sex,p->age,p->addr);
}

int main()
{

	struct student s[3] = { {10000,"Zhang",'m',21,"Shang Hai"},
		                {10001,"Li",'f',20,"Bei Jing"}, 
	                        {10002,"Liu",'m',22,"Guang Dong"} };
	printf("%d,%d,%d\n",s[0].age,s[1].age,s[2].age);
	struct student *p; 
	for(p=s; p<s+3; p++)
		print_struct(p);
	printf("%d,%d,%d\n",s[0].age,s[1].age,s[2].age);
	return 0;
}
