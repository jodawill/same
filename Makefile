NAME = same
CC=gcc
CFLAGS=-I. -lcurses
DEPS = src/same.h
OBJECTS = src/same.o src/common.o src/draw.o src/hst.o src/endgame.o src/save.o src/colors.o src/highlight.o src/board.o src/command.o src/init.o

.PHONY: clean make install uninstall

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< -std=c99

$(NAME): $(OBJECTS)
	$(CC) -o $@ $^ $(CFLAGS)

install:
	cp $(NAME) /usr/bin

uninstall:
	rm /usr/bin/$(NAME)

clean:
	rm -f $(OBJECTS) $(NAME)

