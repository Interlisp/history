/* @(#) shift.c Version 2.10 (4/21/92). copyright envos & Fuji Xerox  */
static char *id = "@(#) shift.c	2.10 4/21/92";

/*
 *	Copyright (C) 1987 by Fuji Xerox Co., Ltd. All rights reserved.
 *
 *	Author :  Hiroshi Hayata
 *
 */
#include <stdio.h>
#include "lispemul.h"
#include "lspglob.h"
#include "emlglob.h"
#include "adr68k.h"
#include "lispmap.h"
#include "lsptypes.h"
#include "arith.h"

#define	LSH	0347

DLword	*createcell68k();


/************************************************************
N_OP_llsh1
	entry		LLSH1		OPCODE[0340]
	return(a << 1)
************************************************************/
N_OP_llsh1(a)
	int a;
{
	N_ARITH_BODY_1_UNSIGNED(a, 1, <<);
}

/************************************************************
N_OP_llsh8
	entry		LLSH8		OPCODE[0341]
	return(a << 8)
************************************************************/
N_OP_llsh8(a)
	int a;
{
	N_ARITH_BODY_1_UNSIGNED(a, 8, <<);
}

/************************************************************
N_OP_lrsh1
	entry		LRSH1		OPCODE[0342]
	return(a >> 1)
************************************************************/
N_OP_lrsh1(a)
{
	N_ARITH_BODY_1_UNSIGNED(a, 1, >>);
}

/************************************************************
N_OP_lrsh8
	entry		LRSH8		OPCODE[0343]
	return(a >> 8)
************************************************************/
N_OP_lrsh8(a)
	int a;
{
	N_ARITH_BODY_1_UNSIGNED(a, 8, >>);
}

/************************************************************
N_OP_lsh
	entry		LSH		OPCODE[0347]
	return(a <?> b)
************************************************************/
N_OP_lsh(a, b)
	int a, b;
{
register int	arg,arg2;
register int	size;
/*DLword	*wordp;*/

	N_GETNUMBER(b, size, do_ufn);
	N_GETNUMBER(a, arg2, do_ufn);


	if (size > 0) {
		if (size > 31) goto do_ufn;
		arg = arg2 << size;
		if ((arg >> size) != arg2) goto do_ufn;
	} else
	if (size < 0) {
		if (size < -31) goto do_ufn;
		arg = arg2 >> -size;
/*** Commented out JDS 1/27/89:  This punts if you shifted ***/
/*** ANY 1 bits off the right edge.  You CAN'T overflow    ***/
/*** in this direction!!                                   ***/
/*		if ((arg << -size) != arg2) goto do_ufn; */
	} else return(a);



	N_ARITH_SWITCH(arg);

do_ufn:	ERROR_EXIT(b);
}


