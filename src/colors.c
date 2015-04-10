#include "same.h"

// This function defines the console color scheme.
int define_colors() {
 #if defined(__NCURSES__)
  // 1-4 are for regular blocks.
  init_pair(1,COLOR_BLACK,COLOR_RED);
  init_pair(2,COLOR_BLACK,COLOR_BLUE);
  init_pair(3,COLOR_BLACK,COLOR_GREEN);
  init_pair(4,COLOR_BLACK,COLOR_YELLOW);

  // 5-8 are for highlighted blocks.
  init_pair(5,COLOR_WHITE,COLOR_MAGENTA);
  init_pair(6,COLOR_WHITE,COLOR_CYAN);
  init_pair(7,COLOR_WHITE,COLOR_GREEN);
  init_pair(8,COLOR_WHITE,COLOR_YELLOW);

  // Schemes for default text and error output.
  init_pair(COLOR_DEFAULT,COLOR_WHITE,COLOR_BLACK);
  init_pair(COLOR_ERROR,COLOR_WHITE,COLOR_RED);
  return 0;
 #endif
 return -1;
}

