/* @(#) array.c Version 2.8 (12/23/88). copyright envos & Fuji Xerox  */
static char *id = "@(#) array.c	2.8 12/23/88		(envos & Fuji Xerox)";


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
#include "arith.h"
#include "my.h"

/************************************************************
 OP_claref  -- op 372/9 (base typenumber index)

type    size    typenumber
  0       0             0      unsigned  : 1 bit
  0       3             3      unsigned  : 8 bits
  0       4             4      unsigned  : 16 bits
  1       4            20      signed    : 16 bits
  1       6            22      signed    : 32 bits
  2       6            38      pointer   : 32 bits
  3       6            54      float     : 32 bits
  4       3            67      character : 8 bits
  4       4            68      character : 16 bits
  5       6            86      Xpointer  : 32 bits


***********************************************************/

/***	N_OP_misc3  -- op 372/9 (base typenumber index)   ***/
N_OP_misc3(baseL, typenumber, inx, alpha)
  int alpha;
  LispPTR baseL, typenumber, inx;
  {
    register int result;
    register int index, type;
    register DLword *wordp;

	/*	for CREATECELL  */
    DLword	*createcell68k();

    if (alpha != 9) ERROR_EXIT(inx);
    /*  test and setup index  */
    N_GetPos(inx, index, inx);

    /*  test and setup typenumber  */
    N_GetPos(typenumber, type, inx);

    /*  disp on type  */
    aref_switch(type, inx);

  } /*  end N_OP_misc3()  */
