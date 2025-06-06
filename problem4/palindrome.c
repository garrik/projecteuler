int is_palindrome(int number) {
    int digits[100] = {0};
    int index = 0;
    while (number > 0) {
        digits[index++] = number % 10;
        number = number / 10;
    }
    for (int i = 0; i < index / 2; i++) {
        if (digits[i] != digits[index - i - 1]) {
            return 0;
        }
    }
    return 1;
}