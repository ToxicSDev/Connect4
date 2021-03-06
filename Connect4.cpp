#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include <cstdlib>

#include "Board.h"
#include "Connect4.h"
#include "utils.h"

vector<int> Connect4::getValidMoves() {
    vector<int> validMoves;
    for (int i = 0; i < width; i++) {
        if (isValid(i)) {
            validMoves.push_back(i);
        }
    }
    return validMoves;
}

Connect4::Connect4(int height, int width, char player, char computer) : Board::Board(height, width) {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            this->board[i][j] = ' ';
        }
    }
    for (int i = 0; i < width; i++) {
        this->heights[i] = 0;
    }
    this->player = player;
    this->computer = computer;
    this->currentMoves = 0;
}

Connect4::~Connect4() {
    for (int i = 0; i < height; i++) {
        delete[] board[i];
    }
    delete[] board;
    delete[] heights;
}

Connect4::Connect4(const Connect4 &other) : Board(other.height, other.width) {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            this->board[i][j] = other.board[i][j];
        }
    }
    for (int i = 0; i < width; i++) {
        this->heights[i] = other.heights[i];
    }
    this->player = other.player;
    this->computer = other.computer;
    this->currentMoves = other.currentMoves;
}

Connect4 &Connect4::operator=(const Connect4 &other) {
    if (this != &other) {
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                this->board[i][j] = other.board[i][j];
            }
        }
        for (int i = 0; i < width; i++) {
            this->heights[i] = other.heights[i];
        }
        this->player = other.player;
        this->computer = other.computer;
    }
    return *this;
}

char Connect4::getPlayer() const {
    return player;
}

char Connect4::getComputer() const {
    return computer;
}

int Connect4::getCurrentMoves() const {
    return currentMoves;
}

char Connect4::getOpponent(char inputChar) const {
    if (inputChar == player) {
        return computer;
    }

    return player;
}

void Connect4::setCurrentMoves(int inputCurrentMoves) {
    this->currentMoves = inputCurrentMoves;
}

void Connect4::setPlayer(char inputChar) {
    this->player = inputChar;
}

void Connect4::setComputer(char inputChar) {
    this->computer = inputChar;
}

void Connect4::setHeight(int inputHeight) {
    this->height = inputHeight;
}

void Connect4::setWidth(int inputWidth) {
    this->width = inputWidth;
}

bool Connect4::checkWin(char inputChar) {

    if(currentMoves < 7) {
        return false;
    }

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (board[i][j] == inputChar) {
                // horizontal check
                if (j + 3 < width) {
                    if (board[i][j] == board[i][j + 1] && board[i][j] == board[i][j + 2] &&
                        board[i][j] == board[i][j + 3]) {
                        return true;
                    }
                }
                // vertical check
                if (i + 3 < height) {
                    if (board[i][j] == board[i + 1][j] && board[i][j] == board[i + 2][j] &&
                        board[i][j] == board[i + 3][j]) {
                        return true;
                    }
                }
                // right diagonal check
                if (i + 3 < height && j + 3 < width) {
                    if (board[i][j] == board[i + 1][j + 1] && board[i][j] == board[i + 2][j + 2] &&
                        board[i][j] == board[i + 3][j + 3]) {
                        return true;
                    }
                }
                // left diagonal check
                if (i + 3 < height && j - 3 >= 0) {
                    if (board[i][j] == board[i + 1][j - 1] && board[i][j] == board[i + 2][j - 2] &&
                        board[i][j] == board[i + 3][j - 3]) {
                        return true;
                    }
                }
            }
        }
    }

    return false;
}

int Connect4::calculateMaxRounds() {
    return (height * width);
}

void Connect4::makeMove(int column, char inputChar) {
    if (heights[column] < height) {
        board[heights[column]][column] = inputChar;
        heights[column]++;
    }
}

void Connect4::resetGame() {
    this->resetBoard();
    delete[] heights;
    heights = new int[width];
}

void Connect4::playManual(){
    int column;
    char inputChar;

    int turn = rand() % 2;

    while (true) {
        clearScreen();
        printFile("resources/logo.txt");
        printBoard();
        cout << endl;

        cout << "Player " << (turn + 1) << " turn: ";
        cin >> column;

        column = column - 1;

        if (column < 0 || column >= width) {
            cout << endl << "Invalid column. Try again." << endl;

            cout << endl;
            cout << "Press enter to continue...";
            cin.ignore();
            cin.get();

            continue;
        }
        if (heights[column] == height) {
            cout << endl << "Column is full. Try again." << endl;

            cout << endl;
            cout << "Press enter to continue...";
            cin.ignore();
            cin.get();

            continue;
        }

        if(turn == 0){
            inputChar = player;
        }
        else{
            inputChar = computer;
        }

        makeMove(column, inputChar);
        currentMoves++;
        if (checkWin(inputChar)) {
            clearScreen();
            if(inputChar == player){
                printFile("resources/player1.txt");
            }
            else{
                printFile("resources/player2.txt");
            }
            cout << endl;

            printBoard();

            cout << endl;
            cout << "Press enter to continue...";
            cin.ignore();
            cin.get();

            break;
        }
        if (currentMoves == calculateMaxRounds()) {
            clearScreen();
            printFile("resources/draw.txt");
            cout << endl;

            printBoard();

            cout << endl;
            cout << "Press enter to continue...";
            cin.ignore();
            cin.get();

            break;
        }

        turn = (turn + 1) % 2;
    }
}
