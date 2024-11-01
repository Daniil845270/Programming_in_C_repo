#include "rot18.h"
#define BIG_NUM 500

int palindrome_checker(char palindromes[], int p1, int p2);
int pointer_set(char palindromes[], int p1, int p2);

int main(void)
{
    char palindromes[BIG_NUM] = {'0'};
    int p1 = 0, p2 = 0;

    if (fgets(palindromes, BIG_NUM, stdin) == NULL){
        return 1;
    }

    if (pointer_set(palindromes, p1, p2) == -1){
        printf("Need at least 2 characters\n");
        return 0;
    }
    else{
        p2 = pointer_set(palindromes, p1, p2);
    }

    if (palindrome_checker(palindromes, p1, p2) == 0){
        printf("Your string is not a palindrome\n");
    }
    else{
        printf("This is a palindrome\n");
    }

    return 0;
} 

int pointer_set(char palindromes[], int p1, int p2)
{
    if (palindromes[p1] == '\n'){
        return -1;
    }
    char buffer_char = palindromes[p2];
    while (buffer_char != '\n'){
        p2++;
        buffer_char = palindromes[p2];
    }
    p2--;
    if (p1 == p2){
        return -1;
    }
    return p2;
}

int palindrome_checker(char palindromes[], int p1, int p2)
{
    while (p1 < p2)
    {
        while (isalnum(palindromes[p1]) == false){
            p1++;
        }
        while (isalnum(palindromes[p2]) == false){
            p2--;
        }
        palindromes[p1] = tolower(palindromes[p1]); 
        palindromes[p2] = tolower(palindromes[p2]); 
        if (palindromes[p1] != palindromes[p2]){
            return 0;
        }
        p1++; p2--;
    }
    return 1;
}