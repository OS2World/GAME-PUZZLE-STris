/****************************************************************************
*																			*
* CRC V0.80 							  Project started  : 16.11.1995 	*
* --------- 									  finished : .......... 	*
*																			*
* CRC (Cyclic reduncancy check) generieren									*
*																			*
* Author Rene Straub				Tel.  +41 62 776 26 61					*
*		 Talstrasse 4				Fax.  +41 62 776 14 17					*
*		 5726 Unterkulm (Schweiz)	EMail straub@crack.aare.ch				*
*																			*
* Copyright (C) 1995. All rights reserved.									*
*																			*
* Modification History: 													*
* --------------------- 													*
*																			*
* 16.11.95	RHS  Created this file											*
* 18.11.95	RHS  Optimierung und vereinfachung								*
* 24.03.96	RHS  Portierung nach OS/2										*
*																			*
****************************************************************************/

//#include <stdio.h>
#include <string.h>

/*** Definitionen **********************************************************/

#define FAST							// Set this for faster Operation

typedef char			BYTE;
typedef unsigned char	UBYTE;
typedef unsigned long	ULONG;


/*** Variablen *************************************************************/

static	BYTE	ubCRC;

#ifdef FAST
 static UBYTE	ubXORMask[] = { 0x00, 0x8C };
#endif



/*** Funktionen ************************************************************/


/****************************************************************************
* ByteCRC(ubValue)
* CRC für das Byte ubValue berechnen
* ubValue : Byte für das CRC berechnet werden soll
* return  : keine
****************************************************************************/

static void ByteCRC(UBYTE ubValue)
{
	ULONG	i;
	UBYTE	ubTemp;


	for(i=0;i<8;i++)
	{
		ubTemp = (ubValue^ubCRC);		// CRC[0] XOR ubValue[0]

		ubCRC	>>= 1;					// Das neue CRC
		ubValue >>= 1;					// Naechstes Bit an Input legen


#ifdef FAST
		ubCRC ^= ubXORMask[ubTemp&1];
#else
		if( ubTemp & 1) 				// Wenn die Verknuepfung
			ubCRC ^= 0x8C;				// CRC[0] XOR ubValue[0] TRUE wird
										// das MSB des CRC gesetzt sowie
										// Bit 2+3 invertiert (mittels XOR)
#endif
//		printf("  Bit %ld  Temp = %ld	CRC = 0x%02lx\n",i,ubTemp&1,ubCRC);
	}
}


/****************************************************************************
* GenerateCRC(ubValue)
* CRC für ein ByteArray berechnen
* ubValue : Bytearray für das CRC berechnet werden soll
* return  : CRC Wert
****************************************************************************/

BYTE GenerateCRC(char *pszText)
{
	ULONG	i;


	ubCRC = 0;							// CRC initialisieren

	for(i=0;i<strlen(pszText);i++)				// Array durchgehen
	{
//		printf("\nByte %ld = 0x%02lx (%ld)\n\n",i,ubArray[i],ubArray[i]);
		ByteCRC(pszText[i]);			// CRC für aktuelles Byte berechnen
	}

	return ubCRC;
}


