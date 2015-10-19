#include "same.h"

int check_flags(int argc, char *argv[]) {
 // Set each flag as not flagged
 for (int i = 0; i < FLAG_TOTAL; i++) {
  checked_flags[i] = false;
 }

 for (int i = 1; i < argc; i++) {
  if (strcmp(argv[i],"--god") == 0) {
   checked_flags[FLAG_GOD] = true;
   god = true;
   continue;
  }

  if (strcmp(argv[i],"--width") == 0) {
   if (i == argc-1) break;
   if (atoi(argv[i+1]) > 0) {
    checked_flags[FLAG_WIDTH] = true;
    width = atoi(argv[++i]);
    continue;
   }
  }

  if (strcmp(argv[i],"--height") == 0) {
   if (i == argc-1) break;
   if (atoi(argv[i+1]) > 0) {
    checked_flags[FLAG_HEIGHT] = true;
    height = atoi(argv[++i]);
    continue;
   }
  }

  if (strcmp(argv[i],"--easy") == 0) {
   checked_flags[FLAG_DIF] = true;
   difficulty = DIF_EASY;
   continue;
  }

  if (strcmp(argv[i],"--hard") == 0) {
   checked_flags[FLAG_DIF] = true;
   difficulty = DIF_HARD;
   continue;
  }
 }

 return 0;
}

