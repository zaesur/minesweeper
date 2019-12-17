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

void initialize_window(const char *title, int columns, int rows) {
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

void initialize_gui(int columns, int rows) {
  initialize_window("Minesweeper", columns, rows);
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

void show_quit_popup(game_t *game) {
  const SDL_MessageBoxButtonData buttons[] = {
    { 0, 0, "Quit" },
    { SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 1, "Save" },
    { SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT, 2, "Cancel" },
  };

  const SDL_MessageBoxData messageboxdata = {
    SDL_MESSAGEBOX_INFORMATION,
    NULL,
    "Quit",
    "Do you want to save before quitting?",
    SDL_arraysize(buttons),
    buttons,
    NULL
  };

  int buttonid;

  SDL_ShowMessageBox(&messageboxdata, &buttonid);
  
  if (buttonid == 1) {
    save(game);
  }

  if (buttonid > 0) {
    game->lost = true;
  }

  return;  
}

void read_input(game_t *game) {
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    switch (event.type) {
      case SDL_QUIT:
        show_quit_popup(game);
        break;
      case SDL_MOUSEBUTTONDOWN:
        if (event.button.button == SDL_BUTTON_LEFT) {
          click_cell(game, event.button.x / IMAGE_WIDTH, event.button.y / IMAGE_HEIGHT);
        } else if (event.button.button == SDL_BUTTON_RIGHT) {
          flag_cell(game, event.button.x / IMAGE_WIDTH, event.button.y / IMAGE_HEIGHT);
        }
        break;
      default: {}
    }
  }
}

void free_gui() {
  for (int i = 0; i < NUMBER_OF_TEXTURES; i++) {
    SDL_DestroyTexture(textures[i]);
  };

  SDL_DestroyWindow(window);
  SDL_DestroyRenderer(renderer);

  SDL_Quit();
}
