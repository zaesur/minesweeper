CC=gcc

all: game

game: game.o printer.o board.o
	$(CC) game.o printer.o board.o -o game

game.o: game.c printer.h
	$(CC) -c game.c

printer.o: printer.c board.h
	$(CC) -c printer.c

board.o: board.c
	$(CC) -c board.c

clean:
	rm -f *.o game
