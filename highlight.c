#include "same.h"

int highlight_none() {
 for (int col = 0; col < width; col++) {
  for (int row = 0; row < height; row++) {
   attron(COLOR_PAIR(1 + board[col][row]));
   mvprintw(row,col,"%c",blocks[1 + board[col][row]]);
   hled[col][row] = false;
  }
 }

 return 0;
}

int check_hl(int x, int y, bool remq) {
 if (x > 0 && !hled[x-1][y] && board[x-1][y] == board[x][y]) {
  if (remq) {
   attron(COLOR_PAIR(100));
   mvprintw(y,x-1," ");
   hled[x-1][y] = true;
   check_hl(x-1,y,true);
  } else {
   attron(COLOR_PAIR(blocknum + 1 + board[x][y]));
   mvprintw(y,x-1,"%c",blocks[board[x][y]+blocknum+1]);
   hled[x-1][y] = true;
   check_hl(x-1,y,false);
  }
 }

 if (x+1 < width && !hled[x+1][y] && board[x+1][y] == board[x][y]) {
  if (remq) {
   attron(COLOR_PAIR(100));
   mvprintw(y,x+1," ");
   hled[x+1][y] = true;
   check_hl(x+1,y,true);
  } else {
   attron(COLOR_PAIR(blocknum + 1 + board[x][y]));
   mvprintw(y,x+1,"%c",blocks[board[x][y]+blocknum+1]);
   hled[x+1][y] = true;
   check_hl(x+1,y,false);
  }
 }

 if (y > 0 && !hled[x][y-1] && board[x][y-1] == board[x][y]) {
  if (remq) {
   attron(COLOR_PAIR(100));
   mvprintw(y-1,x," ");
   hled[x][y-1] = true;
   check_hl(x,y-1,true);
  } else {
   attron(COLOR_PAIR(blocknum + 1 + board[x][y]));
   mvprintw(y-1,x,"%c",blocks[board[x][y]+blocknum+1]);
   hled[x][y-1] = true;
   check_hl(x,y-1,false);
  }
 }

 if (y+1 < height && !hled[x][y+1] && board[x][y+1] == board[x][y]) {
  if (remq) {
   attron(COLOR_PAIR(100));
   mvprintw(y+1,x," ");
   hled[x][y+1] = true;
   check_hl(x,y+1,true);
  } else {
   attron(COLOR_PAIR(blocknum + 1 + board[x][y]));
   mvprintw(y+1,x,"%c",blocks[board[x][y]+blocknum+1]);
   hled[x][y+1] = true;
   check_hl(x,y+1,false);
  }
 }

 return 0;
}

int delblock(int x, int y) {
 highlight_none();
 check_hl(x,y,true);
 move(y,x);
 refresh();

 return 0;
}

int highlight(int x, int y) {
 highlight_none();
 check_hl(x,y,false);
 move(y,x);
 refresh();

 return 0;
}

