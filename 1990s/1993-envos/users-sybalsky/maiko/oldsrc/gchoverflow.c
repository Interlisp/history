/* @(#) gchoverflow.c Version 2.4 (6/15/90). copyright venue & Fuji Xerox  */
static char *id = "@(#) gchoverflow.c	2.4 6/15/90		(venue & Fuji Xerox)";

/*************************************************************************/
/*************************************************************************/
/*	Copyright (C) 1987 by Fuji Xerox Co., Ltd. All rights reserved.	 */
/*************************************************************************/
/*                                                                       */
/*                       File Name : gchoverflow.c                       */
/*                                                                       */
/*************************************************************************/
/*                                                                       */
/*                      Creation Date : July-8-1987                      */
/*                      Written by Tomoru Teruuchi                       */
/*                                                                       */
/*************************************************************************/
/*                                                                       */
/*           Functions : gc_handleoverflow(arg);                         */
/*                       gcmaptable(arg);                                */
/*                                                                       */
/*************************************************************************/
/*           Descreption :                                               */
/*                                                                       */
/*************************************************************************/
/*                                                               \Tomtom */
/*************************************************************************/

#include "lispemul.h"
#include "lisptypes.h"
#include "address.h"
#include "address68k.h"
#include "lispglobal.h"
#include "gc.h"



#define MAXSMALLP		65535
#define HTBIGENTRYSIZE		4
#define WORDSPERPAGE		256
#define MAXTYPENUMBER		INIT_TYPENUM
#define GetSegnuminColl(entry1) ((entry1 & 0x01fe) >> 1)
#define GetCountinColl(entry1)  ((entry1 & 0x0fc00) >> 10)
#define GetStkCnt(entry1)		 ((entry1 & 0x0fe00) >> 9)
#define Oddp(num) (((num % 2) != 0)?1:0)
#define Evenp(num,prim) (((num % prim) == 0)?1:0)
#define Increment_Allocation_Count(n)			\
    if (*Reclaim_cnt_word != NIL) 			\
		if (*Reclaim_cnt_word > n)		\
			(*Reclaim_cnt_word) -= n;	\
		else { *Reclaim_cnt_word = NIL; 	\
			  doreclaim();  		\
			};				\


gc_handleoverflow(arg)
DLword	arg;
   { struct htoverflow  *cell;
     struct dtd	        *ptr;
     DLword		cellcnt;
     LispPTR            addr;
	  cell = (struct htoverflow *)HToverflow;
			/* This proc. protected from interrupt */
	while((addr = cell->ptr) != NIL)
	   {
		REC_GCLOOKUP(addr, cell->pcase);
		cell->ptr = 0;
		cell->pcase = 0;
		++cell; /* (\ADDBASE CELL WORDSPERCELL) */
	   };
	ptr = (struct dtd *)GetDTD(TYPE_LISTP);
		/* same as "extern struct dtd *ListpDTD" */
	if ((cellcnt = ptr->dtd_cnt0) > 1024)
	   { Increment_Allocation_Count(cellcnt);
		ptr->dtd_oldcnt += cellcnt;
		ptr->dtd_cnt0 = 0;
	   };
	return(arg);
   }

gcmaptable(arg)
DLword	arg;
   { struct htoverflow	*cell;
	struct dtd	*ptr;
	DLword		cellcnt;
	int		typnum;
	LispPTR		addr;			
	cell = (struct htoverflow *)HToverflow;	
			/* This proc. protected from interrupt */
	while((addr = cell->ptr) != NIL)
	   {
		REC_GCLOOKUP(addr, cell->pcase);
		cell->ptr = 0;
		cell->pcase = 0;
		++cell; /* (\ADDBASE CELL WORDSPERCELL) */
	   };
	for(typnum = 1; typnum <= *MaxTypeNumber_word; ++typnum)
	   /* applied alltype */
	   { ptr = (struct dtd *)GetDTD(typnum);
		if ((cellcnt = ptr->dtd_cnt0) != 0)
		   { ptr->dtd_oldcnt += cellcnt;
		     ptr->dtd_cnt0 = 0;
		     Increment_Allocation_Count(cellcnt);
		   };
	   };
	return(arg);
   }




