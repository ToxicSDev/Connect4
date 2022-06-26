#include <iostream>
#include <fstream>

#include "utils.h"
#include "Board.h"
#include "Connect4.h"

using namespace std;


void printFile(const string& fileName) {
    ifstream file (fileName.c_str());
    string line;
    while (getline(file, line)) {
        cout <<  line << endl;
    }
    file.close();
}

void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #elif _WIN64
        system("cls");
    #else
        system("clear");
    #endif
}

int countInWindow(const char* window, char inputChar){
    int count = 0;
    for (int i = 0; i < 4; i++) {
        if(window[i] == inputChar){
            count++;
        }
    }
    return count;
}

char* getWindow(const char* row, int offset){
    char* window = new char[4];
    for (int i = 0; i < 4; i++) {
        window[i] = row[(i + offset)];
    }

    return window;
}

int evaluateWindow(const Connect4& game, const char *window, char inputChar){
    int score = 0;
    char opponent = game.getOpponent(inputChar);

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