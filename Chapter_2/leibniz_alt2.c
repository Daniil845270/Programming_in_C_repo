// this version of the program in theory works but it is extremely unoptimised, because we compute the new approximation of the pi number from anew. Therefore, need to optimise this program to the point that it works -> need to completely rewrite it 


// The answer that I got is 17727292


#include <stdio.h>
#include <math.h>

double pi_calc_alt(double pi_approximaiton, int lenght, double divider);

int main(void)
{
	double user_pi = 3.1415927;
	
	int lenght = 0; // of the leibniz pi equation
	double difference, pi_approximaiton = 4, divider = 3, pi_est;
	
	do 
	{
		pi_approximaiton = pi_calc_alt(pi_approximaiton, lenght, divider);
		difference =  user_pi - pi_approximaiton;
		
		printf("%i , %lf, %.8lf\n", lenght, difference, pi_approximaiton);
		lenght++;
		divider += 2;
		
	} while (difference > 0.00000001 || difference < -0.00000001);
	
	printf("%i\n", lenght);

	return 0;
}



double pi_calc_alt(double pi_approximaiton, int lenght, double divider)
{
	if (lenght % 2 == 0)
	{
		pi_approximaiton = pi_approximaiton - (4 / divider);
	}
	else 
	{
		pi_approximaiton = pi_approximaiton + (4 / divider);
	}
	return pi_approximaiton;
}


// Pi is 3.1415927 to 7 decimal places 
// how to compare 2 floats to 7 decimal places?


