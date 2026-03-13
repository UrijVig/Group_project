#ifndef NCURSES_UTILS_H
#define NCURSES_UTILS_H
#include "grid.h"

#include <ncurses.h>

void init_ncurses();
WINDOW* create_game_window();
void draw_cell(WINDOW *win, int i, int j, int status);
void draw_grid(WINDOW *win, struct cell grid[HEIGHT][WIDTH]);
void draw_info(WINDOW *win, int generation, int live, int speed);
void draw_game_over(WINDOW *win);
void cleanup_ncurses(WINDOW *win);

#endif