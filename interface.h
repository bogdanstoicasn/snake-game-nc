#ifndef INTERFACE_H
#define INTERFACE_H

#define DELAY 30000
#define TIMEOUT 10

typedef struct _win_st WINDOW;

typedef struct point
{
	int x;
	int y;
} point;

typedef enum
{
	LEFT,
	RIGHT,
	UP,
	DOWN
} direction_type;

void seed_random_number();
int generate_random_number(int max);

void begin_ncurses(int *x, int *y);
void end_ncurses(WINDOW *win);
void nc_refresh(void);

WINDOW *border_creator(int x, int y, int score);
void moving_snake(WINDOW *win, int x, int y, int *score);
void auto_move_snake(WINDOW *win,int x, int y, int *score);
int check_collision(point head[128], int length, int x, int y);
void shift_snake(point head[128],int length,int x, int y);
void draw_snake(WINDOW **win, point SNAKE[128], int snake_length, int x, int y, int rand_x,int rand_y);

#endif