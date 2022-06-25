#include <iostream>
#include <string>
#include <vector>
#include <limits>

#include "Board.h"
#include "Connect4.h"

int MAX_INT = std::numeric_limits<int>::max();
int MIN_INT = std::numeric_limits<int>::min();

vector<int> Connect4::getValidMoves() {
    vector<int> validMoves;
    for (int i = 0; i < width; i++) {
        if (isValid(i)) {
            validMoves.push_back(i);
        }
    }
    return validMoves;
}

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

int Connect4::getHeight() {
    return height;
}

int Connect4::getWidth() {
    return width;
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
