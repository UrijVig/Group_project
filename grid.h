#ifndef GRID_H
#define GRID_H

#define WIDTH 80
#define HEIGHT 25

struct cell {
    int status;
    int neighbour;
};

void init_grid(struct cell grid[HEIGHT][WIDTH]);
int get_neighbor_index(int index, int delta, int max);
void add_neighbor_count(struct cell grid[HEIGHT][WIDTH], int i, int j);
void count_neighbour(struct cell grid[HEIGHT][WIDTH]);
int count_live_cells(struct cell grid[HEIGHT][WIDTH]);

#endif