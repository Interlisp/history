/* @(#) LispCursorDef.h Version 1.2 (4/19/90). copyright Venue & Fuji Xerox  */
/*
*
*
* Copyright (C) 1988 by Fuji Xerox co.,Ltd. All rights reserved.
*
*		Author: Mitsunori Matsuda
*		Date  : August 29, 1988
*/

typedef struct {
	short cubitsprepixel;
	char *cuimage;
	char *cumask;
	short cuhotspotx;
	short cuhotspoty;
	short cudata;
} LISP_CURSOR;
