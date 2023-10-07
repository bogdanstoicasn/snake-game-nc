#include <stdio.h>
#include "interface.h"

int main()
{
    seed_random_number();

    int x = 0, y = 0, score = 1;
    WINDOW *win;

    begin_ncurses(&x, &y);

    win = border_creator(x, y, score);
    moving_snake(win, x, y, &score);
    
    end_ncurses(win);
    return 0;
}