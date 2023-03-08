/* @(#) MakeXicon.c Version 1.4 (4/16/91). copyright venue & Fuji Xerox  */
static char *id = "@(#) MakeXicon.c	1.4 4/16/91	(venue & Fuji Xerox)";



/************************************************************************/
/*									*/
/*	Copyright 1989, 1990, 1991 Venue				*/
/*									*/
/*	This file was work-product resulting from the Xerox/Venue	*/
/*	Agreement dated 18-August-1989 for support of Medley.		*/
/*									*/
/************************************************************************/




#include <stdio.h>

#include <X11/Xlib.h>
#include <X11/Xutil.h>

#include "dbprint.h"

#include "XVersion.h"
#include "MyWindow.h"
#include "Xicon.h"

extern Display *Xdisplay;
extern MyWindow Lisp_Window;
extern int Bitmap_Pad
		 , Default_Depth;

Pixmap IconPixmap;
XImage IconImage;



/************************************************************************/
/*									*/
/*			m a k e _ X i c o n				*/
/*									*/
/*	Make the icon for the shrunken Medley window.			*/
/*									*/
/************************************************************************/

make_Xicon()
  {
    TPRINT(( "TRACE: make_Xicon()\n" ));

    IconImage.width = Lisp_icon_width;
    IconImage.height = Lisp_icon_height;
    IconImage.xoffset = 0;
    IconImage.format  = XYBitmap;
    IconImage.data    = (char*) Lisp_icon;
#if (defined(XV11R1) || defined(BYTESWAP))
    IconImage.byte_order  = LSBFirst;
#else XV11R1 | BYTESWAP
    IconImage.byte_order  = MSBFirst;
#endif XV11R1 | BYTESWAP
    IconImage.bitmap_unit = 8;
    IconImage.bitmap_pad  = Bitmap_Pad;
    IconImage.depth       = 1;
    IconImage.bytes_per_line = Lisp_icon_width/8;
#if defined(X_ICON_IN_X_BITMAP_FORMAT)
    IconImage.bitmap_bit_order = LSBFirst;
#else
    IconImage.bitmap_bit_order = MSBFirst;
#endif

    IconPixmap = XCreatePixmap( Xdisplay, Lisp_Window.win
                                , Lisp_icon_width , Lisp_icon_height
				, Default_Depth );

    XPutImage( Xdisplay, IconPixmap, *(Lisp_Window.gc), &IconImage
			, 0, 0, 0, 0
                        , Lisp_icon_width, Lisp_icon_height );

  } /* end make_Xicon */
