/*******************************************************************************
*
* SOUND.C
* -------
*
* Handling of Beeps, Boops, Blips, Blings and other SoundFx
*
* Modification History:
* ---------------------
*
* 12.07.95  RHS  Created this file
* 22.07.95  RHS  First usable version. Supports open,close & play commands
* 21.09.95  RHS  Added DeviceSharing
* 06.06.96  RHS  Added SamplesList instead of hard-coded table
* 2025      Dynamic loading of MDM/MMIO so EXE starts without MMPM2 present.
*
*******************************************************************************/

#define INCL_WIN
#define INCL_OS2MM
#define INCL_DOSMODULEMGR
#define INCL_DOSPROCESS

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

typedef struct  _mmInit
{
    ULONG       im_ID;
    char        *im_Name;
} MM_INIT;

typedef struct _mmList
{
    LIST                mm_List;
    SHORT               mm_Entries;
} MM_LIST;

typedef struct _mmMusic
{
    NODE                mm_Node;
    MCI_WAVE_SET_PARMS  mm_Params;
    PVOID               mm_Data;
    char                *mm_Name;
    ULONG               mm_ID,
                        mm_Len;
    BOOL                mm_Loaded,
                        mm_Playing;
} MM_MUSIC;

typedef MM_MUSIC *PMM_MUSIC;



/*** Dynamic-load function pointer types *************************************/

typedef ULONG   (_System *PFNMCISEND)(USHORT, USHORT, ULONG, PVOID, USHORT);
typedef BOOL    (_System *PFNMCIERR )(ULONG,  PSZ,    USHORT);
typedef HMMIO   (_System *PFNMOPEN  )(PSZ, PMMIOINFO, ULONG);
typedef LONG    (_System *PFNMGETHDR)(HMMIO, PVOID, LONG, PLONG, ULONG, ULONG);
typedef LONG    (_System *PFNMREAD  )(HMMIO, PSZ, LONG);
typedef ULONG   (_System *PFNMCLOSE )(HMMIO, USHORT);

static PFNMCISEND   pfnMciSendCommand   = NULL;
static PFNMCIERR    pfnMciGetErrorString = NULL;
static PFNMOPEN     pfnMmioOpen         = NULL;
static PFNMGETHDR   pfnMmioGetHeader    = NULL;
static PFNMREAD     pfnMmioRead         = NULL;
static PFNMCLOSE    pfnMmioClose        = NULL;

static HMODULE hmodMDM  = NULLHANDLE;
static HMODULE hmodMMIO = NULLHANDLE;
static BOOL    fDllLoaded = FALSE;

static BOOL LoadSoundDLLs(void)
{
    char errbuf[64];

    if (fDllLoaded)
        return (pfnMciSendCommand != NULL && pfnMmioOpen != NULL);

    fDllLoaded = TRUE;

    if (DosLoadModule(errbuf, sizeof(errbuf), (PSZ)"MDM", &hmodMDM) == 0)
    {
        DosQueryProcAddr(hmodMDM, 0, (PSZ)"mciSendCommand",
                         (PFN *)&pfnMciSendCommand);
        DosQueryProcAddr(hmodMDM, 0, (PSZ)"mciGetErrorString",
                         (PFN *)&pfnMciGetErrorString);
    }

    if (DosLoadModule(errbuf, sizeof(errbuf), (PSZ)"MMIO", &hmodMMIO) == 0)
    {
        DosQueryProcAddr(hmodMMIO, 0, (PSZ)"mmioOpen",
                         (PFN *)&pfnMmioOpen);
        DosQueryProcAddr(hmodMMIO, 0, (PSZ)"mmioGetHeader",
                         (PFN *)&pfnMmioGetHeader);
        DosQueryProcAddr(hmodMMIO, 0, (PSZ)"mmioRead",
                         (PFN *)&pfnMmioRead);
        DosQueryProcAddr(hmodMMIO, 0, (PSZ)"mmioClose",
                         (PFN *)&pfnMmioClose);
    }

    return (pfnMciSendCommand != NULL && pfnMmioOpen != NULL);
}



