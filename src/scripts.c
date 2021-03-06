#include "same.h"

int read_script(char fn[]) {
 FILE *f = fopen(fn,"r");
 if (f == NULL) {
  char msg[64];
  strcpy(msg,"Unable to load script ");
  strcat(msg,fn);
  draw_error(msg);
  return 1;
 }
 size_t length = 0;
 char *line = NULL;
 char *token;

 while (getline(&line,&length,f) != EOF) {
  char *ptr;
  // getline leaves the newline at the end of the string. Not cool
  strtok_r(line,"\n",&ptr);

  // Ignore everything on a line after a comment
  token = strsep(&line,"//");

  // Process each command separated by a semicolon
  token = strtok_r(token,";",&ptr);
  while (token != NULL) {

   // Process statement
   evaluate(token,true);

   // Read next statement
   token = strtok_r(NULL,";",&ptr);
  }
 }

 fclose(f);
 return 0;
}

int evaluate(char *cmd,bool script_mode) {
 // Evaluate expression enclosed by `cmd` and prepend its result to the
 // proceeding command. Example: `undonum`u will undo the board to its
 // original state.
 char str[32];
 int i;
 if (cmd[0] == '`') {
  for (i = 1; i < strlen(cmd); i++) {
   if (cmd[i] == '`') {
    break;
   } else {
    str[i-1] = cmd[i];
   }
  }
  str[i-1] = '\0';
  cmd = &cmd[i+1];
  sprintf(str,"%d",evaluate(str,script_mode));
  sprintf(str,"%s%s",str,cmd);
  return evaluate(str,script_mode);
 }


 // Remove white space from command & argument
 char argument[32];
 char command[32];
 strcpy(command,"");
 if (sscanf(cmd,"%s %s",command,argument) > 1) {
  strcat(command," ");
  strcat(command,argument);
 }

 // Return command
 return read_command(command,script_mode);
} 

