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
 draw_display(h-4,msg);
 sprintf(msg,"Redos available: %i",redonum);
 draw_display(h-3,msg);

 return 0;
}

int draw_hst() {
 read_hst();
 if (highscore <= 0) {
  draw_display(height-10,"Highscore:");
  draw_display(height-9,"  Not Set  ");
  draw_display(height-8,"");
  return 1;
 }
 int h;
 if (height >= display_height) {
  h = height;
 } else {
  h = display_height;
 }
 draw_display(h-10,"Highscore:");
 char msg[32];
 sprintf(msg,"  %s",hsn);
 draw_display(h-9,msg);
 sprintf(msg,"  %d",highscore);
 draw_display(h-8,msg);

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
 sprintf(msg,"Score: %d",score);
 draw_display(h-1,msg);
 if (god) {
  draw_display(h-6,"Difficulty: God Mode");
 }
 else {
  if (difficulty == DIF_EASY) {
   draw_display(h-6,"Difficulty: Easy");
  } else if (difficulty == DIF_HARD) {
   draw_display(h-6,"Difficulty: Hard");
  }
 }
 return 0;
}

