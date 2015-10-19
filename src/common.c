#include "same.h"

// Is the substring srch at str[0]?
bool is_subst_here(const char *str,const char *srch) {
 int i;
 for (i = 0; i < strlen(srch); i++) {
  if (str[i] != srch[i]) return false;
 }
 return true;
}

// Remove sl characters from str at str[i] and insert repl there.
int replst(char *str,int i,int sl,const char* repl) {
 char str1[1024];
 char str2[1024];
 char str3[1024];
 strncpy(str1,str,i);
 str1[i] = '\0';
 strcat(str1,repl);
 strcat(str1,&str[i+sl]);
 strcpy(str,str1);
 return 0;
}

// Replace all occurrences of srch in str with repl. This function works
// even if srch is a substring of repl. It's a very lazy implemenation and
// is almost assuredly vulnerable to buffer overflows. I will fix this soon.
int strrep(char *str,const char* srch, const char* repl) {
 int i,n = strlen(str);
 for (i = 0; i < n; i++) {
  if (is_subst_here(&str[i],srch)) {
   replst(str,i,strlen(srch),repl);
   i += strlen(repl);
  }
 }
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

int get_rand(int n) {
 int x = rand();
 while (n < RAND_MAX && x >= RAND_MAX - (RAND_MAX %n)) {
  x = rand();
 }
 return x%n;
}

int set_dir() {
 #if defined(__UNISTD__)
  char *homedir = getenv("HOME");
  strcpy(dir,homedir);
  strcat(dir,"/.same");
  mkdir(dir,S_IRWXU);
  return 0;
 #endif

 return -1;
}