/*** Prototypes ***************************************************************/

static  BOOL LoadWaveFile(char *, ULONG);
static  BOOL FreeWaveFile(PMM_MUSIC pMusic);
static  PMM_MUSIC FindMusic(ULONG ulID);


/*** Variables ****************************************************************/



/* Directory prefix for sound files, built at runtime from EXE location */

static  char        szSoundsDir[CCHMAXPATH];

static  void BuildSoundsDir(void)
{
    PTIB    ptib;
    PPIB    ppib;
    char    szExePath[CCHMAXPATH];
    char    *p;

    szSoundsDir[0] = '\0';
    if (DosGetInfoBlocks(&ptib, &ppib) == 0)
    {
        if (DosQueryModuleName(ppib->pib_hmte, sizeof(szExePath), szExePath) == 0)
        {
            p = strrchr(szExePath, '\\');
            if (p)
            {
                *(p + 1) = '\0';
                strcpy(szSoundsDir, szExePath);
            }
        }
    }
    strcat(szSoundsDir, "sounds\\");
}


/* Define the sounds to load */

static  MM_INIT     InitMusic[] =
{
    WAV_GLASS,      "Glass.WAV",
    WAV_DING,       "Ding.WAV",
    WAV_BREAKIT,    "BreakIt.WAV",
    0,              NULL                        /* Don't remove !!!! */
};

static  MM_LIST             SampleList;         /* List of loaded samples */
static  MCI_OPEN_PARMS      mci_open_parms;
static  ULONG               playlist[3][4];

static  BOOL                fDeviceAvailable,   /* Audio Device connected ? */
                            fMusicAvailable,    /* Music loaded and available */
                            fAcquired,          /* Do we have the device */
                            fMusicOn;           /* Music enabled */




/*******************************************************************************
* GetMusicState()
*******************************************************************************/

BOOL GetMusicState(void)
{
    return fMusicOn;
}



/*******************************************************************************
* SetMusicState(fState)
*******************************************************************************/

BOOL SetMusicState( BOOL fState )
{
    BOOL fOldState;

    fOldState = fMusicOn;
    fMusicOn  = fState;
    return fOldState;
}




/*******************************************************************************
* OpenDevice()
*******************************************************************************/

BOOL OpenDevice(void)
{
    ULONG               mm_rc;
    char                szStr[256];


    if (!LoadSoundDLLs())
        return FALSE;

    if( fDeviceAvailable )
        return TRUE;

    fDeviceAvailable    = FALSE;
    fAcquired           = FALSE;


    memset(&mci_open_parms,0,sizeof(mci_open_parms));
    mci_open_parms.pszElementName = (PSZ)&playlist;
    mci_open_parms.pszDeviceType  = (PSZ)MAKEULONG(MCI_DEVTYPE_WAVEFORM_AUDIO,1);
    mci_open_parms.hwndCallback   = hwndClient;

    mm_rc = pfnMciSendCommand(0, MCI_OPEN,
                              MCI_WAIT | MCI_OPEN_PLAYLIST |
                              MCI_OPEN_TYPE_ID | MCI_OPEN_SHAREABLE,
                              &mci_open_parms, 0);

    if(mm_rc != 0)
        return FALSE;

    fDeviceAvailable = TRUE;
    fAcquired        = TRUE;

    return TRUE;
}



/*******************************************************************************
* CloseDevice()
*******************************************************************************/

void CloseDevice(void)
{
    if(!fDeviceAvailable)
        return;

    pfnMciSendCommand(mci_open_parms.usDeviceID,
                      MCI_CLOSE, MCI_WAIT,
                      (PVOID)NULL, 0);

    fAcquired        = FALSE;
    fDeviceAvailable = FALSE;
}



/*******************************************************************************
* GetAudioState()
*******************************************************************************/

BOOL GetAudioState(void)
{
    return fMusicAvailable;
}



/*******************************************************************************
* OpenMusic()
*******************************************************************************/

