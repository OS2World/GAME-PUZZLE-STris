/*******************************************************************************
*																			   *
* PIECES.C																	   *
* --------																	   *
*																			   *
* Handling for Pieces														   *
*																			   *
* Modification History: 													   *
* --------------------- 													   *
*																			   *
* 14.04.95	RHS  Extracted this file from STris.c							   *
* 17.04.95	RHS  New placement for 'Next Piece' Element 					   *
* 21.04.95	RHS  Removed Pieces-Ressource. Pieces are now drawn into memory    *
* 23.04.95	RHS  Recursionbug in GetNewPiece() removed. Failed if NextPiece=-1 *
* 09.05.95	RHS  Score for every Piece fallen down							   *
*																			   *
*******************************************************************************/

#define INCL_WIN
#define INCL_GPI

#include <os2.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "pieces.h"
#include "stris.h"
#include "window.h"
#include "playfield.h"
#include "timer.h"
#include "sound.h"
#include "stub.h"
#include "preferences.h"

#include "piece_data.h"


/*** Defines ******************************************************************/

#define FALL_DELAY_CNT		2


/*** Prototypes ***************************************************************/

static BOOL CheckCollision( LONG x, LONG y, LONG angle );


/*** Variables ****************************************************************/

		LONG		PieceWidth,PieceHeight,
					PieceBorder;
		LONG		ActPiece=-1;

static	HPS 		hpsMemory;
static	HBITMAP 	hbmPieces;
static	HDC 		hdcMemory;
static	BITMAPINFOHEADER2	bmp;
static	HBITMAP 	hbm;
static	SIZEL		sizl;
static	LONG		xPos,yPos,				// Current position of Piece
					LastxPos,LastyPos,		// Last ....
					xFallPos,yFallPos;		// Position when Piece was fallen
static	LONG		NextPiece=-1,ActAngle;
static	BOOL		fLastMove,
					fPlaced;


static	POINTL	npOffset[] =		// Offset for Piece in NextPieceWindow
{									// Offset = PieceWidth(Height)/2
	3,0,
	2,1,
	3,2,
	4,1,
	2,2,
	3,2,
	3,2
};

static LONG ColorMapStandard[] =			// Standard
{
	0x666666,		// GridLine
	0x00DD00,		// Piece 0
	0xEE0000,
	0xFFCC00,
	0x0055DD,
	0x00DDFF,
	0xCC00EE,
	0xFF6600		// Piece 6
};

static LONG ColorMapRedYellow[] =			// Red->Yellow
{
	0x666666,		// GridLine
	0xFF3300,		// Piece 0
	0xFF5500,
	0xFF7700,
	0xFF9900,
	0xFFBB00,
	0xFFDD00,
	0xFFEE00		// Piece 6
};

static LONG ColorMapGreenYellow[] = 		// Green->Yellow
{
	0x666666,		// GridLine
	0x00DD00,		// Piece 0
	0x66DD00,
	0x88DD00,
	0xAAEE00,
	0xCCEE00,
	0xEEEE00,
	0xFFEE00		// Piece 6
};

static LONG ColorMapBlue[] =				// Blue
{
	0x666666,		// GridLine
	0x002288,		// Piece 0
	0x004499,
	0x0066AA,
	0x0088BB,
	0x00AACC,
	0x00BBDD,
	0x00DDEE		// Piece 6
};

static LONG ColorMapGrayscale[] =			// Grayscale
{
	0x555555,		// GridLine
	0x333333,		// Piece 0
	0x444444,
	0x555555,
	0x666666,
	0x777777,
	0x888888,
	0x999999		// Piece 6
};


static LONG ColorMapBW[] =					// Black & White
{
	0x555555,		// GridLine
	0x888888,		// Piece 0
	0x888888,
	0x888888,
	0x888888,
	0x888888,
	0x888888,
	0x888888		// Piece 6
};


static	LONG *ColorMap[] =
{
	ColorMapStandard,
	ColorMapRedYellow,
	ColorMapGreenYellow,
	ColorMapBlue,
	ColorMapGrayscale,
	ColorMapBW
};




/*** Functions ****************************************************************/


/*******************************************************************************
* GetFallPiecesPos()
* Returns the position of the piece before it felt down.
*******************************************************************************/

void GetFallPiecePos(LONG *x, LONG *y)
{
	*x = xFallPos;
	*y = yFallPos;
}


/*******************************************************************************
* SetPiecesSize()
* Set the correct piece-size respecting the Dimensions of the Desktop
*******************************************************************************/

