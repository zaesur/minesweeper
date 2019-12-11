#include <stdio.h>
#include <stdbool.h> 
#include <stdlib.h> 
#include <time.h>
#include <math.h>
#include "board.h"

void place_mines(int height, int width, int mine_count, cell_t **board) {
  // initialize the seed so the mines are truly random
  srand(time(0));

  // place the mines
  for (int i = 0; i < mine_count; i++) { 
    int m, n; 

    // look for a cell that does not have a mine
    do { 
      m = rand() % height;
      n = rand() % width;
    } while (board[m][n].has_mine);

    // place the mine
    board[m][n].has_mine = true; 

    // increment mine count for neighbouring cells
    for (int p = fmax(0, m - 1); p < fmin(height, m + 2); p++) {
      for (int q = fmax(0, n - 1); q < fmin(width, n + 2); q++) {
        board[p][q].neighbouring_mine_count++;
      };
    };
  }; 
};

cell_t **create_board(int height, int width, int mine_count) {
  cell_t **board; 

  // allocate space for the board
  board = (cell_t **)malloc(sizeof(cell_t *) * height);

  for (int m = 0; m < height; m++) {
    board[m] = (cell_t *)malloc(sizeof(cell_t) * width);
    for (int n = 0; n < width; n++) {
      cell_t c = { 
        .neighbouring_mine_count = 0,
        .has_mine = false,
        .has_flag = false,
        .is_revealed = false
      };
      board[m][n] = c;
    };
  };

  place_mines(height, width, mine_count, board);
  return board; 
}
