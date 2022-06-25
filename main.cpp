#include <iostream>
#include <string>
#include <fstream>

#include "Connect4.h"

// max height = 20
// max width = 40
// min width = 4
// min height = 1

// default height = 6
// default width = 7

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

void menu(){
    clearScreen();
    printFile("resources/menu.txt");
    printFile("resources/info.txt");
}

int main() {
    menu();

    Connect4 game(6, 7, 'X', 'O');

    game.aiMove(1, 'X');
    game.aiMove(1, 'X');
    game.makeMove(3, 'O');
    game.makeMove(3, 'O');
    game.aiMove(1, 'X');
    game.printBoard();

    return 0;
}