#if !defined(LATTICE_H)

#include <stdint.h>

#typedef uint8_t u8 
#typedef uint16_t u16 
#typedef uint32_t u32 
#typedef uint64_t u64 

struc Memory_Arena {
    u8 *start;
    u8 *current;
    u8 *end;
};

#define "LATTIC_H"
#endif
