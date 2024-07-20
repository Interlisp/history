/* @(#) XEvent.c Version 1.11 (2/8/93). copyright venue & Fuji Xerox  */
static char *id = "@(#) XEvent.c	1.11 2/8/93	(venue & Fuji Xerox)";




/************************************************************************/
/*									*/
/*	Copyright 1989, 1990, 1991 Venue.				*/
/*									*/
/*	This file was work-product resulting from the Xerox/Venue	*/
/*	Agreement dated 18-August-1989 for support of Medley.		*/
/*									*/
/************************************************************************/


#include <stdio.h>

#include <X11/Xlib.h>
#include <X11/Xutil.h>

#include "XVersion.h"
#include "MyWindow.h"
#include "Xbitblt.h"
#include "dbprint.h"

#define FALSE 0
#define TRUE  !FALSE

int Mouse_Included = FALSE;

extern XImage XScreenBitmap;
extern XSetWindowAttributes Lisp_SetWinAttributes;
extern DisplayArea ScreenRegion;
extern MyWindow Display_Window
	      , Lisp_Window
	      , Grav_Window[];
extern int Bit_Gravity;
extern int Backing_Store;



/************************************************************************/
/*									*/
/*			l i s p _ X e x p o s e				*/
/*									*/
/*	Handle X "Expose" Events, when lisp window gets uncovered.	*/
/*									*/
/************************************************************************/

lisp_Xexpose( event, window )
  XExposeEvent *event;
  MyWindow *window;
  {
    TPRINT(( "TRACE:	lisp_Xexpose()\n" ));
    TPRINT(( "lisp_Xexpose: Exposed region x=%d, y=%d, w=%d, h=%d\n"
		, event->x, event->y, event->width, event->height ));

    /* Repair Display Window */
    XLOCK;
	Xbitblt ( event->display
	     , event->x+ScreenRegion.left_x
	    , event->y+ScreenRegion.top_y
	    , event->width
	    , event->height );
    XFlush(event->display);
    XUNLOCK;

  } /* end lisp_Xexpose */



/************************************************************************/
/*									*/
/*									*/
/*									*/
/*									*/
/*									*/
/************************************************************************/

Raise_LispWindow( event, window )
  XCrossingEvent *event;
  MyWindow *window;
  {
    TPRINT(( "TRACE:Raise_LispWindow()\n" ));

    if( !Backing_Store )
      {
	XLOCK;
	XRaiseWindow( event->display, Lisp_Window.win );
	XFlush( event->display );
	XUNLOCK;
      }

  } /* end Raise_LispWindow */



/************************************************************************/
/*									*/
/*									*/
/*									*/
/*									*/
/*									*/
/************************************************************************/

#define North_West 0
#define North_East 1
#define South_West 2
#define South_East 3

extern Pixmap GravityOn_Pixmap
            , GravityOff_Pixmap;

Set_BitGravity( event, window )
  XButtonEvent *event;
  MyWindow  *window;
  {

    int old_gravity
	  , win;

    TPRINT(( "TRACE: Set_BitGravity()\n" ));

    old_gravity = Bit_Gravity;

    if( (event->type == ButtonPress) 
	 && ((event->button & 0xFF) == Button1) )
      {
	if( window->win == Grav_Window[0].win )      
	  Bit_Gravity = NorthWestGravity;
	else if( window->win == Grav_Window[1].win ) 
	  Bit_Gravity = NorthEastGravity;
	else if( window->win == Grav_Window[2].win ) 
	  Bit_Gravity = SouthWestGravity;
	else if( window->win == Grav_Window[3].win ) 
	  Bit_Gravity = SouthEastGravity;
      } /* end if(button) */

    if( Bit_Gravity != old_gravity )
      { /* gravity changed */

	if( old_gravity == NorthWestGravity ) win = North_West;
	if( old_gravity == NorthEastGravity ) win = North_East;
	if( old_gravity == SouthWestGravity ) win = South_West;
	if( old_gravity == SouthEastGravity ) win = South_East;

	/* Change Background Pixmap of Gravity Window */
	XLOCK;
	XSetWindowBackgroundPixmap( event->display
				, Grav_Window[win].win
				, GravityOff_Pixmap );
	XClearWindow( event->display, Grav_Window[win].win );

	XSetWindowBackgroundPixmap( event->display
				, window->win 
				, GravityOn_Pixmap );
	XClearWindow( event->display, window->win );

	/* Display BitGravity */
	Lisp_SetWinAttributes.bit_gravity = Bit_Gravity;
	XChangeWindowAttributes( event->display
				, Display_Window.win
				, CWBitGravity
				, &Lisp_SetWinAttributes );

	/* Lisp_Window Window Gravity */
	/*
	Lisp_SetWinAttributes.win_gravity = Bit_Gravity;
	XChangeWindowAttributes( event->display
				, Lisp_Window.win
				, CWWinGravity
				, &Lisp_SetWinAttributes );
	*/
	XFlush( event->display );
	XUNLOCK;
      } /* end if */

  } /* end Set_BitGravity */



/************************************************************************/
/*									*/
/*									*/
/*									*/
/*									*/
/*									*/
/************************************************************************/

extern int LispWindow_MaxWidth
	    , LispWindow_MaxHeight;

lisp_Xconfigure( event, window )
  XConfigureEvent *event;
  MyWindow *window;
  {
    int flag;

    TPRINT(( "TRACE: lisp_Xconfigure()\n" ));

	XLOCK;

    window->x = event->x;
    window->y = event->y;

    if( (event->width  != window->width)
	 || (event->height != window->height) )
      { /* Lisp Window Resized */

	window->width  = event->width;
	window->height = event->height;
	
	flag = FALSE;

	if( window->width > LispWindow_MaxWidth )
	  {
	    window->width  = LispWindow_MaxWidth;
	    flag = TRUE;
	  }

	if( window->height > LispWindow_MaxHeight )
	  {
	    window->height = LispWindow_MaxHeight;
	    flag = TRUE;
	  }

	if( flag )
	  { /* need to display new parts of the window */
	    XResizeWindow( event->display
			 , window->win
			 , window->width 
			 , window->height );
	  }

	Resize_Subwindows(event->display);

      } /* end if */
    XFlush(event->display);
	XUNLOCK;

  } /* end lisp_Xconfigure */



/************************************************************************/
/*									*/
/*									*/
/*									*/
/*									*/
/*									*/
/************************************************************************/

mouse_Xcrossed( event, window )
  XCrossingEvent *event;
  MyWindow *window;
  {
    TPRINT(( "TRACE: mouse_Xcrossed()\n" ));

    if( event->type == EnterNotify )
      {
	Mouse_Included = TRUE;
      }

    if( event->type == LeaveNotify )
      {
	Mouse_Included = FALSE;
      }
  } /* end mouse_Xcrossed */