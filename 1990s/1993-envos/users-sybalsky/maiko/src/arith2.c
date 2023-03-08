/* @(#) arith2.c Version 2.13 (3/19/90). copyright Venue & Fuji Xerox  */
static char *id = "@(#) arith2.c	2.13 3/19/90		(Venue & Fuji Xerox)";


/************************************************************************/
/*									*/
/*	Copyright 1989, 1990 Venue, Fuji Xerox Co., Ltd, Xerox Corp.	*/
/*									*/
/*	This file is work-product resulting from the Xerox/Venue	*/
/*	Agreement dated 18-August-1989 for support of Medley.		*/
/*									*/
/************************************************************************/

/*
 *	Copyright (C) 1987 by Fuji Xerox Co., Ltd. All rights reserved.
 *
 *	Author	:	Hiroshi Hayata
 */
#include <stdio.h>
#include "lispemul.h"
#include "lspglob.h"
#include "emlglob.h"
#include "adr68k.h"
#include "lispmap.h"
#include "lsptypes.h"
#include "fp.h"
#include "arith.h"

DLword	*createcell68k();


/************************************************************
N_OP_plus2
	entry		PLUS2		OPCODE[0324]
	entry		IPLUS2		OPCODE[0330]
	return(tos + b)
************************************************************/

int N_OP_plus2(tosm1, tos)
	int tosm1, tos;
{
register int	arg1,arg2;
register int	result;

	N_GETNUMBER( tos, arg1, doufn );
	N_GETNUMBER( tosm1, arg2, doufn );

#if defined(SUN3_OS3_OR_OS4_IL) || defined(I386)

	result = plus32(arg1, arg2);
	N_ARITH_SWITCH(result);

doufn2:	plus_err_label();
	ERROR_EXIT(tos);

#else
	result = arg1 + arg2;
	if ( ((arg1>=0) == (arg2>=0)) && ((result>=0) != (arg1>=0)) )
		{ERROR_EXIT(tos);}
	N_ARITH_SWITCH(result);

#endif

doufn:	return(N_OP_fplus2(tosm1, tos));

}



/************************************************************************/
/*									*/
/*			N _ O P _ i p l u s 2				*/
/*									*/
/*	Implements the IPLUS2 opcode--add the two arguments, which	*/
/*	must be SMALLP or FIXP						*/
/*									*/
/************************************************************************/

int N_OP_iplus2(tosm1, tos)
	int tosm1, tos;
{
register int	arg1,arg2;
register int	result;

	N_IGETNUMBER( tos, arg1, doufn );
	N_IGETNUMBER( tosm1, arg2, doufn );

#if defined(SUN3_OS3_OR_OS4_IL) || defined(I386)

	result = iplus32(arg1, arg2);
	N_ARITH_SWITCH(result);
dummy:	iplus_err_label();

#else

	result = arg1 + arg2;
	if ( ((arg1>=0) == (arg2>=0)) && ((result>=0) != (arg1>=0)) )
		{ERROR_EXIT(tos);}
	N_ARITH_SWITCH(result);

#endif

doufn:		ERROR_EXIT(tos);

}


/************************************************************
N_OP_difference
	entry		DIFFERENCE		OPCODE[0325]
	entry		IDIFFERENCE		OPCODE[0331]
	return(a - tos)
************************************************************/

int N_OP_difference(tosm1, tos)
	int tosm1, tos;
{
register int	arg1,arg2;
register int	result;

	N_GETNUMBER( tosm1, arg1, doufn );
	N_GETNUMBER( tos, arg2, doufn );

#if defined(SUN3_OS3_OR_OS4_IL) || defined(I386)

	result = sub32(arg1, arg2);
	N_ARITH_SWITCH(result);

doufn2:	diff_err_label();
	ERROR_EXIT(tos);

#else

	result = arg1 - arg2;
	if ( ((arg1>=0) == (arg2<0)) && ((result>=0) != (arg1>=0)) )
		{ERROR_EXIT(tos);}
	N_ARITH_SWITCH(result);

#endif

doufn:	return(N_OP_fdifference(tosm1, tos));

}


