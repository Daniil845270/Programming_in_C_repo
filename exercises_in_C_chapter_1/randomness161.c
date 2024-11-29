#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>

int main(void)
{
	int median = RAND_MAX / 2;

	int minus_cnt = 0, plus_cnt = 0, rand_iteration, difference;
	srand(time(NULL));
	for(int i = 0; i < 50000; i++){
		
		rand_iteration = rand();
		if (rand_iteration > median){
			plus_cnt++;
			}
		else if (rand_iteration < median){
			minus_cnt++;
			}		
		//when rand_iteration == median, we don't need to change the plus and minus 			counters, so we just need to print them again 
		difference = plus_cnt - minus_cnt;
		printf("%i\n", difference);
		}

}
