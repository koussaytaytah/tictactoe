#include <stdio.h>
#include <stdbool.h>

#define SIZE 3

// Function prototypes
void initializeBoard(char board[SIZE][SIZE]);
void displayBoard(char board[SIZE][SIZE]);
bool makeMove(char board[SIZE][SIZE], int row, int col, char player);
bool checkWin(char board[SIZE][SIZE], char player);
bool isDraw(char board[SIZE][SIZE]);
void machineMove(char board[SIZE][SIZE]);

int main() {
    char board[SIZE][SIZE];
    char currentPlayer = 'X';
    int row, col;
    bool gameRunning = true;

    initializeBoard(board);

    printf("Welcome to Tic-Tac-Toe with a virtual player!\n");

    while (gameRunning) {
        displayBoard(board);
        if (currentPlayer == 'X') {
            // Human player
            printf("Player %c, enter your move (row and column: 1-3): ", currentPlayer);
            scanf("%d %d", &row, &col);

            // Adjust for zero-based indexing
            row--;
            col--;

            if (row >= 0 && row < SIZE && col >= 0 && col < SIZE) {
                if (makeMove(board, row, col, currentPlayer)) {
                    if (checkWin(board, currentPlayer)) {
                        displayBoard(board);
                        printf("Player %c wins!\n", currentPlayer);
                        gameRunning = false;
                    } else if (isDraw(board)) {
                        displayBoard(board);
                        printf("It's a draw!\n");
                        gameRunning = false;
                    } else {
                        currentPlayer = 'O'; // Switch to machine
                    }
                } else {
                    printf("Invalid move, cell already occupied. Try again.\n");
                }
            } else {
                printf("Invalid input, please enter row and column between 1 and 3.\n");
            }
        } else {
            // Machine's turn
            printf("Machine (Player O) is making a move...\n");
            machineMove(board);

            if (checkWin(board, currentPlayer)) {
                displayBoard(board);
                printf("Player %c (Machine) wins!\n", currentPlayer);
                gameRunning = false;
            } else if (isDraw(board)) {
                displayBoard(board);
                printf("It's a draw!\n");
                gameRunning = false;
            } else {
                currentPlayer = 'X'; // Switch to human
            }
        }
    }

    return 0;
}

void initializeBoard(char board[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            board[i][j] = ' ';
        }
    }
}

void displayBoard(char board[SIZE][SIZE]) {
    printf("\n");
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf(" %c ", board[i][j]);
            if (j < SIZE - 1) printf("|");
        }
        printf("\n");
        if (i < SIZE - 1) printf("---+---+---\n");
    }
    printf("\n");
}

bool makeMove(char board[SIZE][SIZE], int row, int col, char player) {
    if (board[row][col] == ' ') {
        board[row][col] = player;
        return true;
    }
    return false;
}

bool checkWin(char board[SIZE][SIZE], char player) {
    // Check rows and columns
    for (int i = 0; i < SIZE; i++) {
        if ((board[i][0] == player && board[i][1] == player && board[i][2] == player) ||
            (board[0][i] == player && board[1][i] == player && board[2][i] == player)) {
            return true;
        }
    }

    // Check diagonals
    if ((board[0][0] == player && board[1][1] == player && board[2][2] == player) ||
        (board[0][2] == player && board[1][1] == player && board[2][0] == player)) {
        return true;
    }

    return false;
}

bool isDraw(char board[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == ' ') {
                return false;
            }
        }
    }
    return true;
}

void machineMove(char board[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == ' ') {
                board[i][j] = 'O';
                return;
            }
        }
    }
}
