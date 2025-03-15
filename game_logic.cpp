#include "game_logic.h"

#include <array>
#include <iostream>
#include <vector>

constexpr int max_cols = 70;
constexpr int max_rows = 20;
constexpr int max_apples = 20;

//array of actual characters to be printed
char gameArray[max_rows][max_cols];

//resizable array of apple coords of std::pairs
std::vector<std::pair<int, int>> applesCollection;

//resizable array of snake body parts of std::pairs
std::vector<std::pair<int, int>> snakeBodyCollection;

//snake head location
std::pair<int, int> snakeHead;



bool isApple(int row, int col)
{
    //for each coordinate pair in applesCollection, return true if the row AND col matches any pair
    for (std::pair<int, int>& appleCoords : applesCollection)
    {
        if (appleCoords.first == row && appleCoords.second == col)
            return true;
    }
    return false;
}

bool isSnakeBody(int row, int col)
{
    //for each coordinate pair in snakeBodyCollection, return true if the row AND col matches any pair
    for (std::pair<int, int>& bodyCoords : snakeBodyCollection)
    {
        if (bodyCoords.first == row && bodyCoords.second == col)
            return true;
    }
    return false;
}

bool isSnakeHead(int row, int col)
{
    //return true if arguments match snakeHead's row AND column
    return (snakeHead.first == row) && (snakeHead.second == col);
}

bool isEdge(int row, int col)
{
    //return true if row/col equals 0, OR(inclusive) equals max_rows
    return (row == 0 || row == max_rows - 1) || (col == 0 || col == max_cols - 1);
}

void insertCharsToArray()
{
    //for each row in gameArray, insert into every column a char based on what it is determined by function calls
    for (int i = 0; i < max_rows; i++)
    {
        for (int j = 0; j < max_cols; j++)
        {
            if      (isEdge(i, j))      { gameArray[i][j] = '#'; }
            else if (isApple(i, j))     { gameArray[i][j] = '@'; }
            else if (isSnakeHead(i, j)) { gameArray[i][j] = '%'; }
            else if (isSnakeBody(i, j)) { gameArray[i][j] = 'O'; }
            else                                { gameArray[i][j] = ' '; }
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
    snakeBodyCollection.emplace_back(15, 20);
    snakeBodyCollection.emplace_back(15, 21);
    snakeBodyCollection.emplace_back(15, 22);
    snakeHead = {5, 10};
    applesCollection.emplace_back(8, 45);

    insertCharsToArray();
    draw();
}
