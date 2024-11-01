#include "rot18.h"
#define BIGSTR 1000

void int2string(int i, char* str);
int int_pow(int number, int power);
int int_len(int i);
int num_iteration(int i, int j, int i_len);

int main(void)
{
   char s[BIGSTR];     
   int2string(0, s);
   assert(strcmp(s, "0")==0);
   int2string(10, s);
   assert(strcmp(s, "10")==0);
   int2string(99, s);
   assert(strcmp(s, "99")==0);
   int2string(124, s);
   assert(strcmp(s, "124")==0);
   int2string(3141, s);
   assert(strcmp(s, "3141")==0);
   int2string(-1000, s);
   assert(strcmp(s, "-1000")==0);
   
   return 0;
}

void int2string(int i, char* str) 
{
    int str_pointer = 0;
    int i_len = int_len(i);
    if (i < 0){
        str[str_pointer] = '-';
        str_pointer++;
        i *= -1;
    }

    for (int j = 0; j < i_len; j++){
        str[str_pointer] = '0' + num_iteration(i, j, i_len);
        str_pointer++;
    }
    str[str_pointer] = '\0';
}

int num_iteration(int i, int j, int i_len)
{
    int power = i_len - 1 - j;
    int selected_digit = (i / int_pow(10, power)) % 10;
    return selected_digit;
}

int int_len(int i)
{
    if (i == 0)
    {
        return 1;
    }
    int power = 0;
    while (i / int_pow(10, power) != 0){
        power++;
    }
    return power;
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