int N_OP_idifference(tosm1, tos)
	int tosm1, tos;
{
register int	arg1,arg2;
register int	result;

	N_IGETNUMBER( tosm1, arg1, doufn );
	N_IGETNUMBER( tos, arg2, doufn );

#if defined(SUN3_OS3_OR_OS4_IL) || defined(I386)

	result = isub32(arg1, arg2);
	N_ARITH_SWITCH(result);
dummy:	idiff_err_label();

#else

	result = arg1 - arg2;
	if ( ((arg1>=0) == (arg2<0)) && ((result>=0) != (arg1>=0)) )
		{ERROR_EXIT(tos);}
	N_ARITH_SWITCH(result);

#endif
doufn:	ERROR_EXIT(tos);

}



/************************************************************
N_OP_logxor
	entry		LOGXOR2		OPCODE[0346]
	return(tosm1 ^ tos)
************************************************************/

N_OP_logxor(tosm1, tos)
	int tosm1, tos;
{
	N_IARITH_BODY_2(tosm1, tos, ^);
}



/************************************************************
N_OP_logand
	entry		LOGAND2		OPCODE[0345]
	return(tosm1 & tos)
************************************************************/
N_OP_logand(tosm1, tos)
	int tosm1, tos;
{
	N_IARITH_BODY_2(tosm1, tos, &);
}



/************************************************************
N_OP_logor
	entry		LOGOR2		OPCODE[0344]
	return(tosm1 | tos)
************************************************************/
N_OP_logor(tosm1, tos)
	int tosm1, tos;
{
	N_IARITH_BODY_2(tosm1, tos, |);
}

/************************************************************
N_OP_greaterp
	entry		GREATERP		OPCODE[0363]
	entry		IGREATERP		OPCODE[0361]
	return(tosm1 > tos)

************************************************************/
N_OP_greaterp(tosm1, tos)
	int tosm1, tos;
{
register int arg1,arg2;

	N_GETNUMBER( tosm1, arg1, do_ufn);
	N_GETNUMBER( tos, arg2, do_ufn);

	if(arg1 > arg2)
		return(ATOM_T);
	else
		return(NIL_PTR);

do_ufn:	 return(N_OP_fgreaterp(tosm1, tos));
}


N_OP_igreaterp(tosm1, tos)
	int tosm1, tos;
{
register int arg1,arg2;

	N_IGETNUMBER( tosm1, arg1, do_ufn);
	N_IGETNUMBER( tos, arg2, do_ufn);

	if(arg1 > arg2)
		return(ATOM_T);
	else
		return(NIL_PTR);

do_ufn:	ERROR_EXIT(tos);
}



/************************************************************
N_OP_iplusn
	entry		IPLUS.N		OPCODE[0335]
	return(tos + n)
************************************************************/
N_OP_iplusn(tos, n)
	int n, tos;
{

register int	arg1;
register int	result;

	N_IGETNUMBER( tos, arg1, do_ufn );

#if defined(SUN3_OS3_OR_OS4_IL) || defined(I386)

	result = iplus32n(arg1, n);
	N_ARITH_SWITCH(result);
dummy:	iplusn_err_label();

#else

	result = arg1 + n;
	if ((result < 0) && (arg1 >= 0)) {ERROR_EXIT(tos);}
	N_ARITH_SWITCH(result);

#endif

do_ufn:	ERROR_EXIT(tos);

}



/************************************************************
N_OP_idifferencen
	entry		IDIFFERENCE.N		OPCODE[0336]
	return(tos - n)
************************************************************/
N_OP_idifferencen(tos, n)
	int n, tos;
{
register int	arg1;
register int	result;

	N_IGETNUMBER( tos, arg1, do_ufn );

#if defined(SUN3_OS3_OR_OS4_IL) || defined(I386)

	result = sub32n(arg1, n);
	N_ARITH_SWITCH(result);
dummy:	idiffn_err_label();

#else

	result = arg1 - n;
	if ((result >= 0) && (arg1 < 0)) {ERROR_EXIT(tos);}
	N_ARITH_SWITCH(result);

#endif

do_ufn:	ERROR_EXIT(tos);

}


