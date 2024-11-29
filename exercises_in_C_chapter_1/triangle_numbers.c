#include<stdio.h>

int main(void)
{
	printf("What triangular number would you like to see?\n");
	int triangular_number, initial_number = 0;
	scanf("%i", &triangular_number);
	for (int i = 1; i <= triangular_number; i++){
		initial_number += i;
		printf("%i\n", initial_number);
	}

// i could rewrite the program for the formula but literally I can't be asked, cos it's even easier
}
