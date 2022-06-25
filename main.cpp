#include <iostream>
#include <string>
#include <limits>
#include <vector>
#include <fstream>

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
};

class Connect4 : public Board{
private:
    char player;
    char computer;
    int currentMoves;

    vector<int> getValidMoves(){
        vector<int> validMoves;
        for(int i = 0; i < width; i++){
            if(isValid(i)){
                validMoves.push_back(i);
            }
        }
        return validMoves;
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

    int getScore(char inputChar){
        int score = 0;

        if(checkWin(inputChar)){
            score += 100000;
        }else if(checkWin(getOpponent(inputChar))){
            score -= 100000;
        }

        if(board[3][3] == ' '){
            score += MAX_INT;
        }

        return score;
    }

    int negamax(int depth, int alpha, int beta, char inputChar){
        if(depth == 0 || isTerminal(inputChar)){
            return getScore(inputChar);
        }
        int best = MIN_INT;
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
        this->currentMoves = 0;
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
        this->currentMoves = other.currentMoves;
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

    char getPlayer() const{
        return player;
    }

    char getComputer() const{
        return computer;
    }

    int getCurrentMoves() const{
        return currentMoves;
    }

    char getOpponent(char inputChar) const{
        if(inputChar == player){
            return computer;
        }

        return player;
    }

    void setCurrentMoves(int inputCurrentMoves){
        this->currentMoves = inputCurrentMoves;
    }

    void setPlayer(char inputChar){
        this->player = inputChar;
    }

    void setComputer(char inputChar){
        this->computer = inputChar;
    }

    void setHeight(int inputHeight){
        this->height = inputHeight;
    }

    void setWidth(int inputWidth){
        this->width = inputWidth;
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

    void aiMove(int depth, char inputChar){
        int best = MIN_INT;
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
    cout << endl << endl;

    cout << "1. Play against a friend" << endl;
    cout << "2. Play against the computer" << endl;
    cout << "3. View the rules" << endl;
    cout << "3. View information about the game" << endl;
    cout << "4. Quit" << endl;
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