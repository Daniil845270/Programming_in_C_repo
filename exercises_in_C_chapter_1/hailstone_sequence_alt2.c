#include<stdio.h>

int find_largest_hailstone(long long hailstorm_number);

int main(void)
{	
	long long i_largest_hailstone, largest_hailstone_ever = 0, initial_number_answer = 0;
	
	for (long long i = 1; i <= 10000000; i++)
	{
		i_largest_hailstone = find_largest_hailstone(i);
		if (i_largest_hailstone > largest_hailstone_ever)
		{
			largest_hailstone_ever = i_largest_hailstone;
			initial_number_answer = i;
		}
	}
	printf("%lld\n", initial_number_answer);
}
			
int find_largest_hailstone(long long hailstorm_number)
{
	long long largest_hailstone = 0;
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
		if (hailstorm_number > largest_hailstone)
		{
		largest_hailstone = hailstorm_number;
		}
	}
	return largest_hailstone;
}

// is the answer to the question 9,807,643
//2,147,353,792?
