// Game difficulty magic numbers
#define DIF_EASY 1
#define DIF_HARD 0

// Decide what graphics library to use based on the OS. Throw a compiler
// error if the OS isn't known to be supported.
#if defined(__APPLE__) || defined(__linux__)
 #define __NCURSES__
 #define __SUPPORTED__
#endif
#if defined(WIN32) || defined(WIN64) || defined(MSDOS) || defined(_WIN32) || defined(_WIN64) || defined(__WIN32__) || defined(__WIN64__) || defined(__CYGWIN32__) || defined(__CYGWIN64__) || defined(__CYGWIN__)
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

// Include headers for graphics libraries
#if defined(__NCURSES__)
 #include <ncurses.h>
 #define COLOR_DEFAULT 20
 #define COLOR_ERROR   21
#endif
#if defined(__CONIO__)
 #include <conio.h>
#endif

// These keys should be defined here when using a graphics library other
// than ncurses. They default to {-2,-3,-4,-5} so they don't cause errors
// in the keyboard wait function if they're not properly defined.
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
bool gameover; // Whether the game is over
int x,y; // Where the cursor is. This should be changed to a struct later
int display_height, display_width; // Dimensions for the table that displays
                                   // logo, score, highscore, etc.
char hst_fn[1024]; // Highscore table filename
int difficulty; // Difficulties are defined as DIF_EASY, DIF_HARD
bool god; // God mode fills the screen with one block
int highscore;
bool hled[1024][1024]; // Stores whether a position is highlighted
int width; // Board width. For screen width, get_max_x()
int height; // Board height. For screen height, get_max_y()
int board[1024][1024]; // Stores value of each block on board. The
                       // actual character map is in blocks[int].
int board_undo[1024][64][64]; // Same as board[][], but for the
                              // undo history.
static int blocknum = 4; // Total number of distinct block types
char hsn[14]; // Highscore name
int redonum; // Number of redos available
int undonum; // Number of undos available
int score_undo[1024]; // Stores score at each point in undo history
int n, score; // n is the number of blocks currently highlighted
static char blocks[16] = " abcdABCD"; // Character map for board
char dir[1024]; // Directory where settings are stored
bool saved; // Whether game has been saved since last change

// The rest of this file declares the functions in each file for global use.
// See each file for function descriptions.

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
int rest();

