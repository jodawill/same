#include "same.h"

int read_hst() {
 FILE *hstf = fopen(".hst","r");
 if (hstf == NULL) {
  highscore = 0;
  return 1;
 }
 char hs[10];
 fgets(hs,sizeof hs,hstf);
 highscore = atoi(hs);
 fclose(hstf);
 return 0;
}

int write_hst() {
 FILE *hstf = fopen(".hst","w");
 if (hstf == NULL) return 1;
 fprintf(hstf,"%i",highscore);
 fclose(hstf);
 return 0;
}

