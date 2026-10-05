/*******************************************************************************
*																			   *
* LIST.H																	   *
* ------																	   *
*																			   *
* Include File for LIST.C													   *																			  *
*																			   *
*******************************************************************************/

#ifndef LIST_H
#define LIST_H



/*** Defines ******************************************************************/

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
#define ISLISTEMPTY(x) \
	( ((x)->lh_TailPred) == (PNODE)(x) )


/*
**	Process a list. If you are not the owner of the list, you must first
**	obtain a lock on it (see above).
*/
#define DOLIST(list, node) \
	for(node=(void *)(list)->lh_Head; ((PNODE)(node))->ln_Succ; \
	(node)=(void *)(((PNODE)(node))->ln_Succ))



typedef struct _List
{
	struct  _Node	*lh_Head,
					*lh_Tail,
					*lh_TailPred;
	char			*lh_Name;
} LIST;

typedef LIST *PLIST;


typedef struct _Node
{
	struct	_Node	*ln_Succ,
					*ln_Pred;
	BYTE			ln_Type;			/* ITNT_... */
	BYTE			ln_Priority;
	char			*ln_Name;
	SHORT			Flags;				/* ITNF_... */
} NODE;

typedef NODE *PNODE;



/*** Prototypes ***************************************************************/

extern	void NewList(PLIST);
extern	void AddHead(PLIST, PNODE);
extern	void RemoveNode(PNODE);


/*** Variables ****************************************************************/



#endif /* LIST_H */



