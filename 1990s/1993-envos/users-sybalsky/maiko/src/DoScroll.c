/* @(#) DoScroll.c Version 1.6 (2/8/93). copyright venue & Fuji Xerox  */
static char *id = "@(#) DoScroll.c	1.6 2/8/93	(venue & Fuji Xerox)";
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
#include "Xbitblt.h"

extern Cursor VertScrollCursor
	    , VertThumbCursor
	    , ScrollUpCursor
	    , ScrollDownCursor
	    , HorizScrollCursor
	    , HorizThumbCursor
	    , ScrollLeftCursor
	    , ScrollRightCursor;
extern XImage XScreenBitmap;
extern GC Copy_GC;
extern DisplayArea ScreenRegion;
extern MyWindow Lisp_Window
	      , Display_Window
	      , Vert_Scroll
	      , Horiz_Scroll;
extern int LispDisplayWidth
	 , LispDisplayHeight;

DisplayArea new_region;
int Scroll_Pitch = SCROLL_PITCH;
static int vertical   = VERTICAL
         , horizontal = HORIZONTAL;

Do_Scroll( event, window )
XButtonEvent *event;
MyWindow *window;
{
	int direction;
#ifdef TRACE
	printf( "TRACE: Do_Scroll()\n" );
#endif
	if( event->window == Vert_Scroll.win ) {
		direction = VERTICAL;
	} else { 
		direction = HORIZONTAL;
	}

	if( event->type == ButtonPress ) {
		switch( event->button & 0xFF ) {
		case Button1:
			if( direction == VERTICAL ) {
				DefineCursor( event->display, window, &ScrollUpCursor );
			} else { /* direction == HORIZONTAL */	
				DefineCursor( event->display, window, &ScrollLeftCursor );
			} /* end if(direction) */
			Scroll_Up( event, direction );
			break;	
		case Button2:
			if( direction == VERTICAL ) {
				DefineCursor( event->display, window, &VertThumbCursor );
			} else { /* direction == HORIZONTAL */	
				DefineCursor( event->display, window, &HorizThumbCursor );
			} /* end if(direction) */
			break;
		case Button3:
			if( direction == VERTICAL ) {
				DefineCursor( event->display, window, &ScrollDownCursor );
			} else { /* direction == HORIZONTAL */	
				DefineCursor( event->display, window, &ScrollRightCursor );
			} /* end if(direction) */
			Scroll_Down( event, direction );
			break;
		default:
			break;
		} /* end switch */
	} 
	else if( event->type == ButtonRelease ) {
		switch( event->button & 0xFF ) {
		case Button1:
		case Button3:
			if( direction == VERTICAL ) {
				DefineCursor( event->display, window, &VertScrollCursor );
			} else { /* direction == HORIZONTAL */	
				DefineCursor( event->display, window, &HorizScrollCursor );
			} /* end if(direction) */
			break;
		case Button2:
			JumpScroll( direction, event );
			if( direction == VERTICAL ) {
				DefineCursor( event->display, window, &VertScrollCursor );
			} else { /* direction == HORIZONTAL */	
				DefineCursor( event->display, window, &HorizScrollCursor );
			} /* end if(direction) */
			break;
		default:
			break;
		} /* end switch */
	} /* end if(type) */

} /* end Do_Scroll */

JumpScroll( direction, event )
int direction;
XButtonEvent *event;
{
	float temp;
#ifdef TRACE
	printf( "TRACE: JumpScroll()\n" );
#endif

	if( direction == VERTICAL ) {
		temp = (float)event->y / (float)Vert_Scroll.height;
		new_region.top_y = (int)((float)LispDisplayHeight * temp )
						- Display_Window.height/2;
		if( new_region.top_y < 0 ) new_region.top_y = 0;
		new_region.bottom_y = new_region.top_y 
					+ Display_Window.height - 1;
		if( new_region.bottom_y > LispDisplayHeight-1 ) {
			new_region.bottom_y = LispDisplayHeight - 1;
			new_region.top_y = new_region.bottom_y 
						- Display_Window.height + 1;
		} /* end if */

	} else { /* direction == HORIZONTAL */
		temp = (float)event->x / (float)Horiz_Scroll.width;
		new_region.left_x = (int)((float)LispDisplayWidth * temp)
					- Display_Window.width/2;
		if( new_region.left_x < 0 ) new_region.left_x = 0;
		new_region.right_x = new_region.left_x 
					+ Display_Window.width - 1;
		if( new_region.right_x > LispDisplayWidth-1 ) {
			new_region.right_x = LispDisplayWidth - 1;
			new_region.left_x = new_region.right_x 
						- Display_Window.width + 1;
		} /* end if */
	} /* end if(direction) */

	Scroll( event, direction, &new_region);

} /* end Jump_Scroll */

