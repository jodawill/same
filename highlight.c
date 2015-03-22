#include "same.h"

int collapse_vertical() {
 for (int col = width-1; col >= 0; col--) {
  for (int row = height-1; row > 0; row--) {
   if (board[col][row] < 0 && row > 0) {
    board[col][0] = -1;
    int r;
    for (r = row; r > 0 && board[col][r] < 0; r--);
    board[col][row] = board[col][r];
    for (; r > 0; r--) {
     board[col][r] = board[col][r-1];
    }
   }
  }
 }

 return 0;
}

int collapse() {
 collapse_vertical();

 highlight_none();
 refresh();

 return 0;
}

int highlight_none() {
 for (int col = 0; col < width; col++) {
  for (int row = 0; row < height; row++) {
   if (board[col][row] > -1) {
    attron(COLOR_PAIR(1 + board[col][row]));
    mvprintw(row,col,"%c",blocks[1 + board[col][row]]);
    hled[col][row] = false;
   } else {
    attron(COLOR_PAIR(20));
    mvprintw(row,col," ");
    hled[col][row] = false;
   }
  }
 }

 return 0;
}

int check_hl(int x, int y, char bl, bool remq) {
 if (bl < 0) return 1;
 if (x > 0 && !hled[x-1][y] && board[x-1][y] == bl
     && board[x-1][y] > -1) {
  if (remq) {
   attron(COLOR_PAIR(20));
   mvprintw(y,x-1," ");
   board[x-1][y] = -1;
   hled[x-1][y] = true;
   check_hl(x-1,y,bl,true);
  } else {
   attron(COLOR_PAIR(blocknum + 1 + board[x][y]));
   mvprintw(y,x-1,"%c",blocks[board[x][y]+blocknum+1]);
   hled[x-1][y] = true;
   check_hl(x-1,y,bl,false);
  }
 }

 if (x+1 < width && !hled[x+1][y] && board[x+1][y] == bl
     && board[x+1][y] > -1) {
  if (remq) {
   attron(COLOR_PAIR(20));
   mvprintw(y,x+1," ");
   board[x+1][y] = -1;
   hled[x+1][y] = true;
   check_hl(x+1,y,bl,true);
  } else {
   attron(COLOR_PAIR(blocknum + 1 + board[x][y]));
   mvprintw(y,x+1,"%c",blocks[board[x][y]+blocknum+1]);
   hled[x+1][y] = true;
   check_hl(x+1,y,bl,false);
  }
 }

 if (y > 0 && !hled[x][y-1] && board[x][y-1] == bl
     && board[x][y-1] > -1) {
  if (remq) {
   attron(COLOR_PAIR(20));
   mvprintw(y-1,x," ");
   board[x][y-1] = -1;
   hled[x][y-1] = true;
   check_hl(x,y-1,bl,true);
  } else {
   attron(COLOR_PAIR(blocknum + 1 + board[x][y]));
   mvprintw(y-1,x,"%c",blocks[board[x][y]+blocknum+1]);
   hled[x][y-1] = true;
   check_hl(x,y-1,bl,false);
  }
 }

 if (y+1 < height && !hled[x][y+1] && board[x][y+1] == bl
     && board[x][y+1] > -1) {
  if (remq) {
   attron(COLOR_PAIR(20));
   mvprintw(y+1,x," ");
   board[x][y+1] = -1;
   hled[x][y+1] = true;
   check_hl(x,y+1,bl,true);
  } else {
   attron(COLOR_PAIR(blocknum + 1 + board[x][y]));
   mvprintw(y+1,x,"%c",blocks[board[x][y]+blocknum+1]);
   hled[x][y+1] = true;
   check_hl(x,y+1,bl,false);
  }
 }

 return 0;
}

int delblock(int x, int y) {
 highlight_none();
 check_hl(x,y,board[x][y],true);
 collapse();
 move(y,x);
 refresh();

 return 0;
}

int highlight(int x, int y) {
 if (board[x][y] < 0) return 1;
 highlight_none();
 check_hl(x,y,board[x][y],false);
 move(y,x);
 refresh();

 return 0;
}

