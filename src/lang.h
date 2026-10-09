/*******************************************************************************
*                                                                             *
* LANG.H                                                                      *
* ------                                                                      *
*                                                                             *
* Multi-language support for STris. The visible user-interface strings        *
* (menus, buttons, in-window labels, dialog labels) are kept in a             *
* lang_strings[6][NUM_STRINGS] table. The active language is stored in       *
* current_lang (0..5, see LANG_EN..LANG_IT).                                 *
*                                                                             *
*******************************************************************************/

#ifndef LANG_H
#define LANG_H


/*** Languages ****************************************************************/

#define LANG_EN       0
#define LANG_ES       1
#define LANG_NL       2
#define LANG_DE       3
#define LANG_FR       4
#define LANG_IT       5

#define LANG_COUNT    6


/*** String ID's **************************************************************/

enum
{
    STR_GAME,               /* Game menu title                  */
    STR_NEW,                /* New Game                         */
    STR_PAUSE,              /* Pause Game                       */
    STR_QUIT,               /* Quit Game                        */
    STR_EXIT,               /* Exit                             */
    STR_OPTIONS,            /* Options menu title               */
    STR_SETTINGS,           /* Settings...                      */
    STR_KEYS,               /* Define Keys...                   */
    STR_HISCORE,            /* Hiscore...                       */
    STR_DETAIL,             /* Detail                           */
    STR_DETAIL_HIGH,        /* High                             */
    STR_DETAIL_MEDIUM,      /* Medium                           */
    STR_DETAIL_LOW,         /* Low                              */
    STR_LANGUAGE,           /* Language                         */
    STR_BACKGROUND,         /* Background Run                   */
    STR_FRAME,              /* Frame Controls                   */
    STR_SAVEONEXIT,         /* Save settings on exit            */
    STR_HELP,               /* Help menu title                  */
    STR_USINGHELP,          /* Using Help                       */
    STR_HELPINDEX,          /* Help Index                       */
    STR_HELPCONTENTS,       /* Contents                         */
    STR_HOWTOPLAY,          /* How to play                      */
    STR_KEYSHELP,           /* Keys                             */
    STR_ABOUT,              /* Product information              */
    STR_LANG_EN,            /* Language names                  */
    STR_LANG_ES,
    STR_LANG_NL,
    STR_LANG_DE,
    STR_LANG_FR,
    STR_LANG_IT,
    STR_BTN_START,          /* Window buttons                  */
    STR_BTN_STOP,
    STR_BTN_HISCORE,
    STR_BTN_OPTIONS,
    STR_BTN_ABOUT,
    STR_BTN_PAUSE,
    STR_TXT_HISCORE,        /* In-window labels                */
    STR_TXT_SCORE,
    STR_TXT_LINES,
    STR_TXT_LEVEL,
    STR_DLG_NEWHISCORE,     /* Dialog titles                   */
    STR_DLG_HISCORE,
    STR_DLG_OPTIONS,
    STR_DLG_KEYS,
    STR_DLG_ENT_PROMPT,     /* Enter-name dialog               */
    STR_DLG_HISCORE_TEXT,   /* Hiscore dialog                  */
    STR_COL_NR,
    STR_COL_NAME,
    STR_COL_SCORE,
    STR_COL_LINES,
    STR_COL_LEVEL,
    STR_OPT_SETTINGS,       /* Options dialog                  */
    STR_OPT_DIFFICULTY,
    STR_OPT_SOUND,
    STR_OPT_GRID,
    STR_OPT_NEXTPIECE,
    STR_OPT_ROTATE,
    STR_OPT_REMAINPAUSED,
    STR_OPT_PALETTE,
    STR_OPT_SOLID,
    STR_OPT_SPEED,
    STR_OPT_STARTLEVEL,
    STR_KEY_GROUP,          /* Key dialog                      */
    STR_KEY_TEXT1,
    STR_KEY_TEXT2,
    STR_KEY_PROMPT,         /* "Press a key to %s, ESC to abort" */
    STR_KEY_FUNC_LEFT,
    STR_KEY_FUNC_RIGHT,
    STR_KEY_FUNC_ROTATE,
    STR_KEY_FUNC_ROTATE2,
    STR_KEY_FUNC_DROP,
    STR_KEY_MSG_SUCCESS,
    STR_KEY_MSG_ABORTED,
    STR_KEY_MSG_USED,
    STR_KEY_MSG_STRIS,
    STR_KEY_MSG_UNKNOWN,
    STR_OPT_PAL1,           /* Palette names                  */
    STR_OPT_PAL2,
    STR_OPT_PAL3,
    STR_OPT_PAL4,
    STR_OPT_PAL5,
    STR_OPT_PAL6,
    STR_ENT_CONG_T1,        /* Enter-name dialog               */
    STR_ENT_CONG_T2,
    STR_ABORT_GAME,         /* Confirm: abort the running game */
    STR_OPT_EXTRA,          /* Option: start with extra squares */
    NUM_STRINGS
};


/*** Variables ****************************************************************/

extern  char    *lang_strings[LANG_COUNT][NUM_STRINGS];
extern  int     current_lang;


/*** Prototypes ***************************************************************/

char *tr(int id);
void set_language(HWND hMenu, int lang);


#endif /* LANG_H */
