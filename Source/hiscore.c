/***********************************************************************
* Program: Hiscore.c (V0.92)										   *
* Date	 : 15. M„rz 1995 (18.03 20.03)								   *
*																	   *
* Authors: Th. Sch„r & R. Straub									   *
* Address: Schlattweg 4, CH-4147 Aesch BL							   *
* Phone  : +41 (0)61-751 58 77										   *
* Email  : ec93scha@htlulx.htl-bw.ch								   *
*																	   *
* Note	 : Hiscore-Verwaltung fr S-Tris							   *
*																	   *
* Modification History												   *
*																	   *
* 19.04.95	RHS  Removed ANSI-C -> uses now OS/2 Functions			   *
* 27.04.95	RHS  Fixed Bug in SaveHiscore. Couldn't create new file    *
*				 Added ClearHiscore to set Playername to "..."		   *
*																	   *
***********************************************************************/

#define INCL_DOS
#include <os2.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hiscore.h"



/*** Variables ****************************************************************/

static struct Player_Entry	  ScoreList[max_entries];



/*** Prototypes ***************************************************************/

static	void ClearHiscore(void);




/*******************************************************************************
* LoadHiscore(Filename)
* L„dt Hiscore aus File Filename
* Parameter : Filename
* Return	: hsc_OK wenn alles OK
*******************************************************************************/

ULONG LoadHiscore(char *filename)
{
	APIRET	rc;
	HFILE	datei;
	ULONG	action,kenn,len;




	ClearHiscore();

	rc = DosOpen(filename,						/* File path name */
			 &datei,							/* File handle */
			 &action,							/* Action taken */
			 0, 								/* File primary allocation */
			 0, 								/* File attribute */
			 OPEN_ACTION_OPEN_IF_EXISTS,		/* Open function type */
			 OPEN_FLAGS_SEQUENTIAL | OPEN_FLAGS_FAIL_ON_ERROR |
			 OPEN_SHARE_DENYREADWRITE | OPEN_ACCESS_READONLY,
			 NULL); 							/* No extended attributes */

	if(rc)		return hsc_FILE_NOT_FOUND;

	rc = DosRead(datei,&kenn,sizeof(kenn),&len);
	if( len != sizeof(kenn) || kenn != ID_HEADER )
	{
		DosClose( datei );
		return hsc_INVALID_FILE;
	}

	rc = DosRead(datei,&kenn,sizeof(kenn),&len);
	if( len != sizeof(kenn) || kenn != ID_VERSION )
	{
		DosClose(datei);
		return hsc_INVALID_VERSION;
	}

	rc = DosRead(datei,&ScoreList,sizeof(struct Player_Entry)*max_entries,&len);
	if( len != sizeof(struct Player_Entry)*max_entries )
	{
		DosClose(datei);
		return hsc_READ_ERROR;
	}

	DosClose(datei);
	return hsc_OK;
}



/**************************************************************************
* SaveHiscore(Filename)
* Speichert Hiscore in File Filename
* Parameter : Filename
* Return	: 0=nicht gespeichert, 1=gespeichert
**************************************************************************/

ULONG SaveHiscore(char *filename)
{
	APIRET	rc;
	HFILE	datei;
	ULONG	action,kenn,len;


	rc = DosOpen(filename,						/* File path name */
			 &datei,							/* File handle */
			 &action,							/* Action taken */
			 0, 								/* File primary allocation */
			 0, 								/* File attribute */
			 OPEN_ACTION_CREATE_IF_NEW | OPEN_ACTION_OPEN_IF_EXISTS,		/* Open function type */
			 OPEN_FLAGS_SEQUENTIAL | OPEN_FLAGS_FAIL_ON_ERROR |
			 OPEN_SHARE_DENYREADWRITE | OPEN_ACCESS_WRITEONLY ,
			 NULL); 							/* No extended attributes */

	if(rc)		return hsc_OPEN_FILE_ERROR;

	kenn = ID_HEADER;
	rc = DosWrite(datei,&kenn,sizeof(kenn),&len);
	if( len != sizeof(kenn) )
	{
		DosClose( datei );
		return hsc_WRITE_ERROR;
	}


	kenn = ID_VERSION;
	rc = DosWrite(datei,&kenn,sizeof(kenn),&len);
	if( len != sizeof(kenn) )
	{
		DosClose(datei);
		return hsc_WRITE_ERROR;
	}

	rc = DosWrite(datei,&ScoreList,sizeof(struct Player_Entry)*max_entries,&len);
	if( len != sizeof(struct Player_Entry)*max_entries )
	{
		DosClose(datei);
		return hsc_WRITE_ERROR;
	}

	DosClose(datei);
	return hsc_OK;
}




/**************************************************************************
* ClearHiscore(void)
* Ganze Hiscoreliste l”schen
**************************************************************************/

static void ClearHiscore(void)
{
	LONG	i;


	memset( &ScoreList,0,sizeof(ScoreList));

	for(i=0;i<max_entries;i++)
		strcpy(ScoreList[i].Name,"..." );
}




/**************************************************************************
* GetPosition(Score)
* Position suchen an der Score zu finden w„re. 1. Eintrag = 1
* Parameter : Score
* Return	: Position, 0=nicht in Hiscore
**************************************************************************/

ULONG GetPosition(ULONG NewScore)
{
	ULONG	i;

	if( NewScore == 0 ) return 0;	/* Score 0 -> kein Eintrag */

	for(i=0;i<max_entries;i++)
	{
		if (ScoreList[i].Score <= NewScore)
		{
			return i+1;    /* Platz 1 bekommt auch Wert 1 */
		}
	}

	return 0;				/* Rckgabe NULL, wenn nicht in Hiscoreliste */
}


/**************************************************************************
* GetHiscore()
* Den aktuellen Hiscore zurckgeben.
* Parameter : nix
* Return	: Hiscore
**************************************************************************/

ULONG GetHiscore(void)
{
	return ScoreList[0].Score;
}



/**************************************************************************
* GetEntry(Position)
* Zeiger auf Hiscoredaten des gewnschten Eintrages liefern.
* Parameter : Position
* Return	: Zeiger auf struct Player_Entry
**************************************************************************/

struct Player_Entry *GetEntry(ULONG pos)
{
	return &ScoreList[pos];
}


/**************************************************************************
* InsertScore(Position,Name,Score)
* Fgt neuer Name an Position ein
* Parameter : Position Name Score
* Return	: keine
**************************************************************************/

void InsertScore(ULONG Position,struct Player_Entry *entry)
{
   ULONG	i;


   /* Position bezeichnet den Rang und nicht den Index */

   if (!Position) return;

   Position--;

   for(i=max_entries-1;i>Position;i--)
	  memcpy(&ScoreList[i],&ScoreList[i-1],sizeof(struct Player_Entry));

//	memcpy( &ScoreList[Position], entry, sizeof( entry ));

	strcpy( ScoreList[Position].Name, entry->Name );
	ScoreList[Position].Score = entry->Score;
	ScoreList[Position].Level = entry->Level;
	ScoreList[Position].Lines = entry->Lines;
}



