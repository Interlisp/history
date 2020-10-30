/* @(#) ubf2.c Version 1.10 (4/22/92). copyright Venue & Fuji Xerox  */
static char *id = "@(#) ubf2.c	1.10 4/22/92";
/*	ubf2.c
 */





/************************************************************************/
/*									*/
/*	(C) Copyright 1989-92 Venue. All Rights Reserved.		*/
/*	Manufactured in the United States of America.			*/
/*									*/
/*	The contents of this file are proprietary information 		*/
/*	belonging to Venue, and are provided to you under license.	*/
/*	They may not be further distributed or disclosed to third	*/
/*	parties without the specific permission of Venue.		*/
/*									*/
/************************************************************************/


#include <stdio.h>
#include <math.h>
#include "lispemul.h"
#include "fp.h"

/************************************************************
	OP_ub2  -- op 354  ==  UBFLOAT2
354/0	ADD
354/1	SUB
354/2	ISUB
354/3	MULT
354/4	DIV
354/5	GREAT
354/6	MAX
354/7	MIN
354/8	REM
354/9	AREF
***********************************************************/
N_OP_ubfloat2(a2, a1, alpha)
int a1, a2;
int alpha;
{
REGISTER float arg1, arg2;
float ans;
int ret;

/*	Unboxed floating point args (a1, a2) look like float, but	*/
/*	can't be declared as such because all float args get passed	*/
/*	as double.  (That can be avoided in ansi C.)  Instead, they	*/
/*	are declared int and accessed as float through cast pointers.	*/
/*	The return value is handled similarly.				*/


  arg1 = *(float *)&a1;	
  arg2 = *(float *)&a2;
  FPCLEAR;
  switch (alpha) {
    case 0: /* add */  ans = arg1 + arg2; break;
    case 1: /* sub */  ans = arg2 - arg1; break;
    case 2: /* isub */ ans = arg1 - arg2; break;
    case 3: /* mul */  ans = arg1 * arg2; break;
    case 4: /* div */  ans = arg2 / arg1; break;
    case 5: /* gt */   if (arg2 > arg1) return(ATOM_T); else return(NIL_PTR);
    case 6: /* max */  if (arg2 > arg1) return(a2);     else return(a1);
    case 7: /* min */  if (arg2 > arg1) return(a1);     else return(a2);
    case 8: /* rem */  ans = fmod(arg2,arg1); break;
    default: ERROR_EXIT(a1);
  }/* end switch */

  ret = *(int *)&ans;	/* Convert it back to int for 32 bit storage */
  if (FPTEST(ans)) ERROR_EXIT(a1);
  return(ret);


}/* end N_OP_ub2() */

	/* end module */
