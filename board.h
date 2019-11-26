#include "cell.h"
void initialize_board(int length, int width, Cell board[length][width]);
void place_mines(int length, int width, struct Cell board[length][width]);
void reveal_cell(int length, int width, struct Cell board[length][width], int m, int n);
void flag_cell(int length, int width, struct Cell board[length][width], int m, int n);
