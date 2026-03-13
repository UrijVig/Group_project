#include "patterns.h"
#include <stdio.h>

void load_glider(struct cell grid[HEIGHT][WIDTH]) {
    init_grid(grid);
    int i = 12, j = 40;
    grid[i][j+1].status = 1;
    grid[i+1][j+2].status = 1;
    grid[i+2][j].status = 1;
    grid[i+2][j+1].status = 1;
    grid[i+2][j+2].status = 1;
}

void load_blinker(struct cell grid[HEIGHT][WIDTH]) {
    init_grid(grid);
    int i = 12, j = 40;
    // Осциллятор - мигалка (3 клетки в ряд)
    grid[i][j].status = 1;
    grid[i][j+1].status = 1;
    grid[i][j+2].status = 1;
}

void load_block(struct cell grid[HEIGHT][WIDTH]) {
    init_grid(grid);
    int i = 12, j = 40;
    // Стабильный блок 2x2
    grid[i][j].status = 1;
    grid[i][j+1].status = 1;
    grid[i+1][j].status = 1;
    grid[i+1][j+1].status = 1;
}

void load_beehive(struct cell grid[HEIGHT][WIDTH]) {
    init_grid(grid);
    int i = 12, j = 40;
    // Улей - стабильная фигура
    grid[i][j+1].status = 1;
    grid[i][j+2].status = 1;
    grid[i+1][j].status = 1;
    grid[i+1][j+3].status = 1;
    grid[i+2][j+1].status = 1;
    grid[i+2][j+2].status = 1;
}

void load_gosper_glider_gun(struct cell grid[HEIGHT][WIDTH]) {
    init_grid(grid);
    int i = 5, j = 20;  // Смещаем для лучшего отображения
    
    // Левая часть ружья Госпера
    grid[i+4][j].status = 1;
    grid[i+5][j].status = 1;
    grid[i+4][j+1].status = 1;
    grid[i+5][j+1].status = 1;
    
    grid[i+4][j+10].status = 1;
    grid[i+5][j+10].status = 1;
    grid[i+6][j+10].status = 1;
    grid[i+3][j+11].status = 1;
    grid[i+7][j+11].status = 1;
    grid[i+2][j+12].status = 1;
    grid[i+8][j+12].status = 1;
    grid[i+5][j+13].status = 1;
    
    // Правая часть
    grid[i+3][j+14].status = 1;
    grid[i+7][j+14].status = 1;
    grid[i+4][j+15].status = 1;
    grid[i+5][j+15].status = 1;
    grid[i+6][j+15].status = 1;
    grid[i+5][j+16].status = 1;
    
    grid[i+2][j+20].status = 1;
    grid[i+3][j+20].status = 1;
    grid[i+4][j+20].status = 1;
    grid[i+2][j+21].status = 1;
    grid[i+3][j+21].status = 1;
    grid[i+4][j+21].status = 1;
    grid[i+1][j+22].status = 1;
    grid[i+5][j+22].status = 1;
    
    grid[i+1][j+24].status = 1;
    grid[i+5][j+24].status = 1;
    grid[i+2][j+34].status = 1;
    grid[i+3][j+34].status = 1;
    grid[i+2][j+35].status = 1;
    grid[i+3][j+35].status = 1;
}

void load_pattern(struct cell grid[HEIGHT][WIDTH], int pattern_num) {
    switch(pattern_num) {
        case 1:
            load_glider(grid);
            break;
        case 2:
            load_blinker(grid);
            break;
        case 3:
            load_block(grid);
            break;
        case 4:
            load_beehive(grid);
            break;
        case 5:
            load_gosper_glider_gun(grid);
            break;
        default:
            load_glider(grid);  // По умолчанию - планер
    }
}

void load_from_stdin(struct cell grid[HEIGHT][WIDTH]) {
    init_grid(grid);
    char line[WIDTH + 2];  // +2 для \n и \0
    int row = 0;
    
    printf("\n=== ЗАГРУЗКА ПАТТЕРНА ИЗ STDIN ===\n");
    printf("Введите паттерн %dx%d (используйте '*' для живой клетки, пробел для мертвой):\n", HEIGHT, WIDTH);
    printf("(После ввода нажмите Ctrl+D для завершения)\n\n");
    
    // Читаем построчно из stdin
    while (row < HEIGHT && fgets(line, sizeof(line), stdin)) {
        for (int col = 0; col < WIDTH && line[col] != '\0' && line[col] != '\n'; col++) {
            if (line[col] == '*') {
                grid[row][col].status = 1;
            }
        }
        row++;
    }
    
    printf("\nЗагружено %d строк. Нажмите любую клавишу для начала...\n", row);
    getchar();  // Ждем нажатия клавиши
}