/* @(#) XInit.c Version 1.6 (2/8/93). copyright venue & Fuji Xerox  */
static char *id = "@(#) XInit.c	1.6 2/8/93	(venue & Fuji Xerox)";




/************************************************************************/
/*									*/
/*	Copyright 1989, 1990 Venue, Fuji Xerox Co., Ltd, Xerox Corp.	*/
/*									*/
/*	This file is work-product resulting from the Xerox/Venue	*/
/*	Agreement dated 18-August-1989 for support of Medley.		*/
/*									*/
/************************************************************************/

/*
*
*
* Copyright (C) 1988 by Fuji Xerox co.,Ltd. All rights reserved.
*
*		Author: Mitsunori Matsuda
*		Date  : August 10, 1988
*/

#include <stdio.h>
#include <X11/Xlib.h>
#define FALSE 0 
#define TRUE  !FALSE

extern int Lisp_Xinitialized;

init_Xdisplay(display)
     Display *display;
{
  Create_LispWindow(display);	/* Make the main window */
  Lisp_Xinitialized = TRUE;
} /* end init_Xdisplay() */
