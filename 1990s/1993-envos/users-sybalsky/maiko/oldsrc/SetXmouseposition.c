/* %Z% %M% Version %I% (%G%). copyright venue & Fuji Xerox  */
static char *id = "%Z% %M%	%I% %G%	(venue & Fuji Xerox)";
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
		XWarpPointer( Xdisplay, NULL, Display_Window.win
				, NULL, NULL
				, NULL, NULL
				, dest_x, dest_y );
		XFlush( Xdisplay );
	}
} /* end set_Xmouseposition */