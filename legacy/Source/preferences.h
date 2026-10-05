/*******************************************************************************
*																			   *
* PREFERENCES.H 															   *
* ------------- 															   *
*																			   *
* Include File for PREFERENCES.C											   *																			  *
*																			   *
*******************************************************************************/

#ifndef PREFERENCES_H
#define PREFERENCES_H

#ifndef KEY_H
#include "key.h"
#endif


/*** Defines ******************************************************************/

struct PrefsStruct
{
	BOOL		fSoundState,
				fGridFlag,
				fShowNextPiece,
				fRotateFlag,
				fRemainPaused,
				fSolidColor;

	LONG		StartSpeed,
				StartLevel,
				Palette;

	char		szRegistration[64],
				szUsername[32];

	KEYPREFS	Keys[KEY_NUM];

	RECTL		win_rcl,
				opt_rcl,
				hsc_rcl,
				abt_rcl,
				ent_rcl,
				key_rcl,
				reg_rcl,
				nerv_rcl;
};




/*** Prototypes ***************************************************************/

BOOL LoadPrefs(void);
BOOL SavePrefs(void);

void StoreWindowPos(HWND hwnd, PRECTL rectl);
void RestoreWindowPos(HWND hwnd, PRECTL rectl);



/*** Variables ****************************************************************/

extern	struct	PrefsStruct STrisPrefs;


#endif /* PREFERENCES_H */

