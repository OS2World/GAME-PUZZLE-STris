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
* 2026	     OD2  Standardized (register now) about dialog, registration	   *
*                functions removed.										   *
*																			   *
********************************************************************************/

#define INCL_WIN
#include <os2.h>

#include "about.h"
#include "stris.h"
#include "window.h"
#include "preferences.h"

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
	switch( msg )
	{
		case WM_INITDLG:

			// Place Window
			RestoreWindowPos( hwnd, &STrisPrefs.abt_rcl );
			return 0;


		case WM_COMMAND:
			switch( COMMANDMSG(&msg)->cmd)
			{
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
