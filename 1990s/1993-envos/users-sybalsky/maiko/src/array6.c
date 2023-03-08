/* This is G-file @(#) array6.c Version 2.10 (4/21/92). copyright Xerox & Fuji Xerox  */
static char *id = "@(#) array6.c	2.10 4/21/92";


/************************************************************************/
/*									*/
/*	Copyright 1989, 1990 Venue, Fuji Xerox Co., Ltd, Xerox Corp.	*/
/*									*/
/*	This file is work-product resulting from the Xerox/Venue	*/
/*	Agreement dated 18-August-1989 for support of Medley.		*/
/*									*/
/************************************************************************/


#include <stdio.h>
#include "lispemul.h"
#include "lspglob.h"
#include "adr68k.h"
#include "lispmap.h"
#include "lsptypes.h"
#include "emlglob.h"
#include "gc.h"
#include "arith.h"
#include "my.h"

/***	N_OP_aset2   -- op 357   (new-value array index0 index1)   ***/
N_OP_aset2(data, arrayarg, inx0, inx1)
LispPTR arrayarg, inx0, inx1;
register LispPTR data;
{

register int type;
register LispArray *arrayblk;
register LispPTR base;
register int new;
register int index, temp;
int j;

      /*  verify array  */
      if (GetTypeNumber(arrayarg) != TYPE_TWOD_ARRAY) ERROR_EXIT(inx1);
      arrayblk = (LispArray *)Addr68k_from_LADDR(arrayarg);
      base = arrayblk->base;

      /*  test and setup index  */
      N_GetPos(inx1, temp, inx1);
      if (temp >= (j = arrayblk->Dim1)) ERROR_EXIT(inx1);
      N_GetPos(inx0, index, inx1);
      if (index >= arrayblk->Dim0) ERROR_EXIT(inx1);
      index *= j;
      index += temp;

      /*  setup typenumber  */
      type = 0xFF & arrayblk->typenumber;

      /*  disp on type  */
      aset_switch(type, inx1);

doufn:		ERROR_EXIT(inx1);

} /*  end N_OP_aset2()  */

