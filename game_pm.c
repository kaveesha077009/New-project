#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <ctype.h>

#define MAX_SIZE 10
#define MAX_PLAYERS 10
#define MIN_SIZE 3
#define MIN_PLAYERS 3

char board[MAX_SIZE][MAX_SIZE];
int board_size;

void init_board() {
    for (int i=0; i < board_size; i++) {
    for (int j=0; j < board_size; j++) {
    board[i][j] = ' ';
}
}
}

void print_board() {
    printf("\n  ");
    for (int j=0; j < board_size; j++) {
    printf(" %d  ", j);
}
    printf("\n");
    for (int i=0; i < board_size; i++) {
    printf("%d ", i);
    for (int j=0; j < board_size; j++) {
        printf(" %c ", board[i][j]);
        if (j < board_size - 1) printf("|");
}
        printf("\n");
        if (i < board_size - 1) {
        printf("  ");
        for (int j=0; j < board_size; j++) {
            printf("---");
            if (j < board_size - 1) printf("+");
 }
            printf("\n");
}
}
    printf("\n");
}

bool is_valid_move(int row, int col) {
    return row >= 0 && row < board_size && col >= 0 && col < board_size && board[row][col] == ' ';
}

bool check_win(char symbol) {
    for (int i = 0; i < board_size; i++) {
        bool row_win = true, col_win = true;
        for (int j = 0; j < board_size; j++) {
         if (board[i][j] != symbol) row_win = false;
         if (board[j][i] != symbol) col_win = false;
}
        if (row_win || col_win) return true;
}
    bool diag1 = true, diag2 = true;
    for (int i = 0; i < board_size; i++) {
     if (board[i][i] != symbol) diag1 = false;
     if (board[i][board_size - i - 1] != symbol) diag2 = false;
}
    return diag1 || diag2;
}

bool is_draw() {
    for (int i = 0; i < board_size; i++) {
     for (int j = 0; j < board_size; j++) {
         if (board[i][j] == ' ') return false;
}
}
    return true;
}

int get_valid_input(const char* prompt, int min, int max) {
    int value;
    char buffer[100];
    bool valid = false;

    while (!valid) {
    printf("%s (%d-%d): ", prompt, min, max);
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
    printf("Error reading input. Try again.\n");
            continue;
     }
        if (sscanf(buffer, "%d", &value) != 1) {
            printf("Please enter a valid number.\n");
            continue;
     }
        if (value >= min && value <= max) {
            valid = true;
     }
      else {
            printf("Input must be between %d and %d.\n", min, max);
    }
}
    return value;
}

void user_move(char symbol, int player_num) {
    while (true) {
    printf("Player %d (%c), enter row and column (e.g., '0 0'): ", player_num, symbol);
        int row = get_valid_input("Row", 0, board_size - 1);
        int col = get_valid_input("Column", 0, board_size - 1);
    if (is_valid_move(row, col)) {
        board[row][col] = symbol;
            break;
    } 
    else {
            printf("Invalid move: position is taken or out of bounds. Try again.\n");
    }
    }
}

void computer_move(char symbol) {
    for (int i=0; i < board_size; i++) {
    for (int j=0; j < board_size; j++) {
         if (is_valid_move(i, j)) {
         board[i][j] = symbol;
            if (check_win(symbol)) {
            printf("Computer (%c) played at %d %d\n", symbol, i, j);
                    return;
}
    board[i][j] = ' ';
    board[i][j] = (symbol == 'X') ? 'O' : 'X';
    if (check_win((symbol == 'X') ? 'O' : 'X')) {
    board[i][j] = symbol;
    printf("Computer (%c) played at %d %d\n", symbol, i, j);
                    return;
}
                board[i][j] = ' ';
    }
    }
    }
    int row, col;
do {
        row = rand() % board_size;
        col = rand() % board_size;
    } while (!is_valid_move(row, col));
    printf("Computer (%c) played at %d %d\n", symbol, row, col);
    board[row][col] = symbol;
}

void play_two_players() {
    char symbols[2] = {'X', 'O'};
    int turn = 0;
    while (true) {
    print_board();
    user_move(symbols[turn], turn + 1);
    if (check_win(symbols[turn])) {
      print_board();
    printf("Player %d (%c) wins! Congratulations!\n", turn + 1, symbols[turn]);
            break;
 }
        if (is_draw()) {
            print_board();
            printf("It's a draw! Well played!\n");
            break;
}
        turn = 1 - turn;
}
}

void play_vs_computer() {
    char user_symbol, comp_symbol;
    printf("Choose your symbol (X or O): ");
    while (true) {
     scanf(" %c", &user_symbol);
     user_symbol = toupper(user_symbol);
     if (user_symbol == 'X' || user_symbol == 'O') break;
        printf("Please choose X or O: ");
}
    comp_symbol = (user_symbol == 'X') ? 'O' : 'X';
    int turn = (user_symbol == 'X') ? 0 : 1;
    while (true) {
        print_board();
        if (turn == 0) {
        user_move(user_symbol, 1);
 } 
 else {
     computer_move(comp_symbol);
}
    char current_symbol = (turn == 0) ? user_symbol : comp_symbol;
    if (check_win(current_symbol)) {
    print_board();
    printf("%s wins!\n", (turn == 0) ? "You" : "Computer");
            break;
}
    if (is_draw()) {
    print_board();
    printf("It's a draw! Nice try!\n");
            break;
}
        turn = 1 - turn;
    }
}

void play_multiplayer(int num_players) {
    char symbols[MAX_PLAYERS];
    for (int i = 0; i < num_players; i++) {
     symbols[i] = 'A' + i;
 }
    int turn = 0;
    while (true) {
        print_board();
        user_move(symbols[turn], turn + 1);
        if (check_win(symbols[turn])) {
        print_board();
        printf("Player %d (%c) wins! Great job!\n", turn + 1, symbols[turn]);
            break;
    }
        if (is_draw()) {
            print_board();
            printf("It's a draw! Good game, everyone!\n");
            break;
 }
        turn = (turn + 1) % num_players;
    }
}

int main() {
    srand(time(NULL));
    printf("Welcome to Tic-Tac-Toe!\n");
    board_size = get_valid_input("Enter board size", MIN_SIZE, MAX_SIZE);
    init_board();
    printf("\nChoose game mode:\n");
    printf("1. Two Players\n");
    printf("2. Play against Computer\n");
    printf("3. Multiplayer (%d-%d players)\n", MIN_PLAYERS, MAX_PLAYERS);
    int mode = get_valid_input("Enter choice", 1, 3);
    if (mode == 1) {
        play_two_players();
}
 else if (mode == 2) {
        play_vs_computer();
 } 
 else 
 {
    int num_players = get_valid_input("Enter number of players", MIN_PLAYERS, MAX_PLAYERS);
        play_multiplayer(num_players);
 }
    return 0;
}
