/*******************************************************************************
*																			   *
* HELP.C																	   *
* ------																	   *
*																			   *
* About Requester															   *
*																			   *
* Modification History: 													   *
* --------------------- 													   *
*																			   *
* 14.04.95	RHS  Copied from Borlands Clock Example 						   *
* 07.04.96  RHS  Windowsize now controlled by STris                            *
*																			   *
*******************************************************************************/

#define INCL_WINHELP
#define INCL_WIN

#include <os2.h>
#include <string.h>

#include "stris.h"
#include "window.h"
#include "stub.h"
#include "stris_id.h"
#include "help.h"


/*** Defines ******************************************************************/

/*** Prototypes ***************************************************************/

/*** Variables ****************************************************************/

		HWND	hwndHelpInstance;
		BOOL	fHelpAvailable;


static	CHAR	szLibName[] 	= "STris.hlp",
				szWindowTitle[] = "STris Help System";



/*** Functions ****************************************************************/


/****************************************************************
*  Routine for initializing the help manager
*  Name:	OpenHelp()
*  Purpose: Initializes the IPF help facility
*  Usage:	Called once during initialization of the program
*  Method:	Initializes the HELPINIT structure and creates the
*			help instance.	If successful, the help instance
*			is associated with the main window
*  Returns: TRUE if ok, otherwise FALSE
*
****************************************************************/

BOOL OpenHelp(void)
{
	HELPINIT	hini;
	HWND		hwndMenu;
	RECTL		rect;



	/* if we return because of an error, Help will be disabled */
	hwndMenu						= WinWindowFromID(hwndFrame,FID_MENU);
	fHelpAvailable					= FALSE;


	/* initialize help init structure */
	hini.cb 						= sizeof(HELPINIT);
	hini.ulReturnCode				= 0;
	hini.pszTutorialName			= (PSZ)NULL;   /* if tutorial added, add name here */

	hini.phtHelpTable				= (PHELPTABLE)(0xFFFF0000 | STRIS_HELP_TABLE );

	hini.hmodAccelActionBarModule	= 0L;
	hini.idAccelTable				= 0L;
	hini.idActionBar				= 0L;

	hini.pszHelpWindowTitle 		= (PSZ)szWindowTitle;
	hini.hmodHelpTableModule		= 0L;
	hini.fShowPanelId				= CMIC_HIDE_PANEL_ID;
	hini.pszHelpLibraryName 		= (PSZ)szLibName;

	/* Creating help instance */
	hwndHelpInstance				= WinCreateHelpInstance(hab, &hini);
	if(hwndHelpInstance == NULLHANDLE || hini.ulReturnCode)
	{
		Message("Can't create HelpInstance\nCheck if file '%s' exists.",szLibName);
		return FALSE;
	}

	/* Associate help instance with main frame */
	if(!WinAssociateHelpInstance(hwndHelpInstance, hwndFrame))
	{
		Message("Can't associate help to window\nOnlineHelp will not be available.");
		return FALSE;
	}

	/* Set size of HelpWindow */
	rect.xLeft   = desk_width/4;
	rect.yBottom = 0;
	rect.xRight  = desk_width;
	rect.yTop    = desk_height;
	WinSendMsg(hwndHelpInstance,HM_SET_COVERPAGE_SIZE,(MPARAM)&rect,0);


	/* Enable Menues */
	fHelpAvailable = TRUE;

	WinEnableMenuItem(hwndMenu, IDF_USINGHELP, TRUE);
	WinEnableMenuItem(hwndMenu, IDF_HELPINDEX, TRUE);
	WinEnableMenuItem(hwndMenu, IDF_HELP, TRUE);
	WinEnableMenuItem(hwndMenu, IDF_HOWTOPLAY, TRUE);
	WinEnableMenuItem(hwndMenu, IDF_KEYSHELP, TRUE);


	return TRUE;
}


/****************************************************************
*  Destroys the help instance
*  Name:	CloseHelp(VOID)
*  Purpose: Destroys the help instance for the application
*  Usage:	Called after exit from message loop
*  Method:	Calls WinDestroyHelpInstance() to destroy the
*			help instance
*  Returns:
****************************************************************/

void CloseHelp(void)
{
	if(hwndHelpInstance != NULLHANDLE)
		WinDestroyHelpInstance(hwndHelpInstance);
}



/****************************************************************
*  Displays the help panel indicated
*  Name:	DisplayHelpPanel(idPanel)
*  Purpose: Displays the help panel whose id is given
*  Usage:	Called whenever a help panel is desired to be
*			displayed, usually from the WM_HELP processing
*			of the dialog boxes
*  Method:	Sends HM_DISPLAY_HELP message to the help instance
*  Returns:
****************************************************************/

void DisplayHelpPanel(LONG idPanel)
{
	if(WinSendMsg(hwndHelpInstance,
		   HM_DISPLAY_HELP,
		   MPFROMLONG(idPanel),
		   MPFROMSHORT(HM_RESOURCEID)))
	{
		Message("Error in OnlineHelp");
	}
}



ULONG HelpForHelp(HWND hwnd,ULONG msg,MPARAM mp1, MPARAM mp2)
{
	/* this just displays the system help for help panel */
	if(WinSendMsg(hwndHelpInstance,HM_DISPLAY_HELP,MPVOID,MPVOID ) )
	{
		Message("Error in OnlineHelp");
	}

	return TRUE;
}




ULONG HelpIndex(HWND hwnd,ULONG msg,MPARAM mp1, MPARAM mp2)
{
	/* this just displays the system help index panel */

	if(WinSendMsg(hwndHelpInstance,
			HM_HELP_INDEX,MPVOID,MPVOID))
	{
		Message("Error in OnlineHelp");
	}

	return TRUE;
}


ULONG HelpContents(HWND hwnd,ULONG msg,MPARAM mp1, MPARAM mp2)
{
	/* this just displays the system help index panel */

	if(WinSendMsg(hwndHelpInstance,
			HM_HELP_CONTENTS,MPVOID,MPVOID))
	{
		Message("Error in OnlineHelp");
	}

	return TRUE;
}




ULONG HelpMain(HWND hwnd,ULONG msg,MPARAM mp1, MPARAM mp2)
{
	DisplayHelpPanel(HELP_GENERAL);

	return TRUE;
}



ULONG HelpKeys(HWND hwnd,ULONG msg,MPARAM mp1, MPARAM mp2)
{
	DisplayHelpPanel(HELP_KEYS);

	return TRUE;
}



ULONG HelpHowToPlay(HWND hwnd,ULONG msg,MPARAM mp1, MPARAM mp2)
{
	DisplayHelpPanel(HELP_HOWTOPLAY);

	return TRUE;
}


