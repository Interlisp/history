/* @(#) Xlspwin.c Version 1.6 (2/8/93). copyright venue & Fuji Xerox  */
static char *id = "@(#) Xlspwin.c	1.6 2/8/93	(venue & Fuji Xerox)";
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
#include "Xdeflt.h"

#include "Xcursdef.h"
#include "XWaitCur.h"

#include "dbprint.h"


#define FALSE 0
#define TRUE  !FALSE

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

extern char Window_Title[];
extern char Icon_Title[];

Pixmap      IconPixmap;
GC          Copy_GC
          , CopyInvert_GC;
XGCValues   gcv;
XSizeHints  szhint;
XWMHints    Lisp_WMhints;
XClassHint  xclasshint;
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
        , Lisp_Window = { Window_Title
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

Create_LispWindow(display)
     Display *display;
  {
    TPRINT(( "TRACE: Create_LispWindow()\n" ));

    CreateWindow( display, &Root_Window, &Lisp_Window );

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

	TPRINT(( "TRACE: CreateLisp_Window()\n" ));

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
  MyWindow *parent, *child;
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

    make_Xicon(Xdisplay);

    szhint.max_width  = LispWindow_MaxWidth = LispDisplayWidth 
			+ ( (Scroll_Width > 0) ? Scroll_Width + 2*Scroll_Border
					       : 0 );
    szhint.max_height = LispWindow_MaxHeight = LispDisplayHeight 
			+ ( (Scroll_Width > 0) ? Scroll_Width + 2*Scroll_Border
					       : 0 );
    szhint.flags = PMaxSize;

    XSetStandardProperties( Xdisplay, child->win, child->name, Icon_Title,
#ifdef OSF1
			    NULL,	/* Current icon code is bad */
#else
			    IconPixmap,
#endif /* OSF1 */
			    NULL, NULL, &szhint );

    Lisp_WMhints.icon_pixmap = IconPixmap;
    Lisp_WMhints.input = True;
#ifdef OSF1
    Lisp_WMhints.flags  = InputHint;
#else
    Lisp_WMhints.flags  = IconPixmapHint | InputHint;
#endif /* OSF1 */

    xclasshint.res_name = "lde";
    xclasshint.res_class = "Lde";

    XSetWMHints( Xdisplay, child->win, &Lisp_WMhints );

    /* XSetWMProperties( Xdisplay,
			 child->win, child->name,
			 Icon_Title,
			 NULL,
			 NULL,
			 &szhint,
			 &Lisp_WMhints,
			 &xclasshint); */

    /* Lisp_WMhints.icon_x = Display_Width - Lisp_icon_width ;
    Lisp_WMhints.icon_y = 0;
    Don't set any icon hints, the WM takes care of that. /jarl */

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

    init_Xcursor(Xdisplay);
	
    Create_Subwindows( Xdisplay, child );

    set_Xcursor( Xdisplay
		    , (char*) wait_cursor.cuimage
		    , (int) wait_cursor.cuhotspotx
		    , (int) (15 - wait_cursor.cuhotspoty)
		    , &WaitCursor, 0 );

    DefineCursor( Xdisplay, child, &WaitCursor );

  } /* end After_CreateLispWindow */ 