void SetPieceSize(void)
{
	PieceWidth	=
	PieceHeight = 16;
	PieceBorder = 1;

	if( desk_width > 800 )
	{
		PieceWidth	=
		PieceHeight = 20;
		PieceBorder = 1;
	}
	else if( desk_width > 1024 )
	{
		PieceWidth	=
		PieceHeight = 24;
		PieceBorder = 2;
	}
}



/*******************************************************************************
* PaintRectElem(hps,x,y,num)
* Paint Element (part of a piece) num at position (x,y)
* hps = Presentation space
* x   = XPos (Pixel)
* y   = YPos (Pixel)
* num = Element-Number (-> Color)
*******************************************************************************/

static void PaintRectElem( HPS hps, LONG x, LONG y, BYTE num )
{
	POINTL	aptl[3];


	aptl[0].x = x;
	aptl[0].y = y;
	aptl[1].x = x+PieceWidth;
	aptl[1].y = y+PieceHeight;
	aptl[2].x = num*PieceWidth;
	aptl[2].y = 0;

	GpiBitBlt(hps,hpsMemory,3,aptl,ROP_SRCCOPY,BBO_AND);
}



/*******************************************************************************
* PaintBlock(hps,x,y,num)
* Paint Element in Playfield at logical position (x,y), (0,0) = Top,Left
* hps = Presentation space
* x   = XPos (Logical)
* y   = YPos (Logical)
* num = Element-Number (-> Color)
*******************************************************************************/

void PaintBlock( HPS hps, LONG x, LONG y, BYTE num )
{
	PaintRectElem(hps,pfLeft+x*PieceWidth,pfTop-(y+1)*PieceHeight,num);
}



/*******************************************************************************
* PaintNextPiece(hps)
* Draw the next-coming piece in the window
* hps = Presentation space
*******************************************************************************/

void PaintNextPiece(HPS hps)
{
	struct	Block	*block;
	POINTL			ptl;
	ULONG			i;


	// Clear Rectangle

	GpiSetColor(hps,CLR_PALEGRAY);
	ptl.x = npLeft;
	ptl.y = npTop;
	GpiMove(hps,&ptl);

	ptl.x += npWidth-1;
	ptl.y += npHeight-1;
	GpiBox(hps,DRO_OUTLINEFILL,&ptl,0,0);


	if( !STrisPrefs.fShowNextPiece || NextPiece == -1 ) return; // || !OnGame ) 	return;


	// Draw Piece

	for(i=0;i<4;i++)
	{
		block	= &Pieces[NextPiece].Block[0][i];

		PaintRectElem(hps,npLeft+block->x*PieceWidth+
					  npOffset[NextPiece].x*PieceWidth/2,
					  npTop+npHeight-(block->y+1)*PieceHeight-
					  npOffset[NextPiece].y*PieceHeight/2,
					  block->color);
	}
}




/*******************************************************************************
* GeneratePieces(hps)
* Generate the pieces in the desired size and color into memoryPS
*******************************************************************************/

static void DrawBorderLine(LONG x, LONG y, LONG width, LONG height )
{
	POINTL	ptl;


	GpiSetColor(hpsMemory,CLR_WHITE );
	ptl.x	= x;
	ptl.y	= y;
	GpiMove( hpsMemory,&ptl );
	ptl.y	+= height;
	GpiLine( hpsMemory,&ptl );
	ptl.x	+= width;
	GpiLine( hpsMemory,&ptl);
	GpiSetColor(hpsMemory,CLR_BLACK );
	ptl.y -= height;
	GpiLine( hpsMemory, &ptl);
	ptl.x -= width;
	GpiLine( hpsMemory, &ptl);
}


void GeneratePieces(void)
{
	POINTL	ptl;
	RECTL	rcl;
	LONG	i,j,
			lColMode;



	lColMode = STrisPrefs.fSolidColor ? LCOL_PURECOLOR : 0;

	GpiCreateLogColorTable(hpsMemory,lColMode,LCOLF_CONSECRGB,0,8,		//10
						   ColorMap[STrisPrefs.Palette] );

	rcl.xLeft	= 0;
	rcl.yBottom = 0;
	rcl.xRight	= PieceWidth;
	rcl.yTop	= PieceHeight;
	WinFillRect(hpsMemory,&rcl,CLR_PALEGRAY );

	if( STrisPrefs.fGridFlag )
	{
		GpiSetColor(hpsMemory,0);

		ptl.x = 0;
		ptl.y = 0;
		GpiMove(hpsMemory,&ptl);
		ptl.x += PieceWidth-1;
		GpiLine(hpsMemory,&ptl);
		ptl.y += PieceHeight-1;
		GpiLine(hpsMemory,&ptl);
	}

	for(i=1;i<=NUM_PIECES;i++)
	{
		rcl.xLeft	= i*PieceWidth;
		rcl.yBottom = 0;
		rcl.xRight += PieceWidth;
		rcl.yTop	= PieceHeight;

		WinFillRect(hpsMemory,&rcl,i );

		if( i>0 )
		{
			for(j=0;j<PieceBorder;j++)
				DrawBorderLine(i*PieceWidth+j,j,PieceWidth-1-2*j,PieceHeight-1-2*j);
		}
	}
}



