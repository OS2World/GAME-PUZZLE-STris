/*******************************************************************************
*																			   *
* TIMER.C																	   *
* -------																	   *
*																			   *
* Reservieren und freigeben des Systemtimers.								   *
*																			   *
* Modification History: 													   *
* --------------------- 													   *
*																			   *
* 14.04.95	RHS  Extracted this file from STris.c							   *
*																			   *
*******************************************************************************/

#define INCL_WIN
#include <os2.h>

#include "timer.h"


/*** Defines ******************************************************************/

/*** Prototypes ***************************************************************/

/*** Variables ****************************************************************/

static	BOOL	GotTimer;



/*******************************************************************************
* AllocTimer(hwnd,interval)
* Allocate and run timer with specified interval
* hwnd	   = ClientWindow to attach timer to
* interval = Time interval [ms]
*******************************************************************************/

ULONG AllocTimer(HAB hab, HWND hwnd, ULONG interval)
{
	/* Free Timer if alredy running */

	if( GotTimer )		FreeTimer( hab, hwnd );


	/* Allocate new Timer */

	if( WinStartTimer(hab,hwnd,ID_TIMER,60*interval) )
		GotTimer = TRUE;
	else
		GotTimer = FALSE;

	return GotTimer;
}


/*******************************************************************************
* FreeTimer()
* Stop and free Timer allocated with AllocTimer()
*******************************************************************************/

void FreeTimer(HAB hab,HWND hwnd)
{
	if( GotTimer )
	{
		WinStopTimer(hab,hwnd,ID_TIMER);
		GotTimer = FALSE;
	}
}


/*******************************************************************************
* TickTimer()
* Send a WM_TIMER Message to main-application
*******************************************************************************/

void TickTimer(HWND hwnd)
{
	if( GotTimer )
		WinPostMsg(hwnd,WM_TIMER,(MPARAM)0,(MPARAM)0);
}


