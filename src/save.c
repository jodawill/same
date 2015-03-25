#include "same.h"

int copy_board() {
 if (undonum < 0) return 1;

 for (int col = 0; col < width; col++) {
  for (int row = 0; row < height; row++) {
   board_undo[undonum][col][row] = board[col][row];
  }
 }
 score_undo[undonum] = score;

 return 0;
}

int redo() {
 if (redonum <= 0) {
  draw_command("Already at the latest saved state.");
  return 1;
 }
 undonum++;
 for (int col = 0; col < width; col++) {
  for (int row = 0; row < height; row++) {
   board[col][row] = board_undo[undonum][col][row];
  }
 }
 draw_board();
 highlight(x,y);
 score = score_undo[undonum];
 draw_score();
 redonum--;
 draw_command("Reverted to next board state.");
 if (is_game_over()) end_game();
 refresh();

 return 0;
}

int undo() {
 if (undonum <= 0) {
  draw_command("Already at the earliest state.");
  return 1;
 }

 gameover = false;
 if (redonum <= 0) copy_board();
 undonum--;

 for (int col = 0; col < width; col++) {
  for (int row = 0; row < height; row++) {
   board[col][row] = board_undo[undonum][col][row];
  }
 }
 score = score_undo[undonum];
 draw_board();
 highlight(x,y);
 draw_score();
 redonum++;
 draw_command("Reverted to last change.");
 refresh();

 return 0;
}

