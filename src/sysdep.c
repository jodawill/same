#include "same.h"

// Since there's no standard method for obtaining a char without hitting the
// return key, we're going to use system dependent funcitons for this.
int ask_char() {
 #if defined(__NCURSES__)
  return getch();
 #endif
 return -1;
}

