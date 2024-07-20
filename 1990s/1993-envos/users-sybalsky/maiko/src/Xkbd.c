/* @(#) Xkbd.c Version 1.5 (2/8/93). copyright venue & Fuji Xerox  */
static char *id = "@(#) Xkbd.c	1.5 2/8/93	(venue & Fuji Xerox)";





/************************************************************************/
/*									*/
/*	(C) Copyright 1989-92 Venue. All Rights Reserved.		*/
/*	Manufactured in the United States of America.			*/
/*									*/
/*	The contents of this file are proprietary information 		*/
/*	belonging to Venue, and are provided to you under license.	*/
/*	They may not be further distributed or disclosed to third	*/
/*	parties without the specific permission of Venue.		*/
/*									*/
/************************************************************************/
/*
*
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

extern MyWindow Lisp_Window
	      , Display_Window;

enable_Xkeyboard(display)
     Display *display;
{
#ifdef TRACE
	printf( "TRACE: enable_Xkeyboard()\n" );
#endif
	Lisp_Window.event_mask    |= KeyPressMask
				 	|KeyReleaseMask;
	Display_Window.event_mask |= ButtonPressMask
				 	|ButtonReleaseMask
				  	|PointerMotionMask;
	XLOCK;
	XSelectInput( display, Lisp_Window.win   , Lisp_Window.event_mask );
	XSelectInput( display, Display_Window.win, Display_Window.event_mask );
	XFlush( display );
	XUNLOCK;
}



disable_Xkeyboard(display)
     Display *display;
{
#ifdef TRACE
	printf( "TRACE: disable_Xkeyboard()\n" );
#endif
	Lisp_Window.event_mask 	  &= ~( KeyPressMask
				  	|KeyReleaseMask );
	Display_Window.event_mask &= ~( ButtonPressMask
			     		|ButtonReleaseMask
			     		|PointerMotionMask );
	XLOCK;
	XSelectInput( display, Lisp_Window.win   , Lisp_Window.event_mask );
	XSelectInput( display, Display_Window.win, Display_Window.event_mask );
	XFlush( display );
	XUNLOCK;
}

beep_Xkeyboard(display)
     Display *display;
{
#ifdef TRACE
	printf( "TRACE: beep_Xkeyboard()\n" );
#endif

		XLOCK;
		XBell( display, (int) 50 );
		XFlush( display );
		XUNLOCK;


} /* end beep_Xkeyboard */