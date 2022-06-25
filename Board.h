#ifndef CONNECT4_BOARD_H
#define CONNECT4_BOARD_H

using namespace std;

class Board{
protected:
    int height;
    int width;
    char** board;
    int* heights;

    Board(int height, int width);
    void resetBoard();
    bool isValid(int col);

public:
    void printBoard();
};

#endif