#ifndef HELP_H
#define HELP_H



/*** Variables ****************************************************************/

extern	HWND	hwndHelpInstance;
extern	BOOL	fHelpAvailable;


/*** Prototypes ***************************************************************/

BOOL OpenHelp(void);
void CloseHelp(void);
void DisplayHelpPanel(LONG sIdPanel);

ULONG HelpForHelp(HWND hwnd,ULONG msg,MPARAM mp1, MPARAM mp2);
ULONG HelpContents(HWND hwnd,ULONG msg,MPARAM mp1, MPARAM mp2);
ULONG HelpIndex(HWND hwnd,ULONG msg,MPARAM mp1, MPARAM mp2);
ULONG HelpKeys(HWND hwnd,ULONG msg,MPARAM mp1, MPARAM mp2);
ULONG HelpMain(HWND hwnd,ULONG msg,MPARAM mp1, MPARAM mp2);
ULONG HelpHowToPlay(HWND hwnd,ULONG msg,MPARAM mp1, MPARAM mp2);




#endif /* HELP_H */

