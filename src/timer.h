/*******************************************************************************
*																			   *
* TIMER.H																	   *
* -------																	   *
*																			   *
* Include File for TIMER.C													   *
*																			   *
*******************************************************************************/

#ifndef TIMER_H
#define TIMER_H


/*** Defines ******************************************************************/

#define ID_TIMER	1


/*** Prototypes ***************************************************************/

ULONG AllocTimer(HAB hab, HWND hwnd, ULONG interval);
void FreeTimer(HAB hab, HWND hwnd);
void TickTimer(HWND hwnd);


/*** Variables ****************************************************************/



#endif /* TIMER_H */

