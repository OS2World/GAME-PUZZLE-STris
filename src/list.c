/*******************************************************************************
*																			   *
* LIST.C																	   *
* ------																	   *
*																			   *
* Double-Linked-List Routines												   *
*																			   *
* Modification History: 													   *
* --------------------- 													   *
*																			   *
* 01.06.96	RHS  Created this file											   *
*																			   *
*******************************************************************************/

#define INCL_WIN

#include <os2.h>
#include <stdio.h>
#include <string.h>

#include "list.h"



void NewList(PLIST list)
{
	list->lh_Head		= (PNODE)&list->lh_Tail;
	list->lh_Tail		= NULL;
	list->lh_TailPred	= (PNODE)&list->lh_Head;
}



void AddHead(PLIST list, PNODE node)
{
	PNODE			ptr;

	ptr				= list->lh_Head;
	list->lh_Head	= node;
	node->ln_Succ	= ptr;
	node->ln_Pred	= (PNODE)list;
	ptr->ln_Pred	= node;
}



void RemoveNode(PNODE node)
{
	PNODE	nextnode,
			lastnode;


	nextnode			= node->ln_Succ;
	lastnode			= node->ln_Pred;
	lastnode->ln_Succ	= nextnode;
	nextnode->ln_Pred	= lastnode;
}




