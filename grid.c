#include "grid.h"

void init_grid(struct cell grid[HEIGHT][WIDTH]) {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            grid[i][j].status = 0;
            grid[i][j].neighbour = 0;
        }
    }
}

int get_neighbor_index(int index, int delta, int max) {
    return (index + delta + max) % max;
}

void add_neighbor_count(struct cell grid[HEIGHT][WIDTH], int i, int j) {
    for (int di = -1; di <= 1; di++) {
        for (int dj = -1; dj <= 1; dj++) {
            if (di == 0 && dj == 0) continue;
            
            int ni = get_neighbor_index(i, di, HEIGHT);
            int nj = get_neighbor_index(j, dj, WIDTH);
            
            grid[ni][nj].neighbour++;
        }
    }
}

void count_neighbour(struct cell grid[HEIGHT][WIDTH]) {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (grid[i][j].status == 1) {
                add_neighbor_count(grid, i, j);
            }
        }
    }
}

int count_live_cells(struct cell grid[HEIGHT][WIDTH]) {
    int live = 0;
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (grid[i][j].status == 1) live++;
        }
    }
    return live;
}