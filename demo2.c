#include <stdio.h>

void initializeBoard(int ROWS,int COLUMNS,char (*board)[COLUMNS]) {
    for (int row = 0; row < ROWS; row++) {
        for (int col = 0; col < COLUMNS; col++) {
            board[row][col] = ' ';}}}

void printBoard(int ROWS,int COLUMNS,char (*board)[COLUMNS]) {
    for (int row = 0; row < ROWS; row++) {
        for (int col = 0; col < COLUMNS; col++) {
            printf("| %c ", board[row][col]);}
        printf("|\n");}
    printf("  %d",1);
    for (int col = 2; col < COLUMNS+1; col++)
    {
    if(col<=10)
    printf("   %d",col);
    if(col>10)
    printf("  %d",col);}
    printf("\n");}

int push(int col, char player,int ROWS,int COLUMNS,char (*board)[COLUMNS]) {
    for (int row = ROWS - 1; row >= 0; row--) {
        if (board[row][col] == ' ') {
            board[row][col] = player;
            return 1;
        }}
    return 0;}

int checkWin(char player,int ROWS,int COLUMNS,char (*board)[COLUMNS],int connect) {
    if(connect==4)
    {
    for (int row = 0; row < ROWS; row++) {
        for (int col = 0; col <= COLUMNS - 4; col++) {
            if (board[row][col] == player &&
                board[row][col + 1] == player &&
                board[row][col + 2] == player &&
                board[row][col + 3] == player) {
                return 1;}}}

    for (int col = 0; col < COLUMNS; col++) {
        for (int row = 0; row <= ROWS - 4; row++) {
            if (board[row][col] == player &&
                board[row + 1][col] == player &&
                board[row + 2][col] == player &&
                board[row + 3][col] == player) {
                return 1;}}}

    for (int row = 3; row < ROWS; row++) {
        for (int col = 0; col <= COLUMNS - 4; col++) {
            if (board[row][col] == player &&
                board[row - 1][col + 1] == player &&
                board[row - 2][col + 2] == player &&
                board[row - 3][col + 3] == player) {
                return 1;}}}
for (int row = 3; row < ROWS; row++) {
        for (int col = 3; col < COLUMNS; col++) {
            if (board[row][col] == player &&
                board[row - 1][col - 1] == player &&
                board[row - 2][col - 2] == player &&
                board[row - 3][col - 3] == player) {
                return 1;}}}

    for (int row = 0; row < ROWS - 3; row++) {
        for (int col = 0; col < COLUMNS - 3; col++) {
            if (board[row][col] == player &&
                board[row + 1][col + 1] == player &&
                board[row + 2][col + 2] == player &&
                board[row + 3][col + 3] == player) {
                return 1;}}}

    for (int row = 0; row < ROWS - 3; row++) {
        for (int col = COLUMNS - 1; col >= 3; col--) {
            if (board[row][col] == player &&
                board[row + 1][col - 1] == player &&
                board[row + 2][col - 2] == player &&
                board[row + 3][col - 3] == player) {
                return 1;}}}
    }
    if(connect==5)
    {
    for (int row = 0; row < ROWS; row++) {
        for (int col = 0; col <= COLUMNS - 5; col++) {
            if (board[row][col] == player &&
                board[row][col + 1] == player &&
                board[row][col + 2] == player &&
                board[row][col + 3] == player &&
                board[row][col + 4] ==player) {
                return 1;}}}

    for (int col = 0; col < COLUMNS; col++) {
        for (int row = 0; row <= ROWS - 5; row++) {
            if (board[row][col] == player &&
                board[row + 1][col] == player &&
                board[row + 2][col] == player &&
                board[row + 3][col] == player &&
                board[row + 4][col] == player) {
                return 1;}}}

    for (int row = 4; row < ROWS; row++) {
        for (int col = 0; col <= COLUMNS - 5; col++) {
            if (board[row][col] == player &&
                board[row - 1][col + 1] == player &&
                board[row - 2][col + 2] == player &&
                board[row - 3][col + 3] == player &&
                board[row - 4][col + 4] == player) {
                return 1;}}}
for (int row = 4; row < ROWS; row++) {
        for (int col = 4; col < COLUMNS; col++) {
            if (board[row][col] == player &&
                board[row - 1][col - 1] == player &&
                board[row - 2][col - 2] == player &&
                board[row - 3][col - 3] == player &&
                board[row - 4][col - 4] == player ) {
                return 1;}}}

    for (int row = 0; row < ROWS - 4; row++) {
        for (int col = 0; col < COLUMNS - 4; col++) {
            if (board[row][col] == player &&
                board[row + 1][col + 1] == player &&
                board[row + 2][col + 2] == player &&
                board[row + 3][col + 3] == player &&
                board[row + 4][col + 4] == player) {
                return 1;}}}

    for (int row = 0; row < ROWS - 4; row++) {
        for (int col = COLUMNS - 1; col >= 4; col--) {
            if (board[row][col] == player &&
                board[row + 1][col - 1] == player &&
                board[row + 2][col - 2] == player &&
                board[row + 3][col - 3] == player &&
                board[row + 4][col - 4] == player ) {
                return 1;}}}
    }

    return 0;
}
char fun(int currentplayer)
{
        switch(currentplayer)
        {
            case 1:
            return 'X';
            case 2:
            return 'O';
            case 3:
            return 'Y';
            case 4:
            return 'Z';
            case 5:
            return 'A';
        }}
