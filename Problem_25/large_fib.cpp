
#include <stdio.h>
#include <string.h>

#define MAX_SIZE 1000


static void AddLargeNumbers(int *array1, int *array2, int *result)
{
    int carry = 0;
    for (int i = MAX_SIZE - 1; i >= 0; i--) {
        int sum   = array1[i] + array2[i] + carry;
        result[i] = sum % 10;
        carry     = sum / 10;
    }
}

static void CopyArray(int *source, int *dest)
{
    for (int i = 0; i < MAX_SIZE; i++) {
        dest[i] = source[i];
    }
}

int main()
{
    int fib1[MAX_SIZE]       = {};
    int fib2[MAX_SIZE]       = {};
    int fib_result[MAX_SIZE] = {};
    fib1[MAX_SIZE - 1]       = 1;
    fib2[MAX_SIZE - 1]       = 1;

    int digit_count          = 1;
    int term                 = 2;

    while (digit_count < 1000) {
        AddLargeNumbers(fib1, fib2, fib_result);

        CopyArray(fib2, fib1);
        CopyArray(fib_result, fib2);

        if(fib2[MAX_SIZE - digit_count - 1] != 0)
        {
            digit_count++;
        }

        term++;
    }

    printf("The first term with 1000 digits is: %d\n", term);
}
