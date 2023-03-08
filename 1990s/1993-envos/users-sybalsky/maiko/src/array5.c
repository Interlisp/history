/* This is G-file @(#) array5.c Version 2.7 (10/12/88). copyright Xerox & Fuji Xerox  */
static char *id = "@(#) array5.c	2.7 10/12/88";


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
/*			    A R R A Y 5 . C				*/
/*									*/
/*	Contains:	N_OP_aref2  2-d AREF opcode			*/
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



/************************************************************************/
/*									*/
/*			N _ O P _ a r e f 2				*/
/*									*/
/*	2-d AREF op 356   (array index0 index1)				*/
/*									*/
/************************************************************************/

N_OP_aref2(arrayarg, inx0, inx1)
  LispPTR arrayarg, inx0, inx1;
  {
    register LispPTR baseL;
    register int type;
    register int index, temp;
    register LispArray *arrayblk;
    register int result;
    int j;
	/*	for CREATECELL  */
    register DLword	*wordp;
    DLword	*createcell68k();

      /*  verify array  */
      if (GetTypeNumber(arrayarg) != TYPE_TWOD_ARRAY) ERROR_EXIT(inx1);
      arrayblk = (LispArray *)Addr68k_from_LADDR(arrayarg);
      baseL = arrayblk->base;

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
      aref_switch(type, inx1);

} /*  end N_OP_aref2()  */


