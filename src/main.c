#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include "snake.h"
#include "interface.h"

int main()
{
    int x = 0, y = 0, score = 0, ok = 0, best_score = 0;
    char ch;
    init_menu_window();
    score_data(&best_score);

    while(1) {
        print_large_text(&x, &y);
        ch = getchar();
        switch(ch) {
        case 'Q':
            ok = 1;
            break;
        case 'q':
            ok = 1;
            break;
        case '\n':
            game_wrapper(&score);
            save_data(&best_score, &score);
            game_over_window(x,y,score, best_score);
            break;
        case '\r':
            game_wrapper(&score);
            save_data(&best_score, &score);
            game_over_window(x,y,score, best_score);
            break;
        default:
            break;
        }
        if (ok == 1)
            break;
    }


    end_menu_window();
    return 0;
}