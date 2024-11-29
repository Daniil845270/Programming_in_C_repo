#include <stdio.h>
#include <math.h>

int main(void)
{
	int lower_num, upper_num, ans_num, ans_denom;
	double accuracy = 10, e_est = 2.718281828459045, e_calc;
	for (int denom = 1; denom < 100000; denom++)
	{
		lower_num = denom * 2 + 1; upper_num = denom * 3;
		
		double den = denom, pos_diff;
		
		while(lower_num < upper_num)
		{
			double lower = lower_num;
			
			e_calc = lower / den;
			
			pos_diff = fabs(e_calc - e_est);
			
			if (pos_diff < accuracy)
			{
				accuracy = pos_diff;
				// e_est = e_calc;
				ans_num = lower_num;
				ans_denom = denom;
				//printf("%i/%i = %lf\n", ans_num, ans_denom, e_calc);
				printf("%lf %lf\n", pos_diff, accuracy);
			}
			
			lower_num++;
			//printf("%Lf %lf\n", pos_diff, accuracy);
			//printf("count");
			
		}
	}
	
	printf("%i/%i = %lf\n", ans_num, ans_denom);
	
	return 0;
}
