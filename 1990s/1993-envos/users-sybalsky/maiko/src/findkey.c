/* @(#) findkey.c Version 2.7 (4/21/92). copyright envos & Fuji Xerox  */
static char *id = "@(#) findkey.c	2.7 4/21/92";


/************************************************************************/
/*									*/
/*	Copyright 1989, 1990 Venue, Fuji Xerox Co., Ltd, Xerox Corp.	*/
/*									*/
/*	This file is work-product resulting from the Xerox/Venue	*/
/*	Agreement dated 18-August-1989 for support of Medley.		*/
/*									*/
/************************************************************************/


#include "lispemul.h"
#include "lispmap.h"
#include "emlglob.h"
#include "stack.h"
#include "lspglob.h"
#include "adr68k.h"


/***********************************************************************/
/*
		File Name :	findkey.c

		Desc	:

				Date :		Mar. 29 88
				Edited by :	Bob Krivacic
		Including :	N_OP_findkey


*/
/**********************************************************************/


LispPTR N_OP_findkey(tos, byte)
  register LispPTR tos;
  register int byte;
  {
    LispPTR *ptr ;
    DLword *find_end ;
   DLword arg_nth ;

#ifdef TRACE
    printPC();
    printf("TRACE : N_OP_findkey \n");
#endif

    if(CURRENTFX->alink & 1)
      { /* slow case */
	find_end = (DLword *)Addr68k_from_LADDR(STK_OFFSET | (CURRENTFX->blink-4)) ;
      }
    else
      { /*  Fast cae */
	find_end = ((DLword *)CURRENTFX) -2-4;
      }

    arg_nth =byte + 1 ;

    for ( ptr =(LispPTR *) (IVar + ((byte * 2) - 2));
	  (unsigned)find_end >= (unsigned) ptr ; ptr += 2, arg_nth +=2)
      {
	if (*ptr == tos)
	  { /* KEY founded */
	    return(S_POSITIVE | arg_nth);
	  }
      } /* for end */

/* No matched */

    return(NIL_PTR);

  }/* end N_OP_findkey() */


