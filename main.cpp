#include <iostream>
#include <cstdlib>
#include "game_logic.h"

int main()
{
    game_init();
    insert_generated_apples();

    while (true)
    {
        draw_game_array();

        print_apples_eaten();
        ask_for_direction();
        snake_move();
        snake_eat();

        insert_generated_apples();

        draw_game_array();

        if (check_game_lose())
        {
            system("clear");
            draw_game_array();
            std::cout << "\nYOU LOSE!!!" << std::endl;
            break;
        }

        if (check_game_win())
        {
            system("clear");
            draw_game_array();
            std::cout << "\nYOU WIN!!!" << std::endl;
            break;
        }
        system("clear");
    }
}
