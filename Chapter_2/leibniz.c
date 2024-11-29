#include <stdio.h>
#include <math.h>

double pi_calculations(int cnt);

int main(void)
{
	printf("How long do you want your addition and subtraction to be?\n Enter a number of set values: ");
	int lenght; // of the substraction/addition chain
	scanf("%i", &lenght);
		
	double answer = pi_calculations(lenght);

	printf("The pi approximation is %.8lf\n", answer);

	return 0;
}

double pi_calculations(int cnt)
{
	double pi_approximaiton = 4;
	double divider = 3;

	for (int i = 0; i < cnt; i++, divider += 2)
	{
		if (i % 2 == 0) 
		{
			pi_approximaiton = pi_approximaiton - (4 / divider);
			//printf("Option1 %lf ", divider);
		}
		else 
		{
			pi_approximaiton = pi_approximaiton + (4 / divider);
			//printf("Option2 %lf ", divider);
		}
		//printf("%lf\n", pi_approximaiton);
	}
	
	return pi_approximaiton;
}
