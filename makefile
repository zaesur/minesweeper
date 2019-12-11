CC=gcc

all: minesweeper

minesweeper: main.o board.o rendering.o
	$(CC) main.o board.o rendering.o -lsdl2 -o minesweeper

main.o: main.c
	$(CC) -c main.c

game.o: game.c
	$(CC) -c game.c

board.o: board.c
	$(CC) -c board.c

rendering.o: rendering.c
	$(CC) -c rendering.c

clean:
	rm -f *.o game
