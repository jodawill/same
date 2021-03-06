#include "same.h"

int save_game(char in[]) {
 set_dir();
 char sfn[1024];
 char name[1024];
 strcpy(name,in);
 if (strcmp(name,"") == 0) {
  prompt_str("Enter save game name:",name,24);
 }
 strcpy(sfn,dir);
 strcat(sfn,"/");
 strcat(sfn,name);
 strcat(sfn,".sav");

 if (strstr(name,"..") != NULL) {
  draw_error("Game names are not allowed to contain two dots.");
  return 1;
 }

 FILE *sgf = fopen(sfn,"w");

 if (fprintf(sgf,"%d\n%d\n%d\n%d\n%d\n%d\n%d\n",width,height,score,undonum,redonum,(int)difficulty,(int)god) < 0) {
  draw_error("Cannot open file: access denied");
  return ERROR;
 }

 for (int u = 0; u <= undonum+redonum; u++) {
  fprintf(sgf,"%d\n",score_undo[u]);
 }

 for (int col = 0; col < width; col++) {
  for (int row = 0; row < height; row++) {
   fprintf(sgf,"%c",(char)board[col][row]+1);
  }
 }

 for (int u = 0; u <= undonum+redonum; u++) {
  for (int col = 0; col < width; col++) {
   for (int row = 0; row < height; row++) {
    // Add 1 to the block number so we don't print a -1
    fprintf(sgf,"%c",(char)board_undo[u][col][row]+1);
   }
  }
 }

 fclose(sgf);

 saved = true;
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
  prompt_str("Enter game name:",name,sizeof name-4);
 }
 strcpy(sfn,dir);
 strcat(sfn,"/");
 strcat(sfn,name);
 strcat(sfn,".sav");

 FILE *sgf = fopen(sfn,"r");
 if (sgf == NULL) {
  draw_error("Unable to open saved game file.");
  return 1;
 }

 int t_width, t_height, t_score, t_undonum, t_redonum, t_difficulty, t_god;
 int t_score_undo[1024];

 fscanf(sgf,"%d",&t_width);
 fscanf(sgf,"%d",&t_height);
 fscanf(sgf,"%d",&t_score);
 fscanf(sgf,"%d",&t_undonum);
 fscanf(sgf,"%d",&t_redonum);
 fscanf(sgf,"%d",&t_difficulty);
 fscanf(sgf,"%d",&t_god);

 for (int u = 0; u <= t_undonum+t_redonum; u++) {
  fscanf(sgf,"%d",&t_score_undo[u]);
 }

 int t_board[64][64];
 int t_board_u[128][64][64];

 if (feof(sgf)) lge();
 fgetc(sgf);

 for (int col = 0; col < t_width; col++) {
  for (int row = 0; row < t_height; row++) {
   t_board[col][row] = fgetc(sgf)-1;
  }
 }

 for (int u = 0; u <= t_undonum+t_redonum; u++) {
  for (int col = 0; col < t_width; col++) {
   for (int row = 0; row < t_height; row++) {
    t_board_u[u][col][row] = (int)fgetc(sgf)-1;
    if (t_board_u[u][col][row]+1 == EOF) return lge();
   }
  }
 }

 width = t_width;
 height = t_height;
 score = t_score;
 undonum = t_undonum;
 redonum = t_redonum;
 difficulty = t_difficulty;
 god = (bool)t_god;

 for (int u = 0; u <= undonum+redonum; u++) {
  score_undo[u] = t_score_undo[u];
 }

 for (int col = 0; col < width; col++) {
  for (int row =0; row < height; row++) {
   board[col][row] = t_board[col][row];
  }
 }

 for (int u = 0; u <= undonum+redonum; u++) {
  for (int col = 0; col < width; col++) {
   for (int row = 0; row < height; row++) {
    board_undo[u][col][row] = t_board_u[u][col][row];
   }
  }
 }

 fclose(sgf);

 clear_all();
 draw_hst();
 draw_score();
 draw_board();
 draw_undo();

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

int redo(bool script_mode) {
 saved = false;
 if (redonum <= 0) {
  if (!script_mode) draw_command("Already at the latest saved state.");
  return 1;
 }
 undonum++;
 for (int col = 0; col < width; col++) {
  for (int row = 0; row < height; row++) {
   board[col][row] = board_undo[undonum][col][row];
  }
 }
 draw_board();
 highlight(pos.x,pos.y);
 score = score_undo[undonum];
 draw_score();
 redonum--;
 if (!script_mode) draw_command("Reverted to next board state.");
 if (is_game_over()) end_game();
 draw_undo();

 return 0;
}

int undo(bool script_mode) {
 if (undonum <= 0) {
  if (!script_mode) draw_command("Already at the earliest state.");
  return 1;
 }

 saved = false;
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
 highlight(pos.x,pos.y);
 draw_score();
 redonum++;
 draw_undo();
 if (!script_mode) draw_command("Reverted to last change.");

 return 0;
}

