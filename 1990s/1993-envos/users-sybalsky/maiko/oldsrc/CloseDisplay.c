/* %Z% %M% Version %I% (%G%). copyright venue & Fuji Xerox  */
static char *id = "%Z% %M%	%I% %G%	(venue & Fuji Xerox)";
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
extern MyWindow Lisp_Window
	      , Display_Window
	      , Vert_Scroll
	      , Horiz_Scroll
	      , Grav_Window[];
extern int Lisp_Xinitialized;

lisp_Xexit()
{
#ifdef TRACE
	printf( "TRACE: lisp_Xexit()\n" );
#endif

	XDestroySubwindows( Xdisplay, Lisp_Window.win );
	XDestroyWindow( Xdisplay, Lisp_Window.win );
	XXClose( Xdisplay );
	
	Lisp_Xinitialized = FALSE;
} /* end lisp_Xexit */

Xevent_before_raid()
{
#ifdef TRACE
	printf( "TRACE: Xevent_before_raid()\n" );
#endif

	XSelectInput( Xdisplay, Lisp_Window.win,    NoEventMask );
	XSelectInput( Xdisplay, Display_Window.win, NoEventMask );
	XSelectInput( Xdisplay, Vert_Scroll.win,    NoEventMask );
	XSelectInput( Xdisplay, Horiz_Scroll.win,  NoEventMask );
	{ int i;
	  for( i ; i<4 ; i++ ) {
		XSelectInput( Xdisplay
				, Grav_Window[i].win
				,  NoEventMask );
	  }
	}
	XFlush( Xdisplay );

} /* end Xevent_before_raid */

Xevent_after_raid()
{
#ifdef TRACE
	printf( "TRACE: Xevent_after_raid()\n" );
#endif

	XSelectInput( Xdisplay, Lisp_Window.win,    Lisp_Window.event_mask );
	XSelectInput( Xdisplay, Display_Window.win, Display_Window.event_mask );
	XSelectInput( Xdisplay, Vert_Scroll.win,    Vert_Scroll.event_mask );
	XSelectInput( Xdisplay, Horiz_Scroll.win,  Horiz_Scroll.event_mask );
	{ int i;
	  for( i ; i<4 ; i++ ) {
	    XSelectInput( Xdisplay
			, Grav_Window[i].win
			, Grav_Window[i].event_mask );
	  }
	}
	refresh_Xscreen();
	XFlush( Xdisplay );

} /* end Xevent_before_raid */