#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H

#include "grid.h"

int get_next_status(int current, int neighbours);
void compute_next_generation(struct cell grid[HEIGHT][WIDTH], int next[HEIGHT][WIDTH]);
void apply_next_generation(struct cell grid[HEIGHT][WIDTH], int next[HEIGHT][WIDTH]);

#endif