Scroll_Up( event, direction )
XButtonEvent *event;
int direction;
{
#ifdef TRACE
	printf( "TRACE: Scroll_Up()\n" );
#endif

	if( direction == VERTICAL ) {
		new_region.top_y = ScreenRegion.top_y + Scroll_Pitch;
		new_region.bottom_y = new_region.top_y 
					+ Display_Window.height - 1;
		if( new_region.bottom_y > LispDisplayHeight-1 ) {
			new_region.bottom_y = LispDisplayHeight - 1;
			new_region.top_y = new_region.bottom_y 
						- Display_Window.height + 1;
		} /* end if */
	} else { /* direction == HORIZONTAL */
		new_region.left_x = ScreenRegion.left_x + Scroll_Pitch;
		new_region.right_x = new_region.left_x 
					+ Display_Window.width - 1;
		if( new_region.right_x > LispDisplayWidth-1 ) {
			new_region.right_x = LispDisplayWidth - 1;
			new_region.left_x = new_region.right_x 
						- Display_Window.width + 1;
		} /* end if */
	} /* end  if(direction) */

#ifdef TRACE
	printf( "Scroll_Up():     NewRegion=(%d,%d)-(%d,%d)\n"
		, new_region.left_x, new_region.top_y
		, new_region.right_x, new_region.bottom_y );
#endif

	Scroll( event, direction, &new_region);

} /* end Scroll_Up */

Scroll_Down( event, direction )
XButtonEvent *event;
int direction;
{
#ifdef TRACE
	printf( "TRACE: Scroll_Down()\n" );
#endif

	if( direction == VERTICAL ) {
		new_region.top_y = ScreenRegion.top_y - Scroll_Pitch;
		if( new_region.top_y < 0 ) new_region.top_y = 0;
		new_region.bottom_y = new_region.top_y 
					+ Display_Window.height - 1;
	} else { /* direction == HORIZONTAL */
		new_region.left_x = ScreenRegion.left_x - Scroll_Pitch;
		if( new_region.left_x < 0 ) new_region.left_x = 0;
		new_region.right_x = new_region.left_x 
					+ Display_Window.width - 1;
	} /* end  if(direction) */

#ifdef TRACE
	printf( "Scroll_Down():     NewRegion=(%d,%d)-(%d,%d)\n"
		, new_region.left_x, new_region.top_y
		, new_region.right_x, new_region.bottom_y );
#endif

	Scroll( event, direction, &new_region );

} /* end Scroll_Down */

