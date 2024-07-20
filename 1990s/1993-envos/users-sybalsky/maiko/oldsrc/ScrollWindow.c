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
#include "XCursors.h"


Cursor HorizScrollCursor
     , HorizThumbCursor
     , ScrollDownCursor
     , ScrollLeftCursor
     , ScrollRightCursor
     , ScrollUpCursor
     , VertScrollCursor
     , VertThumbCursor;

extern Display *Xdisplay;
extern MyWindow Vert_Scroll
	      , Horiz_Scroll;
extern int Scroll_Width
	 , Scroll_Border;

Before_CreateScroll( parent, child )
MyWindow *parent
       , *child;
{
#ifdef TRACE
	printf( "TRACE: Before_CreateScroll()\n" );
#endif
	/* Scroll Window Geometory */
	child->border = parent->border;

	if( child == &Vert_Scroll ) {
		child->y = 0;
		child->width = Scroll_Width;
		child->x = (parent->width - 1)
				- (child->width + child->border);
		child->height = parent->height
				- (Scroll_Width + 3*Scroll_Border);
	} 
	else if( child == &Horiz_Scroll ) { 
		child->x = 0;
		child->height = Scroll_Width;
		child->y = (parent->height - 1)
				- (child->height + child->border);
		child->width = parent->width
				- (Scroll_Width + 3*Scroll_Border);
	} /* end if(child) */

} /* end Before_CreateScroll */

After_CreateScroll( parent, child )
MyWindow *parent
       , *child;
{
#ifdef TRACE
	printf( "TRACE: After_CreateScroll()\n" );
#endif

	XMapWindow( Xdisplay, child->win );
	Add_WindowList( child );

	/* Cursor */
	if( child == &Vert_Scroll ) {
		set_Xcursor( (char*)scrolldown_cursor.cuimage
				, (int) scrolldown_cursor.cuhotspotx
				, (int) (15 - scrolldown_cursor.cuhotspoty)
				, &ScrollDownCursor );
		set_Xcursor( (char*)scrollleft_cursor.cuimage
				, (int) scrollleft_cursor.cuhotspotx
				, (int) (15 - scrollleft_cursor.cuhotspoty)
				, &ScrollLeftCursor );
		set_Xcursor( (char*)vertscroll_cursor.cuimage
				, (int) vertscroll_cursor.cuhotspotx
				, (int) (15 - vertscroll_cursor.cuhotspoty)
				, &VertScrollCursor );
		set_Xcursor( (char*)vertthumb_cursor.cuimage
				, (int) vertthumb_cursor.cuhotspotx
				, (int) (15 - vertthumb_cursor.cuhotspoty)
				, &VertThumbCursor );
		DefineCursor( child, &VertScrollCursor );
	}
	else if( child == &Horiz_Scroll ) {
		set_Xcursor( (char*)horizscroll_cursor.cuimage
				, (int) horizscroll_cursor.cuhotspotx
				, (int) (15 - horizscroll_cursor.cuhotspoty)
				, &HorizScrollCursor );
		set_Xcursor( (char*)horizthumb_cursor.cuimage
				, (int) horizthumb_cursor.cuhotspotx
				, (int) (15 - horizthumb_cursor.cuhotspoty)
				, &HorizThumbCursor );
		set_Xcursor( (char*)scrollright_cursor.cuimage
				, (int) scrollright_cursor.cuhotspotx
				, (int) (15 - scrollright_cursor.cuhotspoty)
				, &ScrollRightCursor );
		set_Xcursor( (char*)scrollup_cursor.cuimage
				, (int) scrollup_cursor.cuhotspotx
				, (int) (15 - scrollup_cursor.cuhotspoty)
				, &ScrollUpCursor );
		DefineCursor( child, &HorizScrollCursor );
	}

} /* end After_CreateScroll */

Before_ResizeScroll( window )
MyWindow *window;
{
#ifdef TRACE
	printf( "TRACE: Before_ResizeScroll()\n" );
#endif
	
	if( window == &Vert_Scroll ) {
		window->x = (window->parent->width - 1)
				- (window->width + window->border);
		window->height = window->parent->height
				- (Scroll_Width + 3*Scroll_Border);
	} 
	else if( window == &Horiz_Scroll ) { 
		window->y = (window->parent->height - 1)
				- (window->height + window->border);
		window->width = window->parent->width
				- (Scroll_Width + 3*Scroll_Border);
	} /* end if(window) */

} /* Before_ResizeScroll */

After_ResizeScroll( window )
MyWindow *window; 
{
#ifdef TRACE
	printf( "TRACE: After_ResizeScroll()\n" );
#endif
	
	if( window == &Vert_Scroll ) {
	} 
	else { 
	}

} /* After_ResizeScroll */

