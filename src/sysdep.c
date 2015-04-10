#include "same.h"

// Since there's no standard method for obtaining a char without hitting the
// return key, we're going to use system dependent funcitons for this.
int ask_char() {
 #if defined(__NCURSES__)
  return getch();
 #endif
 return -1;
}

int rest() {
 #if defined(__APPLE__)
  struct timespec time1, time2;
  time1.tv_sec = 0;
  time1.tv_nsec = 20000000;
  nanosleep(&time1,&time2);
  return 0;
 #endif
 return -1;
}

