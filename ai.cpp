#include <iostream>
#include <vector>
#include <limits>
#include <cstdlib>

#include "Connect4.h"
#include "utils.h"

int MAX_INT = std::numeric_limits<int>::max();
int MIN_INT = std::numeric_limits<int>::min();

bool Connect4::isTerminal(char inputChar) {
    if (checkWin(inputChar)) {
        return true;
    }
    if (checkWin(getOpponent(inputChar))) {
        return true;
    }
    if (getValidMoves().empty()) {
        return true;
    }
    return false;
}

char* Connect4::getRow(int pos) {
    char* row = new char[width];
    for (int i = 0; i < width; i++) {
        row[i] = board[pos][i];
    }

    return row;
}

char* Connect4::getCol(int pos) {
    char* col = new char[height];
    for (int i = 0; i < height; i++) {
        col[i] = board[i][pos];
    }

    return col;
}

char* Connect4::getWindow(const char* row, int offset){
    char* window = new char[4];
    for (int i = 0; i < 4; i++) {
        window[i] = row[(i + offset)];
    }

    return window;
}

char* Connect4::getPosDiag(int pos1, int pos2) {
    char* posDiag = new char[4];
    for (int i = 0; i < 4; i++) {
        posDiag[i] = board[pos1 + i][pos2 + i];
    }

    return posDiag;
}

char* Connect4::getNegDiag(int pos1, int pos2) {
    char* negDiag = new char[4];
    for (int i = 0; i < 4; i++) {
        negDiag[i] = board[pos1 + 3 - i][pos2 + i];
    }

    return negDiag;
}

int Connect4::countInWindow(const char* window, char inputChar) const{
    int count = 0;
    for (int i = 0; i < 4; i++) {
        if(window[i] == inputChar){
            count++;
        }
    }
    return count;
}

int Connect4::evaluateWindow(const char *window, char inputChar) const {
    int score = 0;
    char opponent = getOpponent(inputChar);

    if(countInWindow(window, inputChar) == 4){
        score += 100;
    }else if(countInWindow(window, inputChar) == 3 && countInWindow(window, ' ') == 1) {
        score += 5;
    }else if(countInWindow(window, inputChar) == 2 && countInWindow(window, ' ') == 2) {
        score += 2;
    }

    if(countInWindow(window, opponent) == 4) {
        score -= 4;
    }

    return score;
}

int Connect4::getScore(char inputChar) {
    int score = 0;

    char* middleCol = getCol(width / 2);
    score = countInWindow(middleCol, inputChar) * 3;

    // Horizontal Score Check
    for(int i = 0; i < height; i++){
        char* row = getRow(i);
        for(int j = 0; j < width - 3; j++){
            char* window = getWindow(row, j);
            score += evaluateWindow(window, inputChar);
        }
    }

    // Vertical Score Check
    for(int i = 0; i < width; i++){
        char* col = getCol(i);
        for(int j = 0; j < height - 3; j++){
            char* window = getWindow(col, j);
            score += evaluateWindow(window, inputChar);
        }
    }

    // Positive Diagonal Score Check
    for(int i = 0; i < height - 3; i++){
        for(int j = 0; j < width - 3; j++){
            char* posDiag = getPosDiag(i, j);
            score += evaluateWindow(posDiag, inputChar);
        }
    }

    // Negative Diagonal Score Check
    for(int i = 0; i < height - 3; i++){
        for(int j = 0; j < width - 3; j++){
            char* negDiag = getNegDiag(i, j);
            score += evaluateWindow(negDiag, inputChar);
        }
    }

    return score;
}

int Connect4::negamax(int depth, int alpha, int beta, char inputChar) {
    if (depth == 0 || isTerminal(inputChar)) {
        if(isTerminal(inputChar)) {
            if (checkWin(inputChar)) {
                return 100000;
            } else if (checkWin(getOpponent(inputChar))) {
                return -100000;
            } else {
                return 0;
            }
        }else {
            return getScore(inputChar);
        }
    }
    int best = MIN_INT;
    vector<int> validMoves = getValidMoves();
    for (int i = 0; i < validMoves.size(); i++) {
        Connect4 temp(*this);
        temp.makeMove(validMoves[i], inputChar);
        int score = -temp.negamax(depth - 1, -beta, -alpha, getOpponent(inputChar));
        if (score > best) {
            best = score;
        }
        if (best >= beta) {
            return best;
        }
        alpha = max(alpha, best);
    }
    return best;
}

void Connect4::aiMove(int depth, char inputChar) {
    int best = MIN_INT;
    int bestMove = -1;
    vector<int> validMoves = getValidMoves();
    for (int i = 0; i < validMoves.size(); i++) {
        Connect4 temp(*this);
        temp.makeMove(validMoves[i], inputChar);
        int score = -temp.negamax(depth, MIN_INT, MAX_INT, inputChar);
        if (score > best) {
            best = score;
            bestMove = validMoves[i];
        }
    }
    makeMove(bestMove, inputChar);
}

void Connect4::playAI(int depth){
    int column;
    char inputChar;

    int turn = rand() % 2;

    while (true) {
        clearScreen();
        printFile("resources/logo.txt");
        printBoard();
        cout << endl;

        if (turn == 0) {
            cout << "Player's turn: ";
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

            makeMove(column, player);
            currentMoves++;
        } else {
            aiMove(depth, computer);
            currentMoves++;
        }

        if(turn == 0){
            inputChar = player;
        }
        else{
            inputChar = computer;
        }

        if (checkWin(inputChar)) {
            clearScreen();
            if(inputChar == player){
                printFile("resources/player.txt");
            }
            else{
                printFile("resources/ai.txt");
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