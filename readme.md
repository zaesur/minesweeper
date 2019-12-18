### Minesweeper

# A basic C implementation of minesweeper:
  * Left clicking opens a cell
  * Right clicking places or removes a flag
  * Closing the window prompts the user to save the game in a .txt file
  * the -w -h -m flags control the number of columns, rows and mines in the game
  * the -f flag allows the player to resume a saved game

# Some caveats:
  * There is no win condition, but this is straighforward to implement
  * The UI is kept simple
  * The player cannot choose the name of the save file, so game.txt always gets overridden
