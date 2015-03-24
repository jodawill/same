#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "same.h"
#include <unistd.h>

int draw_board() {
 for (int col = 0; col < width; col++) {
  for (int row = 0; row < height; row++) {
   if (board[col][row] < 0) {
    attron(COLOR_PAIR(20));
    mvprintw(row,col," ");
   } else {
    attron(COLOR_PAIR(board[col][row]+1));
    mvprintw(row,col,"%c",blocks[board[col][row]+1]);
   }
  }
 }
 refresh();
 return 0;
}

int draw_undo() {
 attron(COLOR_PAIR(20));
 mvprintw(0,width+1,"                     ");
 mvprintw(1,width+1,"                     ");
 mvprintw(0,width+1,"Undos available: %i",undonum);
 mvprintw(1,width+1,"Redos available: %i",redonum);
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

int draw_score() {
 attron(COLOR_PAIR(20));
 mvprintw(19,0,"                             ");
 mvprintw(19,0,"Score: %i",score);
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

int command_wait() {
 char key[1024];
 echo();
 getnstr(key,1024);
 noecho();
 int a,b;
 getmaxyx(stdscr,a,b);
 
 if (strcmp(key,"new") == 0) {
  clear_command();
  reset_board();
  return 0;
 }
 if (strcmp(key,"") == 0) {
  clear_command();
  return 0;
 }
 if (strcmp(key,"u") == 0) {
  clear_command();
  undo();
  return 0;
 }
 if (strcmp(key,"r") == 0) {
  clear_command();
  redo();
  return 0;
 }
 if (strcmp(key,"q") == 0) return 1;
 if (strcmp(key,"x") == 0) {
  // Save game
  draw_command("Save not yet implemented.");
  sleep(1);
  return 1;
 }
 if (strcmp(key,"w") == 0) {
  // Save game
  draw_command("Save not yet implemented.");
  return 0;
 }

 // Clear command line
 char text[1024] = "";
 strcat(text,"Not a command: ");
 strcat(text,key);
 draw_command(text);
 refresh();

 return 0;
}

int cursor_wait() {
 char c = '\0';
 move(y,x);
 while (true) {
  switch (getch()) {
   case ':': {
    clear_command();
    int a,b;
    getmaxyx(stdscr,a,b);
    attron(COLOR_PAIR(20));
    mvprintw(a - 1,0,":");
    move(a-1,1);
    refresh();
    if (command_wait() == 1) {
     return 0;
    }
    break;
   }
   case 'u': {
    undo();
    break;
   }
   case 'r': {
    redo();
    break;
   }
   case 'd': {
    if (getch() != 'd') break;
   }
   case 'x': {
   }
   case '\n': {
    delblock(x,y);
    break;
   }
   case KEY_LEFT: {
   }
   case 'h': {
    if (x > 0) x--;
    break;
   }
   case KEY_RIGHT: {
   }
   case 'l': {
    if (x < width - 1) x++;
    break;
   }
   case KEY_UP: {
   }
   case 'k': {
    if (y > 0) y--;
    break;
   }
   case KEY_DOWN: {
   }
   case 'j': {
    if (y < height - 1) y++;
    break;
   }
  }
  move(y,x);
  highlight(x,y);
  refresh();
 }
}

