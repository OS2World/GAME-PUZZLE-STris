/*******************************************************************************
*																			   *
* HISCWINDOW.H																   *
* ------------																   *
*																			   *
* Include File for HISCWINDOW.C 											   *																			  *
*																			   *
*******************************************************************************/

#ifndef HISCWINDOW_H
#define HISCWINDOW_H


/*** Defines ******************************************************************/


/*** Prototypes ***************************************************************/

char *GetUserName(void);
ULONG ShowHiscoreFunction(HWND hwnd,ULONG msg,MPARAM mp1, MPARAM mp2);
ULONG ShowHiscoreFunctionHilite(HWND hwnd, ULONG);


/*** Variables ****************************************************************/



#endif /* HISCWINDOW_H */

