/* @(#) asmbitblt.c Version 1.2 (4/23/92). copyright venue & Fuji Xerox  */
static char *id = "@(#) asmbitblt.c	1.2 4/23/92	(venue & Fuji Xerox)";
/* @(#) asmbitblt.c Version 2.45 (5/20/91). copyright Venue & Fuji Xerox  */
static char *id = "@(#) asmbitblt.c	2.45 5/20/91		(Venue & Fuji Xerox)";

/************************************************************************/
/*									*/
/*			File:	asmbitblt.c				*/
/*									*/
/*	Dummy C-function "bitblt", used to compile the bitblt code	*/
/*	for hand-optimization.						*/
/*									*/
/*									*/
/*									*/
/*									*/
/************************************************************************/


/************************************************************************/
/*									*/
/*	(C) Copyright 1989, 1990, 1991 Venue. All Rights Reserved.	*/
/*	Manufactured in the United States of America.			*/
/*									*/
/*	The contents of this file are proprietary information 		*/
/*	belonging to Venue, and are provided to you under license.	*/
/*	They may not be further distributed or disclosed to third	*/
/*	parties without the specific permission of Venue.		*/
/*									*/
/************************************************************************/



#include "lispemul.h"
#include "lispglobal.h"
#include "lispmap.h"
#include "lisptypes.h"
#include "emulglobal.h"
#include "address68k.h"
#include "address.h"
#include "arith.h"
#include "stack.h"
#include "cell.h"
#include "gc.h"


#include "bb.h"
#include "bitblt.h"
#include "pilotbbt.h"


void	bitblt(srcbase, dstbase, sx, dx, w, h, srcbpl, dstbpl,
		  backwardflg, src_comp, op, gray, num_gray, curr_gray_line)

  DLword * srcbase, dstbase;
  int sx, dx, w, h, srcbpl, dstbpl, backwardflg, src_comp, op, gray, num_gray, curr_gray_line;
  
  { 
	new_bitblt_code;
  }

