#include "same.h"

int command_wait() {
 char key[1024];
 echo();
 getnstr(key,sizeof key);
 noecho();
 int a,b;
 getmaxyx(stdscr,a,b);
 char str[32];
 
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
   return 1;
  } else {
   draw_error("No write since last change (add ! to override)");
   return 0;
  }
 }
 if (strcmp(key,"q!") == 0 ) {
  return 1;
 }
 if (key[0] == 'x') {
  // Save game
  if (strcmp(key,"x") == 0) {
   save_game("");
   return 1;
  }
  if (key[1] == ' ') {
   strncpy(str,&key[2],strlen(key)-1);
   str[strlen(key)-2] = '\0';
   save_game(str);
   return 1;
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
 if (key[0] == 'o') {
  // Open saved game
  if (strcmp(key,"o") == 0) {
   load_game("");
   return 0;
  }
  if (key[1] == ' ') {
   strncpy(str,&key[2],strlen(key)-1);
   str[strlen(key)-2] = '\0';
   load_game(str);
   return 0;
  }
 }
 if (strcmp(key,"easy") == 0) {
  if (!easy || god) {
   if (!gameover &&
       !confirm("Changing difficulty will reset the board. Continue?")) {
    return 0;
   }
   draw_command("Easy mode enabled.");
   god = false;
   easy = true;
   reset_board();
  } else {
   draw_error("Already on easy mode.");
  }
  return 0;
 }
 if (strcmp(key,"hard") == 0) {
  if (easy || god) {
   draw_command("Hard mode enabled");
   if (!gameover &&
       !confirm("Changing difficulty will reset the board. Continue?")) {
    return 0;
   }
   god = false;
   easy = false;
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
 refresh();

 return 0;
}

int cursor_wait() {
 char c = '\0';
 move(y,x);
 while (true) {
  switch (getch()) {
   case ':': {
    clear_command();
    draw_command_prompt();
    if (command_wait() == 1) {
     return 0;
    }
    break;
   }
   case 'u': {
    undo();
    break;
   }
   case 'r': {
    redo();
    break;
   }
   case 'd': {
    if (getch() != 'd') break;
   }
   case 'x': {
   }
   case '\n': {
    delblock(x,y);
    break;
   }
   case KEY_LEFT: {
   }
   case 'h': {
    if (x > 0) x--;
    break;
   }
   case KEY_RIGHT: {
   }
   case 'l': {
    if (x < width - 1) x++;
    break;
   }
   case KEY_UP: {
   }
   case 'k': {
    if (y > 0) y--;
    break;
   }
   case KEY_DOWN: {
   }
   case 'j': {
    if (y < height - 1) y++;
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
  }
  move(y,x);
  highlight(x,y);
  refresh();
 }
}

