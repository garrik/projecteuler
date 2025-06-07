#include <assert.h>
#include <string.h> // required by memset

static const int DIGITS_SIZE = 50;

int is_palindrome(int number);

int find_largest_palindrome_from_product_of(int n, int m) {
    int i = n, j = m;
    while (i > -1 && j > -1) {
        int number = i * j;
        if (is_palindrome(number)) {
            // printf("Found palindrome %d, product of %d and %d\n", number, i, j);
            return number;
        }
        // printf("Not a palindrome %d, product of %d and %d\n", number, i, j);
        if (i < j) {
            j--;
        } 
        else {
            i--;
        }
    }
    return -1;
}

int find_largest_palindrome_from_product_of___wrong(int n, int m) {
    for (int i = n; i > -1; i--) {
        for (int j = m; j > -1; j--) {
            int number = i * j;
            if (is_palindrome(number)) {
                // printf("Found palindrome %d, product of %d and %d\n", number, i, j);
                return number;
            }
            // printf("Not a palindrome %d, product of %d and %d\n", number, i, j);
        }
    }
    return -1;
}

int is_palindrome(int number) {
    int digits[DIGITS_SIZE];
    memset(digits, 0, sizeof(digits));
    // int digits[DIGITS_SIZE] = {}; // not a standard before C23, does not compile with -pedantic
    int index = 0;
    while (number > 0) {
        digits[index++] = number % 10;
        number = number / 10;
        assert(index < DIGITS_SIZE);
    }
    for (int i = 0; i < index / 2; i++) {
        if (digits[i] != digits[index - i - 1]) {
            return 0;
        }
    }
    return 1;
}