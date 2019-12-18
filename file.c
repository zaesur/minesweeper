#include "file.h" 

void write_cell(FILE *fp, cell_t *cell) {
  char content = cell->has_mine ? 'm' : cell->neighbouring_mine_count + '0';
  char state = cell->has_flag ? 'f' : cell->is_revealed ? 'r' : 'u'; 
  fprintf(fp, "%c%c", content, state);
}

void save(game_t *game) {
  /* open the file */
  FILE *fp = fopen("game.txt", "w");

  if (fp == NULL) {
    printf("Error opening file!\n");
    exit(1);
  }

  /* save the header */
  fprintf(fp, "%d %d %d\n", game->columns, game->rows, game->flag_count);

  /* save the state */
  for (int column = 0; column < game->columns; column++) {
    for (int row = 0; row < game->rows; row++) {
      write_cell(fp, &game->board[column][row]);
    }
    fputs("\n", fp);
  }

  /* close the file */
  fclose(fp);
} 

void load_cell(FILE *fp, cell_t *cell) {
  char content, state;
  content = fgetc(fp);
  state = fgetc(fp);

  if (content == '\n' || state == '\n') {
    puts("Did not expect a line break");
    exit(1);
  }

  if (content == 'm') {
    cell->has_mine = true;
  } else {
    cell->neighbouring_mine_count = content - '0';
  }

  switch (state) {
    case 'f':
      cell->has_flag = true;
      break;
    case 'r':
      cell->is_revealed = true;
      break;
    default:
      break;
  }
}

void load(game_t *game, char path[]) {
  /* open the file */
  FILE *fp = fopen(path, "r");

  if (fp == NULL) {
    puts("Error opening file!\n");
    exit(1);
  }

  fscanf(fp, "%d %d %d\n", &game->columns, &game->rows, &game->flag_count);
  
  /* initialize the game */
  game->mine_count = 0;
  game->board = create_board(game->columns, game->rows);

  /* fill in the data */
  for (int column = 0; column < game->columns; column++) {
    for (int row = 0; row < game->rows; row++) {
      load_cell(fp, &game->board[column][row]);
    }
    if (fgetc(fp) != '\n') {
      puts("Expected a line break\n");
      exit(1);
    };
  }

  /* close the file */
  fclose(fp);
}

