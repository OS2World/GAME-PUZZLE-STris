/*******************************************************************************
*																			   *
* REGISTRATION.C															   *
* --------------															   *
*																			   *
* Alle Routinen die fuer die Registrierung verantwortlich sind				   *
*																			   *
* Modification History: 													   *
* --------------------- 													   *
*																			   *
* 24.03.96	RHS  Created this file											   *
*																			   *
********************************************************************************/
#define INCL_WIN
#include <os2.h>
#include <string.h>

#include "registration.h"
#include "preferences.h"
#include "window.h"
#include "stris.h"
#include "stub.h"
#include "crc.h"

#include "stris_id.h"



/*** Defines ******************************************************************/

#define DELAY_TIME			15

#define ID_ENABLE_TIMER 	2


/*** Prototypes ***************************************************************/


/*** Variables ****************************************************************/

static	struct	PrefsStruct 	LocalPrefs;

static	BYTE	sCodeTab[] =		// 16 moegliche Woerter codieren
										// z.B. in HEX-Code
//	{ '0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F' };
	{ 'C','E','O','F','K','L','A','P','R','Q','B','M','X','D','U','N' };

static	BYTE	sDecodeTab[256];	// Gegenstueck zu oben
static	BOOL	fContinue;





/*** Functions *****************************************************************/

void CreateCodeTab(void)
{
	ULONG	i;


	for(i=0;i<256;i++)
		sDecodeTab[i] = -1;


	for(i=0;i<16;i++)
		sDecodeTab[sCodeTab[i]] = i;

}



/**************************************************************************
* DeCode(pszName)
* Aus dem Code den Usernamen extrahieren und auf Korrektheit pruefen
* pszCode	: Codestring
* Return	: none
**************************************************************************/

static BOOL DeCode(char *pszCode)
{
	ULONG	lLen,lLenHalf,
			i,j;
	BYTE	bCRC,
			bCRCStored,
			bHighNibble,
			bLowNibble;
	char	szInterleave[32+4],
			*pszTarget;




	/* Assume code is not valid. Change this assumption if code OK. */
	strcpy(STrisPrefs.szUsername,"not registered");


	/* Build DecodeTab for later use */
	CreateCodeTab();

	lLen	 = strlen(pszCode);
	lLenHalf = lLen/2-1;

	/* Check for too short code */
	if(lLen<4)
		return FALSE;

	j = 0;
	for(i=0;i<lLen;i+=2)
	{
		/* Check for invalid character in code */
		bHighNibble = sDecodeTab[ pszCode[i] ];
		bLowNibble	= sDecodeTab[ pszCode[i+1] ];
		if( bHighNibble == (BYTE)-1 || bLowNibble == (BYTE)-1 )
			return FALSE;

		szInterleave[j++] = (bHighNibble<<4) + bLowNibble;
	}

	bCRCStored = szInterleave[lLenHalf];
	szInterleave[lLenHalf] = 0;
	bCRC = GenerateCRC(szInterleave);

//	Message("Stored %lx\nComputed %lx",(ULONG)bCRCStored,(ULONG)bCRC);

	if( bCRC != bCRCStored )
	{
		// Code not valid
#if 0
		Message("ASCII Hex : %s\n"
			"Interleaved : %s\n"
			"Name : %s",
			pszCode,szInterleave,STrisPrefs.szUsername );
#endif
		return FALSE;
	}

	// Alles OK. Namen entcoden
	pszTarget = STrisPrefs.szUsername;

	lLen	 = strlen(szInterleave);
	lLenHalf = (lLen+1)/2;

	/* Interleave Name (odd bytes first then even bytes) */
	for(i=0;i<lLenHalf;i++)
	{
		pszTarget[i]		  = szInterleave[i*2];
		pszTarget[i+lLenHalf] = szInterleave[i*2+1];
	}

	pszTarget[lLen] = 0;

#if 0
	Message("ASCII Hex : %s\n"
		"Interleaved : %s\n"
		"Name : %s",
		pszCode,szInterleave,STrisPrefs.szUsername );
#endif
	return TRUE;
}



/**************************************************************************
* Code(pszName)
* Aus Usernamen einen Code erzeugen der hoffentlich einmalig ist.
* pszName	: Name
* Return	: Zeiger auf codierten String
**************************************************************************/

static void Code(char *pszName)
{
	ULONG	lLen,lLenHalf,
			i;
	BYTE	bCRC;
	char	szInterleave[32+4],
			*pszTarget;



	pszTarget = STrisPrefs.szRegistration;

	/* Interleave Name (odd bytes first then even bytes) */
	lLen	 = strlen(pszName);
	lLenHalf = (lLen+1)/2;

	if( lLen >= 31 )
	{
		Message("Sorry but name must be shorter than 31 chars");
		strncpy(pszTarget,pszName,30);
		pszTarget[30] = 0;
		return;
	}


//	pszName[lLen+1] = 0;			// Add 0 to fill up

	/* Interleave Name (odd bytes first then even bytes) */
	for(i=0;i<lLenHalf;i++)
	{
		szInterleave[i*2]	= pszName[i];
		szInterleave[i*2+1] = pszName[i+lLenHalf];
	}

	szInterleave[lLen] = 0; 		// End String


	/* Add CRC at the end of the interleaved name */
	bCRC = GenerateCRC(szInterleave);
	szInterleave[lLen]	 = bCRC;
	szInterleave[lLen+1] = 0;


	/* Create a solid AsciiString containing only	*/
	/* Hex-Codes (or something else)				*/
	for(i=0;i<lLen+1;i++)
	{
		pszTarget[i*2]	 = sCodeTab[ szInterleave[i]>>4 & 0x0F ];
		pszTarget[i*2+1] = sCodeTab[ szInterleave[i]	& 0x0F ];
	}
	pszTarget[i*2] = 0;

#if 0
	Message("Input : %s\n"
			"Interleaved : %s\n"
			"Code : %s\n",
			pszName,szInterleave,
			STrisPrefs.szRegistration);
#endif
}



