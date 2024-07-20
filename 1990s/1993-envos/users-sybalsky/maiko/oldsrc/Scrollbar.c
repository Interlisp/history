/* @(#) Scrollbar.c Version 1.4 (9/18/90). copyright venue & Fuji Xerox  */
static char *id = "@(#) Scrollbar.c	1.4 9/18/90	(venue & Fuji Xerox)";
/*
*
*
* Copyright (C) 1988 by Fuji Xerox co.,Ltd. All rights reserved.
*
*		Author: Mitsunori Matsuda
*		Date  : September 5, 1988
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

#include "dbprint.h"

#include "XVersion.h"
#include "MyWindow.h"

extern Display *Xdisplay;
extern MyWindow Vert_Scroll_Bar
	      , Horiz_Scroll_Bar;
extern DisplayArea ScreenRegion;
extern int LispDisplayWidth
	 , LispDisplayHeight
	 , Scroll_Width
	 , Default_Depth
	 , Scroll_Border;

extern MyWindow Lisp_Window;

Pixmap ScrollBar_Pixmap = NULL;


/************************************************************************/
/*									*/
/*	        B e f o r e _ C r e a t e S c r o l l b a r		*/
/*									*/
/*	Called before a scroll bar is created for the X main window.	*/
/*									*/
/************************************************************************/

Before_CreateScrollbar( parent, child )
  MyWindow *parent, *child;
  {
    float temp;

    TPRINT(( "TRACE: Before_CreateScrollbar()\n" ));
	
    child->border = 1; 			/* fixed width */

    if( child == &Vert_Scroll_Bar )
      {
	int height;
/* commented
	child->x     = 1 + child->border;
*/
	child->x     = child->border;
	child->width = parent->width - 2*(1 + child->border);

	height = parent->parent->height 
		- (Scroll_Width + 2*Scroll_Border) - 1;
	temp = (float)ScreenRegion.top_y / (float)LispDisplayHeight;
/* commented
	child->y = (1 + child->border)
			+ (int)((float)((height - Scroll_Border)
						- 2*(1 + child->border))
					* temp);
*/
	child->y = child->border
			+ (int)((float)((height - Scroll_Border)
						- 2*child->border)
					* temp);
	temp = (float)height / (float)LispDisplayHeight;
/* commented
	child->height = (int)((float)(height - 2*(1 + child->border)) 
						* temp);
*/
	child->height = (int)((float)(height - 2*child->border) 
					* temp);

      } 
    else if( child == &Horiz_Scroll_Bar )
      {

	int width;
/* commented
	child->y      = 1 + child->border;
*/
	child->y      = child->border;
	child->height = parent->height - 2*(1 + child->border);

	width = parent->parent->width 
		- (Scroll_Width + 2*Scroll_Border);
	temp = (float)ScreenRegion.left_x / (float)LispDisplayWidth;
/* commented
	child->x = (1 + child->border)
			+ (int)((float)((width - Scroll_Border)
						- 2*(1 + child->border))
					* temp);
*/ 
	child->x = child->border
			+ (int)((float)((width - Scroll_Border)
						- 2*child->border)
					* temp);
	temp = (float)width / (float)LispDisplayWidth;
/* commented
	child->width = (int)((float)((width - Scroll_Border)
						- 2*(1 + child->border))
					* temp);
*/
	child->width = (int)((float)((width - Scroll_Border)
							- 2*child->border)
						* temp) - 1;

      } /* end if */

  } /* end Before_CreateScrollbar */



/************************************************************************/
/*									*/
/*									*/
/*									*/
/*									*/
/*									*/
/************************************************************************/

#include "Stipple.h"

After_CreateScrollbar( parent, child )
MyWindow *parent
       , *child;
  {
    TPRINT(( "TRACE: After_CreateScrollbar()\n" ));

    XMapWindow( Xdisplay, child->win );

#ifdef NEVER
    if( !ScrollBar_Pixmap )
	ScrollBar_Pixmap = XCreateBitmapFromData( Xdisplay
						  , Lisp_Window.win
						  , check_bits
						  , check_width
						  , check_height );

#else
    if (!ScrollBar_Pixmap)
      ScrollBar_Pixmap = XCreatePixmapFromBitmapData( Xdisplay,
						      Lisp_Window.win,
						      check_bits,
						      check_width,
						      check_height,
						      1, 0, Default_Depth);
#endif NEVER

    XSetWindowBackgroundPixmap( Xdisplay, child->win, ScrollBar_Pixmap );
    XClearWindow( Xdisplay, child->win );

  } /* end After_CreateScrollbar */



/************************************************************************/
/*									*/
/*									*/
/*									*/
/*									*/
/*									*/
/************************************************************************/

Before_ResizeScrollbar( window )
MyWindow *window;
  {
    float temp;
    TPRINT(( "TRACE: Before_ResizeScrollbar()\n" ));
	
    if( window == &Vert_Scroll_Bar )
      {
	int height;

	height = window->parent->parent->height 
		- (Scroll_Width + 2*Scroll_Border);
	temp = (float)ScreenRegion.top_y / (float)LispDisplayHeight;
/* commented
	window->y = (1 + window->border)
			+ (int)((float)((height - Scroll_Border)
					      - 2*(1 + window->border))
					* temp);
*/
	window->y = window->border
			+ (int)((float)((height - Scroll_Border)
					      - 2*window->border)
					* temp);
	temp = (float)height / (float)LispDisplayHeight;
/* commented
	window->height = (int)((float)((height - Scroll_Border)
					     - 2*(1 + window->border)) 
					* temp);
*/
	window->height = (int)((float)((height - Scroll_Border)
					     - 2*window->border) 
					* temp) - 1;

      } 
    else if( window == &Horiz_Scroll_Bar )
      {
	int width;

	width = window->parent->parent->width 
		- (Scroll_Width + 2*Scroll_Border);
	temp = (float)ScreenRegion.left_x / (float)LispDisplayWidth;
/* commented
	window->x = (1 + window->border)
			+ (int)((float)((width - Scroll_Border)
					- 2*(1 + window->border))
					*temp);
*/
	window->x = window->border
			+ (int)((float)((width - Scroll_Border)
					- 2*window->border)
					*temp);
	temp = (float)width / (float)LispDisplayWidth;
/* commented
	window->width = (int)((float)((width - Scroll_Border)
					- 2*(1 + window->border)) 
					* temp);
*/
	window->width = (int)((float)((width - Scroll_Border)
					- 2*window->border) 
					* temp) - 1;

      } /* end if */


  } /* Before_ResizeScrollbar */



/************************************************************************/
/*									*/
/*									*/
/*									*/
/*									*/
/*									*/
/************************************************************************/

After_ResizeScrollbar( window )
  MyWindow *window;
  {
    TPRINT(( "TRACE: After_ResizeScrollbar()\n" ));
	
    if( window == &Vert_Scroll_Bar )
      {
      } 
    else 
      { 
      }

  } /* After_ResizeScrollbar */



/************************************************************************/
/*									*/
/*									*/
/*									*/
/*									*/
/*									*/
/************************************************************************/

Move_ScrollBar( direction )
  int direction;
  {
    TPRINT(( "TRACE: Reconf_ScrollBar()\n" ));

    if( direction == VERTICAL )
      {
	ResizeWindow( &Vert_Scroll_Bar );
      }
    else
      { /* direction == HORIZONTAL */
	ResizeWindow( &Horiz_Scroll_Bar );
      } /* end if(direction) */

  } /* end Move_ScrollBar */