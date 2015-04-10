#include "same.h"

int collapse_vertical() {
 for (int col = width-1; col >= 0; col--) {
  for (int row = height-1; row > 0; row--) {
   if (board[col][row] < 0 && row > 0) {
    int r;
    for (r = row; r > 0 && board[col][r] < 0; r--);
    board[col][row] = board[col][r];
    for (; r > 0; r--) {
     board[col][r] = board[col][r-1];
    }
    board[col][0] = -1;
   }
  }
 }

 return 0;
}

bool move_horizontal(int col) {
 int c;
 for (c = col; c < width; c++) {
  for (int r = 0; r < height; r++) {
   if (c < width - 1) {
    board[c][r] = board[c+1][r];
   } else {
    board[c][r] = -1;
   }
  }
 }
 return true;
}

bool is_col_empty(int col) {
 for (int r = height-1; r >= 0; r--) {
  if (board[col][r] >= 0) return false;
  else if (r == 0) return true;
 }
 return false;
}

int collapse_horizontal() {
 for (int col = 0; col < width; col++) {
  if (is_col_empty(col)) {
   for (int c = col; c < width; c++) {
    move_horizontal(col);
    if (!is_col_empty(col)) break;
   }
  }
 }
 return 0;
}

int collapse() {
 collapse_vertical();
 collapse_horizontal();

 highlight_none();

 return 0;
}

int highlight_none() {
 for (int col = 0; col < width; col++) {
  for (int row = 0; row < height; row++) {
   hled[col][row] = false;
   if (board[col][row] > -1) {
    draw_block(col,row,board[col][row],false);
   } else {
    draw_clear_block(col,row);
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
   n++;
   board[x-1][y] = -1;
   hled[x-1][y] = true;
   check_hl(x-1,y,bl,true);
  } else {
   draw_block(x-1,y,board[x][y],true);
   hled[x-1][y] = true;
   check_hl(x-1,y,bl,false);
  }
 }

 if (x+1 < width && !hled[x+1][y] && board[x+1][y] == bl
     && board[x+1][y] > -1) {
  if (remq) {
   n++;
   draw_clear_block(x+1,y);
   board[x+1][y] = -1;
   hled[x+1][y] = true;
   check_hl(x+1,y,bl,true);
  } else {
   draw_block(x+1,y,board[x][y],true);
   hled[x+1][y] = true;
   check_hl(x+1,y,bl,false);
  }
 }

 if (y > 0 && !hled[x][y-1] && board[x][y-1] == bl
     && board[x][y-1] > -1) {
  if (remq) {
   n++;
   draw_clear_block(x,y-1);
   board[x][y-1] = -1;
   hled[x][y-1] = true;
   check_hl(x,y-1,bl,true);
  } else {
   draw_block(x,y-1,board[x][y],true);
   hled[x][y-1] = true;
   check_hl(x,y-1,bl,false);
  }
 }

 if (y+1 < height && !hled[x][y+1] && board[x][y+1] == bl
     && board[x][y+1] > -1) {
  if (remq) {
   n++;
   draw_clear_block(x,y+1);
   board[x][y+1] = -1;
   hled[x][y+1] = true;
   check_hl(x,y+1,bl,true);
  } else {
   draw_block(x,y+1,board[x][y],true);
   hled[x][y+1] = true;
   check_hl(x,y+1,bl,false);
  }
 }

 return 0;
}

int delblock(int x, int y) {
 highlight_none();
 n = 0;
 copy_board();
 check_hl(x,y,board[x][y],true);
 if (n > 1) {
  undonum++;
  redonum = 0;
  score += (n-1)*(n-1);
  draw_score();
  n = 0;
  collapse();
  saved = false;
  if (is_game_over()) end_game();
 }

 return 0;
}

int highlight(int x, int y) {
 draw_undo();
 if (is_block_alone(x,y)) {
  highlight_none();
  return 1;
 }
 if (board[x][y] < 0) return 1;
 highlight_none();
 check_hl(x,y,board[x][y],false);

 return 0;
}

