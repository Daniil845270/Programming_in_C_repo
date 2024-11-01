#include "rot18.h"
#define BIG_NUM 1000000 
//#define PHI 1.61803398875
#define PHI 1.618
bool fibword_subs(bool fibonacci[], int digit);
int test(bool fibonacci[]);
bool fibword_phi(int n);
long my_floor(float number);
bool fibonacci_old(int digit);
bool fibonacci_new(int digit);

int main(void)
{
    int same_digit = 1;
    /*
    printf("Which digit do you want to test?\n");
    if ((scanf("%i", &same_digit) != 1))
    {
        printf("That's not a valid number\n");
        return -1;
    } 
    */   
    int cnt = 0;
    
    while (fibonacci_new(same_digit) == fibonacci_old(same_digit))
    {
        //printf("Was here \n");
        cnt++;
        same_digit++;
    }
    
    printf("%i \n", cnt);
    
    return 0;
   
}

bool fibonacci_new(int digit)
{
    bool fibonacci[BIG_NUM] = {false};
    bool ans = fibword_subs(fibonacci, digit);
    //printf("\n%i\n", ans);
    //test(fibonacci);
    
    return ans;
}

bool fibonacci_old(int digit)
{
	bool zero_or_one;
	zero_or_one = fibword_phi(digit);
	//printf("\n%i\n", zero_or_one);
	return zero_or_one;
}

bool fibword_phi(int n)
{
	long answer = 2 + my_floor(n * PHI) - my_floor((n + 1) * PHI);
	
	return answer;
}

long my_floor(float number)
{
	long round_down =  number;
	return round_down;
}

bool fibword_subs(bool fibonacci[], int digit)
{
    int iter = 0;
    int cnt = 1;
    while (iter < digit)
    {
        if (fibonacci[iter] == false)
        {
            fibonacci[cnt] = true; 
            fibonacci[(cnt + 1)] = false;
            cnt += 2;
        }
        else
        {
            fibonacci[cnt] = false;
            cnt++;
        }
        iter++;
    }
    return fibonacci[(iter)];
}
