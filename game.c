#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include "printer.h"
#include "board.h"

int main(int argc, char **argv) {
  int option, height = 10, width = 15, mine_count = 10;
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
    }

  int flag_count = mine_count;

  // setup the board
  Cell board[height][width];
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