/*******************************************************************************
* InitPieceBitmap()
* Initialize the MemoryPS for our PieceSet
* Return : TRUE  all ok.
*		   FALSE something went wrong
*******************************************************************************/

BOOL InitPieceBitmap(void)
{
	// Initialize PS, DC and Bitmap

	hdcMemory	= DevOpenDC(hab,OD_MEMORY,"*",0L,NULL,0);
	if( !hdcMemory )	return FALSE;

	sizl.cx 	= 0;
	sizl.cy 	= 0;
	hpsMemory	= GpiCreatePS(hab, hdcMemory, &sizl, PU_PELS|GPIF_DEFAULT|
							  GPIT_MICRO|GPIA_ASSOC );
	if( !hpsMemory )	return FALSE;

	memset(&bmp,0,sizeof(BITMAPINFOHEADER2));
	bmp.cbFix		= sizeof(BITMAPINFOHEADER2);
	bmp.cx			= (NUM_PIECES+1)*PieceWidth;
	bmp.cy			= PieceHeight;
	bmp.cPlanes 	= 1;
	bmp.cBitCount	= 8;
	hbm 			= GpiCreateBitmap( hpsMemory, &bmp, 0L, 0L, NULL );
	if( !hbm )			return FALSE;

	GpiSetBitmap(hpsMemory,hbm);


	// Draw Pieces

	GeneratePieces();

	return TRUE;
}




/*******************************************************************************
* ClosePieceBitmap()
* Close the memoryPS and it's associated handles
*******************************************************************************/

void ClosePieceBitmap(void)
{
	// Destroy PS,DC and Bitmap

	if( hpsMemory )
	{
		GpiDestroyPS(hpsMemory);
//		hpsMemory = NULLHANDLE;
	}

	if( hdcMemory )
	{
		DevCloseDC(hdcMemory);
//		hdcMemory = NULLHANDLE;
	}

	if( hbm )
	{
		GpiDeleteBitmap(hbm);
//		hbm = NULLHANDLE;
	}
}






/*******************************************************************************
* GetNewPiece(hps)
* Select a new piece and place it on the top of our playfield.
* hps = Presentation space
*******************************************************************************/

BOOL GetNewPiece(HPS hps)
{
	// Fill in NextPiece for first usage

	if( NextPiece == -1 )
		NextPiece = rand() % NUM_PIECES;

	ActPiece	= NextPiece;
	NextPiece	= rand() % NUM_PIECES;

	AllocTimer( hab, hwndClient, GameSpeed );


	// Initialization

	ActAngle	= 0;

	xPos		= NUM_PIECES_X/2;
	yPos		= 0;

	LastxPos	= -100;
	LastyPos	= -100;

	xFallPos	= -1;
	yFallPos	= -1;

	fLastMove	= FALSE;
	fPlaced 	= FALSE;

	LockControl = FALSE;

	if( CheckCollision(xPos,yPos,ActAngle ) == CHK_PIECE )
	{
		return FALSE;
	}

	PaintNextPiece(hps);

	return TRUE;
}




void DrawPiece(HPS hps)
{
	struct	Block	*block;
	ULONG			i,x,y,col;


	/* Don't draw invisible piece */
	if( ActPiece == -1 )	return;

	/* Don't draw if no move was done */
//	if( LastxPos == xPos && LastyPos == yPos )
//		return;

	LastxPos = xPos;
	LastyPos = yPos;

	for(i=0;i<4;i++)
	{
		block = &Pieces[ActPiece].Block[ActAngle][i];

		x	= xPos+block->x;
		y	= yPos+block->y;
		col = block->color;

		PaintBlock(hps,x,y,col);
	}
}



static void RestorePiece(HPS hps)
{
	struct	Block	*block;
	ULONG	i,x,y;


	if( LastxPos != -100 )
	{
		for(i=0;i<4;i++)
		{
			block = &Pieces[ActPiece].Block[ActAngle][i];

			x	= LastxPos+block->x;
			y	= LastyPos+block->y;

			PaintBlock(hps,x,y,0);
		}
	}
}


