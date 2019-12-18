#include "board.h"

cell_t **create_board(int columns, int rows) {
  cell_t **board; 

  // allocate space for the board
  board = (cell_t **)malloc(sizeof(cell_t *) * columns);

  for (int m = 0; m < columns; m++) {
    board[m] = (cell_t *)malloc(sizeof(cell_t) * rows);
    for (int n = 0; n < rows; n++) {
      cell_t c = { 
        .neighbouring_mine_count = 0,
        .has_mine = false,
        .has_flag = false,
        .is_revealed = false
      };
      board[m][n] = c;
    };
  };

  return board; 
}

void free_board(cell_t **board, int columns) {
  while (columns) free(board[--columns]);
  free(board);
}
