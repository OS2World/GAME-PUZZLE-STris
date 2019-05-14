:userdoc.
:title.Indexing Demo
:docprof toc=123.
.***************File Created with BookMaker ********************
.*****    Indexing Demo
.*****    11 Nov 1994
.*****    15:52:35
.***************************************************************
.************************************************************
:h1 res=1.
Overview
.************************************************************
:i1 id=1.Overview of Indexes
:p.
:color fc=darkblue bc=default.
:font facename=Helv size=36x20.Indexing:font facename=default size=0x0.
:color fc=default bc=default.
:i2 refid=1.Description
:p.
Indexing allows the user to search an index for a particular topic or
keyword in alphabetical order.  The indexing features of the Information
Presentation Facility allow the developer to set keywords and synonyms and
to place these keywords into appropriate order using the sortkey tag.
:p.
In this example &colon.h1 the words "Overview of Indexes" are used as a primary index
tag for the heading.  The word "Description" is a secondary heading, and
so it falls as a subheading to the first.
:note.
You don't need to insert an ID unless you're going to be using a secondary tag.

.************************************************************
:h1 res=2.
Index Order
.************************************************************
:i1.Index Order
:p.
Notice that in the index, "Index Order" comes before "Overview".  By default, an index
is alphabetical.  A secondary index is listed in alphbetical order beneath it's primary.
:i1 sortkey='ZZZZ'.A Placement Example
Notice that "A Placement Example" is listed at the end of our index.  In this case
"A Placement Example"  would normally come first in our list, but we have changed
it's sort order to "ZZZZ" which places it last.  
.************************************************************
:h1 res=3.
Index Synonyms
.************************************************************
:i1 roots='fruit'.Index Synonyms
:isyn root=fruit.apple pear banana peach grape
:p.
Index synonyms are used as a sort of invisible secondary index to
your document.  It's a bit difficult to explain in an online document.  We
add the word -A-p-p-l-e- (we're using the actual word in the synonym
tag, but I don't want the search engine to see it in the actual document)
as an example.  This page is located under "Index Synonyms", but if
you search the index for -A-p-p-l-e-(minus the dashes) you'll see that
the page comes up in your search.  Try some other fruits and see if you
can come up with the something.
:p.
In this example we set a root word for the heading and then associated
root word with the synonyms we chose for the word. 
.************************************************************
:h1 res=4.
Global Attributes
.************************************************************
:i1.Global Setting
:p.
You'll notice in the BookMaker Index window that there's a checkbox
for a global tag.  This tag is valid only in Help (*.hlp) windows.  Using this tag
will add a topic to the OS/2 Master Help Index.
 
 







:euserdoc.
