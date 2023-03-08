/* This is G-file @(#) timeout.h Version 1.9 (6/4/90). copyright Venue & Fuji Xerox  */

extern jmp_buf jmpbuf;


/************************************************************************/
/*									*/
/*	Copyright 1989, 1990 Venue, Fuji Xerox Co., Ltd, Xerox Corp.	*/
/*									*/
/*	This file is work-product resulting from the Xerox/Venue	*/
/*	Agreement dated 18-August-1989 for support of Medley.		*/
/*									*/
/************************************************************************/


/*** TIMEOUT_TIME is changeable by UNIX env var LDEFILETIMEOUT. 
#define	TIMEOUT_TIME	10 **/

extern	int	TIMEOUT_TIME;


#define	SETJMP(x)	\
  {				\
    if(setjmp(jmpbuf) != 0) return(x);		\
  }

#define	TIMEOUT(exp)			\
  {			\
    alarm(TIMEOUT_TIME);	\
    exp;			\
    alarm(0);		\
  }

#define	S_TOUT(exp)	\
		alarm(TIMEOUT_TIME),\
		exp,			\
		alarm(0)

#define	ERRSETJMP(rval)					\
  {							\
    if(setjmp(jmpbuf) != 0)				\
      {							\
	*Lisp_errno = 100;				\
	return(rval);					\
      }							\
  }
