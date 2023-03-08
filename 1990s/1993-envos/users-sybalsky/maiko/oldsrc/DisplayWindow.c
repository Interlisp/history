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

#include "lispemul.h"
#include "address.h"
#include "address68k.h"

#include "XVersion.h"
#include "MyWindow.h"

extern DLword *DisplayRegion68k;
extern Display *Xdisplay;
extern GC Copy_GC
	, CopyInvert_GC;
extern XSetWindowAttributes Lisp_SetWinAttributes;
extern int Bitmap_Pad
	 , Video_Inverted
	 , LispDisplayWidth
	 , LispDisplayHeight
	 , Scroll_Width
	 , Scroll_Border;
extern int Backing_Store;

XImage XScreenBitmap;
DisplayArea ScreenRegion;
int Bit_Gravity;

Before_CreateDisplay( parent, child )
MyWindow *parent
       , *child;
{
#ifdef TRACE
	printf( "TRACE: Before_CreateDisplay()\n" );
#endif
	/* Display Window Geometory */
	child->border = 0;			/* fixed width */
	child->x = child->y = 0;
	child->width  = parent->width  
			- ( (Scroll_Width>0) ? (Scroll_Width + 2*Scroll_Border)
					     : 0 );
	child->height = parent->height 
			- ( (Scroll_Width>0) ? (Scroll_Width + 2*Scroll_Border)
					     : 0 );

} /* end Before_CreateDisplay */

After_CreateDisplay( parent, child )
MyWindow *parent
       , *child;
{
#ifdef TRACE
	printf( "TRACE: After_CreateDisplay()\n" );
#endif

	XMapWindow( Xdisplay, child->win );
	AddTop_WindowList( child );

	/* Default BitGravity is NorthWest */
	Bit_Gravity = NorthWestGravity;
	Lisp_SetWinAttributes.bit_gravity = Bit_Gravity;
	XChangeWindowAttributes( Xdisplay
				, child->win
				, CWBitGravity
				, &Lisp_SetWinAttributes );

	/* Backing Store */

	if( Backing_Store ) {
		Lisp_SetWinAttributes.backing_store = Always;
		XChangeWindowAttributes( Xdisplay
				, child->win
				, CWBackingStore
				, &Lisp_SetWinAttributes );
	} /* end if(Backing_Store) */

	/* Dispay Region */
	ScreenRegion.left_x   = 0;
	ScreenRegion.top_y    = 0;
	ScreenRegion.right_x  = child->width  - 1;
	ScreenRegion.bottom_y = child->height - 1;

#ifdef TRACE
	printf( "After_CreateDisplayRegion(): " );
	printf( " ScreenRegion( %d, %d )-( %d, %d )\n"
				, ScreenRegion.left_x
				, ScreenRegion.top_y
				, ScreenRegion.right_x
				, ScreenRegion.bottom_y );
#endif

	child->gc = Video_Inverted ? &CopyInvert_GC
				    : &Copy_GC;

	/* Initialize Image */
        XScreenBitmap.width   = LispDisplayWidth;
        XScreenBitmap.height  = LispDisplayHeight; 
        XScreenBitmap.xoffset = 0;
        XScreenBitmap.format  = XYBitmap;
        XScreenBitmap.data = (char*) DisplayRegion68k;
#ifdef XV11R1
        XScreenBitmap.byte_order = LSBFirst;
#else XV11R1
        XScreenBitmap.byte_order = MSBFirst;
#endif XV11R1
        XScreenBitmap.bitmap_unit = 16;
        XScreenBitmap.bitmap_bit_order = MSBFirst;
        XScreenBitmap.bitmap_pad = Bitmap_Pad;
        XScreenBitmap.depth = 1;
        XScreenBitmap.bytes_per_line = ((LispDisplayWidth+(BITSPER_DLWORD-1))
                                        /BITSPER_DLWORD) * (BITSPER_DLWORD/8);

} /* end After_CreateDisplay */

Before_ResizeDisplay( child )
MyWindow *child;
{
#ifdef TRACE
	printf( "TRACE: Before_ResizeDisplay()\n" );
#endif
	child->width = child->parent->width 
			- ( (Scroll_Width>0) ? (Scroll_Width + 2*Scroll_Border)
					    : 0 );
	child->height = child->parent->height 
			- ( (Scroll_Width>0) ? (Scroll_Width + 2*Scroll_Border)
					    : 0 );

} /* end Before_ResizeDisplay */

After_ResizeDisplay( child )
MyWindow *child;
{
#ifdef TRACE
	printf( "TRACE: After_ResizeDisplay()\n" );
#endif

} /* end After_ResizeDisplay */


