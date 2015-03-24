#include "same.h"

int copy_board() {
 undonum++;
 for (int col = 0; col < width; col++) {
  for (int row = 0; row < height; row++) {
   board_undo[undonum][col][row] = board[col][row];
  }
 }
 score_undo[undonum] = score;

 return 0;
}

int undo() {
 if (undonum <= 0) return 1;

 for (int col = 0; col < width; col++) {
  for (int row = 0; row < height; row++) {
   board[col][row] = board_undo[undonum][col][row];
  }
 }
 score = score_undo[undonum];
 highlight(x,y);
 draw_score();
 undonum--;
 draw_command("Reverted to last change.");
 refresh();

 return 0;
}

