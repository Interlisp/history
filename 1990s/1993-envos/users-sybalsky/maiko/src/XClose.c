/* @(#) XClose.c Version 1.6 (11/25/92). copyright venue & Fuji Xerox  */
static char *id = "@(#) XClose.c	1.6 11/25/92	(venue & Fuji Xerox)";




/************************************************************************/
/*									*/
/*	(C) Copyright 1989, 1990, 1991 Venue. All Rights Reserved.	*/
/*	Manufactured in the United States of America.			*/
/*									*/
/*	The contents of this file are proprietary information 		*/
/*	belonging to Venue, and are provided to you under license.	*/
/*	They may not be further distributed or disclosed to third	*/
/*	parties without the specific permission of Venue.		*/
/*									*/
/************************************************************************/




#include <stdio.h>

#ifdef ISC
#include <sys/bsdtypes.h>
#include <stropts.h>
#include <sys/ioctl.h>
#endif /* ISC */


#include <X11/Xlib.h>
#include <X11/Xutil.h>

#include "XVersion.h"
#include "MyWindow.h"
#include "dbprint.h"

#define FALSE 0
#define TRUE  !FALSE

extern Display *Xdisplay;
extern MyWindow Lisp_Window
	      , Display_Window
	      , Vert_Scroll
	      , Horiz_Scroll
	      , Grav_Window[];
extern int Lisp_Xinitialized;
extern int Xfd;



/************************************************************************/
/*									*/
/*			l i s p _ X e x i t				*/
/*									*/
/*	Turn off the X window we've been using for display.		*/
/*									*/
/************************************************************************/

lisp_Xexit()
  {
    TPRINT(( "TRACE: lisp_Xexit()\n" ));

#ifdef ISC
    ioctl(Xfd, I_SETSIG, 0); /* so no interrupts happen during */
#endif ISC			/* the following code.... */

    XDestroySubwindows( Xdisplay, Lisp_Window.win );
    XDestroyWindow( Xdisplay, Lisp_Window.win );
    XCloseDisplay( Xdisplay );
	
    Lisp_Xinitialized = FALSE;
  } /* end lisp_Xexit */



/************************************************************************/
/*									*/
/*		    X e v e n t _ b e f o r e _ r a i d			*/
/*									*/
/*	Called before Medley enters URAID, to turn off events in	*/
/*	the X windows we use for Medley's display.			*/
/*									*/
/************************************************************************/

Xevent_before_raid()
  {
    TPRINT(( "TRACE: Xevent_before_raid()\n" ));

    XSelectInput( Xdisplay, Lisp_Window.win,    NoEventMask );
    XSelectInput( Xdisplay, Display_Window.win, NoEventMask );
    XSelectInput( Xdisplay, Vert_Scroll.win,    NoEventMask );
    XSelectInput( Xdisplay, Horiz_Scroll.win,  NoEventMask );
      { int i;
	for( i=0 ; i<4 ; i++ )
	  {
	    XSelectInput( Xdisplay, Grav_Window[i].win,  NoEventMask );
	  }
      }
    XFlush( Xdisplay );

  } /* end Xevent_before_raid */



/************************************************************************/
/*									*/
/*		    X e v e n t _ a f t e r _ r a i d			*/
/*									*/
/*	Called after Medley returns from URAID, to re-enable events	*/
/*	from the X server in the windows we use for the display.	*/
/*									*/
/************************************************************************/

Xevent_after_raid()
  {
    TPRINT(( "TRACE: Xevent_after_raid()\n" ));

    XSelectInput( Xdisplay, Lisp_Window.win,    Lisp_Window.event_mask );
    XSelectInput( Xdisplay, Display_Window.win, Display_Window.event_mask );
    XSelectInput( Xdisplay, Vert_Scroll.win,    Vert_Scroll.event_mask );
    XSelectInput( Xdisplay, Horiz_Scroll.win,  Horiz_Scroll.event_mask );
      { int i;
	for( i=0 ; i<4 ; i++ )
	  {
	    XSelectInput( Xdisplay, Grav_Window[i].win
			, Grav_Window[i].event_mask );
	  }
      }
    refresh_Xscreen( Xdisplay );
    XFlush( Xdisplay );

  } /* end Xevent_before_raid */
