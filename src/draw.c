// This file contains functions for drawing the display. Although they are
// not system dependent, they do require a monospace, plain text display.
// This needs to go away.

#include "same.h"

int draw_undo() {
 int h;
 if (height >= display_height) {
  h = height;
 } else {
  h = display_height;
 }
 char msg[32];
 sprintf(msg,"Undos available: %d",undonum);
 draw_display(h-5,msg);
 sprintf(msg,"Redos available: %i",redonum);
 draw_display(h-4,msg);

 return 0;
}

int draw_hst() {
 read_hst();
 if (highscore <= 0) {
  draw_display(height-11,"Highscore:");
  draw_display(height-10,"  Not Set  ");
  draw_display(height-9,"");
  return 1;
 }
 int h;
 if (height >= display_height) {
  h = height;
 } else {
  h = display_height;
 }
 draw_display(h-11,"Highscore:");
 char msg[32];
 sprintf(msg,"  %s",hsn);
 draw_display(h-10,msg);
 sprintf(msg,"  %d",highscore);
 draw_display(h-9,msg);

 return 0;
}

int draw_score() {
 int h;
 if (height >= display_height) {
  h = height;
 } else {
  h = display_height;
 }
 char msg[32];
 sprintf(msg,"Potential score: %d",potential_score);
 draw_display(h-2,msg);
 sprintf(msg,"Score: %d",score);
 draw_display(h-1,msg);
 if (god) {
  draw_display(h-7,"Difficulty: God Mode");
 }
 else {
  if (difficulty == DIF_EASY) {
   draw_display(h-7,"Difficulty: Easy");
  } else if (difficulty == DIF_HARD) {
   draw_display(h-7,"Difficulty: Hard");
  }
 }
 return 0;
}

