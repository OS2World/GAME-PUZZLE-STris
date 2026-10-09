# Makefile for STris (Open Watcom C on OS/2 / ArcaOS)
# wmake 2.0.1 on ArcaOS - explicit per-file rules (no pattern rules)

# ============================================================================
# Configuration
# ============================================================================

NAME    = STris
SRCDIR  = src
BINDIR  = bin

!ifndef WATCOM
WATCOM  = C:\WATCOM
!endif

!ifndef WIPFC
WIPFC   = $(WATCOM)\wipfc
!endif

!ifndef OS2TK
OS2TK   = C:\OS2TK45
!endif

# ============================================================================
# Tools
# ============================================================================

CC      = wcc386
LINK    = wlink
RC      = wrc
IPFC    = wipfc

# ============================================================================
# Flags (per plan.txt section 2)
# ============================================================================

CFLAGS  = -bt=os2 -mf -5 -fpi -Oaxt -W3 -ze -d0
CFLAGS  = $(CFLAGS) -i=$(OS2TK)\h -i=$(SRCDIR)

RCFLAGS = -r -bt=os2 -i=$(OS2TK)\h -i=$(SRCDIR)

LFLAGS  = system os2v2_pm
LFLAGS  = $(LFLAGS) option stack=65536
LFLAGS  = $(LFLAGS) option map=$(BINDIR)\$(NAME).map

# ============================================================================
# Source files
# ============================================================================

GAME_OBJS = $(BINDIR)\about.obj $(BINDIR)\help.obj $(BINDIR)\hiscore.obj $(BINDIR)\hiscwindow.obj $(BINDIR)\key.obj $(BINDIR)\lang.obj $(BINDIR)\list.obj $(BINDIR)\options.obj $(BINDIR)\pieces.obj $(BINDIR)\playfield.obj $(BINDIR)\preferences.obj $(BINDIR)\sound.obj $(BINDIR)\stris.obj $(BINDIR)\stub.obj $(BINDIR)\timer.obj $(BINDIR)\window.obj

OBJS    = $(GAME_OBJS)

HLPDIR  = $(BINDIR)\help
HELPS   = $(HLPDIR)\STris_en.hlp $(HLPDIR)\STris_es.hlp $(HLPDIR)\STris_nl.hlp $(HLPDIR)\STris_de.hlp $(HLPDIR)\STris_fr.hlp $(HLPDIR)\STris_it.hlp

ROBJ    = $(BINDIR)\$(NAME).res
RCFILE  = $(SRCDIR)\$(NAME).rc
DEFFILE = $(SRCDIR)\$(NAME).def

# ============================================================================
# Targets
# ============================================================================

all : $(BINDIR)\$(NAME).exe helpfiles .SYMBOLIC

helpfiles : $(HELPS) .SYMBOLIC
	@echo Help files done

$(BINDIR) :
	@if not exist $(BINDIR) mkdir $(BINDIR)

$(BINDIR)\$(NAME).exe : $(OBJS) $(ROBJ) $(DEFFILE)
	@echo Linking $(NAME).exe...
	@$(LINK) $(LFLAGS) name $(BINDIR)\$(NAME).exe file $(BINDIR)\*.obj library os2386.lib
	@echo Binding resources...
	@$(RC) -q -bt=os2 -fe=$(BINDIR)\$(NAME).exe $(ROBJ) $(BINDIR)\$(NAME).exe
	@if exist $(BINDIR)\$(NAME).exe echo BUILD OK

# ============================================================================
# Game objects
# ============================================================================

$(BINDIR)\about.obj : $(SRCDIR)\about.c $(BINDIR)
	@echo Compiling src\about.c
	@$(CC) $(CFLAGS) -fo=$@ $(SRCDIR)\about.c

$(BINDIR)\help.obj : $(SRCDIR)\help.c $(BINDIR)
	@echo Compiling src\help.c
	@$(CC) $(CFLAGS) -fo=$@ $(SRCDIR)\help.c

$(BINDIR)\hiscore.obj : $(SRCDIR)\hiscore.c $(BINDIR)
	@echo Compiling src\hiscore.c
	@$(CC) $(CFLAGS) -fo=$@ $(SRCDIR)\hiscore.c

$(BINDIR)\hiscwindow.obj : $(SRCDIR)\hiscwindow.c $(BINDIR)
	@echo Compiling src\hiscwindow.c
	@$(CC) $(CFLAGS) -fo=$@ $(SRCDIR)\hiscwindow.c

$(BINDIR)\key.obj : $(SRCDIR)\key.c $(BINDIR)
	@echo Compiling src\key.c
	@$(CC) $(CFLAGS) -fo=$@ $(SRCDIR)\key.c

$(BINDIR)\lang.obj : $(SRCDIR)\lang.c $(BINDIR)
	@echo Compiling src\lang.c
	@$(CC) $(CFLAGS) -fo=$@ $(SRCDIR)\lang.c

$(BINDIR)\list.obj : $(SRCDIR)\list.c $(BINDIR)
	@echo Compiling src\list.c
	@$(CC) $(CFLAGS) -fo=$@ $(SRCDIR)\list.c

