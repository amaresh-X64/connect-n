#include <stdio.h>


void initializeBoard(int ROWS,int COLUMNS,char (*board)[COLUMNS]) {
    for (int row = 0; row < ROWS; row++) {
        for (int col = 0; col < COLUMNS; col++) {
            board[row][col] = ' ';
        }
    }
}

void printBoard(int ROWS,int COLUMNS,char (*board)[COLUMNS]) {
    for (int row = 0; row < ROWS; row++) {
        for (int col = 0; col < COLUMNS; col++) {
            printf("| %c ", board[row][col]);
        }
        printf("|\n");
    }
    printf("  %d",1);
    for (int col = 2; col < COLUMNS+1; col++)
    printf("   %d",col);
    printf("\n");
}

int dropPiece(int col, char player,int ROWS,int COLUMNS,char (*board)[COLUMNS]) {
    for (int row = ROWS - 1; row >= 0; row--) {
        if (board[row][col] == ' ') {
            board[row][col] = player;
            return 1;
        }
    }
    return 0; // Column is full
}

int checkWin(char player,int ROWS,int COLUMNS,char (*board)[COLUMNS]) {
    // Check for horizontal wins
    for (int row = 0; row < ROWS; row++) {
        for (int col = 0; col <= COLUMNS - 4; col++) {
            if (board[row][col] == player &&
                board[row][col + 1] == player &&
                board[row][col + 2] == player &&
                board[row][col + 3] == player) {
                return 1;
            }
        }
    }

    // Check for vertical wins
    for (int col = 0; col < COLUMNS; col++) {
        for (int row = 0; row <= ROWS - 4; row++) {
            if (board[row][col] == player &&
                board[row + 1][col] == player &&
                board[row + 2][col] == player &&
                board[row + 3][col] == player) {
                return 1;
            }
        }
    }

    // Check for diagonal wins (bottom-left to top-right)
    for (int row = 3; row < ROWS; row++) {
        for (int col = 0; col <= COLUMNS - 4; col++) {
            if (board[row][col] == player &&
                board[row - 1][col + 1] == player &&
                board[row - 2][col + 2] == player &&
                board[row - 3][col + 3] == player) {
                return 1;
            }
        }
    }

    // Check for diagonal wins (bottom-right to top-left)
    for (int row = 3; row < ROWS; row++) {
        for (int col = 3; col < COLUMNS; col++) {
            if (board[row][col] == player &&
                board[row - 1][col - 1] == player &&
                board[row - 2][col - 2] == player &&
                board[row - 3][col - 3] == player) {
                return 1;
            }
        }
    }

    // Check for crossward consecutive 1s
    for (int row = 0; row < ROWS - 3; row++) {
        for (int col = 0; col < COLUMNS - 3; col++) {
            if (board[row][col] == player &&
                board[row + 1][col + 1] == player &&
                board[row + 2][col + 2] == player &&
                board[row + 3][col + 3] == player) {
                return 1;
            }
        }
    }

    for (int row = 0; row < ROWS - 3; row++) {
        for (int col = COLUMNS - 1; col >= 3; col--) {
            if (board[row][col] == player &&
                board[row + 1][col - 1] == player &&
                board[row + 2][col - 2] == player &&
                board[row + 3][col - 3] == player) {
                return 1;
            }
        }
    }

    return 0;
}

int main() {
    int ROWS,COLUMNS;
    printf("enter number of rows greater than 6\n");
    scanf("%d",&ROWS);
    printf("enter number ofcolumns greater than 6\n");
    scanf("%d",&COLUMNS);
    char board[ROWS][COLUMNS];
    initializeBoard(ROWS,COLUMNS,board);
    int currentPlayer = 1;
    int moves = 0;

    while (1) {
        printf("Current board:\n");
        printBoard(ROWS,COLUMNS,board);

        int col;
        printf("Player %d, enter a column (1-7): ", currentPlayer);
        scanf("%d", &col);
        col--;

        if (col < 0 || col >= COLUMNS) {
            printf("Invalid column. Try again.\n");
            continue;
        }

        if (dropPiece(col, (currentPlayer == 1) ? 'X' : 'O',ROWS,COLUMNS,board)) {
            if (checkWin((currentPlayer == 1) ? 'X' : 'O',ROWS,COLUMNS,board)) {
                printBoard(ROWS,COLUMNS,board);
                printf("Player %d wins!\n", currentPlayer);
                break;
            }
            moves++;
            if (moves == ROWS * COLUMNS) {
                printf("It's a draw!\n");
                printBoard(ROWS,COLUMNS,board);
                break;
            }
            currentPlayer = (currentPlayer == 1) ? 2 : 1;
        } else {
            printf("Column is full. Try again.\n");
        }
    }

    return 0;
}
