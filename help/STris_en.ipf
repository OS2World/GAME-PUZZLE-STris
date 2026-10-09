:userdoc.
:title.STris Online Help
:docprof toc=12.
:h1 res=1000.General
:p.STris is a Tetris clone for OS/2 Presentation Manager, originally written by Rene Straub (1995-1996).
:p.Pieces of four blocks fall into the playfield. Move and rotate them so that they fill complete horizontal lines. A complete line disappears and scores points. The game ends when there is no more room for a new piece.
:p.Use the Help menu for the topics How to play, Keys and Options, or press F1 in any dialog.
:p.:link reftype=hd res=4000.How to play:elink.
:p.:link reftype=hd res=4100.The Keys:elink.
:p.:link reftype=hd res=11000.Options:elink.
:p.:link reftype=hd res=2200.About STris:elink.
:h1 res=4000.How to play
:p.Navigate the falling pieces so that they fill up horizontal lines. Several lines removed at once score more points. Starting at a higher level or with a higher speed also gives more points.
:p.The falling piece is controlled with the keys listed under Keys. As the game goes on, the pieces fall faster.
:p.Choose Start Game (Ctrl+N) to begin. Pause (Ctrl+P) stops the game, Quit Game (Ctrl+Q) ends the current game and Exit (Ctrl+X) closes the program.
:h1 res=4100.The Keys
:p.These are the default keys. They can be changed in the Define Keys dialog (Options menu).
:table cols='26 22 10' rules=both frame=box.
:row.:c.:hp2.Function:ehp2.:c.:hp2.Key:ehp2.:c.:hp2.Numlock:ehp2.
:row.:c.Move left:c.Cursor Left:c.4
:row.:c.Move right:c.Cursor Right:c.6
:row.:c.Rotate:c.Cursor Up:c.8
:row.:c.Drop faster:c.Cursor Down:c.2
:row.:c.Pause:c.Pause or Ctrl+P:c. 
:etable.
:p.To use the numeric keypad, Numlock has to be enabled. The rotation in the other direction has no key by default; assign one in Define Keys.
:p.:hp2.Shortcuts:ehp2.
:table cols='12 50' rules=both frame=box.
:row.:c.Ctrl+N:c.Start a new game (ignored while a game is running)
:row.:c.Ctrl+P:c.Pause / resume
:row.:c.Ctrl+Q:c.Quit the current game (ignored when no game is running)
:row.:c.Ctrl+X:c.Exit the program
:row.:c.Ctrl+B:c.Background Run on/off
:row.:c.Ctrl+F:c.Frame Controls on/off
:etable.
:h1 res=11000.Options
:p.The settings dialog and the Options menu change the game. All settings are saved when you exit, if Save settings on exit is checked.
:parml tsize=22 break=none.
:pt.Speed
:pd.Initial falling speed of the pieces.
:pt.Startlevel
:pd.Each level starts the game with one more randomly filled line.
:pt.Sound
:pd.Sound effects on or off. Ghosted if no sound is available on your system.
:pt.Grid
:pd.Grid on the playfield, useful when dropping pieces.
:pt.Next Piece
:pd.Shows the next piece.
:pt.Remain paused
:pd.Keeps the game paused when the window regains the focus.
:pt.Palette
:pd.Selects a color map.
:pt.Solid color
:pd.Uses only solid colors (for 16 color displays).
:pt.Start with extra squares
:pd.Fills random rows at the bottom&colon. as many as the Startlevel says, or 4 rows if Startlevel is 0. Off = start with an empty playfield.
:pt.Detail
:pd.High, Medium or Low rendering detail.
:pt.Language
:pd.User interface and help language (English, Spanish, Dutch, German, French, Italian).
:pt.Background Run
:pd.If checked, the game keeps running when STris is not the active window. Otherwise it pauses automatically.
:pt.Frame Controls
:pd.Shows or hides the title bar and menu (borderless play). The window resizes automatically.
:pt.Save settings on exit
:pd.Saves the settings to STris.cfg when you exit. On by default.
:eparml.
:h1 res=12000 hide.Hiscore
:p.The Hall of Fame of the best players.
:h1 res=13000 hide.Enter Name
:p.You reached a score that enters the Hall of Fame. Type your name in the entry field.
:h1 res=14000 hide.Define Keys
:p.Select the function whose key you want to change by pressing its button, then press the new key. Press Esc to cancel. Some keys cannot be used; a message tells you.
:p.The Default button restores the standard keys.
:h1 res=2200.About STris
:p.STris 1.50 for OS/2, ArcaOS and eComStation.
:p.Original author&colon. Rene Straub (1995-1996).
:p.Port to Open Watcom 2.0&colon. OS2World community (2026).
:p.Licence&colon. GNU General Public License v3. See LICENSE.txt.
:p.:link reftype=hd res=6000.Changes in 1.50:elink.
:h1 res=6000.Changes in 1.50
:ul compact.
:li.Ported to Open Watcom 2.0.
:li.Menus&colon. Game, Options (with Language), Help; standard shortcuts.
:li.Six languages for the interface and the help.
:li.Background Run, Frame Controls, Save settings on exit.
:li.Pause is cleared when a game ends.
:eul.
:euserdoc.