static void PlacePiece(HPS hps)
{
	struct	Block	*block;
	ULONG			i,x,y,col;
	int 			position;


	LastxPos = xPos;
	LastyPos = yPos;

	for(i=0;i<4;i++)
	{
		block = &Pieces[ActPiece].Block[ActAngle][i];

		x	= xPos+block->x;
		y	= yPos+block->y;
		col = block->color;

		PaintBlock(hps,x,y,col);

		PlayField[y][x] = col;
	}

	CheckFullLine(hps);
}




/*******************************************************************************
* CheckCollision()
* Check if the actual piece (angle) could be set to position (x,y)
* Return CHK_OK   OK piece can be set
*		 other	  Place is occupied or out of border
*******************************************************************************/

static BOOL CheckCollision( LONG x, LONG y, LONG angle )
{
	struct	Block	*block;
	LONG			xp,yp,i;


	// Scan the 4 Elements

	for(i=0;i<4;i++)
	{
		block = &Pieces[ActPiece].Block[angle][i];

		// Calculate Position
		xp	= x+block->x;
		yp	= y+block->y;

		// Position out of Border ?
		if( xp<0 )					return	CHK_LEFT;
		if( yp<0 )					return	CHK_TOP;
		if( xp>=NUM_PIECES_X )		return	CHK_RIGHT;
		if( yp>=NUM_PIECES_Y )		return	CHK_BOTTOM;

		// Check if place is occupied by another piece
		if( PlayField[yp][xp] ) 	return	CHK_PIECE;
	}

	// All OK. Position is ready to be used

	return CHK_OK;
}




void FallPiece(HWND hwnd)
{
	HPS 	hps;
	LONG	right,left;



	hps 	= WinGetPS( hwnd );

	if( CheckCollision( xPos, yPos+1, ActAngle ) == CHK_OK )
	{
		fLastMove =
		fPlaced   = FALSE;
		yPos++;
	}
	else
	{
		/* Reset to normal game-speed, in case piece has been dropped */
		if( LockControl )
		{
			AllocTimer( hab, hwndClient, GameSpeed );
			LockControl = FALSE;
		}

		/* Give the player some time to move the piece in an accurate position */
		right = CheckCollision(xPos+1,yPos,ActAngle);
		left  = CheckCollision(xPos-1,yPos,ActAngle);

		/* Place instantly if there is no other way */
		if( fLastMove || (right!=CHK_OK && left!=CHK_OK) )
		{
			ChangeScore( (Level+1)*5 );
			UpdateTextBlock(hps,PRT_UPDATE_CHANGES);

			fPlaced = TRUE;
			PlacePiece(hps);		// Put piece into playfield

			// Start new piece. If not possible -> playfield filled -> Game over
			if( GetNewPiece(hps) == FALSE )
			{
				OnGame		= FALSE;
				GameOver	= TRUE;
			}
		}
		else
			fLastMove = TRUE;
	}

	if( OnGame )
	{
		RestorePiece( hps );
		DrawPiece( hps );
	}

	WinReleasePS( hps );

	if( GameOver )	FinishGame();
}



void RotatePiece(LONG direction)
{
	HPS 	hps;
	LONG	i,
			move_dir,
			new_angle;


	/* Don't allow rotation while final-placing */
	if( fLastMove ) 	return;


	new_angle = (ActAngle+direction) % 4;
	move_dir  = (xPos > NUM_PIECES_X/2) ? -1 : 1;

	/* Try to rotate piece with colliding */
	/* Move max. 2 positions			  */
	for(i=0;i<=2;i++)
	{
		if( CheckCollision( xPos+i*move_dir,yPos,new_angle) == CHK_OK )
		{
			hps = WinGetPS( hwndClient );

			RestorePiece( hps );
			xPos	+= i*move_dir;
			ActAngle = new_angle;
			DrawPiece( hps );

			WinReleasePS( hps );
			break;
		}
	}
}



void MovePiece(LONG direction)
{
	HPS 	hps;


	if( fPlaced )		return;

	if( CheckCollision( xPos+direction,yPos,ActAngle ) == CHK_OK )
	{
		hps = WinGetPS( hwndClient );

		RestorePiece( hps );
		xPos += direction;
		DrawPiece( hps );

		WinReleasePS( hps );

		xFallPos = -1;
		yFallPos = -1;

		/* Allow one last move before finally placing */
		if( fLastMove )
		{
			fPlaced = TRUE;
			TickTimer(hwndClient);
		}
	}
}


void FallDownPiece(void)
{
	AllocTimer( hab, hwndClient, 0 );

	LockControl 	= TRUE;

	xFallPos = xPos;
	yFallPos = yPos;
}


