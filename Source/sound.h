/*******************************************************************************
*																			   *
* SOUND.H																	   *
* -------																	   *
*																			   *
* Include File for SOUND.C													   *																			  *
*																			   *
*******************************************************************************/
#ifndef SOUND_H
#define SOUND_H


/*** Defines ******************************************************************/

enum WAV_FILE_ID
{
	WAV_GLASS	= 1000,
	WAV_DING,
	WAV_BREAKIT,
};



/*** Prototypes ***************************************************************/

BOOL SetMusicState( BOOL NewState );
BOOL GetMusicState(void);

BOOL OpenMusic(void);
void CloseMusic(void);
BOOL GetAudioState(void);

void PlayMusic(ULONG);

void MusicNotifyProc( HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2 );
void AcquireAudioDevice( HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2 );
void PassDeviceProc( HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2 );


/*** Variables ****************************************************************/



#endif /* SOUND_H */

