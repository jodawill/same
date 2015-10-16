#include "same.h"

// Most graphics libraries require initialization. Call this before using
// any functions from this file.
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

// This function defines the block color scheme if applicable.
int define_colors() {
 #if defined(__NCURSES__)
  // 1-4 are for regular blocks.
  init_pair(1,COLOR_BLACK,COLOR_RED);
  init_pair(2,COLOR_BLACK,COLOR_BLUE);
  init_pair(3,COLOR_BLACK,COLOR_GREEN);
  init_pair(4,COLOR_BLACK,COLOR_YELLOW);

  // 5-8 are for highlighted blocks.
  init_pair(5,COLOR_WHITE,COLOR_MAGENTA);
  init_pair(6,COLOR_WHITE,COLOR_CYAN);
  init_pair(7,COLOR_WHITE,COLOR_GREEN);
  init_pair(8,COLOR_WHITE,COLOR_YELLOW);

  // Schemes for default text and error output.
  init_pair(COLOR_DEFAULT,COLOR_WHITE,COLOR_BLACK);
  init_pair(COLOR_ERROR,COLOR_WHITE,COLOR_RED);
  return 0;
 #endif
 return -1;
}

// Cleanup after graphics library.
int clean_screen() {
 #if defined(__NCURSES__)
  endwin();
  return 0;
 #endif
 return -1;
}

// This clears the entire screen.
int clear_all() {
 #if defined(__NCURSES__)
  erase();
  return 0;
 #endif
 return -1;
}

// Draw a block to the board
int draw_block(int col,int row,int block,bool hled) {
 #if defined(__NCURSES__)
  if (hled) {
   attron(COLOR_PAIR(block + 1));
   mvprintw(row,col,"%c",blocks[block + blocknum + 1]);
  } else {
   attron(COLOR_PAIR(block + 1));
   mvprintw(row,col,"%c",blocks[block + 1]);
  }
  return 0;
 #endif
 return -1;
}

// Clear a block, normally used when a chain is deleted
int draw_clear_block(int col,int row){
 #if defined(__NCURSES__)
  attron(COLOR_PAIR(COLOR_DEFAULT));
  mvprintw(row,col," ");
  return 0;
 #endif
 return -1;
}

// Clear all messages in the command row
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

// Draw a message in the command row
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

// Request a vi-style command
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

// This will draw text to the portion of the screen decided to be the
// display panel. We use it for drawing the score, undo numbers, etc.
int draw_display(int row,const char* msg) {
 #if defined(__NCURSES__)
  attron(COLOR_PAIR(COLOR_DEFAULT));
  int a,b;
  getmaxyx(stdscr,a,b);
  for (int i = width + 1; i < b; i++) {
   mvprintw(row,i," ");
  }
  mvprintw(row,width + 1,msg);
  return 0;
 #endif
 return -1;
}

// Draw vi-style error messages
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

// Currently, only text displays are supported, so we'll just print a plain
// text logo regardless of the graphics library.
int draw_logo() {
 draw_display(0,"    SameGame");
 draw_display(1,"by Josh Williams");
 return 0;
}

// Get the screen width. When run in a console, this returns the number of
// columns on the screen.
int get_max_x() {
 #if defined(__NCURSES__)
  int a,b;
  getmaxyx(stdscr,a,b);
  return b;
 #endif
 return -1;
}

// Get the screen height. When run in a console, this returns the number of
// rows on the screen.
int get_max_y() {
 #if defined(__NCURSES__)
  int a,b;
  getmaxyx(stdscr,a,b);
  return a;
 #endif
 return -1;
}

// We refer to the selected block as the cursor position. If the graphics
// library supports a mouse, a current block will still be selected, but
// the only visible selection should be the entire chain.
int move_cursor(int col,int row) {
 #if defined(__NCURSES__)
  move(row,col);
  return 0;
 #endif
 return -1;
}

// This function will prompt the user to enter a string, such as a filename.
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

// In certain graphics libraries, images aren't drawn until a refresh
// command is issued.
int refresh_screen() {
 #if defined(__NCURSES__)
  refresh();
  return 0;
 #endif
 return -1;
}