/*******************************************************************************
* Message Handler for RegRequester
* Called by the Dialogmanager
*******************************************************************************/

MRESULT EXPENTRY RegDlgProc( HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2 )
{
	HWND	hwndEntry;
	char	szCode[32+4];


	switch( msg )
	{
		case WM_INITDLG:

			hwndEntry = WinWindowFromID(hwnd,IDD_PRGTITEL);
			WinSetWindowText( hwndEntry,
							   PRG_NAME " " VERSION "." REVISION
							   " by Ren‚ Straub (" DATE ")" );

#ifdef CODE_PRG
			WinShowWindow(WinWindowFromID(hwnd,PB_CODE),TRUE);
#endif

			// Place Window
			RestoreWindowPos( hwnd, &STrisPrefs.reg_rcl );
			return 0;


		case WM_COMMAND:
			switch( COMMANDMSG(&msg)->cmd)
			{
				/* INTERNAL 							*/
				/* Code erzeugen						*/
				case PB_CODE:
					WinQueryDlgItemText(hwnd, IDD_REGNAME,
										sizeof(szCode),szCode);
					Code(szCode);
					WinSetDlgItemText(hwnd,IDD_REGNAME,STrisPrefs.szRegistration);

					break;


				case DID_CANCEL:

					WinDismissDlg(hwnd,FALSE);
					break;


				case DID_OK:
					WinQueryDlgItemText(hwnd, IDD_REGNAME,
										sizeof(STrisPrefs.szRegistration),
										STrisPrefs.szRegistration);

					if( !DeCode(STrisPrefs.szRegistration) )
					{
						Message("This is no valid code.\n"
								"Please try again.");

						WinSetFocus(HWND_DESKTOP,
							WinWindowFromID(hwnd,IDD_REGNAME) );
					}
					else
					{
						Message("STris has been succesfully registered "
								"to %s",STrisPrefs.szUsername);
						WinDismissDlg(hwnd,TRUE);
					}

					break;

			}

			return 0;


		case WM_DESTROY:

			StoreWindowPos(hwnd,&STrisPrefs.reg_rcl);
			return 0;
	}

	return WinDefDlgProc( hwnd, msg, mp1, mp2 );
}



/*******************************************************************************
* RegFunction()
* Dialog zur Registrierung
*******************************************************************************/

ULONG RegFunction(HWND hwnd,ULONG msg,MPARAM mp1, MPARAM mp2)
{
	LocalPrefs = STrisPrefs;

	if( !WinDlgBox( HWND_DESKTOP, hwnd, RegDlgProc, NULLHANDLE, DLG_REGISTRATION, NULL ) )
	{
		/* Cancelled -> Undo all changes */
		STrisPrefs = LocalPrefs;
	}

	return TRUE;
}






MRESULT EXPENTRY NervDlgProc( HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2 )
{
	HWND	hwndEntry;


	switch( msg )
	{
		case WM_INITDLG:

			hwndEntry = WinWindowFromID(hwnd,IDD_PRGTITEL);
			WinSetWindowText( hwndEntry,
							 "Welcome to " PRG_NAME " " VERSION "." REVISION );

			fContinue = TRUE;

			if( WinStartTimer(hab,hwnd,ID_ENABLE_TIMER,DELAY_TIME*1000) )
			{
				WinEnableWindow(WinWindowFromID(hwnd,DID_OK),FALSE);
				fContinue = FALSE;
			}

			RestoreWindowPos(hwnd, &STrisPrefs.nerv_rcl);

			return 0;


		case WM_COMMAND:
			switch( COMMANDMSG(&msg)->cmd)
			{
				case DID_OK:
					WinDismissDlg( hwnd, TRUE );
					return 0;
			}

			return 0;


		case WM_TIMER:

			WinStopTimer(hab,hwnd,ID_ENABLE_TIMER);
			WinEnableWindow(WinWindowFromID(hwnd,DID_OK),TRUE);
			break;


		case WM_DESTROY:

			StoreWindowPos(hwnd, &STrisPrefs.nerv_rcl);
			return 0;
	}

	return WinDefDlgProc( hwnd, msg, mp1, mp2 );
}


/*******************************************************************************
* NervFunction()
* Nerv-Requester fuer unregistrierte Versionen
*******************************************************************************/

void CheckRegistration(HWND hwnd)
{
	if( !DeCode( STrisPrefs.szRegistration ) )
	{
		WinDlgBox( HWND_DESKTOP, hwnd, NervDlgProc,
					NULLHANDLE, DLG_UNREGISTERED,NULL );
	}
}


