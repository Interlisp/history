h58722s 00266/00028/00219d D 2.16 93/02/08 15:03:45 sybalsky 20 19c Big VM (and new CDR coding) changes for 3.0 \nes 00000/00000/00247d D 2.15 92/04/21 16:24:30 sybalsky 19 18c shortening file names for DOSes 00012/00005/00235d D 2.14 92/02/06 12:52:42 sybalsky 18 17c Add byte-swapped bit to DefCell, to allow  fn opcodes on byte-swap machines to be native-order.es 00052/00000/00188d D 2.13 91/02/07 19:15:05 sybalsky 17 16c Make GETDEFCELL &c work with new-symbols, add new- and old-atom specific versions of them for speed.es 00014/00001/00174d D 2.12 90/06/04 10:33:16 sybalsky 16 15c reformat, copyrightes 00007/00020/00168d D 2.11 89/04/07 20:19:35 shih 15 14c bad sccsides 00019/00000/00169d D 2.10 89/03/27 13:18:12 sybalsky 14 13c Added xpointer struct defn here, with byte-swapped version.  Taken from gvar2.ces 00000/00000/00169d D 2.9 89/03/27 10:15:27 sybalsky 13 12c more work-order changeses 00051/00000/00118d D 2.8 89/03/16 12:04:43 sybalsky 12 11c Added byte-swapped structure definitionses 00041/00023/00077d D 2.7 89/03/02 11:51:12 sybalsky 11 10c Added GetPropCell macro to get proplist cell from atom index.es 00003/00018/00097d D 2.6 88/10/12 14:47:38 krivacic 10 9c new out-of-line interfacees 00008/00000/00107d D 2.5 88/07/29 17:38:33 shimizu 9 8c Add S_N_CHECKANDCADRes 00004/00003/00103d D 2.4 88/06/21 13:51:39 krivacic 8 7c fix N_CHECKANDCADR to evaluate arg only oncees 00009/00000/00097d D 2.3 88/06/03 10:12:56 masinter 7 6c Put back in CheckAndCadr (old version used by C_ONLY code)es 00001/00028/00096d D 2.2 88/05/31 20:22:53 masinter 6 5c remove obsolete CheckAndCadr macro (wrong UFN), IncAllocCntes 00000/00000/00124d D 2.1 88/05/17 09:17:09 hayata 5 4c Version up to 2.1es 00005/00003/00119d D 1.4 88/04/21 18:19:01 masinter 4 3c merge new GC codees 00009/00000/00113d D 1.3 88/03/29 18:46:59 krivacic 3 2c N_CHECKANDCADRes 00001/00001/00112d D 1.2 88/03/13 13:17:07 hayata 2 1c Add SCCS key id (%Z%)es 00113/00000/00000d D 1.1 88/02/23 18:36:06 hayata 1 0c date and time created 88/02/23 18:36:06 by hayataeuUtTI 1D 2/* This is G-file %M% Version %I% (%G%). copyright Xerox & Fuji Xerox  */E 2I 2D 10/* This is G-file %Z% %M% Version %I% (%G%). copyright Xerox & Fuji Xerox  */E 10I 10D 15/* This is G-file @(#) cell.h Version 2.5 (7/29/88). copyright Xerox & Fuji Xerox  */E 15I 15D 16/* %Z% %M% Version %I% (%G%). copyright envos & Fuji Xerox  */E 16I 16D 20/* %Z% %M% Version %I% (%G%). copyright Venue & Fuji Xerox  */E 20I 20/* %Z% %M% Version %I% (%G%). copyright Venue   */E 20E 16E 15E 10E 2D 20/*D 15 *	Copyright (C) 1987 by Fuji Xerox Co., Ltd. All rights reserved. *E 15D 6 *	Auther	:	Takeshi ShimizuE 6I 6 *	Author	:	Takeshi ShimizuE 6D 15 *			Hiroshi Hayata	E 15I 15 *			Hiroshi HayataE 15 */E 20I 16D 20I 18E 20E 18/************************************************************************//*									*/D 18/*	Copyright 1989, 1990 Venue, Fuji Xerox Co., Ltd, Xerox Corp.	*/E 18I 18/*	(C) Copyright 1989-92 Venue. All Rights Reserved.		*//*	Manufactured in the United States of America.			*/E 18/*									*/D 18/*	This file is work-product resulting from the Xerox/Venue	*//*	Agreement dated 18-August-1989 for support of Medley.		*/E 18I 18/*	The contents of this file are proprietary information 		*//*	belonging to Venue, and are provided to you under license.	*//*	They may not be further distributed or disclosed to third	*//*	parties without the specific permission of Venue.		*/E 18/*									*//************************************************************************/E 16/**********************************************************************//*D 15 		File Name :	cell.hE 15I 15		File Name :	cell.hE 15		Cell Manipulate MacrosD 15  				Date :		December 16, 1986 				Edited by :	Takeshi Shimizu				Changed :  24-Mar-87 take					17-APR-87 take					24-APR-87 take					08-MAY-87 take					19-may-87 take					 4-jun-87 take					15-jun-87 take(GetCons)					22-Sep-87 take(inc-alloccnt)					06-Oct-87 take(inc-alloccnt FIX)					09-Nov-87 Hayata(CheckAndCadr)D 4 E 4I 4					15-Apr-88 Tomtom(IncAllocCnt)E 15I 15				Date :		December 16, 1986				Edited by :	Takeshi ShimizuE 15E 4*//**********************************************************************//*  CONS CELL (LISTP) definitions moved to lispemulater.h */D 15  /* This Macro may produce the CDR code */ E 15I 15D 20  /* This Macro may produce the CDR code */E 15#define  CDRCODE(x)     LRSH (((int)x & 0x0ff000000) , 24)E 20  /* This Macro may produce a pointer that points CAR cell */D 20  /* On 68010,68000 This Macro does not effect *E 20I 20  /* On 68010,68000 This Macro does not effect */#ifdef NEWCDRCODING#define  CARFIELD(x)    ((int)x & 0x0fffffff)/* CDR-Codes defs */#define CDR_ONPAGE		8#define CDR_NIL			8#define CDR_INDIRECT		0#define CDR_MAXINDIRECT	7#elseE 20#define  CARFIELD(x)    ((int)x & 0x00ffffff)/* CDR-Codes defs */#define CDR_ONPAGE		128#define CDR_NIL			128#define CDR_INDIRECT		0#define CDR_MAXINDIRECT	127D 6/******* Folowing defs are moved to lispemul.h  *******//* #define NIL_PTR			0  (int)Atomspace*//* #define NOBIND_PTR		1 (int)(Atomspace +1)*//***********************************************/E 6D 20short  CarCdrError ;E 20I 20#endif /* NEWCDRCODING */E 20I 12D 20#ifndef BYTESWAPE 20I 20/************************************************************************//*									*//*	CONSPAGE describes the free-space management fields at the	*//*	beginning of a cons page -- # of free cells on the page, etc.	*//*									*//************************************************************************/E 20I 20#ifndef BYTESWAP#ifdef NEWCDRCODINGE 20E 12D 6struct listp     {  /* This definition uses only when CdrCoding==0 */			DLword  *car;			DLword  *cdr;    };E 6D 11struct conspage  {              unsigned    count : 8   ;              unsigned    next_cell :8 ;              DLword  next_page ;      };E 11I 11struct  conspage    {I 20      unsigned count: 8;	/* free cells on this page */      unsigned next_cell: 8;	/* next free cell in chain */      unsigned nil:16;      LispPTR  next_page;	/* next cons page, or 0 if none */    };#elsestruct  conspage    {E 20      unsigned    count : 8   ;      unsigned    next_cell :8 ;      DLword  next_page ;    };E 11D 20E 20I 20#endif /* NEWCDRCODING */E 20I 12#else/* byte-swapped version */I 20#ifdef NEWCDRCODINGE 20struct  conspage    {I 20      unsigned nil: 16;      unsigned next_cell: 8;      unsigned count: 8;      LispPTR  next_page;    };#elsestruct  conspage    {E 20      DLword  next_page ;      unsigned    next_cell :8 ;      unsigned    count : 8   ;    };I 20#endif /* NEWCDRCODING */#endif /* BYTESWAP */E 20D 20#endif BYTESWAPE 20E 12/* Following MACROs for Conspage */I 20E 20/* lisp_ptr is LISP pointer, returns 68k ptr points struct conspage obj */D 20#define Get_ConsPageBase(lisp_ptr)	(struct conspage *)Addr68k_from_LPAGE(POINTER_PAGEBASE(lisp_ptr))#define GetNewCell_68k(conspage68k)	 (ConsCell *)(((DLword *)(conspage68k)) + (unsigned)((conspage68k)->next_cell) )E 20I 20#define Get_ConsPageBase(lisp_ptr)				\  (struct conspage *)Addr68k_from_LPAGE(POINTER_PAGEBASE(lisp_ptr))E 20I 20#define GetNewCell_68k(conspage68k)				\    (ConsCell *)(((DLword *)(conspage68k))			\  + (unsigned)((conspage68k)->next_cell) )E 20/* page : LISP page */D 20#define GetCONSCount(page)	(((struct conspage *)Addr68k_from_LPAGE(page))->count)E 20I 20#define GetCONSCount(page)					\  (((struct conspage *)Addr68k_from_LPAGE(page))->count)E 20I 20E 20I 12#ifndef BYTESWAPI 20  /* For chaining together free cons cells on a page */typedef struct freec  {    unsigned next_free: 8;	/* next free cell on this page */    unsigned nil: 24;  } freecons;#elsetypedef struct freec  {    unsigned next_free: 8;    unsigned nil: 24;  } freecons;#endif /* BYTESWAP */#define FREECONS(page,offset) ((freecons *) ((DLword *)page + offset))/************************************************************************//*									*//*				S Y M B O L   D E F S			*//*									*//*									*//*									*//************************************************************************/#ifndef BYTESWAPE 20	/************************************************/	/*  Definitions for normal byte-order machines	*/	/************************************************/I 20#ifdef BIGVM/* Definition of a new-atom, where all the cells are in one object */typedef  struct new_atom      {	unsigned dfccodep: 1 ;	/* DEFCELL FLAGS */	unsigned dffastp: 1 ;	unsigned dfargtype: 2 ;	unsigned pncell: 28;	/* pointer to the pname itself */	unsigned nil2: 4;	/* top 4 bits of value cell */	unsigned valcell: 28;	/* pointer to the top-level value */	unsigned nil3: 4;	/* top 4 bits of definition cell */	unsigned defcell: 28;	/* pointer to function definition */	unsigned nil4: 4;	/* */	unsigned plcell: 28;	/* pointer to property list */	unsigned pnpkg: 8;	/* package */	unsigned dfnil1: 4 ;	/* DEFCELL FLAGS */	unsigned dfpseudo: 1 ;	unsigned dfswapped: 1 ;	/* T for native-order fn opcodes */	unsigned dfnil:	2 ;	unsigned plunused: 1;	/* PROPLIST FLAGS */	unsigned plgensymp: 1;	unsigned plfatpnamep: 1;	unsigned plnil: 5;	unsigned nil5: 8;	/* Fill out last byte of final cell */      } NewAtom;E 20E 12D 6/* When cell is created,val of \RECLAIM.COUNTDOWN will be decremented *//* but,now I have implemented this except \DOGC sequence  22-sep-87*/D 4#define IncAllocCnt(n)	{if(((*Reclaim_cnt_word) & 0xFFFF) > n) \E 4I 4#define IncAllocCnt(n)	{if (*Reclaim_cnt_word != NIL)		\			{if(((*Reclaim_cnt_word) & 0xFFFF) > n) \E 4			  /* decrement by address incrementing */ \			  *Reclaim_cnt_word -= n; \			 else \D 4			  *Reclaim_cnt_word += 1000 ; /* Instead of DOGC */}E 4I 4			  *Reclaim_cnt_word += 0 ; /* Instead of DOGC */}}E 4E 6/* DEFs for DEFINITIONCELL */D 11typedef struct definition_cell {	unsigned	ccodep	:	1 ;	unsigned	fastp	:	1 ;	unsigned	argtype	:	2 ;	unsigned	pseudocodep :	1 ;	unsigned	nil	:	3 ;	unsigned	defpointer :	24;E 11I 11typedef  struct definition_cell    {      unsigned	ccodep	:	1 ;      unsigned	fastp	:	1 ;      unsigned	argtype	:	2 ;I 20      unsigned	defpointer :	28;	LispPTR nil_PL;	/* skip the proplist cell */	unsigned nilpkg:8;	/* skip pkg byte */      unsigned	nil2	:	4 ;E 20      unsigned	pseudocodep :	1 ;D 18      unsigned	nil	:	3 ;E 18I 18      unsigned	byteswapped :	1 ;	/* T for native-order fn opcodes */I 20	unsigned nil_last: 18;    } DefCell ;typedef  struct pname_cell    {      unsigned	nil	:	4 ;      unsigned	pnamebase : 28 ;	LispPTR nil_val;	LispPTR nil_def;	LispPTR nil_plist;      unsigned	pkg_index : 8 ;	unsigned nil2: 24;    } PNCell ;typedef  struct proplist_cell    {      unsigned nil: 4;      unsigned propbase: 28;	unsigned nilpkg: 8;	unsigned nildef: 8;      unsigned unused: 1;      unsigned gensymp: 1;      unsigned fatpnamep: 1;      unsigned nil2: 5;	unsigned nil3:	8;    } PLCell;struct xpointer{	unsigned	flags:4;	unsigned	addr:28;};#elif oldBIGVM/* Definition of a new-atom, where all the cells are in one object */typedef  struct new_atom      {	unsigned dfccodep: 1 ;	/* DEFCELL FLAGS */	unsigned dffastp: 1 ;	unsigned dfargtype: 2 ;	unsigned nil1:4;	unsigned pncell: 24;	/* pointer to the pname itself */	unsigned nil2: 8;	/* top 4 bits of value cell */	unsigned valcell: 24;	/* pointer to the top-level value */	unsigned nil3: 8;	/* top 4 bits of definition cell */	unsigned defcell: 24;	/* pointer to function definition */	unsigned nil4: 8;	/* */	unsigned plcell: 24;	/* pointer to property list */	unsigned pnpkg: 8;	/* package */	unsigned dfnil1: 4 ;	/* DEFCELL FLAGS */	unsigned dfpseudo: 1 ;	unsigned dfswapped: 1 ;	/* T for native-order fn opcodes */	unsigned dfnil:	2 ;	unsigned plunused: 1;	/* PROPLIST FLAGS */	unsigned plgensymp: 1;	unsigned plfatpnamep: 1;	unsigned plnil: 5;	unsigned nil5: 8;	/* Fill out last byte of final cell */      } NewAtom;/* DEFs for DEFINITIONCELL */typedef  struct definition_cell    {      unsigned	ccodep	:	1 ;      unsigned	fastp	:	1 ;      unsigned	argtype	:	2 ;	  unsigned nil1:4;      unsigned	defpointer :	24;	LispPTR nil_PL;	/* skip the proplist cell */	unsigned nilpkg:8;	/* skip pkg byte */      unsigned	nil2	:	4 ;      unsigned	pseudocodep :	1 ;      unsigned	byteswapped :	1 ;	/* T for native-order fn opcodes */	unsigned nil_last: 18;    } DefCell ;typedef  struct pname_cell    {      unsigned	nil	:	8 ;      unsigned	pnamebase : 24 ;	LispPTR nil_val;	LispPTR nil_def;	LispPTR nil_plist;      unsigned	pkg_index : 8 ;	unsigned nil2: 24;    } PNCell ;typedef  struct proplist_cell    {      unsigned nil: 8;      unsigned propbase: 24;	unsigned nilpkg: 8;	unsigned nildef: 8;      unsigned unused: 1;      unsigned gensymp: 1;      unsigned fatpnamep: 1;      unsigned nil2: 5;	unsigned nil3:	8;    } PLCell;struct xpointer{	unsigned	flags:8;	unsigned	addr:24;};#else	/* not BIGVM *//* DEFs for DEFINITIONCELL */typedef  struct definition_cell    {      unsigned	ccodep	:	1 ;      unsigned	fastp	:	1 ;      unsigned	argtype	:	2 ;      unsigned	pseudocodep :	1 ;      unsigned	byteswapped :	1 ;	/* T for native-order fn opcodes */E 20      unsigned	nil	:	2 ;E 18      unsigned	defpointer :	24;E 11D 11} DefCell ;typedef struct pname_cell {	unsigned	pkg_index : 8 ;	unsigned	pnamebase : 24 ;} PNCell ;E 11I 11    } DefCell ;E 11D 11struct cadr_cell{		LispPTR car_cell;				/* Lisp address (word addressing) */		LispPTR cdr_cell;			/* Lisp address (word addressing) */};E 11I 11typedef  struct pname_cell    {      unsigned	pkg_index : 8 ;      unsigned	pnamebase : 24 ;    } PNCell ;E 11I 11typedef  struct proplist_cell    {      unsigned unused: 1;      unsigned gensymp: 1;      unsigned fatpnamep: 1;      unsigned nil: 5;      unsigned propbase: 24;    } PLCell;I 14struct xpointer{	unsigned	flags:8;	unsigned	addr:24;};I 20#endif /* BIGVM */E 20E 14I 12#else	/************************************************/	/*  Definitions for byte-swapped machines	*/	/************************************************//* DEFs for DEFINITIONCELL */typedef  struct definition_cell    {      unsigned	defpointer :	24;D 18      unsigned	nil	:	3 ;E 18I 18      unsigned	nil	:	2 ;      unsigned	byteswapped : 	1 ;	/* T if opcodes are native-order */E 18      unsigned	pseudocodep :	1 ;      unsigned	argtype	:	2 ;      unsigned	fastp	:	1 ;      unsigned	ccodep	:	1 ;E 12E 11I 12    } DefCell ;typedef  struct pname_cell    {      unsigned	pnamebase : 24 ;      unsigned	pkg_index : 8 ;    } PNCell ;typedef  struct proplist_cell    {       unsigned propbase: 24;      unsigned nil: 5;      unsigned fatpnamep: 1;      unsigned gensymp: 1;     unsigned unused: 1;    } PLCell;I 14struct xpointer  {    unsigned	addr:24;    unsigned	flags:8;  };E 14D 20#endif BYTESWAPE 20I 20#endif /* BYTESWAP */E 20I 14I 20E 20E 14E 12I 11struct  cadr_cell    {      LispPTR car_cell;	/* Lisp address (word addressing) */      LispPTR cdr_cell;	/* Lisp address (word addressing) */    };I 17/************************************************************************//*									*//*	Access to the parts of a SYMBOL: Pname, Definition, Value, 	*//*	and property list.						*//*									*//*									*//*									*//*									*//************************************************************************/#ifndef BIGATOMSE 17E 11#define GetDEFCELL68k(index)	((LispPTR *)Defspace + (index) )#define GetVALCELL68k(index)	((LispPTR *)Valspace + (index))#define GetPnameCell(index)	((LispPTR *)Pnamespace + (index))I 11#define GetPropCell(index)	((LispPTR *)Plistspace + (index))I 17  /* Good only for old-style LITATOMS */#define GetDEFCELLlitatom(index)	((LispPTR *)Defspace + (index) )#define GetVALCELLlitatom(index)	((LispPTR *)Valspace + (index))#define GetPnameCelllitatom(index)	((LispPTR *)Pnamespace + (index))#define GetPropCelllitatom(index)	((LispPTR *)Plistspace + (index))#else  /* Good for old LITATOMS and new NEW-ATOMs */D 20#define GetDEFCELL68k(index)	(((index & 0xFF0000) != 0)	?	   \E 20I 20#define GetDEFCELL68k(index)	(((index & SEGMASK) != 0)	?	   \E 20				  (LispPTR *)(Addr68k_from_LADDR(index)+NEWATOM_DEFN_OFFSET) \D 20				: ((LispPTR *)Defspace + (index) ))E 20I 20				: GetDEFCELLlitatom(index) )E 20D 20#define GetVALCELL68k(index)	(((index & 0xFF0000) != 0)	?	    \E 20I 20#define GetVALCELL68k(index)	(((index & SEGMASK) != 0)	?	    \E 20				  (LispPTR *)(Addr68k_from_LADDR(index)+NEWATOM_VALUE_OFFSET) \D 20				:  ((LispPTR *)Valspace + (index)))E 20I 20				: GetVALCELLlitatom(index))E 20D 20#define GetPnameCell(index)	(((index & 0xFF0000) != 0)	?	   \E 20I 20#define GetPnameCell(index)	(((index & SEGMASK) != 0)	?	   \E 20				  (LispPTR *)(Addr68k_from_LADDR(index)+NEWATOM_PNAME_OFFSET) \D 20				:  ((LispPTR *)Pnamespace + (index)))E 20I 20				: GetPnameCelllitatom(index))E 20D 20#define GetPropCell(index)	(((index & 0xFF0000) != 0)	?	   \E 20I 20#define GetPropCell(index)	(((index & SEGMASK) != 0)	?	   \E 20				  (LispPTR *)(Addr68k_from_LADDR(index)+NEWATOM_PLIST_OFFSET) \D 20				:  ((LispPTR *)Plistspace + (index)))E 20I 20				: GetPropCelllitatom(index))E 20  /* Good only for old-style LITATOMS */I 20#ifdef BIGVM#define GetDEFCELLlitatom(index)\	((LispPTR *)Pnamespace + (5*(index))+NEWATOM_DEFN_PTROFF)#define GetVALCELLlitatom(index)	\	((LispPTR *)Pnamespace + (5*(index))+NEWATOM_VALUE_PTROFF)#define GetPnameCelllitatom(index)	\	((LispPTR *)Pnamespace + (5*(index))+NEWATOM_PNAME_PTROFF)#define GetPropCelllitatom(index)	\	((LispPTR *)Pnamespace + (5*(index))+NEWATOM_PLIST_PTROFF)#else /* BIGVM not set, so use old name-space format */E 20#define GetDEFCELLlitatom(index)	((LispPTR *)Defspace + (index) )#define GetVALCELLlitatom(index)	((LispPTR *)Valspace + (index))#define GetPnameCelllitatom(index)	((LispPTR *)Pnamespace + (index))#define GetPropCelllitatom(index)	((LispPTR *)Plistspace + (index))I 20#endifE 20  /* Good only for new-style NEW-ATOMs */#define GetDEFCELLnew(index) (LispPTR *)(Addr68k_from_LADDR(index)+NEWATOM_DEFN_OFFSET)#define GetVALCELLnew(index) (LispPTR *)(Addr68k_from_LADDR(index)+NEWATOM_VALUE_OFFSET)#define GetPnameCellnew(index) (LispPTR *)(Addr68k_from_LADDR(index)+NEWATOM_PNAME_OFFSET)#define GetPropCellnew(index) (LispPTR *)(Addr68k_from_LADDR(index)+NEWATOM_PLIST_OFFSET)D 20#endif BIGATOMSE 20I 20#endif /* BIGATOMS */E 20E 17E 11D 6/* When cadr() function is called, type check should be done. */#define	CheckAndCadr(sour, dest, ufn_num)	\		{if(GetTypeNumber(sour) != TYPE_LISTP){	\			ufn(ufn_num);	\			return;	\		}else	\			dest = cadr(sour);	\		}E 6I 3I 7/* When cadr() function is called, type check should be done. */D 10#define	CheckAndCadr(sour, dest, ufn_num)	\		{if(GetTypeNumber(sour) != TYPE_LISTP){	\			ufn(ufn_num);	\			return;	\		}else	\			dest = cadr(sour);	\		}E 10E 7D 10#define	N_CHECKANDCADR(sour, dest, ufn_addr)			\E 10I 10#define	S_N_CHECKANDCADR(sour, dest, tos)			\E 10D 8		{if(GetTypeNumber(sour) != TYPE_LISTP){		\E 8I 8		{register LispPTR parm = sour;			\		 if(GetTypeNumber(parm) != TYPE_LISTP){		\E 8D 10			ERROR_EXIT(ufn_addr);			\D 8		}else	\			dest = cadr(sour);			\E 8I 8		}else						\			dest = cadr(parm);			\E 8		}I 9#define	S_N_CHECKANDCADR(sour, dest, ufn_addr, tos)			\		{register LispPTR parm = sour;			\		 if(GetTypeNumber(parm) != TYPE_LISTP){		\			SAVE_ERROR_EXIT(tos,ufn_addr);			\E 10I 10			ERROR_EXIT(tos);			\E 10		}else						\			dest = cadr(parm);			\		}E 9E 3E 1