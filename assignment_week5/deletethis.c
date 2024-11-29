#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() 
{
    srand(time(NULL));
    char string[110] = {0};
    for (int i = 0; i < (20*5); i++) {
        int random_number = rand() % 3 + 'A';
        string[i] = random_number;
    }
    printf("%s\n", string);
}