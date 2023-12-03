
#include <stdio.h>
#include <string.h>

#define MAX_SIZE 1000

static void AddLargeNumbers(int *array_one, int *array_two, int *result)
{
    int carry = 0;

    for (int i = MAX_SIZE - 1; i >= 0; i--) {
        int sum = array_one[i] + array_two[i] + carry;
        result[i] = sum % 10;
        carry     = sum / 10;
    }
}

int main()
{
    int fib1[MAX_SIZE]       = {};
    int fib2[MAX_SIZE]       = {};
    fib1[MAX_SIZE - 1]       = 1;
    fib2[MAX_SIZE - 1]       = 1;
    int fib_result[MAX_SIZE] = {};

    int digit_count          = 1;
    int term                 = 2;

    while (digit_count < 1000) {
        AddLargeNumbers(fib1, fib2, fib_result);

        memcpy(fib1, fib2, sizeof(fib1));
        memcpy(fib2, fib_result, sizeof(fib2));

        // NOTE: Check if we've reached a new digit 
        if (fib2[MAX_SIZE - digit_count - 1] != 0) {
            digit_count++;
        }

        term++;
    }

    printf("First term with 1000 digits: %d\n", term);
}

