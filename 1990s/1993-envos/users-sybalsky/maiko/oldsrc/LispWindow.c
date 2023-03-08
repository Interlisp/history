/* @(#) LispWindow.c Version 1.8 (6/12/91). copyright venue & Fuji Xerox  */
static char *id = "@(#) LispWindow.c	1.8 6/12/91	(venue & Fuji Xerox)";
/*
*
*
* Copyright (C) 1988 by Fuji Xerox co.,Ltd. All rights reserved.
*
*		Author: Mitsunori Matsuda
*		Date  : June 5, 1988
*
*/


/************************************************************************/
/*									*/
/*	Copyright 1989, 1990 Venue, Fuji Xerox Co., Ltd, Xerox Corp.	*/
/*									*/
/*	This file is work-product resulting from the Xerox/Venue	*/
/*	Agreement dated 18-August-1989 for support of Medley.		*/
/*									*/
/************************************************************************/


#include <stdio.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>

#include "XVersion.h"
#include "MyWindow.h"
#include "Xdefaults.h"

#include "XCursorDef.h"
#include "XWaitCur.h"

#include "dbprint.h"


#define FALSE 0
#define TRUE  !FALSE

extern char *Lisp_Window_Geom;
extern int Lisp_Border
         , LispDisplayWidth
         , LispDisplayHeight
         , Display_Width
         , Display_Height
	 , Lisp_icon_height
	 , Lisp_icon_width;
extern long Black_Pixel
	  , White_Pixel;
extern Display *Xdisplay;
extern Bool isXeventtype();
extern int DispatchXhandler()
	 , Before_CreateLispWindow()
	 , After_CreateLispWindow()
	 , lisp_Xkeyboard()
	 , lisp_Xconfigure();
extern MyWindow  Root_Window;
extern int Backing_Store;

Pixmap      IconPixmap;
GC          Copy_GC
          , CopyInvert_GC;
XGCValues   gcv;
XSizeHints  szhint;
XWMHints    Lisp_WMhints;
XEvent      report;
XSetWindowAttributes Lisp_SetWinAttributes;

int         Video_Inverted = FALSE
	  , DisplayRasterWidth
	  , Scroll_Border
	  , Scroll_Width = (SCROLL_WIDTH % 2) ? SCROLL_WIDTH+1 : SCROLL_WIDTH;

Cursor WaitCursor;

MyEvent Lisp_Event[] = {
                  { KeyPress       , lisp_Xkeyboard , &Lisp_Event[1] }
                , { KeyRelease     , lisp_Xkeyboard , &Lisp_Event[2] }
                , { ConfigureNotify, lisp_Xconfigure, NULL           } };

MyWindow *Head_of_Windows
        , Lisp_Window = { WINDOW_NAME
                        , NULL, NULL, NULL, NULL, NULL, NULL, NULL
                        , KeyPressMask|KeyReleaseMask|StructureNotifyMask
                        , NULL
                        , Before_CreateLispWindow
                        , After_CreateLispWindow
                        , NULL
                        , NULL
                        , DispatchXhandler      
                        , &Lisp_Event[0]
                        , NULL
                        , NULL          };



/************************************************************************/
/*									*/
/*									*/
/*									*/
/*									*/
/*									*/
/************************************************************************/

Create_LispWindow()
  {
    TPRINT(( "TRACE: Create_LispWindow()\n" ));

    CreateWindow( &Root_Window, &Lisp_Window );

  } /* end Create_LispWindow */



/************************************************************************/
/*									*/
/*									*/
/*									*/
/*									*/
/*									*/
/************************************************************************/

