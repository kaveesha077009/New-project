#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 10

char board[MAX][MAX];
int N;

void initBoard() {
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            board[i][j] = ' ';
}

void printBoard() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf(" %c ", board[i][j]);
            if (j < N - 1) printf("|");
        }
        printf("\n");
        if (i < N - 1) {
            for (int j = 0; j < N; j++) {
                printf("---");
                if (j < N - 1) printf("+");
            }
            printf("\n");
        }
    }
}

int isWin(char symbol) {
    for (int i = 0; i < N; i++) {
        int row = 0, col = 0;
        for (int j = 0; j < N; j++) {
            if (board[i][j] == symbol) row++;
            if (board[j][i] == symbol) col++;
        }
        if (row == N || col == N) return 1;
    }
    int diag1 = 0, diag2 = 0;
    for (int i = 0; i < N; i++) {
        if (board[i][i] == symbol) diag1++;
        if (board[i][N - i - 1] == symbol) diag2++;
    }
    if (diag1 == N || diag2 == N) return 1;
    return 0;
}

int isDraw() {
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            if (board[i][j] == ' ') return 0;
    return 1;
}

int isValidMove(int x, int y) {
    return x >= 0 && x < N && y >= 0 && y < N && board[x][y] == ' ';
}

void playerMove(char symbol) {
    int x, y;
    while (1) {
        printf("Enter row  (0 to %d): ", N - 1);
        scanf("%d", &x);
        printf("Enter column (0 to %d): ", N - 1);
        scanf("%d", &y);
        if (isValidMove(x, y)) {
            board[x][y] = symbol;
            break;
        } else {
            printf("Invalid move. Try again.\n");
        }
    }
}

void computerMove(char symbol) {
    int x, y;
    while (1) {
        x = rand() % N;
        y = rand() % N;
        if (isValidMove(x, y)) {
            board[x][y] = symbol;
            printf("Computer placed at %d %d\n", x, y);
            break;
        }
    }
}

void twoPlayerMode() {
    char p1 = 'X', p2 = 'O';
    initBoard();
    printBoard();
    while (1) {
        printf("Player 1's chance:\n");
        playerMove(p1);
        printBoard();
        if (isWin(p1)) {
            printf("Player 1 wins!\n");
            break;
        }
        if (isDraw()) {
            printf("Game draw!\n");
            break;
        }
        printf("Player 2's chance:\n");
        playerMove(p2);
        printBoard();
        if (isWin(p2)) {
            printf("Player 2 wins!\n");
            break;
        }
        if (isDraw()) {
            printf("Game draw!\n");
            break;
        }
    }
}

void vsComputerMode() {
    char player = 'X', computer = 'O';
    initBoard();
    printBoard();
    while (1) {
        printf("Your chance:\n");
        playerMove(player);
        printBoard();
        if (isWin(player)) {
            printf("You win!\n");
            break;
        }
        if (isDraw()) {
            printf("game draw!\n");
            break;
        }
        printf("Computer's chance:\n");
        computerMove(computer);
        printBoard();
        if (isWin(computer)) {
            printf("Computer wins!\n");
            break;
        }
        if (isDraw()) {
            printf("Game draw!\n");
            break;
        }
    }
}

void multiplayerMode(int players) {
    char symbols[MAX] = {'A','B','C','D','E','F','G','H','I','J'};
    initBoard();
    printBoard();
    int chance = 0;
    while (1) {
        printf("Player %d (%c)'s chance:\n", chance + 1, symbols[chance]);
        playerMove(symbols[chance]);
        printBoard();
        if (isWin(symbols[chance])) {
            printf("Player %d wins!\n", chance + 1);
            break;
        }
        if (isDraw()) {
            printf("It's a draw!\n");
            break;
        }
        chance = (chance + 1) % players;
    }
}

int main() {
    int mode, players;
    srand(time(NULL));
    printf("Enter board size (3 to 10): ");
    scanf("%d", &N);
    if (N < 3 || N > 10) {
        printf("Invalid board size.\n");
        return 1;
    }
    printf("Select mode:\n1. Two Players\n2. Player vs Computer\n3. Multiplayer\n");
    scanf("%d", &mode);
    if (mode == 1) {
        twoPlayerMode();
    } else if (mode == 2) {
        vsComputerMode();
    } else if (mode == 3) {
        printf("Enter number of players (3 to 10): ");
        scanf("%d", &players);
        if (players < 3 || players > 10) {
            printf("Invalid number of players.\n");
            return 1;
        }
        multiplayerMode(players);
    } else {
        printf("Invalid mode.\n");
    }
    return 0;
}

