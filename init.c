#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "same.h"

int get_rand(int cap) {
 return rand() % cap;
}

int init() {
 highlight_none();
 x = 0;
 y = 0;
 initscr();
 cbreak();
 noecho();
 start_color();
 intrflush(stdscr,false);
 time_t t;
 srand((unsigned)time(&t));
 define_colors();
 //attron(COLOR_PAIR(1));
 keypad(stdscr,true);
 reset_board();
 cursor_wait();
 return 0;
}

int cleanup() {
 endwin();
 return 0;
}

