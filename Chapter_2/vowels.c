#include <stdio.h>
#include <ctype.h>

int isvowel(int character);

int main(void)
{
    int character;

    while ((character = getchar()) != '!')
    {
        putchar(isvowel(character));
    }
    putchar('\n');
    putchar('\n');

    return 0;
}

int isvowel(int character)
{
    if (character == 'a' || character == 'e' || character == 'i' || character == 'o' || character == 'u' 
    || character == 'A' || character == 'E' || character == 'I' || character == 'O' || character == 'U')
    {
        return toupper(character);
    }

    else
    {
        return tolower(character); // I didn't expect it, but it aslo hanldes numbers and special characters just fine
    }

    return 0; //should anything crash for some reason
}