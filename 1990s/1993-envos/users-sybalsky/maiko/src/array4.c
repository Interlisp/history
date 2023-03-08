/* This is G-file @(#) array4.c Version 2.7 (10/12/88). copyright Xerox & Fuji Xerox  */
static char *id = "@(#) array4.c	2.7 10/12/88";


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
/*				A R R A Y 4 . C				*/
/*									*/
/*	Contains:	N_OP_aset1					*/
/*									*/
/************************************************************************/

#include <stdio.h>
#include "lispemul.h"
#include "lspglob.h"
#include "adr68k.h"
#include "lispmap.h"
#include "lsptypes.h"
#include "arith.h"
#include "gc.h"
#include "my.h"

/***	N_OP_aset1   -- op 267   (new-value array index)   ***/


/************************************************************************/
/*									*/
/*			N _ O P _ a s e t 1				*/
/*									*/
/*	1-dimensional array setter.					*/
/*									*/
/************************************************************************/

N_OP_aset1(data, arrayarg, inx)
  register int inx;
  LispPTR arrayarg;
  register LispPTR data;
  {
    register int type;
    register OneDArray *arrayblk;
    register LispPTR base;
    register int new;
    register int index;

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
      base = arrayblk->base;


      /*  disp on type  */
      aset_switch(type, inx);

doufn:		ERROR_EXIT(inx);

  } /*  end N_OP_aset1()  */

