/*******************************************************************************
*																			   *
* PLAYFIELD.C																   *
* -----------																   *
*																			   *
* Create and handle Playfield area. 										   *
*																			   *
* Modification History: 													   *
* --------------------- 													   *
*																			   *
* 14.04.95	RHS  Extracted this file from STris.c							   *
* 08.09.95	RHS  New scoring modes implemented								   *
* 08.11.95	RHS  Fixed Bug in BuildStartLevel								   *
*																			   *
*******************************************************************************/

#define INCL_WIN
#define INCL_GPI

#include <os2.h>
#include <stdlib.h>
#include <string.h>

#include "stris.h"
#include "window.h"
#include "pieces.h"
#include "hiscore.h"
#include "hiscwindow.h"
#include "timer.h"
#include "sound.h"
#include "stub.h"
#include "preferences.h"
#include "key.h"
#include "stris_id.h"
#include "playfield.h"


/*** Defines ******************************************************************/


/*** Prototypes ***************************************************************/


/*** Variables ****************************************************************/

		LONG		Score,Hiscore,Lines,Level,
					LastScore,LastHiscore,LastLines,LastLevel;
		ULONG		GameSpeed;
		BYTE		PlayField[NUM_PIECES_Y][NUM_PIECES_X];
		BOOL		Pause,LockControl,OnGame,GameOver,
					fNewHiscore;


/*** Functions ****************************************************************/


void ChangeScore(LONG lScoreChange)
{
	Score += lScoreChange;

	if( Score > Hiscore )
	{
		Hiscore = Score;

		if( !fNewHiscore )
		{
			fNewHiscore = TRUE;

//			PlayMusic(WAV_NEWHISCORE);
		}
	}
}



void BuildStartLevel(void)
{
	ULONG	y,x;


	for(y=0;y<STrisPrefs.StartLevel;y++)
	{
		for(x=0;x<NUM_PIECES_X;x++)
		{
			if( !(rand()%3) )
				PlayField[NUM_PIECES_Y-1-y][x] = rand() % NUM_PIECES+1;
		}
	}
}



void ClearPlayField(void)
{
	ULONG	x,y;


	ActPiece = -1;

	for(y=0;y<NUM_PIECES_Y;y++)
	{
		for(x=0;x<NUM_PIECES_X;x++)
		{
			PlayField[y][x] = 0;
		}
	}
}


void PaintPlayField(HPS hps)
{
	ULONG	x,y;


	for(y=0;y<NUM_PIECES_Y;y++)
	{
		for(x=0;x<NUM_PIECES_X;x++)
		{
			PaintBlock(hps,x,y,PlayField[y][x]);
		}
	}

//	DrawPiece(hps);
}


void CheckFullLine(HPS hps)
{
	LONG	x,y,y2,filled,
			line_multiplier,			// Multiplier for completed lines
			fall_bonus,
			xPiece,yPiece;				// Position of Piece before falling



	// Alle Zeilen durchgehen

	line_multiplier = 1;

	for(y=NUM_PIECES_Y-1;y>=0;y--)
	{
		// Spalten absuchen

		filled = TRUE;

		for(x=0;x<NUM_PIECES_X;x++)
		{
			if( !PlayField[y][x] )
			{
				filled = FALSE;
				break;
			}
		}

		// Wenn Zeile ganz gefllt ist scrollen wir alles oberhalb
		// dieser Zeile um 1 Zeile nach unten

		if( filled )
		{
			PlayMusic(WAV_GLASS);

			// Scroll 1 line down, insert blank line on top

			for(y2=y;y2>0;y2--)
			{
				for(x=0;x<NUM_PIECES_X;x++)
					PlayField[y2][x] = PlayField[y2-1][x];
			}
			for(x=0;x<NUM_PIECES_X;x++) PlayField[0][x] = 0;

			PaintPlayField(hps);


			// Check this *new* line once again in case more than one
			// line has been filled up.

			y++;


			// Increase Score, Lines etc.
			// Speed'up game if necessary

			// Scoring modes.
			// 1. 100 points per line multiplied by current level
			// 2. 10 points for every line the piece fell down
			// 3. Every completed lines doubles the next score


			Lines++;							// Number of lines destroyed

			GetFallPiecePos(&xPiece,&yPiece);
			if(yPiece>=0)
				fall_bonus = max(0,y-yPiece);		// see 2.
			else
				fall_bonus = 0;

			ChangeScore( (100+fall_bonus)*(Level+1)*line_multiplier );

			if( Lines % NEXT_LEVELS == 0 )
			{
//				  PlayMusic(WAV_DING);
//				ClearPlayField();
//				BuildStartLevel();
//				PaintPlayField(hps);

				Level++;
				if( GameSpeed > 2 ) GameSpeed--;
			}

			line_multiplier <<= 1;

			// Print new informations

			UpdateTextBlock(hps,PRT_UPDATE_CHANGES);
		}
	}
}



