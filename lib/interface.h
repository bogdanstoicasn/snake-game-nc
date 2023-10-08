#ifndef INTERFACE_h
#define INTERFACE_H

void init_menu_window();
void end_menu_window();
void print_large_text(int *x, int *y);
void game_over_window(int max_x, int max_y, int score, int best_score);

void score_data(int *best_score);
void save_data(int *best_score, int *score);

#endif