Before_CreateLispWindow( parent, child )
MyWindow *parent
       , *child;
{
	int bitmask;

	TPRINT(( "TRACE: CreateLisp_Window()\n" ));

	/* Get Geometry */
	bitmask = XParseGeometry( Lisp_Window_Geom
					, &(child->x)
					, &(child->y)
					, &(child->width)
					, &(child->height) );
	if( !(bitmask & WidthValue) ) {
		child->width = DEF_WIN_WIDTH;
	}
	if( !(bitmask & HeightValue) ) {
		child->height = DEF_WIN_HEIGHT;
	}
	if( !(bitmask & XValue) ) { 
		child->x = DEF_WIN_X;
	}
	if ( Lisp_Window.x < 0 ) { 
		child->x += Display_Width - (child->width - 1);
	}
	if( !(bitmask & YValue) ) {
		child->y = DEF_WIN_Y;
	}
	if( child->y < 0 ) {
		child->y += Display_Height - (child->height - 1); 
	}

	child->border = Scroll_Border = Lisp_Border;

    TPRINT(("Window geometry: x=%d, y=%d, width=%d, height=%d, border=%d.\n",
	    child->x, child->y, child->width, child->height, child->border));

} /* end Before_CreateLispWindow */




/************************************************************************/
/*									*/
/*									*/
/*									*/
/*									*/
/*									*/
/************************************************************************/

int LispWindow_MaxWidth
  , LispWindow_MaxHeight;

After_CreateLispWindow( parent, child )
MyWindow *parent
       , *child;
{
	unsigned long event_mask;

	TPRINT(( "TRACE: After_CreateLispWindow()\n" ));

	XStoreName( Xdisplay, child->win, child->name );


	TPRINT(( "TRACE:      After XStoreName.\n" ));

	gcv.function   = GXcopy;
	gcv.foreground = Black_Pixel;
	gcv.background = White_Pixel;
	Copy_GC = XCreateGC( Xdisplay, child->win
				, GCForeground|GCBackground|GCFunction
				, &gcv );

	gcv.function   = GXcopyInverted;
	CopyInvert_GC = XCreateGC( Xdisplay, child->win
				, GCForeground|GCBackground|GCFunction
				, &gcv );

	Lisp_Window.gc = Video_Inverted ? &CopyInvert_GC
					: &Copy_GC;

	make_Xicon();

        szhint.max_width  = LispWindow_MaxWidth = LispDisplayWidth 
			+ ( (Scroll_Width > 0) ? Scroll_Width + 2*Scroll_Border
					       : 0 );
        szhint.max_height = LispWindow_MaxHeight = LispDisplayHeight 
			+ ( (Scroll_Width > 0) ? Scroll_Width + 2*Scroll_Border
					       : 0 );
        szhint.flags = PMaxSize;

	XSetStandardProperties( Xdisplay, child->win, child->name
				,ICON_NAME , IconPixmap, NULL, NULL, &szhint );

	Lisp_WMhints.icon_x = Display_Width - Lisp_icon_width ;
				 
	Lisp_WMhints.icon_y = 0;
	Lisp_WMhints.icon_pixmap = IconPixmap;
	Lisp_WMhints.input = True;
	Lisp_WMhints.flags  = IconPositionHint | IconPixmapHint | InputHint;

	XSetWMHints( Xdisplay, child->win, &Lisp_WMhints );

        event_mask =  ExposureMask;
        XSelectInput( Xdisplay,  child->win, event_mask );
	XMapWindow( Xdisplay, child->win );

#ifdef TRACE 
	printf( "XMap() finished.\n" );
#endif

	/* waite for Expose  */
	XIfEvent( Xdisplay, &report, isXeventtype, Expose );

	child->x      = ((XExposeEvent*) &report)->x;
	child->y      = ((XExposeEvent*) &report)->y;
	child->width  = ((XExposeEvent*) &report)->width;
	child->height = ((XExposeEvent*) &report)->height;

        event_mask =  StructureNotifyMask;
        XSelectInput( Xdisplay,  child->win, event_mask );

	Lisp_SetWinAttributes.win_gravity = NorthWestGravity;
	Lisp_SetWinAttributes.override_redirect = TRUE;
	XChangeWindowAttributes( Xdisplay
				, child->win
				, CWWinGravity||CWOverrideRedirect
				, &Lisp_SetWinAttributes );

	XFlush( Xdisplay );

	Add_WindowList( child );

	init_Xcursor();
	
	Create_Subwindows( child );

	set_Xcursor( (char*) wait_cursor.cuimage
			, (int) wait_cursor.cuhotspotx
			, (int) (15 - wait_cursor.cuhotspoty)
			, &WaitCursor, 0 );

	DefineCursor( child, &WaitCursor );

} /* end After_CreateLispWindow */ 
