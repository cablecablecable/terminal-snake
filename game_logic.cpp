#include "game_logic.h"

#include <array>
#include <iostream>
#include <vector>

constexpr int MAX_COLS = 50;
constexpr int MAX_ROWS = 20;
constexpr int MAX_APPLES = 20;

char gameArray[MAX_ROWS][MAX_COLS]; //array of actual characters to be printed
std::vector<std::pair<int, int>> appleArray(MAX_APPLES); //array of apple coords objects of std::pair type





bool isApple()

bool isSnakeBody()


bool isSnakeHead();

bool isEdge(int row, int col)
{
    //if position is at edge then return true
    return (row == 0 || row == MAX_ROWS - 1) || (col == 0 || col == MAX_COLS - 1);
}

void insertCharsToArray()
{
    //for each gameRows, insert by the number of columns specified
    for (int i = 0; i < MAX_ROWS; i++)
    {
        for (int j = 0; j < MAX_COLS; j++)
        {
            if (isEdge(i, j))
            {
                gameArray[i][j] = '#';
            }
            else
                gameArray[i][j] = ' ';
        }
    }
}

void draw()
{
    //draw every element to the terminal
    for (int i = 0; i < MAX_ROWS; i++)
    {
        for (int j = 0; j < MAX_COLS; j++)
        {
            std::cout << gameArray[i][j];
        }
        std::cout << "\n"; //newline after each row is drawn
    }
}
