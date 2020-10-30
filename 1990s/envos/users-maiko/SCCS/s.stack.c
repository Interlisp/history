h07721s 00000/00000/00097d D 2.1 88/05/17 09:26:41 hayata 4 3c Version up to 2.1es 00002/00002/00095d D 1.3 88/03/13 15:06:49 hayata 3 2c Add SCCS key id (%Z%)es 00004/00004/00093d D 1.2 88/03/03 11:38:47 krivacic 2 1c Removed global CurrentFX to use CURRENTFX = PVAR - FRAMESIZEes 00097/00000/00000d D 1.1 88/02/24 16:58:28 hayata 1 0c date and time created 88/02/24 16:58:28 by hayataeuUtTI 1D 3/* This is G-file %M% Version %I% (%G%). copyright Xerox & Fuji Xerox  */static char *id = "%M%	%I% %G%";E 3I 3/* This is G-file %Z% %M% Version %I% (%G%). copyright Xerox & Fuji Xerox  */static char *id = "%Z% %M%	%I% %G%";E 3/* *	Copyright (C) 1987 by Fuji Xerox Co., Ltd. All rights reserved. * *	Auther :  Takeshi Shimizu,Naoyuki Mitani * *//**********************************************************************//* 		File Name :	stack.c		Desc	:	stack management  					Date :		Mar 06, 1987 					Edited by :	Naoyuki Mitani 		Including :	OP_myalink				OP_myargcount				*//**********************************************************************/#include "lispemul.h"#include "stack.h"#include "lispmap.h"#include "emulglobal.h"#include "lispglobal.h"/**********************************************************************//*		Func name :	OP_myalink				Get the word offset of the FX of the caller				from the top of StackSpace . And set it to 				TOS as a pointer to integer .				It ignore slowp.					Date :		Apr 13, 1987					Edited by :	Naoyuki Mitani					Change :	Jun. 2 1987 take*//**********************************************************************/OP_myalink(){#ifdef TRACE	printPC();	printf("TRACE: OP_myalink()\n");#endif PushCStack;D 2 TopOfStack = (((CurrentFX -> alink) & 0xfffe)-FRAMESIZE) | S_POSITIVE;E 2I 2 TopOfStack = ((( CURRENTFX-> alink) & 0xfffe)-FRAMESIZE) | S_POSITIVE;E 2	/* Set the alink offset to TOS as a pointer to integer */ PC++; if (StackCheck)	StackOverflow;}/* end OP_myalink *//**********************************************************************//*		Func name :	OP_myargcount				Get the number of arguments of current stack 				frame . And set it to TOS as a pointer to 				integer .					Date :		Apr 14, 1987					Edited by :	Naoyuki Mitani					Changed by:	Naoyuki Mitani(Mar-06)	*//**********************************************************************/OP_myargcount(){ DLword  arg_num;		/* Number of arguments */ #ifdef TRACE	printPC();	printf("TRACE: OP_myargcount()\n");#endif PushCStack;D 2 if ((CurrentFX -> alink & 1) == 0)	arg_num =((int)((DLword *)CurrentFX - 2) - (int)IVar) >> 2;E 2I 2 if (( CURRENTFX-> alink & 1) == 0)	arg_num =((int)((DLword *)CURRENTFX - 2) - (int)IVar) >> 2;E 2					/* FAST case */ elseD 2	arg_num =((int)(Stackspace + CurrentFX->blink) - (int)IVar) >> 2;E 2I 2	arg_num =((int)(Stackspace + CURRENTFX->blink) - (int)IVar) >> 2;E 2					/* SLOWP case */ TopOfStack = S_POSITIVE | arg_num; PC++; if (StackCheck)	StackOverflow;}/* end OP_myargcount */E 1