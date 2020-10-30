h34185s 00003/00003/00074d D 2.7 92/04/21 17:11:05 sybalsky 11 10c shortening file names for DOS \nes 00000/00000/00077d D 2.6 90/04/20 01:29:15 sybalsky 10 9c e names, bulk change.es 00000/00000/00077d D 2.5 90/03/02 21:43:30 sybalsky 9 8c 386 checks, commentses 00034/00030/00043d D 2.4 90/03/02 11:17:01 sybalsky 8 7c check for 386, new SCCS header.es 00009/00009/00064d D 2.3 89/01/09 16:33:59 shih 7 6c minor spellinges 00000/00061/00073d D 2.2 88/05/25 17:50:48 krivacic 6 5c removed obsolete fnes 00000/00000/00134d D 2.1 88/05/17 09:23:55 hayata 5 4c Version up to 2.1es 00066/00006/00068d D 1.4 88/03/29 18:50:43 krivacic 4 3c New Interfaceses 00002/00002/00072d D 1.3 88/03/13 14:46:24 hayata 3 2c Add SCCS key id (%Z%)es 00003/00003/00071d D 1.2 88/03/03 11:34:47 krivacic 2 1c Removed global CurrentFX to use CURRENTFX = PVAR - FRAMESIZEes 00074/00000/00000d D 1.1 88/02/24 16:56:41 hayata 1 0c date and time created 88/02/24 16:56:41 by hayataeuUtTI 1D 3/* This is G-file %M% Version %I% (%G%). copyright Xerox & Fuji Xerox  */static char *id = "%M%	%I% %G%";E 3I 3D 7/* This is G-file %Z% %M% Version %I% (%G%). copyright Xerox & Fuji Xerox  */E 7I 7/* %Z% %M% Version %I% (%G%). copyright envos & Fuji Xerox  */E 7static char *id = "%Z% %M%	%I% %G%";E 3D 8/* *	Copyright (C) 1987 by Fuji Xerox Co., Ltd. All rights reserved. *D 7 *	Auther :  Takeshi ShimizuE 7I 7 *	Author :  Takeshi ShimizuE 7 * *//***********************************************************************/E 8I 4I 8/************************************************************************//*									*//*	Copyright 1989, 1990 Venue, Fuji Xerox Co., Ltd, Xerox Corp.	*//*									*//*	This file is work-product resulting from the Xerox/Venue	*//*	Agreement dated 18-August-1989 for support of Medley.		*//*									*//************************************************************************/E 8#include "lispemul.h"#include "lispmap.h"D 11#include "emulglobal.h"E 11I 11#include "emlglob.h"E 11#include "stack.h"D 11#include "lispglobal.h"#include "address68k.h"E 11I 11#include "lspglob.h"#include "adr68k.h"E 11D 6/***********************************************************************/E 4/* 		File Name :	findkey.c		Desc	:	  				Date :		Aug. 10, 1987 				Edited by :	Takeshi Shimizu				Changed :	Oct. 23 1987(Take)				Changed :	Nov. 04 1987(Hayata) 		Including :	OP_findkey							*//**********************************************************************/D 4#include "lispemul.h"#include "lispmap.h"#include "emulglobal.h"#include "stack.h"#include "lispglobal.h"#include "address68k.h"E 4OP_findkey(){ LispPTR *ptr ; DLword *find_end ; DLword arg_nth ;#ifdef TRACE	printPC();	printf("TRACE : OP_findkey \n");#endifD 2if(CurrentFX->alink & 1)E 2I 2if(CURRENTFX->alink & 1)E 2 { /* slow case */D 2	find_end = (DLword *)Addr68k_from_LADDR(STK_OFFSET | (CurrentFX->blink-4)) ;E 2I 2	find_end = (DLword *)Addr68k_from_LADDR(STK_OFFSET | (CURRENTFX->blink-4)) ;E 2 } else { /*  Fast cae */D 2	find_end = ((DLword *)CurrentFX) -2-4;E 2I 2	find_end = ((DLword *)CURRENTFX) -2-4;E 2 } arg_nth =Get_BYTE(PC+1) +1 ; for ( ptr =(LispPTR *) (IVar + ((Get_BYTE(PC+1) * 2) - 2));	  (unsigned)find_end >= (unsigned) ptr ; ptr += 2, arg_nth +=2)	/** FIXED : '<' to '>=' by take 23-Oct-87  **/	/** FIXED : 'ptr+=4,' to 'ptr+=2,' by hayata 04-Nov-87		Andy Daniels pointed out this bug. Thank you. **/ {	if (*ptr == TopOfStack)	{ /* KEY founded */		TopOfStack = S_POSITIVE | arg_nth ;		PC += 2 ;		return;	}  } /* for end *//* No matched */ TopOfStack = NIL; PC += 2 ; return;}/* end OP_findkey() */I 4E 6/***********************************************************************//*D 7 		File Name :	findkey.cE 7I 7		File Name :	findkey.cE 7D 7		Desc	:	  				Date :		Mar. 29 88 				Edited by :	Bob KrivacicE 7I 7		Desc	:				Date :		Mar. 29 88				Edited by :	Bob KrivacicE 7		Including :	N_OP_findkeyD 7							E 7I 7E 7*//**********************************************************************/LispPTR N_OP_findkey(tos, byte)D 8	register LispPTR tos;	register int byte;{ LispPTR *ptr ; DLword *find_end ; DLword arg_nth ;E 8I 8  register LispPTR tos;  register int byte;  {    LispPTR *ptr ;    DLword *find_end ;   DLword arg_nth ;E 8#ifdef TRACED 8	printPC();	printf("TRACE : N_OP_findkey \n");E 8I 8    printPC();    printf("TRACE : N_OP_findkey \n");E 8#endifD 8if(CURRENTFX->alink & 1) { /* slow case */E 8I 8    if(CURRENTFX->alink & 1)      { /* slow case */E 8	find_end = (DLword *)Addr68k_from_LADDR(STK_OFFSET | (CURRENTFX->blink-4)) ;D 8 } else { /*  Fast cae */E 8I 8      }    else      { /*  Fast cae */E 8	find_end = ((DLword *)CURRENTFX) -2-4;D 8 }E 8I 8      }E 8D 8 arg_nth =byte + 1 ;E 8I 8    arg_nth =byte + 1 ;E 8D 8 for ( ptr =(LispPTR *) (IVar + ((byte * 2) - 2));E 8I 8    for ( ptr =(LispPTR *) (IVar + ((byte * 2) - 2));E 8	  (unsigned)find_end >= (unsigned) ptr ; ptr += 2, arg_nth +=2)D 8 {E 8I 8      {E 8	if (*ptr == tos)D 8	{ /* KEY founded */		return(S_POSITIVE | arg_nth);	}  } /* for end */E 8I 8	  { /* KEY founded */	    return(S_POSITIVE | arg_nth);	  }      } /* for end */E 8/* No matched */D 8 return(NIL_PTR);E 8I 8    return(NIL_PTR);E 8D 8}/* end N_OP_findkey() */E 8I 8  }/* end N_OP_findkey() */E 8E 4E 1