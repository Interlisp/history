/* %Z% %M% Version %I% (%G%). copyright venue & Fuji Xerox  */
static char *id = "%Z% %M%	%I% %G%	(venue & Fuji Xerox)";
/*
*
*
* Copyright (C) 1988 by Fuji Xerox co.,Ltd. All rights reserved.
*
*		Author: Mitsunori Matsuda
*		Date  : September 5, 1988
*/

#include <stdio.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>

#include "XVersion.h"
#include "MyWindow.h"

#include "XCursorDef.h"
#include "Xdefcur.h"

extern Display *Xdisplay;
extern MyWindow Lisp_Window
	      , Grav_Window[];
extern int Bit_Gravity
	 , Scroll_Width
	 , Scroll_Border;

Cursor DefaultCursor = NULL;
Pixmap GravityOn_Pixmap
     , GravityOff_Pixmap;

Before_CreateGrav( parent, child )
MyWindow *parent
       , *child;
{
#ifdef TRACE
	printf( "TRACE: Before_CreateGrav()\n" );
#endif
	{ int i;
	  for( i=0; i<2; i++)
	    { int j;
	      for( j=0; j<2; j++ ) {
		if( child == &Grav_Window[i*2+j] ) {
			Grav_Window[i*2+j].border = parent->border;
			Grav_Window[i*2+j].width  = Grav_Window[i*2+j].height 
				= Scroll_Width / 2 - Grav_Window[i*2+j].border;
			Grav_Window[i*2+j].x = (parent->width - 1)
						- (Scroll_Width + Scroll_Border)
					+ ( j ? ( Grav_Window[i*2+(j-1)].width
						 +Grav_Window[i*2+(j-1)].border
						 +Grav_Window[i*2+j].border)
					      : 0 );
			Grav_Window[i*2+j].y = (parent->height - 1)
						- (Scroll_Width + Scroll_Border)
					+ ( i ? ( Grav_Window[(i-1)*2+j].height
						 +Grav_Window[(i-1)*2+j].border
						 +Grav_Window[i*2+j].border)
					      : 0 );
		} /* end if */
	      } /* end for(j) */
	    } /* end for(i) */
	}

} /* end Before_CreateScrollbar */

#include "Check.h"
#define North_West 0
#define North_East 1
#define South_West 2
#define South_East 3

After_CreateGrav( parent, child )
MyWindow *parent
       , *child;
{
	int win;
#ifdef TRACE
	printf( "TRACE: After_CreateGrav()\n" );
#endif
	
	if( !DefaultCursor ) {
		set_Xcursor( (char*)default_cursor.cuimage
				, (int)default_cursor.cuhotspotx
				, (int)(15 - default_cursor.cuhotspoty)
				, &DefaultCursor );
	} /* end if */

	if( !GravityOn_Pixmap )
		GravityOn_Pixmap = XCreateBitmapFromData( Xdisplay
							, Lisp_Window.win
							, check_bits
							, check_width
							, check_height );
	if( !GravityOff_Pixmap )
		GravityOff_Pixmap = XCreateBitmapFromData( Xdisplay
							, Lisp_Window.win
							, plain_bits
							, check_width
							, check_height );

	if( Bit_Gravity == NorthWestGravity ) win = North_West;
	if( Bit_Gravity == NorthEastGravity ) win = North_East;
	if( Bit_Gravity == SouthWestGravity ) win = South_West;
	if( Bit_Gravity == SouthEastGravity ) win = South_East;

	if( child == &Grav_Window[win] ) {
		XSetWindowBackgroundPixmap( Xdisplay
						, child->win
						, GravityOn_Pixmap );
	} else {
		XSetWindowBackgroundPixmap( Xdisplay
						, child->win
						, GravityOff_Pixmap );
	} /* end if */

	XMapWindow( Xdisplay, child->win );
	Add_WindowList( child );

	DefineCursor( child, &DefaultCursor );	

} /* end After_CreatGrav */

Before_ResizeGrav( window )
MyWindow *window;
{
#ifdef TRACE
	printf( "TRACE: Before_ResizeGrav()\n" );
#endif
	{ int i;
	  for( i=0; i<2; i++ )
	    { int j;
	      for( j=0; j<2; j++ ) {
		if( window == &Grav_Window[i*2+j] ) {
			Grav_Window[i*2+j].x = (window->parent->width - 1)
						- (Scroll_Width + Scroll_Border)
					+ ( j ? ( Grav_Window[i*2+(j-1)].width
						 +Grav_Window[i*2+(j-1)].border
						 +Grav_Window[i*2+j].border)
					      : 0 );
			Grav_Window[i*2+j].y = (window->parent->height - 1)
						- (Scroll_Width + Scroll_Border)
					+ ( i ? ( Grav_Window[(i-1)*2+j].height
						 +Grav_Window[(i-1)*2+j].border
						 +Grav_Window[i*2+j].border)
					      : 0 );
		} /* end if */
	      } /* end for(j) */
	    } /* end for(i) */
	}
	

} /* Before_ResizeGrav */

After_ResizeGrav( window )
MyWindow *window;
{
#ifdef TRACE
	printf( "TRACE: After_ResizeGrav()\n" );
#endif

} /* After_ResizeGrav */

