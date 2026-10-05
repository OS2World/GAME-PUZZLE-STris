/*******************************************************************************
*																			   *
* STUB.C																	   *
* ------																	   *
*																			   *
* Some usefull functions that everybody needs								   *
*																			   *
* Modification History: 													   *
* --------------------- 													   *
*																			   *
* 14.04.95	RHS  Extracted this file from STris.c							   *
*																			   *
*******************************************************************************/


#define INCL_WIN
#define INCL_GPI

#include <os2.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

#include "stris.h"
#include "window.h"
#include "stub.h"


/*** Defines ******************************************************************/

/*** Prototypes ***************************************************************/

/*** Variables ****************************************************************/

		LONG		cxChar, cxCaps, cyChar, cyDesc,
					desk_width,desk_height;



/*******************************************************************************
* GetCharSize()
* H”he und Breite des Fonts ermitteln.
* hwnd	 = Clientwindow
* cxChar = mittlere Breite
* cyChar = H”he
*******************************************************************************/

void GetCharSize(HWND hwnd)
{
	FONTMETRICS fm;
	HPS 		hps;


	hps 	= WinGetPS(hwnd);
	GpiQueryFontMetrics(hps,sizeof(fm),&fm);

	cxChar	= fm.lAveCharWidth;
	cxCaps	= (fm.fsType &1 ? 2 : 3 ) * cxChar / 2;
	cyChar	= fm.lMaxBaselineExt;
	cyDesc	= fm.lMaxDescender;

	WinReleasePS(hps);
}



/*******************************************************************************
* GetDesktopSize
* Die Gr”sse des Desktops (Breite und H”he) in Pixel auslesen.
*******************************************************************************/

void GetDesktopSize(void)
{
	desk_width	= WinQuerySysValue( HWND_DESKTOP,SV_CXSCREEN);
	desk_height = WinQuerySysValue( HWND_DESKTOP,SV_CYSCREEN);
}


/*******************************************************************************
* InitRandom()
* Randomgenerator initialisieren. Als Seed wird die Systenzeit verwendet.
*******************************************************************************/

void InitRandom(void)
{
	DATETIME	date;

	DosGetDateTime(&date);
	srand(date.hundredths+date.seconds*date.weekday);
}



/*******************************************************************************
* EmptyFunction()
* Just a silly dummy-function
*******************************************************************************/

ULONG EmptyFunction(HWND hwnd,ULONG msg,MPARAM mp1, MPARAM mp2)
{
	BOOL	fOldPause;


	fOldPause = SetPause( TRUE );

	Message("Sorry, this function is not yet implemented." );
	SetPause( fOldPause );

	return TRUE;
}



/*******************************************************************************
* BusyPointer(State)
* Set/Reset BusyPointer (Hourglass)
* State : TRUE	= Busypointer On
*		  FALSE = Normal Pointer
*******************************************************************************/

void BusyPointer(BOOL state)
{
	HPOINTER	newPointer;


	if(state)
	{
		newPointer = WinQuerySysPointer(	/* This API will give the handle of the PTR. */
					  HWND_DESKTOP, 		/* Desktop window handle.					 */
					  SPTR_WAIT,			/* The Hourglass icon.						 */
					  FALSE );				/* Return the system pointer's handle.		 */
	}
	else
	{
		newPointer = WinQuerySysPointer(	/* This API will give the handle of the PTR. */
					  HWND_DESKTOP, 		/* Desktop window handle.					 */
					  SPTR_ARROW,			/* The Hourglass icon.						 */
					  FALSE );				/* Return the system pointer's handle.		 */
	}

	WinSetPointer(HWND_DESKTOP,newPointer);
}




/* Der Name sagt alles */

/*******************************************************************************
* DEBUG(txt)
* Display text on Window
* txt : Text to display
*******************************************************************************/

void DEBUG(char *szFmt,...)
{
	RECTL		rcl;
	HPS 		hps;
	va_list 	pArg;
	char		szBuffer[256];


	va_start(pArg, szFmt);
	vsprintf(szBuffer, szFmt, pArg);
	va_end(pArg);

	hps = WinGetPS(hwndClient);

	rcl.yTop	= 30;
	rcl.yBottom = 10;
	rcl.xLeft	= 10;
	rcl.xRight	= 200;

	WinDrawText( hps,strlen(szBuffer),szBuffer,&rcl,
				0,CLR_BACKGROUND,DT_ERASERECT|DT_LEFT|DT_TEXTATTRS );

	WinReleasePS( hps );
}





/*******************************************************************************
* Message(txt)
* Display Requester showing MessageText
* txt : Text to display
*******************************************************************************/

void Message( char *fmt, ... )
{
	HWND		hwnd;
	va_list 	argptr;
	char		buffer[256];


	if( hwndClient )	hwnd = hwndClient;		// Use Client Window as parent
	else				hwnd = HWND_DESKTOP;	// if available

	va_start(argptr, fmt);
	vsprintf(buffer, fmt, argptr);
	va_end(argptr);

//	WinMessageBox(HWND_DESKTOP,hwnd,buffer,FULL_NAME,0,MB_OK|MB_ERROR|MB_MOVEABLE);
	WinMessageBox(HWND_DESKTOP,hwnd,buffer,FULL_NAME,0,MB_OK|MB_QUERY|MB_MOVEABLE);
}


/*******************************************************************************
* ErrorMsg(txt)
* Display Requester showing errortext. After processing the Requester quit
* the Program with errorcode RC_ERROR.
* txt : Text to display
*******************************************************************************/

void ErrorMsg( char *fmt, ... )
{
	HWND		hwnd;
	va_list 	argptr;
	char		buffer[256];


	if( hwndClient )	hwnd = hwndClient;		// Use Client Window as parent
	else				hwnd = HWND_DESKTOP;	// if available

	va_start(argptr, fmt);
	vsprintf(buffer, fmt, argptr);
	va_end(argptr);

	WinMessageBox(HWND_DESKTOP,hwnd,buffer,FULL_NAME,0,MB_OK|MB_ERROR|MB_MOVEABLE);

	cleanup(RC_ERROR);							// Exit Program
}





