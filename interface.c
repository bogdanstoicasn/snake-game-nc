#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "interface.h"



void seed_random_number()
{
	// Seed the random number generator with the current time
	srand((unsigned int)time(NULL));
}

int generate_random_number(int max)
{
	// Generate a random number between 1 and 'max'
	int randomNumber = (rand() % max) + 1;

	return randomNumber;
}


void begin_ncurses(int *x, int *y)
{
	initscr();
	noecho();
	curs_set(0);
	timeout(TIMEOUT);
	int max_x, max_y;
	getmaxyx(stdscr, max_y, max_x);

	if (max_x < 30 || max_y < 10) {
		printw("Increase the size of terminal\n");
		return;
	}

	*x = max_x;
	*y = max_y;
}

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


// bagat in jocul propriu-zis: snake.c/snake.h 
WINDOW *border_creator(int x, int y, int score)
{

	// create border
	WINDOW *win = newwin(y, x, 0, 0);

	wborder(win,'x','x','x','x','x','x','x','x');
	mvwprintw(win,0, x / 2 - 6," Score: %d ", score);
	wrefresh(win);

	return win;
}

int check_collision(point head[128], int length, int x, int y)
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

void shift_snake(point head[128],int length,int x, int y)
{
    for (int j = length; j> 0; j--)
        head[j] = head[j -1 ];
    
    head[0].x = x;
    head[0].y = y;
}

void draw_snake(WINDOW **win, point SNAKE[128], int snake_length, int x, int y, int rand_x,int rand_y)
{
    delwin(*win);
    *win = border_creator(x, y, snake_length);
    for (int j = 0; j < snake_length; j++)
        mvwaddch(*win, SNAKE[j].y, SNAKE[j].x, 'o');

    mvwaddch(*win, rand_y, rand_x, 'i');

    wrefresh(*win);
}

void moving_snake(WINDOW *win, int x, int y, int *score)
{
    char click_mover;
    direction_type current_dirr = RIGHT;

    int snake_length = 1;
    int rand_x = generate_random_number(x - 2);
    int rand_y = generate_random_number(y - 2);

    point SNAKE[128];
    SNAKE[0].x = x / 2;
    SNAKE[0].y = y / 2;

    int mov_x = SNAKE[0].x;
    int mov_y = SNAKE[0].y;

    while (1)
    {
        click_mover = wgetch(win);
        switch (click_mover)
        {
        case 'w':
            mov_y--;
            break;
        case 's':
            mov_y++;
            break;
        case 'a':
            mov_x--;
            break;
        case 'd':
            mov_x++;
            break;
        case 'q':
            delwin(win);
            return;
        default:
            break;
        }

        shift_snake(SNAKE, snake_length,mov_x,mov_y);

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
        if (mov_y == 0 || mov_y == y - 1 || mov_x == 0 || mov_x == x - 1)
            return;

		// redraw snake and map
        draw_snake(&win,SNAKE,snake_length,x,y,rand_x,rand_y);


        // delwin(win);
        // win = border_creator(x, y, *score);

        // for (int j = 0; j < snake_length; j++)
        // {
        //     mvwaddch(win, SNAKE[j].y, SNAKE[j].x, 'o');
        // }

        // mvwaddch(win, rand_y, rand_x, 'i');

        // wrefresh(win);
        
    }
}
