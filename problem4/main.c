#include <stdio.h>

#include "palindrome.c" // unity build

int main() {
    printf("Look for the largest palindrome\n");
    int result = find_largest_palindrome_from_product_of(999, 999);
    if (result == -1) {
        printf("Cannot find a palindrome.\n");
        return 1;
    }
    printf("The largest palindrome is %d\n", result);
    return 0;
}