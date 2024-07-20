/* @(#) asmbbt.c Version 1.2 (4/23/92). copyright venue & Fuji Xerox  */
static char *id = "@(#) asmbbt.c	1.2 4/23/92	(venue & Fuji Xerox)";

/************************************************************************/
/*									*/
/*			File:	asmbbt.c				*/
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
#include "lspglob.h"
#include "lispmap.h"
#include "lsptypes.h"
#include "emlglob.h"
#include "adr68k.h"
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
