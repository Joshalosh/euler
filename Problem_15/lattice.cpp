
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

struct Point {
    Point *right;
    Point *down;
};

Point **SetUpGrid(int size) {
    int height = size + 1;
    int width  = size + 1;
    Point **grid = (Point **)malloc(height * sizeof(Point *));
    for (int i = 0; i < height; i++) {
        grid[i] = (Point *)malloc(width * sizeof(Point));
    }

    // Initialise the grid with points
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            grid[y][x].right = (x < width - 1)  ? &grid[y][x+1] : NULL;
            grid[y][x].down  = (y < height - 1) ? &grid[y+1][x] : NULL;
        }
    }

    return grid;
}

void FreeGrid(Point **grid, int size) {
    int height = size + 1;
    for (int i = 0; i < height; i++) {
        free(grid[i]);
    }
    free(grid);
}

bool IsDigit(char c) {
    bool result = (c >= '0' && c <= '9');
    return result;
}

int StringToInt(char *str) {
    int result = 0;
    int sign = 1;
    
    if (*str == '-') {
        sign = -1;
        *str++;
    }

    while (IsDigit(*str)) {
        result = result * 10 + (*str - '0');
        *str++;
    }

    result *= sign;
    return result;
}

void FindUniquePaths(Point *travel_node, uint64_t *path_count) {
    if (travel_node->right == NULL && travel_node->down == NULL) {
        (*path_count)++;
        return;
    }

    if (travel_node->right != NULL) {
        FindUniquePaths(travel_node->right, path_count); 
    }

    if (travel_node->down != NULL) {
        FindUniquePaths(travel_node->down, path_count);
    }
}

void FreeGrid(uint64_t **grid, int size) {
    for (int i = 0; i < size; i++) {
        free(grid[i]);
    }
    free(grid);
}

uint64_t **CountGridPaths(int grid_size) {
    int height = grid_size;
    int width  = grid_size;

    uint64_t **grid = (uint64_t **)malloc((height + 1) * sizeof(uint64_t *));
    if (grid == NULL) {
        fprintf(stderr, "Failed to allocate Memory\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i <= height; i++) {
        grid[i] = (uint64_t *)calloc((width + 1), sizeof(uint64_t));
        if (grid[i] == NULL) {
            fprintf(stderr, "Failed to allocate Memory\n");
            exit(EXIT_FAILURE);
        }
    }

    grid[height][width] = 1;

    for (int y = height; y >= 0; y--) {
        for (int x = width; x >= 0; x--) {
            if (x != width || y != height) {
                uint64_t path_right = (x == width)  ? 0 : grid[y][x+1];
                uint64_t path_down  = (y == height) ? 0 : grid[y+1][x];
                grid[y][x] = path_right + path_down;
            }
        }
    }

    //FreeGrid(grid, grid_size+1);

    return grid;
}

void PrintGrid(uint64_t **grid, int size) {
    for(int y = 0; y <= size; y++) {
        for (int x = 0; x <= size; x++) {
            printf("%4llu ", grid[y][x]);
        }
        printf("\n");
    }
}


int main(int argc, char **argv) {
    if (argc == 2 && IsDigit(*argv[1])) {

        int grid_size = StringToInt(argv[1]);

#if 0
        Point **grid = SetUpGrid(grid_size);
        Point *travel_node = grid[0];

        uint64_t path_count = 0;
        FindUniquePaths(travel_node, &path_count);

        printf("The number of unique lattice paths for a %dx%d grid is:\n%llu\n", grid_size, grid_size, path_count);

        free(grid, grid_size);
#endif
        uint64_t **grid = CountGridPaths(grid_size);

        PrintGrid(grid, grid_size);
        //printf("The number of unique lattice paths for a %dx%d grid is:\n%llu\n", grid_size, grid_size, path_count);
    } else {
        printf("You need to pass a grid size\n");
    }
}

