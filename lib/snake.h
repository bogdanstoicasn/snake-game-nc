#ifndef SNAKE_H
#define SNAKE_H

#define T_SIZE_T 8192

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
void shift_snake(point head[T_SIZE_T],int length,int x, int y);
void draw_snake(WINDOW **win, point SNAKE[T_SIZE_T], int snake_length, int x, int y, int rand_x,int rand_y);

int check_collision(point head[T_SIZE_T], int length, int x, int y);
void game_wrapper(int *table);

#endif