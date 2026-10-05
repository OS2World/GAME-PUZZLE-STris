:userdoc.
:title.STris V1.40 Online-Help
:docprof toc=123.
:ctrldef.
:ctrl ctrlid=new1 controls='ESC PRINT CONTENTS BACK FORWARD' coverpage.
:ectrldef.


.************************************************************
:h1 res=1000 name=HELP_GENERAL
 x=right y=top
 width=100% height=100%.
General
.************************************************************
:p.:lines align=center.
:color fc=darkblue bc=default.
:font facename='Tms Rmn' size=36x20.STris V1.40:font facename=default size=0x0.
:color fc=default bc=default.
:elines.

:p.I'd like to welcome you to STris, which simply stands
for Straub's Tetris.

:p.STris is my first project developed under OS/2. I was looking for a program where
I could learn the basics in OS/2 programming. As a great fan of Tetris games
I was somewhat disappointed by the existing Tetris versions I found, so I decided
to write one by myself.
If you are an old-fashioned Amiga-user (like me)  you may recognize some parallels to
WBTris written by Dirk Bîhmer and Ralf Pieper.

:lines.

:lm margin=30.Have fun with STris

:lm margin=40.:font facename='Courier' size=18x14.RenÇ Straub:font facename=default size=0x0.
:lm margin=1.
:elines.



.************************************************************
:h1 res=2000 name=HELP_COPYRIGHT.
Copyright
.************************************************************
:p.:lines align=center.
:color fc=darkblue bc=default.
:font facename='Tms Rmn' size=36x20.Copyright:font facename=default size=0x0.
:color fc=default bc=default.
:elines.

:rm margin=5.
:artwork align=right name='..\graphics\copyrght.bmp' .

:p.All right's on STris, including copyright, belong to the
:link reftype=hd res=2200.author.:elink. .

STris is Shareware. Please :link reftype=hd res=15000.click here.:elink.
for further information about purchasing STris.




.************************************************************
:h1 res=2100 name=HELP_DISCLAIMER.
Disclaimer
.************************************************************
:p.:lines align=center.
:color fc=darkblue bc=default.
:font facename='Tms Rmn' size=36x20.Disclaimer:font facename=default size=0x0.
:color fc=default bc=default.
:elines.

:p.This program is provided as is. You may use it only at your own risk.
:p.STris is supplied with no warranty, neither expressed nor implied. We disclaim
all warranties for any damages included but not limited to incidental or consequential
damaged caused directly or indirectly by this software.
:p.STris mustn't be used in states that do not allow the above limitation of liability.


.************************************************************
:h1 res=2200 name=HELP_AUTHOR.
The Authors
.************************************************************
:p.:lines align=center.
:color fc=darkblue bc=default.
:font facename='Tms Rmn' size=36x20.The Authors:font facename=default size=0x0.
:color fc=default bc=default.

.*:rm margin=5.
.*:artwork align=right name='..\graphics\label2.bmp' .

:elines.
:p.:lines.
Programming, Graphics,             Hiscore Mangement
Online-Help
:font facename=Courier size=14x10.

.*:lm margin=6.
RenÇ Straub                       Thomas SchÑr
Talstrasse 4                      Schlattweg 4
CH-5726 Unterkulm                 CH-4147 Aesch BL
Switzerland                       Switzerland
Tel.  +41 62 776 26 61
Fax   +41 62 776 14 17
EMail straub@crack.aare.ch
:lm margin=1.
:elines.


.************************************************************
:h1 res=2300 name=HELP_CREDITS.
Credits
.************************************************************
:p.:lines align=center.
:color fc=darkblue bc=default.
:font facename='Tms Rmn' size=36x20.Credits:font facename=default size=0x0.
:color fc=default bc=default.
:elines.

:p.I'd like to dedicate this page to all people that helped me during the development of STris. Special thanks go
to these persons:

:font facename=Courier size=14x10.
:p.:lines.
:lm margin=6.
Thomas SchÑr        : Hiscore management
Hillary Bannister   : Proof reading
Dirk Bîhmer and     : Amiga Version (WBTris)
Ralf Pieper
Chris Haller        : Beta testing
Chris Weber         : Owner of ftp.relog.ch
:lm margin=1.

:elines.
:font facename=default size=0x0.

:p.Greetings also go to the following persons:

:font facename=Courier size=14x10.
:lm margin=6.
:p.Erich Bachfischer, Stefan LÅscher, Urs Kyburz, Class Ec93, RenÇ Siegrist, SWF3 Radio
and to all those I forgot.
:font facename=default size=0x0.
:lm margin=1.



