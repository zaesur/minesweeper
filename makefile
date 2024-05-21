CC=gcc
EXEC=minesweeper

CFLAGS=$(shell sdl2-config --cflags)
LDFLAGS=$(shell sdl2-config --libs)

all: $(EXEC)

$(EXEC): main.o game.o board.o rendering.o file.o
	$(CC) main.o game.o board.o rendering.o file.o $(LDFLAGS) -lm -o $(EXEC)

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

game.o: game.c game.h
	$(CC) $(CFLAGS) -c game.c

board.o: board.c board.h
	$(CC) $(CFLAGS) -c board.c

rendering.o: rendering.c rendering.h
	$(CC) $(CFLAGS) -c rendering.c

file.o: file.c file.h
	$(CC) $(CFLAGS) -c file.c

clean:
	rm -f *.o $(EXEC)
