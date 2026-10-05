/*******************************************************************************
*																			   *
* S-Tris V1.43								 Project started  : 07.04.1995	   *
* ------------									  Last Update : 13.03.1996	   *
*																			   *
* Mein erstes PM Programm unter OS/2. Ein Ersatz fÅr all die unbrauchbaren	   *
* Tetris Versionen die es unter OS/2 gibt.									   *
*																			   *
* Author RenÇ Straub				Tel.  +41 776 26 61 					   *
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
#include "registration.h"
#include "help.h"
#include "stub.h"

#include "stris_id.h"



/*** Defines ******************************************************************/

#define NO_SAFE_QUIT		// Disable 'Quit'-Requester


/*** Prototypes ***************************************************************/


/*** Variables ****************************************************************/

		HAB 		hab;
static	HMQ 		hmq;
static	BOOL		fPaused;


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


	hab = WinInitialize(0);
	hmq = WinCreateMsgQueue(hab,0);

#ifndef CODE_PRG
	BusyPointer(TRUE);

	GetDesktopSize();
	InitRandom();
	LoadPrefs();

	OpenWindow( hab );
	OpenHelp();

	CheckRegistration( hwndClient );

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

	IDF_USINGHELP,	HelpForHelp,
	IDF_HELP,		HelpContents,
	IDF_HELPINDEX,	HelpIndex,
	IDF_HOWTOPLAY,	HelpHowToPlay,
	IDF_KEYSHELP,	HelpKeys,
	IDF_ABOUT,		AboutFunction,
	IDF_REGISTER,	RegFunction,

	IDF_TEST,		EmptyFunction,
	0,NULL
};



void MessageHandler(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2 )
{
	ULONG	i,id,idList;


	i  = 0;
	id = COMMANDMSG(&msg)->cmd; 	// Get ID of selected Object

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



MRESULT EXPENTRY ClientWndProc( HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2 )
{
	HPS 		hps;
	SWP 		swp;
	ULONG		state;
	SHORT		key;


	switch(msg)
	{
		case WM_PAINT:
			hps = WinBeginPaint( hwnd, NULLHANDLE, NULL );
			GpiErase( hps );

			PaintPlayField( hps );
			DrawPiece( hps );
			PaintNextPiece( hps );
			PaintBitmap( hps );
			UpdateTextBlock( hps, PRT_UPDATE_ALL );

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

//			if( OnGame && Pause && STrisPrefs.fRemainPaused )
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


		case WM_ACTIVATE:						// If we lose the Focus we go to
			if( mp1 )							// pause mode
			{
				/* Don't break pause if RemainPaused-Flag is set */
				if( !(OnGame && STrisPrefs.fRemainPaused) )
					SetPause( fPaused );

				AcquireAudioDevice(hwnd,msg,mp1,mp2);
			}
			else
			{
				fPaused = SetPause( TRUE ); 	// Go on Pause-Mode
			}
			break;
//			return( WinDefWindowProc( hwnd, msg, mp1, mp2 ) );
//			return 0;

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



