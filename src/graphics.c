#include "same.h"

int clean_screen() {
 #if defined(__NCURSES__)
  endwin();
  return 0;
 #endif
 return -1;
}

int clear_all() {
 #if defined(__NCURSES__)
  erase();
  return 0;
 #endif
 return -1;
}

int draw_block(int col,int row,int block,bool hled) {
 #if defined(__NCURSES__)
  if (hled) {
   attron(COLOR_PAIR(board[col][row] + 1));
   mvprintw(row,col,"%c",blocks[board[col][row] + blocknum + 1]);
  } else {
   attron(COLOR_PAIR(board[col][row] + 1));
   mvprintw(row,col,"%c",blocks[board[col][row] + 1]);
  }
  return 0;
 #endif
 return -1;
}

int draw_clear_block(int col,int row){
 #if defined(__NCURSES__)
  attron(COLOR_PAIR(COLOR_DEFAULT));
  mvprintw(row,col," ");
  return 0;
 #endif
 return -1;
}

int clear_command() {
 #if defined(__NCURSES__)
  int a,b;
  getmaxyx(stdscr,a,b);
  attron(COLOR_PAIR(COLOR_DEFAULT));
  for (int c = 0; c < b; c++) {
   mvprintw(a-1,c," ");
  }
  return 0;
 #endif
 return -1;
}

int draw_command(const char* text) {
 clear_command();
 #if defined(__NCURSES__)
  attron(COLOR_PAIR(COLOR_DEFAULT));
  int a,b;
  getmaxyx(stdscr,a,b);
  mvprintw(a-1,0,text);
  refresh();
  return 0;
 #endif
 return -1;
}

int command_prompt(char key[]) {
 #if defined(__NCURSES__)
  attron(COLOR_PAIR(COLOR_DEFAULT));
  int a,b;
  getmaxyx(stdscr,a,b);
  mvprintw(a-1,0,":");
  refresh();
  echo();
  getnstr(key,get_max_x()-1);
  noecho();
  return 0;
 #endif
 return -1;
}

int draw_display(int row,const char* msg) {
 #if defined(__NCURSES__)
  attron(COLOR_PAIR(COLOR_DEFAULT));
  mvprintw(row,width + 1,msg);
  return 0;
 #endif
 return -1;
}

int draw_error(const char* msg) {
 #if defined(__NCURSES__)
  int a,b;
  getmaxyx(stdscr,a,b);
  attron(COLOR_PAIR(COLOR_ERROR));
  mvprintw(a-1,0,msg);
  return 0;
 #endif
 return -1;
}

int draw_logo() {
 draw_display(0,"    SameGame");
 draw_display(1,"by Josh Williams");
 return 0;
}

int get_max_x() {
 #if defined(__NCURSES__)
  int a,b;
  getmaxyx(stdscr,a,b);
  return b;
 #endif
 return -1;
}

int get_max_y() {
 #if defined(__NCURSES__)
  int a,b;
  getmaxyx(stdscr,a,b);
  return a;
 #endif
 return -1;
}

int init_screen() {
 #if defined(__NCURSES__)
  initscr();
  cbreak();
  noecho();
  start_color();
  intrflush(stdscr,false);
  keypad(stdscr,true);
  return 0;
 #endif
 return -1;
}

int move_cursor(int col,int row) {
 #if defined(__NCURSES__)
  move(row,col);
  return 0;
 #endif
 return -1;
}

int prompt_str(const char msg[],char outstr[],int strn) {
 #if defined(__NCURSES__)
  int a,b;
  char msg2[strn+4];
  strcpy(msg2,msg);
  if (msg2[strlen(msg2)-1] != ' ') {
   strcat(msg2," ");
  }
  attron(COLOR_PAIR(COLOR_DEFAULT));
  getmaxyx(stdscr,a,b);
  mvprintw(a-1,0,msg2);
  echo();
  getnstr(outstr,strn);
  noecho();
  outstr[strn] = '\0';
  return 0;
 #endif
 return -1;
}

int refresh_screen() {
 #if defined(__NCURSES__)
  refresh();
  return 0;
 #endif
 return -1;
}

