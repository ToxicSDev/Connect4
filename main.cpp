#include <iostream>
#include <string>
#include <fstream>

#include "Connect4.h"

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
    bool running = true;

    char player1 = 'X';
    char player2 = 'O';

    int height = 6;
    int width = 7;

    int depth = 5;

    while(running) {
        clearScreen();
        printFile("resources/menu.txt");
        cout << endl;
        cout << "Select a menu option: ";
        int option;
        cin >> option;

        clearScreen();
        if(option == 1) {

        } else if(option == 2) {

        } else if(option == 3) {
            printFile("resources/info.txt");
            cout << endl;
            cout << "Press enter to continue...";
            cin.ignore();
            cin.get();
        } else if(option == 4) {
            printFile("resources/settings.txt");
            cout << endl;
            cout << "Select a menu option: ";
            int setting;
            cin >> setting;
            clearScreen();
            if(setting == 1){
                cout << "Current Character for Player 1: " << player1 << endl << endl;
                cout << "Enter a new character for Player 1: ";
                cin >> player1;
            }else if(setting == 2){
                cout << "Current Character for Player 2 (Computer): " << player2 << endl << endl;
                cout << "Enter a new character for Player 2 (Computer): ";
                cin >> player2;
            }else if(setting == 3){
                cout << "Current Height: " << height << endl << endl;
                cout << "Enter a new height (between 1 and 20): ";
                cin >> height;
                if(height < 1 || height > 20){
                    height = 6;
                }
            }else if(setting == 4){
                cout << "Current Width: " << width << endl << endl;
                cout << "Enter a new width (between 4 and 40): ";
                cin >> width;
                if(width < 4 || width > 40){
                    width = 7;
                }
            }else if(setting == 5){
                cout << "Current Depth: " << depth << endl << endl;
                cout << "Enter a new depth (between 1 and 10): ";
                cin >> depth;
                if(depth < 1 || depth > 10){
                    depth = 5;
                }
            }else if(setting == 6){
                continue;
            }
            else {
                printFile("resources/invalid.txt");
                cout << endl;
                cout << "Press enter to continue...";
                cin.ignore();
                cin.get();
            }
        } else if(option == 5) {
            running = false;
        }else {
            printFile("resources/invalid.txt");
            cout << endl;
            cout << "Press enter to continue...";
            cin.ignore();
            cin.get();
        }
    }
}

int main() {
    menu();

    return 0;
}