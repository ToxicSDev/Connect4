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

    char getOpponent(char inputChar) const{
        if(inputChar == player){
            return computer;
        }

        return player;
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

    bool isTerminal(char inputChar){
        if(checkWin(inputChar)){
            return true;
        }
        if(checkWin(getOpponent(inputChar))){
            return true;
        }
        if(getValidMoves().empty()){
            return true;
        }
        return false;
    }

    int minimax(char inputChar, int depth, bool isMax, int alpha, int beta){
        if(isTerminal(inputChar) || depth == 0){
            if(checkWin(computer)){
                return MAX_INT;
            }else if(checkWin(player)) {
                return MIN_INT;
            }else{
                return 0;
            }
        }

        vector<int> validLocations = getValidMoves();
        if(isMax){
            int bestScore = MIN_INT;
            for(unsigned int i = 0; i < validLocations.size(); i++){
                int row = getNextOpenRow(validLocations[i]);
                if(row != -1){
                    Connect4 temp(*this);
                    temp.makeMove(validLocations[i], inputChar);
                    int score = temp.minimax(getOpponent(inputChar), depth - 1, false, alpha, beta);
                    bestScore = max(bestScore, score);
                    alpha = max(alpha, score);
                    if(beta <= alpha){
                        break;
                    }
                }
            }
            return bestScore;
        }else{
            int bestScore = MAX_INT;
            for(unsigned int i = 0; i < validLocations.size(); i++){
                int row = getNextOpenRow(validLocations[i]);
                if(row != -1){
                    Connect4 temp(*this);
                    temp.makeMove(validLocations[i], inputChar);
                    int score = temp.minimax(getOpponent(inputChar), depth - 1, true, alpha, beta);
                    bestScore = min(bestScore, score);
                    beta = min(beta, score);
                    if(beta <= alpha){
                        break;
                    }
                }
            }
            return bestScore;
        }
    }

};

int main() {
    Connect4 game(6, 7, 'X', 'O');

    game.makeMove(0, 'O');
    game.makeMove(1, 'O');

    game.makeMove(3, 'O');
    game.makeMove(3, 'X');

    game.printBoard();

    int move = game.minimax('O', 3, true, MIN_INT, MAX_INT);
    game.makeMove(move, 'O');
    game.printBoard();

}