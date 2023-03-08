/* @(#) EventHandler.c Version 1.2 (4/16/91). copyright venue & Fuji Xerox  */
static char *id = "@(#) EventHandler.c	1.2 4/16/91	(venue & Fuji Xerox)";


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

extern Display *Xdisplay;
extern XImage XScreenBitmap;
extern XSetWindowAttributes Lisp_SetWinAttributes;
extern DisplayArea ScreenRegion;
extern MyWindow Display_Window
	      , Lisp_Window
	      , Grav_Window[];
extern int Bit_Gravity;
extern int Auto_Repeat;
extern int Def_Auto_Repeat;
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
	XRaiseWindow( Xdisplay, Lisp_Window.win );
	XFlush( Xdisplay );
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
	XSetWindowBackgroundPixmap( Xdisplay
				, Grav_Window[win].win
				, GravityOff_Pixmap );
	XClearWindow( Xdisplay, Grav_Window[win].win );

	XSetWindowBackgroundPixmap( Xdisplay
				, window->win 
				, GravityOn_Pixmap );
	XClearWindow( Xdisplay, window->win );

	/* Display BitGravity */
	Lisp_SetWinAttributes.bit_gravity = Bit_Gravity;
	XChangeWindowAttributes( Xdisplay
				, Display_Window.win
				, CWBitGravity
				, &Lisp_SetWinAttributes );

	/* Lisp_Window Window Gravity */
	/*
	Lisp_SetWinAttributes.win_gravity = Bit_Gravity;
	XChangeWindowAttributes( Xdisplay
				, Lisp_Window.win
				, CWWinGravity
				, &Lisp_SetWinAttributes );
	*/
	XFlush( Xdisplay );
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
	if( flag ) XResizeWindow( Xdisplay, window->win
				  , window->width, window->height );

	Resize_Subwindows();

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
	if(Def_Auto_Repeat && !Auto_Repeat ) XAutoRepeatOff( Xdisplay );
      }

    if( event->type == LeaveNotify )
      {
	Mouse_Included = FALSE;
	if(Def_Auto_Repeat && !Auto_Repeat ) XAutoRepeatOn( Xdisplay );
      }
  } /* end mouse_Xcrossed */
