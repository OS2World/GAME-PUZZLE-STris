:userdoc.
:title.Basic Demo
:docprof toc=123.
.***************File Created with BookMaker ********************
.*****    Basic Demo
.*****    22 Sep 1994
.*****    04:29:17
.***************************************************************
.************************************************************
:h1 res=1.
Introduction (Page 1)
.************************************************************
:p.
This file will demonstrate building a simple INF or HLP file.  
The source for this file is available as BASIC.IPF.
:p.
This type of file can be created simply and easily by inserting pages,
paragraphs, lines and lists, one after the other using BookMaker.  Click
forward to see the next page which contains additional enhancements to
simple paragraphs.
:p.
This page was created by selecting File/New, typing in a Title and then
clicking on page.  At the Insert Heading dialog, I typed in Introduction and hit return. 
I then selected Paragraph and typed in each paragraph seperately.
:p.
Because Options/Autosave is checked, the file is saved after every dialog
is presented.

.************************************************************
:h1 res=2.
Page 2
.************************************************************
:p.
The second page was created the same way as the first.  Notice
that the res (resource id) number automatically jumped one.  Within
the same session, the res number is automatically increased with every
new page.
:p.
Click forward to see the next page.
.************************************************************
:h1 res=3.
Page 3
.************************************************************
:p.
:font facename=Helv size=48x28.Surprise:font facename=default size=0x0.
:p.
The preceeding word was enhanced.  This was done by creating the
word with a paragraph tag and then selecting the word in the main
BookMaker window.  I then clicked font and at the Font Dialog selected
Helv  48x28.  The new font was added to the begining of the selected
word and the defaults were placed at the end of the word.  In the
following paragraph the same is done only this time an entire paragraph
is selected.
:p.
:color fc=darkcyan bc=default.
:font facename=Helv size=14x8.The words in this paragraph are enhanced in two ways.  First
they are selected and the Font is changed.  They are selected once again and the
color is changed.  (It's OK to select the font tags with the text.  Just
be sure to get the whole thing.):font facename=default size=0x0.
:color fc=default bc=default.
:p.
You can select almost anything and apply tags to your selection.  The exceptions
are artwork, tables, lists, and autotags.
.************************************************************
:h1 res=4.
Page 4 (Primary)
.************************************************************
:p.
This page is listed as primary.  The box preceeding the heading in
the TOC indicates that there is a sub-heading.  Press forward to see the next page.
.************************************************************
:h2 res=5.
Page 4 Level 2
.************************************************************
:p.
When this Heading was created I selected Heading 2.  This made the
window a sub-heading of Page 4
.************************************************************
:h1 res=6.
Page 5 Lines
.************************************************************
:p.
In this page we'll use lines of text.  Using this tag you won't have
to add a paragraph for each line.
:lines align=left.
This is the first line.
This is the second.
This is the third.
These lines are left justified.
:elines.
:lines align=center.
This is a single line that is centered
:elines.
:color fc=red bc=default.
:font facename='Tms Rmn' size=24x14.:lines align=right.
This is a single line that is right justified.
Notice that we changed the font and color.
:elines.:font facename=default size=0x0.
:color fc=default bc=default.
.************************************************************
:h1 res=7.
Page 7 Lists
.************************************************************
:p.
This page demonstrates lists.
:p.This is a caption (optional)&colon.
:ol.
:li.Item 1
:ol.
:li.This list is placed within another
:eol.
:li.Item 2
:li.Item 3
:li.Remember this is an ordered (numbered) list
:eol.
:p.This is an unordered list&colon.
:ul.
:li.Item 1
:li.Item 2
:li.Item 3
:eul.

:font facename=Courier size=14x8.
:p.This is a simple list&colon.
:sl compact.
:li.Item 1
:li.Item 2
:li.Item 3
:li.Notice that this list is compact
:esl.
:font facename=default size=0x0.
:p.
In the last list I changed the font.
.********This comment will not be seen in the file********
.************************************************************
:h1 res=8.
Page 8 Example Text
.************************************************************
:p.
This page contains the example tag.  Notice that the font is automatically
changed.  This is used mostly for code examples.
:xmp.
#define  INCL_DOS
#include <os2.h>
#include <malloc.h>
#include <process.h>
#include <stdio.h>
#include <stdlib.h>


int main( int argc, char * argv[] );
void childcode( void * arg );

typedef struct            /* the thread information structure          */
{                         /*                                           */
   unsigned count;        /* the number of times to display the text   */
   HEV      hev  ;        /* the individual thread's event semaphore   */
}  THREAD_INFO ;          /* handle                                    */
:exmp.
.************************************************************
:h1 res=9.
Page 9 (Highlighted Text)
.************************************************************
:p.
Within this :hp1.paragraph:ehp1.
 are selected words with various :hp7.highlight:ehp7.
characteristics.  This was done by selecting certain words within the
:hp8.paragraph:ehp8.
and selecting :hp2.Highlight.:ehp2.
.************************************************************
:h1 res=11.
Page 10 (Graphics)
.************************************************************
:p.
Graphics are one of the main enhancements to any INF file. 
This and the following page include Three graphics examples.
:cgraphic.
ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
³                            ³
³  This is a Character       ³
³  Graphics example.         ³
³  Its a simple way to       ³
³  to create boxesÚÄÄÄÄ¿     ³
³                 ³    ³     ³
³                 ÀÄÄÄÄÙ     ³
³    and the like.           ³
ÃÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ´
³ It takes some practice!    ³
ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ 
:ecgraphic.

:artwork align=left name='F:\GRAFIX\PLMTREES.BMP' .
:p.
This is a left aligned bitmap.
:p.
Click forward to see the same bitmap as a full page graphic.
.************************************************************
:h2 res=12.
Full Page Graphic
.************************************************************

:artwork align=left name='F:\GRAFIX\PLMTREES.BMP' fit.
:p.
In this example fit to page was selected.  The picture is stretched
so it appears strange.  You can manipulate pages to fix this.  See
Windows.INF for details on this.
.************************************************************
:h1 res=13.
Table
.************************************************************
:table cols='10 10 10 10' rules=both frame=box.
:row.
:c.Computer
:c. Monitor
:c. CD-ROM
:c. Modem
:row.
:c.Pentium
:c. NEC
:c. NEC
:c. Hays
:row.
:c.486
:c. STAR
:c. Creative
:c. Practical
:row.
:c.386
:c. IBM
:c. Philips
:c. ZOOM
:etable.
:p.
This table was created by selecting the table option and inserting text
into each listbox.  The width of each column was changed to ten. 
Keep in mind that you must fill all spaces in the first column for
the other rows you wish to show.  For example if the first column contains
4 items and one of the others contains five, you must insert a blank
space into the first column to make up the difference.



.************************************************************
:h1 res=10.
A final word...
.************************************************************
:p.
Keep in mind that all rules for your IPF compiler still apply.  You can
get a better idea of what's really possible and not possible by going
through ipfc20.inf(included with your IPF compiler) first.
:p.
:color fc=blue bc=default.
:hp3.My old bosses always got mad at me because I always made them read the manual!:ehp3.
:color fc=default bc=default.
:p.
If you're new to IPF creation, play with the basics first.  When you're ready,
read the Linking.INF file.






:euserdoc.


