#include "rot18.h"
int int_pow(int number, int power);

int main(void)
{
    int number = 10, power = 4;
    printf("%i\n", int_pow(number, power));
    return 0;
}


int int_pow(int number, int power)
{
    int raised_number = number;
    if (power < 0){
        printf("Invalid power function input");
        return -1;
    }
    int cycles = 0;
    if (power == cycles){
        return 1;
    }
    for (; cycles < power - 1; cycles++){
        raised_number *= number;
    }
    return raised_number;
}