#include <stdio.h>


// this program takes 3 numbers from the main program, adds them all up, dobles it
// and then adds 7.
int calcfunction(int iNum1, int iNum2, int iNum3)
{
	int i;
	i = (iNum1 + iNum2 + iNum3) * 2 + 7;
	return i;
}

int main(void)
{
	int a, b, c;
	printf("Input three integers: ");
	scanf("%i %i %i", &a, &b, &c);
	int outcome = calcfunction(a, b, c);
	printf("Twice the sum of integers plus 7 is %i!\n", outcome);
}
	



