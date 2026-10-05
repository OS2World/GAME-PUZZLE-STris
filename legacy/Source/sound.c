/*******************************************************************************
*																			   *
* SOUND.C																	   *
* -------																	   *
*																			   *
* Handling of Beeps, Boops, Blips, Blings and other SoundFx 				   *
*																			   *
* Modification History: 													   *
* --------------------- 													   *
*																			   *
* 12.07.95	RHS  Created this file											   *
* 22.07.95	RHS  First usable version. Supports open,close & play commands	   *
* 21.09.95	RHS  Added DeviceSharing										   *
* 06.06.96	RHS  Added SamplesList instead of hard-coded table				   *
*																			   *
*******************************************************************************/

#define INCL_WIN
#define INCL_OS2MM

#include <os2.h>
#include <os2me.h>
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>

#include "stris.h"
#include "window.h"
#include "stub.h"
#include "list.h"
#include "sound.h"



/*** Defines ******************************************************************/

typedef struct	_mmInit
{
	ULONG		im_ID;
	char		*im_Name;
} MM_INIT;

typedef struct _mmList
{
	LIST				mm_List;
	SHORT				mm_Entries;
} MM_LIST;

typedef struct _mmMusic
{
	NODE				mm_Node;
	MCI_WAVE_SET_PARMS	mm_Params;
	PVOID				mm_Data;
	char				*mm_Name;
	ULONG				mm_ID,
						mm_Len;
	BOOL				mm_Loaded,
						mm_Playing;
} MM_MUSIC;

typedef MM_MUSIC *PMM_MUSIC;




/*** Prototypes ***************************************************************/

static	BOOL LoadWaveFile(char *, ULONG);
static	BOOL FreeWaveFile(PMM_MUSIC pMusic);
static	PMM_MUSIC FindMusic(ULONG ulID);


/*** Variables ****************************************************************/



/* Define the sounds to load */

static	MM_INIT 	InitMusic[] =
{
	WAV_GLASS,		"Glass.WAV",
	WAV_DING,		"Ding.WAV",
	WAV_BREAKIT,	"BreakIt.WAV",
	0,				NULL						/* Don't remove !!!! 			*/
};

static	MM_LIST				SampleList;			/* List of loaded samples		*/
static	MCI_OPEN_PARMS		mci_open_parms;
static	ULONG				playlist[3][4];

static	BOOL				fDeviceAvailable,	/* Audio Device connected ? 	*/
							fMusicAvailable,	/* Music loaded and available	*/
							fAcquired,			/* Do we have the device		*/
							fMusicOn;			/* Music enabled				*/




/*******************************************************************************
* GetMusicState()
* Zustand des Music-Flags retournieren
*******************************************************************************/

BOOL GetMusicState(void)
{
	return fMusicOn;
}



/*******************************************************************************
* SetMusicState(fState)
* Samples ein und ausschalten
* fState = Neuer Zustand. TRUE = EIN, FALSE = AUS
* return = Vorheriger Zustand
*******************************************************************************/

BOOL SetMusicState( BOOL fState )
{
	BOOL fOldState;


	fOldState = fMusicOn;

	fMusicOn = fState;

	return fOldState;
}




/*******************************************************************************
* OpenDevice()
* AudioDevice oeffnen
*******************************************************************************/

BOOL OpenDevice(void)
{
	ULONG				mm_rc;
	char				szStr[256];



	if( fDeviceAvailable )			// Return if Device already opened
		return TRUE;

	fDeviceAvailable	= FALSE;
	fAcquired			= FALSE;


	// Open Audio Device

	memset(&mci_open_parms,0,sizeof(mci_open_parms));
	mci_open_parms.pszElementName = (PSZ)&playlist;
	mci_open_parms.pszDeviceType  = (PSZ)MAKEULONG(MCI_DEVTYPE_WAVEFORM_AUDIO,1); // ,0);
	mci_open_parms.hwndCallback   = hwndClient;

	mm_rc = mciSendCommand(0,MCI_OPEN,MCI_WAIT | MCI_OPEN_PLAYLIST |
						   MCI_OPEN_TYPE_ID | MCI_OPEN_SHAREABLE,
						   &mci_open_parms,0);

	if(mm_rc != 0)
	{
//		if( mciGetErrorString(mm_rc,szStr,sizeof(szStr) ))
//		  Message("Can't open audio device.\n%s",szStr);

		return FALSE;
	}


//	DEBUG("Device opened");

	fDeviceAvailable = TRUE;
	fAcquired		 = TRUE;				// Gained control of device


	return TRUE;
}



/*******************************************************************************
* CloseDevice()
* AudioDevice schliessen
*******************************************************************************/