int fun1(int currentPlayer,int players)
{
    switch(players)
    {
        case 2:
        {currentPlayer = (currentPlayer == 1) ? 2 : 1;
        return currentPlayer;}
        case 3:
        {
            switch(currentPlayer)
            {
            case 1:
                currentPlayer=2;
                break;
            case 2:
                currentPlayer=3;
                break;
            case 3:
                currentPlayer=1;
                break;
            }
            return currentPlayer;
        }
        case 4:
        {
            switch(currentPlayer)
            {
            case 1:
                currentPlayer=2;
                break;
            case 2:
                currentPlayer=3;
                break;
            case 3:
                currentPlayer=4;
                break;
            case 4:
                currentPlayer=1;
                break;
            }
            return currentPlayer;
        }
        case 5:
        {
            switch(currentPlayer)
            {
            case 1:
                currentPlayer=2;
                break;
            case 2:
                currentPlayer=3;
                break;
            case 3:
                currentPlayer=4;
                break;
            case 4:
                currentPlayer=5;
                break;
            case 5:
                currentPlayer=1;
                break;
            }
            return currentPlayer;
        }
    }
}
int main() {
    int ROWS,COLUMNS,players;
    int connect;
    printf("enter 4 for connect 4 or 5 for connect 5\n");
    scanf("%d",&connect);
    while(!(connect==4|connect==5))
    {
        printf("4,5 are the only valid inputs\n");
        scanf("%d",&connect);
    }
    printf("enter number of rows greater than 6\n");
    scanf("%d",&ROWS);
    printf("enter number ofcolumns greater than 6\n");
    scanf("%d",&COLUMNS);
    printf("enter number of players less than 5\n");
    scanf("%d",&players);
    while(players>5)
    {
    printf("enter number of players less than 5\n");
    scanf("%d",&players);
    }

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

        if (push(col,fun(currentPlayer),ROWS,COLUMNS,board)) {
            if (checkWin(fun(currentPlayer),ROWS,COLUMNS,board,connect)) {
                printBoard(ROWS,COLUMNS,board);
                printf("Player %d wins!\n", currentPlayer);
                printf("### ##   ####       ##     ##  ##   ### ###  ### ##            ##   ##    ####   ###  ##   ## ##   \n");
                printf(" ##  ##   ##         ##    ##  ##    ##  ##   ##  ##           ##   ##     ##      ## ##  ##   ##  \n");
                printf(" ##  ##   ##       ## ##   ##  ##    ##       ##  ##           ##   ##     ##     # ## #  ####     \n");
                printf(" ##  ##   ##       ##  ##   ## ##    ## ##    ## ##            ## # ##     ##     ## ##    #####   \n");
                printf(" ## ##    ##       ## ###    ##      ##       ## ##            # ### #     ##     ##  ##      ###  \n");
                printf(" ##       ##  ##   ##  ##    ##      ##  ##   ##  ##            ## ##      ##     ##  ##  ##   ##  \n");
                printf("####     ### ###  ###  ##    ##     ### ###  #### ##           ##   ##    ####   ###  ##   ## ##   \n");
            
                break;
            }
            moves++;
            if (moves == ROWS * COLUMNS) {
                printf("It's a draw!\n");
                printBoard(ROWS,COLUMNS,board);
                break;
            }
            currentPlayer=fun1(currentPlayer,players);
        } 
        else {
            printf("Column is full. Try again.\n");
        }
    }
    return 0;
}
