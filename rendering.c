#include <SDL2/SDL.h>
#include <stdbool.h>
#include "board.h"
#include "game.h"
#include "rendering.h"

SDL_Renderer *renderer;
SDL_Window *window;
char *paths[NUMBER_OF_TEXTURES] = { 
  "images/0.bmp",
  "images/1.bmp",
  "images/2.bmp",
  "images/3.bmp",
  "images/4.bmp",
  "images/5.bmp",
  "images/6.bmp",
  "images/7.bmp",
  "images/8.bmp",
  "images/covered.bmp",
  "images/flagged.bmp"
}; 

SDL_Texture *textures[NUMBER_OF_TEXTURES];

void initialize_window(const char *title, int rows, int columns) {
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    printf("Could not initialize SDL: %s\n", SDL_GetError());
    exit(1);
  }

  window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, IMAGE_WIDTH * columns, IMAGE_HEIGHT * rows, SDL_WINDOW_SHOWN);

  if (window == NULL) {
    printf("Couldn't set screen mode to required dimensions: %s\n", SDL_GetError());
    exit(1);
  }

  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
}


void initialize_textures() {
  for (int i = 0; i < NUMBER_OF_TEXTURES; i++) {
    // Import the texture
    SDL_Surface *surface = SDL_LoadBMP(paths[i]);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    // Save it
    textures[i] = texture;
  };
}

void initialize_gui(int rows, int columns) {
  initialize_window("Minesweeper", rows, columns);
  initialize_textures();
}

void render_cell(SDL_Rect *rectangle, cell_t *cell) {
  SDL_Texture *texture = cell->has_flag
   ? textures [10]
   : cell->is_revealed
   ? textures[cell->neighbouring_mine_count]
   : textures[9];
  SDL_RenderCopy(renderer, texture, NULL, rectangle);
}

void render_game(game_t *game) {
  SDL_RenderClear(renderer);
  for (int m = 0; m < game->columns; m++) {
    for (int n = 0; n < game->rows; n++) {
      cell_t cell = game->board[m][n];
      SDL_Rect rectangle = { m * IMAGE_WIDTH, n * IMAGE_HEIGHT, IMAGE_WIDTH, IMAGE_HEIGHT };
      render_cell(&rectangle, &cell);
    };
  };
  SDL_RenderPresent(renderer);
}

void free_gui() {
  for (int i = 0; i < NUMBER_OF_TEXTURES; i++) {
    SDL_DestroyTexture(textures[i]);
  };

  SDL_DestroyWindow(window);
  SDL_DestroyRenderer(renderer);

  SDL_Quit();
}
