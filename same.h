#include <stdlib.h>
#include <ncurses.h>
#include <time.h>

static int width = 32;
static int height = 16;
int board[32][16];
static int blocknum = 4;

bool hled[1024][1024];
bool newgame;
bool firstgame;
int n, score;
int delblock(int x, int y);
int highlight(int x, int y);
int highlight_none();
int init();
int get_rand(int cap);
int reset_board();
int cursor_wait();
int cleanup();
int define_colors();
int x,y;
static char blocks[16] = " abcdABCD";

