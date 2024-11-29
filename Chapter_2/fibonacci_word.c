#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <assert.h>
#define PHI 1.61803398875

bool fibword_phi(int n);

long my_floor(float number);

int main(void)

{
	char* character;
	int digit;
	printf("Plese, enter what digit of the sequence you want to see: ");
	while (scanf("%i", &digit) != 1 || digit < 1)
	{
		scanf("%s", character);
		printf("\nPlese, enter a number above 0: ");
	}
	
	bool zero_or_one;
	zero_or_one = fibword_phi(digit);
	if (zero_or_one == true)
	{
		printf("1\n");
	}
	else
	{
		printf("0\n");
	}
	
	assert(fibword_phi(1) == false);
	assert(fibword_phi(2) == 1);
	assert(fibword_phi(3) == 0);
	assert(fibword_phi(4) == 0);
	assert(fibword_phi(5) == 1);
	assert(fibword_phi(6) == 0);
	assert(fibword_phi(7) == 1);
	assert(fibword_phi(8) == 0);
	assert(fibword_phi(9) == 0);
	assert(fibword_phi(10) == 1);
	assert(fibword_phi(11) == 0);
	assert(fibword_phi(12) == 0);
	assert(fibword_phi(13) == 1);
	assert(fibword_phi(14) == 0);
	assert(fibword_phi(15) == 1);
	
	return 0;
}

bool fibword_phi(int n)
{
	long answer = 2 + my_floor(n * PHI) - my_floor((n + 1) * PHI);
	
	return answer;
}


long my_floor(float number)
{
	long round_down =  number; //looks horrible, but does exacly what I want, i.e. cuts off everything past the floating point (at least I think it does that)
	return round_down;
}

