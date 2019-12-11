#ifndef RENDERER_H_
#define RENDERER_H_
#define IMAGE_HEIGHT 50
#define IMAGE_WIDTH 50
#define NUMBER_OF_TEXTURES 11
void initialize_gui(int rows, int columns);
void render_game(game_t *game);
void free_gui();
#endif // RENDERER_H_
