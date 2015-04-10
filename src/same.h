#define DIF_EASY 1
#define DIF_HARD 0

#if defined(__APPLE__) || defined(__linux__)
 #define __NCURSES__
 #define __SUPPORTED__
#endif
#if defined(WIN16) || defined(WIN32) || defined(WIN64) || defined(MSDOS)
 #warning "MS graphics libraries are not yet supported. Graphics and" \\
          "keyboard features will not work, but we will compile anyway."
 #define __CONIO__
 #define __SUPPORTED__
#endif
#ifndef __SUPPORTED__
  #error "Your system is not supported."
#endif

#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <sys/stat.h>
#include <stdbool.h>
#include <stdio.h>
#if defined(__NCURSES__)
 #include <ncurses.h>
 #define COLOR_DEFAULT 20
 #define COLOR_ERROR   21
#endif

#ifndef KEY_UP
 #define KEY_UP -2
#endif
#ifndef KEY_DOWN
 #define KEY_DOWN -3
#endif
#ifndef KEY_LEFT
 #define KEY_LEFT -4
#endif
#ifndef KEY_RIGHT
 #define KEY_RIGHT -5
#endif

// Global variables
bool gameover;
int x,y;
int display_x, display_height, display_width;
char hst_fn[1024];
int difficulty;
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
int command_wait();
int cursor_wait();

// common.c
bool confirm(const char* str);
int get_rand(int n);
int set_dir();

// draw.c
int draw_hst();
int draw_score();
int draw_undo();

// endgame.c
int end_game();

// graphics.c
int clean_screen();
int clear_all();
int draw_block(int col,int row,int block,bool hled);
int draw_clear_block(int col,int row);
int clear_command();
int command_prompt(char key[]);
int draw_command(const char* text);
int draw_display(int row,const char* msg);
int draw_error(const char *msg);
int draw_logo();
int get_max_x();
int get_max_y();
int init_screen();
int move_cursor(int col,int row);
int prompt_str(const char msg[],char outstr[],int strn);
int refresh_screen();

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

// sysdep.c
int ask_char();

