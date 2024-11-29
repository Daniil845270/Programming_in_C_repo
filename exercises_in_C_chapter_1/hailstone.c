#include<stdio.h>

int main(void)
{
	printf("Enter your first hailstorm number\n");
		
	int hailstorm_number;
	scanf("%i", &hailstorm_number);
	while (hailstorm_number != 1)
	{
		if (hailstorm_number % 2 == 0)
		{
		hailstorm_number /= 2;
		}
		else
		{
		hailstorm_number = 3 * hailstorm_number + 1;
		}	
		printf("%i\n", hailstorm_number);
	}
}
