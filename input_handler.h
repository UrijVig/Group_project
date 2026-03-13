#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

#define DELAY_MIN 10000
#define DELAY_MAX 500000
#define DELAY_STEP 20000

void adjust_speed(int *speed, int delta);
void handle_input(int *speed, int *running);

#endif