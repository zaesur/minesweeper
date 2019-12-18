#ifndef FILE_H_
#define FILE_H_
#include <stdio.h>
#include "game.h"
void save(game_t *game);
void load(game_t *game, char path[]);
#endif // FILE_H_
