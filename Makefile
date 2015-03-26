NAME = same
CC=gcc
CFLAGS=-I. -lcurses
DEPS = src/same.h
OBJECTS = src/same.o src/hst.o src/endgame.o src/save.o src/colors.o src/highlight.o src/board.o src/command.o src/init.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< -std=c99

$(NAME): $(OBJECTS)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -f $(OBJECTS) $(NAME)

