#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

typedef uint8_t  u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef int8_t  s8;
typedef int16_t s16;
typedef int32_t s32;
typedef int64_t s64;

#define DIGIT_COUNT 10
#define ARRAY_COUNT(array) sizeof(array) / sizeof((array)[0])

static u64 Factorial(u32 factorial_number)
{
    u64 result = 1;

    for (u32 i = 1; i <= factorial_number; i++) {
        result *= i;
    }

    return result;
}

static void FindSpecificPermutation(u32 number, u32 digits[], u32 size) {
    number--; // NOTE: Adjust to account for starting at 0.

    for (u32 i = size; i > 0; i--) {
        u64 factorial = Factorial(i - 1);
        u32 index = number / factorial;
        number %= factorial;

        printf("%d", digits[index]);

        // NOTE: remove the used digit.
        for (u32 j = index; j < size - 1; j++) {
            digits[j] = digits[j + 1];
        }
    }

    printf("\n");
}

int main()
{
    u32 digits[DIGIT_COUNT] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    FindSpecificPermutation(1000000, digits, DIGIT_COUNT);
}
