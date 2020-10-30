/* @(#) atom.c Version 2.5 (1/9/89). copyright envos & Fuji Xerox  */
static char *id = "@(#) atom.c	2.5 1/9/89";


/************************************************************************/
/*									*/
/*	Copyright 1989, 1990 Venue, Fuji Xerox Co., Ltd, Xerox Corp.	*/
/*									*/
/*	This file is work-product resulting from the Xerox/Venue	*/
/*	Agreement dated 18-August-1989 for support of Medley.		*/
/*									*/
/************************************************************************/

				/* hack */

/**********************************************************************/
/*
		File Name :	atom.c

		Desc	:	implement opcode ATOMCELL.N

					Date :		Apr 13, 1987
					Edited by :	Naoyuki Mitani

		Including :	OP_atomcellN

*/
/**********************************************************************/

#include "lispemul.h"
#include "lispmap.h"
#include "emlglob.h"


#ifndef BIGATOMS
N_OP_atomcellN(tos, n)
  register int tos;
  int n;
  {

    if ((tos & 0xffff0000) != 0) ERROR_EXIT(tos);

   tos = (tos << 1);

    switch(n)
      {
	case D_DEFSHI :	return(DEFS_OFFSET + tos);
	case D_VALSHI :	return(VALS_OFFSET + tos);
	case D_PLISHI :	return(PLIS_OFFSET + tos);
	case D_PNHI :	return(PNP_OFFSET + tos);
	default :	ERROR_EXIT(tos);
      }
}

#else
N_OP_atomcellN(tos, n)
  register int tos;
  int n;
  {

   if ((tos & 0xffff0000) == 0){ /* XeroxLisp traditional symbol */
     tos = (tos << 1);
     switch(n)
      {
        case D_DEFSHI :	return(DEFS_OFFSET + tos);
	case D_VALSHI :	return(VALS_OFFSET + tos);
	case D_PLISHI :	return(PLIS_OFFSET + tos);
	case D_PNHI :	return(PNP_OFFSET + tos);
	default :	ERROR_EXIT(tos);
      }
   }
   else{			/* New Symbol */
     switch(n)
      {
        case D_DEFSHI :	return(NEWATOM_DEFN_OFFSET + tos);
	case D_VALSHI :	return(NEWATOM_VALUE_OFFSET + tos);
	case D_PLISHI :	return(NEWATOM_PLIST_OFFSET + tos);
	case D_PNHI :	return(NEWATOM_PNAME_OFFSET + tos);
	default :	ERROR_EXIT(tos);
      }
   }
 }
   
#endif
