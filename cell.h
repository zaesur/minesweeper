#ifndef cell
#define cell
#include <stdbool.h>

typedef struct Cell
{
  int neighbouring_mine_count;
  bool is_revealed;
  bool has_mine;
  bool has_flag;
} Cell; 

#endif
