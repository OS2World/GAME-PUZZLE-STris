/*******************************************************************************
*																			   *
* PREFERENCES.C 															   *
* ------------- 															   *
*																			   *
* Handling for default-settings, window-positions and so on.				   *
*																			   *
* Modification History: 													   *
* --------------------- 													   *
*																			   *
* 19.04.95	RHS  Created this file											   *
* 10.05.95	RHS  Added Rotateflag											   *
* 02.06.95	RHS  Collected all variables in PrefsStruct.					   *
* 30.09.95	RHS  Added PositionRecord for KeyDialog 						   *
*																			   *
*******************************************************************************/

#define INCL_WIN
#include <os2.h>
#include <string.h>
#include <memory.h>

#include "stris.h"
#include "window.h"
#include "sound.h"
#include "stub.h"
#include "key.h"
#include "preferences.h"


/*** Defines ******************************************************************/

#define PREFS_VERSION	"1.40"


/*** Prototypes ***************************************************************/

/*** Variables ****************************************************************/

		struct	PrefsStruct STrisPrefs;

static	char				PrefsVersion[4];





/*** Functions ****************************************************************/


/*******************************************************************************
* Reset Preferences State to default
*******************************************************************************/

void InitPrefs(void)
{
	memset( &STrisPrefs,0,sizeof( STrisPrefs ));

	STrisPrefs.win_rcl.xLeft =					// Windowplazierung loeschen
	STrisPrefs.opt_rcl.xLeft =
	STrisPrefs.hsc_rcl.xLeft =
	STrisPrefs.abt_rcl.xLeft =
	STrisPrefs.ent_rcl.xLeft =
	STrisPrefs.reg_rcl.xLeft =
	STrisPrefs.nerv_rcl.xLeft =
	STrisPrefs.key_rcl.xLeft = POS_INVALID;

	STrisPrefs.fGridFlag		=
	STrisPrefs.fShowNextPiece	= TRUE;

	InitKeymap();								// Default Keymap setzen
}




/*******************************************************************************
* Load Preferences
*******************************************************************************/

BOOL LoadPrefs(void)
{
	APIRET	rc;
	HINI	hDatei;
	ULONG	action,len;
	BOOL	flag;


	InitPrefs();

	hDatei = PrfOpenProfile(hab,"STris.ini");
//	Message("profile %lx",hDatei);
	if( !hDatei )
	{
		Message("Can't open preferences STris.INI !");
		return FALSE;
	}

	len = sizeof( PrefsVersion );
	PrefsVersion[0] = 0;
	PrfQueryProfileData(hDatei,PRG_NAME,"Version",&PrefsVersion,&len);
//	  Message("Version %s",PrefsVersion);


	/* Check for 1st load initialization */
	if( !strncmp( PrefsVersion, "9.99",4) )
	{
		/* Default Preferences */
//		Message("Loading installation prefs");
	}
	else if( !strncmp( PrefsVersion, PREFS_VERSION,4 ) )
	{
		len = sizeof( STrisPrefs );
		PrfQueryProfileData(hDatei,PRG_NAME,"Prefs",&STrisPrefs,&len);

		SetMusicState( STrisPrefs.fSoundState );

		SetKeymap();
	}
	else
	{
		Message("Warning: Optionsfile 'STris.INI' not found or outdated !\n"
				"Using default settings." );
	}

	PrfCloseProfile(hDatei);


	return TRUE;
}


BOOL SavePrefs(void)
{
	APIRET	rc;
	HINI	hDatei;
	ULONG	action;
	LONG	value;
	BOOL	flag;


	hDatei = PrfOpenProfile(hab,"STris.ini");
	if(!hDatei) return FALSE;

	strncpy(PrefsVersion,PREFS_VERSION,4);
	STrisPrefs.fSoundState = GetMusicState();
	PrfWriteProfileData(hDatei,PRG_NAME,"Version",&PrefsVersion,sizeof(PrefsVersion));
	PrfWriteProfileData(hDatei,PRG_NAME,"Prefs",&STrisPrefs,sizeof(STrisPrefs));

	PrfCloseProfile(hDatei);


	return TRUE;
}



void StoreWindowPos(HWND hwnd, PRECTL rectl)
{
	SWP 	swp;


	WinQueryWindowPos(hwnd,&swp);
	rectl->xLeft	= swp.x;
	rectl->yBottom	= swp.y;
}



void RestoreWindowPos(HWND hwnd, PRECTL rectl)
{
	if( rectl->xLeft != POS_INVALID )
	{
		WinSetWindowPos(hwnd,HWND_TOP,
						rectl->xLeft,
						rectl->yBottom,
						0,0,SWP_MOVE | SWP_ZORDER );
	}
}


