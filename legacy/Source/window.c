/*******************************************************************************
*																			   *
* WINDOW.C																	   *
* --------																	   *
*																			   *
* Open and close the mainwindow. Load necessary bitmaps and update them.	   *
*																			   *
* Modification History: 													   *
* --------------------- 													   *
*																			   *
* 14.04.95	RHS  Extracted this file from STris.c							   *
* 22.04.95	RHS  Position of MainWindow is saved into profile				   *
*																			   *
*******************************************************************************/

#define INCL_WIN
#define INCL_GPI
#define INCL_OS2MM				   /* required for MCI and MMIO headers   */
//#define INCL_SECONDARYWINDOW		 /* required for secondary window		*/

#include <os2.h>
#include <os2me.h>
#include <sw.h>

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

#include "stris.h"
#include "window.h"
#include "playfield.h"
#include "pieces.h"
#include "hiscore.h"
#include "stub.h"
#include "preferences.h"

#include "stris_id.h"


/*** Defines ******************************************************************/

/*** Prototypes ***************************************************************/

/*** Variables ****************************************************************/

		HWND		hwndFrame,
					hwndClient;
		LONG		info_width,info_height;
		LONG		pfLeft,pfTop,pfRight,pfBottom,pfWidth,pfHeight,
					npLeft,npTop,npWidth,npHeight;

static	HPS 		hpsLabel;
static	HBITMAP 	hbmLabel;
static	HDC 		hdcLabel;
static	LONG		win_width,win_height;
static	ULONG		flFrameFlags = FCF_TITLEBAR  | FCF_SYSMENU	| FCF_BORDER |
								   FCF_TASKLIST  | FCF_MENU 	| FCF_ICON |
								   FCF_MINBUTTON | FCF_AUTOICON | FCF_ACCELTABLE;
static	CHAR		szClientClass[] = PRG_NAME;



/*******************************************************************************
* OpenWindow()
* Window registrieren und ”ffnen
* Sollte ein Fehler auftreten wird das Program mit einer Fehlermeldung
* abgebrochen.
*******************************************************************************/

void OpenWindow(HAB hab)
{
	if( !WinRegisterClass(hab,szClientClass,ClientWndProc,
		CS_SIZEREDRAW,0))
		ErrorMsg("Can't register Mainwindow !");

#if 1
	hwndFrame = WinCreateStdWindow( HWND_DESKTOP, WS_VISIBLE, &flFrameFlags,
									szClientClass, FULL_NAME, 0,0,STrisID,
									&hwndClient );

#endif
#if 0
	hwndFrame = WinLoadDlg(HWND_DESKTOP,HWND_DESKTOP,NULL,NULLHANDLE,
							TestDialog,NULL);
	hwndClient = WinWindowFromID(hwndFrame,FID_CLIENT);

	WinLoadMenu(hwndFrame,NULLHANDLE,PrgMenu);
	WinSetWindowText(hwndFrame,FULL_NAME);
#endif

	if( !hwndFrame )
		ErrorMsg("Can't open Mainwindow !");

}




/*******************************************************************************
* CloseWindow(hwnd)
* Window und alle zugeh”rigen Clients schliessen
* hwnd = FrameWindow
*******************************************************************************/

void CloseWindow( HWND hwnd )
{
	if( hwndFrame )
	{
		WinDestroyWindow( hwnd );			// Close Window (and all Subwindows)

//		hwndFrame  =
//		hwndClient = NULLHANDLE;
	}
}



/*******************************************************************************
* InitLabelBitmap(void)
* Alle ben”tigten Bitmaps laden
* return = TRUE alles ok
*		   FALSE Fehler beim laden
*******************************************************************************/

BOOL LoadBitmaps(void)
{
	SIZEL		sizl;


	// Initialize PS, DC and Bitmap
	hdcLabel	= DevOpenDC(hab,OD_MEMORY,"*",0L,NULL,0);
	if( !hdcLabel ) return FALSE;

	sizl.cx = 0;
	sizl.cy = 0;
	hpsLabel	= GpiCreatePS(hab, hdcLabel, &sizl, PU_PELS|GPIF_DEFAULT|
							  GPIT_MICRO|GPIA_ASSOC );
	if( !hpsLabel ) return FALSE;

	hbmLabel	= GpiLoadBitmap(hpsLabel,0,ToMBitmap,0L,0L);
	GpiSetBitmap(hpsLabel,hbmLabel);

//	GpiCreateLogColorTable(hpsLabel,0,LCOLF_CONSECRGB,0,16,
//						   TestColorMap );
//	TestDraw();


	return TRUE;
}


/*******************************************************************************
* UnloadBitmaps()
* Bitmaps freigeben, die mit LoadBitmaps geladen wurden
*******************************************************************************/

