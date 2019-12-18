#include "game.h"

void place_mines(game_t *game) {
  /* initialize the seed so the mines are truly random */
  srand(time(0));

  /* place the mines */
  while (game->mine_count--) { 
    int m, n; 
    cell_t *cell;

    // look for a cell that does not have a mine
    do { 
      m = rand() % game->columns;
      n = rand() % game->rows;
      cell = &game->board[m][n];
    } while (cell->has_mine);

    /* place the mine*/
    cell->has_mine = true; 

    /* increment mine count for neighbouring cells */
    for (int p = fmax(0, m - 1); p < fmin(game->columns, m + 2); p++) {
      for (int q = fmax(0, n - 1); q < fmin(game->rows, n + 2); q++) {
        game->board[p][q].neighbouring_mine_count++;
      };
    };
  }; 
};

void flood_cells(game_t *game, int column, int row) {
  cell_t *cell = &game->board[column][row];
  bool was_unrevealed = !cell->is_revealed;
  cell->is_revealed = true;

  /* if a flag had been placed it should be removed */
  if (cell->has_flag) {
    cell->has_flag = false;
    game->flag_count++;
  }

  if (cell->neighbouring_mine_count == 0 && was_unrevealed) {
    for (int m = fmax(0, column - 1); m < fmin(game->columns, column + 2); m++) {
      for (int n = fmax(0, row - 1); n < fmin(game->rows, row + 2); n++) {
        flood_cells(game, m, n);
      };
    }; 
  }
}

void click_cell(game_t *game, int column, int row) {
  cell_t *cell = &game->board[column][row];
  
  /* if a flag had been placed it should be removed */
  if (cell->has_flag) {
    cell->has_flag = false;
    game->flag_count++;
  }

  if (cell->has_mine) {
    game->lost = true;
  } else if (cell->neighbouring_mine_count > 0) {
    cell->is_revealed = true;
  } else {
    flood_cells(game, column, row);
  }
}

void flag_cell(game_t *game, int column, int row) {
  cell_t *cell = &game->board[column][row];
  
  /* do nothing for revealed cells */
  if (cell->is_revealed) {
    return;
  }

  if (cell->has_flag) {
    cell->has_flag = false;
    game->flag_count++;
  } else if (game->flag_count > 0) {
    cell->has_flag = true;
    game->flag_count--;
  }
}