.************************************************************
:h1 res=3100 name=HELP_INSTALLATION.
Installation
.************************************************************
:p.:lines align=center.
:color fc=darkblue bc=default.
:font facename='Tms Rmn' size=36x20.Installation:font facename=default size=0x0.
:color fc=default bc=default.
:elines.

:p.If you are reading this text you have already installed STris succesfully. So there is no
need to lose a lot of words about the installation procedure.



.************************************************************
:h1 res=3300 name=HELP_UNINSTALLING.
Uninstallation
.************************************************************
:p.:lines align=center.
:color fc=darkblue bc=default.
:font facename='Tms Rmn' size=36x20.Uninstalling:font facename=default size=0x0.
:color fc=default bc=default.
:elines.

:p.I can't believe it. You really want to throw STris away. Nothing easier than that. STris does not need
any DLL's and it does not modify your CONFIG.SYS or any other system files. If you want to get rid of
STris you can simply delete it's directory and the WPS Object created by the Installscript.



.************************************************************
:h1 res=4000 name=HELP_HOWTOPLAY.
How to play
.************************************************************
:p.:lines align=center.
:color fc=darkblue bc=default.
:font facename='Tms Rmn' size=36x20.How to play:font facename=default size=0x0.
:color fc=default bc=default.
:elines.

:p.Hey, you really want to tell me that you don't know how to play Tetris. You must
be kidding.

:p.The main goal in this type of games is to navigate the falling pieces so that they
fill up horizontal lines. If a line is entirely filled it disappears and you get lots of
points. The game ends when there is no more space for a new piece.

:p.The falling piece is controlled with the cursor keys. You can move the piece left/right and
you can rotate it. As the game goes on the falling speed of the pieces increases

:p.:link reftype=hd res=4100.Click here.:elink. if you want to see the key-bindings.

:p.So I think that's all you need to know for the moment. Any more questions ?



.************************************************************
:h1 res=4100 name=HELP_KEYS.
The Keys
.************************************************************
:p.:lines align=center.
:color fc=darkblue bc=default.
:font facename='Tms Rmn' size=36x20.The Keys:font facename=default size=0x0.
:color fc=default bc=default.
:elines.

:p.You don't need a lot of keys to play STris. These are the relevant ones

:font facename=Courier size=14x8.
:lines.
:lm margin=6.
:hp2.Function       Key              NumPad:ehp2.

Move Left       Cursor Left      4
Move Right      Cursor Right     6
Rotate          Cursor Up        8
Rotate                           5
Drop            Cursor Down      2
Toggle Pause    Toggle Pause
:elines.
:lm margin=1.
:font facename=default size=0x0.

:p.Please note that if you want use the numeric keypad NumLock has to be enabled.

:p.With V1.40 of STris it finally happened. You can now define your own keys. Use the
'Define Keys' Dialog found in the 'Game' menu. There are some limitations in defining
keys. You can't redefine keys that are used by STris itself and there are
some keys that are currently not supported.

:p.As in any good OS/2 program there are shortcuts for most of the functions in STris.



.************************************************************
:h1 res=5000 name=HELP_BUGS.
Bugs / Reporting
.************************************************************
:p.:lines align=center.
:color fc=darkblue bc=default.
:font facename='Tms Rmn' size=36x20.Bugs / Reporting:font facename=default size=0x0.
:color fc=default bc=default.
:elines.

:p.This program has been written using the most sophisticated programming and debugging
tools available. So it is absolutely impossible for you to find any bugs in STris.

:p.Did you believe that ? I supposse you did not. Ok to become more serious.
Throughout intensive tests I haven't found severe bugs in STris.
If you detect any please write a short bug-report containing at least the
following information:

:lines.
 - the version of STris
 - your system (eg. CPU, Graphics adapter etc.)
 - the bug itself (and how it can be reproduced)

and send it the following EMail address:

                       straub@crack.aare.ch
:elines.




.************************************************************
:h1 res=6000 name=HELP_REVISIONS.
Revisions
.************************************************************
:p.:lines align=center.
:color fc=darkblue bc=default.
:font facename='Tms Rmn' size=36x20.Revisions:font facename=default size=0x0.
:color fc=default bc=default.
:elines.

:font facename=Courier size=14x8.
:p.:lines.:hp2.Date      Version      Description:ehp2.

14.03.1996 V1.40        User definable Keys
                        New Hiscore entry will be hilighted
                        Larger score field in HiscoreWindow
                        New scoring method
                        RemainPaused-flag
                        New drop-handler that let's you move the piece before placing

