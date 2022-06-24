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
    int currentMoves;
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

    char getPlayer(){
        return player;
    }

    char getComputer(){
        return computer;
    }

    int getCurrentMoves(){
        return currentMoves;
    }

    void setCurrentMoves(int currentMoves){
        this->currentMoves = currentMoves;
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

    int heuristic(char inputChar){
        int score = 0;

        if(checkWin(inputChar)){
            score += 100000;
        }else if(checkWin(getOpponent(inputChar))){
            score -= 100000;
        }

        return score;
    }

    int negamax(int depth, int alpha, int beta, char inputChar){
        if(depth == 0 || isTerminal(inputChar)){
            return heuristic(inputChar);
        }
        int best = -1000000;
        vector<int> validMoves = getValidMoves();
        for(int i = 0; i < validMoves.size(); i++){
            Connect4 temp(*this);
            temp.makeMove(validMoves[i], inputChar);
            int score = -temp.negamax(depth - 1, -beta, -alpha, getOpponent(inputChar));
            if(score > best){
                best = score;
            }
            if(best >= beta){
                return best;
            }
            alpha = max(alpha, best);
        }
        return best;
    }

    int aiMove(int depth, char inputChar){
        int best = -1000000;
        int bestMove = -1;
        vector<int> validMoves = getValidMoves();
        for(int i = 0; i < validMoves.size(); i++){
            Connect4 temp(*this);
            temp.makeMove(validMoves[i], inputChar);
            int score = -temp.negamax(depth, MIN_INT, MAX_INT, inputChar);
            if(score > best){
                best = score;
                bestMove = validMoves[i];
            }
        }
        makeMove(bestMove, inputChar);
    }


};

int main() {
    Connect4 game(6, 7, 'X', 'O');

    while(true){
        game.printBoard();
        cout << "Player: " << game.getPlayer() << endl;
        cout << "Computer: " << game.getComputer() << endl;
        cout << "Enter column: ";
        int column;
        cin >> column;
        while(!game.isValid(column)){
            cout << "Invalid column, try again: ";
            cin >> column;
        }
        game.makeMove(column, game.getPlayer());
        game.setCurrentMoves(game.getCurrentMoves() + 1);
        if(game.checkWin(game.getPlayer())){
            game.printBoard();
            cout << "Player wins!" << endl;
            break;
        }
        game.aiMove(5, game.getComputer());
        game.setCurrentMoves(game.getCurrentMoves() + 1);
        if(game.checkWin(game.getComputer())){
            game.printBoard();
            cout << "Computer wins!" << endl;
            break;
        }
    }
}