#ifndef BOARD_H_
#define BOARD_H_

typedef struct {
  int neighbouring_mine_count;
  bool has_mine;
  bool has_flag;
  bool is_revealed;
} cell_t;

cell_t **create_board(int height, int width, int mine_count);
#endif // BOARD_H_
