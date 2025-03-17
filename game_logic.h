#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H

struct coord;

bool is_snake_head(const coord& current_coord);
bool is_snake_body(const coord& current_coord);
bool is_apple(const coord& current_coord);
bool is_edge(const coord& current_coord);
int random_number(int min, int max);
void insert_generated_apples();
void ask_for_direction();
void snake_move();
void snake_eat();
void game_init();
void draw_game_array();
bool check_game_lose();
bool check_game_win();
void print_apples_eaten();


#endif //GAME_LOGIC_H
