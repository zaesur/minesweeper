#include <stdio.h> 
#include "cell.h"

void print_flags(int flags) {
  printf("\nRemaining flags: %d\n", flags);
}

void print_header(int length) {
  printf("     ");
  for (int i = 0; i < length; i++) {
    printf("%d   ", i);
  };
  printf(" \n");
}

char choose_symbol(Cell c) {
  if (c.has_flag) {
    return 'F';
  } else if (!c.is_revealed) {
    return ' ';
  } else {
    return c.neighbouring_mine_count + '0';
  };
} 

void print_row(int m, int width, struct Cell board[][width]) {
  printf("%d  ", m);
  for (int n = 0; n < width; n++) {
    printf("| %c|", choose_symbol(board[m][n]));
  };
  printf("\n");
} 

void print_rows(int length, int width, struct Cell board[length][width]) {
  for (int m = 0; m < length; m++) {
    print_row(m, width, board);
  };
} 

void print_board(int length, int width, struct Cell board[length][width], int flags) {
  print_flags(flags);
  print_header(length);
  print_rows(length, width, board);
} 
