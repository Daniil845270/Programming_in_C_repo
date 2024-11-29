// this version of the program in theory works but it is extremely unoptimised, because we compute the new approximation of the pi number from anew. Therefore, need to optimise this program to the point that it works -> need to completely rewrite it 


#include <stdio.h>
#include <math.h>

double pi_calc(int cnt);

int main(void)
{
	// printf("How accurate do you want to calculate pi?\nEnter a pi number: ");
	
	double user_pi = 3.1415927;
	
	/*
	
	char character; //for the scanf test 
	while (scanf("%lf", &user_pi) != 1) // just a user input check
	{
		printf("Please, enter pi in a decimal form\n");
		scanf("%c", &character);
	}
	*/
	
	int lenght = 0; // of the leibniz pi equation
	double difference;
	
	do 
	{
		difference =  user_pi - pi_calc(lenght);
		
		printf("%i , %lf, %.8lf\n", lenght, difference, pi_calc(lenght));
		lenght++;
		
	} while (difference > 0.00000001 || difference < -0.00000001);
	
	printf("%i\n", lenght);

	return 0;
}





double pi_calc(int cnt)
{
	double pi_approximaiton = 4;
	double divider = 3;

	for (int i = 0; i < cnt; i++, divider += 2)
	{
		if (i % 2 == 0) 
		{
			pi_approximaiton = pi_approximaiton - (4 / divider);
		}
		else 
		{
			pi_approximaiton = pi_approximaiton + (4 / divider);
		}
	}
	
	return pi_approximaiton;
}

// Pi is 3.1415927 to 7 decimal places 
// how to compare 2 floats to 7 decimal places?


