#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <SDL2/SDL.h>
#include "board.h"
#include "game.h"
#include "rendering.h"

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

  if (!(height & width & mine_count)) {
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

  initialize_gui(height, width);
  SDL_Event e;
  bool quit = false;
  while (!quit) {
    while (SDL_PollEvent(&e)) {
      if (e.type == SDL_QUIT) {
        quit = true;
      }
    }
    render_game(&game);
  }
  free_gui(); 

  return EXIT_SUCCESS;
}
