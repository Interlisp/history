/* @(#) picture.h Version 1.2 (4/21/92). copyright Venue & Fuji Xerox  */
/*  (c) CopyRight Fuji Xerox 1989  Maiko Project */
/* FILE: picture.h REL.1 SCCSID:1.1 Date: 6/13/91 10:49:26 */
/* SCCS file: /tmp_mnt/net/vogue/project1/emul/SCCS/s.picture.h  */

/*
*
*
* Copyright (C) 1990 by Fuji Xerox co.,Ltd.. All rights reserved.
*
*               Author: Mitsunori Matsuda
*               Date  : May 14, 1991
*/

typedef struct _picture{
	DLword	width;
	DLword	height;
	DLword	bitsperpixel;
	DLword	nil;
	unsigned int storage;
	LispPTR	userdata;
} LispPicture;