void CloseDevice(void)
{
//	Message("CloseDevice()");

	if(!fDeviceAvailable)
		return; 				// Device never opened


	mciSendCommand(mci_open_parms.usDeviceID,
					MCI_CLOSE,MCI_WAIT,
					(PVOID)NULL,0);


//	DEBUG("Device closed");

	fAcquired		 = FALSE;
	fDeviceAvailable = FALSE;
}



/*******************************************************************************
* GetAudioState()
* AudioDevice oeffnen
*******************************************************************************/

BOOL GetAudioState(void)
{
	return fMusicAvailable;
}


/*******************************************************************************
* OpenMusic()
* Audio device ”ffnen und Samples laden die in InitMusic definiert sind.
* Return = TRUE wenn alles OK, ansonsten FALSE.
*******************************************************************************/

BOOL OpenMusic(void)
{
	PMM_MUSIC		pMusic;
	ULONG			mm_rc,
					i;


	fMusicAvailable = FALSE;

	if( !OpenDevice() ) 					// Return Error if Device
		return FALSE;						// couldn't be opened


	/* Initialize the Sampleslist */
	NewList(&SampleList.mm_List);

	/* Load WAV-Files */
	for(i=0;InitMusic[i].im_ID;i++)
	{
//		Message("Opening %ld = '%s'",InitMusic[i].im_ID,InitMusic[i].im_Name);

		LoadWaveFile(InitMusic[i].im_Name,InitMusic[i].im_ID);

#if 0
		pMusic = malloc(sizeof(MM_MUSIC));

		pMusic->mm_ID		= InitMusic[i].im_ID;
		pMusic->mm_Name		= InitMusic[i].im_Name;

		AddHead(&SampleList.mm_List,&pMusic->mm_Node);
		SampleList.mm_Entries++;

		if( LoadWaveFile(pMusic) )
		{
			pMusic->mm_Loaded = TRUE;

			Message("Music %ld = '%s' loaded",pMusic->mm_ID,pMusic->mm_Name);
		}
#endif

	}

	fMusicAvailable = TRUE;


//	Message("Showing List of Samples");

//	DOLIST(&SampleList.mm_List,pMusic)
//		Message("name %s",pMusic->mm_Name);


	return TRUE;
}





/*******************************************************************************
* CloseMusic()
* Audio device schliessen und alle geladenen Samples freigeben.
* return = kein
*******************************************************************************/

void CloseMusic(void)
{
	PMM_MUSIC		pMusic;
	ULONG			i;



	if( !fMusicAvailable )
		return;

	fMusicAvailable = FALSE;


	/* Close Audio Device */
	CloseDevice();


//	Message("Showing List of Samples");
//	DOLIST(&SampleList.mm_List,pMusic)
//		Message("name %s",pMusic->mm_Name);

	/* Free WAV-Files */
	DOLIST(&SampleList.mm_List,pMusic)
	{
		FreeWaveFile(pMusic);
	}

#if 1
	if( ISLISTEMPTY(&SampleList.mm_List) )
		Message("List empty");
	else
		Message("ERROR List nonempty");
#endif
}



/*******************************************************************************
* PlayMusic(ulSound)
* Sample asynchron abspielen. Nach Ende des Abspielens wird eine Message
* verschickt, die den Status des Samples aendert (mm_Playing).
* ulSound = ID des zu spielenden Samples
* return  = kein
*******************************************************************************/

void PlayMusic(ULONG ulSound)
{
	PMM_MUSIC			pMusic;
	MCI_PLAY_PARMS		mci_play_parms;
	ULONG				mm_rc;
	LONG				lWav;
	char				szStr[128];


//	Message("Playing Id = %ld",ulSound);

	if( !fMusicAvailable || !fMusicOn )
		return;


	pMusic = FindMusic(ulSound);
	if( pMusic )
	{
		// If sample is already playing we do nothing
		// Later versions may stop the current sample and start it new.

		if( pMusic->mm_Playing )
		{
//			DEBUG("Already playing");
			return;
		}

//		Message("ID %ld -> '%s' (%ld)\nPlaying %s Id = %ld",
//				ulSound,Music[lWav].mm_Name,lWav,
//				Music[lWav].mm_Name, Music[lWav].mm_ID );

		if( !fAcquired )
		{
//			DEBUG("NO DEVICE");

			if( !OpenDevice() )
			{
				Message("OpenDevice() failed.");
				return;
			}
		}

		// Parameter fr WAV einstellen

		mm_rc = mciSendCommand(mci_open_parms.usDeviceID,
						MCI_SET,MCI_WAIT | MCI_WAVE_SET_SAMPLESPERSEC|
						MCI_WAVE_SET_CHANNELS | MCI_WAVE_SET_BITSPERSAMPLE,
						&pMusic->mm_Params,0);
		if( mm_rc )
		{
			if( !mciGetErrorString(mm_rc,szStr,sizeof(szStr)) )
				Message("PlayMusic()\nError in MCI_SET.\n%s",szStr);
		}


		// Playlist aufbauen

		playlist[0][0]	= DATA_OPERATION;
		playlist[0][1]	= (ULONG)pMusic->mm_Data;
		playlist[0][2]	= pMusic->mm_Len;
		playlist[0][3]	= 0;

		playlist[1][0]	= EXIT_OPERATION;
		playlist[1][1]	= 0;
		playlist[1][2]	= 0;
		playlist[1][3]	= 0;


		// Sample abspielen

		memset(&mci_play_parms,0,sizeof(mci_play_parms));
		mci_play_parms.hwndCallback = hwndClient;
		mm_rc = mciSendCommand( mci_open_parms.usDeviceID,
								MCI_PLAY|MCI_FROM,MCI_NOTIFY,
								&mci_play_parms,pMusic->mm_ID );
		if( mm_rc )
		{
			if( !mciGetErrorString(mm_rc,szStr,sizeof(szStr)))
				Message("PlayMusic()\nError in MCI_PLAY.\n%s",szStr);
		}
		else
			pMusic->mm_Playing = TRUE;
	}
}




