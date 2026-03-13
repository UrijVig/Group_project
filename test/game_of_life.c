#include <stdio.h>
#include <stdlib.h>

// ограничение поля
#define WIDTH 80
#define HEIGHT 25

// структура, описывающая клетку
struct cell
{
    int status; // жива не жива
    int neighbour; // количество живых соседей
};

void start_game(struct cell grid[HEIGHT][WIDTH]); // функция для старта игры
void count_neighbour(struct cell grid[HEIGHT][WIDTH]); // подсчёт соседей
int print(struct cell grid[HEIGHT][WIDTH]); // отрисовка


int main(){
    struct cell grid[HEIGHT][WIDTH]; // создание матрицы из клеток
    int generation = 0; // счётчик поколений
    start_game(grid); // инициализация игры

    // бесконечный цикл
    while (1)
    {
       generation++; 

       count_neighbour(grid);

       if (print(grid) == 0){
            printf("the game is over! Generation = %d", generation); // окончание игры при смерти всех клеток
            return 0;
       }
    }
    return 0;
    
}

void start_game(struct cell grid[HEIGHT][WIDTH]){
    // обнуление всех данных матрицы
    for (int i = 0; i < HEIGHT; i++)
    {
        for (int j = 0; j < WIDTH; j++)
        {
            grid[i][j].status = 0;
            grid[i][j].neighbour = 0;
        }
        
    }

    // инициализация первых живых клеток (вручную, для бесконечной генерации)
    int i0 = HEIGHT/2;
    int j0 = WIDTH/2;
    grid[i0][j0+1].status = 1;
    grid[i0+1][j0+2].status = 1;
    grid[i0+2][j0].status = 1;
    grid[i0+2][j0+1].status = 1;
    grid[i0+2][j0+2].status = 1;
    

}


void count_neighbour(struct cell grid[HEIGHT][WIDTH]){

    // Подсчёт соседей
    for (int i = 0; i < HEIGHT; i++)
    {
        for (int j = 0; j < WIDTH; j++)
        {
            // Если клетка жива, она передайт сигнал соседни клеткам 
            if (grid[i][j].status == 1)
            {
                grid[(i + HEIGHT - 1) % HEIGHT][(j + 1)%WIDTH].neighbour++;
                grid[(i + HEIGHT - 1) % HEIGHT][j].neighbour++;
                grid[(i + HEIGHT - 1) % HEIGHT][(j + WIDTH - 1) % WIDTH].neighbour++;
                grid[i][(j + WIDTH - 1) % WIDTH].neighbour++;
                grid[i][(j + 1)%WIDTH].neighbour++;
                grid[(i + 1)%HEIGHT][(j + WIDTH - 1) % WIDTH].neighbour++;
                grid[(i + 1)%HEIGHT][j].neighbour++;
                grid[(i+ 1)%HEIGHT][(j + 1)%WIDTH].neighbour++;
            }
            
        }
        
    }
}

int print(struct cell grid[HEIGHT][WIDTH]){
    int live = 0; // счётчик живых клеток
    for (int i = 0; i < HEIGHT; i++)
    {
        for (int j = 0; j < WIDTH; j++) {
            int n = grid[i][j].neighbour; // ввод переменной отвечающей за кол-во соседей
            int new_status; // переменная отвечающая за стату
            
            // в зависимости от статуса клетки, проверяем наличие и количество соседей, изменяя или сохраняя статус
            if (grid[i][j].status == 1) {
                new_status = (n == 2 || n == 3) ? 1 : 0;
            } else {
                new_status = (n == 3) ? 1 : 0;
            }
            
            // отрисовываем клетку, согласно статусу
            printf("%c", grid[i][j].status ? '*' : ' ');
            
            // Изменяем данные для следующего поколения
            grid[i][j].status = new_status;
            grid[i][j].neighbour = 0;
            
            // изменяем количество живых клеток
            if (new_status) live++;
        }

        
            printf("\n");
        
    }
    return live;
}