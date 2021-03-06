#ifndef CONNECT4_CONNECT4_H
#define CONNECT4_CONNECT4_H

#include <iostream>
#include <vector>

#include "Board.h"
#include "Connect4.h"

class Connect4 : public Board {
private:
    char player;
    char computer;
    int currentMoves;

    vector<int> getValidMoves();

    int getScore(char inputChar);
    bool isTerminal(char inputChar);
    int negamax(int depth, int alpha, int beta, char inputChar);
    void aiMove(int depth, char inputChar);

    bool checkWin(char inputChar);
    bool canWin(char inputChar);

    int calculateMaxRounds();

public:
    Connect4(int height, int width, char player, char computer);
    ~Connect4();
    Connect4(const Connect4& other);
    Connect4& operator=(const Connect4& other);

    char getPlayer() const;
    char getComputer() const;
    int getCurrentMoves() const;
    char getOpponent(char inputChar) const;

    void setCurrentMoves(int inputCurrentMoves);
    void setPlayer(char inputChar);
    void setComputer(char inputChar);
    void setHeight(int inputHeight);
    void setWidth(int inputWidth);

    void makeMove(int column, char inputChar);
    void resetGame();

    void playAI(int depth);
    void playManual();
};

#endif
