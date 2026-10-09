/*******************************************************************************
*																			   *
* S-Tris V1.43								 Project started  : 07.04.1995	   *
* ------------									  Last Update : 13.03.1996	   *
*																			   *
* Mein erstes PM Programm unter OS/2. Ein Ersatz fuer all die unbrauchbaren	   *
* Tetris Versionen die es unter OS/2 gibt.									   *
*																			   *
* Author Rene Straub				Tel.  +41 776 26 61 					   *
*		 Talstrasse 4				Fax   +41 776 14 17 					   *
*		 5726 Unterkulm (Schweiz)	EMail straub@crack.aare.ch				   *
*																			   *
* Modification History: 													   *
* --------------------- 													   *
*																			   *
* 07.04.95	RHS  Created this file. 										   *
* 09.04.95	RHS  First (poor) playable Version								   *
* 13.04.95	RHS  Split into several Sourcefiles 							   *
* 15.04.95	RHS  Hiscoreroutines											   *
* 20.04.95	RHS  Options Dialog 											   *
* 21.04.95	RHS  Preferences, New Handling for Piecesgraphics				   *
* 06.05.95	RHS  First Beta Version released								   *
* 02.07.95	RHS  Fixed Bug with Pause() Function							   *
* 23.07.95	RHS  OnLineHelp implemented 									   *
* 21.09.95	RHS  SoundEffects added 										   *
* 2026	     OD2  Ported to Open Watcom. Shareware registration removed,	   *
*                standardized menu structure, six-language UI, settings moved *
*                to 'STris.cfg', standard about dialog.						   *
*																			   *
*******************************************************************************/

#define INCL_SW
#define INCL_WIN
#define INCL_GPI
#define INCL_OS2MM

#include <os2.h>
#include <os2me.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#include "stris.h"
#include "window.h"
#include "playfield.h"
#include "pieces.h"
#include "timer.h"
#include "about.h"
#include "hiscore.h"
#include "hiscwindow.h"
#include "options.h"
#include "key.h"
#include "sound.h"
#include "preferences.h"
#include "help.h"
#include "lang.h"
#include "stub.h"

#include "stris_id.h"



/*** Defines ******************************************************************/

#define NO_SAFE_QUIT		// Disable 'Quit'-Requester


/*** Prototypes ***************************************************************/

static ULONG DetailFunction(HWND hwnd,ULONG msg,MPARAM mp1, MPARAM mp2);
static ULONG BackgrndFunction(HWND hwnd,ULONG msg,MPARAM mp1, MPARAM mp2);
static ULONG FrameFunction(HWND hwnd,ULONG msg,MPARAM mp1, MPARAM mp2);
static ULONG SaveOnExitFunction(HWND hwnd,ULONG msg,MPARAM mp1, MPARAM mp2);
static ULONG LanguageFunction(HWND hwnd,ULONG msg,MPARAM mp1, MPARAM mp2);


/*** Variables ****************************************************************/

		HAB 		hab;
static	HMQ 		hmq;
static	BOOL		fPaused;
static	BOOL		bFrameHidden;


/*** Functions ****************************************************************/


/*******************************************************************************
* ExitFunction()
* Send WM_CLOSE Message to MessageHandler. Main MessageLoop will prompt user
* for confirmation
*******************************************************************************/

static ULONG ExitFunction(HWND hwnd,ULONG msg,MPARAM mp1, MPARAM mp2)
{
	WinSendMsg( hwnd, WM_CLOSE, 0,0 );

	return TRUE;
}



