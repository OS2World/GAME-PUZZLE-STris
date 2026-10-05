/*******************************************************************************
*																			   *
* STUB.H																	   *
* ------																	   *
*																			   *
* Some usefull functions that everybody needs								   *																			  *
*																			   *
*******************************************************************************/

#ifndef STUB_H
#define STUB_H


/*** Defines ******************************************************************/


/*** Prototypes ***************************************************************/

void GetCharSize(HWND hwnd);
void GetDesktopSize(void);
void InitRandom(void);
ULONG EmptyFunction(HWND hwnd,ULONG msg,MPARAM mp1, MPARAM mp2);
void BusyPointer(BOOL state);
void DEBUG(char *,...);

void ErrorMsg( char *txt, ... );
void Message( char *txt, ... );


/*** Variables ****************************************************************/

extern	LONG		cxChar, cxCaps, cyChar, cyDesc,
					desk_width,desk_height;


#endif /* STUB_H */

