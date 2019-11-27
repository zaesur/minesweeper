#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include "board.h"

int main(int argc, char **argv) {
  // declare variables
  int height = 10, width = 10, mine_count = height * width / 10;

  // process command line arguments
  int option;
  while ((option = getopt(argc, argv, "w:h:m:f:")) != -1)
    switch (option) {
      case 'w':
        width = atoi(optarg);
        break;
      case 'h':
        height = atoi(optarg);
        break;
      case 'm':
        mine_count = atoi(optarg);
        break;
      case 'f':
        break;
      default:
        abort();
    }

  int flag_count = mine_count;

  // setup the board
  cell board[height][width];
  initialize_board(height, width, board);
  place_mines(height, width, board);

  // game loop
  int m, n;
  bool lost = false;

  do {
    print_board(height, width, board, 5);

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
      reveal_cell(height, width, board, m, n);
    }
  } while (!lost);

  printf("You lost!\n");
  return 0;
}
