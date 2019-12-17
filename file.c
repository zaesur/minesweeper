#include "file.h" 

void save(game_t *game) {
  /* open the file */
  FILE *fp = fopen("game.txt", "w");

  if (fp == NULL) {
    printf("Error opening file!\n");
    exit(1);
  }

  /* save the data */
  fprintf(fp, "Rows: %d, Columns: %d\n", game->rows, game->columns);

  /* close the file */
  fclose(fp);
}
