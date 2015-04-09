#include "same.h"

// Since there's no standard method for obtaining a char without hitting the
// return key, we're going to use system dependent funcitons for this.
char ask_char() {
 // ncurses
 return getch();
}

