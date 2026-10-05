/*******************************************************************************
*																			   *
* ABOUT.C																	   *
* -------																	   *
*																			   *
* About Requester															   *
*																			   *
* Modification History: 													   *
* --------------------- 													   *
*																			   *
* 14.04.95	RHS  Extracted this file from STris.c							   *
* 22.04.95	RHS  Little rebuild (optical), Window positions are saved		   *
* 08.09.95	RHS  Optical restyling											   *
*																			   *
********************************************************************************/

#define INCL_WIN
#include <os2.h>
#include <string.h>

#include "about.h"
#include "stris.h"
#include "window.h"
#include "preferences.h"
#include "registration.h"

#include "stris_id.h"



/*** Defines ******************************************************************/

/*** Prototypes ***************************************************************/

/*** Variables ****************************************************************/


/*******************************************************************************
* Message Handler for AboutRequester
* Called by the Dialogmanager
*******************************************************************************/

MRESULT EXPENTRY AboutDlgProc( HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2 )
{
	HWND	hwndEntry;


	switch( msg )
	{
		case WM_INITDLG:

#if 0
			WinSetDlgItemText( hwnd, IDD_PRGTITEL,
							   PRG_NAME " " VERSION "." REVISION
							   " by Ren‚ Straub (" DATE ")" );
#endif
			WinSetDlgItemText( hwnd, IDD_PRGTITEL,
							   PRG_NAME " " VERSION "." REVISION
							   " by Ren‚ Straub" );

			WinSetDlgItemText( hwnd, IDD_USERNAME,
								STrisPrefs.szUsername);

			// Place Window
			RestoreWindowPos( hwnd, &STrisPrefs.abt_rcl );
			return 0;


		case WM_COMMAND:
			switch( COMMANDMSG(&msg)->cmd)
			{
				case PB_REGISTER:
					RegFunction(hwnd,0,0,0);
					WinSetDlgItemText( hwnd, IDD_USERNAME,
										STrisPrefs.szUsername);
					break;

				case DID_OK:
					WinDismissDlg( hwnd, TRUE );
					return 0;
			}

			return 0;


		case WM_DESTROY:

			StoreWindowPos( hwnd, &STrisPrefs.abt_rcl );
			return 0;
	}

	return WinDefDlgProc( hwnd, msg, mp1, mp2 );
}


/*******************************************************************************
* AboutFunction()
* Display the Aboutrequester
*******************************************************************************/

ULONG AboutFunction(HWND hwnd,ULONG msg,MPARAM mp1, MPARAM mp2)
{
	WinDlgBox( HWND_DESKTOP, hwnd, AboutDlgProc, NULLHANDLE, DLG_ABOUT, NULL );

	return TRUE;
}


