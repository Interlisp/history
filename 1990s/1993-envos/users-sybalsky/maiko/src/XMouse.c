/* @(#) XMouse.c Version 1.5 (2/8/93). copyright venue & Fuji Xerox  */
static char *id = "@(#) XMouse.c	1.5 2/8/93	(venue & Fuji Xerox)";




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
*		Date  : August 12, 1988
*/

#include <stdio.h>

#include <X11/Xlib.h>
#include <X11/Xutil.h>

#include "XVersion.h"
#include "MyWindow.h"

extern Display *Xdisplay;
extern MyWindow Display_Window;
extern DisplayArea ScreenRegion;

set_Xmouseposition( x, y )
int x
  , y;
{
	int dest_x
	  , dest_y;

#ifdef TRACE
	printf( "TRACE: set_Xmouseposition(%d,%d)\n", x, y );
#endif

	dest_x = (x&0xFFFF) - ScreenRegion.left_x;
	dest_y = (y&0xFFFF) - ScreenRegion.top_y;

	if( (dest_x>=0) && (dest_x<=Display_Window.width)
	 && (dest_y>=0) && (dest_y<=Display_Window.height) ) {
		XLOCK;
		XWarpPointer( Xdisplay, NULL, Display_Window.win
				, NULL, NULL
				, NULL, NULL
				, dest_x, dest_y );
		XFlush( Xdisplay );
		XUNLOCK;
	}
} /* end set_Xmouseposition */
