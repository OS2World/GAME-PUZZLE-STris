:userdoc.
:title.Linking Demo
:docprof toc=123.
.***************File Created with BookMaker ********************
.*****    Linking Demo
.*****    23 Sep 1994
.*****    12:04:42
.***************************************************************
.************************************************************
:h1 res=1.
Introduction
.************************************************************
:p.
:color fc=darkblue bc=default.
:font facename=Helv size=36x20.Linking Demo - :hp1.Introduction:ehp1.
:font facename=default size=0x0.
:color fc=default bc=default.
:p.
This IPF file introduces you to the linking functions built
into BookMaker.  Using links, you'll be able to set keywords to link to
headings which describe or are related to the particular topic.
:lines align=left.
The following topics are linked to headings.
:link reftype=hd res=2.Linking:elink.
:link reftype=hd res=3.Footnotes:elink.
:link reftype=hd res=4.Artlinks:elink.
:elines.
.************************************************************
:h1 res=2.
Linking
.************************************************************
:p.
This page was linked to the previous through the word linking. 
This was done by selecting the word Linking and double clicking
the Link option in the toolbar.  The res number for the link was changed
to 2 because this is the number which was automatically created during the creation
of this page.
.************************************************************
:h1 res=3.
Footnotes
.************************************************************
:p.
This page decribes :link refid=footnotes reftype=fn.footnotes:elink.
:fn id=footnotes. This is an example of a footnote.  A small window opens to describe the term selected.:efn..  
In this example, the word footnotes in
the previous sentance was selected and the Footnote option was applied.
This allows you to define terms throughout your document.  Keep in mind
that selecting more than one word for use as a footnote will probably give you an error
during compile.
.************************************************************
:h1 res=4.
Artlink
.************************************************************
:p.
This example contains an artlink.
:artwork align=left name='F:\Projects\INF_MASTER\bookmaker.BMP' .
:artlink.
:link reftype=hd res=5.
:eartlink.
:artwork align=left name='F:\GRAFIX\KATTLSML.BMP' .
:artlink.
:link reftype=hd res=5.
:eartlink.

:p.
This page is connected to a hidden window by use of an artlink.  The
link is defined within each Artwork selection window.  The res number 5
was added to the bitmap specification and the link was automatically
palced around the selection.

.************************************************************
:h1 res=5
hide .
Linked Page
.************************************************************
:p.
This is a hidden window accessed by the bitmaps on the artlink page.  
For more information concerning windows capabilities see Windows.INF.






:euserdoc.
