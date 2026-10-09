STris for ArcaOS / eComStation / OS/2
======================================
Version 1.50

DESCRIPTION
-----------
STris is a Tetris clone for OS/2 Presentation Manager.
Originally written by Rene Straub in 1995-1996 (version 1.45).
Ported to OpenWatcom 2.0 by the OS2World community in 2026.

Features:
  - Tetris gameplay with 7 standard pieces
  - Optional random "extra squares" at the bottom when a game starts
  - Three detail levels: High, Medium, Low (affects rendering detail)
  - High-score table with name entry
  - 6-language interface and online help: English, Spanish, Dutch,
    German, French, Italian (switch at runtime in Options - Language)
  - Configurable key bindings
  - Sound effects (OS/2 multimedia), on by default
  - The game pauses automatically when the window loses the focus
    (unless Background Run is on)
  - Frame Controls toggle (Ctrl+F) for borderless play; the window
    resizes itself
  - Settings are saved to STris.cfg on exit (can be switched off)

LICENSE
-------
  GNU General Public License v3
  See doc\LICENSE.txt for the full license text.

REQUIREMENTS
------------
  - OS/2 Warp 4, eComStation, or ArcaOS
  - 32-bit Presentation Manager
  - OS/2 Multimedia (for sound effects; the game also runs without it)

INSTALLATION
------------
  Copy the program folder to any place and run STris.exe. Keep these
  next to STris.exe:
    help\    the online help, one file per language (STris_en.hlp, ...)
    Sounds\  the sound effects (breakit.wav, ding.wav, glass.wav)
  STris.cfg and STris.hsc (the high scores) are created in the folder
  you start the program from.

HOW TO PLAY
-----------
  Pieces fall from the top. Move and rotate them to fill complete rows.
  Each complete row is cleared and scores points; several rows at once
  score more. The game ends when a new piece has no room.

  Default keys (change them in Options - Define Keys):
    Left arrow   Move left
    Right arrow  Move right
    Up arrow     Rotate
    Down arrow   Drop faster
  A second rotation key (the other direction) is not assigned by
  default; give it a key in Define Keys.

KEYBOARD SHORTCUTS
------------------
  Ctrl+N    New game (ignored while a game is running)
  Ctrl+P    Pause / resume game
  Ctrl+Q    Quit the current game (asks first; ignored if no game runs)
  Ctrl+X    Exit the program
  Ctrl+B    Toggle Background Run
  Ctrl+F    Toggle Frame Controls (borderless mode)
  F1        Help

SETTINGS (Options - Settings)
-----------------------------
  Sound, Grid, Next Piece, Rotate clockwise, Remain paused, Palette,
  Solid colors, Speed, Startlevel and "Start with extra squares".

  Start with extra squares: when a game starts, the bottom of the
  playfield is filled with random squares - one row per Startlevel, or
  4 rows if Startlevel is 0. Switch it off to start with an empty
  playfield.

  Settings are stored in STris.cfg in the current directory.
  Delete STris.cfg to reset all settings to the defaults.

COMPILING FROM SOURCE
---------------------
  Requirements:
    - OpenWatcom 2.0  (wmake, wcc386, wlink, wrc, wipfc)
    - OS/2 Toolkit 4.5

  Build:
    compile-wat.cmd

  Output:
    bin\STris.exe
    bin\help\STris_xx.hlp

CREDITS
-------
  Original author:  Rene Straub (1995-1996)
  OS/2 port:        OS2World community (2026)
  OS2World site:    https://www.os2world.com

LINKS
-----
  https://github.com/OS2World/GAME-PUZZLE-STris
