#include <stdio.h>

char *name[7] = { "Monday","Tuesday","Wednesday","Thursday",
   	               "Friday","Saturday","Sunday" };
char *message = "wrong input";

char *week(int day)
{
	if(day<0 || day>7)
		return message;
	else
		return name[day-1];
}

int main()
{
	int  day;
	char *p;

	printf("Input a number of a week:\n");
	scanf("%d",&day);

	p = week(day);
	printf("%s\n",p);
	return 0;
}
