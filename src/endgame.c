#include "same.h"

int end_game() {
 if (highscore < score) {
  get_hsn();
 }
 clear_command();
 draw_undo();

 // End of game animation. Display the entire undo and redo history.
 for (int u = undonum-1; u >= 0; u--) {
  for (int col = 0; col < width; col++) {
   for (int row = 0; row < height; row++) {
    draw_clear_block(col,row);
    draw_block(col,row,board_undo[u][col][row],false);
   }
   refresh_screen();
  }
  refresh_screen();
  rest();
 }
 for (int u = 0; u <= undonum; u++) {
  for (int col = 0; col < width; col++) {
   for (int row = 0; row < height; row++) {
    draw_clear_block(col,row);
    draw_block(col,row,board_undo[u][col][row],false);
   }
  }
  refresh_screen();
  rest();
 }

 draw_command("Game Over. :new to start a new game.");
 gameover = true;
 draw_hst();

 return 0;
}

