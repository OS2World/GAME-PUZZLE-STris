/*******************************************************************************
*																			   *
* PIECES.H																	   *
* --------																	   *
*																			   *
* Include File for PIECES.C 												   *																			  *
*																			   *
*******************************************************************************/

#ifndef PIECES_H
#define PIECES_H


/*** Defines ******************************************************************/

// Return Codes for CheckCollision

enum CheckStates
{
	CHK_OK,
	CHK_PIECE,
	CHK_LEFT,
	CHK_RIGHT,
	CHK_BOTTOM,
	CHK_TOP
};


/*** Prototypes ***************************************************************/

extern	BOOL GetNewPiece(HPS hps);
extern	void SetPieceSize(void);

extern	void PaintBlock( HPS hps, LONG x, LONG y, BYTE num );
extern	void PaintNextPiece(HPS hps);

extern	void DrawPiece(HPS hps);
extern	void RestorePiece(HPS hps);

extern	void FallPiece(HWND hwnd);
extern	void FallDownPiece(void);
extern	void RotatePiece(LONG direction);
extern	void MovePiece(LONG direction);

extern	BOOL InitPieceBitmap(void);
extern	void ClosePieceBitmap(void);
extern	void GeneratePieces(void);
extern	void GetFallPiecePos(LONG *x, LONG *y);


/*** Variables ****************************************************************/

extern	LONG		PieceWidth,PieceHeight,PieceBorder;
extern	LONG		ActPiece,ActPalette;



#endif /* PIECES_H */

