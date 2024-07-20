static char *id = "@(#) VideoColor.c 1.1  2/7/91 19:00:47 ";
/*  (c) CopyRight Fuji Xerox 1991  Maiko for VISION Project */
/* FILE: VideoColor.c REL.1 SCCSID:1.1  */
/* SCCS file: /medley/project1/emul/SCCS/s.VideoColor.c  */

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

		Video_Inverted = flag;

	} /* end if */

} /* end lisp_Xvideocolor */