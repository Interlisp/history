h47594s 00000/00000/00391d D 1.6 93/02/08 14:41:05 sybalsky 6 5c Big VM (and new CDR coding) changes for 3.0 \nes 00013/00000/00378d D 1.5 92/05/27 19:11:24 sybalsky 5 4c fixing SCCS headers \nes 00037/00031/00341d D 1.4 92/04/27 18:36:47 nilsson 4 3c Fix of Xdisplay deps.es 00000/00000/00372d D 1.3 92/04/21 16:55:47 sybalsky 3 2c shortening file names for DOS \nes 00001/00001/00371d D 1.2 90/04/20 01:06:53 sybalsky 2 1c AIX:  shortening file names, bulk change.es 00372/00000/00000d D 1.1 90/03/01 15:30:11 osamu 1 0c date and time created 90/03/01 15:30:11 by osamueuUf e 0tTI 1/* %Z% %M% Version %I% (%G%). copyright venue & Fuji Xerox  */static char *id = "%Z% %M%	%I% %G%	(venue & Fuji Xerox)";/**** Copyright (C) 1988 by Fuji Xerox co.,Ltd. All rights reserved.**		Author: Mitsunori Matsuda*		Date  : August 11, 1988*/#include <stdio.h>#include <X11/Xlib.h>#include <X11/Xutil.h>#include "XVersion.h"#include "MyWindow.h"D 2#include "lispXbitblt.h"E 2I 2#include "Xbitblt.h"E 2D 4extern Display *Xdisplay;E 4extern Cursor VertScrollCursor	    , VertThumbCursor	    , ScrollUpCursor	    , ScrollDownCursor	    , HorizScrollCursor	    , HorizThumbCursor	    , ScrollLeftCursor	    , ScrollRightCursor;extern XImage XScreenBitmap;extern GC Copy_GC;extern DisplayArea ScreenRegion;extern MyWindow Lisp_Window	      , Display_Window	      , Vert_Scroll	      , Horiz_Scroll;extern int LispDisplayWidth	 , LispDisplayHeight;DisplayArea new_region;int Scroll_Pitch = SCROLL_PITCH;static int vertical   = VERTICAL         , horizontal = HORIZONTAL;Do_Scroll( event, window )XButtonEvent *event;MyWindow *window;{	int direction;#ifdef TRACE	printf( "TRACE: Do_Scroll()\n" );#endif	if( event->window == Vert_Scroll.win ) {		direction = VERTICAL;	} else { 		direction = HORIZONTAL;	}	if( event->type == ButtonPress ) {		switch( event->button & 0xFF ) {		case Button1:			if( direction == VERTICAL ) {D 4				DefineCursor( window, &ScrollUpCursor );E 4I 4				DefineCursor( event->display, window, &ScrollUpCursor );E 4			} else { /* direction == HORIZONTAL */	D 4				DefineCursor( window, &ScrollLeftCursor );E 4I 4				DefineCursor( event->display, window, &ScrollLeftCursor );E 4			} /* end if(direction) */D 4			Scroll_Up( direction );E 4I 4			Scroll_Up( event, direction );E 4			break;			case Button2:			if( direction == VERTICAL ) {D 4				DefineCursor( window, &VertThumbCursor );E 4I 4				DefineCursor( event->display, window, &VertThumbCursor );E 4			} else { /* direction == HORIZONTAL */	D 4				DefineCursor( window, &HorizThumbCursor );E 4I 4				DefineCursor( event->display, window, &HorizThumbCursor );E 4			} /* end if(direction) */			break;		case Button3:			if( direction == VERTICAL ) {D 4				DefineCursor( window, &ScrollDownCursor );E 4I 4				DefineCursor( event->display, window, &ScrollDownCursor );E 4			} else { /* direction == HORIZONTAL */	D 4				DefineCursor( window, &ScrollRightCursor );E 4I 4				DefineCursor( event->display, window, &ScrollRightCursor );E 4			} /* end if(direction) */D 4			Scroll_Down( direction );E 4I 4			Scroll_Down( event, direction );E 4			break;		default:			break;		} /* end switch */	} 	else if( event->type == ButtonRelease ) {		switch( event->button & 0xFF ) {		case Button1:		case Button3:			if( direction == VERTICAL ) {D 4				DefineCursor( window, &VertScrollCursor );E 4I 4				DefineCursor( event->display, window, &VertScrollCursor );E 4			} else { /* direction == HORIZONTAL */	D 4				DefineCursor( window, &HorizScrollCursor );E 4I 4				DefineCursor( event->display, window, &HorizScrollCursor );E 4			} /* end if(direction) */			break;		case Button2:			JumpScroll( direction, event );			if( direction == VERTICAL ) {D 4				DefineCursor( window, &VertScrollCursor );E 4I 4				DefineCursor( event->display, window, &VertScrollCursor );E 4			} else { /* direction == HORIZONTAL */	D 4				DefineCursor( window, &HorizScrollCursor );E 4I 4				DefineCursor( event->display, window, &HorizScrollCursor );E 4			} /* end if(direction) */			break;		default:			break;		} /* end switch */	} /* end if(type) */} /* end Do_Scroll */JumpScroll( direction, event )int direction;XButtonEvent *event;{	float temp;#ifdef TRACE	printf( "TRACE: JumpScroll()\n" );#endif	if( direction == VERTICAL ) {		temp = (float)event->y / (float)Vert_Scroll.height;		new_region.top_y = (int)((float)LispDisplayHeight * temp )						- Display_Window.height/2;		if( new_region.top_y < 0 ) new_region.top_y = 0;		new_region.bottom_y = new_region.top_y 					+ Display_Window.height - 1;		if( new_region.bottom_y > LispDisplayHeight-1 ) {			new_region.bottom_y = LispDisplayHeight - 1;			new_region.top_y = new_region.bottom_y 						- Display_Window.height + 1;		} /* end if */	} else { /* direction == HORIZONTAL */		temp = (float)event->x / (float)Horiz_Scroll.width;		new_region.left_x = (int)((float)LispDisplayWidth * temp)					- Display_Window.width/2;		if( new_region.left_x < 0 ) new_region.left_x = 0;		new_region.right_x = new_region.left_x 					+ Display_Window.width - 1;		if( new_region.right_x > LispDisplayWidth-1 ) {			new_region.right_x = LispDisplayWidth - 1;			new_region.left_x = new_region.right_x 						- Display_Window.width + 1;		} /* end if */	} /* end if(direction) */D 4	Scroll( direction, &new_region);E 4I 4	Scroll( event, direction, &new_region);E 4} /* end Jump_Scroll */D 4Scroll_Up( direction )E 4I 4Scroll_Up( event, direction )XButtonEvent *event;E 4int direction;{#ifdef TRACE	printf( "TRACE: Scroll_Up()\n" );#endif	if( direction == VERTICAL ) {		new_region.top_y = ScreenRegion.top_y + Scroll_Pitch;		new_region.bottom_y = new_region.top_y 					+ Display_Window.height - 1;		if( new_region.bottom_y > LispDisplayHeight-1 ) {			new_region.bottom_y = LispDisplayHeight - 1;			new_region.top_y = new_region.bottom_y 						- Display_Window.height + 1;		} /* end if */	} else { /* direction == HORIZONTAL */		new_region.left_x = ScreenRegion.left_x + Scroll_Pitch;		new_region.right_x = new_region.left_x 					+ Display_Window.width - 1;		if( new_region.right_x > LispDisplayWidth-1 ) {			new_region.right_x = LispDisplayWidth - 1;			new_region.left_x = new_region.right_x 						- Display_Window.width + 1;		} /* end if */	} /* end  if(direction) */#ifdef TRACE	printf( "Scroll_Up():     NewRegion=(%d,%d)-(%d,%d)\n"		, new_region.left_x, new_region.top_y		, new_region.right_x, new_region.bottom_y );#endifD 4	Scroll( direction, &new_region);E 4I 4	Scroll( event, direction, &new_region);E 4} /* end Scroll_Up */D 4Scroll_Down( direction )E 4I 4Scroll_Down( event, direction )XButtonEvent *event;E 4int direction;{#ifdef TRACE	printf( "TRACE: Scroll_Down()\n" );#endif	if( direction == VERTICAL ) {		new_region.top_y = ScreenRegion.top_y - Scroll_Pitch;		if( new_region.top_y < 0 ) new_region.top_y = 0;		new_region.bottom_y = new_region.top_y 					+ Display_Window.height - 1;	} else { /* direction == HORIZONTAL */		new_region.left_x = ScreenRegion.left_x - Scroll_Pitch;		if( new_region.left_x < 0 ) new_region.left_x = 0;		new_region.right_x = new_region.left_x 					+ Display_Window.width - 1;	} /* end  if(direction) */#ifdef TRACE	printf( "Scroll_Down():     NewRegion=(%d,%d)-(%d,%d)\n"		, new_region.left_x, new_region.top_y		, new_region.right_x, new_region.bottom_y );#endifD 4	Scroll( direction, &new_region );E 4I 4	Scroll( event, direction, &new_region );E 4} /* end Scroll_Down */D 4Scroll( direction, new_region )E 4I 4Scroll( event, direction, new_region )XButtonEvent *event;E 4int direction;DisplayArea *new_region;{#ifdef TRACE	printf( "TRACE: Scroll()\n" );#endif	if( direction == VERTICAL ) {		if( new_region->top_y == ScreenRegion.top_y ) return;		if( (new_region->top_y > ScreenRegion.bottom_y)		 || (new_region->bottom_y < ScreenRegion.top_y) ) {                	ScreenRegion.top_y    = new_region->top_y;                	ScreenRegion.bottom_y = ScreenRegion.top_y                                                 + Display_Window.height - 1; D 4			refresh_Xscreen();E 4I 4			refresh_Xscreen(event->display);E 4		}		else if ( new_region->top_y > ScreenRegion.top_y ) {			int copy_y			  , copy_height			  , blt_y			  , blt_height;			blt_height = copy_y = new_region->top_y 						- ScreenRegion.top_y;			copy_height = Display_Window.height - blt_height;			blt_y = ScreenRegion.bottom_y + 1;                        ScreenRegion.top_y    = new_region->top_y;                        ScreenRegion.bottom_y = ScreenRegion.top_y                                                + Display_Window.height - 1; I 5			XLOCK;E 5D 4			XCopyArea( XdisplayE 4I 4			XCopyArea( event->displayE 4					, Display_Window.win					, Display_Window.win					, Copy_GC					, 0					, copy_y					, Display_Window.width					, copy_height					, 0					, 0 );D 4			Xbitblt( ScreenRegion.left_xE 4I 4			Xbitblt( event->display				, ScreenRegion.left_xE 4				, blt_y				, Display_Window.width				, blt_height );I 5			XFlush(event->display);			XUNLOCK;E 5		}		else { /* new_region->top_y < ScreenRegion.top_y */			int copy_y			  , copy_height			  , blt_height;			blt_height = copy_y =  ScreenRegion.top_y 						- new_region->top_y;			copy_height = Display_Window.height - blt_height;                        ScreenRegion.top_y    = new_region->top_y;                        ScreenRegion.bottom_y = ScreenRegion.top_y                                                + Display_Window.height - 1; I 5			XLOCK;E 5D 4			XCopyArea( XdisplayE 4I 4			XCopyArea( event->displayE 4					, Display_Window.win					, Display_Window.win					, Copy_GC					, 0					, 0					, Display_Window.width					, copy_height					, 0					, copy_y );D 4			Xbitblt( ScreenRegion.left_xE 4I 4			Xbitblt( event->display				, ScreenRegion.left_xE 4				, ScreenRegion.top_y				, Display_Window.width				, blt_height );I 5			XFlush(event->display);			XUNLOCK;E 5		} /* end if */D 4		Move_ScrollBar( vertical );E 4I 4		Move_ScrollBar( event->display, vertical );E 4	} else { /* direction == HORIZONTAL */		if( new_region->left_x == ScreenRegion.left_x ) return;		if( (new_region->left_x > ScreenRegion.right_x)		 || (new_region->right_x < ScreenRegion.left_x) ) {                	ScreenRegion.left_x   = new_region->left_x;                	ScreenRegion.right_x  = ScreenRegion.left_x                                                + Display_Window.width - 1;D 4			refresh_Xscreen();E 4I 4			refresh_Xscreen(event->display);E 4		}		else if( new_region->left_x > ScreenRegion.left_x ) {			int copy_x			  , copy_width			  , blt_x			  , blt_width;			blt_width = copy_x = new_region->left_x						- ScreenRegion.left_x;			copy_width = Display_Window.width - blt_width;			blt_x = ScreenRegion.right_x + 1;                        ScreenRegion.left_x   = new_region->left_x;                        ScreenRegion.right_x  = ScreenRegion.left_x                                                + Display_Window.width - 1;I 5			XLOCK;E 5D 4			XCopyArea( XdisplayE 4I 4			XCopyArea( event->displayE 4					, Display_Window.win					, Display_Window.win					, Copy_GC					, copy_x					, 0					, copy_width					, Display_Window.height				 	, 0					, 0 );D 4			Xbitblt( blt_xE 4I 4			Xbitblt( event->display				, blt_xE 4				, ScreenRegion.top_y				, blt_width				, Display_Window.height );I 5			XFlush(event->display);			XUNLOCK;E 5		}		else { /* new_region->left_x < ScreenRegion.left_x */			int copy_x			  , copy_width			  , blt_width;			blt_width = copy_x = ScreenRegion.left_x 						- new_region->left_x;			copy_width = Display_Window.width - blt_width;                        ScreenRegion.left_x   = new_region->left_x;                        ScreenRegion.right_x  = ScreenRegion.left_x                                                + Display_Window.width - 1;I 5			XLOCK;E 5D 4			XCopyArea( XdisplayE 4I 4			XCopyArea( event->displayE 4					, Display_Window.win					, Display_Window.win					, Copy_GC					, 0					, 0					, copy_width					, Display_Window.height					, copy_x					, 0 );D 4			Xbitblt( ScreenRegion.left_xE 4I 4			Xbitblt( event->display				, ScreenRegion.left_xE 4				, ScreenRegion.top_y				, blt_width				, Display_Window.height );I 5			XFlush(event->display);			XUNLOCK;E 5		} /* end if */D 4		Move_ScrollBar( horizontal );E 4I 4		Move_ScrollBar( event->display, horizontal );E 4	} /* end if(direction) */} /* end Scroll */E 1