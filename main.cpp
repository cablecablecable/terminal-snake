#include <iostream>
#include <cstdlib>
#include <unistd.h>

constexpr int maxColumns = 81;
constexpr int maxRows = 16;

bool atEdge(int rowNum, int columnNum) {
    bool rowNumAtTopOrBottom = rowNum == 0 || rowNum == maxRows - 1;
    bool columnNumAtLeftOrRight = columnNum == 0 || columnNum == maxColumns - 1;

    return (rowNumAtTopOrBottom || columnNumAtLeftOrRight);
}

void drawWindow() {

    char arr[maxRows][maxColumns];

    //for each row, insert elements column by column
    for (int i = 0; i < maxRows; i++) {
        for (int j = 0; j < maxColumns; j++) {
            if (atEdge(i, j)) {
                arr[i][j] = '#';
            }
            else {
                arr[i][j] = ' ';
            }
        }
    }


    for (int i = 0; i < maxRows; i++) {
        for (int j = 0; j < maxColumns; j++) {
            std::cout << arr[i][j];
        }
        std::cout << "\n";
    }
}

int main() {
    drawWindow();
}
