#include <iostream>
#include <vector>
using namespace std;

class TicTacToe {
private:
    vector<vector<char>> board;
    char currentPlayer;

    // Helper function to check if a line has the same character
    bool isLineWin(char a, char b, char c) {
        return (a == b && b == c && a != ' ');
    }

public:
    TicTacToe() {
        board = vector<vector<char>>(3, vector<char>(3, ' '));
        currentPlayer = 'X';
    }

    void displayBoard() {
        cout << "\nCurrent Board:\n";
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                cout << " " << board[i][j] << " ";
                if (j < 2) cout << "|";
            }
            cout << "\n";
            if (i < 2) cout << "---|---|---\n";
        }
        cout << "\n";
    }

    bool makeMove(int row, int col) {
        if (row < 0 || row >= 3 || col < 0 || col >= 3) {
            cout << "Out of bounds! Enter values between 0 and 2.\n";
            return false;
        }
        if (board[row][col] != ' ') {
            cout << "Cell already taken. Try a different move.\n";
            return false;
        }
        board[row][col] = currentPlayer;
        return true;
    }

    bool checkWin() {
        for (int i = 0; i < 3; i++) {
            // Check rows and columns
            if (isLineWin(board[i][0], board[i][1], board[i][2]) || isLineWin(board[0][i], board[1][i], board[2][i])) {
                return true;
            }
        }
        // Check diagonals
        return isLineWin(board[0][0], board[1][1], board[2][2]) || isLineWin(board[0][2], board[1][1], board[2][0]);
    }

    bool checkDraw() {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == ' ') return false;
            }
        }
        return true;
    }

    void switchPlayer() {
        currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
    }

    void playGame() {
        cout << "Welcome to Tic-Tac-Toe!\n";
        while (true) {
            displayBoard();
            cout << "Player " << currentPlayer << "'s turn. Enter row and column (0-2): ";
            int row, col;
            cin >> row >> col;

            if (makeMove(row, col)) {
                if (checkWin()) {
                    displayBoard();
                    cout << "Congratulations! Player " << currentPlayer << " wins!\n";
                    break;
                } else if (checkDraw()) {
                    displayBoard();
                    cout << "It's a draw!\n";
                    break;
                }
                switchPlayer();
            }
        }
    }
};

int main() {
    TicTacToe game;
    game.playGame();
    return 0;
}