21.09.1995 V1.35        Sound effects implemented

08.09.1995 V1.27        Added first (incomplete) version of OnlineHelp

02.06.1995 V1.22 BETA   Added Install-Script
                        Shortened configuration file STris.INI

23.05.1995 V1.21 BETA   First version released.

02.06.1995 V1.12        Fixed bug in OptionsDialog that could lock the PaletteGadget

:elines.

:font facename=default size=0x0.



.************************************************************
:h1 res=11000 name=HELP_OPTIONS
 hide.
Options
.************************************************************
:p.:lines align=center.
:color fc=darkblue bc=default.
:font facename='Tms Rmn' size=36x20.Options:font facename=default size=0x0.
:color fc=default bc=default.
:elines.

:p.
<Under construction>



.************************************************************
:h1 res=12000 name=HELP_HISCORE
 hide.
Hiscore
.************************************************************
:p.:lines align=center.
:color fc=darkblue bc=default.
:font facename='Tms Rmn' size=36x20.Hiscore:font facename=default size=0x0.
:color fc=default bc=default.
:elines.

:p.
Do I need to lose a lot of words about this one. This is the
STris Hall of Fame where only the finest STris players are
allowed to enter. Just try if you can make it to the top...



.************************************************************
:h1 res=13000 name=HELP_ENTER_HISCORE
 hide.
Enter Name
.************************************************************
:p.:lines align=center.
:color fc=darkblue bc=default.
:font facename='Tms Rmn' size=36x20.Enter Hiscore:font facename=default size=0x0.
:color fc=default bc=default.
:elines.

:p.You have reached a score that will allow you to enter the
Stris Hall of Fame. Enter your name in the entry field.



.************************************************************
:h1 res=14000 name=HELP_DEFINE_KEYS
 hide.
Define Keys
.************************************************************
:p.:lines align=center.
:color fc=darkblue bc=default.
:font facename='Tms Rmn' size=36x20.Define Keys:font facename=default size=0x0.
:color fc=default bc=default.
:elines.

:p.
<Under construction>






.************************************************************
:h1 res=15000 name=HELP_REGISTRATION
 hide.
Registration
.************************************************************
:p.:lines align=center.
:color fc=darkblue bc=default.
:font facename='Tms Rmn' size=36x20.Registration:font facename=default size=0x0.
:color fc=default bc=default.
:elines.

:p.STris V1.40 is Shareware. You may use it for a 30 day trial
period, after which you must purchase it. If you buy STris you will
get an unique registration code that will:

:p.Remove all dialogs reffering to registration
:p.Allow you to upgrade to all future versions of STris
:p.Provide you with support through EMail

:p.The cost of STris is 20 US dollar. You can order STris through
BMT Micro. Payment can be made by cash, cheque or all major credit
cards.

:link reftype=hd res=15001.Click here to see order form.:elink.

Send your order form containg postal or EMail adress to .....,
 ...., ..... .




.************************************************************
:h1 res=15001 name=HELP_REG_FORM
 hide.
Registration form
.************************************************************
:p.:lines align=center.
:color fc=darkblue bc=default.
:font facename='Tms Rmn' size=36x20.Registration form:font facename=default size=0x0.
:color fc=default bc=default.
:elines.


:lines.
:font facename=Courier size=14x8.

 Name    _________________________________________________________________

 Address _________________________________________________________________

         _________________________________________________________________

         _________________________________________________________________

 Email address ___________________________________________________________

 Email type  ____Internet  ____Compuserve   Other_________________________

 Ship to (check one)  ____Regular mail    ____Email

 Where did you find STris ________________________________________________

 - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

 ________  STris registration fee (20.00 US $)
 ________  7% PST  (BC residents only)

 ________  Total enclosed

 - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

 Mail registration fee (cheque or money order drawn on Canadian or US bank,
 payable to xxxx Software) and this form to:

     Registration, xxxx Software, yyy, zzz,
     Vancouver, BC, CANADA, V6R 1G0

 - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  Comments or Suggestions:







:elines.

:font facename=default size=0x0.



.************************************************************
:h1 res=32000 name=HELP_EMPTY_PAGE
 hide.
Empty Page
.************************************************************
:p.:lines align=center.
:color fc=darkblue bc=default.
:font facename='Tms Rmn' size=36x20.Empty Page:font facename=default size=0x0.
:color fc=default bc=default.
:elines.

:p.If you are reading this text then the author was too lazy to
write a decent help text.

:euserdoc.


