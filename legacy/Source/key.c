/*******************************************************************************
*																			   *
* KEY.C 																	   *
* ----- 																	   *
*																			   *
* Alles rund um den KeyDialog												   *
*																			   *
* Modification History: 													   *
* --------------------- 													   *
*																			   *
* 30.09.95	RHS  Created this file											   *
* 06.11.95	RHS  First test-version 										   *
* 13.03.96	RHS  1. Rework -> Released for test purpose 					   *
* 06.04.96	RHS  Changed to GraphicButtons              					   *
*																			   *
********************************************************************************/

#define INCL_WIN
#define INCL_OS2MM
#define INCL_SW
#define INCL_MACHDR


#include <os2.h>
#include <os2me.h>
#include <stdio.h>
#include <string.h>

#include "stris.h"
#include "window.h"
#include "preferences.h"
#include "key.h"

#include "stris_id.h"



/*** Defines ******************************************************************/

enum _STATES							/* Statemachine 					*/
{										/* SCANNING : NÑchster Tastendruck	*/
	STATE_NORMAL = 0,					/* wird in Keymap aufgenommen		*/
	STATE_SCANNING, 					/* NORMAL	: ...					*/
	STATE_ABORTED
};


enum _SETKEY
{
	SETKEY_SUCCESS,
	SETKEY_ABORTED,
	SETKEY_USED,
	SETKEY_STRIS,
	SETKEY_UNKNOWN
};



/*** Prototypes ***************************************************************/


/*** Variables ****************************************************************/

static	KEYSTRUCT	Keys[KEY_NUM];		/* KeyMap							*/

static	USHORT		usState,			/* Statemachine 					*/
					usFunction; 		/* Funktion die neue Taste erhalten soll	*/

static	USHORT		usButtonID;			/* ID of clicked button				*/

static	KEYINFO 	KeyInfo[] = 		/* Tabelle der mîglichen Tasten mit */
{										/* ASCII Beschreibung				*/

	VK_ESC, 		"Escape",			// Don't change order

	VK_LEFT,		"Cursor Left",
	VK_RIGHT,		"Cursor Right",
	VK_UP,			"Cursor Up",
	VK_DOWN,		"Cursor Down",
//	VK_SPACE,		"Space",

	'a',			"A",				// Internal used
	'b',			"B",
	'c',			"C",
	'd',			"D",
	'e',			"E",
	'f',			"F",
	'g',			"G",
	'h',			"H",				// Internal used
	'i',			"I",
	'j',			"J",
	'k',			"K",
	'l',			"L",
	'm',			"M",
	'n',			"N",
	'o',			"O",				// Internal used
	'p',			"P",				// Internal used
	'q',			"Q",
	'r',			"R",
	's',			"S",				// Internal used
	't',			"T",
	'u',			"U",
	'v',			"V",
	'w',			"W",
	'x',			"X",
	'y',			"Y",
	'z',			"Z",
//	'0',			"0",
//	'1',			"1",
//	'2',			"2",
//	'3',			"3",
//	'4',			"4",
//	'5',			"5",
//	'6',			"6",
//	'7',			"7",
//	'8',			"8",
//	'9',			"9",

	0,				"<unset>",

	-1, 			0					/* Don't remove this one		*/
};


static	USHORT	usDefKeys[] =			/* Default Keymap				*/
{
	VK_LEFT,VK_RIGHT,VK_UP,0,VK_DOWN
};

static	char	*szFuncText[] = 		/* Texte die bei Tastenabfrage	*/
{										/* Angezeigt werden 			*/
	"move the piece leftwards",
	"move the piece rightwards",
	"rotate counter-clockwise",
	"rotate clockwise",
	"drop the piece"
};


/*** Lokale Funktionen ********************************************************/


/**************************************************************************
* CheckKey(usKeyCode)
* Testet ob der Key verwendet werden kann
* usKeyCode : KeyCode von MessageHandler
* Return	: Index auf KeyInfo Tabelle
*			  -1 = ungÅltig, -2 = StrisKey, 0 = ESCAPE
**************************************************************************/

