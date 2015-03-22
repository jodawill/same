#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "same.h"
#include <strings.h>
#include <unistd.h>

int clear_command() {
 int a,b;
 getmaxyx(stdscr,a,b);
 attron(COLOR_PAIR(20));
 for (int c = 0; c < b; c++) {
  mvprintw(a-1,c," ");
 }
 refresh();
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
  reset_board();
  clear_command();
  return 0;
 }
 if (strcmp(key,"q") == 0) return 1;
 if (strcmp(key,"x") == 0) {
  // Save game
  mvprintw(a-1,0,"Save not yet implemented");
  refresh();
  sleep(2);
  return 1;
 }
 if (strcmp(key,"w") == 0) {
  // Save game
  mvprintw(a-1,0,"Save not yet implemented");
  refresh();
  sleep(2);
  clear_command();
  return 0;
 }

 // Clear command line
 mvprintw(a-1,0,"E492: Not an editor command: %s",key);
 refresh();
 sleep(2);
 clear_command();

 return 0;
}

int cursor_wait() {
 char c = '\0';
 move(y,x);
 while (true) {
  switch (getch()) {
   case ':': {
    int a,b;
    getmaxyx(stdscr,a,b);
    attron(COLOR_PAIR(20));
    mvprintw(a - 1,0,":");
    move(a-1,1);
    refresh();
    if (command_wait() == 1) {
     return 0;
    }
   }
   case '\n': {
    delblock(x,y);
    //mvprintw(y,x,"%c",blocks[board[x][y]]);
    break;
   }
   case KEY_LEFT: {
    if (x > 0) x--;
    break;
   }
   case 'h': {
    if (x > 0) x--;
    break;
   }
   case KEY_RIGHT: {
    if (x < width - 1) x++;
    break;
   }
   case 'l': {
    if (x < width - 1) x++;
    break;
   }
   case KEY_UP: {
    if (y > 0) y--;
    break;
   }
   case 'k': {
    if (y > 0) y--;
    break;
   }
   case KEY_DOWN: {
    if (y < height - 1) y++;
    break;
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

