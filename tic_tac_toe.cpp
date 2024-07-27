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
    // Check rows for a win
    for (int row = 0; row < SIZE; row++) {
        if (board[row][0] == board[row][1] && board[row][1] == board[row][2]) {
            if (board[row][0] == computer_marker) {
                return 10;
            } else if (board[row][0] == player_marker) {
                return -10;
            }
        }
    }

    // Check columns for a win
    for (int col = 0; col < SIZE; col++) {
        if (board[0][col] == board[1][col] && board[1][col] == board[2][col]) {
            if (board[0][col] == computer_marker) {
                return 10;
            } else if (board[0][col] == player_marker) {
                return -10;
            }
        }
    }

    // Check diagonals for a win
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

    // No winner
    return 0;
}

int minimax(char board[SIZE][SIZE], int depth, bool isMax) {
    int score = evaluate(board);

    // If Maximizer has won the game
    if (score == 10) {
        return score - depth;
    }

    // If Minimizer has won the game
    if (score == -10) {
        return score + depth;
    }

    // If there are no more moves and no winner, it's a tie
    if (!isMovesLeft()) {
        return 0;
    }

    // If this is maximizer's move
    if (isMax) {
        int best = -1000;

        // Traverse all cells
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                // Check if cell is empty
                if (board[i][j] == ' ') {
                    // Make the move
                    board[i][j] = computer_marker;

                    // Call minimax recursively and choose the maximum value
                    best = std::max(best, minimax(board, depth + 1, !isMax));

                    // Undo the move
                    board[i][j] = ' ';
                }
            }
        }
        return best;
    } else {
        int best = 1000;

        // Traverse all cells
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                // Check if cell is empty
                if (board[i][j] == ' ') {
                    // Make the move
                    board[i][j] = player_marker;

                    // Call minimax recursively and choose the minimum value
                    best = std::min(best, minimax(board, depth + 1, !isMax));

                    // Undo the move
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

    // Traverse all cells, evaluate minimax function for all empty cells
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            // Check if cell is empty
            if (board[i][j] == ' ') {
                // Make the move
                board[i][j] = computer_marker;

                // Compute evaluation function for this move
                int moveVal = minimax(board, 0, false);

                // Undo the move
                board[i][j] = ' ';

                // If the value of the current move is more than the best value, update best
                if (moveVal > bestVal) {
                    bestMoveRow = i;
                    bestMoveCol = j;
                    bestVal = moveVal;
                }
            }
        }
    }

    // Make the best move
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

        if (playerTurn) {  // Player's turn
            int row, col;
            std::cout << "Enter row and column (0, 1, or 2): ";
            std::cin >> row >> col;

            while (!placeMarker(row, col, player_marker)) {
                std::cout << "Invalid move. Try again: ";
                std::cin >> row >> col;
            }

            playerTurn = false;
        } else {  // Computer's turn
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

    // Prompt to play again
    char playAgain;
    std::cout << "Do you want to play again? (y/n): ";
    std::cin >> playAgain;

    if (playAgain == 'y' || playAgain == 'Y') {
        // Reset the game
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
