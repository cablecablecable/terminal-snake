#include "game_logic.h"

#include <iostream>
#include <vector>

//some game rules
constexpr int max_cols = 70;
constexpr int max_rows = 10;
constexpr int max_apples = 20;

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
char gameArray[max_rows][max_cols];

//resizable array of apples stored in coord structs
std::vector<coord> applesCollection;

//resizable array of snake body parts stored in coord structs
std::vector<coord> snakeBodyCollection;

//snake head location
coord snakeHead;


bool isApple(const coord& currentCoords)
{
    //for each coord in applesCollection, return true if the row AND col matches any coord
    for (const coord& appleCoords : applesCollection)
    {
        if (currentCoords == appleCoords)
            return true;
    }
    return false;
}

bool isSnakeBody(const coord& currentCoords)
{
    //for each coord in snakeBodyCollection, return true if the row AND col matches any coord
    for (const coord& bodyCoords : snakeBodyCollection)
    {
        if (currentCoords == bodyCoords)
            return true;
    }
    return false;
}

bool isSnakeHead(const coord& currentCoords)
{
    //return true if arguments match snakeHead's row AND column
    return currentCoords == snakeHead;
}

bool isEdge(const coord& currentCoords)
{
    //return true if row/col equals 0, OR(inclusive) equals max_rows
    return (currentCoords.row == 0 || currentCoords.row == max_rows - 1) ||
           (currentCoords.col == 0 || currentCoords.col == max_cols - 1);
}

void insertCharsToArray()
{
    //for each row in gameArray, insert into every column a char based on what it is determined by function calls
    for (int i = 0; i < max_rows; i++)
    {
        for (int j = 0; j < max_cols; j++)
        {
            //store the current coords into the coord struct for easy and fast pass by reference
            coord currentCoords = {i, j};
            if      (isEdge(currentCoords))      { gameArray[i][j] = '#'; }
            else if (isApple(currentCoords))     { gameArray[i][j] = '@'; }
            else if (isSnakeHead(currentCoords)) { gameArray[i][j] = '%'; }
            else if (isSnakeBody(currentCoords)) { gameArray[i][j] = 'O'; }
            else                                 { gameArray[i][j] = ' '; }
        }
    }
}

void draw()
{
    //draw everything to the terminal
    //for each row in gameArray, print every column: gameArray[row][column]
    for (int i = 0; i < max_rows; i++)
    {
        for (int j = 0; j < max_cols; j++)
        {
            std::cout << gameArray[i][j];
        }
        std::cout << "\n"; //newline after each row is drawn
    }
}

int main()
{
    snakeBodyCollection.emplace_back(5, 20);
    snakeBodyCollection.emplace_back(6, 21);
    snakeBodyCollection.emplace_back(7, 22);
    snakeHead = {5, 10};
    applesCollection.emplace_back(8, 45);


    insertCharsToArray();
    draw();

    coord foo = {5, 5};
    coord bar = {5, 6};

    (foo == bar) ? std::cout << "true" : std::cout << "false";


}
