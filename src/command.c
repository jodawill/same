#include "same.h"

int command_wait() {
 char key[get_max_x()+4];
 char str[32];

 command_prompt(key);
 
 if (strcmp(key,"new") == 0) {
  clear_command();
  if (!gameover && confirm("Are you sure you want to start a new game?")) {
   reset_board();
  }
  if (gameover) reset_board();
  return 0;
 }
 if (strcmp(key,"") == 0) {
  clear_command();
  return 0;
 }
 if (strcmp(key,"u") == 0) {
  clear_command();
  undo();
  return 0;
 }
 if (strcmp(key,"r") == 0) {
  clear_command();
  redo();
  return 0;
 }
 if (strcmp(key,"q") == 0) {
  if (saved) {
   return EXIT;
  } else {
   draw_error("No write since last change (add ! to override)");
   return 0;
  }
 }
 if (strcmp(key,"q!") == 0 ) {
  return EXIT;
 }
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
 if (key[0] == 'w') {
  // Save game
  if (strcmp(key,"w") == 0) {
   save_game("");
   return 0;
  }
  if (key[1] == ' ') {
   strncpy(str,&key[2],strlen(key)-1);
   str[strlen(key)-2] = '\0';
   save_game(str);
   return 0;
  }
 }
 if (key[0] == 'e') {
  // Open saved game
  if (key[1] != '!' && !saved) {
   draw_error("No write since last change (add ! to override)");
   return 0;
  }
  if (strcmp(key,"e") == 0 || strcmp(key,"e!") == 0) {
   load_game("");
   return 0;
  }
  if (key[1] == ' ' || (key[1] == '!' && key[2] == ' ')) {
   int offset = 2;
   if (key[1] == '!') offset++;
   strncpy(str,&key[offset],strlen(key)-1);
   str[strlen(key)-offset] = '\0';
   load_game(str);
   return 0;
  }
 }
 if (strcmp(key,"easy") == 0) {
  if (difficulty == DIF_HARD || god) {
   if (!gameover &&
       !confirm("Changing difficulty will reset the board. Continue?")) {
    return 0;
   }
   draw_command("Easy mode enabled.");
   god = false;
   difficulty = DIF_EASY;
   reset_board();
  } else {
   draw_error("Already on easy mode.");
  }
  return 0;
 }
 if (strcmp(key,"hard") == 0) {
  if (difficulty == DIF_EASY || god) {
   draw_command("Hard mode enabled");
   if (!gameover &&
       !confirm("Changing difficulty will reset the board. Continue?")) {
    return 0;
   }
   god = false;
   difficulty = DIF_HARD;
   reset_board();
  } else {
   draw_error("Already on hard mode");
  }
  return 0;
 }
 if (strcmp(key,"god") == 0) {
  if (god) {
   draw_command("God mode disabled");
   god = false;
   reset_board();
  } else {
   if (!confirm("Enabling god mode will reset the board.")) return 0;
   draw_command("God mode enabled");
   god = true;
   reset_board();
  }
  return 0;
 }
 strncpy(str,key,9);
 str[9] = '\0';
 if (strcmp(str,"animation") == 0) {
  sscanf(key,"%s %s",str,str);
  if (strcmp(str,"off") == 0) animation = false;
  else if (strcmp(str,"on") == 0) animation = true;
  else draw_error("Error: Invalid argument to 'animation'");
  return 0;
 }
 strncpy(str,key,4);
 str[4] = '\0';
 if (strcmp(str,"setw") == 0) {
  if (!confirm("Setting the width will reset the game. Continue?")) {
   return 0;
  }
  char w[strlen(key-5)];
  strncpy(w,&key[5],strlen(key)-5);
  set_width(atoi(w));
  return 0;
 }
 if (strcmp(str,"seth") == 0) {
  if (!confirm("Setting the height will reset the game. Continue?")) {
   return 0;
  }
  char h[strlen(key-5)];
  strncpy(h,&key[5],strlen(key)-5);
  set_height(atoi(h));
  return 0;
 }

 // If we haven't found a command by now, the input must be invalid
 char text[1024] = "";
 strcat(text,"Not a command: ");
 strcat(text,key);
 draw_error(text);

 return 0;
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
     undo();
    }
    break;
   }
   case 'r': {
    for (int i = 0; i < multiplier; i++) {
     redo();
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

