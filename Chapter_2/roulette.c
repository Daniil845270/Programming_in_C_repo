#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>

int trhown_ball(void);
int black_bet(int num);
int red_bet(int num)

int main(void)
{
	int ball_number = trhown_ball();
	printf("%i\n", ball_number);

	printf("\nPlease, choose a number between 0 and 35\n");





    return 0;
}

int trhown_ball(void)

{
	//create a time-tied seed from 0 to 35
	srand(time(NULL));
	int rand_num = rand() % 36;
	return rand_num;
}

int black_bet(int num)
{
	
}

int red_bet(int num)
{

}