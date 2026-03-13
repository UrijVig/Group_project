#include "game_logic.h"

int get_next_status(int current, int neighbours) {
    if (current == 1) {
        return (neighbours == 2 || neighbours == 3) ? 1 : 0;
    } else {
        return (neighbours == 3) ? 1 : 0;
    }
}

void compute_next_generation(struct cell grid[HEIGHT][WIDTH], int next[HEIGHT][WIDTH]) {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            next[i][j] = get_next_status(grid[i][j].status, grid[i][j].neighbour);
        }
    }
}

void apply_next_generation(struct cell grid[HEIGHT][WIDTH], int next[HEIGHT][WIDTH]) {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            grid[i][j].status = next[i][j];
            grid[i][j].neighbour = 0;
        }
    }
}