void UnloadBitmaps(void)
{
	// Destroy PS,DC and Bitmap
	if( hpsLabel )
		GpiDestroyPS(hpsLabel);
	if( hdcLabel )
		DevCloseDC(hdcLabel);
	if( hbmLabel )
		GpiDeleteBitmap(hbmLabel);
}


/*******************************************************************************
* PaintBitmap(hps)
* Bitmaps in Window zeichnen
*******************************************************************************/

void PaintBitmap(HPS hps)
{
	POINTL	aptl[3];


	aptl[0].x = BORDER+(info_width-LABEL_WIDTH)/2;
	aptl[0].y = BORDER; 				// Target LowerLeft

	aptl[1].x = aptl[0].x+LABEL_WIDTH;
	aptl[1].y = aptl[0].y+LABEL_HEIGHT; // Target UpperRight

	aptl[2].x = 0;
	aptl[2].y = 0;						// Source LowerLeft

	GpiBitBlt(hps,hpsLabel,3,aptl,ROP_SRCCOPY,BBO_IGNORE);
}



/*******************************************************************************
* UpdateTextBlock(hps,flag)
* Hiscore,Score,Level,Lines aktualisieren
* hps  = Presentation Space
* flag = TRUE  -> alles neuzeichnen
*		 FALSE -> nur Aenderungen neuzeichnen
*******************************************************************************/

void UpdateTextBlock( HPS hps, LONG flag )
{
	ULONG	ydist;
	RECTL	rcl;
	CHAR	str[16];


	if( flag == PRT_UPDATE_ALL )
	{
		LastScore	= -1;
		LastHiscore = -1;
		LastLevel	= -1;
		LastLines	= -1;
	}

	ydist = cyChar+cyDesc-2;

	rcl.xLeft	= BORDER;
//	rcl.xRight	= rcl.xLeft+cxChar*18;
	rcl.xRight  = info_width+BORDER;
	rcl.yTop	= win_height-BORDER-4*PieceHeight-3/2*BORDER;
	rcl.yBottom = rcl.yTop-ydist;

	GpiSetColor( hps, CLR_BLACK );

	if( Hiscore != LastHiscore )
	{
		if( fNewHiscore )	GpiSetColor( hps, CLR_RED );
		WinDrawText( hps,sprintf(str,"%8ld",Hiscore),str,&rcl,
					0,CLR_BACKGROUND,DT_ERASERECT|DT_RIGHT|DT_TEXTATTRS );
		if( fNewHiscore )	GpiSetColor( hps, CLR_BLACK );

		WinDrawText( hps,8,"Hiscore",&rcl,0,0,DT_LEFT|DT_TEXTATTRS );

	}

	rcl.yTop	-= ydist;
	rcl.yBottom -= ydist;
	if( Score != LastScore )
	{
		WinDrawText( hps,sprintf(str,"%8ld",Score),str,&rcl,
					0,CLR_BACKGROUND,DT_ERASERECT|DT_RIGHT|DT_TEXTATTRS );
		WinDrawText( hps,5,"Score",&rcl,0,0,DT_LEFT|DT_TEXTATTRS );
	}

	rcl.yTop	-= ydist;
	rcl.yBottom -= ydist;
	if( Lines != LastLines )
	{
		WinDrawText( hps,sprintf(str,"%8ld",Lines),str,&rcl,
					0,CLR_BACKGROUND,DT_ERASERECT|DT_RIGHT|DT_TEXTATTRS );
		WinDrawText( hps,5,"Lines",&rcl,0,0,DT_LEFT|DT_TEXTATTRS );
	}

	rcl.yTop	-= ydist;
	rcl.yBottom -= ydist;
	if( Level != LastLevel )
	{
		WinDrawText( hps,sprintf(str,"%8ld",Level),str,&rcl,
					0,CLR_BACKGROUND,DT_ERASERECT|DT_RIGHT|DT_TEXTATTRS );
		WinDrawText( hps,5,"Level",&rcl,0,0,DT_LEFT|DT_TEXTATTRS );
	}

	LastHiscore = Hiscore;
	LastScore	= Score;
	LastLevel	= Level;
	LastLines	= Lines;
}



/*******************************************************************************
* BuildWindow(hwndClient,hwndFrame)
* Hauptfenster aufbauen und plazieren.
* hwndCLient = ClientWindow
* hwndFrame  = FrameWindow
*******************************************************************************/