INT main ( VOID )
{
	QMSG		qmsg;
	ULONG		l;
	HWND		hwndMenu;

	hab = WinInitialize(0);
	hmq = WinCreateMsgQueue(hab,0);

#ifndef CODE_PRG
	BusyPointer(TRUE);

	GetDesktopSize();
	InitRandom();
	LoadPrefs();
	current_lang = STrisPrefs.current_lang;		// language saved in STris.cfg

	OpenWindow( hab );
	OpenHelp();

	GetCharSize( hwndClient );
	SetPieceSize();
	if( !InitPieceBitmap() )
		ErrorMsg("Can't create pieces !");

	if( LoadHiscore(HISCORE_FILE) != hsc_OK)
		Message("Can't open hiscore !" );
	Hiscore = GetHiscore();

	if(!LoadBitmaps())
		ErrorMsg("Can't open LabelBitmap !");

	OpenMusic();

	BuildWindow( hwndClient, hwndFrame );

	/* Re-label the UI according to the language loaded from the config */
	set_language( WinWindowFromID( hwndFrame, FID_MENU ), current_lang );

	/* Bring the toggle check marks in line with the loaded config and
	   disable the Pause/Quit actions until a game is started */
	hwndMenu = WinWindowFromID( hwndFrame, FID_MENU );
	WinCheckMenuItem(hwndMenu, IDM_BACKGRND,  STrisPrefs.BackgroundRun);
	WinCheckMenuItem(hwndMenu, IDM_SAVEONEXIT, STrisPrefs.saveonexit);
	WinCheckMenuItem(hwndMenu, IDM_FRAME,     FALSE);
	SetActionMenus( FALSE );

	BusyPointer(FALSE);

	while( TRUE )
	{
		{
			while( WinGetMsg( hab, &qmsg, NULLHANDLE, 0, 0 ) )
			{
				WinDispatchMsg(hab, &qmsg );
			}

#ifdef SAFE_QUIT
			if( MBID_YES == WinMessageBox(HWND_DESKTOP,hwndClient,
							"Do you really want to quit ?",
							FULL_NAME,0,MB_ICONQUESTION | MB_YESNO | MB_MOVEABLE ) )
				break;
			else
				WinCancelShutdown( hmq, FALSE );
#else
				break;
#endif
		}
	}
#endif


#ifdef CODE_PRG
	RegFunction(NULLHANDLE,0,0,0);
#endif

	cleanup( RC_NORMAL );

	return 0;
}


/*******************************************************************************
* cleanup(error_code)
* Global exit routine. Frees all opened resources and returns to system with
* given error_code.
*******************************************************************************/

void cleanup(int error_code)
{
#ifndef CODE_PRG
	FreeTimer( hab, hwndClient );			// Stop Timer

	CloseMusic();
	CloseHelp();							// Close Help System
	CloseWindow( hwndFrame );				// Close Window (and all subwindows)
	UnloadBitmaps();						// Free Bitmaps
	ClosePieceBitmap(); 					// Free Bitmap with Elements

	if( SaveHiscore(HISCORE_FILE) != hsc_OK )
		Message("Can't write hiscore !");

	if( STrisPrefs.saveonexit )
		if( !SavePrefs() )
			Message("Can't write profile !");

#endif
	WinDestroyMsgQueue( hmq );				// Close MessageQueue
	WinTerminate( hab );					// Terminate Windowsystem

	exit( error_code ); 					// Return to System
}



static struct IDCommandList Commands[] =
{
	IDF_NEW_GAME,	NewGameFunction,
	IDF_OPTIONS,	OptionsFunction,
	IDF_HISCORE,	ShowHiscoreFunction,
	IDF_PAUSE,		PauseFunction,
	IDF_QUIT,		ExitFunction,
	IDF_KEY,		KeyFunction,
	IDF_ABOUT,		AboutFunction,

	IDM_NEW,		MenuNewGameFunction,
	IDM_PAUSE,		PauseFunction,
	IDM_QUIT,		QuitGameFunction,
	IDM_EXIT,		ExitFunction,

	IDM_SETTINGS,	OptionsFunction,
	IDM_KEYS,		KeyFunction,
	IDM_HISCORE_MENU,ShowHiscoreFunction,
	IDM_HIGHDET,	DetailFunction,
	IDM_MEDIUMDET,	DetailFunction,
	IDM_LOWDET,		DetailFunction,
	IDM_BACKGRND,	BackgrndFunction,
	IDM_FRAME,		FrameFunction,
	IDM_SAVEONEXIT,	SaveOnExitFunction,

	IDM_LANG_EN,	LanguageFunction,
	IDM_LANG_ES,	LanguageFunction,
	IDM_LANG_NL,	LanguageFunction,
	IDM_LANG_DE,	LanguageFunction,
	IDM_LANG_FR,	LanguageFunction,
	IDM_LANG_IT,	LanguageFunction,

