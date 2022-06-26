#ifndef CONNECT4_UTILS_H
#define CONNECT4_UTILS_H

#include <iostream>
#include "Board.h"
#include "Connect4.h"

void printFile(const std::string& fileName);
void clearScreen();

int countInWindow(const char* window, char inputChar);
char* getWindow(const char* row, int offset);
int evaluateWindow(const Connect4& game, const char *window, char inputChar);

#endif
