# SameGame

This is a SameGame clone with vi-like commands.

##Controls

To navigate, you may either use the arrows or 'hjkl'. To delete a section of blocks, press &lt;enter&gt;, 'dd', or 'x'.

To undo, press 'u' or type ':u'. To redo, press 'r' or type ':r'. You can see how many undos and redos you have available on the right side of the screen.

To quit, type ':q'. To save before quitting, type ':x'. (Not yet implemented.)

To save the game, type ':w'. (Not yet implemented.)

To play on easy mode, type ':easy'. To go back to hard mode, type ':hard'. There is also a special "god" mode to fill the board with one type of block, mainly for debugging purposes. To enable, type ':god'.

To resize the board, use ':seth n' and ':setw n'.

##Strategy

Points are calculated by (n-1)<sup>2</sup>, where n is the number of blocks in the chain being deleted. Thus, the more blocks you have in a chain, the more points you will earn.

