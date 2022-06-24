#include <iostream>
#include <string>
#include <limits>
#include <vector>

int MAX_INT = std::numeric_limits<int>::max();
int MIN_INT = std::numeric_limits<int>::min();

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
        cout << "Board:" << endl;
        for (int i = height - 1; i >= 0; i--) {
            cout << "|";
            for (int j = 0; j < width; j++) {
                cout << board[i][j] << "|";
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

    bool isValid(int col) {
        if (col < 0 || col >= width || heights[col] == height) {
            return false;
        }

        return true;
    }
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

    ~Connect4() {
        for (int i = 0; i < height; i++) {
            delete[] board[i];
        }
        delete[] board;
        delete[] heights;
    }

    Connect4(const Connect4& other) : Board(other.height, other.width) {
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

    Connect4& operator=(const Connect4& other) {
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

    int getHeight(){
        return height;
    }

    int getWidth(){
        return width;
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

    int winningMove(char inputChar){
        for (int i = 0; i < width; i++) {
            if (isValid(i)) {
                Connect4 temp(*this);
                temp.makeMove(i, inputChar);
                if (temp.checkWin(inputChar)) {
                    return i;
                }
            }
        }
        return -1;
    }

    char getOpponent(char inputChar){
        if(inputChar == player){
            return computer;
        }

        return player;
    }

    char* getRow(int pos) {
        char* row = new char[width];
        for (int i = 0; i < width; i++) {
            row[i] = board[pos][i];
        }

        return row;
    }

    char* getWindow(const char* row, int offset){
        char* window = new char[4];
        for (int i = 0; i < 4; i++) {
            window[i] = row[(i + offset)];
        }

        return window;
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

    int evaluateWindow(const char* window, char inputChar) {
        int score = 0;
        char opponent = getOpponent(inputChar);

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

    int getScore(char inputChar){
        int score = 0;
        for(int i = 0; i < height; i++){
            char* row = getRow(i);
            for(int j = 0; j < width - 3; j++){
                char* window = getWindow(row, j);
                score += evaluateWindow(window, inputChar);
            }
        }

        return score;
    }


    vector<int> getValidMoves(){
        vector<int> validMoves;
        for(int i = 0; i < width; i++){
            if(isValid(i)){
                validMoves.push_back(i);
            }
        }
        return validMoves;
    }

    int getNextOpenRow(int col){
        for(int i = heights[col]; i < height; i++){
            if(board[i][col] == ' '){
                return i;
            }
        }
        return -1;
    }

    int bestMove(char inputChar){
        vector<int> validLocations = getValidMoves();

        int bestScore = MIN_INT;
        unsigned int bestCol;

        for(unsigned int i = 0; i < validLocations.size(); i++){
            int row = getNextOpenRow(validLocations[i]);
            if(row != -1){
                Connect4 temp(*this);
                temp.makeMove(validLocations[i], inputChar);
                int score = temp.getScore(inputChar);
                if(score > bestScore){
                    bestScore = score;
                    bestCol = i;
                }
            }
        }

        return bestCol;
    }
};

int main() {
    Connect4 game(6, 7, 'X', 'O');

    game.makeMove(0, 'O');
    game.makeMove(1, 'O');

    cout << game.winningMove('O') << endl;

    game.makeMove(3, 'O');
    game.makeMove(3, 'X');

    cout << game.winningMove('O') << endl;
    game.printBoard();

    int col = game.bestMove('O');

    cout << "Best move: " << col << endl;


}