#ifndef BOARD_H_
#define BOARD_H_
#include <stdbool.h> 
#include <stdlib.h> 
#include <time.h>
#include <math.h> 
typedef struct {
  int neighbouring_mine_count;
  bool has_mine;
  bool has_flag;
  bool is_revealed;
} cell_t;

cell_t **create_board(int columns, int rows, int mine_count);
void free_board(cell_t **board, int columns);
#endif // BOARD_H_
