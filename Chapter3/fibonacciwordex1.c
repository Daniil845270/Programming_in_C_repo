#include "rot18.h"
#define BIG_NUM 1000000 

bool fibword_subs(bool fibonacci[], int digit);
int test(bool fibonacci[]);

int main(void)
{
    int digit;
    printf("Which digit of the sequence do you want to see?\n");
    if ((scanf("%i", &digit) != 1))
    {
        printf("That's not a valid number\n");
        return -1;
    }
    
    bool fibonacci[BIG_NUM] = {false};
    bool ans = fibword_subs(fibonacci, digit);
    printf("\n%i\n", ans);
    test(fibonacci);
    
    return 0;
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
    return fibonacci[iter];
}

int test(bool fibonacci[])
{
	assert(fibonacci[0] == 0);
	assert(fibonacci[1] == 1);
	assert(fibonacci[2] == 0);
	assert(fibonacci[3] == 0);
	assert(fibonacci[4] == 1);
	assert(fibonacci[5] == 0);
	assert(fibonacci[6] == 1);
	assert(fibonacci[7] == 0);
	assert(fibonacci[8] == 0);
	assert(fibonacci[9] == 1);
	assert(fibonacci[10] == 0);
	assert(fibonacci[11] == 0);
	assert(fibonacci[12] == 1);
	assert(fibonacci[13] == 0);
	assert(fibonacci[14] == 1);
	
	return 0;
}
