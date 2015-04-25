#include "same.h"

int read_script(char fn[]) {
 FILE *f = fopen(fn,"r");
 if (f == NULL) {
  return 1;
 }
 size_t length = 0;
 char *line = NULL;
 char *token;

 // Currently, same only supports one command per line. This may change in
 // the future.
 while (getline(&line,&length,f) != EOF) {
  // getline leaves the newline at the end of the string. Not cool
  strtok(line,"\n");

  // Ignore everything on a line after a comment
  token = strsep(&line,"//");

  // Process each command separated by a semicolon
  token = strtok(token,";");
  while (token != NULL) {

   // Process statement
   evaluate(token);

   // Read next statement
   token = strtok(NULL,";");
  }
 }

 fclose(f);
 return 0;
}

int evaluate(char *cmd) {
 // Remove white space from command & argument
 char argument[32];
 char command[32];
 strcpy(command,"");
 if (sscanf(cmd,"%s %s",command,argument) > 1) {
  strcat(command," ");
  strcat(command,argument);
 }

 // Return command
 return read_command(command,true);
} 

