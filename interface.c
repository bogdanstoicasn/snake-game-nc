#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "interface.h"




typedef struct point
{
	int x;
	int y;
} point;

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

int check_collision(point head, point body[], int length)
{
    for (int i = 0; i < length; i++)
    {
        if (head.x == body[i].x && head.y == body[i].y)
        {
            return 1; // Collision detected
        }
    }
    return 0; // No collision
}

void moving_snake(WINDOW *win, int x, int y, int *score)
{
    char click_mover;

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
        }

        for (int j = snake_length; j > 0; j--)
        {
            SNAKE[j] = SNAKE[j - 1];
        }
        SNAKE[0].x = mov_x;
        SNAKE[0].y = mov_y;

		// eat to grow big
        if (mov_y == rand_y && mov_x == rand_x)
        {
            rand_x = generate_random_number(x - 2);
            rand_y = generate_random_number(y - 2);
            *score = *score + 1;
            snake_length++;
        }

		// collision with the body
		for (int j = 1; j < snake_length; j++)
            if (mov_x == SNAKE[j].x && mov_y == SNAKE[j].y)
                return;
		
		// border collision
        if (mov_y == 0 || mov_y == y - 1 || mov_x == 0 || mov_x == x - 1)
            return;

		// redraw snake and map
        delwin(win);
        win = border_creator(x, y, *score);

        for (int j = 0; j < snake_length; j++)
        {
            mvwaddch(win, SNAKE[j].y, SNAKE[j].x, 'o');
        }

        mvwaddch(win, rand_y, rand_x, 'i');

        wrefresh(win);
    }
}
