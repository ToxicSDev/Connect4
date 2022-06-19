#include <iostream>
#include <string>

using namespace std;

class Board{
protected:
    int height;
    int width;
    char** board;
    int* heights;

    Board(int height, int width) {
        this->height = height;
        this->width = width;
        this->board = new char *[height];
        this->heights = new int[width];
        for (int i = 0; i < height; i++) {
            this->board[i] = new char[width];
        }
    }

public:
    void printBoard() {
        for (int i = height - 1; i >= 0; i--) {
            for (int j = 0; j < width; j++) {
                cout << board[i][j];
            }
            cout << endl;
        }
    }

    void resetBoard() {
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                board[i][j] = ' ';
            }
        }
    }

    bool isValid(int col){
        if(col < 0 || col >= width || heights[col] == height){
            return false;
        }

        return true;
};

class Connect4 : public Board{
private:
    char player;
    char computer;
public:
    Connect4(int height, int width, char player, char computer) : Board(height, width) {
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
    }

    bool checkWin(char inputChar) {
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
                    if(i + 3 < height && j + 3 < width) {
                        if (board[i][j] == board[i + 1][j + 1] && board[i][j] == board[i + 2][j + 2] &&
                            board[i][j] == board[i + 3][j + 3]) {
                            return true;
                        }
                    }
                    // left diagonal check
                    if(i + 3 < height && j - 3 >= 0) {
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

    int calculateMaxRounds() {
        return (height * width);
    }

    void makeMove(int column, char inputChar) {
        if (heights[column] < height) {
            board[heights[column]][column] = inputChar;
            heights[column]++;
        }
    }

    void resetGame() {
        this->resetBoard();
        delete [] heights;
        heights = new int[width];
    }
};

int main() {
    Connect4 game(6, 7, 'X', 'O');
}