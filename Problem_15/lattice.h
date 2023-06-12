#if !defined(LATTICE_H)

#include <stdint.h>

typedef uint8_t  u8; 
typedef uint16_t u16; 
typedef uint32_t u32;
typedef uint64_t u64;

typedef int8_t  s8;
typedef int16_t s16;
typedef int32_t s32;
typedef int64_t s64;

#define Assert(expression) if(!(expression)) {*(int *)0 = 0;}

struct Memory_Arena {
    u8 *start;
    u8 *current;
    u8 *end;
};

void InitArena(Memory_Arena *arena, size_t size) {
    arena->start   = (u8 *)malloc(size);
    arena->current = arena->start;
    arena->end     = arena->start + size;
}

void *ArenaAlloc(Memory_Arena *arena, size_t size) {
    void *result = NULL;
    // Check to see if there is enough space in the arena for allocation.
    // if not we will return NULL as an error;
    if (!(arena->current + size > arena->end)) {
        result = arena->current;
        arena->current += size;
    }

    return result;
}

void FreeArena(Memory_Arena *arena) {
    free(arena->start);
}

#define ZeroArray(pointer, count) (pointer, count*sizeof((pointer)[0])) 
void ZeroSize(void *ptr, size_t size) {
    u8 *byte = (u8 *)ptr;
    while (size--) {
        *byte++ = 0;
    }
}

#define LATTICE_H
#endif
