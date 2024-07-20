/*
*
*
* Copyright (C) 1990 by Venue. All rights reserved.
*
*		Author: Bob Bane
*		Date  : July 1990
*
*   Assorted hacks used to speed up Medley X display by letting X server
*    draw stuff instead of flushing bits from the Image
*
*/


#include <X11/Xlib.h>
#include <X11/Xutil.h>

#include "XVersion.h"
#include "MyWindow.h"

#define FALSE 0
#define TRUE  !FALSE

extern Display *Xdisplay;
extern XImage XScreenBitmap;
extern MyWindow Lisp_Window
	      , Display_Window;
extern DisplayArea ScreenRegion;
extern int Video_Inverted;

/* file globals used to cache lineGC parameters */

GC lineGC;
int lineGCfunction;
extern XGCValues gcv;


/************************************************************************/
/* lXs{mumble} is the pile of functions called by the various           */
/* displaystream functions and does equivalent X things to draw on the  */
/* screen instead of the usual flush-the-bounding-box strategy.         */
/************************************************************************/
/* There are some bogus global dependencies here. -jarl */

lXsinit()
{
    gcv.function = lineGCfunction = GXset;
    lineGC = XCreateGC(Xdisplay, Display_Window.win,
		       GCForeground|GCBackground|GCFunction,
		       &gcv);
  }

/* lispXdraw_line is called in draw.c from N_OP_drawline to draw simple lines
   instead of flushing the bounding box; this wins BIG for diagonal lines and
   small for horizontal and vertical lines
*/

lispXdraw_line(x1, y1, x2, y2, mode)
int x1, y1, x2, y2, mode;
  {
    int drawfun;
  /* coordinates are in screen space; must convert to window space */
  /* mode: 0 - draw black,
           1 - draw white,
	   2 - draw inverted
     Mode + whether-or-not-we're-in-inverse-video selects a GC for us */
  /* No clipping necessary here; line was clipped by N_OP_drawline */

  x1 -= ScreenRegion.left_x;
  x2 -= ScreenRegion.left_x;
  y1 -= ScreenRegion.top_y;
  y2 -= ScreenRegion.top_y;

  switch(mode) {
  case 0: drawfun = (Video_Inverted? GXclear: GXset); break;
  case 1: drawfun = (Video_Inverted? GXset: GXclear); break;
  case 2: drawfun = GXinvert; break;
  }
  if(lineGCfunction != drawfun)
    XSetFunction(Xdisplay, lineGC, lineGCfunction = drawfun);

  XDrawLine(Xdisplay, Display_Window.win,
	    lineGC,
	    x1, y1, x2, y2);
}