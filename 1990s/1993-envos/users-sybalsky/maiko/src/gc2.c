/* This is G-file @(#) gc2.c Version 2.7 (2/8/93). copyright Xerox & Fuji Xerox  */
static char *id = "@(#) gc2.c	2.7 2/8/93";



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
/**********************************************************************/
/*
 		File Name:	gc2.c
		Desc: implement opcode SCAN1,SCAN2,GCRECLAIMCELL
 
 
		Including :	OP_scan1
				OP_scan2
				OP_gcreccell
							
*/
/**********************************************************************/

#include "lispemul.h"
#include "lispmap.h"
#include "lsptypes.h"
#include "lspglob.h"
#include "emlglob.h"
#include "address.h"
#include "adr68k.h"

#ifdef GCC386
#include "inlnPS2.h"
#endif /* GCC386 */





/**********************************************************************/
/*
		Func Name : OP_gcscan1
*/
/**********************************************************************/

OP_gcscan1()
  {
    DLword gcscan1();

#ifdef TRACE
    printPC();
    printf("TRACE: OP_gcscan1()\n");
#endif
    if((TopOfStack & SEGMASK)==S_POSITIVE)
      {
	TopOfStack=gcscan1(LOLOC(TopOfStack));
      }
    if(TopOfStack != NIL) TopOfStack |= S_POSITIVE ;
    PC++;
   } /* OP_gcscan1 end */




/**********************************************************************/
/*
		Func Name : OP_gcscan2
*/
/**********************************************************************/

OP_gcscan2()
  {
    DLword gcscan2();

#ifdef TRACE
    printPC();
    printf("TRACE: OP_gcscan2()\n");
#endif
    if((TopOfStack & SEGMASK)==S_POSITIVE)
      {
	TopOfStack=gcscan2(LOLOC(TopOfStack));
      }
    if(TopOfStack != NIL) TopOfStack |= S_POSITIVE ;
    PC++;
  } /* OP_gcscan2 end */

