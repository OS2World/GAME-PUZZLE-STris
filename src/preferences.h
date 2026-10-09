/*******************************************************************************
*                                                                             *
* PREFERENCES.H                                                               *
* -------------                                                               *
*                                                                             *
* Settings for STris are stored in 'STris.cfg' as a binary record. The first  *
* three fields (saveonexit, detaillevel, current_lang) are the standard       *
* header required for the Games project; the rest are the game specific       *
* settings. Old or foreign files are tolerated as far as possible.            *
*                                                                             *
*******************************************************************************/

#ifndef PREFERENCES_H
#define PREFERENCES_H

#include "key.h"


/*** Defines ******************************************************************/

#define CFG_FILE        "STris.cfg"


/*** Types ********************************************************************/

struct PrefsStruct
{
    /* Standard header (see SETTINGS documents) */

    LONG    saveonexit;             /* 0 = do not save settings on exit       */
    LONG    detaillevel;            /* 0 = high, 1 = medium, 2 = low          */
    LONG    current_lang;           /* LANG_EN..LANG_IT                       */

    /* Game specific settings */

    BOOL    fSoundState;            /* Sound on/off                          */
    BOOL    fGridFlag;              /* Draw grid in the pieces               */
    BOOL    fShowNextPiece;         /* Show the next piece                   */
    BOOL    fRotateFlag;            /* Rotate clockwise instead of counter   */
    BOOL    fRemainPaused;          /* Keep pause after loosing the focus    */
    BOOL    fSolidColor;            /* Solid colours instead of dithered     */

    LONG    StartSpeed;             /* 0 (slow) .. MAX_SPEED (fast)          */
    LONG    StartLevel;             /* 0 .. MAX_LEVEL                        */
    LONG    Palette;                /* Index into palette table              */

    LONG    BackgroundRun;          /* Do not auto-pause on focus loss       */
    LONG    FrameControls;          /* Hide frame controls while playing     */

    KEYPREFS Keys[KEY_NUM];         /* Player defined keys                   */

    RECTL   win_rcl;                /* Window positions                      */
    RECTL   opt_rcl;
    RECTL   hsc_rcl;
    RECTL   abt_rcl;
    RECTL   ent_rcl;
    RECTL   key_rcl;

    BOOL    fExtraSquares;          /* Fill the start rows (see StartLevel)  */
};


/*** Variables ****************************************************************/

extern  struct  PrefsStruct STrisPrefs;


/*** Prototypes ***************************************************************/

void    InitPrefs(void);
BOOL    LoadPrefs(void);
BOOL    SavePrefs(void);

void    StoreWindowPos(HWND hwnd, PRECTL rectl);
void    RestoreWindowPos(HWND hwnd, PRECTL rectl);


#endif /* PREFERENCES_H */
