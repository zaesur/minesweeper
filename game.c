#include "game.h"

void flood_cells(game_t *game, int column, int row) {
  cell_t cell = game->board[column][row];

  game->board[column][row].is_revealed = true;

  if (cell.neighbouring_mine_count == 0 && !cell.is_revealed) {
    for (int m = fmax(0, column - 1); m < fmin(game->columns, column + 2); m++) {
      for (int n = fmax(0, row - 1); n < fmin(game->rows, row + 2); n++) {
        flood_cells(game, m, n);
      };
    }; 
  }
}

void click_cell(game_t *game, int column, int row) {
  cell_t *cell = &game->board[column][row];

  if (cell->has_mine) {
    game->lost = true;
  } else if (cell->neighbouring_mine_count > 0) {
    cell->is_revealed = true;
  } else {
    flood_cells(game, column, row);
  }
}

void flag_cell(game_t *game, int column, int row) {
  game->board[column][row].has_flag = true;
}
