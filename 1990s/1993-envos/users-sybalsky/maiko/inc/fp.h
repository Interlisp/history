/* @(#) fp.h Version 1.17 (11/25/92). copyright Venue  */


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
/*									*/
/*									*/
/*									*/
/*									*/
/************************************************************************/

#ifdef ULTRIX
#include <ieeefp.h>
#endif /* ULTRIX */

#ifdef RISCOS
/*#include <ieeefp.h> */
/*#define isnan isnand */
#define isnan(x) 0
#endif /* RISCOS */


/*  --------------------------------------------------
    FPCLEAR         - clear status as necessary
    FPTEST(result)  - check result or status

    Sun 4 compiler w. -O2 moves too much code around
    to use FLTINT.
    --------------------------------------------------  */

#ifdef FLTINT
extern int  FP_error;

/*  Note that a compiler may very likely move code around the arithmetic
    operation, causing this test (set by an interrupt handler) to be
    incorrect.  For example, the Sun SPARC compiler with -O2 makes
    this test incorrect.
 */

#define FPCLEAR         FP_error = 0;
#define FPTEST(result)  FP_error

#else

/*  fpstatus_ is a FORTRAN library routine (in libc) which
    can be called to determine floating point status results.
    Documented in the Sun manual, "Floating Point Programmer's Guide",
    (Rev. A 19-Sep-86), pg. 34, it does *not* exist in libc for the
    SPARC.

    For sparc, should also check for isnan?  Don't know what isnormal
    & issubnormal do (these are sunos4.0 only)
 */

#if (defined(sparc) || defined(I386) || defined(HPUX))

#define FPCLEAR
#define FPTEST(result) (isinf(result) || isnan(result))

#elif APOLLO
	/**********************************************************/
	/*  Need values.h & nan.h, so we all parts of IsNANorINF  */
	/*  are defined.  IsNANorINF uses structure aliasing to   */
	/*  get at pieces of the float to test it, so the item    */
	/*  being tested can't be a register variable.  Sigh.     */
	/**********************************************************/
#include </sys5/usr/include/values.h>
#include </sys5/usr/include/nan.h>
#define FPCLEAR
#define FPTEST(result) (IsNANorINF(result))
#undef REGISTER
#define REGISTER

#elif INDIGO
#include <nan.h>
#define FPCLEAR
#define FPTEST(result) (IsNANorINF(result))
#else
#ifdef AIX
#define FPCLEAR
#define FPTEST(result) ((!finite(result)) || isnan(result))
#else
static int constant0 = 0;
unsigned int fpstatus_();

#define FPCLEAR         fpstatus_(&constant0);
#define FPTEST(result) (fpstatus_(&constant0) & 0xF0)

#endif /* AIX */

#endif /* sparc | I386 */

#endif /* FLTINT */



/************************************************************************/
/*									*/
/*		Sun 386i Floating-point accelerator (80387)		*/
/*			Initialization macros				*/
/*									*/
/*	I386Reset -- set up so convert-to-integer truncates		*/
/*	I386Round -- set up so FP operation round properly		*/
/*									*/
/************************************************************************/

#ifdef I386
#define I386Reset			\
  {	/* 80387 initialization */ 	\
    asm(".text");			\
    asm("fldcw __FP_trunc");		\
  }

#define I386Round		\
  {				\
    asm(".text");		\
    asm("fldcw __FP_round");	\
  }

#endif /* I386 */

