CC=gcc
CFLAGS=-I. -lncurses
DEPS = same.h
OBJECTS = same.o hst.o endgame.o save.o colors.o highlight.o board.o command.o init.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

same: $(OBJECTS)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm *.o same

