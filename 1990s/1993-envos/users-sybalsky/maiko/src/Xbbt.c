/* @(#) Xbbt.c Version 1.7 (2/8/93). copyright venue & Fuji Xerox  */
static char *id = "@(#) Xbbt.c	1.7 2/8/93	(venue & Fuji Xerox)";
/*
*
*
* Copyright (C) 1988 by Fuji Xerox co.,Ltd. All rights reserved.
*
*		Author: Mitsunori Matsuda
*		Date  : August 11, 1988
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
#include "dbprint.h"

#define FALSE 0
#define TRUE  !FALSE

extern Display *Xdisplay;
extern XImage XScreenBitmap;
extern MyWindow Lisp_Window
	      , Display_Window;
extern DisplayArea ScreenRegion;



#define Xbitblt(display, x,y,w,h)			\
  {						\
    XLOCK;									\
	XPutImage( display, Display_Window.win,	\
	       *(Display_Window.gc),		\
	       &XScreenBitmap,			\
	       x , y, x - ScreenRegion.left_x,	\
	      y - ScreenRegion.top_y, w, h );	\
	XFlush(display);						\
	XUNLOCK;								\
  } 



/************************************************************************/
/*									*/
/*		    c l i p p i n g _ X b i t b l t			*/
/*									*/
/*	BITBLT from the display region to the X server's display,	*/
/*	clipping to fit the window we're in on the server.		*/
/*									*/
/************************************************************************/

clipping_Xbitblt(x,y,w,h)
  int x, y, w, h;
  { 
    int temp_x, temp_y; 

    TPRINT(( "TRACE: clipping_Xbitblt()\n" ));

    temp_x = x + w - 1; 
    temp_y = y + h - 1; 

    if ( (temp_x < ScreenRegion.left_x) 
	 || (x > ScreenRegion.right_x) 
	 || (temp_y < ScreenRegion.top_y) 
	 || (y > ScreenRegion.bottom_y)) return; 
	
    if ( ( x >= ScreenRegion.left_x ) 
	 && ( temp_x <= ScreenRegion.right_x ) 
	 && ( y >= ScreenRegion.top_y ) 
	 && ( temp_y <= ScreenRegion.bottom_y ) )
      { 
	Xbitblt(Xdisplay, x, y, w, h ); 
	return; 
      }
 
    if ( x < ScreenRegion.left_x )
      { 
	w -= ScreenRegion.left_x - x; 
	x = ScreenRegion.left_x; 
      }
 
    if ( temp_x > ScreenRegion.right_x ) w -= temp_x - ScreenRegion.right_x; 
 
    if ( y < ScreenRegion.top_y )
      { 
	h -= ScreenRegion.top_y - y; 
	y = ScreenRegion.top_y; 
      }
 
    if ( temp_y > ScreenRegion.bottom_y ) h -= temp_y - ScreenRegion.bottom_y; 
 
    if ((w>0) && (h>0)) Xbitblt(Xdisplay, x, y, w, h ); 

  } /* end clipping_Xbitblt */


/************************************************************************/
/*									*/
/*			r e f r e s h _ X s c r e e n			*/
/*									*/
/*	Redisplay the X display completely.				*/
/*									*/
/************************************************************************/

refresh_Xscreen(display)
     Display *display;
  {
    TPRINT(( "TRACE: refresh_Xscreen()\n" ));

    Xbitblt( display,
	    ScreenRegion.left_x
	   , ScreenRegion.top_y
	   , Display_Window.width
	   , Display_Window.height );

  } /* end refresh_Xscreen */
