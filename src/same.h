#include <stdlib.h>
#include <curses.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <sys/stat.h>

int width;
int height;
int max_width, max_height;
int board[1024][1024];
int board_undo[1024][1024][1024];
static int blocknum = 4;
char hsn[14];

// hst.c
int set_hst_fn();

bool gameover;
int set_width(int w);
int set_height(int h);
int display_height, display_width;
char hst_fn[1024];
bool easy;
bool god;
int highscore;
bool hled[1024][1024];
bool is_game_over();
bool is_block_alone(int x, int y);
int draw_logo();
int get_hsn();
int read_hst();
int write_hst();
int draw_hst();
int draw_board();
int redonum;
int draw_undo();
int end_game();
int draw_command(const char *text);
int draw_error(const char *text);
int clear_command();
int draw_score();
int undonum;
int score_undo[1024];
int undo();
int redo();
int copy_board();
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

