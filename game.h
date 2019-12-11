#ifndef GAME_H_
#define GAME_H_
#include "board.h"
typedef struct {
  bool lost;
  int rows;
  int columns;
  int mine_count;
  int flag_count;
  cell_t **board;
} game_t;

void click_cell(game_t *game, int column, int row);
void flag_cell(game_t *game, int column, int row);
#endif // GAME_H_
