/* @(#) Xsubwin.c Version 1.3 (4/27/92). copyright venue & Fuji Xerox  */
static char *id = "@(#) Xsubwin.c	1.3 4/27/92	(venue & Fuji Xerox)";

/*
*
*
* Copyright (C) 1988 by Fuji Xerox co.,Ltd. All rights reserved.
*
*		Author: Mitsunori Matsuda
*		Date  : August 11, 1988
*/

#include <stdio.h>

#include <X11/Xlib.h>
#include <X11/Xutil.h>

#include "XVersion.h"
#include "MyWindow.h"

extern XAnyEvent report;
extern Bool isXeventtype();
extern unsigned long Black_Pixel
		   , White_Pixel;
extern int lisp_Xmotion()
         , lisp_Xbutton()
	 , mouse_Xcrossed()
	 , lisp_Xexpose()
	 , Do_Scroll()
	 , Set_BitGravity()
	 , Raise_LispWindow()
	 , Before_CreateDisplay()
	 , After_CreateDisplay()
	 , Before_CreateScroll()
	 , After_CreateScroll()
	 , Before_CreateScrollbar()
	 , After_CreateScrollbar()
	 , Before_CreateGrav()
	 , After_CreateGrav()
	 , Before_ResizeDisplay()
	 , After_ResizeDisplay()
	 , Before_ResizeScroll()
	 , After_ResizeScroll()
	 , Before_ResizeScrollbar()
	 , After_ResizeScrollbar()
	 , Before_ResizeGrav()
	 , After_ResizeGrav()
	 , DispatchXhandler();

MyEvent Display_Event[] = {
                  { MotionNotify , lisp_Xmotion  , &Display_Event[1] }
                , { ButtonPress  , lisp_Xbutton  , &Display_Event[2] }
                , { ButtonRelease, lisp_Xbutton  , &Display_Event[3] }
		   , { EnterNotify  , mouse_Xcrossed, &Display_Event[4] }
		   , { LeaveNotify  , mouse_Xcrossed, &Display_Event[5] }
                , { Expose       , lisp_Xexpose  , NULL              } }

        , Scroll_Event[] = {
                  { ButtonPress  , Do_Scroll   , &Scroll_Event[1] }
                , { ButtonRelease, Do_Scroll   , &Scroll_Event[2] }
		, { EnterNotify  , Raise_LispWindow, NULL           }
		/* yet unimplemented 
                , { Expose       , ??, NULL             } 
		*/
		}

        , Grav_Event[] = {
                  { ButtonPress  , Set_BitGravity, NULL }
		/* yet umimplemented 
                , { ButtonRelease, ??, &Grav_Event[2] }
                , { Exopse       , ??, NULL           }
		*/ 
        	};


MyWindow Display_Window = {
                          NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL
                        , ButtonPressMask|ButtonReleaseMask|PointerMotionMask
                         |ExposureMask|EnterWindowMask|LeaveWindowMask
                        , NULL
                        , Before_CreateDisplay
                        , After_CreateDisplay
		        , Before_ResizeDisplay
		        , After_ResizeDisplay
                        , DispatchXhandler
                        , &Display_Event[0]
			, NULL
                        , NULL          }
        , Vert_Scroll = {
                          NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL
                        , ButtonPressMask|ButtonReleaseMask|EnterWindowMask
                        , NULL
			, Before_CreateScroll
                        , After_CreateScroll
			, Before_ResizeScroll
                        , After_ResizeScroll
                        , DispatchXhandler
                        , &Scroll_Event[0]
                        , NULL
                        , NULL         }
        , Vert_Scroll_Bar = {
                          NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL
                        , NoEventMask
                        , NULL
			, Before_CreateScrollbar
                        , After_CreateScrollbar
			, Before_ResizeScrollbar
                        , After_ResizeScrollbar
                        , DispatchXhandler
                        , NULL
                        , NULL
                        , NULL         }
        , Horiz_Scroll = {
                          NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL
                        , ButtonPressMask|ButtonReleaseMask|EnterWindowMask
                        , NULL
			, Before_CreateScroll
                        , After_CreateScroll
			, Before_ResizeScroll
                        , After_ResizeScroll
                        , DispatchXhandler
                        , &Scroll_Event[0]        
                        , NULL
                        , NULL       }
        , Horiz_Scroll_Bar = {
                          NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL
                        , NoEventMask
                        , NULL
			, Before_CreateScrollbar
                        , After_CreateScrollbar
			, Before_ResizeScrollbar
                        , After_ResizeScrollbar
                        , DispatchXhandler
                        , NULL
                        , NULL
                        , NULL         }
        , Grav_Window[] = {
                 {
                          NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL
                        , ButtonPressMask
                        , NULL
			, Before_CreateGrav
			, After_CreateGrav
			, Before_ResizeGrav
			, After_ResizeGrav
                        , DispatchXhandler
                        , &Grav_Event[0] 
                        , NULL
                        , NULL       }
                ,{
                          NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL
                        , ButtonPressMask
                        , NULL
			, Before_CreateGrav
			, After_CreateGrav
			, Before_ResizeGrav
			, After_ResizeGrav
                        , DispatchXhandler      
                        , &Grav_Event[0]          
                        , NULL
                        , NULL       }
                ,{
                          NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL
                        , ButtonPressMask
                        , NULL
			, Before_CreateGrav
			, After_CreateGrav
			, Before_ResizeGrav
			, After_ResizeGrav
                        , DispatchXhandler
                        , &Grav_Event[0]           
                        , NULL
                        , NULL       }
                ,{
                          NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL
                        , ButtonPressMask
                        , NULL
			, Before_CreateGrav
			, After_CreateGrav
			, Before_ResizeGrav
			, After_ResizeGrav
                        , DispatchXhandler
                        , &Grav_Event[0]         
                        , NULL
                        , NULL                  }
                                                 };

Create_Subwindows( display, parent )
     Display *display;
MyWindow *parent;
{
#ifdef TRACE
	printf( "TRACE: Create_Subwindows()\n" );
#endif

	/* Lisp Screen */
	CreateWindow( display, parent       , &Display_Window );

	/* Scroll */
	CreateWindow( display, parent       , &Vert_Scroll );
	CreateWindow( display, parent       , &Horiz_Scroll );

	CreateWindow( display, &Vert_Scroll , &Vert_Scroll_Bar );
	CreateWindow( display, &Horiz_Scroll, &Horiz_Scroll_Bar );

	/* Bit Bravity */
	{ int i;
	  for( i=0; i<4; i++ ) {
		CreateWindow( display, parent, &Grav_Window[i] );
	  } /* end for(i) */
	}

#ifdef TRACE 
	{
	extern DisplayArea ScreenRegion;
	printf( "Create_Subwindows(): ScreenRegion( %d, %d )-( %d, %d )\n"
			, ScreenRegion.left_x
			, ScreenRegion.top_y
			, ScreenRegion.right_x	
			, ScreenRegion.bottom_y );
	}
#endif

} /* end Create_Subwindows */

Resize_Subwindows(display)
     Display *display;
{
#ifdef TRACE
	printf( "TRACE: Resize_Subwindows()\n " );
#endif
/*
	ResizeWindow( display, &Display_Window  );
*/
	ResizeWindow( display, &Vert_Scroll     );
	ResizeWindow( display, &Horiz_Scroll    );

	{ int i;
	  for( i=0; i<4; i++ ) 
		ResizeWindow( display, &Grav_Window[i] );
	}

	ResizeWindow( display, &Display_Window  );

	Reconf_ScreenRegion(display);

} /* end Reconf_Subwindows */