$(BINDIR)\options.obj : $(SRCDIR)\options.c $(BINDIR)
	@echo Compiling src\options.c
	@$(CC) $(CFLAGS) -fo=$@ $(SRCDIR)\options.c

$(BINDIR)\pieces.obj : $(SRCDIR)\pieces.c $(BINDIR)
	@echo Compiling src\pieces.c
	@$(CC) $(CFLAGS) -fo=$@ $(SRCDIR)\pieces.c

$(BINDIR)\playfield.obj : $(SRCDIR)\playfield.c $(BINDIR)
	@echo Compiling src\playfield.c
	@$(CC) $(CFLAGS) -fo=$@ $(SRCDIR)\playfield.c

$(BINDIR)\preferences.obj : $(SRCDIR)\preferences.c $(BINDIR)
	@echo Compiling src\preferences.c
	@$(CC) $(CFLAGS) -fo=$@ $(SRCDIR)\preferences.c

$(BINDIR)\sound.obj : $(SRCDIR)\sound.c $(BINDIR)
	@echo Compiling src\sound.c
	@$(CC) $(CFLAGS) -fo=$@ $(SRCDIR)\sound.c

$(BINDIR)\stris.obj : $(SRCDIR)\stris.c $(BINDIR)
	@echo Compiling src\stris.c
	@$(CC) $(CFLAGS) -fo=$@ $(SRCDIR)\stris.c

$(BINDIR)\stub.obj : $(SRCDIR)\stub.c $(BINDIR)
	@echo Compiling src\stub.c
	@$(CC) $(CFLAGS) -fo=$@ $(SRCDIR)\stub.c

$(BINDIR)\timer.obj : $(SRCDIR)\timer.c $(BINDIR)
	@echo Compiling src\timer.c
	@$(CC) $(CFLAGS) -fo=$@ $(SRCDIR)\timer.c

$(BINDIR)\window.obj : $(SRCDIR)\window.c $(BINDIR)
	@echo Compiling src\window.c
	@$(CC) $(CFLAGS) -fo=$@ $(SRCDIR)\window.c


# ============================================================================
# Resources. The bitmap files are referenced relative to the working
# directory, so wmake must run from the project root (see compile-wat.cmd).
# ============================================================================

$(ROBJ) : $(RCFILE) $(SRCDIR)\stris_id.h $(SRCDIR)\help.h src\Graphics\Label2.bmp src\Graphics\STris.ico $(BINDIR)
	@echo Compiling resources...
	@$(RC) $(RCFLAGS) -fo=$(ROBJ) $(RCFILE)

# ============================================================================
# Help files (one per language, wipfc)
# ============================================================================

$(HLPDIR) :
	@if not exist $(HLPDIR) mkdir $(HLPDIR)

$(HLPDIR)\STris_en.hlp : help\STris_en.ipf $(HLPDIR)
	@echo Compiling help\STris_en.ipf
	@set WIPFC=$(WIPFC)
	@$(IPFC) -l en_US -o $@ help\STris_en.ipf

$(HLPDIR)\STris_es.hlp : help\STris_es.ipf $(HLPDIR)
	@echo Compiling help\STris_es.ipf
	@set WIPFC=$(WIPFC)
	@$(IPFC) -l en_US -o $@ help\STris_es.ipf

$(HLPDIR)\STris_nl.hlp : help\STris_nl.ipf $(HLPDIR)
	@echo Compiling help\STris_nl.ipf
	@set WIPFC=$(WIPFC)
	@$(IPFC) -l en_US -o $@ help\STris_nl.ipf

$(HLPDIR)\STris_de.hlp : help\STris_de.ipf $(HLPDIR)
	@echo Compiling help\STris_de.ipf
	@set WIPFC=$(WIPFC)
	@$(IPFC) -l de_DE -o $@ help\STris_de.ipf

$(HLPDIR)\STris_fr.hlp : help\STris_fr.ipf $(HLPDIR)
	@echo Compiling help\STris_fr.ipf
	@set WIPFC=$(WIPFC)
	@$(IPFC) -l fr_FR -o $@ help\STris_fr.ipf

$(HLPDIR)\STris_it.hlp : help\STris_it.ipf $(HLPDIR)
	@echo Compiling help\STris_it.ipf
	@set WIPFC=$(WIPFC)
	@$(IPFC) -l en_US -o $@ help\STris_it.ipf

# ============================================================================
# Clean
# ============================================================================

clean : .SYMBOLIC
	@if exist $(BINDIR)\*.obj del $(BINDIR)\*.obj >nul
	@if exist $(BINDIR)\$(NAME).res del $(BINDIR)\$(NAME).res >nul
	@if exist $(BINDIR)\$(NAME).exe del $(BINDIR)\$(NAME).exe >nul
	@if exist $(BINDIR)\$(NAME).map del $(BINDIR)\$(NAME).map >nul
	@if exist $(HLPDIR)\*.hlp del $(HLPDIR)\*.hlp >nul
	@echo Clean complete