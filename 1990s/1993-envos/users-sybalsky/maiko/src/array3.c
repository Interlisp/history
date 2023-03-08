/* This is G-file @(#) array3.c Version 2.9 (10/12/88). copyright Xerox & Fuji Xerox  */
static char *id = "@(#) array3.c	2.9 10/12/88";


/************************************************************************/
/*									*/
/*	Copyright 1989, 1990 Venue, Fuji Xerox Co., Ltd, Xerox Corp.	*/
/*									*/
/*	This file is work-product resulting from the Xerox/Venue	*/
/*	Agreement dated 18-August-1989 for support of Medley.		*/
/*									*/
/************************************************************************/


/************************************************************************/
/*									*/
/*			     A R R A Y 3 . C				*/
/*									*/
/*	Contains:	N_OP_aref1					*/
/*									*/
/************************************************************************/

#include <stdio.h>
#include "lispemul.h"
#include "lspglob.h"
#include "adr68k.h"
#include "lispmap.h"
#include "lsptypes.h"
#include "emlglob.h"
#include "arith.h"
#include "my.h"

/***	N_OP_aref1   -- op 266   (array index)   ***/
N_OP_aref1(arrayarg, inx)
  register LispPTR arrayarg, inx;
  {

    register LispPTR baseL;
    register int type, index;
    register OneDArray *arrayblk;
    LispPTR temp;
    register int result;

	/*	for CREATECELL  */
    register DLword	*wordp;
    DLword	*createcell68k();

  /*  verify array  */
    if (GetTypeNumber(arrayarg) != TYPE_ONED_ARRAY) ERROR_EXIT(inx);
    arrayblk = (OneDArray *)Addr68k_from_LADDR(arrayarg);

  /*  test and setup index  */
    N_GetPos(inx, index, inx);
    if (index >= arrayblk->totalsize) ERROR_EXIT(inx);
    index += arrayblk->offset;

  /*  setup typenumber  */
    type = 0xFF & arrayblk->typenumber;

  /*  setup base  */
    baseL = arrayblk->base;

  /*  disp on type  */
    aref_switch(type, inx);

} /*  end N_OP_aref1()  */


