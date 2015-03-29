#include "same.h"

int init() {
 god = false;
 easy = false;
 highlight_none();
 x = 0;
 y = 0;
 width = 32;
 height = 16;
 initscr();
 cbreak();
 noecho();
 start_color();
 intrflush(stdscr,false);
 time_t t;
 srand((unsigned)time(&t));
 define_colors();
 draw_logo();
 keypad(stdscr,true);

 reset_board();
 cursor_wait();

 return 0;
}

int cleanup() {
 endwin();
 return 0;
}

