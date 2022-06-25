#include "utils.h"
#include <iostream>
#include <fstream>

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