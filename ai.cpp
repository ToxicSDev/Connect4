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

int Connect4::getScore(char inputChar) {
    int score = 0;

    if (checkWin(inputChar)) {
        score += 100000;
    } else if (checkWin(getOpponent(inputChar))) {
        score -= 100000;
    }

    if (board[3][3] == ' ') {
        score += MAX_INT;
    }

    return score;
}

int Connect4::negamax(int depth, int alpha, int beta, char inputChar) {
    if (depth == 0 || isTerminal(inputChar)) {
        return getScore(inputChar);
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