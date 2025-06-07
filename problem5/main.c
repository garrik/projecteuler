#include <stdio.h>
#include <limits.h>

int find_smallest_number_divisible_by_1_to_20(void);
int is_divisible_by_1_to_20(int number);

int find_smallest_number_divisible_by_1_to_20(void) {
    for (int i = 20; i < INT_MAX; i++) {
        int is_divisible = is_divisible_by_1_to_20(i);
        if (is_divisible) {
            return i;
        }
    }
    return 0;
}

int is_divisible_by_1_to_20(int number) {
    int divisible = 1;
    for (int i = 2; i < 21; i++) {
        if (number % i != 0) {
            divisible = 0;
            break;
        }
    }
    return divisible;
}

int main(void)
{
    printf("Look for the smallest number divisible by 1 to 20\n");
    int result = find_smallest_number_divisible_by_1_to_20();
    if (result != 0) {
        printf("The smallest number divisible by 1 to 20 is %d\n", result);
    }
    else {
        printf("Cannot find the smallest number divisible by 1 to 20\n");
    }
    return 0;
}