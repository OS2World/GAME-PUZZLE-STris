/*******************************************************************************
*                                                                             *
* PREFERENCES.C 															   *
* ------------- 															   *
*                                                                             *
* Handling for default-settings, window-positions and so on.				   *
*                                                                             *
* Modification History: 													   *
* --------------------- 													   *
*                                                                             *
* 19.04.95	RHS  Created this file											*
* 10.05.95	RHS  Added Rotateflag											*
* 02.06.95	RHS  Collected all variables in PrefsStruct.					*
* 30.09.95	RHS  Added PositionRecord for KeyDialog 						   *
* 2026	     OD2  Ported to Open Watcom; settings moved from the OS/2        *
*                profile to 'STris.cfg' (standard Games-project format).     *
*                                                                             *
*******************************************************************************/

#define INCL_WIN
#include <os2.h>
#include <stdio.h>
#include <string.h>

#include "stris.h"
#include "window.h"
#include "playfield.h"
#include "sound.h"
#include "stub.h"
#include "key.h"
#include "lang.h"
#include "preferences.h"


/*** Variables ****************************************************************/

        struct  PrefsStruct STrisPrefs;


/*** Functions ****************************************************************/

/*******************************************************************************
* InitPrefs()
* Reset Preferences State to default
*******************************************************************************/

void InitPrefs(void)
{
    memset( &STrisPrefs, 0, sizeof( STrisPrefs ));

    STrisPrefs.win_rcl.xLeft =       /* Window placement to be deleted */
    STrisPrefs.opt_rcl.xLeft =
    STrisPrefs.hsc_rcl.xLeft =
    STrisPrefs.abt_rcl.xLeft =
    STrisPrefs.ent_rcl.xLeft =
    STrisPrefs.key_rcl.xLeft = POS_INVALID;

    STrisPrefs.saveonexit   = TRUE;
    STrisPrefs.detaillevel  = 1;             /* Medium (like the original) */
    STrisPrefs.current_lang = LANG_EN;

    STrisPrefs.fSoundState  = TRUE;          /* Sound on by default       */
    STrisPrefs.fExtraSquares = TRUE;         /* Like the original game    */

    STrisPrefs.fGridFlag    =
    STrisPrefs.fShowNextPiece = TRUE;

    InitKeymap();                            /* Default Keymap setzen     */
}


/*******************************************************************************
* Check the loaded values for sanity
*******************************************************************************/

static void ValidatePrefs(void)
{
    if( STrisPrefs.saveonexit != 0 && STrisPrefs.saveonexit != 1 )
        STrisPrefs.saveonexit = TRUE;

    if( STrisPrefs.detaillevel < 0 || STrisPrefs.detaillevel > 2 )
        STrisPrefs.detaillevel = 1;

    if( STrisPrefs.current_lang < 0 || STrisPrefs.current_lang >= LANG_COUNT )
        STrisPrefs.current_lang = LANG_EN;

    if( STrisPrefs.StartSpeed < 0 || STrisPrefs.StartSpeed > MAX_SPEED )
        STrisPrefs.StartSpeed = 0;

    if( STrisPrefs.StartLevel < 0 || STrisPrefs.StartLevel > MAX_LEVEL )
        STrisPrefs.StartLevel = 0;

    if( STrisPrefs.Palette < 0 || STrisPrefs.Palette > 5 )
        STrisPrefs.Palette = 0;

    STrisPrefs.fExtraSquares = (STrisPrefs.fExtraSquares != 0);
    STrisPrefs.BackgroundRun = (STrisPrefs.BackgroundRun != 0);
    STrisPrefs.FrameControls = (STrisPrefs.FrameControls != 0);
}


/*******************************************************************************
* Load Preferences
*******************************************************************************/

BOOL LoadPrefs(void)
{
    FILE    *f;
    LONG    hdr[3];
    size_t  got;

    InitPrefs();

    f = fopen( CFG_FILE, "rb" );
    if( !f )                                 /* first run: keep the defaults */
    {
        SetMusicState( STrisPrefs.fSoundState );   /* sound on by default */
        return TRUE;
    }

    got = fread( hdr, sizeof( LONG ), 3, f );
    if( got == 3 )
    {
        STrisPrefs.saveonexit   = hdr[0];
        STrisPrefs.detaillevel  = hdr[1];
        STrisPrefs.current_lang = hdr[2];

        /* Read the remaining game specific settings if present */
        /* byte count: an older, shorter file keeps the defaults for the rest */
        fread( ((PBYTE)&STrisPrefs) + 3*sizeof(LONG), 1,
               sizeof( STrisPrefs ) - 3*sizeof( LONG ), f );
    }

    fclose( f );

    ValidatePrefs();

    SetMusicState( STrisPrefs.fSoundState );
    SetKeymap();

    return TRUE;
}


/*******************************************************************************
* Save Preferences
*******************************************************************************/

BOOL SavePrefs(void)
{
    FILE    *f;

    STrisPrefs.fSoundState = GetMusicState();

    f = fopen( CFG_FILE, "wb" );
    if( !f ) return FALSE;

    fwrite( &STrisPrefs, 1, sizeof( STrisPrefs ), f );
    fclose( f );

    return TRUE;
}


/*******************************************************************************
* StoreWindowPos(hwnd, rectl)
* Store the current position of window hwnd into rectl.
*******************************************************************************/

void StoreWindowPos(HWND hwnd, PRECTL rectl)
{
    SWP     swp;

    WinQueryWindowPos( hwnd, &swp );
    rectl->xLeft   = swp.x;
    rectl->yBottom = swp.y;
}


/*******************************************************************************
* RestoreWindowPos(hwnd, rectl)
* Move window hwnd to the position described by rectl.
*******************************************************************************/

void RestoreWindowPos(HWND hwnd, PRECTL rectl)
{
    if( rectl->xLeft != POS_INVALID )
    {
        WinSetWindowPos( hwnd, HWND_TOP,
                         rectl->xLeft,
                         rectl->yBottom,
                         0, 0, SWP_MOVE | SWP_ZORDER );
    }
}
