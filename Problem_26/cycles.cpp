#include <stdio.h>
#include <stdint.h>
#include <string.h>

typedef uint8_t  u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef int8_t  s8;
typedef int16_t s16;
typedef int32_t s32;
typedef int64_t s64;

typedef float       f32;
typedef double      f64;
typedef long double f128;

void PrintBinary(u32 num) {
    for (int i = 23; i >= 0; i--) {
        printf("%d", (num >> i) & 1);
    }
}

s32 FindRecurringCycleLength(s32 d) {
    s32 remainders[1000]; // Array to store remainders
    memset(remainders, 0, sizeof(remainders));

    s32 remainder = 1;
    s32 position  = 0;

    while (remainder != 0 && remainders[remainder] == 0) {
        remainders[remainder] = position;
        remainder = remainder * 10 % d;
        position++;
    }

    if (remainder == 0) { // No cycle found, decimal terminates
        return 0;
    }

    return position - remainder[remainders]; // NOTE: Length of the cycle
}

int main() {
    s32 longest = 0;
    s32 best_d = 0;

    for (int d = 2; d <= 1000; d++) {
        s32 length = FindRecurringCycleLength(d);
        if (length > longest) {
            longest = length;
            best_d = d;
        }
    }

    printf("The value of d < 1000 with the longest recurring cycle is %d with a cycle length of %d.\n", best_d, longest);
}


#if 0
int main() {
#if 0
    f32 num = 1;
    num /= 7;
    int top_mask = 0;
    top_mask = ~top_mask;

    u32 test = 1;
    test <<= 31;

    int bum = (int)num;

    int x = 5;
#endif

    union {
        float f;
        uint32_t s;
    } u;

    u.f = 1;
    u.f /= 7;

#if 0
    u32 bits;
    memcpy(&bits, &f, sizeof(f));
#else
    u32 bits = u.s;
#endif


    u32 mask = 0x7FFFFF;
    u32 mantissa = bits & mask;

    if ((bits & 0x7F800000) != 0) {
        mantissa |= 0x800000;
    }

    printf("Mantissa (with implicit '1' if normalized): %u (as integer)\n", mantissa);

    PrintBinary(mantissa);
    printf("\n");
}
#endif
