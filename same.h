#include <stdlib.h>
#include <ncurses.h>
#include <strings.h>
#include <unistd.h>
#include <time.h>

static int width = 32;
static int height = 16;
int board[32][16];
int board_undo[1024][32][16];
static int blocknum = 4;
char hsn[14];

bool easy;
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

