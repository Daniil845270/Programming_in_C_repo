#include <stdio.h>

// Write a program that prints out the first n primes, where n is input by the user.

int main(void)
{
    printf("Please, enter what prime number you want to see\n");
    int final_prime_number;
    scanf("%i", &final_prime_number);

// final_prime_number - it is the number that represents the n th prime number a user wants to see
// prime_counter - a variable that stores the number of prime numenrs detected by the for loop
// prime_candidate - a number that is tested to be prime
// iteration - a number that divides the prime_candidate to test if it is prime

    int prime_candidate = 1, prime_marker = 1, prime_counter = 1;

    while (prime_counter != final_prime_number + 2)
    {

        for (int iteration = 1; iteration <= prime_candidate; iteration++){
            if (prime_candidate % iteration == 0 && iteration != prime_candidate && iteration != 1){
                prime_marker = 2; // 2 is an arbitrary value to signify that prime_candidate is not prime
            }
        }
        if (prime_marker == 1) {
            printf("%i\n", prime_candidate);
            prime_counter++;
        }
        // Because this is a while loop we need to manually increment the prime_candidate and reset the prime
        // marker even if the i th number was prime
        prime_marker = 1;
        prime_candidate++;
    }

}
