#include<stdio.h>

int main(void)
{
	printf("How many numbers do you wish to enter?\n");
	int numbers_cnt;
	scanf("%i", &numbers_cnt);
	
	if (numbers_cnt == 1){
		printf("Enter your number\n");
		float your_number;
		scanf("%f", &your_number);
		printf("Maximum value: %f\n", your_number);
		}

	else if (numbers_cnt >= 1){
		printf("Please, enter the fisrt number\n");
		float max_number;
		scanf("%f", &max_number);
		
		float number_iteration;
		for (int i = 1; i < numbers_cnt; i++){
			printf("Enter number %i\n", i + 1);
			scanf("%f", &number_iteration);
			if (number_iteration > max_number){
				max_number = number_iteration;
				}
		printf("Maximum value: %f\n", max_number);

		}
	
	//to make it perfect need to make it a while loop in the beginning
	else {
		printf("Plase, enter at least one number\n");
		}
}
	
	
























