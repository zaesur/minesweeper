#ifndef RENDERER_H_
#define RENDERER_H_
#include <SDL2/SDL.h>
#include <stdbool.h>
#include "board.h"
#include "game.h"
#include "file.h"
#define IMAGE_HEIGHT 50
#define IMAGE_WIDTH 50
#define NUMBER_OF_TEXTURES 11
void initialize_gui(int columns, int rows);
void render_game(game_t *game);
void read_input(game_t *game);
void free_gui();
#endif // RENDERER_H_
