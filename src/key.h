/*******************************************************************************
*																			   *
* KEY.H 																	   *
* ----- 																	   *
*																			   *
* Include File for KEY.C													   *																			  *
*																			   *
*******************************************************************************/

#ifndef KEY_H
#define KEY_H


/*** Defines ******************************************************************/

enum _KeyFunctions				/* Don't change order !!!!!!!		*/
{
	KEY_LEFT=0,
	KEY_RIGHT,
	KEY_ROTATE,
	KEY_ROTATE2,
	KEY_DROP,
	KEY_RESERVED,

	KEY_NUM
};

typedef struct _KEYSTRUCT
{
	USHORT	usQualifier,
			usKeyCode;
	char	*szKeyText;
} KEYSTRUCT;

typedef KEYSTRUCT *PKEYSTRUCT;


typedef struct _KEYPREFS
{
	USHORT	usQualifier,
			usKeyCode;
} KEYPREFS;

typedef KEYPREFS *PKEYPREFS;


typedef struct _KEYINFO 		/* Used for plausibility check of key */
{
	SHORT	sKeyCode;
	char	*szKeyText;
} KEYINFO;

typedef KEYINFO *PKEYINFO;



/*** Prototypes ***************************************************************/

void InitKeymap(void);
void SetKeymap(void);
SHORT MapKey2Function(USHORT);
ULONG KeyFunction(HWND hwnd,ULONG msg,MPARAM mp1, MPARAM mp2);


/*** Variables ****************************************************************/


#endif /* KEY_H */

