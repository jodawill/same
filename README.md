# SameGame

This is a SameGame clone with vi-like commands.

## Compiling

This software is known to compile on Mac OS X and GNU/Linux. The portability is mainly limited to the available graphics libraries. Currently, only ncurses is supported. In future releases, I intend to include support for other libraries, such as GTK. If you're interested in porting this to another system, please contact me. jodawill@members.fsf.org

GNU Make, gcc, and ncurses are required to compile SameGame.

### GNU/Linux
For Debian-based systems (such as Ubuntu):

````
sudo apt-get install build-essential libncurses5-dev
make
````

### Mac OS X
To simply install GNU Make and gcc, you can just install Xcode from the App Store. To install ncurses:

````
curl -O ftp://ftp.gnu.org/gnu/ncurses/ncurses-5.9.tar.gz
tar -xzvf ncurses-5.9.tar.gz
cd ./ncurses-5.9
./configure --prefix=/usr/local \
  --without-cxx --without-cxx-binding --without-ada --without-progs --without-curses-h \
  --with-shared --without-debug \
  --enable-widec --enable-const --enable-ext-colors --enable-sigwinch --enable-wgetch-events \
make
sudo make install
````

Once you have these installed, 'cd' back to the "same" directory and type 'make' to compile and './same' to run.

##Controls

To navigate, you may either use the arrows or 'hjkl'. To delete a section of blocks, press &lt;enter&gt;, 'dd', or 'x'.

To undo, press 'u' or type ':u'. To redo, press 'r' or type ':r'. You can see how many undos and redos you have available on the right side of the screen.

Command multipliers are supported. For example, to move 5 rows down, type '5j', or to delete 3 chains, type '3x'.

To quit, type ':q'. To save before quitting, type ':x'.

To save the game, type ':w'. Games are stored in '~/.same/NAME.sav'.

To play on easy mode, type ':easy'. To go back to hard mode, type ':hard'. There is also a special "god" mode to fill the board with one type of block, mainly for debugging purposes. To enable, type ':god'.

To resize the board, use ':seth n' and ':setw n'.

##Strategy

Points are calculated by (n-1)<sup>2</sup>, where n is the number of blocks in the chain being deleted. Thus, the more blocks you have in a chain, the more points you will earn.

##Bugs
Please report any bugs to https://github.com/jodawill/same/issues

