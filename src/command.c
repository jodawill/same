#include "same.h"

int draw_board() {
 for (int col = 0; col < width; col++) {
  for (int row = 0; row < height; row++) {
   if (board[col][row] < 0) {
    attron(COLOR_PAIR(20));
    mvprintw(row,col," ");
   } else {
    attron(COLOR_PAIR(board[col][row]+1));
    mvprintw(row,col,"%c",blocks[board[col][row]+1]);
   }
  }
 }
 refresh();
 return 0;
}

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

int draw_undo() {
 attron(COLOR_PAIR(20));
 int h;
 if (height >= display_height) {
  h = height;
 } else {
  h = display_height;
 }
 mvprintw(h-4,width+1,"                     ");
 mvprintw(h-3,width+1,"                     ");
 mvprintw(h-4,width+1,"Undos available: %i",undonum);
 mvprintw(h-3,width+1,"Redos available: %i",redonum);
 move(y,x);

 return 0;
}

int draw_logo() {
 attron(COLOR_PAIR(20));
 mvprintw(0,width+1,"    SameGame");
 mvprintw(1,width+1,"by Josh Williams");
 move(y,x);
 return 0;
}

int draw_hst() {
 attron(COLOR_PAIR(20));
 if (highscore <= 0) {
  mvprintw(height-10,width+1,"Highscore:");
  mvprintw(height-9,width+1,"  Not set");
  return 1;
 }
 int h;
 if (height >= display_height) {
  h = height;
 } else {
  h = display_height;
 }
 mvprintw(h-10,width+1,"                 ");
 mvprintw(h-9,width+1,"                 ");
 mvprintw(h-8,width+1,"                 ");
 mvprintw(h-10,width+1,"Highscore:");
 mvprintw(h-9,width+3,"%s",hsn);
 mvprintw(h-8,width+3,"%i",highscore);
 move(y,x);
 return 0;
}

int draw_command(const char *text) {
 clear_command();
 attron(COLOR_PAIR(20));
 int a,b;
 getmaxyx(stdscr,a,b);
 mvprintw(a-1,0,text);
 refresh();
 move(y,x);
 return 0;
}

int draw_error(const char *text) {
 clear_command();
 attron(COLOR_PAIR(21));
 int a,b;
 getmaxyx(stdscr,a,b);
 mvprintw(a-1,0,text);
 refresh();
 move(y,x);

 return 0;
}

int draw_score() {
 attron(COLOR_PAIR(20));
 int h;
 if (height >= display_height) {
  h = height;
 } else {
  h = display_height;
 }
 mvprintw(h-1,width+1,"                             ");
 mvprintw(h-1,width+1,"Score: %i",score);
 if (easy) {
  mvprintw(h-6,width+1,"Difficulty: Easy");
 } else {
  mvprintw(h-6,width+1,"Difficulty: Hard");
 }
 return 0;
}

int clear_command() {
 int a,b;
 getmaxyx(stdscr,a,b);
 attron(COLOR_PAIR(20));
 for (int c = 0; c < b; c++) {
  mvprintw(a-1,c," ");
 }
 refresh();
 move(y,x);
 return 0;
}

int command_wait() {
 char key[1024];
 echo();
 getnstr(key,sizeof key);
 noecho();
 int a,b;
 getmaxyx(stdscr,a,b);
 
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
 if (strcmp(key,"q") == 0) return 1;
 if (strcmp(key,"x") == 0) {
  // Save game
  draw_error("Save not yet implemented.");
  sleep(1);
  return 1;
 }
 if (strcmp(key,"w") == 0) {
  // Save game
  draw_error("Save not yet implemented.");
  return 0;
 }
 if (strcmp(key,"easy") == 0) {
  if (!easy) {
   draw_command("Easy mode enabled.");
   easy = true;
   reset_board();
  } else {
   draw_error("Already on easy mode.");
  }
  return 0;
 }
 if (strcmp(key,"hard") == 0) {
  if (easy) {
   draw_command("Hard mode enabled");
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
 char str[5];
 strncpy(str,key,4);
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
    int a,b;
    getmaxyx(stdscr,a,b);
    attron(COLOR_PAIR(20));
    mvprintw(a - 1,0,":");
    move(a-1,1);
    refresh();
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

