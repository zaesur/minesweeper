CC=gcc

all: game

game: game.o board.o
	$(CC) game.o board.o -lsdl2 -o game

game.o: game.c
	$(CC) -c game.c

board.o: board.c
	$(CC) -c board.c

clean:
	rm -f *.o game