	IDM_HELPUSING,	HelpForHelp,
	IDM_HELPCONTENTS,	HelpContents,
	IDM_HELPINDEX,	HelpIndex,
	IDM_HELPHOWTOPLAY,	HelpHowToPlay,
	IDM_HELPKEYS,	HelpKeys,
	IDM_ABOUT_MENU,	AboutFunction,

	IDF_TEST,		EmptyFunction,
	0,NULL
};



void MessageHandler(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2 )
{
	ULONG	i,id,idList;


	i  = 0;
	id = SHORT1FROMMP(mp1);		// Get ID of selected Object

	// Scan CommandList for Id and call associated Function
	// if available

	while((idList=Commands[i].idl_Id) != 0)
	{
		if(idList == id)
		{
			Commands[i].idl_Function(hwnd,msg,mp1,mp2);
			break;
		}
		i++;
	};
}


/*******************************************************************************
* SetActionMenus(on)
* Enable (on = TRUE) or disable (on = FALSE) the Pause and Quit Game menu
* items depending on the game state.
*******************************************************************************/

void SetActionMenus( BOOL on )
{
	HWND	hwndMenu;


	hwndMenu = WinWindowFromID( hwndFrame, FID_MENU );
	if( hwndMenu == NULLHANDLE )
		return;

	WinEnableMenuItem(hwndMenu, IDM_PAUSE, on);
	WinEnableMenuItem(hwndMenu, IDM_QUIT,  on);
}


/*******************************************************************************
* SetDetailMenu()
* Bring the check marks of the Detail menu in line with the current
* detaillevel.
*******************************************************************************/

void SetDetailMenu(void)
{
	HWND	hwndMenu;


	hwndMenu = WinWindowFromID( hwndFrame, FID_MENU );
	if( hwndMenu == NULLHANDLE )
		return;

	WinCheckMenuItem(hwndMenu, IDM_HIGHDET,   STrisPrefs.detaillevel == 0);
	WinCheckMenuItem(hwndMenu, IDM_MEDIUMDET, STrisPrefs.detaillevel == 1);
	WinCheckMenuItem(hwndMenu, IDM_LOWDET,    STrisPrefs.detaillevel == 2);
}


/*******************************************************************************
* DetailFunction(msg)
* Apply one of the three detail presets:
* High   = grid + solid colors
* Medium = grid + dithered colors  (the original look)
* Low    = no grid + dithered colors
*******************************************************************************/

static ULONG DetailFunction(HWND hwnd,ULONG msg,MPARAM mp1, MPARAM mp2)
{
	ULONG	id;
	HPS		hps;


	id = SHORT1FROMMP(mp1);

	if( id == IDM_HIGHDET )
		STrisPrefs.detaillevel = 0;
	else if( id == IDM_MEDIUMDET )
		STrisPrefs.detaillevel = 1;
	else if( id == IDM_LOWDET )
		STrisPrefs.detaillevel = 2;
	else
		return TRUE;

	switch( STrisPrefs.detaillevel )
	{
		case 0:
			STrisPrefs.fGridFlag   = TRUE;
			STrisPrefs.fSolidColor = TRUE;
			break;

		case 1:
			STrisPrefs.fGridFlag   = TRUE;
			STrisPrefs.fSolidColor = FALSE;
			break;

		default:
			STrisPrefs.fGridFlag   = FALSE;
			STrisPrefs.fSolidColor = FALSE;
			break;
	}

	GeneratePieces();

	hps = WinGetPS(hwndClient);
	PaintPlayField(hps);
	DrawPiece(hps);
	PaintNextPiece(hps);
	WinReleasePS(hps);

	SetDetailMenu();

	return TRUE;
}


/*******************************************************************************
* BackgrndFunction(msg)
* Toggle BackgroundRun: when on, the game keeps running while the window
* does not have the focus.
*******************************************************************************/

