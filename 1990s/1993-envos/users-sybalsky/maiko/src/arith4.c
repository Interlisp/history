/* @(#) arith4.c Version 2.12 (4/21/92). copyright envos & Fuji Xerox  */
static char *id = "@(#) arith4.c	2.12 4/21/92	(envos & Fuji Xerox)";
/*
 *	Copyright (C) 1987 by Fuji Xerox Co., Ltd. All rights reserved.
 *
 *	Author :  Takeshi Shimizu
 *
 */
/***********************************************************************/
/*
		File Name :	arith4.c

		Including :	OP_times2 326Q(OP_itimes2 332Q)

				OP_quot 327Q(OP_iquot 333Q)
				OP_reminder 334Q

*/
/**********************************************************************/

#include "lispemul.h"
#include "lispmap.h"
#include "emlglob.h"
#include "lspglob.h"
#include "lsptypes.h"
#include "address.h"
#include "adr68k.h"
#include "cell.h"
#include "fp.h"
#include "arith.h"



/**********************************************************************/
/*

		Func name :	N_OP_times2(itimes2)

*/
/**********************************************************************/
int N_OP_times2(tosm1, tos)
	int tosm1, tos;
{
register int	arg1,arg2;
register int	result;



	N_GETNUMBER( tosm1, arg1, doufn );
	N_GETNUMBER( tos, arg2, doufn );

#ifdef SUN3_OS3_OR_OS4_IL

	result = mpy32(arg1, arg2);
	N_ARITH_SWITCH(result);
dummy:	mpy_err_label();

#else

	result = arg1 * arg2;
	if ((arg2 !=0) &&((result / arg2) != arg1) ) goto doufn2;
	N_ARITH_SWITCH(result);

#endif

doufn2:	ERROR_EXIT(tos);
doufn:	return(N_OP_ftimes2(tosm1, tos));


} /* end N_OP_times2 */

int N_OP_itimes2(tosm1, tos)
	int tosm1, tos;
{
register int	arg1,arg2;
register int	result;


	N_IGETNUMBER( tosm1, arg1, doufn );
	N_IGETNUMBER( tos, arg2, doufn );

#ifdef SUN3_OS3_OR_OS4_IL

	result = impy32(arg1, arg2);
	N_ARITH_SWITCH(result);
dummy:	impy_err_label();

#else

	result = arg1 * arg2;
	if ((arg2 !=0) &&( (result / arg2) != arg1) ) {goto doufn;}
	N_ARITH_SWITCH(result);

#endif

doufn:	ERROR_EXIT(tos);


} /* end N_OP_itimes2 */



/**********************************************************************/
/*

		Func name :	N_OP_quot(iquot)

*/
/**********************************************************************/
int N_OP_quot(tosm1, tos)
	int tosm1, tos;
{
register int	arg1,arg2;
register int	result;


	N_GETNUMBER( tosm1, arg1, doufn );
	N_GETNUMBER( tos, arg2, doufn );
	if (arg2 == 0) goto doufn2;

#ifdef SUN3_OS3_OR_OS4_IL

	result = quot32(arg1, arg2);
	N_ARITH_SWITCH(result);
dummy:	quot_err_label();

#else

	result = arg1/arg2;	/* lmm: note: no error case!! */
	N_ARITH_SWITCH(result);
#endif
doufn2:	ERROR_EXIT(tos);
doufn:	return(N_OP_fquotient(tosm1, tos));

} /* end N_OP_quot */

int N_OP_iquot(tosm1, tos)
	int tosm1, tos;
{
register int	arg1,arg2;
register int	result;


	N_IGETNUMBER( tosm1, arg1, doufn );
	N_IGETNUMBER( tos, arg2, doufn );
	if (arg2 == 0) goto doufn;

#ifdef SUN3_OS3_OR_OS4_IL

	result = iquot32(arg1, arg2);
	N_ARITH_SWITCH(result);
dummy:	iquot_err_label();

#else

	result = arg1/arg2;
	N_ARITH_SWITCH(result);

#endif

doufn:	ERROR_EXIT(tos);

} /* end N_OP_quot */


/**********************************************************************/
/*

		Func name :	N_OP_iremainder

*/
/**********************************************************************/

int N_OP_iremainder(tosm1, tos)
	int tosm1, tos;
{
register int	arg1,arg2;
register int	result;


	N_IGETNUMBER( tosm1, arg1, doufn );
	N_IGETNUMBER( tos, arg2, doufn );
	if (arg2 == 0) goto doufn;

#ifdef SUN3_OS3_OR_OS4_IL

	result = irem32(arg1, arg2);
	N_ARITH_SWITCH(result);
dummy:	irem_err_label();

#else

	result = arg1 % arg2;
	N_ARITH_SWITCH(result);

#endif

doufn:	ERROR_EXIT(tos);

} /* end N_OP_iremainder */

