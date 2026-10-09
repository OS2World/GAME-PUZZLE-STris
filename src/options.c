/*******************************************************************************
*																			   *
* OPTIONS.C 																   *
* --------- 																   *
*																			   *
* Options Requester 														   *
*																			   *
* Modification History: 													   *
* --------------------- 													   *
*																			   *
* 14.04.95	RHS  Extracted this file from STris.c							   *
* 20.04.95	RHS  Dialog nearly finished (added Sliders) 					   *
* 22.04.95	RHS  Window positions are saved 								   *
* 28.04.95	RHS  Spinbutton for Palette added. Changes are now shown online    *
* 10.05.95	RHS  Added Rotateflag for Counterclockwise rotation of piece	   *
* 02.06.95	RHS  Modifications for new Prefshandling						   *
*				 Removed bug concerning locking of palette-gadget			   *
* 21.07.95	RHS  Fixed writing-bug (green to yellow)						   *
* 15.09.95	RHS  Corrected Slider keyboard control, redesign for dialog 	   *
* 24.09.95	RHS  ReCorrected slider control 								   *
* 13.03.96	RHS  RemainPaused Flag implemented								   *
*																			   *
*******************************************************************************/
#define INCL_WIN
#include <os2.h>
#include <stdlib.h>
#include <stdio.h>

#include "options.h"
#include "stris.h"
#include "playfield.h"
#include "pieces.h"
#include "window.h"
#include "sound.h"
#include "preferences.h"
#include "lang.h"

#include "stris_id.h"
#include "help.h"


/*** Defines ******************************************************************/

/*** Prototypes ***************************************************************/

/*** Variables ****************************************************************/

static	struct	PrefsStruct 	LocalPrefs;

static	HWND	hwndSpeedSlider,hwndSpeedText,
				hwndLevelSlider,hwndLevelText,
				hwndPalette;

static	BOOL	Lock;

static	char	*PaletteNames[6];



/*******************************************************************************
* Message Handler for AboutRequester
* Called by the Dialogmanager
*******************************************************************************/

