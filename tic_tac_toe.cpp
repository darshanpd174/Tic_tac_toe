#include <iostream>
#include <vector>
#include <limits>

const int SIZE = 3;
char board[SIZE][SIZE] = { {' ', ' ', ' '}, {' ', ' ', ' '}, {' ', ' ', ' '} };
char player_marker = 'X';
char computer_marker = 'O';

int playerWins = 0;
int computerWins = 0;

void drawBoard() {
    std::cout << "-------------\n";
    for (int i = 0; i < SIZE; ++i) {
        std::cout << "|";
        for (int j = 0; j < SIZE; ++j) {
            std::cout << " " << board[i][j] << " |";
        }
        std::cout << "\n-------------\n";
    }
    std::cout << "Wins: " + std::to_string(playerWins) + " Losses: " + std::to_string(computerWins) + "\n";
}

bool isMovesLeft() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == ' ') {
                return true;
            }
        }
    }
    return false;
}

int evaluate(char board[SIZE][SIZE]) {
    
    for (int row = 0; row < SIZE; row++) {
        if (board[row][0] == board[row][1] && board[row][1] == board[row][2]) {
            if (board[row][0] == computer_marker) {
                return 10;
            } else if (board[row][0] == player_marker) {
                return -10;
            }
        }
    }

    for (int col = 0; col < SIZE; col++) {
        if (board[0][col] == board[1][col] && board[1][col] == board[2][col]) {
            if (board[0][col] == computer_marker) {
                return 10;
            } else if (board[0][col] == player_marker) {
                return -10;
            }
        }
    }

    if (board[0][0] == board[1][1] && board[1][1] == board[2][2]) {
        if (board[0][0] == computer_marker) {
            return 10;
        } else if (board[0][0] == player_marker) {
            return -10;
        }
    }
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0]) {
        if (board[0][2] == computer_marker) {
            return 10;
        } else if (board[0][2] == player_marker) {
            return -10;
        }
    }

    return 0;
}

int minimax(char board[SIZE][SIZE], int depth, bool isMax) {
    int score = evaluate(board);

    if (score == 10) {
        return score - depth;
    }

    if (score == -10) {
        return score + depth;
    }

    if (!isMovesLeft()) {
        return 0;
    }

    if (isMax) {
        int best = -1000;

        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                
                if (board[i][j] == ' ') {
                  
                    board[i][j] = computer_marker;

                    best = std::max(best, minimax(board, depth + 1, !isMax));

                    board[i][j] = ' ';
                }
            }
        }
        return best;
    } else {
        int best = 1000;

        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
               
                if (board[i][j] == ' ') {
                 
                    board[i][j] = player_marker;

                    best = std::min(best, minimax(board, depth + 1, !isMax));

                    board[i][j] = ' ';
                }
            }
        }
        return best;
    }
}

void computerMove() {
    int bestVal = -1000;
    int bestMoveRow = -1;
    int bestMoveCol = -1;

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            
            if (board[i][j] == ' ') {
               
                board[i][j] = computer_marker;

                int moveVal = minimax(board, 0, false);

                board[i][j] = ' ';

                if (moveVal > bestVal) {
                    bestMoveRow = i;
                    bestMoveCol = j;
                    bestVal = moveVal;
                }
            }
        }
    }

    board[bestMoveRow][bestMoveCol] = computer_marker;
}

bool placeMarker(int row, int col, char marker) {
    if (row >= 0 && row < SIZE && col >= 0 && col < SIZE && board[row][col] == ' ') {
        board[row][col] = marker;
        return true;
    }

    return false;
}

void game() {
    int player_won = 0;
    bool playerTurn = true;

    while (player_won == 0 && isMovesLeft()) {
        drawBoard();

        if (playerTurn) { 
            int row, col;
            std::cout << "Enter row and column (0, 1, or 2): ";
            std::cin >> row >> col;

            while (!placeMarker(row, col, player_marker)) {
                std::cout << "Invalid move. Try again: ";
                std::cin >> row >> col;
            }

            playerTurn = false;
        } else {  
            computerMove();
            playerTurn = true;
        }

        player_won = evaluate(board);
    }

    drawBoard();

    if (player_won == 10) {
        std::cout << "Computer won! Better luck next time.\n";
        computerWins++;
    } else if (player_won == -10) {
        std::cout << "You won! Congratulations!\n";
        playerWins++;
    } else {
        std::cout << "It's a tie!\n";
    }

    char playAgain;
    std::cout << "Do you want to play again? (y/n): ";
    std::cin >> playAgain;

    if (playAgain == 'y' || playAgain == 'Y') {
      
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                board[i][j] = ' ';
            }
        }
        game();
    }
}

int main() {
    game();
    return 0;
}
