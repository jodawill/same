#include "same.h"

int set_hst_fn() {
 set_dir();
 sprintf(hst_fn,"%s/.hst-%d-%d-%d",dir,(int)easy,width,height);

 return 0;
}

int get_hsn() {
 clear_command();
 int a,b;
 getmaxyx(stdscr,a,b);
 attron(COLOR_PAIR(20));
 mvprintw(a-1,0,"New highscore! Name: ");
 echo();
 strcpy(hsn,"");
 move(a-1,21);
 getnstr(hsn,(sizeof hsn)-4);
 while (strcmp(hsn,"") == 0) {
  draw_error("Name is required");
  getch();
  clear_command();
  mvprintw(a-1,0,"New highscore! Name: ");
  move(a-1,21);
  getnstr(hsn,(sizeof hsn)-4);
 }
 noecho();
 clear_command();
 write_hst();
 return 0;
}

int read_hst() {
 highscore = 0;
 set_hst_fn();
 FILE *hstf = fopen(hst_fn,"r");
 if (hstf == NULL) {
  return 1;
 }
 fscanf(hstf,"%s",hsn);
 fscanf(hstf,"%i",&highscore);
 fclose(hstf);
 return 0;
}

int write_hst() {
 FILE *hstf = fopen(hst_fn,"w");
 if (hstf == NULL) return 1;
 if (score > highscore) highscore = score;
 fprintf(hstf,"%s\n",hsn);
 fprintf(hstf,"%i\n",highscore);
 fclose(hstf);
 return 0;
}

