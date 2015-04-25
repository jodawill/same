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
 char sc[] = ";";
 char *token;

 // Currently, same only supports one command per line. This may change in
 // the future.
 while (getline(&line,&length,f) != EOF) {
  // getline leaves the newline at the end of the string. Not cool
  strtok(line,"\n");

  // Ignore everything on a line after a comment
  strtok(line,"//");

  // Process each command separated by a semicolon
  token = strtok(line,sc);
  while (token != NULL) {

   // Remove white space from command & argument
   strcpy(command,"");
   if (sscanf(token,"%s %s",command,argument) > 1) {
    strcat(command," ");
    strcat(command,argument);
   }

   // Process command
   read_command(command,true);

   // Read next command
   token = strtok(NULL,sc);
  }
 }

 fclose(f);
 return 0;
}