BOOL OpenMusic(void)
{
    PMM_MUSIC       pMusic;
    ULONG           mm_rc,
                    i;


    fMusicAvailable = FALSE;

    BuildSoundsDir();

    if( !OpenDevice() )
        return FALSE;


    NewList(&SampleList.mm_List);

    for(i=0;InitMusic[i].im_ID;i++)
        LoadWaveFile(InitMusic[i].im_Name, InitMusic[i].im_ID);

    fMusicAvailable = TRUE;

    return TRUE;
}



/*******************************************************************************
* CloseMusic()
*******************************************************************************/

void CloseMusic(void)
{
    PMM_MUSIC       pMusic;
    ULONG           i;


    if( !fMusicAvailable )
        return;

    fMusicAvailable = FALSE;

    CloseDevice();

    DOLIST(&SampleList.mm_List,pMusic)
        FreeWaveFile(pMusic);
}



/*******************************************************************************
* PlayMusic(ulSound)
*******************************************************************************/

void PlayMusic(ULONG ulSound)
{
    PMM_MUSIC           pMusic;
    MCI_PLAY_PARMS      mci_play_parms;
    ULONG               mm_rc;
    LONG                lWav;
    char                szStr[128];


    if( !fMusicAvailable || !fMusicOn )
        return;


    pMusic = FindMusic(ulSound);
    if( pMusic )
    {
        if( pMusic->mm_Playing )
            return;

        if( !fAcquired )
        {
            if( !OpenDevice() )
            {
                Message("OpenDevice() failed.");
                return;
            }
        }

        mm_rc = pfnMciSendCommand(mci_open_parms.usDeviceID,
                        MCI_SET, MCI_WAIT | MCI_WAVE_SET_SAMPLESPERSEC|
                        MCI_WAVE_SET_CHANNELS | MCI_WAVE_SET_BITSPERSAMPLE,
                        &pMusic->mm_Params, 0);
        if( mm_rc )
        {
            if( pfnMciGetErrorString &&
                !pfnMciGetErrorString(mm_rc, szStr, sizeof(szStr)) )
                Message("PlayMusic()\nError in MCI_SET.\n%s",szStr);
        }


        playlist[0][0]  = DATA_OPERATION;
        playlist[0][1]  = (ULONG)pMusic->mm_Data;
        playlist[0][2]  = pMusic->mm_Len;
        playlist[0][3]  = 0;

        playlist[1][0]  = EXIT_OPERATION;
        playlist[1][1]  = 0;
        playlist[1][2]  = 0;
        playlist[1][3]  = 0;


        memset(&mci_play_parms, 0, sizeof(mci_play_parms));
        mci_play_parms.hwndCallback = hwndClient;
        mm_rc = pfnMciSendCommand( mci_open_parms.usDeviceID,
                                   MCI_PLAY|MCI_FROM, MCI_NOTIFY,
                                   &mci_play_parms, pMusic->mm_ID );
        if( mm_rc )
        {
            if( pfnMciGetErrorString &&
                !pfnMciGetErrorString(mm_rc, szStr, sizeof(szStr)) )
                Message("PlayMusic()\nError in MCI_PLAY.\n%s",szStr);
        }
        else
            pMusic->mm_Playing = TRUE;
    }
}




/*******************************************************************************
* AcquireAudioDevice()
*******************************************************************************/

void AcquireAudioDevice( HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2 )
{
    MCI_GENERIC_PARMS   mci_generic_parms;
    ULONG               mm_rc;


    if( !fDeviceAvailable || fAcquired )
        return;

    mci_generic_parms.hwndCallback = hwndClient;
    pfnMciSendCommand( mci_open_parms.usDeviceID,
                       MCI_ACQUIREDEVICE,
                       MCI_NOTIFY,
                       &mci_generic_parms,
                       0);
}



void PassDeviceProc( HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2 )
{
    if( SHORT1FROMMP(mp2) == MCI_GAINING_USE )
        fAcquired = TRUE;
    else
        fAcquired = FALSE;
}



/*******************************************************************************
* MusicNotifyProc()
*******************************************************************************/

