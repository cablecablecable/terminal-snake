#include "game_logic.h"

#include <iostream>
#include <vector>
#include <random>
#include <string>

//game constants
constexpr int MAX_COLS = 70;
constexpr int MAX_ROWS = 10;
constexpr int MAX_APPLES = 20; //538 is the max for now

//important game variables
int apple_count;
std::string direction;

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


//array of actual characters to be printed
char game_array[MAX_ROWS][MAX_COLS];

//resizable array of apples stored in coord structs
std::vector<coord> apples_collection;

//resizable array of snake parts stored in coord structs
std::vector<coord> snake_parts_collection;


bool is_apple(const coord& current_coord)
{
    //for each apple_collection element, return true if current_coord matches
    for (coord apple_coord : apples_collection)
    {
        if (current_coord == apple_coord)
            return true;
    }
    return false;
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

bool is_snake_head(const coord& current_coord)
{
    //return true if the current coord is equal to the head of the snake that is always snake_parts_collection[0]
    return current_coord == snake_parts_collection[0];
}

bool is_edge(const coord& current_coord)
{
    //return true if row/col equals 0, OR equals max_rows
    return (current_coord.row == 0 || current_coord.row == MAX_ROWS - 1) ||
           (current_coord.col == 0 || current_coord.col == MAX_COLS - 1);
}

int random_number(int min, int max)
{
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
        //random number bounded to prevent edge generation altogether
        new_apple = { random_number(1, MAX_ROWS - 2), random_number(1, MAX_COLS - 2) };

        //if new_apple is not equal to an existing apple, snake body, and snake head, break the loop and return it
        if (!(is_apple(new_apple)) && !(is_snake_body(new_apple)) && !(is_snake_head(new_apple)))
            break;
    }
    return new_apple;
}

void insert_apples()
{
    //generates and inserts apples into apples_collection until apple_count == MAX_APPLES
    while (apple_count < MAX_APPLES)
    {
        apples_collection.emplace_back(generate_apple());
        apple_count = static_cast<int>(apples_collection.size());
    }
}

void direction_input()
{
    std::cout << "\nDirection (wasd): ";
    char user_input;
    std::cin >> user_input;

    switch (user_input)
    {
        case 'w': { direction = "UP";    break;}
        case 'a': { direction = "LEFT";  break;}
        case 's': { direction = "DOWN";  break;}
        case 'd': { direction = "RIGHT"; break;}
        default:  { break; }
    }
}



void init()
{
    direction = "LEFT";
}

void insert_chars()
{
    //for each row in gameArray, insert into every column a char based on what it is determined by function calls
    for (int i = 0; i < MAX_ROWS; i++)
    {
        for (int j = 0; j < MAX_COLS; j++)
        {
            //store the current coords into the coord struct for easy and fast pass by reference
            coord current_coord = {i, j};
            if      (is_edge(current_coord))       { game_array[i][j] = '*'; }
            else if (is_apple(current_coord))      { game_array[i][j] = '@'; }
            else if (is_snake_head(current_coord)) { game_array[i][j] = '%'; }
            else if (is_snake_body(current_coord)) { game_array[i][j] = 'O'; }
            else                                   { game_array[i][j] = ' '; }
        }
    }
}

void draw()
{
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
    snake_parts_collection.emplace_back(5, 19);
    snake_parts_collection.emplace_back(5, 20);
    snake_parts_collection.emplace_back(5, 21);
    snake_parts_collection.emplace_back(5, 22);
    snake_parts_collection.emplace_back(5, 23);
    snake_parts_collection.emplace_back(5, 24);
    snake_parts_collection.emplace_back(5, 25);

    insert_apples();



    insert_chars();
    draw();


}
