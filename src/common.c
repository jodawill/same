#include "same.h"

bool confirm(const char* str) {
 char d[1024];
 strcpy(d,str);
 strcat(d," (y/n)");
 draw_command(d);
 char c;
 for (c = getchar(); c != 'y' && c!= 'Y' && c!= 'n' && c != 'N';
      c = getchar()) {
  draw_command(d);
 }
 clear_command();
 return (c == 'y' || c == 'Y');
}

int get_rand(int n) {
 int x = rand();
 while (n < RAND_MAX && x >= RAND_MAX - (RAND_MAX %n)) {
  x = rand();
 }
 return x%n;
}

int set_dir() {
 char *homedir = getenv("HOME");
 strcpy(dir,homedir);
 strcat(dir,"/.same");
 mkdir(dir,S_IRWXU);

 return 0;
}

