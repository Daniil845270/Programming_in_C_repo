#include <stdio.h>
#include <ctype.h>
#include <assert.h>
#include <stdbool.h>
#define AlPHLEN ('z' - 'a' + 1)

bool isprime(int a, int b, int c);

int main(void)
{
    printf("%i\n", isprime(1,1,2));
    return 0;
}

bool isprime(int a, int b, int c)
{
    int prime_test = a + b + c;
    for (int i = 1; i <= prime_test; i++)
    {
        if (prime_test % i == 0 && (i != 1 && i != prime_test))
        {
            return false;
        }
    }
    return true;
}