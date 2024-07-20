/* @(#) XKeyboard.c Version 1.2 (4/20/90). copyright venue & Fuji Xerox  */
static char *id = "@(#) XKeyboard.c	1.2 4/20/90	(venue & Fuji Xerox)";




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
*		Date  : August 18, 1988
*
*/

#include <stdio.h>

#include <X11/Xlib.h>
#include <X11/Xutil.h>

#include "lispemul.h"

#include "XVersion.h"
#include "MyWindow.h"

extern Display *Xdisplay;
extern MyWindow Lisp_Window
	      , Display_Window;

enable_Xkeyboard()
{
#ifdef TRACE
	printf( "TRACE: enable_Xkeyboard()\n" );
#endif
	Lisp_Window.event_mask    |= KeyPressMask
				 	|KeyReleaseMask;
	Display_Window.event_mask |= ButtonPressMask
				 	|ButtonReleaseMask
				  	|PointerMotionMask;
	XSelectInput( Xdisplay, Lisp_Window.win   , Lisp_Window.event_mask );
	XSelectInput( Xdisplay, Display_Window.win, Display_Window.event_mask );
	XFlush( Xdisplay );
}

disable_Xkeyboard()
{
#ifdef TRACE
	printf( "TRACE: disable_Xkeyboard()\n" );
#endif
	Lisp_Window.event_mask 	  &= ~( KeyPressMask
				  	|KeyReleaseMask );
	Display_Window.event_mask &= ~( ButtonPressMask
			     		|ButtonReleaseMask
			     		|PointerMotionMask );
	XSelectInput( Xdisplay, Lisp_Window.win   , Lisp_Window.event_mask );
	XSelectInput( Xdisplay, Display_Window.win, Display_Window.event_mask );
	XFlush( Xdisplay );
}

beep_Xkeyboard()
{
#ifdef TRACE
	printf( "TRACE: beep_Xkeyboard()\n" );
#endif

		XBell( Xdisplay, (int) 50 );
		XFlush( Xdisplay );

} /* end beep_Xkeyboard */