#include "same.h"

int end_game() {
 if (highscore < score) {
  get_hsn();
 }
 clear_command();
 draw_command("Game Over. :new to start a new game.");
 draw_hst();

 return 0;
}