/*******************************************************************************
* AcquireAudioDevice()
* Wird gerufen wenn unser Fenster den Fokus erh„lt. Sollte das audio device
* unterdessen an einen anderen Thread vergeben worden sein, mssen wir es
* zurckerobern.
*******************************************************************************/

void AcquireAudioDevice( HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2 )
{
	MCI_GENERIC_PARMS	mci_generic_parms;
	ULONG				mm_rc;


//	DEBUG("Acquiring msg");

	if( !fDeviceAvailable || fAcquired )
		return; 			// The device is ours


	// Re-Allocate audio device

//	DEBUG("Acquiring device");

	mci_generic_parms.hwndCallback = hwndClient;
	mciSendCommand( mci_open_parms.usDeviceID,
					MCI_ACQUIREDEVICE,
					MCI_NOTIFY,
					&mci_generic_parms,
					0);
}



void PassDeviceProc( HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2 )
{
//	DEBUG("PassDevice");

	if( SHORT1FROMMP(mp2) == MCI_GAINING_USE )	// gaining control
	{
		fAcquired = TRUE;						// gained the device
//		DEBUG("got device");
	}
	else										// loosing control
	{
		fAcquired = FALSE;						// lost the device
//		DEBUG("lost device");
	}
}



/*******************************************************************************
* MusicNotifyProc()
* Handler fr MCI_PLAY und MCI_PASSDEVICE Messages. Setzt Spielstatus eines
* Samples und reserviert/alloziert Device falls n”tig.
*******************************************************************************/

void MusicNotifyProc( HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2 )
{
	PMM_MUSIC	pMusic;
	USHORT		usNotifyCode;			/* for notification code			  */
	USHORT		usUserParm; 			/* for user parameter				  */
	USHORT		usCommandMessage;		/* for command message				  */
	LONG		wav;
	char		str[128];


	usNotifyCode	 = SHORT1FROMMP(mp1);
	usUserParm		 = SHORT2FROMMP(mp1);
	usCommandMessage = SHORT2FROMMP(mp2);

	if ( ( usNotifyCode != MCI_NOTIFY_SUPERSEDED &&
			usNotifyCode != MCI_NOTIFY_ABORTED &&
			usNotifyCode != MCI_NOTIFY_SUCCESSFUL ) ||
			usNotifyCode == MCI_NOTIFY_SUPERSEDED ||
			usNotifyCode == MCI_NOTIFY_ABORTED ||
			(usNotifyCode == MCI_NOTIFY_SUCCESSFUL && usCommandMessage == MCI_PLAY ) )
	{
		if( usCommandMessage == MCI_PLAY )
		{
			pMusic = FindMusic(usUserParm);	// Find Sound out of UserID
			if( pMusic )	 				// Found Sound
			{
//				Message("Sound finished");
				pMusic->mm_Playing = FALSE;	// Reset playing state
			}
		}
	}
}



/*** Internal Functions *******************************************************/

/*******************************************************************************
* LoadWaveFile(pMusic)
* Soundfile (.WAV) laden. Reserviert speicher, laedt Datei und ermittelt
* Parameter (Rate,Channels,BitsPerSample). Freigeben mit FreeWaveFile()
* pMusic = Zeiger auf MM_MUSIC Struktur
* return = TRUE  : Sample erfolgreich geladen
*          FALSE : Fehler
*******************************************************************************/

