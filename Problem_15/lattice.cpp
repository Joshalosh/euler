
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

    while(IsDigit(*str)) {
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

int main(int argc, char **argv) {
    if (argc == 2 && IsDigit(*argv[1])) {

        int grid_size = StringToInt(argv[1]);

        Point **grid = SetUpGrid(grid_size);
        Point *travel_node = grid[0];

        uint64_t path_count = 0;
        FindUniquePaths(travel_node, &path_count);

        printf("The number of unique lattice paths for a %dx%d grid is:\n%llu\n", grid_size, grid_size, path_count);

        free(grid, grid_size);

    } else {
        printf("You need to pass a grid size\n");
    }
}

