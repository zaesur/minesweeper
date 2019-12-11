#ifndef GAME_H_
#define GAME_H_
typedef struct {
  bool lost;
  int rows;
  int columns;
  int mine_count;
  int flag_count;
  cell_t **board;
} game_t;

void click_cell(game_t *game, int row, int column);
#endif // GAME_H_
