
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

struct Point {
    Point *right;
    Point *down;
};

Point **SetUpGrid(int size) {

    // We need to add one to the size as we are setting up the nodes
    // on a grid not the paths between. So that means a 2x2 grid is 
    // made up of 3x3 nodes.
    int height = size + 1;
    int width  = size + 1;

    Point **grid = (Point **)malloc(height * sizeof(Point *));
    for (int i = 0; i < height; i++) {
        grid[i] = (Point *)malloc(width * sizeof(Point));
    }

    // Initialise the grid and set up the pointers correctly
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            // All nodes except the last node on the x axis are pointed to the
            // next node in the array. This needs to stop happening by the second
            // last node in the array, if not it will then point out of bounds
            grid[y][x].right = (x < width - 1)  ? &grid[y][x+1] : NULL;
            
            // Same on the y axis
            grid[y][x].down   = (y < height - 1) ? &grid[y+1][x] : NULL;
        }
    }

    return grid;
}

void FreeGrid(Point **grid, int size) {
    //need to make sure to account for the extra node
    //that was allocated
    int height = size + 1;
    for (int i = 0; i < height; i++) {
        free(grid[i]);
    }

    free(grid);
}

void SearchGridForUniquePaths(Point *travel_node, uint64_t *path_count) {
    if (travel_node->right == NULL && travel_node->down == NULL) {
        (*path_count)++;
    }

    if (travel_node->right != NULL) {
        SearchGridForUniquePaths(travel_node->right, path_count);
    }

    if (travel_node->down != NULL) {
        SearchGridForUniquePaths(travel_node->down, path_count);
    }
}

int main(int argc, char **argv) {
    if (argc == 2) {

        int size = atoi(argv[1]);

        Point **grid = SetUpGrid(size);
        Point *travel_node = grid[0];
        
        uint64_t path_count = 0;
        SearchGridForUniquePaths(travel_node, &path_count);

        printf("The number of unique paths are: %llu\n", path_count);
    } else {
        ("You need to pass a grid size\n");
    }
}
