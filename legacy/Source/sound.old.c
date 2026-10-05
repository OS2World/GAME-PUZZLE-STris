/*******************************************************************************
*                                                                              *
* SOUND.C                                                                      *
* -------                                               					   *
*                                                                              *
* Handling of Beeps, Boops, Blips, Blings and other SoundFx                    *
*                                                                              *
* Modification History:                                                        *
* ---------------------                                                        *
*                                                                              *
* 17.04.95  RHS  Created this file                                             *
*                                                                              *
*******************************************************************************/

#define INCL_MACHDR
#define INCL_MCIOS2

#include <os2.h>
#include <os2me.h>
#include <stdio.h>
#include <memory.h>

#include "stris.h"
#include "window.h"
#include "sound.h"


/*** Defines ******************************************************************/

typedef struct	_mmMusic
{
	MCI_PLAY_PARMS	mm_mci_play;
	MCI_LOAD_PARMS	mm_mci_load;
	ULONG			mm_ID;
	ULONG			mm_rc;
	ULONG			mm_error;
	ULONG			mm_state;
} MM_MUSIC;

typedef	struct	_mmInit
{
	ULONG	mi_ID;
	char	*mi_name;
} MM_INIT;


/*** Prototypes ***************************************************************/

/*** Variables ****************************************************************/


static	MM_INIT		InitMusic[] =
{
	WAV_GLASS,	"Sound/Glass.WAV",
	WAV_DING,	"Sound/Ding.WAV",
	0,			NULL
};

static	MM_MUSIC	Music[4];

static	BOOL		MusicFlag,
					SoundFlag;






BOOL GetSoundState(void)
{
	return SoundFlag;
}


BOOL GetMusicState(void)
{
	return MusicFlag;
}


BOOL SetSoundState( BOOL NewState )
{
	BOOL OldState;


	OldState = SoundFlag;

	SoundFlag = NewState;

	return OldState;
}


BOOL SetMusicState( BOOL NewState )
{
	BOOL OldState;


	OldState = MusicFlag;

	MusicFlag = NewState;

	return OldState;
}


void Sound(ULONG freq, ULONG duration)
{
	if( SoundFlag )		DosBeep(freq,duration);
}






static	MCI_OPEN_PARMS	mci_open;

void OpenMusic(char *name)
{
	ULONG	i;
	char	str[256];


	mci_open.hwndCallback 	= (HWND)NULLHANDLE;
	mci_open.usDeviceID		= 0;
	mci_open.pszDeviceType	= "waveaudio";
	mci_open.pszElementName	= (PSZ)NULL;
	mci_open.pszAlias	 	= (PSZ)NULL;

	i = mciSendCommand( (USHORT)0,
						MCI_OPEN,
						MCI_WAIT | MCI_OPEN_SHAREABLE,
						(PVOID)&mci_open,
						(USHORT) 0);

	if( i == MCIERR_SUCCESS )
	{
		sprintf(str,"Device %ld opened",mci_open.usDeviceID );
		Message(str);
	}
	else
	{
		sprintf(str,"Error opening device" );
		Message(str);
	}



	i = 0;

	while(InitMusic[i].mi_ID)
	{
		sprintf(str,"Opening %ld = '%s'",InitMusic[i].mi_ID,InitMusic[i].mi_name );
		Message(str);

		memset(&Music[i].mm_mci_load,0,sizeof(MCI_LOAD_PARMS));
//		Music[i].mm_mci_load.hwndCallback 	= (HWND)NULLHANDLE;
		Music[i].mm_mci_load.pszElementName	= InitMusic[i].mi_name;
		Music[i].mm_ID						= InitMusic[i].mi_ID;

		Music[i].mm_rc = mciSendCommand( mci_open.usDeviceID,
								MCI_LOAD,
								MCI_WAIT | MCI_OPEN_ELEMENT,
								(PVOID)&Music[i].mm_mci_load,
								(USHORT) 0);

		if( Music[i].mm_rc == MCIERR_SUCCESS )
		{
			sprintf(str,"Music %ld = '%s' loaded",InitMusic[i].mi_ID,InitMusic[i].mi_name );
			Message(str);
		}
		else
		{
			sprintf(str,"Error loading %ld = '%s'",InitMusic[i].mi_ID,InitMusic[i].mi_name );
			Message(str);
		}

		i++;
	}
}



void CloseMusic(void)
{
	ULONG	i,
			mm_rc;
	char	str[256];



#if 0
	i = 0;

	while(InitMusic[i].mi_ID)
	{
		if( Music[i].mm_rc == MCIERR_SUCCESS )
		{
			sprintf(str,"Freeing music %ld = '%s'",InitMusic[i].mi_ID,InitMusic[i].mi_name );
			Message(str);

			Music[i].mm_rc = mciSendCommand( Music[i].mm_mci_open.usDeviceID,
								MCI_CLOSE,MCI_WAIT,(PVOID)NULL,(USHORT) 2);

			if( Music[i].mm_rc == MCIERR_SUCCESS )
			{
				sprintf(str,"Music %ld = '%s' freed",InitMusic[i].mi_ID,InitMusic[i].mi_name );
				Message(str);
			}
			else
			{
				sprintf(str,"Error freeing %ld = '%s'",InitMusic[i].mi_ID,InitMusic[i].mi_name );
				Message(str);
			}
		}

		i++;
	}
#endif

	mm_rc = mciSendCommand( mci_open.usDeviceID,
						MCI_CLOSE,MCI_WAIT,(PVOID)NULL,(USHORT) 0);

	if( mm_rc == MCIERR_SUCCESS )
	{
		sprintf(str,"Device %ld closed",mci_open.usDeviceID );
		Message(str);
	}
	else
	{
		sprintf(str,"Error closing device %ld",mci_open.usDeviceID );
		Message(str);
	}
}


void PlayMusic(ULONG id)
{
	ULONG	i;


	i = 0;

	while(InitMusic[i].mi_ID)
	{
		if( Music[i].mm_ID == id )
		{
			if( Music[i].mm_rc == MCIERR_SUCCESS )
			{
				Music[i].mm_mci_play.ulFrom = 0;

				mciSendCommand( mci_open.usDeviceID,
								MCI_PLAY,
								MCI_FROM, // | MCI_WAIT,
								(PVOID)&Music[i].mm_mci_play,
								(USHORT) 0);
			}

			break;
		}

		i++;
	}
}


