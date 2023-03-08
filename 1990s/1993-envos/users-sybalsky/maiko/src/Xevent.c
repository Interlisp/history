/* @(#) Xevent.c Version 1.4 (2/8/93). copyright venue & Fuji Xerox  */
static char *id = "@(#) Xevent.c	1.4 2/8/93	(venue & Fuji Xerox)";


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

#include <X11/Xlib.h>
#include <X11/Xutil.h>

#include "XVersion.h"
#include "MyWindow.h"
#include "lispXbitblt.h"

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
/*	Handle an "Expose" event from X.				*/
/*									*/
/************************************************************************/

lisp_Xexpose( event, window )
  XExposeEvent *event;
  MyWindow *window;
  {
#ifdef TRACE
    printf( "TRACE:	lisp_Xexpose()\n" );
    printf( "lisp_Xexpose: Exposed region x=%d, y=%d, w=%d, h=%d\n"
    	, event->x, event->y, event->width, event->height );
#endif
    /* Repair Display Window */
    Xbitblt ( event->x+ScreenRegion.left_x
	    , event->y+ScreenRegion.top_y
	    , event->width
	    , event->height );

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
#ifdef TRACE
    printf( "TRACE:Rase_LispWindow()\n" );
#endif

    if( !Backing_Store )
      {
	XRaiseWindow( event->display, Lisp_Window.win );
	XFlush( event->display );
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

    int old_gravity, win;
#ifdef TRACE
    printf( "TRACE: Set_BitGravity()\" );
#endif

    old_gravity = Bit_Gravity;

    if( (event->type == ButtonPress) 
	 && ((event->button & 0xFF) == Button1) ) {
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

#ifdef TRACE
    printf( "TRACE: lisp_Xconfigure()\n" );
#endif

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
	if( flag ) XResizeWindow( event->display, window->win
				  , window->width, window->height );

	Resize_Subwindows(event->display);

      } /* end if */

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
#ifdef TRACE
    printf( "TRACE: mouse_Xcrossed()\n" );
#endif

    if( event->type == EnterNotify )
      {
	Mouse_Included = TRUE;
      }

    if( event->type == LeaveNotify )
      {
	Mouse_Included = FALSE;
      }
  } /* end mouse_Xcrossed */
