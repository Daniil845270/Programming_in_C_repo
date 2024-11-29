#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
#include <math.h>

int main(void)
{
	//create a time-tied seed
	srand(time(NULL));
	double target_number = rand();
	
	printf("%.2lf %.12lf\n", target_number, target_number / 10000000000);

	return 0;
}
