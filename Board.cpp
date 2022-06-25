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