MRESULT EXPENTRY OptionsDlgProc( HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2 )
{
	HPS 	hps;
	USHORT	state;
	char	str[32];


	switch( msg )
	{
		case WM_INITDLG:

			LocalPrefs		= STrisPrefs;		// Save prefs for 'cancel' action

			hwndLevelSlider = WinWindowFromID( hwnd, IDD_LEVELSLIDER );
			hwndLevelText	= WinWindowFromID( hwnd, IDD_LEVELTEXT );
			hwndSpeedSlider = WinWindowFromID( hwnd, IDD_SPEEDSLIDER );
			hwndSpeedText	= WinWindowFromID( hwnd, IDD_SPEEDTEXT );
			hwndPalette 	= WinWindowFromID( hwnd, IDD_PALETTE );

			/* Localized dialog texts */
			WinSetWindowText( hwnd, tr(STR_DLG_OPTIONS) );
			WinSetDlgItemText( hwnd, GB_SETTINGS,     tr(STR_OPT_SETTINGS) );
			WinSetDlgItemText( hwnd, GB_DIFFICULTY,   tr(STR_OPT_DIFFICULTY) );
			WinSetDlgItemText( hwnd, IDD_SOUND,       tr(STR_OPT_SOUND) );
			WinSetDlgItemText( hwnd, IDD_GRID,        tr(STR_OPT_GRID) );
			WinSetDlgItemText( hwnd, IDD_NEXTPIECE,   tr(STR_OPT_NEXTPIECE) );
			WinSetDlgItemText( hwnd, IDD_ROTATE,      tr(STR_OPT_ROTATE) );
			WinSetDlgItemText( hwnd, IDD_REMAINPAUSED,tr(STR_OPT_REMAINPAUSED) );
			WinSetDlgItemText( hwnd, IDD_SOLID,       tr(STR_OPT_SOLID) );
			WinSetDlgItemText( hwnd, IDD_EXTRASQUARES, tr(STR_OPT_EXTRA) );
			WinSetDlgItemText( hwnd, DLG_PALETTE,     tr(STR_OPT_PALETTE) );
			WinSetDlgItemText( hwnd, DLG_SPEED,       tr(STR_OPT_SPEED) );
			WinSetDlgItemText( hwnd, DLG_STARTLEVEL,  tr(STR_OPT_STARTLEVEL) );

			WinCheckButton(hwnd,IDD_GRID,STrisPrefs.fGridFlag);
			WinCheckButton(hwnd,IDD_NEXTPIECE,STrisPrefs.fShowNextPiece);

			if( GetAudioState() )
				WinCheckButton(hwnd,IDD_SOUND,GetMusicState()); 				// Set MusicState ON/OFF
			else
				WinEnableWindow( WinWindowFromID( hwnd, IDD_SOUND ), FALSE );	// No AudioDevice

			WinCheckButton(hwnd,IDD_ROTATE,STrisPrefs.fRotateFlag);
			WinCheckButton(hwnd,IDD_REMAINPAUSED,STrisPrefs.fRemainPaused);
			WinCheckButton(hwnd,IDD_SOLID,STrisPrefs.fSolidColor);
			WinCheckButton(hwnd,IDD_EXTRASQUARES,STrisPrefs.fExtraSquares);

			sprintf(str,"%ld",STrisPrefs.StartLevel );
			WinSetWindowText( hwndLevelText,str );
			WinSendMsg( hwndLevelSlider,SBM_SETPOS,MPFROM2SHORT(STrisPrefs.StartLevel,0), NULL );
			WinSendMsg( hwndLevelSlider,SBM_SETSCROLLBAR,MPFROM2SHORT(STrisPrefs.StartLevel,0),
						MPFROM2SHORT(0,MAX_LEVEL) );

			sprintf(str,"%ld",STrisPrefs.StartSpeed );
			WinSetWindowText( hwndSpeedText,str );
			WinSendMsg( hwndSpeedSlider,SBM_SETPOS,MPFROM2SHORT(STrisPrefs.StartSpeed,0), NULL );
			WinSendMsg( hwndSpeedSlider,SBM_SETSCROLLBAR,MPFROM2SHORT(STrisPrefs.StartSpeed,0),
						MPFROM2SHORT(0,MAX_SPEED) );


			Lock = TRUE;
			PaletteNames[0] = tr(STR_OPT_PAL1);
			PaletteNames[1] = tr(STR_OPT_PAL2);
			PaletteNames[2] = tr(STR_OPT_PAL3);
			PaletteNames[3] = tr(STR_OPT_PAL4);
			PaletteNames[4] = tr(STR_OPT_PAL5);
			PaletteNames[5] = tr(STR_OPT_PAL6);
			WinSendMsg( hwndPalette,SPBM_SETARRAY,PaletteNames,(MPARAM)6 );
			WinSendMsg( hwndPalette,SPBM_SETCURRENTVALUE,(MPARAM)STrisPrefs.Palette,0 );
			Lock = FALSE;

			// Place Window
			RestoreWindowPos(hwnd,&STrisPrefs.opt_rcl);
			return 0;



		case WM_HSCROLL:

			switch( SHORT1FROMMP( mp1 ) )
			{
				case IDD_LEVELSLIDER:

					switch( SHORT2FROMMP( mp2 ) )
					{
						case SB_LINEDOWN:
							STrisPrefs.StartLevel = min(MAX_LEVEL,STrisPrefs.StartLevel+1);
							break;

						case SB_LINEUP:
							STrisPrefs.StartLevel = max(0,STrisPrefs.StartLevel-1);
							break;

						case SB_PAGEDOWN:
							STrisPrefs.StartLevel = min(MAX_LEVEL,STrisPrefs.StartLevel+5);
							break;

						case SB_PAGEUP:
							STrisPrefs.StartLevel = max(0,STrisPrefs.StartLevel-5);
							break;

						case SB_SLIDERTRACK:
							STrisPrefs.StartLevel = SHORT1FROMMP(mp2);
							break;

						default:
							return 0;
					}

					sprintf(str,"%ld",STrisPrefs.StartLevel );
					WinSetWindowText( hwndLevelText,str );
					WinSendMsg( hwndLevelSlider,SBM_SETPOS,MPFROM2SHORT(STrisPrefs.StartLevel,0), NULL );
					break;


				case IDD_SPEEDSLIDER:

					switch( SHORT2FROMMP( mp2 ) )
					{
						case SB_LINEDOWN:
							STrisPrefs.StartSpeed = min(MAX_SPEED,STrisPrefs.StartSpeed+1);
							break;

						case SB_LINEUP:
							STrisPrefs.StartSpeed = max(0,STrisPrefs.StartSpeed-1);
							break;

						case SB_PAGEDOWN:
							STrisPrefs.StartSpeed = min(MAX_SPEED,STrisPrefs.StartSpeed+5);
							break;

						case SB_PAGEUP:
							STrisPrefs.StartSpeed = max(0,STrisPrefs.StartSpeed-5);
							break;

						case SB_SLIDERTRACK:
							STrisPrefs.StartSpeed = SHORT1FROMMP(mp2);
							break;

						default:
							return 0;
					}

					sprintf(str,"%ld",STrisPrefs.StartSpeed );
					WinSetWindowText( hwndSpeedText,str );
					WinSendMsg( hwndSpeedSlider,SBM_SETPOS,MPFROM2SHORT(STrisPrefs.StartSpeed,0), NULL );
					break;
			}

			return 0;


		case WM_CONTROL:

			switch( SHORT1FROMMP( mp1 ) )
			{
				case IDD_PALETTE:

					if( Lock )	return 0;

					if( SHORT2FROMMP( mp1 ) == SPBN_CHANGE )
					{
						WinSendMsg( hwndPalette,SPBM_QUERYVALUE,&STrisPrefs.Palette,
									MPFROM2SHORT(0,SPBQ_DONOTUPDATE) );

						GeneratePieces();
						hps = WinGetPS(hwndClient);
						PaintPlayField(hps);
						DrawPiece(hps);
						PaintNextPiece(hps);
						WinReleasePS(hps);
					}

					break;


				case IDD_GRID:

					STrisPrefs.fGridFlag = WinQueryButtonCheckstate(hwnd,IDD_GRID);
					GeneratePieces();

					hps = WinGetPS(hwndClient);
					PaintPlayField(hps);
					DrawPiece(hps);
					WinReleasePS(hps);

					break;


				case IDD_NEXTPIECE:

					STrisPrefs.fShowNextPiece = WinQueryButtonCheckstate(hwnd,IDD_NEXTPIECE);

					hps = WinGetPS(hwndClient);
					PaintNextPiece(hps);
					WinReleasePS(hps);
					break;


				case IDD_SOUND:

					state = WinQueryButtonCheckstate(hwnd,IDD_SOUND);
					SetMusicState( state );
					PlayMusic( WAV_DING );
					break;


				case IDD_ROTATE:

					STrisPrefs.fRotateFlag = WinQueryButtonCheckstate(hwnd,IDD_ROTATE);
					break;


				case IDD_REMAINPAUSED:

					STrisPrefs.fRemainPaused = WinQueryButtonCheckstate(hwnd,IDD_REMAINPAUSED);
					break;

				case IDD_EXTRASQUARES:

					STrisPrefs.fExtraSquares = WinQueryButtonCheckstate(hwnd,IDD_EXTRASQUARES);
					break;

				case IDD_SOLID:

					STrisPrefs.fSolidColor = WinQueryButtonCheckstate(hwnd,IDD_SOLID);

					GeneratePieces();
					hps = WinGetPS(hwndClient);
					PaintPlayField(hps);
					DrawPiece(hps);
					PaintNextPiece(hps);
					WinReleasePS(hps);
					break;

			}
			return 0;


		case WM_COMMAND:

			switch( COMMANDMSG(&msg)->cmd)
			{
				case DID_OK:
					WinDismissDlg( hwnd, TRUE );
					break;

				case DID_CANCEL:
					WinDismissDlg( hwnd, FALSE );
					break;
			}

			return 0;


		case WM_DESTROY:

			StoreWindowPos(hwnd,&STrisPrefs.opt_rcl);
			return 0;

	}

	return WinDefDlgProc( hwnd, msg, mp1, mp2 );
}


/*******************************************************************************
* OptionsFunction()
* Display the Aboutrequester
*******************************************************************************/

ULONG OptionsFunction(HWND hwnd,ULONG msg,MPARAM mp1, MPARAM mp2)
{
	HPS 	hps;


	if( !WinDlgBox( HWND_DESKTOP, hwnd, OptionsDlgProc, NULLHANDLE,
				   DLG_OPTIONS, NULL ) )
	{
		/* Undo all changes */

		STrisPrefs = LocalPrefs;

		hps = WinGetPS(hwndClient);
		GeneratePieces();
		PaintPlayField(hps);
		PaintNextPiece(hps);
		DrawPiece(hps);
		WinReleasePS(hps);

		SetMusicState( LocalPrefs.fSoundState );
	}

	return TRUE;
}


