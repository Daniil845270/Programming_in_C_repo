#include <stdio.h>
#define OPTIONS 3
#define NonIntegerInput (scanf("%i", &cook_time) != 1)

int NumPresses(int seconds);

int main(void)
{
    printf("Type the number required (in seconds)\n");

    int cook_time;
    if NonIntegerInput
    {
        printf("Invalid input\n");
        return 0;
    }

    int presses = NumPresses(cook_time);

    printf("Number of button presses = %i\n", presses);

    return 0;
}


//i can potentially create a failsafe for negative numebrs, buuuuut liiiike
int NumPresses(int seconds)
{
    int cook_options[OPTIONS] = {600, 60, 10};
    int presses = 0;
    for (int i = 0; i < OPTIONS; i++)
    {
        while (seconds >= cook_options[i])
        {
            seconds -= cook_options[i];
            presses++;
        }
    }
    if (seconds > 0)
    {
        presses++;
    }
    return presses;
}