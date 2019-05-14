#ifndef ITOOLS_LISTS_H
#define ITOOLS_LISTS_H
/*
**
**	$Id: lists.h,v 9.1 1994/06/12 22:53:24 chris Exp $
**	$Revision: 9.1 $
**
**	$Filename: itools/lists.h $
**	$Author: chris $
**	$Release: 1.199 $
**	$Date: 1994/06/12 22:53:24 $
**
**	Support for access-protected lists
**
**	COPYRIGHT (C) 1991-1994 BY RELOG AG, ZUERICH. ALL RIGHTS RESERVED.
**	NO PART OF THIS SOFTWARE MAY BE COPIED, REPRODUCED, OR TRANSMITTED
**	IN ANY FORM OR BY ANY MEANS,  WITHOUT THE PRIOR WRITTEN PERMISSION
**	OF RELOG AG.
**
*/

#include <proto/exec.h>			/* $$$ sysdep */
#include <exec/semaphores.h>


/*
**	A generic list structure with access protection.
*/
struct ITList
{
	struct ITNode			*Head;		/* First node in list */
	struct ITNode			*Tail;		/* Always zero */
	struct ITNode			*TailPred;	/* Last node in list */
	struct SignalSemaphore	Semaphore;	/* For list arbitration (private!) */
};


/*
**  A generic node structure (16 bytes long!)
*/
struct ITNode
{
	struct ITNode	*Succ;
	struct ITNode	*Pred;
	UBYTE			Type;			/* ITNT_... */
	BYTE			Priority;
	STRPTR			Name;
	WORD			Flags;			/* ITNF_... */
};


/*
**	Node types
*/
#define ITNT_INVALID		0x00		/* Undefined node type */
#define ITNT_CLASS			0x01		/* Node is of type ITClass */
#define ITNT_OBJECT			0x02		/* Node is of type ITObject */
#define ITNT_LISTVIEW		0x03		/* Node is of type ITListViewNode */

#define ITNT_CUSTOM			0x40		/* Custom nodes begin here */

/*
**	Node flags
*/
#define ITNF_IGNORE			0x8000		/* Ignore this node. NOTE: Not always supported */
#define ITNF_SELECTED		0x0001		/* This node is currently selected */


/*
**	A special node used by the listview object
*/
struct ITListViewNode
{
	struct ITNode	Node;				/* Linkage */
	ULONG			TextStyle;			/* ITTSF_ ... flags */
	UWORD			FrontPen;			/* Text pen color, normally IT_TEXTPEN */
	UWORD			BackPen;			/* Text background, normally IT_BACKGROUNDPEN */
};



/*
**	Direct access control. You have to call these macros whenever you access
**	an ITList you don't own directly (i.e. not through an ITools function).
**
**	NOTE: Do NOT try to get a shared lock on a semaphore you have already
**	      locked exclusively, since this will result in a deadlock under 2.04.
*/
#define ITOBTAINLISTEXCLUSIVE(list)	ObtainSemaphore(&(list)->Semaphore)
#define ITOBTAINLISTSHARED(list)	ObtainSemaphoreShared(&(list)->Semaphore)
#define ITRELEASELIST(list)			ReleaseSemaphore(&(list)->Semaphore)


/*
**	Check for the presence of any nodes on the given list.	This
**	macro is even safe to use on lists that are modified by other
**	tasks.	However; if something is simultaneously changing the
**	list, the result of the test is unpredictable.
**
**	Unless you first arbitrated for ownership of the list, you can't
**	_depend_ on the contents of the list.  Nodes might have been added
**	or removed during or after the macro executes.
**
**		if( ITISLISTEMPTY(list) )		printf("List is empty\n");
*/
#define ITISLISTEMPTY(x) \
	( ((x)->TailPred) == (struct ITNode *)(x) )


/*
**	Process a list. If you are not the owner of the list, you must first
**	obtain a lock on it (see above).
*/
#define ITDOLIST(list, node) \
	for(node=(void *)(list)->Head; ((struct ITNode *)(node))->Succ; \
	(node)=(void *)(((struct ITNode *)(node))->Succ))


#endif /* ITOOLS_LISTS_H */
