struct Point {
    Point *Right;
    Point *Down;

    bool has_branch;
    int  branch_count;
}

void SetUpGrid(int size) {
    int height = size;
    int width  = size;

    Point **grid = (Point **)malloc(height * sizeof(Point *));
    for (int i = 0; i < size; i++) {
        points[i] = (struct Point *)width * malloc(sizeof(Point));
    }
}
