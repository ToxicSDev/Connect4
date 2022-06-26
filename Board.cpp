#include <iostream>

#include "Board.h"

using namespace std;

Board::Board(int height, int width) {
    this->height = height;
    this->width = width;
    this->board = new char *[height];
    this->heights = new int[width];
    for (int i = 0; i < height; i++) {
        this->board[i] = new char[width];
    }
}

int Board::getHeight() const {
    return height;
}

int Board::getWidth() const {
    return width;
}

char** Board::getBoard() {
    return board;
}

void Board::resetBoard() {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            board[i][j] = ' ';
        }
    }
}

bool Board::isValid(int col) {
    if (col < 0 || col >= width || heights[col] == height) {
        return false;
    }

    return true;
}

void Board::printBoard() {
    cout << "Board:" << endl;
    for (int i = height - 1; i >= 0; i--) {
        cout << "|";
        for (int j = 0; j < width; j++) {
            cout << board[i][j] << "|";
        }
        cout << endl;
    }
}

char* Board::getRow(int pos) {
    char* row = new char[width];
    for (int i = 0; i < width; i++) {
        row[i] = board[pos][i];
    }

    return row;
}

char* Board::getCol(int pos) {
    char* col = new char[height];
    for (int i = 0; i < height; i++) {
        col[i] = board[i][pos];
    }

    return col;
}

char* Board::getPosDiag(int pos1, int pos2) {
    char* posDiag = new char[4];
    for (int i = 0; i < 4; i++) {
        posDiag[i] = board[pos1 + i][pos2 + i];
    }

    return posDiag;
}

char* Board::getNegDiag(int pos1, int pos2) {
    char* negDiag = new char[4];
    for (int i = 0; i < 4; i++) {
        negDiag[i] = board[pos1 + 3 - i][pos2 + i];
    }

    return negDiag;
}