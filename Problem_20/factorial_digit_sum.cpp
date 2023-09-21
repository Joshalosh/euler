#include <stdio.h>
#include <stdlib.h>

#define MAX_DIGITS 2568

struct Big_Int {
    unsigned int *digits;
    size_t size;
};

static void BigIntInit(Big_Int *number, unsigned int initial_digit) {
    number->digits    = (unsigned int *)malloc(MAX_DIGITS * sizeof(unsigned int));
    number->size      = 1;
    number->digits[0] = initial_digit;
}

static void BigIntFree(Big_Int *number) {
    free(number->digits);
}

static Big_Int Factorial(unsigned int max_factor) {
    Big_Int result;
    BigIntInit(&result, 1);

    for (unsigned int factor = 2; factor <= max_factor; factor++) {
        unsigned int carry = 0;

        for (size_t i = 0; i < result.size; i++) {
            unsigned long long product = (unsigned long long) result.digits[i] * factor + carry;

            result.digits[i] = product % 10;
            carry = product / 10;
        }

        while (carry != 0) {
            if (result.size >= MAX_DIGITS) {
                printf("Exceeded max digits!\n");
                exit(EXIT_FAILURE);
            }

            result.digits[result.size++] = carry % 10;
            carry /= 10;
        }
    }

    return result;
}

int main() {
    unsigned int tests;
    scanf("%u", &tests);

    while (tests--) {
        unsigned int number;
        scanf("%u", &number);

        Big_Int fact = Factorial(number);
        unsigned int sum = 0;

        for (size_t i = 0; i < fact.size; i++) {
            sum += fact.digits[i];
        }
        printf("%u\n", sum);

        BigIntFree(&fact);
    }
}
