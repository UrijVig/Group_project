#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include "grid.h"
#include "patterns.h"
#include "ncurses_utils.h"
#include "game_logic.h"
#include "input_handler.h"

void print_usage(char *program_name) {
    printf("ИГРА \"ЖИЗНЬ\" - ИНСТРУКЦИЯ ПО ЗАПУСКУ\n");
    printf("====================================\n\n");
    printf("Режимы запуска:\n");
    printf("  %s              - интерактивный выбор режима\n", program_name);
    printf("  %s [1-5]        - запуск с готовым паттерном\n", program_name);
    printf("  %s stdin        - запуск с загрузкой из stdin\n", program_name);
    printf("  cat file.txt | %s stdin - загрузка из файла\n", program_name);
    printf("\n");
    printf("Готовые паттерны:\n");
    printf("  1 - Планер (Glider) - движущаяся фигура\n");
    printf("  2 - Мигалка (Blinker) - осциллятор\n");
    printf("  3 - Блок (Block) - стабильная фигура\n");
    printf("  4 - Улей (Beehive) - стабильная фигура\n");
    printf("  5 - Ружье Госпера (Gosper Glider Gun) - генератор планеров\n");
    printf("\n");
    printf("Управление в игре:\n");
    printf("  A - увеличить скорость\n");
    printf("  Z - уменьшить скорость\n");
    printf("  Пробел - выход\n");
    printf("\n");
}

int select_interactive_mode() {
    int choice;
    printf("\n=== ИНТЕРАКТИВНЫЙ ВЫБОР РЕЖИМА ===\n\n");
    printf("Выберите способ инициализации:\n");
    printf("1 - Загрузить готовый паттерн\n");
    printf("2 - Ввести паттерн вручную (stdin)\n");
    printf("0 - Выход\n\n");
    printf("Ваш выбор: ");
    
    scanf("%d", &choice);
    getchar();  // Убираем \n из буфера
    
    return choice;
}

int select_pattern() {
    int pattern;
    printf("\n=== ВЫБОР ГОТОВОГО ПАТТЕРНА ===\n\n");
    printf("Доступные паттерны:\n");
    printf("1 - Планер (Glider)\n");
    printf("2 - Мигалка (Blinker)\n");
    printf("3 - Блок (Block)\n");
    printf("4 - Улей (Beehive)\n");
    printf("5 - Ружье Госпера (Gosper Glider Gun)\n\n");
    printf("Введите номер паттерна (1-5): ");
    
    scanf("%d", &pattern);
    getchar();  // Убираем \n из буфера
    
    return pattern;
}

int main(int argc, char *argv[]) {
    srand(time(NULL));
    
    struct cell grid[HEIGHT][WIDTH];
    int next[HEIGHT][WIDTH];
    int generation = 0;
    int speed = DELAY_MAX / 2;
    int running = 1;
    int use_stdin = 0;
    int pattern = 1;
    
    // Если нет аргументов - показываем инструкцию и переходим в интерактивный режим
    if (argc == 1) {
        print_usage(argv[0]);
        
        int mode = select_interactive_mode();
        
        if (mode == 0) {
            printf("Выход из программы.\n");
            return 0;
        } else if (mode == 1) {
            pattern = select_pattern();
            if (pattern < 1 || pattern > 5) {
                printf("Ошибка: неверный номер паттерна. Используется паттерн 1.\n");
                pattern = 1;
            }
        } else if (mode == 2) {
            use_stdin = 1;
        } else {
            printf("Ошибка: неверный выбор. Используется паттерн 1.\n");
            pattern = 1;
        }
    } 
    // Обработка аргументов командной строки
    else if (argc == 2) {
        if (strcmp(argv[1], "stdin") == 0 || strcmp(argv[1], "0") == 0) {
            use_stdin = 1;
        } else {
            pattern = atoi(argv[1]);
            if (pattern < 1 || pattern > 5) {
                printf("Ошибка: неверный номер паттерна. Используйте число от 1 до 5.\n");
                print_usage(argv[0]);
                return 1;
            }
        }
    } else {
        print_usage(argv[0]);
        return 1;
    }
    
    // Инициализация ncurses
    init_ncurses();
    WINDOW *gamewin = create_game_window();
    
    // Загрузка паттерна
    if (use_stdin) {
        // Временно выходим из ncurses для ввода
        endwin();
        load_from_stdin(grid);
        // Возвращаемся в ncurses
        init_ncurses();
        gamewin = create_game_window();
    } else {
        load_pattern(grid, pattern);
    }
    
    // Игровой цикл
    while (running) {
        generation++;
        
        count_neighbour(grid);
        compute_next_generation(grid, next);
        draw_grid(gamewin, grid);
        apply_next_generation(grid, next);
        
        int live = count_live_cells(grid);
        draw_info(gamewin, generation, live, speed);
        wrefresh(gamewin);
        
        if (live == 0) {
            draw_game_over(gamewin);
            sleep(2);
            break;
        }
        
        handle_input(&speed, &running);
        usleep(speed);
    }
    
    cleanup_ncurses(gamewin);
    printf("\nИгра завершена! Всего поколений: %d\n", generation);
    return 0;
}