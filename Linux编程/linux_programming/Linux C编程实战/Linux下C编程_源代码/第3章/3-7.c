#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int main()
{
		int number, guess, i=8;
		
		srand(time(NULL));
		number = rand() % 100 + 1;
	
		printf("Please guess a number:\n");
		
		while(i > 0)
		{
			scanf("%d",&guess);
	
			if(guess == number)
			{
				printf("Wonderful,you are right!\n\n");
				return 0;
			}
			else if(guess > number)
			{
				printf("Sorry,your are wrong.");
				printf("too high\n");
			}
			else
			{
				printf("Sorry,your are wrong.");
				printf("too low\n");
			}
			i--;
		}

		printf("Game over!\n\n");
		return 0;
}