Scroll( event, direction, new_region )
XButtonEvent *event;
int direction;
DisplayArea *new_region;
{
#ifdef TRACE
	printf( "TRACE: Scroll()\n" );
#endif

	if( direction == VERTICAL ) {
		if( new_region->top_y == ScreenRegion.top_y ) return;

		if( (new_region->top_y > ScreenRegion.bottom_y)
		 || (new_region->bottom_y < ScreenRegion.top_y) ) {
                	ScreenRegion.top_y    = new_region->top_y;
                	ScreenRegion.bottom_y = ScreenRegion.top_y 
                                                + Display_Window.height - 1; 
			refresh_Xscreen(event->display);
		}
		else if ( new_region->top_y > ScreenRegion.top_y ) {
			int copy_y
			  , copy_height
			  , blt_y
			  , blt_height;

			blt_height = copy_y = new_region->top_y 
						- ScreenRegion.top_y;
			copy_height = Display_Window.height - blt_height;
			blt_y = ScreenRegion.bottom_y + 1;

                        ScreenRegion.top_y    = new_region->top_y;
                        ScreenRegion.bottom_y = ScreenRegion.top_y
                                                + Display_Window.height - 1; 


			XLOCK;
			XCopyArea( event->display
					, Display_Window.win
					, Display_Window.win
					, Copy_GC
					, 0
					, copy_y
					, Display_Window.width
					, copy_height
					, 0
					, 0 );
			Xbitblt( event->display
				, ScreenRegion.left_x
				, blt_y
				, Display_Window.width
				, blt_height );
			XFlush(event->display);
			XUNLOCK;
		}
		else { /* new_region->top_y < ScreenRegion.top_y */
			int copy_y
			  , copy_height
			  , blt_height;

			blt_height = copy_y =  ScreenRegion.top_y 
						- new_region->top_y;
			copy_height = Display_Window.height - blt_height;

                        ScreenRegion.top_y    = new_region->top_y;
                        ScreenRegion.bottom_y = ScreenRegion.top_y
                                                + Display_Window.height - 1; 

			XLOCK;
			XCopyArea( event->display
					, Display_Window.win
					, Display_Window.win
					, Copy_GC
					, 0
					, 0
					, Display_Window.width
					, copy_height
					, 0
					, copy_y );
			Xbitblt( event->display
				, ScreenRegion.left_x
				, ScreenRegion.top_y
				, Display_Window.width
				, blt_height );
			XFlush(event->display);
			XUNLOCK;
		} /* end if */

		Move_ScrollBar( event->display, vertical );

	} else { /* direction == HORIZONTAL */

		if( new_region->left_x == ScreenRegion.left_x ) return;

		if( (new_region->left_x > ScreenRegion.right_x)
		 || (new_region->right_x < ScreenRegion.left_x) ) {
                	ScreenRegion.left_x   = new_region->left_x;
                	ScreenRegion.right_x  = ScreenRegion.left_x
                                                + Display_Window.width - 1;
			refresh_Xscreen(event->display);
		}
		else if( new_region->left_x > ScreenRegion.left_x ) {
			int copy_x
			  , copy_width
			  , blt_x
			  , blt_width;

			blt_width = copy_x = new_region->left_x
						- ScreenRegion.left_x;
			copy_width = Display_Window.width - blt_width;
			blt_x = ScreenRegion.right_x + 1;

                        ScreenRegion.left_x   = new_region->left_x;
                        ScreenRegion.right_x  = ScreenRegion.left_x
                                                + Display_Window.width - 1;

			XLOCK;
			XCopyArea( event->display
					, Display_Window.win
					, Display_Window.win
					, Copy_GC
					, copy_x
					, 0
					, copy_width
					, Display_Window.height
				 	, 0
					, 0 );
			Xbitblt( event->display
				, blt_x
				, ScreenRegion.top_y
				, blt_width
				, Display_Window.height );
			XFlush(event->display);
			XUNLOCK;
		}
		else { /* new_region->left_x < ScreenRegion.left_x */
			int copy_x
			  , copy_width
			  , blt_width;

			blt_width = copy_x = ScreenRegion.left_x 
						- new_region->left_x;
			copy_width = Display_Window.width - blt_width;

                        ScreenRegion.left_x   = new_region->left_x;
                        ScreenRegion.right_x  = ScreenRegion.left_x
                                                + Display_Window.width - 1;

			XLOCK;
			XCopyArea( event->display
					, Display_Window.win
					, Display_Window.win
					, Copy_GC
					, 0
					, 0
					, copy_width
					, Display_Window.height
					, copy_x
					, 0 );
			Xbitblt( event->display
				, ScreenRegion.left_x
				, ScreenRegion.top_y
				, blt_width
				, Display_Window.height );
			XFlush(event->display);
			XUNLOCK;
		} /* end if */

		Move_ScrollBar( event->display, horizontal );

	} /* end if(direction) */

} /* end Scroll */