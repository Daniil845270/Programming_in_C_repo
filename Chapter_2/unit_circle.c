#include <stdio.h>
#include <math.h>

// write a program that provides evidence that sin square and cos square is equal to 1

int main(void)
{
	printf("Please, enter your sin and cos values separated by a simple space:  ");	
	
	double sin, cos;
	scanf("%lf %lf", &sin, &cos);

	double answer = pow(sin, 2) + pow(cos, 2);
	printf("sin squared plus cos squared equals to %.2lf \n", answer);

	return 0;
}
