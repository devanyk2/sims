# Kieran Devany
# Makefile for the game of life
CC= gcc
CFLAGS= -g -Wall

life: game.o
	$(CC) $(CFLAGS) -o life game.o

game.o: game.c
	$(CC) $(CFLAGS) -c game.c

clean:
	-rm *.o
	-rm life
