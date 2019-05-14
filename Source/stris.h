#ifndef STRIS_H
#define STRIS_H


/*** Program Information ******************************************************/

#define PRG_NAME	"STris"
#define VERSION 	"1"
#define REVISION	"45"
#define AUTHOR		"Ren‚ Straub"
#define DATE		"20.4.96"

#define FULL_NAME	(PRG_NAME" "VERSION"."REVISION" by "AUTHOR" ("DATE")")


//#define CODE_PRG						// Set this when creating Codegenerator


/*** Error Codes **************************************************************/

#define RC_NORMAL		0
#define RC_WARNING		10
#define RC_ERROR		20



/*** Screen Geometrics ********************************************************/

#define BORDER			12

#define LABEL_WIDTH 	130
#define LABEL_HEIGHT	75


#define NEXT_LEVELS 	10		// Increment Speed after 10 Lines



/*** Other Defines ************************************************************/

#define STAT_OFF				// Set STAT_ON to enable Statistics


/*** Message Handling, Function ID's ******************************************/

struct IDCommandList
{
	ULONG	idl_Id;
	ULONG	(*idl_Function)(HWND,ULONG,MPARAM,MPARAM);
};


/*** Variables ****************************************************************/

extern	HAB 		hab;


/*** Prototypes ***************************************************************/

void cleanup(int);

MRESULT EXPENTRY ClientWndProc( HWND, ULONG, MPARAM, MPARAM );
BOOL SetPause( BOOL );


#endif /* STRIS_H */

