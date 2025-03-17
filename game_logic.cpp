#include "game_logic.h"

#include <iostream>
#include <vector>
#include <random>
#include <string>

//coordinate pair struct, stores rows and columns obviously
struct coord
{
    int row{};
    int col{};
};

//operator== overload for comparing two coord structs
bool operator==(const coord& lhs, const coord& rhs)
{
    return (lhs.row == rhs.row) && (lhs.col == rhs.col);
}

//game constants
constexpr int MAX_COLS = 20;
constexpr int MAX_ROWS = 10;
constexpr int MAX_APPLES = 2;

//important game variables
int apple_count;
char direction;
coord old_snake_tail;


//array of actual characters to be printed
char game_array[MAX_ROWS][MAX_COLS];

//resizable array of apples stored in coord structs
std::vector<coord> apples_collection;

//resizable array of snake parts stored in coord structs
std::vector<coord> snake_parts_collection;

bool is_snake_head(const coord& current_coord)
{
    //return true if the current coord is equal to the head of the snake that is always snake_parts_collection[0]
    return current_coord == snake_parts_collection[0];
}

bool is_snake_body(const coord& current_coord)
{
    //for each snake_parts_collection element, return true if current_coord matches
    for (coord part_coord : snake_parts_collection)
    {
        if (current_coord == part_coord)
            return true;
    }
    return false;
}

bool is_apple(const coord& current_coord)
{
    //for each apple_collection element, return true if current_coord matches
    for (int i = 0; i < apples_collection.size(); i++)
    {
        //for the snake_eat function, if the current_coord is also the snake head,
        //remove the apple from the array as well
        if (current_coord == apples_collection[i] && is_snake_head(current_coord))
        {
            apples_collection.erase(apples_collection.begin() + i);
            return true;
        }

        if (current_coord == apples_collection[i])
            return true;
    }
    return false;
}

bool is_edge(const coord& current_coord)
{
    //return true if row/col equals 0, OR equals max_rows
    return (current_coord.row == 0 || current_coord.row == MAX_ROWS - 1) ||
           (current_coord.col == 0 || current_coord.col == MAX_COLS - 1);
}

int random_number(int min, int max)
{
    //seed the PRNG mt19937 with a random device at runtime then return that from a range of min-max
    static std::random_device random_device;
    static std::mt19937 gen(random_device());
    std::uniform_int_distribution<> distribution(min, max);
    return distribution(gen);
}

coord generate_apple()
{
    //infinitely loops until an apple of unique coords is generated
    coord new_apple;
    while (true)
    {
        //random number bounded to prevent edge generation altogether, MAX - 3 because arrays are 0 indexed,
        //i.e. a MAX_COL of 70 has coordinates of 0-69 so the center of that is 1-68
        new_apple = { random_number(1, MAX_ROWS - 2), random_number(1, MAX_COLS - 2) };

        //if new_apple is not equal to an existing apple and snake part, break the loop and return it
        if (!(is_apple(new_apple)) && !(is_snake_body(new_apple)) && !(is_snake_head(new_apple)))
            break;
    }
    return new_apple;
}

void insert_generated_apples()
{
    //generate and insert an apple if apple_count is less than MAX_APPLES, then update apple count
    while (apple_count < MAX_APPLES)
    {
        apples_collection.emplace_back(generate_apple());
        apple_count = static_cast<int>(apples_collection.size());
    }
}

void ask_for_direction()
{
    //obtain a user input for direction after each turn by assigning it to the direction char
    std::cout << "Direction (wasd): ";
    char user_input;
    std::cin >> user_input;

    //error handling to prevent the snake head from moving in on itself
    if (user_input == 'w' && direction == 's')
        return;
    if (user_input == 's' && direction == 'w')
        return;
    if (user_input == 'a' && direction == 'd')
        return;
    if (user_input == 'd' && direction == 'a')
        return;

    switch (user_input)
    {
        case 'w': { direction = 'w';    break;}
        case 'a': { direction = 'a';  break;}
        case 's': { direction = 's';  break;}
        case 'd': { direction = 'd'; break;}
        default:  { break; }
    }
}

void snake_insert_new_head()
{
    const auto snake_head_position = snake_parts_collection.begin() + 0;
    coord old_snake_head = snake_parts_collection[0];

    //insert new head based off old_snake_head and what the direction is currently specified as
    switch (direction)
    {
        case 'w':
        {
            snake_parts_collection.insert(snake_head_position,
                {old_snake_head.row - 1, old_snake_head.col});
            break;
        }
        case 'a':
        {
            snake_parts_collection.insert(snake_head_position,
                {old_snake_head.row, old_snake_head.col - 1});
            break;
        }
        case 's':
        {
            snake_parts_collection.insert(snake_head_position,
                {old_snake_head.row + 1, old_snake_head.col});
            break;
        }
        case 'd':
        {
            snake_parts_collection.insert(snake_head_position,
                {old_snake_head.row, old_snake_head.col + 1});
            break;
        }
        default:
        {
            break;
        }
    }
}

void snake_move()
{
    //store old tail location before removing (important for snake_eat)
    old_snake_tail = snake_parts_collection.back();

    //remove the old tail of the snake
    snake_parts_collection.pop_back();

    //now inserting a new head essentially moves the one tile in the game grid
    snake_insert_new_head();
}

void snake_eat()
{
    //the is_apple function will recognize that it is the snake head and will remove that apple from the array
    if (is_apple(snake_parts_collection[0]))
    {
        //replace that previous "ghost" snake tail
        snake_parts_collection.emplace_back(old_snake_tail);
        apple_count = static_cast<int>(apples_collection.size());
    }
}

void game_init()
{
    //set the initial direction to be moving left and creates one head and body part
    direction = 'a';
    constexpr int MIDDLE_ROW = MAX_ROWS / 2;
    constexpr int MIDDLE_COL = MAX_COLS / 2;

    snake_parts_collection.emplace_back(MIDDLE_ROW, MIDDLE_COL);
    snake_parts_collection.emplace_back(MIDDLE_ROW, MIDDLE_COL + 1);
    snake_parts_collection.emplace_back(MIDDLE_ROW, MIDDLE_COL + 2);
}

void draw_game_array()
{
    //for each row in game_array, insert into every column a char based on what it is determined by function calls
    for (int i = 0; i < MAX_ROWS; i++)
    {
        for (int j = 0; j < MAX_COLS; j++)
        {
            //store the current coords into the coord struct for inexpensive pass by ref into the is_ functions
            coord current_coord = {i, j};
            if      (is_edge(current_coord))       { game_array[i][j] = '#'; }
            else if (is_apple(current_coord))      { game_array[i][j] = '@'; }
            else if (is_snake_head(current_coord)) { game_array[i][j] = '%'; }
            else if (is_snake_body(current_coord)) { game_array[i][j] = 'O'; }
            else                                   { game_array[i][j] = ' '; }
        }
    }


    //draw everything to the terminal
    //for each row in gameArray, print every column: gameArray[row][column]
    for (int i = 0; i < MAX_ROWS; i++)
    {
        for (int j = 0; j < MAX_COLS; j++)
        {
            std::cout << game_array[i][j];
        }
        std::cout << "\n"; //newline after each row is drawn
    }
}

int main()
{
    game_init();

    insert_generated_apples();

    draw_game_array();

    while (true)
    {
        ask_for_direction();
        snake_move();
        snake_eat();

        insert_generated_apples();

        draw_game_array();
    }

}
