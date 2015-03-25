#include "same.h"

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
 FILE *hstf = fopen(".hst","r");
 if (hstf == NULL) {
  strcpy(hsn,"");
  highscore = 0;
  return 1;
 }
 char hs[10];
 fgets(hsn,(sizeof hsn)-2,hstf);
 fgets(hs,10,hstf);
 highscore = atoi(hs);
 fclose(hstf);
 return 0;
}

int write_hst() {
 FILE *hstf = fopen(".hst","w");
 if (hstf == NULL) return 1;
 if (score > highscore) highscore = score;
 fprintf(hstf,"%s\n",hsn);
 fprintf(hstf,"%i\n",highscore);
 fclose(hstf);
 return 0;
}

