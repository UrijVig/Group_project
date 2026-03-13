#ifndef PATTERNS_H
#define PATTERNS_H

#include "grid.h"

void load_glider(struct cell grid[HEIGHT][WIDTH]);
void load_blinker(struct cell grid[HEIGHT][WIDTH]);
void load_block(struct cell grid[HEIGHT][WIDTH]);
void load_beehive(struct cell grid[HEIGHT][WIDTH]);
void load_gosper_glider_gun(struct cell grid[HEIGHT][WIDTH]);
void load_pattern(struct cell grid[HEIGHT][WIDTH], int pattern_num);

// Новая функция для загрузки из stdin
void load_from_stdin(struct cell grid[HEIGHT][WIDTH]);

#endif