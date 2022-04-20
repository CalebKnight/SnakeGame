CC = gcc
snake: main.c random.c game.c snake.c terminal.c board.c main.h random.h game.h snake.h terminal.h board.h 
	$(CC) -Wall -ansi -pedantic -Werror main.c random.c game.c snake.c terminal.c board.c -o snake 
UNBEATABLE: main.c random.c game.c snake.c terminal.c board.c main.h random.h game.h snake.h terminal.h board.h 
	$(CC) -Wall -ansi -pedantic -Werror main.c random.c game.c snake.c terminal.c board.c -D UNBEATABLE -o snake 