h09850s 00085/00013/00265d D 1.3 93/02/08 14:53:34 sybalsky 3 2c Big VM (and new CDR coding) changes for 3.0 \nes 00008/00005/00270d D 1.2 92/04/22 14:51:45 sybalsky 2 1c fix sccses 00275/00000/00000d D 1.1 92/04/21 15:28:42 sybalsky 1 0c date and time created 92/04/21 15:28:42 by sybalskyeuUf e 0tTI 1/* %Z% %M% Version %I% (%G%). copyright venue & Fuji Xerox  */static char *id = "%Z% %M%	%I% %G%	(venue & Fuji Xerox)";D 2/* %Z% %M% Version %I% (%G%). copyright venue & Fuji Xerox  */static char *id = "%Z% %M%	%I% %G%	(venue & Fuji Xerox)";E 2I 2E 2/************************************************************************//*									*/D 2/*	Copyright 1989, 1990 Venue, Fuji Xerox Co., Ltd, Xerox Corp.	*/E 2I 2/*	(C) Copyright 1989-92 Venue. All Rights Reserved.		*//*	Manufactured in the United States of America.			*/E 2/*									*/D 2/*	This file is work-product resulting from the Xerox/Venue	*//*	Agreement dated 18-August-1989 for support of Medley.		*/E 2I 2/*	The contents of this file are proprietary information 		*//*	belonging to Venue, and are provided to you under license.	*//*	They may not be further distributed or disclosed to third	*//*	parties without the specific permission of Venue.		*/E 2/*									*//************************************************************************//*************************************************************************//*                                                                       *//*                       File Name : gcrcell.c                    	 *//*                                                                       *//*************************************************************************//*                                                                       *//*                      Creation Date : July-7-1987                      *//*                      Written by Tomoru Teruuchi                       *//*                                                                       *//*************************************************************************//*                                                                       *//*           Functions :                                                 *//*                       gcreccell(cell);				 *//*                       freelistcell(cell);                             *//*                                                                       *//*                                                                       *//*************************************************************************//*           Descreption :                                               *//*                                                                       *//*  The functions "gcreccell" and "freelistcell" are the translated 	 *//*  functions from the Lisp functions "\GCRECLAIMCELL" that is the UFN   *//*  function of the opcode "RECLAIMCELL", and "\FREELISTCELL".           *//*  These functions may have the following characteristics :             *//*                                                                       *//*  	gcreccell(cell)	LispPTR cell					 *//* 		This function may always return NIL(= 0), as the Lisp    *//*           	macro .RECLAIMCELLLP. in more upper level may use this   *//*              return value as the further Garbage's pointer.(The Opcode*//*              "RECLAIMCELL"'s function is specified as this, but its   *//*              UFN function is not. The gcreccell function's		 *//*              behavior is same as the UFN function for speed and 	 *//*		simplicity,this is, this function is closed in this level*//*		)							 *//*		This function may reclaim the data of all types that is  *//*		Garbage.Especially, the data whose types are ARRAYBLOCK  *//*		(= 0), STACKP(= 8),VMEMPAGEP(= 10) and CODEBLOCK(= 54,55,*//*		56,57,58,59,60,61,62,63) may be reclaimed by each special*//*		processes that are specified and invoked by this function*//*		.The data whose type is LISTP is the main data type	 *//*		processed in this function actually and only then the 	 *//*		function "freelistcell" may be called for making linkage *//*		of free list.						 *//*									 *//*	freelistcell(cell)	LispPTR cell				 *//*		This function may make the linkage of free list of the	 *//*		cons cell.The header of this linkage is DTD->NEXTPAGE of *//*		LISTP and each cons page has its internal linkage of free*//*		cells.This return value is not considered as not used.	 *//*									 *//*************************************************************************//*                                                               \Tomtom *//*************************************************************************/#include <stdio.h>#include "lispemul.h"#include "lsptypes.h"#include "address.h"#include "adr68k.h"#include "lspglob.h"#include "stack.h"#include "cell.h"#include "ifpage.h"#include "gc.h"#include "dbprint.h"I 3#ifdef NEWCDRCODING#define CONSPAGE_LAST	0x0ffffffff#elseE 3#define CONSPAGE_LAST	0x0ffffI 3#endif /* NEWCDRCODING */E 3I 3#define ADD_TO_DO(ptr,offset)					\  if (do_count < 50)					\	{ 									\	  if (ptr & 0xF0000000) error("illegal ptr in addtodo"); \	  to_do[do_count] = (ptr);			\	  to_do_offset[do_count] = offset;		\	  todo_uses++;						\	  REC_GCLOOKUP((ptr), ADDREF);		\	  do_count++;						\    } else todo_misses++;unsigned todo_uses = 0;unsigned todo_misses = 0;unsigned todo_reads = 0;E 3/************************************************************************//*									*//*				g c r e c c e l l			*//*									*//*	Reclaim a cell, doing necessary finalization &c.		*//*									*//************************************************************************/gcreccell(cell)  LispPTR	cell;  {    register ConsCell *ptr;    struct dtd *typdtd;     DLword typ;     register LispPTR tmpptr, donext, tmpcell, val;    LispPTR ptrfield, carfield;     int index, code;    LispPTR *field;    int freecnt;    LispPTR freeptr;D 3    LispPTR *actptr;E 3I 3#ifdef NEWCDRCODING	LispPTR to_do[50];	/* table of pointers to follow, since Cdr coding lost */	short to_do_offset[50];	/* offset in datatype */	unsigned do_count = 0;	/* counter of entries in to_do table */#endif /* NEWCDRCODING */E 3    val = NIL;    tmpptr = cell;    index = -1;    donext = NIL;  lp:    ptr = (ConsCell *)Addr68k_from_LADDR(tmpptr);/* # ifdef CHECK  if (refcnt(tmpptr) != 1) error("reclaiming cell w/refcnt not 1"); # endif*/#ifdef DEBUG    if (tmpptr & 1) error("Reclaiming cell pointer with low bit 1.");#endif    typ = GetTypeNumber(tmpptr);#ifdef DEBUG    if (typ==6) printf("Reclaiming array ptr 0x%x.\n", tmpptr);#endif    switch(typ)       { 	 case TYPE_LISTP: 		{ 		  if ((code = ptr->cdr_code) == CDR_INDIRECT) /* indirect */		    { tmpcell = ptr->car_field;  /* Monitor */		      freelistcell(tmpptr);		      ptr = (ConsCell *) Addr68k_from_LADDR(tmpcell);		      tmpptr = tmpcell;		      code = ptr->cdr_code;		    };		  if (index != -1)	/* car part */		    index = -1;D 3/*		  else if ((val = htfind(car(tmpptr), DELREF)) != NIL) */E 3		  else		    {		      REC_GCLOOKUPV(car(tmpptr), DELREF, val);I 3#ifndef NEWCDRCODINGE 3		      if (val != NIL)			{ 			  ptr->car_field = donext;			  ptr->cdr_code = code;			  donext = tmpptr; 			  goto doval;			};I 3#else	     if (val != NIL)		   {			 ADD_TO_DO(val,-1);			 val = NIL;	       }#endif /* NEWCDRCODING */E 3		    }D 3/*		  val = htfind(cdr(tmpptr),DELREF); */E 3		  REC_GCLOOKUPV(cdr(tmpptr), DELREF, val);		  if (code <= CDR_MAXINDIRECT)		    {I 3#ifdef NEWCDRCODING		      tmpcell = tmpptr + ((code - CDR_INDIRECT) << 1);#elseE 3		      tmpcell = POINTER_PAGEBASE(tmpptr)				    + ((code - CDR_INDIRECT) << 1);I 3#endif /* NEWCDRCODING */E 3		      freelistcell(tmpcell);		    };		  freelistcell(tmpptr);		  goto doval;    		};	case TYPE_ARRAYBLOCK:		if ((index == -1) && reclaimarrayblock(tmpptr)) 		  goto trynext;		else break;		case TYPE_STACKP:		if ((index == -1) && reclaimstackp(tmpptr)) goto trynext; 		break;		case TYPE_VMEMPAGEP:		if ((index == -1) && releasingvmempage(tmpptr))		  {		    goto trynext;		  }		else break;	case TYPE_CODEHUNK1:	case TYPE_CODEHUNK2:	case TYPE_CODEHUNK3:	case TYPE_CODEHUNK4:	case TYPE_CODEHUNK5:	case TYPE_CODEHUNK6:	case TYPE_CODEHUNK7:	case TYPE_CODEHUNK8:	case TYPE_CODEHUNK9:	case TYPE_CODEHUNK10:		if ((index == -1) && reclaimcodeblock(tmpptr)) goto trynext;		else break; 	default:  ;      };   normal:     typdtd = (struct dtd *)GetDTD(typ);     ptrfield = typdtd->dtd_ptrs;     if (index != -1)      {	index = (index << 1);	ptrfield = cdr(ptrfield);	while ((car(ptrfield) & 0x0ffff) != index) ptrfield = cdr(ptrfield);	index = -1;      };	    while(ptrfield != NIL)      {	carfield = car(ptrfield);	ptrfield = cdr(ptrfield);	carfield &= 0x0ffff;D 3/*	val = GCLOOKUPV(0x8000,DELREF,(0x0ffffff & *(LispPTR *)		Addr68k_from_LADDR(tmpptr+carfield)));*/	REC_GCLOOKUPV((0x0ffffff &E 3I 3	REC_GCLOOKUPV((POINTERMASK &E 3		        *(LispPTR *)Addr68k_from_LADDR(tmpptr+carfield)),		       DELREF, val);D 3E 3I 3#ifndef NEWCDRCODINGE 3	if (val != NIL)	  {	    if (ptrfield != NIL)	      {		ptr = (ConsCell *)Addr68k_from_LADDR(tmpptr);		ptr->car_field = donext;		ptr->cdr_code = ((car(ptrfield) & 0x0ffff) >> 1);		donext = tmpptr;		goto doval;	      }	    else goto addtofreelist;	  };I 3#else	if (val != NIL)	  {	    if (ptrfield != NIL)	      {		  if (do_count<50)			{ ADD_TO_DO(tmpptr, (car(ptrfield) & 0xffff)>>1); goto doval;}		  else todo_misses++;	      }	    else goto addtofreelist;	  };#endif /* NEWCDRCODING */E 3      };  addtofreelist:    field = (LispPTR *)Addr68k_from_LADDR(tmpptr);    *field = typdtd->dtd_free;    typdtd->dtd_free = tmpptr;  doval:    if (val != NIL)      {	tmpptr = val;	REC_GCLOOKUP(tmpptr, ADDREF);/*	GCLOOKUP(0x8000, ADDREF,tmpptr); */	val = NIL;	goto lp;      };  trynext:I 3#ifndef NEWCDRCODINGE 3    if (donext != NIL)      {	tmpptr = donext;	ptr = (ConsCell *)Addr68k_from_LADDR(tmpptr);	donext = (LispPTR)ptr->car_field;	index = ptr->cdr_code;	goto lp;      };I 3#else    if (do_count)	/* If there are other cells to collect */	  {		do_count--;		tmpptr = to_do[do_count];		index  = to_do_offset[do_count];		todo_reads++;	goto lp;      }#endif /*NEWCDRCODING */E 3    return(NIL);  }/************************************************************************//*									*//*			f r e e l i s t c e l l				*//*									*//*									*//*									*//************************************************************************/freelistcell(cell)LispPTR	cell;  {    struct conspage *pbase;     register ConsCell *cell68k;I 3	unsigned int offset, prior, celloffset;E 3    cell68k = (ConsCell *)Addr68k_from_LADDR(cell);    pbase = (struct conspage *)Addr68k_from_LPAGE(POINTER_PAGE(cell));D 3    cell68k->cdr_code = pbase->next_cell;    pbase->next_cell = (cell & 0x0ff);    if ((++pbase->count > 2) && (pbase->next_page == CONSPAGE_LAST)) E 3I 3	celloffset = (LispPTR)cell & 0xFF;	if (celloffset < 4) error("freeing CONS cell that's really freelist ptr");    prior = 0;	for (offset = pbase->next_cell; offset;         offset = FREECONS(pbase,offset) -> next_free)E 3      {I 3	if (offset < celloffset)	  {		break;	  }	  prior = offset;	  }	if (prior) FREECONS(pbase, prior)->next_free = celloffset;	else pbase->next_cell = celloffset;	((freecons *)cell68k) -> next_free = offset;    if ((++pbase->count > 32) && (pbase->next_page == CONSPAGE_LAST))       {E 3	pbase->next_page = ListpDTD->dtd_nextpage;  	ListpDTD->dtd_nextpage = POINTER_PAGE(cell);       };D 3		 	   E 3I 3E 3  }E 1