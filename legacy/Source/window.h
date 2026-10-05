/*******************************************************************************
*																			   *
* WINDOW.H																	   *
* --------																	   *
*																			   *
* Include File for WINDOW.C 												   *																			  *
*																			   *
*******************************************************************************/
#ifndef WINDOW_H
#define WINDOW_H


/*** Defines ******************************************************************/


#define POS_INVALID 	-10000

// Flags for UpdateTextBlock

enum PrintFlags
{
	PRT_UPDATE_ALL,
	PRT_UPDATE_CHANGES
};




/*** Prototypes ***************************************************************/

void OpenWindow( HAB hab );
void CloseWindow( HWND hwnd );

void BuildWindow(HWND hwnd, HWND hwndFrame );

BOOL LoadBitmaps(void);
void UnloadBitmaps(void);
void PaintBitmap(HPS hps);
void UpdateTextBlock( HPS hps, LONG flag );


/*** Variables ****************************************************************/

extern	HWND		hwndFrame,hwndClient;
extern	HBITMAP 	hbmPieces;
extern	HPS 		hpsMemory;
extern	LONG		info_width,info_height;
extern	LONG		pfLeft,pfTop,pfRight,pfBottom,pfWidth,pfHeight,
					npLeft,npTop,npWidth,npHeight;



#endif /* WINDOW_H */

