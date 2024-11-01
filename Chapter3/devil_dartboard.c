#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#define SECTIONS 20
#define FROM0SEC 19
#define SND2LAST 18
#define THRD2LAST 17
#define BIG_NUM 500000000

void init_dartboard(int dartboard[]);
void print_dartboard(int dartboard[]);
int shuffle(int dartboard[], int dartboard_ans[]);
int sum_squared(int dartboard[]);
void shufflet_seed(void);
void record_dartboard(int dartboard[], int dartboard_ans[]);

int main(void)
{
    shufflet_seed();

    int sum;

    int dartboard[SECTIONS]; init_dartboard(dartboard);
    int dartboard_ans[SECTIONS]; init_dartboard(dartboard_ans);

    sum = shuffle(dartboard, dartboard_ans);
    printf("The lowest score it came up with is %i\n", sum);
    printf("With the board configuration: "); print_dartboard(dartboard_ans);

    return 0;
}

int shuffle(int dartboard[], int dartboard_ans[])
{
    int sum = sum_squared(dartboard);
    int itr_sum;
    int rand_dart1; int rand_dart2; int buffer_dart;
    for (int i = 0; i < BIG_NUM; i++)
    {
        rand_dart1 = rand() % SECTIONS; rand_dart2 = rand() % SECTIONS;
        buffer_dart = dartboard[rand_dart1]; 
        dartboard[rand_dart1] = dartboard[rand_dart2]; 
        dartboard[rand_dart2] = buffer_dart;

        itr_sum = sum_squared(dartboard);
        if (itr_sum < sum)
        {
            sum = itr_sum;
            record_dartboard(dartboard, dartboard_ans);
        }
    }
    return sum;
}
void record_dartboard(int dartboard[], int dartboard_ans[])
{
    for (int item = 0; item < SECTIONS; item++)
    {
        dartboard_ans[item] = dartboard[item];
    } 
}

void shufflet_seed(void)
{
	srand(time(NULL));
}

int sum_squared(int dartboard[])
{
    int sum = 0, item = 0;
    int curr = item, oneplus = item + 1, twoplus = item + 2;

    while(item <= THRD2LAST)
    {
        sum += pow((dartboard[curr] + dartboard[oneplus] + dartboard[twoplus]), 2);
        //printf("%i %i %i \n", curr, oneplus, twoplus);
        item++; curr++; oneplus++; twoplus++;
    }

    sum += pow((dartboard[18] + dartboard[19] + dartboard[0]), 2);
    sum += pow((dartboard[19] + dartboard[0] + dartboard[1]), 2);

    return sum;
}

void init_dartboard(int dartboard[])
{
    for (int item = 0; item < SECTIONS; item++)
    {
        dartboard[item] = item + 1;
    }

}

void print_dartboard(int dartboard[])
{
    for (int item = 0; item < SECTIONS; item++)
    {
        printf("%i ", dartboard[item]);
    }
    printf("\n");
}  
