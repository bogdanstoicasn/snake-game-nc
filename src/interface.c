#include "interface.h"
#include <stdio.h>
#include <ncurses.h>
#include <unistd.h>

void init_menu_window()
{
    initscr();
    noecho();
    curs_set(0);
}

void end_menu_window()
{
    endwin();
}

void print_large_text(int *x, int *y)
{
    clear();
    attron(A_BOLD);
    attron(A_STANDOUT);
    attron(A_ITALIC);
    attron(A_UNDERLINE);

    int max_x = 0, max_y = 0;
    getmaxyx(stdscr, max_y, max_x);
    *x = max_x;
    *y = max_y;

    box(stdscr,0, 0);
    mvprintw(max_y / 2 - 7, max_x / 2 - 2, " SNAKE ");
    attroff(A_ITALIC);
    attroff(A_UNDERLINE);

    attroff(A_STANDOUT);
    mvprintw(max_y / 2 + 2, max_x / 2 - 10, "Quit(Q/q) or Play(ENTER)");
    attroff(A_BOLD);

    mvprintw(max_y - 1, max_x / 2 - 6, " w,a,s,d movement ");

    refresh();

}

void game_over_window(int max_x, int max_y, int score, int best_score)
{
    attron(A_BOLD);
    mvprintw(max_y / 2 - 7, max_x / 2 - 4, " GAME OVER ");
    attroff(A_BOLD);
    mvprintw(max_y / 2 - 4, max_x / 2 - 3, " Score: %d", score);
    mvprintw(max_y / 2 - 3, max_x / 2 - 6, " Best score: %d", best_score);
    refresh();
    napms(4000);
}

void score_data(int *best_score)
{
    FILE *fp = fopen("score_data.txt", "r");
    if (!fp) {
        fp = fopen ("score_data.txt", "w");
        fprintf(fp,"0");
        fclose(fp);
        return;
    }
    fscanf(fp,"%d", best_score);
    fclose(fp);
}
void save_data(int *best_score, int *score)
{
    if (*score < *best_score)
        return;

    FILE *fp = fopen("score_data.txt", "w");
    if (!fp)
        return;
    
    fprintf(fp,"%d", *score);
    *best_score = *score;
    fclose(fp);
}