static LONG CheckKey(USHORT usKeyCode)
{
	SHORT	i;
	char	key;


	/* Tastenliste durchsuchen und Index retournieren falls gefunden */

	for(i=0;KeyInfo[i].sKeyCode != -1;i++)
	{
		if( KeyInfo[i].sKeyCode == usKeyCode )
		{
			if( KeyInfo[i].szKeyText == NULL )
				return -2;						// Key internally used
			else
				return i;						// All Ok. Return Key-Num
		}
	}

	/* Nichts gefunden -> -1 */

	return -1;
}


/**************************************************************************
* GetKeyText(usKeyCode)
* Text fÅr den gegebenen Key suchen
* usKeyCode : KeyCode von MessageHandler
* Return	: Text oder NULL
**************************************************************************/

static char *GetKeyText(USHORT usKeyCode)
{
	SHORT	i;


	/* Taste suchen */
	i = CheckKey(usKeyCode);


	/* Text zurÅckgeben */
	if(i != -1)
		return KeyInfo[i].szKeyText;
	else
		return NULL;
}



/**************************************************************************
* UpdateKeyText(hwnd,usFunc)
* Text in Dialogfenster updaten
* hwnd	 : WindowHandle
* usFunc : Funktion (z.B. KEY_LEFT)
**************************************************************************/

static void UpdateKeyText(HWND hwnd, USHORT usFunc)
{
	ULONG	item;


	item = IDD_TEXTLEFT+usFunc; 		/* So, wenn wir mit dieser Methode	*/
										/* arbeiten, muss die Reihenfolge	*/
										/* von Funktionen und Keys genau	*/
										/* Åbereinstimmen					*/

	WinSetDlgItemText(hwnd,item,Keys[usFunc].szKeyText );
}



/**************************************************************************
* UpdateAllKeys(hwnd)
* Keys fÅr alle Funktionen neu zeichnen
* hwnd	 : WindowHandle
**************************************************************************/

static void UpdateAllKeys(HWND hwnd)
{
	USHORT	i;


	for(i=0;i<=(IDD_TEXTDROP-IDD_TEXTLEFT);i++)
	{
		UpdateKeyText(hwnd,i);
	}
}



/**************************************************************************
* GetKey(hwnd,usFunc)
* Dialogfenster sperren, STATE-Machine auf STATE_SCANNING setzen ->
* Messagehandler teste auf Tastendruck.
* hwnd	: WindowHandle
* usKey : Funktion (z.B. KEY_LEFT)
**************************************************************************/

static void GetKey(HWND hwnd, USHORT usFunc)
{
	char	str[128];


	sprintf(str,"Press key to %s, ESC to abort",szFuncText[usFunc] );
	WinSetDlgItemText(hwnd,IDD_KEYTEXT2,str);

	WinEnableWindow(hwnd,FALSE);			/* Window sperren			*/

	usFunction = usFunc;					/* Funktion festlegen		*/
	usState    = STATE_SCANNING;			/* StateMachine anwerfen	*/
}


/**************************************************************************
* SetKey(hwnd,usKey,bCheck)
* Nach Tastendruck Funktion neu belegen und Text updaten.
* hwnd	: WindowHandle
* usKey : Taste
**************************************************************************/

static SHORT SetKey(HWND hwnd, USHORT usKey, USHORT usFunc, BOOL bCheck)
{
	SHORT	ret,
			result,
			i;



	result = CheckKey(usKey);
//	Message("CheckKey %ld",result);

	switch( result )
	{
		case -2:
			/* Key internally used										*/
			return SETKEY_STRIS;

		case -1:
			/* Unknown key												*/
			return SETKEY_UNKNOWN;

		case 0:
			/* User aborted 											*/
			return SETKEY_ABORTED;

		default:
			/* Check ob Taste schon benutzt wird						*/

			if( bCheck )
			{
				for(i=0;i<KEY_NUM;i++)
				{
					if( usKey == Keys[i].usKeyCode )
						return SETKEY_USED;
				}
			}

			Keys[usFunc].usKeyCode	 = usKey;
			Keys[usFunc].usQualifier = 0;
			Keys[usFunc].szKeyText	 = GetKeyText(usKey);

//			Message("Key %d -> '%s'",usKey,Keys[usFunc].szKeyText );
			UpdateKeyText(hwnd,usFunc);

			return SETKEY_SUCCESS;
	}

//	return SETKEY_ABORTED;
}


