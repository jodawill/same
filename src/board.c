#include "same.h"

// Draws every block on the board based on what's currently stored in
// board[][]. This does not draw anything but the blocks.
int draw_board() {
 for (int col = 0; col < width; col++) {
  for (int row = 0; row < height; row++) {
   if (board[col][row] < 0) {
    draw_clear_block(col,row);
   } else {
    draw_block(col,row,board[col][row],false);
   }
  }
 }

 return 0;
}

// Create a new random board.
int reset_board() {

 // eb is the easy block. If difficulty == DIF_EASY, this block is added to
 // the board more often than any other. If god == true, it fills the board
 // with that one block.
 char eb = get_rand(blocknum);

 for (int col = 0; col < width; col++) {
  for (int row = 0; row < height; row++) {
   board[col][row] = get_rand(blocknum);
   if (difficulty == DIF_EASY && get_rand(4) == 1) {
    board[col][row] = eb;
   }
   if (god) {
    board[col][row] = eb;
   }
   draw_block(col,row,board[col][row],false);
   hled[col][row] = false;
  }
 }

 // Set cursor to the origin.
 x = 0;
 y = 0;

 // Move the cursor to (x,y), which we set as the origin.
 move_cursor(x,y);

 // The game is not over because we're starting a new one.
 gameover = false;
 saved = true;

 // Set the dimensions of the display pane.
 display_width = 20;
 display_height = 11;

 // Set the standard global variables to 0.
 undonum = 0;
 redonum = 0;
 score = 0;
 potential_score = 0;
 n = 0;

 // Copies the current board for the undo history
 copy_board();

 // Draw the SameGame logo in the display pane
 draw_logo();

 // Draw score to display pane
 draw_score();
 // Draw display showing number of undos and redos available
 draw_undo();
 // Draw highscore table
 draw_hst();

 return 0;
}

// Look on all four sides of block to see if it's part of a contiguous
// region.
bool is_block_alone(int col, int row) {
 char b = board[col][row];
 if (b < 0) return true;
 if (row > 0 && b == board[col][row-1]) return false;
 if (row < height-1 && b == board[col][row+1]) return false;
 if (col > 0 && b == board[col-1][row]) return false;
 if (col < width-1 && b == board[col+1][row]) return false;

 return true;
}

// Starting at the origin, it checks whether each block is alone. As soon as
// it finds one that's not alone, it returns that the game is not over.
bool is_game_over() {
 for (int col = 0; col < width; col++) {
  for (int row = 0; row < height; row++) {
   if (!is_block_alone(col,row)) return false;
  }
 }
 return true;
}

// Sets the board width and starts a new game
int set_width(int w) {
 if (w > 0 && w <= get_max_x() - display_width) {
  clear_all();
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
 if (h > 0 && h < get_max_y()) {
  clear_all();
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

