#include "same.h"

int read_script(char fn[]) {
 FILE *f = fopen(fn,"r");
 if (f == NULL) {
  return 1;
 }
 size_t length = 0;
 char *line = NULL;
 char command[32];
 char argument[32];

 // Currently, same only supports one command per line. This may change in
 // the future.
 while (getline(&line,&length,f) != EOF) {
  strtok(line,"\n");
  read_command(line,true);
 }

 fclose(f);
 return 0;
}

