#include "same.h"

int command_wait() {
 char key[get_max_x()+4];
 char str[32];
 int num;

 command_prompt(key);
 return evaluate(key,false);
}
 
// Interpret a command string. If script_mode is enabled, nothing will be
// printed to the screen.
int read_command(char inp[],bool script_mode) {
 char arg[32], key[32];
 strcpy(arg,"");
 strcpy(key,"");
 int num, ret;

 // If the command begins with any numbers, use them as multipliers. Not all
 // commands support multipliers. For instance, it doesn't make since to
 // run `e filename` multiple times in one command.
 int mult = -1;
 sscanf(inp,"%d%s %s",&mult,key,arg);
 if (mult < 0) {
  mult = 1;
  sscanf(inp,"%s %s",key,arg);
 }
 if (mult <= 0) {
  return false;
 }

 // If the key is blank, do nothing but clear the command screen if in use
 if (strcmp(key,"") == 0) {
  if (!script_mode) clear_command();
  return true;
 }

 if (strcmp(key,"debug") == 0) {
  draw_command("Debug mode on");
  debug_mode = true;
  return 0;
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

 if (strcmp(key,"revgrav") == 0) {
  if (strcmp(arg,"on") == 0) {
   reverse_gravity = true;
   collapse_vertical();
   draw_command("Reverse gravity enabled");
   return 0;
  }
  if (strcmp(arg,"off") == 0) {
   reverse_gravity = false;
   collapse_vertical();
   draw_command("Reverse gravity disabled");
   return 0;
  }
  draw_error("Invalid argument to revgrav");
  return ERROR;
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
 if (strcmp(key,"x") == 0) {
  save_game(arg);
  return EXIT;
 }

 // :w will save the game
 if (strcmp(key,"w") == 0){
  return save_game(arg);
 }

 // :e will open a saved game
 if (key[0] == 'e' && strcmp(key,"easy") != 0) {
  // Open saved game
  if (key[1] != '!' && !saved) {
   if (!script_mode) {
    return draw_error("No write since last change (add ! to override)");
   }
  }
  return load_game(arg);
 }

 // :s will run the specified script
 if (strcmp(key,"s") == 0) {
  return read_script(arg);
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

 if (strcmp(key,"animation") == 0) {
  if (strcmp(arg,"off") == 0) animation = false;
  else if (strcmp(arg,"on") == 0) animation = true;
  else if (!script_mode) {
   draw_error("Error: Invalid argument to 'animation'");
   return false;
  }
  return true;
 }

 // Set board dimensions
 num = -1;
 sscanf(arg,"%d",&num);
 if (strcmp(key,"setw") == 0) {
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
 if (strcmp(key,"seth") == 0) {
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

 // Wait for a very short amount of time.
 if (strcmp("rest",key) == 0) {
  for (int i = 0; i < mult - 1; i++) {
   rest();
  }
  return rest();
 }

 // Display string (underscores become spaces) and return true or false.
 // Usage: confirm Are_you_sure?
 if (strcmp("confirm",key) == 0) {
  char hidden[] = {-1,0};
  strrep(arg,"\\_",hidden);
  for (int i = 1; i < strlen(arg); i++) {
   if (arg[i] == '_') {
    if (arg[i-(i != 0)] != '\\') {
     arg[i] = ' ';
    }
   }
  }
  strrep(arg,hidden,"_");

  // It isn't very helpful to repeat a confirmation, but who am I to tell the
  // user what they can or cannot do? Only the last return value is useful.
  for (int i = 0; i < mult - 1; i++) {
   confirm(arg);
  }
  return confirm(arg);
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
    if (debug_mode) {
     draw_debug_info();
    }
    break;
   }
   case KEY_RIGHT: {
   }
   case 'l': {
    for (int i = 0; i < multiplier; i++) {
     if (pos.x < width - 1) pos.x++;
    }
    if (debug_mode) {
     draw_debug_info();
    }
    break;
   }
   case KEY_UP: {
   }
   case 'k': {
    for (int i = 0; i < multiplier; i++) {
     if (pos.y > 0) pos.y--;
    }
    if (debug_mode) {
     draw_debug_info();
    }
    break;
   }
   case KEY_DOWN: {
   }
   case 'j': {
    for (int i = 0; i < multiplier; i++) {
     if (pos.y < height - 1) pos.y++;
    }
    if (debug_mode) {
     draw_debug_info();
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
   case '~': {
    if (god) score += multiplier;
    break;
   }
   default: {
    break;
   }
  }
  highlight(pos.x,pos.y);
 }
}