static ULONG BackgrndFunction(HWND hwnd,ULONG msg,MPARAM mp1, MPARAM mp2)
{
	HWND	hwndMenu;


	STrisPrefs.BackgroundRun = STrisPrefs.BackgroundRun ? 0 : 1;

	hwndMenu = WinWindowFromID( hwndFrame, FID_MENU );
	WinCheckMenuItem(hwndMenu, IDM_BACKGRND, STrisPrefs.BackgroundRun);

	return TRUE;
}


/*******************************************************************************
* FrameFunction(msg)
* Hide or show the frame controls (title bar, system menu, min/max buttons,
* menu bar) while playing.
*******************************************************************************/

static ULONG FrameFunction(HWND hwnd,ULONG msg,MPARAM mp1, MPARAM mp2)
{
	HWND	hwndFrame,
			hwndMenu;
	RECTL	rect;
	ULONG	flChange = FCF_TITLEBAR | FCF_SYSMENU | FCF_MINMAX | FCF_MENU;


	/* hwnd is the client window; get the frame and the menu handle first,
	   the menu window disappears from the frame's child list on hiding */

	hwndFrame = WinQueryWindow( hwnd, QW_PARENT );
	hwndMenu  = WinWindowFromID( hwndFrame, FID_MENU );

	if( bFrameHidden )			// show the frame controls again
	{
		WinSetParent( WinWindowFromID( hwndFrame, FID_TITLEBAR ), hwndFrame, FALSE );
		WinSetParent( WinWindowFromID( hwndFrame, FID_SYSMENU ),  hwndFrame, FALSE );
		WinSetParent( WinWindowFromID( hwndFrame, FID_MINMAX ),   hwndFrame, FALSE );
		WinSetParent( WinWindowFromID( hwndFrame, FID_MENU ),     hwndFrame, FALSE );
	}
	else						// hide the frame controls
	{
		WinSetParent( WinWindowFromID( hwndFrame, FID_TITLEBAR ), HWND_OBJECT, FALSE );
		WinSetParent( WinWindowFromID( hwndFrame, FID_SYSMENU ),  HWND_OBJECT, FALSE );
		WinSetParent( WinWindowFromID( hwndFrame, FID_MINMAX ),   HWND_OBJECT, FALSE );
		WinSetParent( WinWindowFromID( hwndFrame, FID_MENU ),     HWND_OBJECT, FALSE );
	}

	bFrameHidden = !bFrameHidden;

	WinSendMsg( hwndFrame, WM_UPDATEFRAME, MPFROMLONG(flChange), 0 );

	/* Re-size the frame so the client keeps its content size */
	WinQueryWindowRect( hwnd, &rect );
	WinCalcFrameRect(hwndFrame, &rect, FALSE);
	WinSetWindowPos( hwndFrame, HWND_TOP, 0, 0,
					 rect.xRight-rect.xLeft, rect.yTop-rect.yBottom, SWP_SIZE );

	WinCheckMenuItem(hwndMenu, IDM_FRAME, bFrameHidden);

	return TRUE;
}


/*******************************************************************************
* SaveOnExitFunction(msg)
* Toggle saveonexit: whether the settings are written to 'STris.cfg' when
* the program ends.
*******************************************************************************/

static ULONG SaveOnExitFunction(HWND hwnd,ULONG msg,MPARAM mp1, MPARAM mp2)
{
	HWND	hwndMenu;


	STrisPrefs.saveonexit = STrisPrefs.saveonexit ? 0 : 1;

	hwndMenu = WinWindowFromID( hwndFrame, FID_MENU );
	WinCheckMenuItem(hwndMenu, IDM_SAVEONEXIT, STrisPrefs.saveonexit);

	return TRUE;
}


/*******************************************************************************
* LanguageFunction(msg)
* Switch the user interface (and the help library) to the selected language.
*******************************************************************************/

static ULONG LanguageFunction(HWND hwnd,ULONG msg,MPARAM mp1, MPARAM mp2)
{
	ULONG	id;
	int		lang;


	id   = SHORT1FROMMP(mp1);
	lang = id - IDM_LANG_EN;		// IDM_LANG_EN .. IDM_LANG_IT

	if( lang < 0 || lang >= LANG_COUNT )
		lang = LANG_EN;

	set_language( WinWindowFromID( hwndFrame, FID_MENU ), lang );

	STrisPrefs.current_lang = lang;

	return TRUE;
}