void BuildWindow(HWND hwnd, HWND hwndFrame )
{
	ULONG	min_height;
	ULONG	xpos,xpos2,ypos,ydist,
			button_width,button_height;



//	info_width	= max( 4*PieceWidth+BORDER, 18*cxChar );
	info_width  = max( LABEL_WIDTH, 18*cxChar );
	win_width	= info_width+PieceWidth*NUM_PIECES_X+4*BORDER;

	min_height	= PieceHeight*NUM_PIECES_Y+2*BORDER;
	info_height = BORDER+4*PieceHeight+BORDER+4*(cyChar+cyDesc)+cyChar+
				  5*cyChar*3/2+BORDER+LABEL_HEIGHT+BORDER;

	win_height	= max( info_height, min_height );

//	button_width	= 18*cxChar;
	button_width    = info_width;
	button_height	= cyChar*3/2;
	ydist			= button_height+2;

	xpos = BORDER;
	ypos = BORDER;
	ypos += LABEL_HEIGHT+3/2*BORDER;

	WinCreateWindow(hwnd,WC_BUTTON,"Start Game",WS_VISIBLE|BS_PUSHBUTTON,xpos,ypos,
					button_width,button_height,hwnd,HWND_BOTTOM,IDF_NEW_GAME,
					NULL,NULL);
	ypos += ydist;

	WinCreateWindow(hwnd,WC_BUTTON,"Hiscore...",WS_VISIBLE|BS_PUSHBUTTON,xpos,ypos,
					button_width,button_height,hwnd,HWND_BOTTOM,IDF_HISCORE,
					NULL,NULL);
	ypos += ydist;

	WinCreateWindow(hwnd,WC_BUTTON,"Options...",WS_VISIBLE|BS_PUSHBUTTON,xpos,ypos,
					button_width,button_height,hwnd,HWND_BOTTOM,IDF_OPTIONS,
					NULL,NULL);
	ypos += ydist;

	WinCreateWindow(hwnd,WC_BUTTON,"About...",WS_VISIBLE|BS_PUSHBUTTON,xpos,ypos,
					button_width,button_height,hwnd,HWND_BOTTOM,IDF_ABOUT,
					NULL,NULL);
	ypos += ydist;

	WinCreateWindow(hwnd,WC_BUTTON,"Pause",WS_VISIBLE|BS_CHECKBOX,xpos+2,ypos,
					button_width,button_height,hwnd,HWND_BOTTOM,IDF_PAUSE,
					NULL,NULL);


	// Next Piece

	npWidth 	= 4*PieceWidth;
	npHeight	= 4*PieceHeight;
	npLeft		= xpos+(info_width-npWidth)/2;
	npTop		= win_height-BORDER-npHeight;

#if 1
	WinCreateWindow(hwnd,WC_STATIC,"",WS_VISIBLE|SS_FGNDFRAME,
					npLeft-1,npTop-1,npWidth+2,npHeight+2,
					hwnd,HWND_BOTTOM,IDF_NEXT_PIECE,NULL,NULL);
#endif


	// PlayField

	pfWidth 	= PieceWidth*NUM_PIECES_X;
	pfHeight	= PieceHeight*NUM_PIECES_Y;

	pfTop		= win_height-BORDER;
	pfLeft		= win_width-BORDER-pfWidth;
	pfBottom	= pfTop-pfHeight;
	pfRight 	= pfLeft+pfWidth;

#if 1
	WinCreateWindow(hwnd,WC_STATIC,"",WS_VISIBLE|SS_FGNDFRAME,
					pfLeft-1,pfBottom-1,pfWidth+2,pfHeight+2,
					hwnd,HWND_BOTTOM,IDF_PLAYFIELD,NULL,NULL);
#endif


	/*** Window plazieren und Gr”sse einstellen ***/

	// If window isn't positioned we center to the screen

	if( STrisPrefs.win_rcl.xLeft == POS_INVALID )
	{
		STrisPrefs.win_rcl.xLeft   = (desk_width-win_width)/2;
		STrisPrefs.win_rcl.yBottom = (desk_height-win_height-
							  WinQuerySysValue(HWND_DESKTOP,SV_CYTITLEBAR)-
							  WinQuerySysValue(HWND_DESKTOP,SV_CYMENU) )/2;
	}

	STrisPrefs.win_rcl.xRight	= STrisPrefs.win_rcl.xLeft+win_width;
	STrisPrefs.win_rcl.yTop 	= STrisPrefs.win_rcl.yBottom+win_height;
	WinCalcFrameRect(hwndFrame,&STrisPrefs.win_rcl,FALSE);

	WinSetWindowPos(hwndFrame,HWND_TOP,
					STrisPrefs.win_rcl.xLeft,STrisPrefs.win_rcl.yBottom,
					STrisPrefs.win_rcl.xRight-STrisPrefs.win_rcl.xLeft,
					STrisPrefs.win_rcl.yTop-STrisPrefs.win_rcl.yBottom,
					SWP_MOVE | SWP_SIZE | SWP_ZORDER | SWP_ACTIVATE | SWP_SHOW);
}




