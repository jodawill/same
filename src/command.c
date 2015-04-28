#include "same.h"

int command_wait() {
 char key[get_max_x()+4];
 char str[32];
 int num;

 command_prompt(key);
 return read_command(key,false);
}
 
// Interpret a command string. If script_mode is enabled, nothing will be
// printed to the screen.
int read_command(char key[],bool script_mode) {
 char str[32];
 int num, ret;

 // If the command begins with any numbers, use them as multipliers. Not all
 // commands support multipliers. For instance, it doesn't make since to
 // run `e filename` multiple times in one command.
 int mult = -1;
 sscanf(key,"%d%s",&mult,key);
 if (mult <= 0) mult = 1;

 // If the key is blank, do nothing but clear the command screen if in use
 if (strcmp(key,"") == 0) {
  if (!script_mode) clear_command();
  return true;
 }

 // :new starts a new game
 if (strcmp(key,"new") == 0) {
  // Script mode
  if (script_mode) {
   reset_board();
   return 0;
  }

  // Interactive mode
  clear_command();
  if (!gameover && confirm("Are you sure you want to start a new game?")) {
   return reset_board();
  }
  if (gameover) return reset_board();
 }

 // :u is undo. Note that the command multiplier works differently in same
 // than it does in vi.
 if (strcmp(key,"u") == 0) {
  clear_command();
  for (int c = 0; c < mult; c++) {
   ret = undo(script_mode);
  }
  return ret;
 }

 // :r is redo
 if (strcmp(key,"r") == 0) {
  clear_command();
  for (int c = 0; c < mult; c++) {
   ret = redo(script_mode);
  }
  return ret;
 }

 // :q quits if the game has been saved
 if (strcmp(key,"q") == 0) {
  if (saved) {
   return EXIT;
  } else {
   if (!script_mode) {
    draw_error("No write since last change (add ! to override)");
   }
   return 0;
  }
 }

 // :q! will quit even if the game has not been saved
 if (strcmp(key,"q!") == 0 ) {
  return EXIT;
 }

 // :x will save the game before quitting
 if (key[0] == 'x') {
  // Save game, then exit the application
  if (strcmp(key,"x") == 0) {
   save_game("");
   return EXIT;
  }
  if (key[1] == ' ') {
   strncpy(str,&key[2],strlen(key)-1);
   str[strlen(key)-2] = '\0';
   save_game(str);
   return EXIT;
  }
 }

 // :w will save the game
 if (key[0] == 'w') {
  // Save game
  if (strcmp(key,"w") == 0) {
   return save_game("");
  }
  if (key[1] == ' ') {
   strncpy(str,&key[2],strlen(key)-1);
   str[strlen(key)-2] = '\0';
   return save_game(str);
  }
 }

 // :e will open a saved game
 if (key[0] == 'e') {
  // Open saved game
  if (key[1] != '!' && !saved) {
   if (!script_mode) {
    return draw_error("No write since last change (add ! to override)");
   }
  }
  if (strcmp(key,"e") == 0 || strcmp(key,"e!") == 0) {
   return load_game("");
  }
  if (key[1] == ' ' || (key[1] == '!' && key[2] == ' ')) {
   int offset = 2;
   if (key[1] == '!') offset++;
   strncpy(str,&key[offset],strlen(key)-1);
   str[strlen(key)-offset] = '\0';
   return load_game(str);
  }
 }

 // Set difficulty to easy, hard, or god
 if (strcmp(key,"easy") == 0) {
  if (difficulty == DIF_HARD || god) {
   if (!gameover && !script_mode) {
    if (!confirm("Changing difficulty will reset the board. Continue?")) {
     return false;
    }
   }
   if (!script_mode) draw_command("Easy mode enabled.");
   god = false;
   difficulty = DIF_EASY;
   reset_board();
   return true;
  } else {
   if (!script_mode) draw_error("Already on easy mode.");
  }
  return false;
 }
 if (strcmp(key,"hard") == 0) {
  if (difficulty == DIF_EASY || god) {
   if (!gameover && !script_mode) {
    if (!confirm("Changing difficulty will reset the board. Continue?")) {
     return false;
    }
   }
   god = false;
   difficulty = DIF_HARD;
   if (!script_mode) draw_command("Hard mode enabled");
   reset_board();
   return true;
  } else {
   if (!script_mode) draw_error("Already on hard mode");
   return false;
  }
 }
 if (strcmp(key,"god") == 0) {
  for (int c = 0; c < mult; c++) {
   if (god) {
    if (!script_mode) draw_command("God mode disabled");
    god = false;
    reset_board();
    return true;
   } else {
    if (!script_mode) {
     if (!confirm("Enabling god mode will reset the board.")) return false;;
     draw_command("God mode enabled");
    }
    god = true;
    reset_board();
    return true;
   }
  }
 }

 sscanf(key,"%s",str);
 if (strcmp(str,"animation") == 0) {
  sscanf(key,"%s %s",str,str);
  if (strcmp(str,"off") == 0) animation = false;
  else if (strcmp(str,"on") == 0) animation = true;
  else if (!script_mode) {
   draw_error("Error: Invalid argument to 'animation'");
   return false;
  }
  return true;
 }

 // Set board dimensions
 num = -1;
 sscanf(key,"%s %d",str,&num);
 if (strcmp(str,"setw") == 0) {
  if (num <= 0) {
   if (!script_mode) draw_error("Error: Invalid argument to 'setw'");
   return false;
  }
  if (!script_mode) {
   if (!confirm("Setting the width will reset the game. Continue?")) {
    return false;
   }
  }
  set_width(num,script_mode);
  return true;
 }
 if (strcmp(str,"seth") == 0) {
  if (num <= 0) {
   if (!script_mode) draw_error("Error: Invalid argument to 'seth'");
   return false;
  }
  if (!script_mode) {
   if (!confirm("Setting the height will reset the game. Continue?")) {
    return false;
   }
  }
  set_height(num,script_mode);
  return true;
 }

 /* --- BEGIN SCRIPT FUNCTIONS --- */
 // The following functions are only useful for scripts.

 if (strcmp("rest",key) == 0) {
  return rest();
 }

 /* --- END SCRIPT FUNCTIONS --- */

 /* --- BEGIN VARIABLES --- */
 // The commands in this section do nothing but return a variable's value.
 // They can be useful when writing scripts.

 if (strcmp("undonum",key) == 0) {
  return undonum;
 }

 if (strcmp("redonum",key) == 0) {
  return redonum;
 }

 if (strcmp("score",key) == 0) {
  return score;
 }

 /* --- END VARIABLES --- */

 // If we haven't found a command by now, the input must be invalid
 if (!script_mode) {
  char text[1024] = "";
  strcat(text,"Not a command: ");
  strcat(text,key);
  draw_error(text);
 }
 return ERROR;
}

