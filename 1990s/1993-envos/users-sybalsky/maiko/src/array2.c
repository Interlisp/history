/* This is G-file @(#) array2.c Version 2.9 (10/12/88). copyright Xerox & Fuji Xerox  */
static char *id = "@(#) array2.c	2.9 10/12/88";


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
/*			    A R R A Y 2 . C				*/
/*									*/
/*	Contains N_OP_misc4, the ASET opcode.				*/
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



/************************************************************************/
/*									*/
/*			N _ O P _ m i s c 4				*/
/*									*/
/*	CL:ASET opcode	op 373/7 (data, base typenumber, index)		*/
/*									*/
/************************************************************************/

N_OP_misc4(data, base, typenumber, inx, alpha)
  int alpha;
  register LispPTR base, data, typenumber, inx;
  {  
    register int new;
    register int index;
    int type;

    if (alpha != 7) ERROR_EXIT(inx);

    /*  test and setup index  */
    N_GetPos(inx, index, inx);
 
    /*  test and setup typenumber  */
    N_GetPos(typenumber, type, inx);

    aset_switch(type, inx);

doufn:		ERROR_EXIT(inx);

  } /*  end N_OP_misc4()  */

