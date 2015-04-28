#include "same.h"

int init() {
 god = false;
 difficulty = DIF_HARD;
 highlight_none();
 struct pos {
  int x;
  int y;
 };
 pos.x = 0;
 pos.y = 0;
 animation = true;
 multiplier = 0;
 width = 32;
 height = 16;
 if (init_screen() < 0) {
  printf("No graphics library specified.\n");
  return -1;
 }
 time_t t;
 srand((unsigned)time(&t));
 define_colors();

 reset_board();

 set_dir();
 char file[1024];
 strcpy(file,dir);
 strcat(file,"/.samerc");
 read_script(file);

 draw_logo();
 draw_hst();
 draw_score();

 cursor_wait();

 return 0;
}

int cleanup() {
 clean_screen();
 return 0;
}

