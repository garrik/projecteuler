#include <stdio.h>

int main(int argc, int **argv) 
{
    int max = 4000000;
    int sum = 0;
    int prev = 1; // 1st number of fibonacci sequence
    int fibonacci = 2; // 2nd number of fibonacci sequence

    while (fibonacci < max) {
        // printf("prev %d fib %d sum %d\n", prev, fibonacci, sum);

        if (fibonacci % 2 == 0) {
           sum += fibonacci;
        }

        // calc next fibonacci number
        int increment = prev;
        prev = fibonacci;
        fibonacci = fibonacci + increment;
    }

    printf("The sum of the even-valued terms in Fibonacci sequence whose values do not exceed four million is %d\n", sum);
    return 0;
}