/**************************************************************************
* DefaultKeys(hwnd)
* Default Tastenbelegung anwenden
* hwnd	: WindowHandle
**************************************************************************/

static void DefaultKeys(HWND hwnd)
{
	USHORT	i;


	for(i=0;i<=(IDD_TEXTDROP-IDD_TEXTLEFT);i++)
	{
		SetKey(hwnd,usDefKeys[i],i,FALSE);
	}
}


/**************************************************************************
* LoadKeymap()
* Tastenbelegung aus Preferences laden.
**************************************************************************/

static void LoadKeymap(void)
{
	USHORT	usKey,
			i;


	for(i=0;i<=KEY_NUM;i++)
	{
		usKey = STrisPrefs.Keys[i].usKeyCode;
		if( !usKey )
			usKey = usDefKeys[i];

		Keys[i].usKeyCode	= usKey;
		Keys[i].usQualifier = 0;
		Keys[i].szKeyText	= GetKeyText(usKey);
	}
}


/**************************************************************************
* SaveKeymap()
* Tastenbelegung in Preferences speichern.
**************************************************************************/

static void SaveKeymap(void)
{
	USHORT	i;


	for(i=0;i<KEY_NUM;i++)
	{
		STrisPrefs.Keys[i].usKeyCode   = Keys[i].usKeyCode;
		STrisPrefs.Keys[i].usQualifier = 0;
	}
}





/*** Globale Funktionen *******************************************************/

/**************************************************************************
* InitKeymap()
* DefaultKeymap setzen
**************************************************************************/

void InitKeymap(void)
{
	USHORT	i;


	for(i=0;i<KEY_NUM;i++)
	{
		STrisPrefs.Keys[i].usKeyCode   = usDefKeys[i];
		STrisPrefs.Keys[i].usQualifier = 0;
	}
}

/**************************************************************************
* SetKeymap()
* Tastenbelegung ueberpruefen. Falls leer DefaultKeymap kopieren.
**************************************************************************/

void SetKeymap(void)
{
	USHORT	usKey,
			i;


	for(i=0;i<KEY_NUM;i++)
	{
		usKey = STrisPrefs.Keys[i].usKeyCode;
		if( !usKey )
		{
			usKey = usDefKeys[i];

			STrisPrefs.Keys[i].usKeyCode   = usKey;
			STrisPrefs.Keys[i].usQualifier = 0;
		}
	}
}



/*******************************************************************************
* Message Handler for KeyRequester
* Called by the Dialogmanager
*******************************************************************************/

