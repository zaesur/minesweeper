#include <stdio.h>
#include <stdbool.h> 
#include <stdlib.h> 
#include <time.h>
#include "cell.h"
#define MINECOUNT 15
#define MAX(a,b) ((a) > (b) ? (a) : (b))
#define MIN(a,b) ((a) < (b) ? (a) : (b)) 

void initialize_board(int length, int width, Cell board[length][width]) {
  for (int m = 0; m < length; m++) {
    for (int n = 0; n < width; n++) {
      Cell c = { 0, false, false, false };
      board[m][n] = c;
    };
  };
};

void place_mines(int length, int width, Cell board[length][width]) {
  // initialize the seed so the mines are truly random
  srand(time(0));

  // place the mines
  for (int i = 0; i < MINECOUNT; i++) { 
    int m, n; 

    // look for a cell that does not have a mine
    do { 
      m = rand() % length;
      n = rand() % width;
    } while (board[m][n].has_mine);

    // place the mine
    board[m][n].has_mine = true; 

    // increment mine count for neighbouring cells
    for (int p = MAX(0, m - 1); p < MIN(length, m + 2); p++) {
      for (int q = MAX(0, n - 1); q < MIN(width, n + 2); q++) {
        board[p][q].neighbouring_mine_count++;
      };
    };
  }; 
};

void reveal_cell(int length, int width, Cell board[length][width], int m, int n) {
  // if the cell hasn't been revealed and its neighbouring mine 
  // count is 0, also reveal neighbours
  Cell c = board[m][n];

  // reveal the cell
  board[m][n].is_revealed = true;

  if (c.neighbouring_mine_count == 0 && !c.is_revealed) {
    for (int p = MAX(0, m - 1); p < MIN(length, m + 2); p++) {
      for (int q = MAX(0, n - 1); q < MIN(width, n + 2); q++) {
        reveal_cell(length, width, board, p, q);
      };
    }; 
  }; 
};

void flag_cell(int length, int width, Cell board[length][width], int m, int n) {
  Cell c = board[m][n];
  c.has_flag = !c.has_flag;
};
