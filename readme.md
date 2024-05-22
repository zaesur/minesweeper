# Minesweeper
Implementation of the classic minesweeper game
for an undergrad course in systems programming.

![minesweeper](https://github.com/zaesur/minesweeper-tasm/blob/main/minesweeper.png?raw=true)

## Installation
 1. Run `apt-get install libsdl2-dev`
 1. Run `make`
 1. Run `./minesweeper -w 10 -h 10 -m 10`

## Playing a game
  * Left clicking opens a cell
  * Right clicking places or removes a flag
  * Closing the window prompts the user to save the game in a .txt file
  * the -w -h -m flags control the number of columns, rows and mines in the game
  * the -f flag allows the player to resume a saved game

## Caveats
  * The UI is kept simple
  * There is no win condition, but this is straighforward to implement
  * The player cannot choose the name of the save file, so game.txt always gets overridden
