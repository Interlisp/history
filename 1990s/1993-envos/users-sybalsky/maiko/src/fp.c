/* @(#) fp.c Version 2.10 (4/22/92). copyright venue & Fuji Xerox  */
static char *id = "@(#) fp.c	2.10 4/22/92	(venue & Fuji Xerox)";




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

/************************************************************************/
/*									*/
/*				  F P . C  				*/
/*									*/
/*	Floating-point arithmetic code.					*/
/*									*/
/************************************************************************/
#include <stdio.h>
#include "lispemul.h"
#include "lspglob.h"
#include "adr68k.h"
#include "lispmap.h"
#include "lsptypes.h"
#include "emlglob.h"
#include "my.h"
#include "fp.h"

/************************************************************
	N_OP_fplus2       -- op 350
	N_OP_fdifference  -- op 351
	N_OP_ftimes2      -- op 352
	N_OP_fquotient    -- op 353
	N_OP_fgreaterp    -- op 362
***********************************************************/

DLword *createcell68k();



/************************************************************************/
/*									*/
/*			N _ O P _ f p l u s 2				*/
/*									*/
/*	2-argument floating point addition opcode			*/
/*									*/
/************************************************************************/

N_OP_fplus2(parg1, parg2)
  LispPTR parg1, parg2;
  {
    REGISTER float arg1;
    REGISTER float arg2;
    REGISTER float result;
    register DLword *wordp;

    N_MakeFloat(parg1, arg1, parg2);
    N_MakeFloat(parg2, arg2, parg2);
    FPCLEAR;
#ifdef I386
    I386Round;
#endif
    result = arg1 + arg2;
    if (FPTEST(result)) ERROR_EXIT(parg2);
    wordp = createcell68k(TYPE_FLOATP);
    *((float *)wordp) = result;
    return(LADDR_from_68k(wordp));
  }  /* end N_OP_fplus2()  */



/************************************************************************/
/*									*/
/*		      N _ O P _ f d i f f e r e n c e			*/
/*									*/
/*	2-arugment floating-point subtraction.				*/
/*									*/
/************************************************************************/

N_OP_fdifference(parg1, parg2)
LispPTR          parg1, parg2;
  {
    REGISTER float arg1, arg2;
    REGISTER float result;
    register DLword *wordp;

    N_MakeFloat(parg1, arg1, parg2);
    N_MakeFloat(parg2, arg2, parg2);
    FPCLEAR;
#ifdef I386
    I386Round;
#endif
    result = arg1 - arg2;
    if (FPTEST(result)) ERROR_EXIT(parg2);
    wordp = createcell68k(TYPE_FLOATP);
    *((float *)wordp) = result;
    return(LADDR_from_68k(wordp));
  }  /* end N_OP_fdifference()  */




/************************************************************************/
/*									*/
/*			    N _ O P _ f t i m e s 2			*/
/*									*/
/*	Floating-point multiplication					*/
/*									*/
/************************************************************************/

N_OP_ftimes2(parg1, parg2)
LispPTR      parg1, parg2;
  {
    REGISTER float arg1, arg2;
    REGISTER float result;
    register DLword *wordp;

    N_MakeFloat(parg1, arg1, parg2);
    N_MakeFloat(parg2, arg2, parg2);
    FPCLEAR;
#ifdef I386
    I386Round;
#endif
    result = arg1 * arg2;
    if (FPTEST(result)) ERROR_EXIT(parg2);
    wordp = createcell68k(TYPE_FLOATP);
    *((float *)wordp) = result;
    return(LADDR_from_68k(wordp));
  }  /* end N_OP_ftimes2()  */




/************************************************************************/
/*									*/
/*			N _ O P _ f q u o t i e n t			*/
/*									*/
/*	floating-point division						*/
/*									*/
/************************************************************************/

N_OP_fquotient(parg1, parg2)
LispPTR        parg1, parg2;
  {
    REGISTER float arg1, arg2;
    REGISTER float result;
    register DLword *wordp;

    N_MakeFloat(parg1, arg1, parg2);
    N_MakeFloat(parg2, arg2, parg2);
    FPCLEAR;
#ifdef I386
    I386Round;
#endif
    result = arg1 / arg2;

    if (FPTEST(result)) ERROR_EXIT(parg2);
    wordp = createcell68k(TYPE_FLOATP);
    *((float *)wordp) = result;
    return(LADDR_from_68k(wordp));
  }  /* end N_OP_fquotient()  */



/************************************************************************/
/*									*/
/*			N _ O P _ f g r e a t e r p			*/
/*									*/
/*	Floating-point >						*/
/*									*/
/************************************************************************/

N_OP_fgreaterp(parg1, parg2)
LispPTR        parg1, parg2;
  {
    REGISTER float arg1, arg2;
    register DLword *wordp;
    register LispPTR lptr;

    N_MakeFloat(parg1, arg1, parg2);
    N_MakeFloat(parg2, arg2, parg2);
    if (arg1 > arg2) return(ATOM_T);
    else return(NIL_PTR);
  }  /* end N_OP_fgreaterp()  */


