/*** Function ID's for STris **************************************************/

#define STrisID                                                                 555
#define PrgAccel                                                                555
#define PrgIcon                                                                 555
#define PrgMenu                                                                 555
#define ID_BLDLEVEL                                                             900


#define AboutDialog                                     16402
#define DLG_OPTIONS                              16403
#define ShowHiscoreDialog                               1002
#define HiscoreDialog                                   1003
#define EnterNameDialog                                 1004
#define EnterName                                               1006
#define KeyDialog                                               1007

#define ToMBitmap                                                        16405
#define KeyLeftBitmap                                   1001
#define KeyRightBitmap                                  1002


/* Menu submenus */

#define IDM_SUBMENU_GAME                                1000
#define IDM_SUBMENU_OPTIONS                             1001
#define IDM_SUBMENU_DETAIL                              1002
#define IDM_SUBMENU_LANGUAGE                            1003
#define IDM_SUBMENU_HELP                                1004

/* Game menu */

#define IDM_NEW                                         101
#define IDM_PAUSE                                       102
#define IDM_QUIT                                        103
#define IDM_EXIT                                        104

/* Options menu */

#define IDM_SETTINGS                                    201
#define IDM_KEYS                                        202
#define IDM_HISCORE_MENU                                203
#define IDM_HIGHDET                                     204
#define IDM_MEDIUMDET                                   205
#define IDM_LOWDET                                      206
#define IDM_BACKGRND                                    207
#define IDM_FRAME                                       208
#define IDM_SAVEONEXIT                                  299

/* Language menu */

#define IDM_LANG_EN                                     300
#define IDM_LANG_ES                                     301
#define IDM_LANG_NL                                     302
#define IDM_LANG_DE                                     303
#define IDM_LANG_FR                                     304
#define IDM_LANG_IT                                     305

/* Help menu */

#define IDM_HELPUSING                                   901
#define IDM_HELPINDEX                                   902
#define IDM_HELPCONTENTS                                903
#define IDM_HELPHOWTOPLAY                               904
#define IDM_HELPKEYS                                    905
#define IDM_ABOUT_MENU                                  999

/* Help subtables */

#define OptionsHelpSubTable                             11002
#define AboutHelpSubTable                               11003
#define ShowHiscoreHelpSubTable                         11004
#define EnterNameHelpSubTable                           11005
#define KeyHelpSubTable                                 11006


#define PrgHelpSubTable                                 1000
#define PrgHelpTable                                    555
#define Help                                                                    555

#define IDD_HELP                                                                3001

#define IDD_ROTATE                                                              303
#define IDD_NR                                                                  1000
#define IDD_NAME                                                                1001
#define IDD_SCORE                                                               1002
#define IDD_LINES                                                               1003
#define IDD_LEVEL                                                               1004

#define IDD_PRGTITEL                                    500
#define IDD_AUTHORS                                                     501
#define IDD_COPYRIGHT                                   502
#define IDD_WARRANTY                                    503
#define IDD_DISTRIBUTION                                504

#define IDD_KEYLEFT                                                     510
#define IDD_KEYRIGHT                                    511
#define IDD_KEYROTATE                                   512
#define IDD_KEYROTATE2                                  513
#define IDD_KEYDROP                                                     514

#define IDD_TEXTLEFT                                    520
#define IDD_TEXTRIGHT                                   521
#define IDD_TEXTROTATE                                  522
#define IDD_TEXTROTATE2                                 523
#define IDD_TEXTDROP                                    524                                                     /* Never change order of these */

#define IDD_KEYTEXT1                                    525
#define IDD_KEYTEXT2                                    526


#define IDD_PALETTE                                     500
#define IDD_SOUND                                               300
#define IDD_GRID                                                301
#define IDD_NEXTPIECE                   302
#define IDD_SPEEDSLIDER                 400
#define IDD_LEVELSLIDER                 401
#define IDD_SPEEDTEXT                   402
#define IDD_LEVELTEXT                   403
#define IDD_REMAINPAUSED                404
#define IDD_SOLID                                               405
#define IDD_EXTRASQUARES                                406
#define IDD_LINES1                                              136
#define IDD_LEVEL1                                              149
#define IDD_RANK1                                               101
#define IDD_NAME1                                               111
#define IDD_SCORE1                                              121
#define IDD_TEXT_FIELD                  200
#define IDD_HISCORETEXT                 2000
#define IDD_DEFAULT                                     2001

/* Options dialog label/groupbox ids */

#define GB_SETTINGS                                     107
#define GB_DIFFICULTY                                   108
#define DLG_PALETTE                                     103
#define DLG_SPEED                                       102
#define DLG_STARTLEVEL                                  106

/* Key dialog label ids */

#define GB_KEYS                                         107

/* Hiscore dialog column ids reuse IDD_NR..IDD_LEVEL */

/* EnterName dialog label ids */

#define DIA_CONG_T1                                     105
#define DIA_CONG_T2                                     101
#define DIA_NAME_PROMPT                                 103

#define IDF_QUIT                                                16384
#define IDF_ABOUT                                               16385

#define IDF_UNUSED                                              16387                                                   /* Function not yet implemented */

#define IDF_HISCORE                                     16388
#define IDF_NEW_GAME                    16389
#define IDF_PAUSE                                               16390
#define IDF_STATISTICS                  16391
#define IDF_OPTIONS                                     16392
#define IDF_TEST                                                16393
#define IDF_KEY                                                 16397
#define IDF_USINGHELP                   16399
#define IDF_HOWTOPLAY                   16400
#define IDF_KEYSHELP                    16401

#define IDF_PLAYFIELD                   16395
#define IDF_NEXT_PIECE                  16396



/*-------------------------------------------------------------*
*  Help table and subtables                                                                *
*--------------------------------------------------------------*/

#define STRIS_HELP_TABLE                555                                                     // ID der HelpTable Ressource

// Manual

#define HELP_GENERAL                    1000

#define HELP_COPYRIGHT                  2000
#define HELP_DISCLAIMER                 2100
#define HELP_AUTHOR                                     2200
#define HELP_CREDITS                    2300
#define HELP_INSTALLATION 3100
#define HELP_HOWTOPLAY                  4000
#define HELP_KEYS                                               4100
#define HELP_BUGS                                               5000
#define HELP_REVISIONS                  6000


// Subpanels

#define HELP_OPTIONS                    11000
#define HELP_HISCORE                    12000
#define HELP_ENTER_HISCORE              13000
#define HELP_KEYDIALOG                  14000



// Commonly used help-pages

#define HELP_EMPTY_PAGE                 32000




#define LabelBitmap 1000
#define DLG_ABOUT 16402
#define DLG_SHOWHISCORE 1002
#define DLG_ENTERNAME 1004
#define DLG_KEY 1007

#define OptionsDialog 16403
#define IDF_HELPINDEX 32035
