HEADERS = same.h
OBJECTS = same.o hst.o endgame.o save.o colors.o highlight.o board.o command.o init.o

default: same

%.o: %.c $(HEADERS)
	gcc -c $< -o $@ -lncurses

same: $(OBJECTS)
	gcc $(OBJECTS) -o $@ -lncurses

clean:
	rm *.o same

