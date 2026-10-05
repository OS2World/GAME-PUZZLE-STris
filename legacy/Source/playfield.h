/*******************************************************************************
*																			   *
* PLAYFIELD.H																   *
* -----------																   *
*																			   *
* Include File for PLAYFIELD.C												   *																			  *
*																			   *
*******************************************************************************/

#ifndef PLAYFIELD_H
#define PLAYFIELD_H



/*** Defines ******************************************************************/

#define NUM_PIECES_X	10
#define NUM_PIECES_Y	24

#define NUM_PIECES		7

#define MAX_SPEED		10
#define MAX_LEVEL		16


/*** Structures ***************************************************************/

struct	Block
{
	char	x,y,color;
};

struct	Piece
{
	struct	Block	Block[4][4];
};


/*** Variables ****************************************************************/

extern	LONG		Score,Hiscore,Lines,Level,
					LastScore,LastHiscore,LastLines,LastLevel;
extern	ULONG		GameSpeed;
extern	BYTE		PlayField[NUM_PIECES_Y][NUM_PIECES_X];
extern	BOOL		Pause,LockControl,OnGame,GameOver,
					fNewHiscore;


/*** Prototypes ***************************************************************/

void ChangeScore(LONG);
void ClearPlayField(void);
void PaintPlayField(HPS hps);
void CheckFullLine(HPS hps);
BOOL CheckTopLine(void);

ULONG PauseFunction(HWND hwnd,ULONG msg,MPARAM mp1, MPARAM mp2);
BOOL SetPause( BOOL state );

void HandleKeys( USHORT key );

ULONG NewGameFunction(HWND hwnd,ULONG msg,MPARAM mp1, MPARAM mp2);
void FinishGame(void);


#endif /* PLAYFIELD_H */

