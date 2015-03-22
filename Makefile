HEADERS = same.h
OBJECTS = same.o colors.o highlight.o board.o misc.o init.o

default: same

%.o: %.c $(HEADERS)
	gcc -c $< -o $@ -lncurses

same: $(OBJECTS)
	gcc $(OBJECTS) -o $@ -lncurses

clean:
	rm *.o same

