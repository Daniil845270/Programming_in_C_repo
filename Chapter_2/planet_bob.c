#include <stdio.h>
#include <ctype.h>
#include <assert.h>
#include <stdbool.h>
#define YES true
#define NO false

bool iscvc(int a, int b, int c);
bool isvcv(int a, int b, int c);
bool firstISthird(int a, int c);
bool isvowel(int character);
bool isprime(int a, int b, int c);
int from1(int a);

int main(void)
{
    int cnt = 0;
    for (int fst = 'a'; fst <= 'z'; fst++)
    {                
        for (int snd = 'a'; snd <= 'z'; snd++)
        {
            for (int thrd = 'a'; thrd <= 'z'; thrd++)
            {
                if (iscvc(fst, snd, thrd) == YES || isvcv(fst, snd, thrd) == YES)
                {
                    if(firstISthird(fst, thrd) == YES)
                    {
                        if(isprime(from1(fst), from1(snd), from1(thrd)) == YES) 
                        {
                            cnt++;
                            printf("%i ", cnt);
                            putchar(fst); putchar(snd); putchar(thrd);
                            putchar('\n');
                        }
                    }
                }
            }
            
        }
    }
    return 0;
}

bool iscvc(int a, int b, int c)
{
    if (isvowel(a) == NO && isvowel(b) == YES && isvowel(c) == NO)
    {
        return YES;
    }
    else
    {
        return NO;
    }
}

bool isvcv(int a, int b, int c)
{
    if (isvowel(a) == YES && isvowel(b) == NO && isvowel(c) == YES)
    {
        return YES;
    }
    else
    {
        return NO;
    }
}

bool firstISthird(int a, int c)
{
    if (a == c)
    {
        return YES;
    }
    else
    {
        return NO;
    }
}

bool isvowel(int character)
{
    if (character == 'a' || character == 'e' || character == 'i' || character == 'o' || character == 'u' 
    || character == 'A' || character == 'E' || character == 'I' || character == 'O' || character == 'U')
    {
        return YES;
    }

    else
    {
        return NO;
    }

    return NO; //should anything crash for some reason
}

bool isprime(int a, int b, int c)
{
    int prime_test = a + b + c;
    for (int i = 1; i < prime_test; i++)
    {
        if (prime_test % i == 0 && i != 1)
        {
            return NO;
        }
    }
    return YES;
}

int from1(int a) 
{
    return a -= 96;
}
