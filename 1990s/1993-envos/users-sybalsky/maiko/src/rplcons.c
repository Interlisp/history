/* @(#) rplcons.c Version 2.10 (2/8/93). copyright venue*/
static char *id = "@(#) rplcons.c	2.10 2/8/93		(venue)";



/************************************************************************/
/*									*/
/*	(C) Copyright 1989-92 Venue. All Rights Reserved.		*/
/*	Manufactured in the United States of America.			*/
/*									*/
/*	The contents of this file are proprietary information 		*/
/*	belonging to Venue, and are provided to you under license.	*/
/*	They may not be further distributed or disclosed to third	*/
/*	parties without the specific permission of Venue.		*/
/*									*/
/************************************************************************/

/***********************************************************************/
/*
 		File Name :	rplcons.c

		Desc	:	rplcons
 
		Including :	rplcons
				OP_rplcons
				
*/
/**********************************************************************/

#include "lispemul.h"
#include "emlglob.h"
#include "lspglob.h"
#include "lsptypes.h"
#include "address.h"
#include "adr68k.h"
#include "gc.h"
#include "cell.h"    

/***************************************************/

N_OP_rplcons(list, item)
  register LispPTR list;
  register LispPTR item;
  {
    register struct conspage *conspage ;
    register ConsCell *new_cell , *list68k;

    LispPTR register page;

    if(!Listp(list)) ERROR_EXIT(item);

    page = POINTER_PAGE(list);
    list68k=(ConsCell *)Addr68k_from_LADDR(list);

    /* There are some rest Cell and "list" must be ONPAGE cdr_coded */
#ifndef NEWCDRCODING
    if((GetCONSCount(page) != 0) && (list68k->cdr_code > CDR_MAXINDIRECT))
      {
	GCLOOKUP(item, ADDREF);
	GCLOOKUP(cdr(list), DELREF);

	conspage = (struct conspage *)Addr68k_from_LPAGE(page);
	new_cell =(ConsCell *)GetNewCell_68k(conspage);

	conspage->count--;
	conspage->next_cell= ((freecons *)new_cell)->next_free;

	new_cell->car_field = item ;
	new_cell->cdr_code = CDR_NIL ;

	ListpDTD->dtd_cnt0++;

	list68k->cdr_code = CDR_ONPAGE | ((LADDR_from_68k(new_cell) &0xff)>>1) ;

	return(LADDR_from_68k(new_cell)) ; 


      }
    else
#endif /* ndef NEWCDRCODING */
      {
	N_OP_rplacd(list, item = cons(item , NIL_PTR));
	return(item);
      }
  }
