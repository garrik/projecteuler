#include <stdio.h>

int main(int argc, int **argv) 
{
    int max = 1000;
    int sum = 0;

    for (int i = 0; i < max; i++) {
        if (i % 3 == 0) { // divisible by 3
            sum += i;
        }
        else if (i % 5 == 0) { // divisible by 5
            sum += i;
        }
    }

    printf("The sum of all the multiples of 3 or 5 below 1000 is %d\n", sum);
    return 0;
}