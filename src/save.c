#include "same.h"

int save_game(char in[]) {
 set_dir();
 char sfn[1024];
 char name[1024];
 strcpy(name,in);
 if (strcmp(name,"") == 0) {
  draw_command("Enter save game name: ");
  int a,b;
  getmaxyx(stdscr,a,b);
  attron(COLOR_PAIR(20));
  move(a-1,22);
  echo();
  getnstr(name,sizeof &name);
  noecho();
 }
 strcpy(sfn,dir);
 strcat(sfn,"/");
 strcat(sfn,name);
 strcat(sfn,".sav");

 FILE *sgf = fopen(sfn,"w");

 fprintf(sgf,"%d\n%d\n%d\n%d\n%d\n",width,height,score,(int)easy,(int)god);
 for (int col = 0; col < width; col++) {
  for (int row = 0; row < height; row++) {
   // Add 1 to the block number so we don't print a -1
   fprintf(sgf,"%c",(char)board[col][row]+1);
  }
 }

 fclose(sgf);

 char str[32];
 strcpy(str,"Saved game as '");
 strcat(str,name);
 strcat(str,"'.");
 draw_command(str);

 return 0;
}

int lge() {
 draw_error("Error loading saved game.");

 return 0;
}

int load_game(char in[]) {
 set_dir();
 char sfn[1024];
 char name[1024];
 strcpy(name,in);
 if (strcmp(name,"") == 0) {
  draw_command("Enter saved game name: ");
  int a,b;
  getmaxyx(stdscr,a,b);
  attron(COLOR_PAIR(20));
  move(a-1,22);
  echo();
  getnstr(name,sizeof &name);
  noecho();
 }
 strcpy(sfn,dir);
 strcat(sfn,"/");
 strcat(sfn,name);
 strcat(sfn,".sav");

 FILE *sgf = fopen(sfn,"r");

 int t_width, t_height, t_score, t_easy, t_god;

 fscanf(sgf,"%d",&t_width);
 fscanf(sgf,"%d",&t_height);
 fscanf(sgf,"%d",&t_score);
 fscanf(sgf,"%d",&t_easy);
 fscanf(sgf,"%d",&t_god);

 int t_board[64][64];

 if (feof(sgf)) lge();
 fgetc(sgf);
 for (int col = 0; col < t_width; col++) {
  for (int row = 0; row < t_height; row++) {
   t_board[col][row] = (int)fgetc(sgf)-1;
   if (t_board[col][row]+1 == EOF) return lge();
  }
 }

 width = t_width;
 height = t_height;
 score = t_score;
 easy = (bool)t_easy;
 god = (bool)t_god;

 for (int col = 0; col < width; col++) {
  for (int row = 0; row < height; row++) {
   board[col][row] = t_board[col][row];
  }
 }

 fclose(sgf);

 draw_hst();
 draw_score();
 draw_board();

 char str[32];
 strcpy(str,"Loaded game '");
 strcat(str,name);
 strcat(str,"'.");
 draw_command(str);

 return 0;
}

int copy_board() {
 if (undonum < 0) return 1;

 for (int col = 0; col < width; col++) {
  for (int row = 0; row < height; row++) {
   board_undo[undonum][col][row] = board[col][row];
  }
 }
 score_undo[undonum] = score;

 return 0;
}

int redo() {
 if (redonum <= 0) {
  draw_command("Already at the latest saved state.");
  return 1;
 }
 undonum++;
 for (int col = 0; col < width; col++) {
  for (int row = 0; row < height; row++) {
   board[col][row] = board_undo[undonum][col][row];
  }
 }
 draw_board();
 highlight(x,y);
 score = score_undo[undonum];
 draw_score();
 redonum--;
 draw_command("Reverted to next board state.");
 if (is_game_over()) end_game();
 refresh();

 return 0;
}

int undo() {
 if (undonum <= 0) {
  draw_command("Already at the earliest state.");
  return 1;
 }

 gameover = false;
 if (redonum <= 0) copy_board();
 undonum--;

 for (int col = 0; col < width; col++) {
  for (int row = 0; row < height; row++) {
   board[col][row] = board_undo[undonum][col][row];
  }
 }
 score = score_undo[undonum];
 draw_board();
 highlight(x,y);
 draw_score();
 redonum++;
 draw_command("Reverted to last change.");
 refresh();

 return 0;
}

