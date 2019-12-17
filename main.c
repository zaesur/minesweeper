#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include "game.h"
#include "rendering.h"
#include "file.h"

int main(int argc, char *argv[]) {
  // declare variables
  int height, width, mine_count;

  // process command line arguments
  int option;
  while ((option = getopt(argc, argv, "w:h:m:f:")) != -1)
    switch (option) {
      case 'w':
        width = atoi(optarg);
        break;
      case 'h':
        height = atoi(optarg);
        break;
      case 'm':
        mine_count = atoi(optarg);
        break;
      case 'f':
        break;
      default:
        abort();
    }

  if (argc < 1) {
    printf("missing arguments\n");
    exit(1);
  }

  game_t game = {
    .lost = false,
    .rows = height,
    .columns = width,
    .mine_count = mine_count,
    .flag_count = mine_count,
    .board = create_board(height, width, mine_count),
  };

  initialize_gui(width, height);

  while (!game.lost) {
    render_game(&game);
    read_input(&game);
  }

  free_board(game.board, game.columns);
  free_gui(); 

  return EXIT_SUCCESS;
}
