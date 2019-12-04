#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <SDL2/SDL.h>
#include "board.h"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 400

int main(int argc, char **argv) {
  // setup SDL
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    fprintf(stderr, "Could not initialize sdl2: %s\n", SDL_GetError());
    return EXIT_FAILURE;
  }

  // setup window
  SDL_Window *window = SDL_CreateWindow("Minesweeper",
                                        100, 100,
                                        SCREEN_WIDTH, SCREEN_HEIGHT,
                                        SDL_WINDOW_SHOWN);

  if (window == NULL) {
    fprintf(stderr, "SDL_CreateWindow Error: %s\n", SDL_GetError());
    return EXIT_FAILURE;
  }

  SDL_Renderer *renderer = SDL_CreateRenderer(window, -1,
                                              SDL_RENDERER_ACCELERATED |
                                              SDL_RENDERER_PRESENTVSYNC);

  if (renderer == NULL) {
    SDL_DestroyWindow(window);
    fprintf(stderr, "SDL_CreateRenderer Error: %s\n", SDL_GetError());
    return EXIT_FAILURE;
  }

  SDL_Event e;
  int quit = 0;

  while(!quit) {
    while (SDL_PollEvent(&e)) {
      switch (e.type) {
        case SDL_QUIT:
          quit = 1;
          break;
        default: {}
      }

      SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
      SDL_RenderClear(renderer);
      SDL_RenderPresent(renderer);
    }
  }

  SDL_DestroyWindow(window);
  SDL_Quit();
  
  return EXIT_SUCCESS;

 // // declare variables
 // int height, width, mine_count, flag_count;

 // // process command line arguments
 // // TODO: handle insufficient arguments
 // int option;
 // while ((option = getopt(argc, argv, "w:h:m:f:")) != -1)
 //   switch (option) {
 //     case 'w':
 //       width = atoi(optarg);
 //       break;
 //     case 'h':
 //       height = atoi(optarg);
 //       break;
 //     case 'm':
 //       mine_count = atoi(optarg);
 //       break;
 //     case 'f':
 //       break;
 //     default:
 //       abort();
 //   }

 // flag_count = mine_count;

 // // setup the board
 // cell **board = initialize_board(height, width);
 // place_mines(height, width, mine_count, board);

 // // game loop
 // int m, n;
 // bool lost = false;

 // do {
 //   print_board(height, width, board, 5);

 //   // ask input
 //   do {
 //     printf("Please select a column number\n");
 //     scanf("%d", &n);
 //   } while (!(n >= 0 && n < width));

 //   do {
 //     printf("Please select a row number\n");
 //     scanf("%d", &m); 
 //   } while (!(m >= 0 && m < width));
 //   
 //   // check if the player lost, else play
 //   if (board[m][n].has_mine) {
 //     lost = true;
 //   } else {
 //     reveal_cell(height, width, board, m, n);
 //   }
 // } while (!lost);

 // printf("You lost!\n");
 // return 0;
}
