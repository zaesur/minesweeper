#include "board.h"
#include "game.h"

void click_cell(game_t *game, int row, int column) {
  cell_t *cell = &game->board[row][column];

  if (cell.has_mine) {
    game->lost = true;
  } else if (cell.neighbouring_mine_count != 0) {
    c->is_revealed = true;
  } else {
    flood_cells(game_t *game, int row, int column);
  }
}

void flood_cells(game_t *game, int row, int column) {
  cell_t *cell = &game->board[row][column];

  if (cell.neighbouring_mine_count == 0 && !cell.is_revealed) {
    c->is_revealed = true;
    for (int p = fmax(0, m - 1); p < fmin(game->height, m + 2); p++) {
      for (int q = fmax(0, n - 1); q < fmin(game->width, n + 2); q++) {
        flood_cells(game, p, q);
      };
    }; 
  }; 
}
