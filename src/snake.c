#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "snake.h"


// seed the random number generator with the current time
void seed_random_number()
{
	srand((unsigned int)time(NULL));
}

// generate a random number between 1 and 'max'
int generate_random_number(int max)
{
	int randomNumber = (rand() % max) + 1;

	return randomNumber;
}


void begin_ncurses(int *x, int *y)
{
	initscr();
	noecho();
	curs_set(0);

    // get terminal size
	int max_x, max_y;
	getmaxyx(stdscr, max_y, max_x);

    // set some terminal size limits
	if (max_x < 30 || max_y < 10) {
		printw("Increase the size of terminal\n");
		return;
	}

	*x = max_x;
	*y = max_y;
}

// end ncurses usage
void end_ncurses(WINDOW *win)
{
	if (!win) {
		endwin();
		return;
	}
	delwin(win);
	endwin();
}

void nc_refresh(void)
{
	refresh();
}


// create game arena 
WINDOW *border_creator(int x, int y, int score)
{

	// create border
	WINDOW *win = newwin(y, x, 0, 0);

	wborder(win,'x','x','x','x','x','x','x','x');
	mvwprintw(win,0 , x / 2 - 6," Score: %d ", score);
    mvwprintw(win, y- 1, x / 2 - 8, " PRESS Q TO QUIT ");
	wrefresh(win);

	return win;
}

// checking for body collision
int check_collision(point head[T_SIZE_T], int length, int x, int y)
{
    for (int i = 1; i < length; i++)
    {
        if (x == head[i].x && y == head[i].y)
        {
            return 1; // Collision detected
        }
    }
    return 0; // No collision
}

// shifting snake coords
void shift_snake(point head[T_SIZE_T],int length,int x, int y)
{
    for (int j = length; j> 0; j--)
        head[j] = head[j -1 ];
    
    head[0].x = x;
    head[0].y = y;
}

// drawing the snake on the gameboard
void draw_snake(WINDOW **win, point SNAKE[T_SIZE_T], int snake_length, int x, int y, int rand_x,int rand_y)
{
    delwin(*win);
    *win = border_creator(x, y, snake_length);
    for (int j = 0; j < snake_length; j++)
        mvwaddch(*win, SNAKE[j].y, SNAKE[j].x, 'o');

    mvwaddch(*win, rand_y, rand_x, 'i');

    wrefresh(*win);
}

/*
    Movement and keys:
        win = ncurses window
        x, y = ncurses window size
        score = scoreboard
*/
void moving_snake(WINDOW *win, int x, int y, int *score)
{
    char ch;
    direction_type currentDir = RIGHT;

    int snake_length = 1;
    int rand_x = generate_random_number(x - 2);
    int rand_y = generate_random_number(y - 2);

    point SNAKE[T_SIZE_T];
    SNAKE[0].x = x / 2;
    SNAKE[0].y = y / 2;

    int mov_x = SNAKE[0].x;
    int mov_y = SNAKE[0].y;

    while (1)
    {
        ch = wgetch(win);
        switch (ch)
        {
        case 'w':
            currentDir = UP;
            break;
        case 's':
            currentDir = DOWN;
            break;
        case 'a':
            currentDir = LEFT;
            break;
        case 'd':
            currentDir = RIGHT;
            break;
        case 'q':
            delwin(win);
            return;
        default:
            break;
        }


        mov_x = SNAKE[0].x;
        mov_y = SNAKE[0].y;
        if (currentDir == RIGHT)
			mov_x++;
		else if (currentDir == LEFT)
			mov_x--;
		else if (currentDir == UP)
			mov_y--;
		else if (currentDir == DOWN)
			mov_y++;

		// eat to grow big
        if (mov_y == rand_y && mov_x == rand_x)
        {
            rand_x = generate_random_number(x - 2);
            rand_y = generate_random_number(y - 2);
            *score = *score + 1;
            snake_length++;
        }

		int ok = check_collision(SNAKE,snake_length,mov_x,mov_y);
        if (ok)
            return;

		// border collision
        if (mov_y <= 0 || mov_y >= y - 1 || mov_x <= 0 || mov_x >= x - 1)
            return;

		// redraw snake and map
        shift_snake(SNAKE,snake_length, mov_x,mov_y);
        draw_snake(&win,SNAKE,snake_length,x,y,rand_x,rand_y);

        // automatic movement
        nodelay(win, TRUE);
        napms(250);
    }
}

void game_wrapper(int *table)
{
    seed_random_number();
    int x = 0, y = 0, score = 1;
    WINDOW *win;

    begin_ncurses(&x, &y);

    win = border_creator(x, y, score);
    moving_snake(win, x, y, &score);
    
    end_ncurses(win);
    clear();
    *table = score;
}