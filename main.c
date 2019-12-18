#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include "game.h"
#include "rendering.h"
#include "file.h"

int main(int argc, char *argv[]) {
  game_t game;

  /* process command line arguments */
  int option;
  while ((option = getopt(argc, argv, "w:h:m:f:")) != -1) {
    /* if we encounter -f we override other flags */
    if (option == 'f') {
        load(&game, optarg);
        break;
    }

    /* else we switch */
    switch (option) {
      case 'w':
        game.columns = atoi(optarg);
        break;
      case 'h':
        game.rows = atoi(optarg);
        break;
      case 'm':
        game.mine_count = game.flag_count = atoi(optarg);
        break;
      default:
        abort();
    }
  }

  if (argc < 1) {
    printf("missing arguments\n");
    exit(1);
  }

  if (game.mine_count > 0) {
    game.board = create_board(game.columns, game.rows);
    place_mines(&game);
  } 

  initialize_gui(game.columns, game.rows);

  while (!game.lost) {
    render_game(&game);
    read_input(&game);
  }

  free_board(game.board, game.columns);
  free_gui(); 

  return EXIT_SUCCESS;
}
