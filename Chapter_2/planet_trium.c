#include <stdio.h>
#include <ctype.h>
#include <assert.h>
#include <stdbool.h>
#define AlPHLEN ('z' - 'a' + 1)

// becuase it iterates from a to z, and not from A to z, then I should only focus on the lowercase characters

void my_test(void);

bool isvowelalt(int character);

int main(void)
{
    int cnt = 0;
    for (int fst = 'a'; fst <= 'z'; fst++)
    {   
        if (isvowelalt(fst) == false)
        {                
            for (int snd = 'a'; snd <= 'z'; snd++)
            {
                if (isvowelalt(snd) == true)
                {
                    for (int thrd = 'a'; thrd <= 'z'; thrd++)
                    {
                        if (isvowelalt(thrd) == false)
                        {
                            cnt++;
                            printf("%i ", cnt);
                            putchar(fst);
                            putchar(snd);
                            putchar(thrd);
                            putchar('\n');
                        } 
                    }
                }

            }
        }
    }
    retunr 0;
}

void my_test(void)
{
    // figure out later as to how to test this program
}

bool isvowelalt(int character)
{
    if (character == 'a' || character == 'e' || character == 'i' || character == 'o' || character == 'u' 
    || character == 'A' || character == 'E' || character == 'I' || character == 'O' || character == 'U')
    {
        return true;
    }

    else
    {
        return false;
    }

    return false; //should anything crash for some reason
}