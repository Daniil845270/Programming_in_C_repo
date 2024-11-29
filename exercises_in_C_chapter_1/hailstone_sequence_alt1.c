#include<stdio.h>

int count_hailstone_seq_length(long long hailstorm_number);

int main(void)
{	
	long long answer = 0, i_hailstone_seq_len, longest_hailstone_seq_len = 0;
	for (long long i = 1; i <= 10000000; i++)
	{
		i_hailstone_seq_len = count_hailstone_seq_length(i);
		if (i_hailstone_seq_len > longest_hailstone_seq_len)
		{
			longest_hailstone_seq_len = i_hailstone_seq_len;
			answer = i;
		}
	}
	printf("%lld\n", answer);
	return 0;
}
			
int count_hailstone_seq_length(long long hailstorm_number)
{
	long long cnt = 0;
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
		cnt++;
	}
	cnt++; //because we also need to count the initial number in
	return cnt;
}

// need also to account for stupid user entries like 0, -1, hello and hello world


// is the answr actually 8,400,511?










	/* printf("Enter your first hailstorm number\n");
		
	long long hailstorm_number;
	scanf("%lld", &hailstorm_number);
	long long answer = count_hailstone_sequence_length(hailstorm_number);
	printf("%lld\n", answer); */
