CC = gcc
LDFLAGS = -lncurses

all:
	$(CC) gomoku.c main.c -o gomoku $(LDFLAGS)

clean:
	rm gomoku
