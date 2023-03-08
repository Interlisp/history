/* @(#) ldeXdefs.h Version 1.2 (5/27/92). copyright Venue & Fuji Xerox  */

/* * * * * X defs for all files in Medley * * * * */



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


#ifndef __LDEXDEF__

#define __LDEXDEF__ 1
#include <signal.h>
#ifdef ISC
#define XLOCK { XLocked++; /* printf("L"); fflush(stdout);*/}
#define XUNLOCK					\
  { XLocked--;/* printf("U"); fflush(stdout);*/	\
    if (XNeedSignal)				\
      {						\
	XNeedSignal = 0;			\
	kill(getpid(), SIGPOLL);		\
      };						\
  }
#else
#define XLOCK
#define XUNLOCK
#endif	/* ISC */

extern int XLocked;
extern int XNeedSignal;
/* this is !0 if we're locked; it should be 0 or larger always */
#endif