void HandleKeys( USHORT key )
{
	USHORT usFunction;


	// If piece is dropping and user pressed a key, we stop the fall

	if( LockControl )
	{
		AllocTimer( hab, hwndClient, GameSpeed );
		LockControl = FALSE;
	}

//	Message("key %d",key );


	usFunction = MapKey2Function( key );
	switch( usFunction )
	{
		case KEY_LEFT:
			MovePiece(-1);
			break;

		case KEY_RIGHT:
			MovePiece(1);
			break;

		case KEY_DROP:
			FallDownPiece();
			break;

		case KEY_ROTATE:
			RotatePiece( STrisPrefs.fRotateFlag ? 1 : 3);
			break;

		case KEY_ROTATE2:
			RotatePiece( STrisPrefs.fRotateFlag ? 3 : 1);
			break;
	}
}



/*******************************************************************************
* SetPause()
* Set Game State. TRUE -> Pause ON, FALSE -> Pause OFF
* This function sets the CheckBox to the specified state and returns the
* old state.
*******************************************************************************/

BOOL SetPause( BOOL state )
{
	BOOL	OldState;


	// If there is no change we simply do nothing

	if( state == Pause )	return Pause;


	// Store last state and switch to new state (that should always toggle)

	OldState	= Pause;
	Pause		= state;

	WinCheckButton(hwndClient,IDF_PAUSE,state);


	return OldState;
}


/*******************************************************************************
* PauseFunction()
* Toggle Pausemode on/off
*******************************************************************************/

ULONG PauseFunction(HWND hwnd,ULONG msg,MPARAM mp1, MPARAM mp2)
{
	if( WinQueryButtonCheckstate(hwnd,IDF_PAUSE) )
		SetPause(FALSE);
	else
		SetPause(TRUE);

	return TRUE;
}



/*******************************************************************************
* NewGameFunction(msg parameters)
* Restart Game
*******************************************************************************/

ULONG NewGameFunction(HWND hwnd,ULONG msg,MPARAM mp1, MPARAM mp2)
{
	HPS 	hps;


	// If there's currently a game running we ask for termination

	if( OnGame )
	{
		if( WinMessageBox(HWND_DESKTOP,hwnd,
			"Do want to abort the current game ?",
			FULL_NAME,0,MB_YESNO|MB_ICONQUESTION|MB_MOVEABLE) == MBID_YES )
		{
			FinishGame();
		}
		return TRUE;
	}


	WinSetWindowText( WinWindowFromID( hwndClient, IDF_NEW_GAME ),"~Stop Game" );


	// Set Game Variables

	Score			= 0;
	Lines			= 0;
	Hiscore 		= GetHiscore();
	Level			= STrisPrefs.StartLevel;
	GameSpeed		= 12-STrisPrefs.StartSpeed;
	fNewHiscore 	= FALSE;


	// Set up Window

	hps = WinGetPS(hwnd);

	ClearPlayField();
	BuildStartLevel();
	PaintPlayField(hps);

	AllocTimer( hab, hwnd, GameSpeed );

	// Select first piece

	GetNewPiece(hps);
	GetNewPiece(hps);
	DrawPiece(hps);
	UpdateTextBlock( hps, PRT_UPDATE_ALL );

	WinReleasePS(hps);


	// Set Game State to : ON

	GameOver	= FALSE;
	OnGame		= TRUE;
	SetPause( FALSE );

	PlayMusic(WAV_BREAKIT);

	return TRUE;
}



/*******************************************************************************
* EnterNameFunction()
* Display the Aboutrequester
*******************************************************************************/

void FinishGame(void)
{
	struct	Player_Entry	entry;
	char	*name;
	ULONG	position;


	/* Spiel pausieren */

	OnGame = FALSE;
	FreeTimer( hab, hwndClient );
	SetPause( TRUE );


//	PlayMusic(WAV_DING);

	/* Haben wir einen Hiscore ? */

	position = GetPosition( Score );
	if( position )
	{
		PlayMusic(WAV_DING);

		name = GetUserName();
		strncpy( entry.Name,name,sizeof(entry.Name) );
		entry.Score = Score;
		entry.Level = Level;
		entry.Lines = Lines;
		InsertScore( position, &entry );

		ShowHiscoreFunctionHilite(hwndClient,position);
	}

	WinSetWindowText( WinWindowFromID( hwndClient, IDF_NEW_GAME ), "~Start Game" );
}


