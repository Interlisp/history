/* @(#) Xcolor.c Version 1.4 (2/8/93). copyright venue & Fuji Xerox  */
static char *id = "@(#) Xcolor.c	1.4 2/8/93	(venue & Fuji Xerox)";
/*
*
*
* Copyright (C) 1988 by Fuji Xerox co.,Ltd. All rights reserved.
*
*		Author: Mitsunori Matsuda
*		Date  : August 18, 1988
*/

#include <stdio.h>

#include <X11/Xlib.h>
#include <X11/Xutil.h>

#include "XVersion.h"
#include "MyWindow.h"

#define FALSE 0
#define TRUE  !FALSE

extern Display *Xdisplay;
extern XGCValues gcv;
extern GC cursor_source_gc
	, CopyInvert_GC
	, Copy_GC;
extern MyWindow Display_Window;
extern int Video_Inverted;

lisp_Xvideocolor( flag )
int flag;
{

	/* if(flag XOR Video_Inverted) */
	if( ( flag && !Video_Inverted)
	 || (!flag &&  Video_Inverted) ) {

		/* Inveted copy on Display Window */
		XLOCK;
		XCopyArea( Xdisplay  
				, Display_Window.win
				, Display_Window.win
				, CopyInvert_GC
				, 0, 0
				, Display_Window.width
				, Display_Window.height
				, 0, 0 );

		Display_Window.gc = flag ? &CopyInvert_GC
					 : &Copy_GC;
		/* Cursor */
		gcv.function = flag ? GXcopyInverted
				    : GXcopy;
		XChangeGC( Xdisplay, cursor_source_gc
					, GCFunction
					, &gcv );
		Set_XCursor( 0, 0 );

		XFlush(Xdisplay);
		XUNLOCK;
		
		Video_Inverted = flag;

	} /* end if */

} /* end lisp_Xvideocolor */