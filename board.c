#include <stdio.h>
#include <stdbool.h> 
#include <stdlib.h> 
#include <time.h>
#define MINECOUNT 15
#define MAX(a,b) ((a) > (b) ? (a) : (b))
#define MIN(a,b) ((a) < (b) ? (a) : (b)) 

typedef struct cell {
  int neighbouring_mine_count;
  bool is_revealed;
  bool has_mine;
  bool has_flag;
} cell;

void initialize_board(int height, int width, struct cell board[height][width]) {
  for (int m = 0; m < height; m++) {
    for (int n = 0; n < width; n++) {
      cell c = { 0, false, false, false };
      board[m][n] = c;
    };
  };
};

void place_mines(int height, int width, cell board[height][width]) {
  // initialize the seed so the mines are truly random
  srand(time(0));

  // place the mines
  for (int i = 0; i < MINECOUNT; i++) { 
    int m, n; 

    // look for a cell that does not have a mine
    do { 
      m = rand() % height;
      n = rand() % width;
    } while (board[m][n].has_mine);

    // place the mine
    board[m][n].has_mine = true; 

    // increment mine count for neighbouring cells
    for (int p = MAX(0, m - 1); p < MIN(height, m + 2); p++) {
      for (int q = MAX(0, n - 1); q < MIN(width, n + 2); q++) {
        board[p][q].neighbouring_mine_count++;
      };
    };
  }; 
};

void reveal_cell(int height, int width, cell board[height][width], int m, int n) {
  // if the cell hasn't been revealed and its neighbouring mine 
  // count is 0, also reveal neighbours

  cell c = board[m][n];

  board[m][n].is_revealed = true;

  if (c.neighbouring_mine_count == 0 && !c.is_revealed) {
    for (int p = MAX(0, m - 1); p < MIN(height, m + 2); p++) {
      for (int q = MAX(0, n - 1); q < MIN(width, n + 2); q++) {
        reveal_cell(height, width, board, p, q);
      };
    }; 
  }; 
};

void flag_cell(cell *c) {
  c->has_flag = !c->has_flag;
};

void print_flags(int flags) {
  printf("\nRemaining flags: %d\n", flags);
}

void print_header(int height) {
  printf("     ");
  for (int i = 0; i < height; i++) {
    printf("%d   ", i);
  };
  printf(" \n");
}

char choose_symbol(cell *c) {
  if (c->has_flag) {
    return 'F';
  } else if (!c->is_revealed) {
    return ' ';
  } else {
    return c->neighbouring_mine_count + '0';
  };
} 

void print_row(int m, int width, cell board[][width]) {
  printf("%d  ", m);
  for (int n = 0; n < width; n++) {
    printf("| %c|", choose_symbol(&board[m][n]));
  };
  printf("\n");
} 

void print_rows(int height, int width, cell board[height][width]) {
  for (int m = 0; m < height; m++) {
    print_row(m, width, board);
  };
} 

void print_board(int height, int width, cell board[height][width], int flags) {
  print_flags(flags);
  print_header(height);
  print_rows(height, width, board);
} 
