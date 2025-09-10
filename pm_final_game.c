#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define max_size 10
#define max_players 10

char board[max_size][max_size];
int N;

void initBoard() {
    for (int i=0; i<N; i++)
        for (int j=0; j<N; j++)
            board[i][j] = ' ';
}

void printBoard() {
    for (int i=0; i<N; i++) {
        for (int j=0; j<N; j++) {
            printf(" %c ", board[i][j]);
            if (j < N - 1) printf("|");
        }
        printf("\n");
        if (i < N - 1) {
            for (int j=0; j<N; j++) {
                printf("---");
                if (j < N - 1) printf("+");
            }
            printf("\n");
        }
    }
}

int isWin(char symbol) {
    for (int i=0; i<N; i++) {
        int row = 0, col = 0;
        for (int j=0; j<N; j++) {
            if (board[i][j] == symbol) row++;
            if (board[j][i] == symbol) col++;
        }
        if (row == N || col == N) return 1;
    }
    int diag1 = 0, diag2 = 0;
    for (int i=0; i<N; i++) {
        if (board[i][i] == symbol) diag1++;
        if (board[i][N - i - 1] == symbol) diag2++;
    }
    if (diag1 == N || diag2 == N) return 1;
    return 0;
}

int isDraw() {
    for (int i=0; i<N; i++)
        for (int j=0; j<N; j++)
            if (board[i][j] == ' ') return 0;
    return 1;
}

int isValidMove(int x, int y) {
    if (x < 0 || x >= N || y < 0 || y >= N) return 0;
    if (board[x][y] != ' ') return 0;
    return 1;
}

void playerMove(char symbol) {
    int x, y;
    while (1) {
        printf("Enter row (0 to %d): ", N - 1);
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
        printf("Player 1's chance (%c):\n", p1);
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
        printf("Player 2's chance (%c):\n", p2);
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
    char user = 'X', comp = 'O';
    initBoard();
    printBoard();
    while (1) {
        printf("Your chance (%c):\n", user);
        playerMove(user);
        printBoard();
        if (isWin(user)) {
            printf("You win!\n");
            break;
        }
        if (isDraw()) {
            printf("Game draw!\n");
            break;
        }
        printf("Computer's chance (%c):\n", comp);
        computerMove(comp);
        printBoard();
        if (isWin(comp)) {
            printf("Computer wins!\n");
            break;
        }
        if (isDraw()) {
            printf("Game draw!\n");
            break;
        }
    }
}

void multiplayerMode(int players, int roles[]) {
    char symbols[max_players] = {'X','O','Z','A','B','C','D','E','F','G'};
    initBoard();
    printBoard();
    int chance = 0;
    while (1) {
        printf("Player %d's chance (%c):\n", chance + 1, symbols[chance]);
        if (roles[chance] == 0)
            playerMove(symbols[chance]);
        else
            computerMove(symbols[chance]);
        printBoard();
        if (isWin(symbols[chance])) {
            printf("Player %d (%c) wins!\n", chance + 1, symbols[chance]);
            break;
        }
        if (isDraw()) {
            printf("Game draw!\n");
            break;
        }
        chance = (chance + 1) % players;
    }
}

int main() {
    int mode, players;
    int roles[max_size];
    srand(time(NULL));
    printf("Enter board size (3 to 10): ");
    scanf("%d", &N);
    if (N < 3 || N > 10) {
        printf("Invalid board size.\n");
        return 1;
    }
    printf("Select mode:\n1. Two Players\n2. Player vs Computer\n3. Multiplayer (up to 10 players)\n");
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
        int humanExists = 0;
        for (int i = 0; i < players; i++) {
            printf("Is Player %d a computer? (1 = Yes, 0 = No): ", i + 1);
            scanf("%d", &roles[i]);
            if (roles[i] == 0) humanExists = 1;
        }
        if (humanExists == 0) {
            printf("At least one player must be human.\n");
            return 1;
        }
        multiplayerMode(players, roles);
    } else {
        printf("Invalid mode.\n");
    }
    return 0;
}

