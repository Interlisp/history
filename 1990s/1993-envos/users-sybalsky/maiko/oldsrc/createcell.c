/* @(#) createcell.c Version 2.9 (6/15/90). copyright venue & Fuji Xerox  */
static char *id = "@(#) createcell.c	2.9 6/15/90		(venue & Fuji Xerox)";

/************************************************************************/
/*									*/
/*	Copyright 1989, 1990 Venue, Fuji Xerox Co., Ltd, Xerox Corp.	*/
/*									*/
/*	This file is work-product resulting from the Xerox/Venue	*/
/*	Agreement dated 18-August-1989 for support of Medley.		*/
/*									*/
/************************************************************************/

/***********************************************************************/
/*
 		File Name :	createcell.c

		Desc	:	
 
 				Date :		Jun. 4, 1987
 				Edited by :	Takeshi Shimizu
				Changed :	9 Jun 1987 take
						26 Oct. 1987 take(add mask)
 
		Including :	OP_createcell
				
				
*/
/**********************************************************************/

#include "lispemul.h"
#include "lispmap.h"
#include "emulglobal.h"
#include "lispglobal.h"
#include "lisptypes.h"
#include "address.h"
#include "address68k.h"
#include "cell.h" 
#include "gc.h" 
 
LispPTR *alloc_mdspage();
LispPTR initmdspage();

LispPTR N_OP_createcell(tos)
	register LispPTR tos;
{
  register struct dtd *dtd68k;
  register DLword *ptr,*lastptr;
  register LispPTR newcell ;
  register unsigned int type ;

  if((tos & 0xff0000) != S_POSITIVE) ERROR_EXIT(tos);
  type = tos & 0xffff ;

#ifdef DEBUG
  if(type==TYPE_LISTP)
	error("N_OP_createcell : Can't create Listp cell with CREATECELL");
	check_dtd_chain(type);
#endif

  
  dtd68k = (struct dtd *)GetDTD(type);

  if(dtd68k->dtd_size == 0) ERROR_EXIT(tos);
  /* error("OP_createcell : Attempt to create a cell not declared yet"); */

retry :
  if((tos=newcell=((dtd68k->dtd_free)&0xffffff)) != NIL)
  {
	ptr = (DLword *)Addr68k_from_LADDR(newcell);

	/* replace dtd_free with newcell's top DLword (it may keep next chain)*/
	dtd68k->dtd_free = (*((LispPTR *)ptr)) & 0xffffff;

	dtd68k->dtd_oldcnt++;

	/* clear 0  */
	for(lastptr=ptr + dtd68k->dtd_size ;
		ptr != lastptr ; ptr++)
	  {  GETWORD(ptr) = 0 ; }

/*	 IncAllocCnt(1); */
	 GCLOOKUP(tos, DELREF);
	 return(tos);
  }
  else
  {
	dtd68k->dtd_free = initmdspage(alloc_mdspage(dtd68k->dtd_typeentry) , 
				dtd68k->dtd_size ,NIL);
	goto retry ;
  }

} /* N_OP_createcell end */





DLword *createcell68k(type)
 unsigned int type;
{
  register struct dtd *dtd68k;
  register DLword *ptr,*lastptr;
  register ConsCell *newcell68k;
  register LispPTR newcell ;
#ifdef DEBUG
  if(type==TYPE_LISTP)
	error("createcell : Can't create Listp cell with CREATECELL");
  if(type==TYPE_STREAM) stab();

	check_dtd_chain(type);

#endif
  
  dtd68k = (struct dtd *)GetDTD(type);

  if(dtd68k->dtd_size == 0)
	error("createcell : Attempt to create a cell not declared yet");

retry :
  if((newcell=(dtd68k->dtd_free & 0xffffff)) != NIL)
  {
#ifdef DEBUG
	if(type != GetTypeNumber(newcell)) 
	  error("createcell : BAD cell in dtdfree");
	if(newcell > 0xFFFFFF)
		error("createcell : BAD Lisp address");
#endif

	ptr = Addr68k_from_LADDR(newcell) ;


	/* replace dtd_free with newcell's top DLword (it may keep next chain)*/
	dtd68k->dtd_free = (*((LispPTR *)ptr)) & 0xFFFFFF ;

#ifdef DEBUG
	if((dtd68k->dtd_free!=0)&&(type != GetTypeNumber(dtd68k->dtd_free)) )
	  error("createcell : BAD cell in next dtdfree");
	check_dtd_chain(type);

#endif

	dtd68k->dtd_oldcnt++;

	/* clear 0  */
	for(lastptr=ptr + dtd68k->dtd_size ;
		ptr != lastptr ; ptr++)
	  {  GETWORD(ptr) = 0 ; }

/*	IncAllocCnt(1); */
	GCLOOKUP(newcell, DELREF);

#ifdef DEBUG
	check_dtd_chain(type);
#endif


	return(Addr68k_from_LADDR(newcell));
	
  }
  else
  {
	dtd68k->dtd_free = initmdspage(alloc_mdspage(dtd68k->dtd_typeentry) , 
				dtd68k->dtd_size ,NIL);

#ifdef DEBUG
	check_dtd_chain(type);
#endif

	goto retry ;
  }


} /* createcell68k end */


/**********************************************************/
/*  Create a Cell of Specified Type & Set to given Value  */
/*  Works with 32 bit typed values only.                  */
/*  (Initially used only by native code)                  */
/**********************************************************/

LispPTR Create_n_Set_Cell(type, value)
 unsigned int type;
 LispPTR value;
{
  register struct dtd *dtd68k;
  register DLword *ptr,*lastptr;
  register ConsCell *newcell68k;
  register LispPTR newcell ;
  
  dtd68k = (struct dtd *)GetDTD(type);

  if(dtd68k->dtd_size == 0)
	error("createcell : Attempt to create a cell not declared yet");

retry :
  if((newcell=(dtd68k->dtd_free & 0xffffff)) != NIL)
  {
	ptr = Addr68k_from_LADDR(newcell) ;

	/* replace dtd_free with newcell's top DLword (it may keep next chain)*/

	dtd68k->dtd_free = (*((LispPTR *)ptr)) & 0xFFFFFF ;
	dtd68k->dtd_oldcnt++;

	/* clear 0  */
	for(lastptr=ptr + dtd68k->dtd_size ;
		ptr != lastptr ; ptr++)
	  {  GETWORD(ptr) = 0 ; }

/*	IncAllocCnt(1); */
	GCLOOKUP(newcell, DELREF);
	(* ((LispPTR *) Addr68k_from_LADDR(newcell))) = value;
	return(newcell);
	
  }
  else
  {
	dtd68k->dtd_free = initmdspage(alloc_mdspage(dtd68k->dtd_typeentry) , 
				dtd68k->dtd_size ,NIL);

	goto retry ;
  }


} /* createcell68k end */