int cursor_wait() {
 int current_char;
 bool reset_mult;
 while (true) {
  move_cursor(pos.x,pos.y);
  current_char = (int)ask_char();

  if (reset_mult) multiplier = 0;

  // If a number is pressed, add it to the multiplier and skip the switch
  if (current_char >= (int)'0' && current_char <= (int)'9') {
   reset_mult = false;
   if (multiplier == 0) {
    multiplier = current_char-(int)'0';
   } else {
    multiplier *= 10;
    multiplier += current_char-(int)'0';
   }
   continue;
  }
  // Else, signal to kill the multiplier next time
  reset_mult = true;

  if (multiplier == 0) {
   multiplier = 1;
  }
  switch (current_char) {
   case ':': {
    clear_command();
    if (command_wait() == EXIT) {
     return 0;
    }
    break;
   }
   case 'u': {
    for (int i = 0; i < multiplier; i++) {
     undo(false);
    }
    break;
   }
   case 'r': {
    for (int i = 0; i < multiplier; i++) {
     redo(false);
    }
    break;
   }
   case 'd': {
    if (ask_char() != 'd') break;
   }
   case 'x': {
   }
   case '\n': {
    for (int i = 0; i < multiplier; i++) {
     delblock(pos.x,pos.y);
    }
    break;
   }
   case KEY_LEFT: {
   }
   case 'h': {
    for (int i = 0; i < multiplier; i++) {
     if (pos.x > 0) pos.x--;
    }
    break;
   }
   case KEY_RIGHT: {
   }
   case 'l': {
    for (int i = 0; i < multiplier; i++) {
     if (pos.x < width - 1) pos.x++;
    }
    break;
   }
   case KEY_UP: {
   }
   case 'k': {
    for (int i = 0; i < multiplier; i++) {
     if (pos.y > 0) pos.y--;
    }
    break;
   }
   case KEY_DOWN: {
   }
   case 'j': {
    for (int i = 0; i < multiplier; i++) {
     if (pos.y < height - 1) pos.y++;
    }
    break;
   }
   case 'n': {
    clear_command();
    if (!gameover &&
        confirm("Are you sure you want to start a new game?")) {
     reset_board();
    }
    if (gameover) reset_board();
    break;
   }
   default: {
    break;
   }
  }
  highlight(pos.x,pos.y);
 }
}

