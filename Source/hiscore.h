/*******************************************************************************
*																			   *
* HISCORE.H 																   *
* --------- 																   *
*																			   *
* Include File for HISCORE.C												   *																			  *
*																			   *
*******************************************************************************/

#ifndef HISCORE_H
#define HISCORE_H


/*** Defines ******************************************************************/

#define HISCORE_FILE	"STris.hsc"

#define name_len	 32
#define max_entries  10

#define TRUE		 1
#define FALSE		 0

#define MAKEID(a,b,c,d) ((ULONG)(a<<24 | b<<16 | c<<8 | d))

#define ID_HEADER	MAKEID('S','T','R','S')
#define ID_VERSION	MAKEID('V','1','0','6')



/*** Structures ****************************************************************/

enum hsc_Errors
{
	hsc_OK,
	hsc_FILE_NOT_FOUND,
	hsc_INVALID_FILE,
	hsc_INVALID_VERSION,
	hsc_READ_ERROR,
	hsc_WRITE_ERROR,
	hsc_OPEN_FILE_ERROR
};



struct Player_Entry
{
   char 	Name[name_len];
   ULONG	Score,Lines,Level;
};



/*** Prototypes ***************************************************************/

void InsertScore(ULONG Position,struct Player_Entry *entry);
ULONG GetPosition(ULONG NewScore);
ULONG LoadHiscore(char *filename);
ULONG SaveHiscore(char *filename);
ULONG GetHiscore(void);
struct Player_Entry *GetEntry(ULONG pos);


/*** Variables ****************************************************************/


#endif /* HISCORE_H */

