#include "board.h"

void place_mines(int columns, int rows, int mine_count, cell_t **board) {
  // initialize the seed so the mines are truly random
  srand(time(0));

  // place the mines
  for (int i = 0; i < mine_count; i++) { 
    int m, n; 

    // look for a cell that does not have a mine
    do { 
      m = rand() % columns;
      n = rand() % rows;
    } while (board[m][n].has_mine);

    // place the mine
    board[m][n].has_mine = true; 

    // increment mine count for neighbouring cells
    for (int p = fmax(0, m - 1); p < fmin(columns, m + 2); p++) {
      for (int q = fmax(0, n - 1); q < fmin(rows, n + 2); q++) {
        board[p][q].neighbouring_mine_count++;
      };
    };
  }; 
};

cell_t **create_board(int columns, int rows, int mine_count) {
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

  place_mines(columns, rows, mine_count, board);
  return board; 
}

void free_board(cell_t **board, int columns) {
  while (columns) free(board[--columns]);
  free(board);
}
