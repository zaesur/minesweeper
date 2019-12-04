#ifndef BOARD_H_
#define BOARD_H_

typedef struct {
  int neighbouring_mine_count;
  bool has_mine;
  bool has_flag;
  bool is_revealed;
} cell;

cell **initialize_board(int length, int width);
void place_mines(int length, int width, int mine_count, cell **board);
void reveal_cell(int length, int width, cell **board, int m, int n);
void flag_cell(cell *c);
void print_board(int length, int width, cell **board, int flags);

#endif // BOARD_H_
