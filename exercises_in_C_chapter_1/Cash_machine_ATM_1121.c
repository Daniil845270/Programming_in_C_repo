#include<stdio.h>

int count_less(int money);

int count_more(int money);

int main(void)


// I will need to create a while loop before the user enters a %20 number 
{
	printf("How much money in GBP would you like?\n");

	int money_withdrawal;
	/* scanf("%i", &money_withdrawal);*/

	while (scanf("%i", &money_withdrawal) != 1){
		printf("Please, enter a number, not a letter\n");
		return 1; // how to make the text check not crash the program and not fall into an infinite loop?
		scanf("%i", &money_withdrawal);
	}

	/*if (scanf("%i", &money_withdrawal) != 1){
		printf("Please, enter a number, not a letter\n");
		return 1;
	}*/
	

	while (money_withdrawal % 20 != 0){
	printf("I have only £20 banknotes\n");
	printf("I can give you %i or %i. Please, enter enter a different amount.\n", count_less(money_withdrawal), count_more(money_withdrawal));
	scanf("%i", &money_withdrawal);
	}
	printf("OK, dispensing £%i\n", money_withdrawal);
	
}

int count_less(int money)
{
	int less_money = money - (money % 20);
	return less_money;
}

int count_more(int money)

{
	int more_money = money + (20 - (money % 20));
	return more_money;
} 