void MusicNotifyProc( HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2 )
{
    PMM_MUSIC   pMusic;
    USHORT      usNotifyCode;
    USHORT      usUserParm;
    USHORT      usCommandMessage;
    LONG        wav;
    char        str[128];


    usNotifyCode     = SHORT1FROMMP(mp1);
    usUserParm       = SHORT2FROMMP(mp1);
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
            pMusic = FindMusic(usUserParm);
            if( pMusic )
                pMusic->mm_Playing = FALSE;
        }
    }
}



/*** Internal Functions *******************************************************/

/*******************************************************************************
* LoadWaveFile(szName, ulID)
*******************************************************************************/

static  BOOL LoadWaveFile(char *szName, ULONG ulID)
{
    PMM_MUSIC       pMusic;
    MMAUDIOHEADER   mmAudioHeader;
    HMMIO           hmmioFile;
    LONG            rc;
    ULONG           ulBytesRead;
    char            szFullPath[CCHMAXPATH];


    if (!pfnMmioOpen)
        return FALSE;

    snprintf(szFullPath, sizeof(szFullPath), "%s%s", szSoundsDir, szName);

    pMusic = malloc(sizeof(MM_MUSIC));

    pMusic->mm_ID   = ulID;
    pMusic->mm_Name = szFullPath;

    AddHead(&SampleList.mm_List, &pMusic->mm_Node);


    hmmioFile = pfnMmioOpen(szFullPath,
                            (PMMIOINFO)NULL,
                            MMIO_READ);

    if(hmmioFile == NULLHANDLE)
    {
        Message("LoadWaveFile()\nError loading '%s'.\nSound will not be available.",szFullPath);
        return FALSE;
    }

    rc = pfnMmioGetHeader(hmmioFile,
                          (PVOID)&mmAudioHeader,
                          sizeof(mmAudioHeader),
                          (PLONG)&ulBytesRead,
                          (ULONG)0,
                          (ULONG)0);

    if(rc != MMIO_SUCCESS)
    {
        Message("LoadWaveFile()\nCan't read header of '%s'.",pMusic->mm_Name);
        pfnMmioClose(hmmioFile, 0);
        return FALSE;
    }

    pMusic->mm_Len = mmAudioHeader.mmXWAVHeader.XWAVHeaderInfo.ulAudioLengthInBytes;

    memset(&pMusic->mm_Params, 0, sizeof(pMusic->mm_Params));
    pMusic->mm_Params.ulSamplesPerSec  = mmAudioHeader.mmXWAVHeader.WAVEHeader.ulSamplesPerSec;
    pMusic->mm_Params.usBitsPerSample  = mmAudioHeader.mmXWAVHeader.WAVEHeader.usBitsPerSample;
    pMusic->mm_Params.usChannels       = mmAudioHeader.mmXWAVHeader.WAVEHeader.usChannels;
    pMusic->mm_Params.ulAudio          = MCI_SET_AUDIO_ALL;

    pMusic->mm_Data = malloc(pMusic->mm_Len);

    rc = pfnMmioRead(hmmioFile,
                     (PSZ)pMusic->mm_Data,
                     pMusic->mm_Len);

    if(rc == MMIO_ERROR)
    {
        Message("LoadWaveFile()\nError reading '%s'.",pMusic->mm_Name);
        free(pMusic->mm_Data);
        pfnMmioClose(hmmioFile, 0);
        return FALSE;
    }

    pfnMmioClose(hmmioFile, 0);

    pMusic->mm_Loaded = TRUE;

    return TRUE;
}



/*******************************************************************************
* FreeWaveFile(pMusic)
*******************************************************************************/

static BOOL FreeWaveFile(PMM_MUSIC pMusic)
{
    if( pMusic->mm_Data)
        free(pMusic->mm_Data);

    RemoveNode(&pMusic->mm_Node);

    return TRUE;
}




/*******************************************************************************
* FindMusic(ulID)
*******************************************************************************/

static PMM_MUSIC FindMusic(ULONG ulID)
{
    PMM_MUSIC   pMusic;


    DOLIST(&SampleList.mm_List,pMusic)
    {
        if( pMusic->mm_Loaded && pMusic->mm_ID == ulID )
            return pMusic;
    }

    return NULLHANDLE;
}
