/*******************************************************************************
*                                                                             *
* HELP.C                                                                     *
* ------                                                                     *
*                                                                             *
* On line help for STris. One help library ('.hlp') per language, the        *
* active one is selected by the current language.                            *
*                                                                             *
* Modification History:                                                       *
* ---------------------                                                       *
*                                                                             *
* 14.04.95	RHS  Copied from Borlands Clock Example                         *
* 07.04.96  RHS  Windowsize now controlled by STris                          *
* 2026	     OD2  Per language help libraries, Open Watcom port             *
*                                                                             *
*******************************************************************************/

#define INCL_WINHELP
#define INCL_WIN
#define INCL_DOSMODULEMGR
#define INCL_DOSPROCESS
#define INCL_DOSFILEMGR

#include <os2.h>
#include <stdio.h>
#include <string.h>

#include "stris.h"
#include "window.h"
#include "stub.h"
#include "lang.h"
#include "stris_id.h"
#include "help.h"


/*** Variables ****************************************************************/

        HWND    hwndHelpInstance;
        BOOL    fHelpAvailable;

static  CHAR    szLibName[CCHMAXPATH],
                szWindowTitle[] = "STris Help System";


/* One help library per language (compiled with IPFC) */

static  CHAR    *szHelpFiles[LANG_COUNT] =
{
    "STris_en.hlp",
    "STris_es.hlp",
    "STris_nl.hlp",
    "STris_de.hlp",
    "STris_fr.hlp",
    "STris_it.hlp"
};


/*** Functions ****************************************************************/

/*** FindHelpFile ***************************************************************
* Looks for the help library next to the executable: <exe dir>\help\ first,
* then <exe dir>. Falls back to the plain file name (system search path).
*******************************************************************************/

static void FindHelpFile(const char *name, char *out)
{
    CHAR        szExe[CCHMAXPATH];
    CHAR        szTry[CCHMAXPATH];
    FILESTATUS3 fs;
    char        *p;

    PTIB        ptib;
    PPIB        ppib;

    strcpy( out, name );
    DosGetInfoBlocks( &ptib, &ppib );
    if( DosQueryModuleName( ppib->pib_hmte, sizeof(szExe), szExe ) )
        return;
    p = strrchr( szExe, '\\' );
    if( p == NULL )
        return;
    p[1] = 0;

    sprintf( szTry, "%shelp\\%s", szExe, name );
    if( !DosQueryPathInfo( szTry, FIL_STANDARD, &fs, sizeof(fs) ) )
    {
        strcpy( out, szTry );
        return;
    }
    sprintf( szTry, "%s%s", szExe, name );
    if( !DosQueryPathInfo( szTry, FIL_STANDARD, &fs, sizeof(fs) ) )
        strcpy( out, szTry );
}


/****************************************************************
*  Routine for initializing the help manager
*  Name:	OpenHelp()
*  Purpose: Initializes the IPF help facility
*  Usage:	Called once during initialization of the program
*  Method:	Initializes the HELPINIT structure and creates the
*			help instance. If successful, the help instance
*			is associated with the main window
*  Returns: TRUE if ok, otherwise FALSE
*
****************************************************************/

BOOL OpenHelp(void)
{
    strcpy( szLibName, szHelpFiles[ current_lang ] );

    return SetHelpLanguage( current_lang );
}


/****************************************************************
*  SetHelpLanguage(lang)
*  Destroys the current help instance and creates a new one using
*  the help library of the given language.
****************************************************************/

BOOL SetHelpLanguage(int lang)
{
    HELPINIT    hini;
    RECTL       rect;

    if( lang < 0 || lang >= LANG_COUNT )
        lang = LANG_EN;

    current_lang = lang;

    /* Free the old instance if there is one */
    if( hwndHelpInstance != NULLHANDLE )
        WinDestroyHelpInstance( hwndHelpInstance );
    hwndHelpInstance = NULLHANDLE;

    fHelpAvailable = FALSE;

    /* initialize help init structure */
    memset( &hini, 0, sizeof( HELPINIT ));

    FindHelpFile( szHelpFiles[ current_lang ], szLibName );

    hini.cb                        = sizeof(HELPINIT);
    hini.ulReturnCode              = 0;
    hini.pszTutorialName           = (PSZ)NULL;   /* if tutorial added, add name here */

    hini.phtHelpTable              = (PHELPTABLE)(0xFFFF0000 | STRIS_HELP_TABLE );

    hini.hmodAccelActionBarModule  = 0L;
    hini.idAccelTable              = 0L;
    hini.idActionBar               = 0L;

    hini.pszHelpWindowTitle        = (PSZ)szWindowTitle;
    hini.hmodHelpTableModule       = 0L;
    hini.fShowPanelId              = CMIC_HIDE_PANEL_ID;
    hini.pszHelpLibraryName        = (PSZ)szLibName;

    /* Creating help instance */
    hwndHelpInstance = WinCreateHelpInstance(hab, &hini);
    if(hwndHelpInstance == NULLHANDLE || hini.ulReturnCode)
    {
        hwndHelpInstance = NULLHANDLE;
        Message("Can't create HelpInstance\n"
                "Check if file '%s' exists.", szLibName);
        return FALSE;
    }

    /* Associate help instance with main frame */
    if(!WinAssociateHelpInstance(hwndHelpInstance, hwndFrame))
    {
        Message("Can't associate help to window\n"
                "OnlineHelp will not be available.");
        return FALSE;
    }

    /* Set size of HelpWindow */
    rect.xLeft   = desk_width/4;
    rect.yBottom = 0;
    rect.xRight  = desk_width;
    rect.yTop    = desk_height;
    WinSendMsg(hwndHelpInstance,HM_SET_COVERPAGE_SIZE,(MPARAM)&rect,0);

    /* Enable the help menu items */
    EnableHelpMenu();

    return TRUE;
}


/****************************************************************
*  EnableHelpMenu()
*  Enables all help menu entries when help is available.
****************************************************************/

void EnableHelpMenu(void)
{
    HWND    hwndMenu;

    hwndMenu = WinWindowFromID( hwndFrame, FID_MENU );
    if( hwndMenu == NULLHANDLE )
        return;

    fHelpAvailable = TRUE;

    WinEnableMenuItem(hwndMenu, IDM_HELPUSING, TRUE);
    WinEnableMenuItem(hwndMenu, IDM_HELPINDEX, TRUE);
    WinEnableMenuItem(hwndMenu, IDM_HELPCONTENTS, TRUE);
    WinEnableMenuItem(hwndMenu, IDM_HELPHOWTOPLAY, TRUE);
    WinEnableMenuItem(hwndMenu, IDM_HELPKEYS, TRUE);
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
    hwndHelpInstance = NULLHANDLE;
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
    /* this just displays the system help contents panel */

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
