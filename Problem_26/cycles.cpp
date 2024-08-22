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
}
