#include "same.h"

int reset_board() {
 for (int col = 0; col < width; col++) {
  for (int row = 0; row < height; row++) {
   board[col][row] = get_rand(blocknum);
   attron(COLOR_PAIR(1 + board[col][row]));
   mvprintw(row,col,"%c",blocks[1 + board[col][row]]);
   hled[col][row] = false;
  }
 }
 x = 0;
 y = 0;
 move(y,x);
 undonum = 0;
 score = 0;
 n = 0;
 attron(COLOR_PAIR(20));
 mvprintw(19,0,"                   ");
 mvprintw(19,0,"Score: %i",score);
 refresh();


 return 0;
}

bool is_block_alone(int col, int row) {
 char b = board[col][row];
 if (b < 0) return true;
 if (row > 0 && b == board[col][row-1]) return false;
 if (row < height && b == board[col][row+1]) return false;
 if (col > 0 && b == board[col-1][row]) return false;
 if (col < width && b == board[col+1][row]) return false;

 return true;
}

bool is_game_over() {
 for (int col = 0; col < width; col++) {
  for (int row = 0; row < height; row++) {
   if (!is_block_alone(col,row)) return false;
  }
 }

 return true;
}

