#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <unistd.h>

#define WIDTH 80
#define HEIGHT 25
#define DELAY_MIN 10000
#define DELAY_MAX 500000
#define DELAY_STEP 20000

struct cell {
    int status;
    int neighbour;
};

// ========== ФУНКЦИИ ИНИЦИАЛИЗАЦИИ ==========

void init_grid(struct cell grid[HEIGHT][WIDTH]) {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            grid[i][j].status = 0;
            grid[i][j].neighbour = 0;
        }
    }
}

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

// ========== ФУНКЦИИ ЗАГРУЗКИ ПАТТЕРНОВ ==========

void load_glider(struct cell grid[HEIGHT][WIDTH]) {
    int i = 12, j = 40;
    grid[i][j+1].status = 1;
    grid[i+1][j+2].status = 1;
    grid[i+2][j].status = 1;
    grid[i+2][j+1].status = 1;
    grid[i+2][j+2].status = 1;
}

void start_game(struct cell grid[HEIGHT][WIDTH]) {
    init_grid(grid);
    load_glider(grid);
}

// ========== ФУНКЦИИ ПОДСЧЕТА СОСЕДЕЙ ==========

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

// ========== ФУНКЦИИ ПРАВИЛ ИГРЫ ==========

int get_next_status(int current, int neighbours) {
    if (current == 1) {
        return (neighbours == 2 || neighbours == 3) ? 1 : 0;
    } else {
        return (neighbours == 3) ? 1 : 0;
    }
}

// ========== ФУНКЦИИ ОБНОВЛЕНИЯ СОСТОЯНИЯ ==========

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
            grid[i][j].neighbour = 0;  // Обнуляем для следующего хода
        }
    }
}

// ========== ФУНКЦИИ ОТРИСОВКИ ==========

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

// ========== ФУНКЦИИ ПОДСЧЕТА ЖИВЫХ КЛЕТОК ==========

int count_live_cells(struct cell grid[HEIGHT][WIDTH]) {
    int live = 0;
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (grid[i][j].status == 1) live++;
        }
    }
    return live;
}

// ========== ФУНКЦИИ ОБРАБОТКИ ВВОДА ==========

void adjust_speed(int *speed, int delta) {
    *speed += delta;
    if (*speed < DELAY_MIN) *speed = DELAY_MIN;
    if (*speed > DELAY_MAX) *speed = DELAY_MAX;
}

void handle_input(int *speed, int *running) {
    int ch = getch();
    
    switch(ch) {
        case 'a':
        case 'A':
            adjust_speed(speed, -DELAY_STEP);
            break;
            
        case 'z':
        case 'Z':
            adjust_speed(speed, DELAY_STEP);
            break;
            
        case ' ':
        case 27:
            *running = 0;
            break;
    }
}

// ========== ФУНКЦИИ ОЧИСТКИ ==========

void cleanup_ncurses(WINDOW *win) {
    delwin(win);
    endwin();
}

// ========== ГЛАВНАЯ ФУНКЦИЯ ==========

int main() {
    struct cell grid[HEIGHT][WIDTH];
    int next[HEIGHT][WIDTH];  // Массив для хранения следующего поколения
    int generation = 0;
    int speed = DELAY_MAX / 2;
    int running = 1;
    
    init_ncurses();
    WINDOW *gamewin = create_game_window();
    start_game(grid);
    
    while (running) {
        generation++;
        
        // Подсчет соседей для текущего поколения
        count_neighbour(grid);
        
        // Вычисление следующего поколения
        compute_next_generation(grid, next);
        
        // Отрисовка ТЕКУЩЕГО поколения
        draw_grid(gamewin, grid);
        
        // Применение следующего поколения
        apply_next_generation(grid, next);
        
        // Подсчет живых клеток в НОВОМ поколении
        int live = count_live_cells(grid);
        
        // Отрисовка информации
        draw_info(gamewin, generation, live, speed);
        wrefresh(gamewin);
        
        // Проверка на окончание игры
        if (live == 0) {
            draw_game_over(gamewin);
            sleep(2);
            break;
        }
        
        // Обработка ввода и задержка
        handle_input(&speed, &running);
        usleep(speed);
    }
    
    cleanup_ncurses(gamewin);
    printf("Game finished! Total generations: %d\n", generation);
    return 0;
}