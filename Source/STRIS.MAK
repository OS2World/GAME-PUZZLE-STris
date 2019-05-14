#=============================================================
#
#	STRIS.MAK - Makefile for project f:\projects\stris\stris.prj
#		Created on 09/16/95 at 18:21
#
#=============================================================

.AUTODEPEND

#=============================================================
#		Translator Definitions
#=============================================================
CC = bcc +STRIS.CFG
TASM = tasm.exe
TLIB = tlib.exe
TLINK = tlink
RC = brcc.exe
RB = rc.exe
LIBPATH = E:\PROGRAMMING\BORLANDC\LIB;E:\Programming\Toolkit\Lib
INCLUDEPATH = E:\PROGRAMMING\BORLANDC\INCLUDE;E:\Programming\Toolkit\H


#=============================================================
#		Implicit Rules
#=============================================================
.c.obj:
  $(CC) -c {$< }

.cpp.obj:
  $(CC) -c {$< }

.asm.obj:
  $(TASM) -Mx $*.asm,$*.obj

.rc.res:
  $(RC) -r $*.rc

#=============================================================
#		List Macros
#=============================================================
LINK_EXCLUDE =  \
 stris.res

LINK_INCLUDE =  \
 hiscore.obj \
 sound.obj \
 e:\programming\toolkit\lib\mmpm2.lib \
 options.obj \
 hiscwindow.obj \
 playfield.obj \
 stris.obj \
 pieces.obj \
 window.obj \
 about.obj \
 timer.obj \
 stub.obj \
 preferences.obj \
 help.obj

#=============================================================
#		Explicit Rules
#=============================================================
stris.exe: stris.cfg $(LINK_INCLUDE) $(LINK_EXCLUDE)
  $(TLINK) /c /x /Toe /aa /L$(LIBPATH) @&&|
E:\PROGRAMMING\BORLANDC\LIB\C02.OBJ+
hiscore.obj+
sound.obj+
options.obj+
hiscwindow.obj+
playfield.obj+
stris.obj+
pieces.obj+
window.obj+
about.obj+
timer.obj+
stub.obj+
preferences.obj+
help.obj
stris
		# no map file
e:\programming\toolkit\lib\mmpm2.lib+
E:\PROGRAMMING\BORLANDC\LIB\C2.LIB+
E:\PROGRAMMING\BORLANDC\LIB\OS2.LIB

|
  rc.exe STris.res stris.exe

#=============================================================
#		Individual File Dependencies
#=============================================================
hiscore.obj: stris.cfg hiscore.c 

sound.obj: stris.cfg sound.c 

options.obj: stris.cfg options.c 

hiscwindow.obj: stris.cfg hiscwindow.c 

playfield.obj: stris.cfg playfield.c 

stris.obj: stris.cfg stris.c 

pieces.obj: stris.cfg pieces.c 

window.obj: stris.cfg window.c 

about.obj: stris.cfg about.c 

timer.obj: stris.cfg timer.c 

stub.obj: stris.cfg stub.c 

STris.res: stris.cfg STRIS.RC 
	brcc.exe -R -I$(INCLUDEPATH) -FO STris.res STRIS.RC

preferences.obj: stris.cfg preferences.c 

help.obj: stris.cfg help.c 

#=============================================================
#		Compiler Configuration File
#=============================================================
stris.cfg: stris.mak
  copy &&|
-R
-L$(LIBPATH)
-I$(INCLUDEPATH)
-H=f:\projects\stris\stris.CSM
-vi-
-k-
-Ot
-y
-v
-N
-w-par
| stris.cfg


