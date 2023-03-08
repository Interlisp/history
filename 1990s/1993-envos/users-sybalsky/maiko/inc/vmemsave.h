/* @(#) vmemsave.h Version 2.4 (4/21/92). copyright Venue & Fuji Xerox  */

/*
 *	Copyright (C) 1987 by Fuji Xerox Co., Ltd. All rights reserved.
 *
 *	Author	:	Hirofumi Komatsubara
 */



/************************************************************************/
/*									*/
/*	Copyright 1989, 1990 Venue, Fuji Xerox Co., Ltd, Xerox Corp.	*/
/*									*/
/*	This file is work-product resulting from the Xerox/Venue	*/
/*	Agreement dated 18-August-1989 for support of Medley.		*/
/*									*/
/************************************************************************/



/*
	File Name : vmemsave.h
	DEfinition for vmemsave
*/

#define	FP_IFPAGE  512			/* IFPAGE address in sysoutfile by Byte */
#define	DOMINOPAGES  301		/* skip dominopages  in  fptovp */
#define	SKIPPAGES  301			/* save first filepage  */
#define	SKIP_DOMINOPAGES  153600	/* Byte size in sysoutfile for dominocode */
#define	SAVE_IFPAGE	223		/* Virtual address for IFPAGES's buffer page. This value is \EMUSWAPBUFFERS in lisp. */
