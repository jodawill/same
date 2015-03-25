#include "same.h"

int get_rand(int cap) {
 return rand() % cap;
}

int init() {
 easy = false;
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
 draw_logo();
 keypad(stdscr,true);
 char *homedir = getenv("HOME");
 strcpy(hst_fn,homedir);
 strcat(hst_fn,"/.samehst");

 reset_board();
 cursor_wait();

 printf("%s",hst_fn);

 return 0;
}

int cleanup() {
 endwin();
 return 0;
}