static	BOOL LoadWaveFile(char *szName, ULONG ulID)
{
	PMM_MUSIC		pMusic;
	MMAUDIOHEADER	mmAudioHeader;
	HMMIO			hmmioFile;
	LONG			rc;
	ULONG			ulBytesRead;



	/* Allocate memory for Sample-Structure (Node) */
	pMusic = malloc(sizeof(MM_MUSIC));

	/* Remember name and ID of Sample */
	pMusic->mm_ID		= ulID;
	pMusic->mm_Name		= szName;

	/* Add Node to List */
	AddHead(&SampleList.mm_List,&pMusic->mm_Node);


	/* Open Sample with MMPM, Read and Store Information (Size,Speed,Channels) */
	hmmioFile = mmioOpen(pMusic->mm_Name,
						(PMMIOINFO) NULL,
						MMIO_READ);

	if(hmmioFile == NULLHANDLE)
	{
		Message("LoadWaveFile()\nError loading '%s'.\nSound will not be available.",pMusic->mm_Name);
		return FALSE;
	}

	rc = mmioGetHeader(hmmioFile,
					  (PVOID) &mmAudioHeader,
					  sizeof (mmAudioHeader),
					  (PLONG) &ulBytesRead,
					  (ULONG) 0,
					  (ULONG) 0);

	if(rc != MMIO_SUCCESS)
	{
		Message("LoadWaveFile()\nCan't read header of '%s'.",pMusic->mm_Name);
		mmioClose(hmmioFile,0);
		return FALSE;
	}

	pMusic->mm_Len = mmAudioHeader.mmXWAVHeader.XWAVHeaderInfo.ulAudioLengthInBytes;

	memset(&pMusic->mm_Params,0,sizeof(pMusic->mm_Params) );
	pMusic->mm_Params.ulSamplesPerSec		= mmAudioHeader.mmXWAVHeader.WAVEHeader.ulSamplesPerSec;
	pMusic->mm_Params.usBitsPerSample		= mmAudioHeader.mmXWAVHeader.WAVEHeader.usBitsPerSample;
	pMusic->mm_Params.usChannels			= mmAudioHeader.mmXWAVHeader.WAVEHeader.usChannels;
	pMusic->mm_Params.ulAudio				= MCI_SET_AUDIO_ALL;


#if 0
	Message("File '%s'\nRate %ld\nBits %ld\nChannels %ld",
			pMusic->mm_Name,
			pMusic->mm_Params.ulSamplesPerSec,
			pMusic->mm_Params.usBitsPerSample,
			pMusic->mm_Params.usChannels );
#endif

	/* Allocate Memory to load sample-datas into */
#if 0
	rc = DosAllocMem(&pMusic->mm_Data,
					  pMusic->mm_Len,
					  PAG_COMMIT | PAG_READ | PAG_WRITE);
	if(rc != 0)
	{
		Message("LoadWaveFile()\nCan't allocate %ld bytes for '%s'.",pMusic->mm_Len,pMusic->mm_Name);
		mmioClose (hmmioFile,0);
		return FALSE;
	}
#endif
	pMusic->mm_Data = malloc(pMusic->mm_Len);

	/* Finally read the datas ... */
	rc = mmioRead(hmmioFile,
				  (PSZ)pMusic->mm_Data,
				  pMusic->mm_Len);

	if(rc == MMIO_ERROR)
	{
		Message("LoadWaveFile()\nError reading '%s'.",pMusic->mm_Name);
		DosFreeMem(pMusic->mm_Data);
		mmioClose(hmmioFile,0);
		return FALSE;
	}

	/* ... close the file and return */
	mmioClose(hmmioFile,0);

	pMusic->mm_Loaded = TRUE;

	return TRUE;
}



/*******************************************************************************
* FreeWaveFile(pMusic)
* Mit LoadWaveFile geladenen Sound freigeben.
* pMusic = Zeiger auf MM_MUSIC Struktur
* return = TRUE
*******************************************************************************/

static BOOL FreeWaveFile(PMM_MUSIC pMusic)
{
	Message("Freeing '%s'",pMusic->mm_Name);

	/* Free memory for sound-data if allocated */
	if( pMusic->mm_Data)
//		DosFreeMem(pMusic->mm_Data);
		free(pMusic->mm_Data);

	/* Unlink Node from list, free memory used by Node-Structure */
	RemoveNode(&pMusic->mm_Node);
//	free(pMusic);


	return TRUE;
}




/*******************************************************************************
* FindMusic(ulID)
* ulID   = ID des gesuchten Samples
* return = Pointer zu MUSIC-Struktur des Samples
*******************************************************************************/

static PMM_MUSIC FindMusic(ULONG ulID)
{
	PMM_MUSIC	pMusic;


	/* Scan the sample-list for the given ID */
	DOLIST(&SampleList.mm_List,pMusic)
	{
		if( pMusic->mm_Loaded && pMusic->mm_ID == ulID )
			return pMusic;
	}

	/* ID not found */
	return NULLHANDLE;
}



