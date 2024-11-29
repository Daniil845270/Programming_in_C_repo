

/*
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>


int game_options(int target_number);

int check_nonint_input(int input);

int main(void)
{
	//create a time-tied seed and generate a number to guess
	srand(time(NULL));
	int target_number = rand() % 1000 + 1;
	printf("%i\n", target_number); // delete this line if want to play for real 
	
	

	//create an actual function that would contain the game options
	game_options(target_number);


	return 0;
}

int game_options(int target_number)
{
	int guess_number, attempts;
	for (int cnt = 0; cnt < 10; cnt++)
	{
		printf("\nYour guess is: ");
		
		if (check_nonint_input(guess_number) == 16)
		{
			printf("\nPlease, enter an integer\n");
		}
		else if (guess_number == target_number)
		{
			printf("\nYou have won! Congratulations!\n");
			cnt = 10;
			return 2; // I put the return statement so that the program would stop
		}
		else if (guess_number < 0 || guess_number > 1000)
		{
			printf("\nYour guess number should be between 1 and a 1000. Try again\n");
			cnt--;
		}
		else if (guess_number > target_number)
		{
			printf("\nYour number is too high. Try again\n");
		}
		else
		{
			printf("\nYour number is too low. Try again\n");
		}
		attempts = 9 - cnt;
		printf("You have %i attemps\n", attempts);
	}
	printf("\nBad luck. Try again next time!\n");
	return 0;
}


int check_nonint_input(int input)
{
	if (scanf("%i", &input) != 1)
	{
		//scanf("%i", &guess_number);
		return 16; //16 and 17 are chosen by random. It's bad, but i need it to work somehow at least
		//cnt--;
	}
	else if (scanf("%i", &input) == 1)
	{
		return 17;
	} 
	return 0;
}
*/





		/* while (scanf("%i", &guess_number) != 1) 
		{
			printf("Please, enter an integer");
		} */


		/*scanf("%i", &guess_number);*/







#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>

int main(void)
{
	//create a time-tied seed
	srand(time(NULL));
	int target_number = rand() % 1000 + 1;
	printf("%i\n", target_number);

	//create a while loop that will break if either the player guesses the number or he runs out of the ten trials
	int guess_number, attempts = 10;
	char character;
	for (int cnt = 0; cnt < 10; cnt++){
		printf("\nYour guess is: ");
	
		if (scanf("%i", &guess_number) != 1){
			printf("Please, enter an integer\n");
			//return 1;
			//cnt--;
			attempts += 1;

			scanf("%c", &character);
		} 
		else if (guess_number == target_number){
			printf("\nYou have won! Congratulations!\n");
			cnt = 10;
			}
		else if (guess_number < 0 || guess_number > 1000){
			printf("\nYour guess number should be between 1 and a 1000. Try again\n");
			attempts += 1;
			cnt--;
			}
		else if (guess_number > target_number){
			printf("\nYour number is too high. Try again\n");
			}
		else{
			printf("\nYour number is too low. Try again\n");
			}
		attempts -= 1;
		printf("You have %i attemps\n", attempts);
	if (attempts == 0){
		printf("\nBad luck. Try again next time!\n");
		}
	}
	return 0;
}


		/* while (scanf("%i", &guess_number) != 1) 
		{
			printf("Please, enter an integer");
		} */


		/*scanf("%i", &guess_number);*/
