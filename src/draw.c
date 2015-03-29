#include "same.h"

int draw_undo() {
 attron(COLOR_PAIR(20));
 int h;
 if (height >= display_height) {
  h = height;
 } else {
  h = display_height;
 }
 mvprintw(h-4,width+1,"                     ");
 mvprintw(h-3,width+1,"                     ");
 mvprintw(h-4,width+1,"Undos available: %i",undonum);
 mvprintw(h-3,width+1,"Redos available: %i",redonum);
 move(y,x);

 return 0;
}

int draw_logo() {
 attron(COLOR_PAIR(20));
 mvprintw(0,width+1,"    SameGame");
 mvprintw(1,width+1,"by Josh Williams");
 move(y,x);
 return 0;
}

int draw_hst() {
 read_hst();
 attron(COLOR_PAIR(20));
 if (highscore <= 0) {
  mvprintw(height-10,width+1,"Highscore:");
  mvprintw(height-9,width+1,"  Not set  ");
  mvprintw(height-8,width+1,"           ");
  return 1;
 }
 int h;
 if (height >= display_height) {
  h = height;
 } else {
  h = display_height;
 }
 mvprintw(h-10,width+1,"                 ");
 mvprintw(h-9,width+1,"                 ");
 mvprintw(h-8,width+1,"                 ");
 mvprintw(h-10,width+1,"Highscore:");
 mvprintw(h-9,width+3,"%s",hsn);
 mvprintw(h-8,width+3,"%i",highscore);
 move(y,x);
 return 0;
}

int draw_command(const char *text) {
 clear_command();
 attron(COLOR_PAIR(20));
 int a,b;
 getmaxyx(stdscr,a,b);
 mvprintw(a-1,0,text);
 refresh();
 move(y,x);
 return 0;
}

int draw_error(const char *text) {
 clear_command();
 attron(COLOR_PAIR(21));
 int a,b;
 getmaxyx(stdscr,a,b);
 mvprintw(a-1,0,text);
 refresh();
 move(y,x);

 return 0;
}

int draw_score() {
 attron(COLOR_PAIR(20));
 int h;
 if (height >= display_height) {
  h = height;
 } else {
  h = display_height;
 }
 mvprintw(h-1,width+1,"                             ");
 mvprintw(h-1,width+1,"Score: %i",score);
 mvprintw(h-6,width+1,"                    ");
 if (god) {
  mvprintw(h-6,width+1,"Difficulty: God Mode");
 }
 else {
  if (easy) {
   mvprintw(h-6,width+1,"Difficulty: Easy");
  } else {
   mvprintw(h-6,width+1,"Difficulty: Hard");
  }
 }
 return 0;
}

int clear_command() {
 int a,b;
 getmaxyx(stdscr,a,b);
 attron(COLOR_PAIR(20));
 for (int c = 0; c < b; c++) {
  mvprintw(a-1,c," ");
 }
 refresh();
 move(y,x);
 return 0;
}

