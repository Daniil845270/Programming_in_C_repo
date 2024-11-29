#include<stdio.h>
#define A 9
#define C 5
#define M 11
#define LOOPS 1000

int main(void)
{
	int seed = C % M, cnt = 1;
	int iteration = (A*seed + C) % M;
	while (seed != iteration){
		iteration = (A*iteration + C) % M;
		cnt++;
	}
	printf("%i\n", cnt);

}


// have to period (how many nubers are in a seq before repeat) 







/*int main(void)
{

	int seed = 0;
	for (int i = 0; i < LOOPS; i++){
		seed = (A*seed + C) % M;
		printf("%i\n", seed);
		}

}*/


// have to period (how many nubers are in a seq before repeat) 
