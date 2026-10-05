### Definitionen ##################################################################################################

.AUTODEPEND

INCPATH = E:\Programming\Toolkit\H;E:\Programming\BorlandC\Include
LIBPATH = E:\Programming\Toolkit\Lib;E:\Programming\BorlandC\Lib

PRGCC   = bcc +STris.cfg
PRGLINK = tlink
PRGRC   = rc


ALL:	STris.exe


### Regeln #########################################################################################################

.c.obj:
	$(PRGCC) -c {$< }

.rc.res:
	$(PRGRC) -r -i $(INCPATH) $*.rc



### Files ##########################################################################################################

MODS =	stris.obj window.obj playfield.obj pieces.obj hiscore.obj sound.obj options.obj \
		hiscwindow.obj key.obj timer.obj stub.obj preferences.obj help.obj \
        registration.obj crc.obj about.obj list.obj



### STrisProgram ###############################################################

stris.exe: stris.cfg $(MODS) stris.res
  $(PRGLINK) -B:10000 /c /x /Toe /aa /L$(LIBPATH) @&&|
    E:\Programming\BorlandC\Lib\C02.OBJ+
    $(MODS)
    STris
        #no map file
    E:\Programming\BorlandC\Lib\C2.lib+
    E:\Programming\BorlandC\Lib\OS2.lib+
    E:\Programming\Toolkit\Lib\mmpm2.lib,
	STris
|
    rc.exe -p -x2 STris.res stris.exe


### Distribution (pack .exe-file, copy changed files, create archive) ##########

Dist: stris.exe
	  update



### Abh„ngigkeiten #################################################################################################

stris.obj:			stris.cfg stris.c
window.obj:			stris.cfg window.c
playfield.obj:		stris.cfg playfield.c
pieces.obj:			stris.cfg pieces.c
hiscore.obj:		stris.cfg hiscore.c
hiscwindow.obj:		stris.cfg hiscwindow.c
timer.obj:			stris.cfg timer.c
options.obj:		stris.cfg options.c
about.obj:			stris.cfg about.c
preferences.obj:	stris.cfg preferences.c
sound.obj:			stris.cfg sound.c
help.obj:			stris.cfg help.c
stub.obj:			stris.cfg stub.c
crc.obj:			stris.cfg crc.c
key.obj:			stris.cfg key.c


### Config File #####################################################################################################

stris.cfg: makefile
    copy &&|
-R
-L$(LIBPATH)
-I$(INCPATH)
-vi-
-k-
-Ot
-y
-v
-N
-a4
-w-par
| stris.cfg


