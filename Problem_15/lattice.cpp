
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

// Definition of the Point structure which includes two pointers 
// (right and down) and two additional attributes.
struct Point {
    Point *right;
    Point *down;
};

// SetUpGrid function allocates memory for the 2D grid and initializes each point.
Point **SetUpGrid(int size) {
    int height = size;
    int width  = size;

    // Allocates memory for an array of pointers. Each pointer will later point to a row in the grid.
    Point **grid = (Point **)malloc(height * sizeof(Point *));
    for (int i = 0; i < size; i++) {
        // Allocates memory for each row in the grid.
        grid[i] = (Point *)malloc(width * sizeof(Point));
    }

    // Initializes the attributes of each point and links them together.
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            // Sets the right pointer to point to the next point on the right, unless it's the rightmost point.
            grid[y][x].right = (x < width - 1)  ? &grid[y][x+1] : NULL; 
            // Sets the down pointer to point to the next point below, unless it's the bottommost point.
            grid[y][x].down  = (y < height - 1) ? &grid[y+1][x] : NULL;

        }
    }

    // Returns the pointer to the first row of pointers, which effectively represents the entire 2D grid.
    return grid;
}

// FreeGrid function frees up the memory that was allocated for the grid.
void FreeGrid(Point **grid, int height) {
    for (int i = 0; i < height; i++) {
        // Frees each row in the grid.
        free(grid[i]);
    }
    // Frees the memory allocated for the array of pointers.
    free(grid);
}

// DepthFirstSearch function traverses the grid from a given point using depth-first search.
void DepthFirstSearch(Point *point, uint64_t *path_count) {
    // If we reached the destination (the bottom-right point), increment the path count.
    if (point->right == NULL && point->down == NULL) {
        (*path_count)++;
        return;
    }

    // If it's possible to go right, go right.
    if (point->right != NULL) {
        DepthFirstSearch(point->right, path_count);
    }

    // If it's possible to go down, go down.
    if (point->down != NULL) {
        DepthFirstSearch(point->down, path_count);
    }
}

// The main function where execution begins.
int main(int argc, char **argv) {
    if (argc == 2) {
        // Converts the first argument passed in the command line to an integer.
        int grid_size = atoi(argv[1]);

        // Sets up the grid of the desired size.
        Point **grid = SetUpGrid(grid_size + 1);
        // The traveler starts from the top-left point of the grid.
        Point *traveler = grid[0];

        // Initializes the count of unique paths to zero.
        uint64_t path_count = 0;
        // Traverses the grid to find all unique paths.
        DepthFirstSearch(traveler, &path_count);

        // Prints the number of unique paths.
        printf("The number of unique paths are: %llu\n", path_count);
        
        // Frees up the memory that was allocated for the grid.
        FreeGrid(grid, grid_size + 1);
    } else {
        // If the user didn't provide the grid size, prints an error message.
        printf("You need to pass a grid size IDIOT \n");
    }
}
