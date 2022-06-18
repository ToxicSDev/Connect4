#include <iostream>
#include <string>

using namespace std;

class Connect4{
protected:
    int height;
    int width;
    char** board;

public:
    Connect4(int h, int w){
        height = h;
        width = w;
        board = new char*[height];
        for(int i = 0; i < height; i++){
            board[i] = new char[width];
        }
        for(int i = 0; i < height; i++){
            for(int j = 0; j < width; j++){
                board[i][j] = ' ';
            }
        }
    }
    ~Connect4(){
        for(int i = 0; i < height; i++){
            delete[] board[i];
        }
        delete[] board;
    }

    void printBoard() {
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                cout << board[i][j];
            }
            cout << endl;
        }
    }

};