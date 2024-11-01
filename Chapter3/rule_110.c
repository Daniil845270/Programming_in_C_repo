#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
#include <string.h>

#define LENGTH 20
#define ARR_FIN_ITEM (LENGTH - 1)
#define ARR_SND2LAST (ARR_FIN_ITEM - 1) 

enum state {off, on};
typedef enum state state;

void shufflet_seed(void);
void fillup(int prev_line[], int new_line[]);
int rules(int prev_line[], int new_line[], int item);
void print(int new_line[]);
void cycle_lines(int prev_line[], int new_line[]);


int main(void)
{
    shufflet_seed();
    
    int prev_line[LENGTH] = {off, off, off, off, off, on, off, off, off, off, off, off, off, off, off, on, off, off, off, off};
    print(prev_line);
    int new_line[LENGTH];
    for (int i = 0; i < 30; i++)
    {
        fillup(prev_line, new_line);
        print(new_line);
        cycle_lines(prev_line, new_line);
    }

    return 0;
}

void shufflet_seed(void)
{
	srand(time(NULL));
}

void cycle_lines(int prev_line[], int new_line[])
{
    for (int item = 0; item < ARR_FIN_ITEM; item++)
    {
        prev_line[item] = new_line[item];
    }
    for (int item = 0; item < ARR_FIN_ITEM; item++) // strictly speaking, don't have to do that but it felt right
    {
        new_line[item] = off;
    }
    
}

void fillup(int prev_line[], int new_line[])
{
    new_line[0] = prev_line[0];
    new_line[ARR_FIN_ITEM] = prev_line[ARR_FIN_ITEM];
    for (int item = 1; item < ARR_SND2LAST; item++)
    {
        new_line[item] = rules(prev_line, new_line, item);
    }
}


int rules(int prev_line[], int new_line[], int item)
{
    int prev = item - 1, cur = item, next = item + 1;
    if ( (prev_line[prev] == on && prev_line[cur] == on  && prev_line[next] == off) 
    || (prev_line[prev] == on   && prev_line[cur] == off && prev_line[next] == on) 
    || (prev_line[prev] == off  && prev_line[cur] == on  && prev_line[next] == on)
    || (prev_line[prev] == off  && prev_line[cur] == on  && prev_line[next] == off) 
    || (prev_line[prev] == off  && prev_line[cur] == off && prev_line[next] == on) )
    {
        return on;
    }
    else 
    {
        return off;
    }
}

void print(int new_line[])
{
    for (int item = 0; item < ARR_FIN_ITEM; item++)
    {
        if (new_line[item] == on)
        {
            printf("%s  ", "on");
        }
        //printf("%i", new_line[item]);
        else
        {
            printf("%s ", "off");
        }
    }
    printf("\n");
}
