/*******************************************************************************
*																			   *
* HISC_WINDOW.C 															   *
* ------------- 															   *
*																			   *
* Asks for Username and displays Hiscorelist								   *
*																			   *
* Modification History: 													   *
* --------------------- 													   *
*																			   *
* 15.04.95	RHS  Created this file											   *
* 22.04.95	RHS  Window positions are saved 								   *
* 09.09.95	RHS  Optical Restyling, Hilite current position 				   *
*																			   *
*******************************************************************************/

#define INCL_WIN

#include <os2.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hiscwindow.h"
#include "stris.h"
#include "window.h"
#include "hiscore.h"
#include "stub.h"
#include "preferences.h"

#include "stris_id.h"


/*** Defines ******************************************************************/

struct InitData
{
	SHORT	usSize;
	ULONG	ulEntry;
};

/*** Prototypes ***************************************************************/

/*** Variables ****************************************************************/

static	struct	InitData	aInitData;
static	char				szHiscoreName[name_len+4];


/*** Functions ****************************************************************/



/*******************************************************************************
* Message Handler for EnterNameRequester
* Called by the Dialogmanager
*******************************************************************************/

MRESULT EXPENTRY EnterNameDlgProc( HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2 )
{
	switch( msg )
	{
		case WM_INITDLG:

			szHiscoreName[0] = 0;
			WinSendDlgItemMsg( hwnd, IDD_TEXT_FIELD, EM_SETTEXTLIMIT,
								MPFROM2SHORT(name_len,0),NULL );

			// Place Window
			RestoreWindowPos(hwnd,&STrisPrefs.ent_rcl);

			WinSetFocus(HWND_DESKTOP,WinWindowFromID(hwnd,IDD_TEXT_FIELD) );
			return MPFROMSHORT(1);


		case WM_COMMAND:
			switch( COMMANDMSG(&msg)->cmd)
			{
				case DID_OK:
					WinQueryDlgItemText(hwnd, IDD_TEXT_FIELD,
										sizeof(szHiscoreName)-4,szHiscoreName);

					if( strlen( szHiscoreName ) > 0 )
						WinDismissDlg( hwnd, TRUE );
					else
						WinSetFocus(HWND_DESKTOP,WinWindowFromID(hwnd,IDD_TEXT_FIELD) );

					return 0;
			}
			break;


		case WM_DESTROY:

			StoreWindowPos(hwnd,&STrisPrefs.ent_rcl);
			return 0;

	}

	return WinDefDlgProc( hwnd, msg, mp1, mp2 );
}


/*******************************************************************************
* name=GetUserName()
* Open dialog and let user enter his name.
* name = Pointer to Username
*******************************************************************************/

char *GetUserName(void)
{
	WinDlgBox( HWND_DESKTOP, hwndClient, EnterNameDlgProc,
				NULLHANDLE, DLG_ENTERNAME, NULL );

	return szHiscoreName;
}



/*******************************************************************************
* Message Handler for ShowHiscoreRequester
* Called by the Dialogmanager
*******************************************************************************/

MRESULT EXPENTRY ShowHiscoreDlgProc( HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2 )
{
	HWND					hwndEntry;
	HPS 					hps;
	struct	Player_Entry	*entry;
	struct	InitData		*pInitData;
	ULONG					ulColor;
	LONG					i;
	char					szStr[16];

	switch( msg )
	{
		case WM_INITDLG:
#if 1
			for(i=0;i<max_entries;i++)
			{
				entry = GetEntry(i);

				WinSetDlgItemText(hwnd,IDD_NAME1+i,entry->Name );
				sprintf(szStr,"%ld",entry->Score );
				WinSetDlgItemText(hwnd,IDD_SCORE1+i,szStr );
				sprintf(szStr,"%3ld",entry->Lines );
				WinSetDlgItemText(hwnd,IDD_LINES1+i,szStr );
				sprintf(szStr,"%3ld",entry->Level );
				WinSetDlgItemText(hwnd,IDD_LEVEL1+i,szStr );
			}
#endif

			if( mp2 )
			{
				pInitData = mp2;
				ulColor = CLR_RED;

				hwndEntry = WinWindowFromID(hwnd,IDD_RANK1-1+pInitData->ulEntry);
				WinSetPresParam(hwndEntry, PP_FOREGROUNDCOLORINDEX,
				   (ULONG)sizeof(LONG), (PVOID)&ulColor);

				hwndEntry = WinWindowFromID(hwnd,IDD_NAME1-1+pInitData->ulEntry);
				WinSetPresParam(hwndEntry, PP_FOREGROUNDCOLORINDEX,
				   (ULONG)sizeof(LONG), (PVOID)&ulColor);

				hwndEntry = WinWindowFromID(hwnd,IDD_SCORE1-1+pInitData->ulEntry);
				WinSetPresParam(hwndEntry, PP_FOREGROUNDCOLORINDEX,
				   (ULONG)sizeof(LONG), (PVOID)&ulColor);

				hwndEntry = WinWindowFromID(hwnd,IDD_LINES1-1+pInitData->ulEntry);
				WinSetPresParam(hwndEntry, PP_FOREGROUNDCOLORINDEX,
				   (ULONG)sizeof(LONG), (PVOID)&ulColor);

				hwndEntry = WinWindowFromID(hwnd,IDD_LEVEL1-1+pInitData->ulEntry);
				WinSetPresParam(hwndEntry, PP_FOREGROUNDCOLORINDEX,
				   (ULONG)sizeof(LONG), (PVOID)&ulColor);
			}

			// Place Window
			RestoreWindowPos(hwnd,&STrisPrefs.hsc_rcl);

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

			StoreWindowPos(hwnd,&STrisPrefs.hsc_rcl);
			return 0;
	}

	return WinDefDlgProc( hwnd, msg, mp1, mp2 );
}


/*******************************************************************************
* ShowHiscoreFunction()
* Show Hiscore Dialog.
* Parameters = unused
*******************************************************************************/

ULONG ShowHiscoreFunction(HWND hwnd,ULONG msg,MPARAM mp1, MPARAM mp2)
{
	WinDlgBox( HWND_DESKTOP, hwndClient, ShowHiscoreDlgProc,
				NULLHANDLE, DLG_SHOWHISCORE, NULL );

	return TRUE;
}

ULONG ShowHiscoreFunctionHilite(HWND hwnd, ULONG ulEntry)
{
	aInitData.usSize  = sizeof(aInitData);
	aInitData.ulEntry = ulEntry;


	WinDlgBox( HWND_DESKTOP, hwndClient, ShowHiscoreDlgProc,
				NULLHANDLE, DLG_SHOWHISCORE, &aInitData );
	return TRUE;
}




