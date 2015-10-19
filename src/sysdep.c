#include "same.h"
#if defined(__APPLE__) || defined(__linux__)
 #define NANOSLEEP_AVAILABLE
#else
 #include <limits.h>
#endif

// Find a directory to place settings and saved games in.
int set_dir() {
 #if defined(__UNISTD__)
  char *homedir = getenv("HOME");
  strcpy(dir,homedir);
  strcat(dir,"/.same");
  mkdir(dir,S_IRWXU);
  return 0;
 #endif

 return -1;
}


// Since there's no standard method for obtaining a char without hitting the
// return key, we're going to use system dependent funcitons for this.
int ask_char() {
 #if defined(__NCURSES__)
  return getch();
 #endif
 return -1;
}

int rest() {
 //#if defined(__APPLE__) || defined(__linux__)
 #if defined(NANOSLEEP_AVAILABLE)
  struct timespec time1, time2;
  time1.tv_sec = 0;
  time1.tv_nsec = 25000000;
  nanosleep(&time1,&time2);
  return 0;
 #else
  // If we can't find a suitable function to sleep less than a second, we'll
  // fall back on a busy wait. It's an ugly hack, so we'll avoid this on
  // every system we officially support.
  for (int c = 0; c < INT_MAX/100; c++);
 #endif
 return -1;
}

