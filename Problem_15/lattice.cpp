
#include <stdio.h>
#include <stdlib.h>

#include "lattice.h"

u64 **SetGridValues(Memory_Arena *arena, s32 size) {
    s32 height = size;
    s32 width  = size;
    // We need to create a grid 1 size larger than the set size
    // to be able to flag where the edges of the grid is
    u64 **grid = (u64 **)ArenaAlloc(arena, (height + 1) * sizeof(u64 *));
    for (int i = 0; i <= height; i++) {
        grid[i] = (u64 *)ArenaAlloc(arena, (width + 1) * sizeof(u64)); // Adding 1 to width just like with height
        ZeroArray(grid[i], width + 1);
    }

    // Initialising the first square in the grid manually
    grid[height][width] = 1;

    for (int y = height; y >= 0; y--) {
        for (int x = width; x >= 0; x--) {
            // Make sure we don't iterate over the case we've
            // already initialised
            if (x < width || y < width) {
                u64 right_path = (x == width)  ? 0 : grid[y][x+1];
                u64 down_path  = (y == height) ? 0 : grid[y+1][x];

                grid[y][x] = right_path + down_path;
            }
        }
    }

    return grid;
}

void PrintGrid(u64 **grid, s32 size) {
    for (int y = 0; y <= size; y++) {
        for (int x = 0; x <= size; x++) {
            printf("%4llu ", grid[y][x]);
        }
        printf("\n");
    }
}

int main(int argc, char **argv) {
    if(argc == 2) {
        s32 grid_size = atoi(argv[1]);
        Assert(grid_size);

        Memory_Arena arena;
        InitArena(&arena, 1024*1024);
        
        u64 **grid = SetGridValues(&arena, grid_size);

        PrintGrid(grid, grid_size);

        FreeArena(&arena);
    } else {
        printf("You need to also pass the grid size you fucking piece of shit\n");
    }
}

