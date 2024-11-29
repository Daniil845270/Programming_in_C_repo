#include<stdio.h>

int main(void)
{
	// here I just ask the user to state how many numbers he wants to enter
	printf("How many odd numbers do you wish to enter?\n");
	int numbers_cnt;
	scanf("%i", &numbers_cnt);
	// need to check the entered number makes sense for the program to start
	while (numbers_cnt < 2){
		printf("You will need to enter at least 2 numbers. Try again\n");
		scanf("%i", &numbers_cnt);
		}
	int max_num;
	for (int i = 0; i < numbers_cnt; i++){
		// i need to check that the input that the user entered is actually a natural number and that it is an odd number here. How to protect the user from entering decimal numbers and letters? 

		int your_number;
		scanf("%i", &your_number);
		while (your_number % 2 == 0){
			printf("Number %i is even. Enter an odd number\n", your_number);
			scanf("%i", &your_number);
			}

		// So after the user enters the correct type of a number, then we can do the data analysis

		
		if (i == 0){
			max_num = your_number;
			}
		else {
			if (your_number > max_num){
				max_num = your_number;
				}
			}
		}
	printf("The max number is %i\n", max_num);
}








