#include "same.h"

int init() {
 god = false;
 difficulty = DIF_HARD;
 highlight_none();
 x = 0;
 y = 0;
 width = 32;
 height = 16;
 #if defined(__NCURSES__)
  initscr();
  cbreak();
  noecho();
  start_color();
  intrflush(stdscr,false);
  keypad(stdscr,true);
 #endif
 time_t t;
 srand((unsigned)time(&t));
 define_colors();
 draw_logo();

 reset_board();
 cursor_wait();

 return 0;
}

int cleanup() {
 endwin();
 return 0;
}

