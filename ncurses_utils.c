#include "ncurses_utils.h"
#include "input_handler.h"

void init_ncurses() {
    initscr();
    cbreak();
    noecho();
    nodelay(stdscr, TRUE);
    keypad(stdscr, TRUE);
    curs_set(0);
}

WINDOW* create_game_window() {
    WINDOW *win = newwin(HEIGHT + 2, WIDTH + 2, 0, 0);
    box(win, 0, 0);
    return win;
}

void draw_cell(WINDOW *win, int i, int j, int status) {
    if (status == 1) {
        mvwprintw(win, i + 1, j + 1, "*");
    } else {
        mvwprintw(win, i + 1, j + 1, " ");
    }
}

void draw_grid(WINDOW *win, struct cell grid[HEIGHT][WIDTH]) {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            draw_cell(win, i, j, grid[i][j].status);
        }
    }
}

void draw_info(WINDOW *win, int generation, int live, int speed) {
    mvwprintw(win, 0, 2, " Gen:%d ", generation);
    mvwprintw(win, HEIGHT + 1, 2, " Live:%d ", live);
    
    int speed_percent = (DELAY_MAX - speed) * 100 / (DELAY_MAX - DELAY_MIN);
    mvwprintw(win, HEIGHT + 1, 20, " Speed:%d%% ", speed_percent);
    
    mvwprintw(win, 0, WIDTH - 25, " A:+ Z:- Space:Exit ");
}

void draw_game_over(WINDOW *win) {
    mvwprintw(win, HEIGHT/2, WIDTH/2 - 10, "GAME OVER - NO LIVE CELLS");
    wrefresh(win);
}

void cleanup_ncurses(WINDOW *win) {
    delwin(win);
    endwin();
}