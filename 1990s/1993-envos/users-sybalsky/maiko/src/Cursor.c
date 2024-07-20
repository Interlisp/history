/* @(#) Cursor.c Version 1.5 (9/18/90). copyright venue & Fuji Xerox  */
static char *id = "@(#) Cursor.c	1.5 9/18/90	(venue & Fuji Xerox)";
/*
*
*
* Copyright (C) 1988 by Fuji Xerox co.,Ltd. All rights reserved.
*
*		Author: Mitsunori Matsuda
*		Date  : August 12, 1988
*
*		Removed global dependency on ``display'' /jarl 92-apr-27
*/



/************************************************************************/
/*									*/
/*	(C) Copyright 1989-92 Venue. All Rights Reserved.		*/
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

#include "lispemul.h"
#include "lsptypes.h"
#include "display.h"
#include "dbprint.h"

#include "XVersion.h"
#include "MyWindow.h"

extern MyWindow Lisp_Window;
extern XGCValues gcv;
extern int Lisp_Xinitialized
	 , Video_Inverted
	 , Bitmap_Pad
	 , Default_Depth;
extern unsigned long Black_Pixel
	           , White_Pixel;


XImage CursorImage;
Pixmap CursorPixmap_source
     , CursorPixmap_mask;
GC cursor_source_gc
 , cursor_mask_gc;
XColor cursor_fore_xcsd
     , cursor_back_xcsd
     , xced;
extern Colormap Colors;



/************************************************************************/
/*									*/
/*			i n i t _ X c u r s o r				*/
/*									*/
/*	Initialization code for X-windows cursors.			*/
/*									*/
/************************************************************************/

init_Xcursor(display)
     Display *display;
{

    TPRINT(( "TRACE: init_Xcursor()\n" ));

	XLOCK;	/* Take no X signals during this activity (ISC 386) */

    CursorImage.width   = CURSORWIDTH;
    CursorImage.height  = CURSORHEIGHT;
    CursorImage.xoffset = 0;
    CursorImage.format  = XYBitmap;
#if (defined (XV11R1) || defined(BYTESWAP))
    CursorImage.byte_order  = LSBFirst;
#else /* XV11R1 | BYTESWAP */

    CursorImage.byte_order  = MSBFirst;
#endif /* XV11R1 | BYTESWAP */


    CursorImage.bitmap_unit = BITSPER_DLWORD;
#ifdef AIX
    CursorImage.bitmap_pad  = 32;
#else
    CursorImage.bitmap_pad  = Bitmap_Pad;
#endif /* AIX */

    CursorImage.depth       = 1;
    CursorImage.bytes_per_line = BITSPER_DLWORD/8; 
    CursorImage.bitmap_bit_order = MSBFirst;

    CursorPixmap_source = XCreatePixmap( display, Lisp_Window.win
				, CURSORWIDTH, CURSORHEIGHT,
				1);
    CursorPixmap_mask   = XCreatePixmap( display, Lisp_Window.win
				, CURSORWIDTH, CURSORHEIGHT, 
				1);

    gcv.function = Video_Inverted ? GXcopyInverted : GXcopy;
    gcv.foreground = Black_Pixel;
    gcv.background = White_Pixel;
#ifdef AIX
    gcv.plane_mask = 1;
#endif /* AIX */


    cursor_source_gc = XCreateGC( display, Lisp_Window.win
				, GCForeground|GCBackground|GCFunction
#ifdef AIX
					|GCPlaneMask
#endif /* AIX */

				, &gcv );
    cursor_mask_gc   = XCreateGC( display, Lisp_Window.win
				, GCForeground|GCBackground|GCFunction
#ifdef AIX
					|GCPlaneMask
#endif /* AIX */

				, &gcv );

    XAllocNamedColor( display, Colors, "black" 
			, &cursor_fore_xcsd, &xced );
    XAllocNamedColor( display, Colors, "white" 
			, &cursor_back_xcsd, &xced );

	XUNLOCK;	/* OK to take signals again */

  } /* end init_Xcursor */



/************************************************************************/
/*									*/
/*			s e t _ X c u r s o r				*/
/*									*/
/*									*/
/*									*/
/************************************************************************/

set_Xcursor( display, bitmap, hotspot_x, hotspot_y, return_cursor, from_lisp )
     Display *display;
     unsigned char *bitmap;
     int hotspot_x
       , hotspot_y
       , from_lisp;
     Cursor *return_cursor;
  {

    extern unsigned char reversedbits[];
    unsigned char image[32];
    int i;
    Pixmap Cursor_src, Cursor_msk;

#ifdef BYTESWAP   
    if (from_lisp) for (i=0; i<32; i++) image[i] = reversedbits[bitmap[i^3]];
    else for ( i=0; i<32; i++) image[i] = reversedbits[bitmap[i]];
#else
    for ( i=0; i<32; i++) image[i] = reversedbits[bitmap[i]];
#endif /* BYTESWAP */


	XLOCK;

    Cursor_src = XCreatePixmapFromBitmapData(display, Lisp_Window.win,
						  image, 16, 16, 1, 0, 1),
    Cursor_msk = XCreatePixmapFromBitmapData(display, Lisp_Window.win,
						  image, 16, 16, 1, 0, 1);
#ifdef NEVER
#ifdef TRACE 
    printf( "TRACE: set_Xcursor()\n" );
#endif
    CursorImage.data = (char*) bitmap;

    XPutImage( display, CursorPixmap_source, cursor_source_gc
	     , &CursorImage, 0, 0, 0, 0, CURSORWIDTH, CURSORHEIGHT );
    XPutImage( display, CursorPixmap_mask  , cursor_mask_gc
	     , &CursorImage, 0, 0, 0, 0, CURSORWIDTH, CURSORHEIGHT );
#endif /* NEVER */


    *return_cursor = XCreatePixmapCursor( display
#ifdef NEVER
			, CursorPixmap_source, CursorPixmap_mask
#else
			, Cursor_src, Cursor_msk
#endif /* NEVER */

			, &cursor_fore_xcsd, &cursor_back_xcsd
			, hotspot_x, hotspot_y );

	/* Should free these now (doc says server may not copy them) */
	XFreePixmap(display, Cursor_src);
	XFreePixmap(display, Cursor_msk);

    XFlush( display );
    XUNLOCK;

  } /* end set_Xcursor */