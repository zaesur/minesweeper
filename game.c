#include <stdio.h>
#include <stdbool.h>
#include "printer.h"
#include "board.h"

int main() {
  // ask for preferences
  int length, width, mine_count, flag_count;

  do {
    printf("Please select a length\n");
    scanf("%d", &length);
  } while (!(length > 0 && length < 10));

  do {
    printf("Please select a width\n");
    scanf("%d", &width);
  } while (!(width > 0 && width < 10));

  mine_count = length * width / 5;
  flag_count = mine_count;

  // setup the board
  Cell board[length][width];
  initialize_board(length, width, board);
  place_mines(length, width, board);

  // game loop
  int m, n;
  bool lost = false;

  do {
    print_board(length, width, board, 5);

    // ask input
    do {
      printf("Please select a column number\n");
      scanf("%d", &n);
    } while (!(n >= 0 && n < width));

    do {
      printf("Please select a row number\n");
      scanf("%d", &m); 
    } while (!(m >= 0 && m < width));
    
    // check if the player lost, else play
    if (board[m][n].has_mine) {
      lost = true;
    } else {
      reveal_cell(length, width, board, m, n);
    }
  } while (!lost);

  printf("You lost!\n");
  return 0;
}
