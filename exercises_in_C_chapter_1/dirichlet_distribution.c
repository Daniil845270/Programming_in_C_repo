#include <stdio.h>

//Write a program that computes what fraction of all primes end with a 3.
//You can do this by generating a large number of primes, in sequence, and keeping a running
//count of the number that end with 3, as compared to the total of primes generated.

int main(void)
{
    printf("Please, enter how many prime numbers you want to include in the sample\n");
    int final_prime_number;
    scanf("%i", &final_prime_number);

    int prime_candidate = 1, prime_marker = 1, prime_counter = 1, ends_with_three = 0;

    while (prime_counter != final_prime_number + 1){

        for (int iteration = 1; iteration <= prime_candidate; iteration++){
            if (prime_candidate % iteration == 0 && iteration != prime_candidate && iteration != 1){
                prime_marker = 2;
            }
        }
        if (prime_marker == 1) {
            // printf("%i\n", prime_candidate);
            prime_counter++;
            if (prime_candidate % 10 == 3){
                ends_with_three++;
            }
        }
        prime_marker = 1;
        prime_candidate++;
    }

    int proportion;
    proportion = (ends_with_three * 100) / final_prime_number;
    printf("There are %i percent of prime numbers that end with a 3\n", proportion);
}