MRESULT EXPENTRY ClientWndProc( HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2 )
{
	HPS 		hps;
	SWP 		swp;
	ULONG		state;
	SHORT		key;


	switch(msg)
	{
		case WM_PAINT:
			{
				RECTL rclPaint;
				BOOL  fInside;

				hps = WinBeginPaint( hwnd, NULLHANDLE, &rclPaint );
				GpiSetBackMix( hps, BM_OVERPAINT );
				GpiSetBackColor( hps, CLR_WHITE );

				/* A paint that only touches the playfield (falling piece) needs no
				   erase: every cell is overpainted. Erasing first caused flicker. */
				fInside = rclPaint.xLeft >= pfLeft-1 && rclPaint.xRight <= pfRight+2 &&
						  rclPaint.yBottom >= pfBottom-1 && rclPaint.yTop <= pfBottom+pfHeight+2;
				if( !fInside )	GpiErase( hps );

				fSkipActivePiece = TRUE;
				PaintPlayField( hps );
				fSkipActivePiece = FALSE;
			}
			DrawPiece( hps );
			PaintNextPiece( hps );
			PaintBitmap( hps );
			UpdateTextBlock( hps, PRT_UPDATE_ALL );

			/* Draw playfield and next-piece borders */
			{
				POINTL ptl;
				GpiSetColor( hps, CLR_BLACK );
				ptl.x = pfLeft-1;       ptl.y = pfBottom-1;
				GpiMove( hps, &ptl );
				ptl.x = pfRight+1;      ptl.y = pfBottom+pfHeight+1;
				GpiBox( hps, DRO_OUTLINE, &ptl, 0, 0 );

				ptl.x = npLeft-1;       ptl.y = npTop-1;
				GpiMove( hps, &ptl );
				ptl.x = npLeft+npWidth+1; ptl.y = npTop+npHeight+1;
				GpiBox( hps, DRO_OUTLINE, &ptl, 0, 0 );
			}

			WinEndPaint( hps );
			return 0;


		case WM_CONTROL:
		case WM_COMMAND:

			MessageHandler(hwnd,msg,mp1,mp2);
			return 0;


		case WM_CHAR:

			state = CHARMSG(&msg)->fs;
			if( state & KC_KEYUP )	return 0;

			key = 0;

			if( state & KC_CHAR )			key = CHARMSG(&msg)->chr;
			if( state & KC_VIRTUALKEY ) 	key = CHARMSG(&msg)->vkey;

			if( Pause && STrisPrefs.fRemainPaused )
			{
				SetPause( FALSE );
				if( key == VK_PAUSE )	key = 0;
			}

			if( OnGame && !Pause )
				HandleKeys( key );

			return 0;


		case WM_TIMER:

			if( OnGame && !Pause )
			{
				FallPiece(hwnd);
			}
			return 0;


		case WM_ACTIVATE:					// If we lose the Focus we go to
			if( mp1 )						// pause mode (unless BackgroundRun)
			{
				/* Don't break pause if RemainPaused-Flag is set */
				if( OnGame && !STrisPrefs.fRemainPaused )
					SetPause( fPaused );

				AcquireAudioDevice(hwnd,msg,mp1,mp2);
			}
			else
			{
				fPaused = Pause; 			// Remember pause state
				if( OnGame && !STrisPrefs.BackgroundRun && !Pause )
					SetPause( TRUE ); 		// Go on Pause-Mode
			}
			break;

		case MM_MCINOTIFY:
			MusicNotifyProc(hwnd,msg,mp1,mp2);
			return 0;

		case MM_MCIPASSDEVICE:
			PassDeviceProc(hwnd,msg,mp1,mp2);
			return 0;

		case WM_DESTROY:

			WinQueryWindowPos(hwndFrame,&swp);
			STrisPrefs.win_rcl.xLeft	= swp.x;
			STrisPrefs.win_rcl.yBottom	= swp.y;
			WinCalcFrameRect(hwndFrame,&STrisPrefs.win_rcl,TRUE);

			return 0;
	}

	return WinDefWindowProc( hwnd, msg, mp1, mp2 );
}
