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
    int getHeight() const;
    int getWidth() const;
    char** getBoard();

    char* getRow(int pos);
    char* getCol(int pos);
    char* getPosDiag(int pos1, int pos2);
    char* getNegDiag(int pos1, int pos2);
};

#endif