MRESULT EXPENTRY KeyDlgProc( HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2 )
{
	HWND		hwndEntry;
	HPS 		hps;
	ULONG		lState;
	USHORT		usKeyCode,
				usQualifier;
	char		*pszText;


	switch( msg )
	{
		case WM_INITDLG:

			// Place Window

			usState = STATE_NORMAL;

			UpdateAllKeys(hwnd);

			RestoreWindowPos(hwnd,&STrisPrefs.key_rcl);
			return 0;

		case WM_CHAR:

//			DosBeep(100,100);

			/* Scan only when necessary */
			if( usState != STATE_SCANNING )
				break;


			lState = CHARMSG(&msg)->fs;
			if( !(lState & KC_KEYUP) )
			{
				usKeyCode	=
				usQualifier = 0;

				if( lState & KC_CHAR )
				{
					usKeyCode	= CHARMSG(&msg)->chr;
					usQualifier = CHARMSG(&msg)->fs;

//					Message("CHAR %d %c  Qualifier %d",usKeyCode,usKeyCode,usQualifier );
				}
				else if( lState & KC_VIRTUALKEY )
				{
					usKeyCode	= CHARMSG(&msg)->vkey;
					usQualifier = CHARMSG(&msg)->fs;

//					Message("VKey %d %c  Qualifier %d",usKeyCode,usKeyCode,usQualifier );
				}

				switch( SetKey(hwnd, usKeyCode, usFunction, TRUE ) )
				{
					case SETKEY_SUCCESS:		// All OK
						pszText = "Key definition successfully completed.";
						usState = STATE_NORMAL;
						break;

					case SETKEY_ABORTED:		// ESC - aborted
						WinAlarm(HWND_DESKTOP,WA_NOTE);
						pszText = "Key definition aborted.";
						usState = STATE_NORMAL;
						break;

					case SETKEY_USED:			// Key already defined
						WinAlarm(HWND_DESKTOP,WA_WARNING);
						pszText = "Key already used. Please try another.";
						break;

					case SETKEY_STRIS:			// Internally used key
						WinAlarm(HWND_DESKTOP,WA_WARNING);
						pszText = "This key is internally used by STris. Please try another.";
						break;

					case SETKEY_UNKNOWN:		// Unknown key
						WinAlarm(HWND_DESKTOP,WA_WARNING);
						pszText = "Sorry. I can't recognize this key. Please try another.";
						break;
				}

				WinSetDlgItemText(hwnd,IDD_KEYTEXT2,pszText );
				if(usState == STATE_NORMAL)
				{
					WinEnableWindow(hwnd,TRUE); 			/* Window freigeben 		*/
					WinSendDlgItemMsg(hwnd,usButtonID,GBM_SETSTATE,(MPARAM)GB_UP,(MPARAM)TRUE);
				}

				return 0;
			}

			break;


		case WM_COMMAND:

//			if( usState == STATE_SCANNING )
//				return 0;

//			DosBeep(200,100);
//			DosBeep(400,100);

			usButtonID = COMMANDMSG(&msg)->cmd;			
			switch( usButtonID )
			{
				case IDD_KEYLEFT:				/* The playing keys */
					GetKey(hwnd,KEY_LEFT);
					break;

				case IDD_KEYRIGHT:
					GetKey(hwnd,KEY_RIGHT);
					break;

				case IDD_KEYROTATE:
					GetKey(hwnd,KEY_ROTATE);
					break;

				case IDD_KEYROTATE2:
					GetKey(hwnd,KEY_ROTATE2);
					break;

				case IDD_KEYDROP:
					GetKey(hwnd,KEY_DROP);
					break;

				case IDD_DEFAULT:				/* Set KeyBindings to Default */
					DefaultKeys(hwnd);
					break;

				case DID_OK:					/* Use this KeyBindings */
					WinDismissDlg( hwnd, FALSE );
					break;

				case DID_CANCEL:				/* Cancel */
					WinDismissDlg( hwnd, TRUE );
					break;
			}

			return 0;


		case WM_DESTROY:

			StoreWindowPos(hwnd,&STrisPrefs.key_rcl);
			return 0;
	}

	return WinDefDlgProc( hwnd, msg, mp1, mp2 );
}



/*******************************************************************************
* KeyFunction()
* Display the KeyRequester
*******************************************************************************/

ULONG KeyFunction(HWND hwnd,ULONG msg,MPARAM mp1, MPARAM mp2)
{
	LoadKeymap();

	if( !WinDlgBox( HWND_DESKTOP, hwnd, KeyDlgProc, NULLHANDLE, DLG_KEY, NULL ) )
	{
		SaveKeymap();					/* Save KeyBindings */
	}

	return TRUE;
}





/**************************************************************************
* MapKey2Function()
* GedrÅckte Taste auswerten. Falls vorhanden ID der Funktion retournieren
**************************************************************************/

SHORT MapKey2Function(USHORT usKey)
{
	USHORT	i;


	/* Suche Key in Preferences KeyMap */

	for(i=0;i<KEY_NUM;i++)
	{
		if( STrisPrefs.Keys[i].usKeyCode == usKey )
			return i;
	}

	return -1;
}


