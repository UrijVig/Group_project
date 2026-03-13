#include "input_handler.h"
#include <ncurses.h>

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