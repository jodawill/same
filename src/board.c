#include "same.h"

int reset_board() {
 char eb = get_rand(blocknum);
 for (int col = 0; col < width; col++) {
  for (int row = 0; row < height; row++) {
   board[col][row] = get_rand(blocknum);
   if (easy && get_rand(4) == 1) {
    board[col][row] = eb;
   }
   attron(COLOR_PAIR(1 + board[col][row]));
   mvprintw(row,col,"%c",blocks[1 + board[col][row]]);
   hled[col][row] = false;
  }
 }
 x = 0;
 y = 0;
 int a,b;
 getmaxyx(stdscr,a,b);
 // At some point, this needs to become a global variable
 display_width = 20;
 display_height = 11;
 max_width = b-display_width;
 max_height = a;
 move(y,x);
 undonum = 0;
 redonum = 0;
 score = 0;
 n = 0;
 copy_board();
 read_hst();
 draw_logo();
 draw_hst();
 draw_score();
 draw_undo();
 refresh();


 return 0;
}

bool is_block_alone(int col, int row) {
 char b = board[col][row];
 if (b < 0) return true;
 if (row > 0 && b == board[col][row-1]) return false;
 if (row < height-1 && b == board[col][row+1]) return false;
 if (col > 0 && b == board[col-1][row]) return false;
 if (col < width-1 && b == board[col+1][row]) return false;

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

int set_width(int w) {
 if (w > 0 && w < max_width) {
  erase();
  width = w;
  char cmd[1024];
  strcpy(cmd,"Board width set to ");
  char str[10];
  snprintf(str,10,"%d",w);
  strcat(cmd,str);
  draw_command(cmd);
  reset_board();
  return 0;
 } else {
  draw_error("Not a valid width");
  return 0;
 }
 return 1;
}

int set_height(int h) {
 if (h > 0 && h < max_height) {
  erase();
  height = h;
  char cmd[1024];
  strcpy(cmd,"Board height set to ");
  char str[10];
  snprintf(str,10,"%d",h);
  strcat(cmd,str);
  draw_command(cmd);
  reset_board();
  return 0;
 } else {
  draw_error("Not a valid height");
  return 1;
 }
 return 0;
}

