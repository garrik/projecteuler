#include <limits.h>
#include <stdio.h>

// run to inspect platform limits
int main()
{
    printf("The min value of signed char is %d\n", SCHAR_MIN);
    printf("The max value of signed char is %d\n", SCHAR_MAX);
    printf("The min value of int is %d\n", INT_MIN);
    printf("The max value of int is %d\n", INT_MAX);
    printf("The max value of unsigned int is %u\n", UINT_MAX);
    printf("The min value of long is %ld\n", LONG_MIN);
    printf("The max value of long is %ld\n", LONG_MAX);
    printf("The max value of unsigned long is %lu\n", ULONG_MAX);
    return 0;
}