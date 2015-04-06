#include <stdlib.h>
#include <curses.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <sys/stat.h>

// Global variables
bool gameover;
int x,y;
int display_height, display_width;
char hst_fn[1024];
bool easy;
bool god;
int highscore;
bool hled[1024][1024];
int width;
int height;
int max_width, max_height;
int board[1024][1024];
int board_undo[1024][64][64];
static int blocknum = 4;
char hsn[14];
int redonum;
int undonum;
int score_undo[1024];
int n, score;
static char blocks[16] = " abcdABCD";
bool hl_board[64][64];
char dir[1024];
bool saved;

// board.c
int draw_board();
bool is_block_alone(int col, int row);
bool is_game_over();
int reset_board();
int set_height();
int set_width();

// colors.c
int define_colors();

// command.c
int clear_command();
int command_wait();
int cursor_wait();

// common.c
bool confirm(const char* str);
int get_rand(int n);
int set_dir();

// draw.c
int draw_command(const char* text);
int draw_error();
int draw_hst();
int draw_logo();
int draw_score();
int draw_undo();

// endgame.c
int end_game();

// graphics.c
int draw_block(int col,int row,int block,bool hled);
int draw_command_prompt();

// highlight.c
int check_hl(int x,int y,char bl,bool remq);
int collapse();
int collapse_horizontal();
int collapse_vertical();
int delblock(int x,int y);
int highlight(int x,int y);
int highlight_none();
bool move_horizontal(int col);
bool is_col_empty(int col);

// hst.c
int get_hsn();
int read_hst();
int set_hst_fn();
int write_hst();

// init.c
int cleanup();
int init();

// save.c
int copy_board();
int load_game(char in[]);
int redo();
int save_game(char in[]);
int undo();

