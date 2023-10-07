#ifndef INTERFACE_H
#define INTERFACE_H

#define DELAY 30000
#define TIMEOUT 10

typedef struct _win_st WINDOW;
typedef struct  point point;


void seed_random_number();
int generate_random_number(int max);

void begin_ncurses(int *x, int *y);
void end_ncurses(WINDOW *win);
void nc_refresh(void);

WINDOW *border_creator(int x, int y, int score);
void moving_snake(WINDOW *win, int x, int y, int *score);
void auto_move_snake(WINDOW *win,int x, int y, int *score);
void drawPart(WINDOW *win, point drawPoint);

#endif