/* @(#) GravityWindow.c Version 1.2 (4/19/90). copyright venue & Fuji Xerox  */
static char *id = "@(#) GravityWindow.c	1.2 4/19/90	(venue & Fuji Xerox)";
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

#include "Xcursdef.h"
#include "Xdefcur.h"

extern Display *Xdisplay;
extern MyWindow Lisp_Window
	      , Grav_Window[];
extern int Bit_Gravity
	 , Scroll_Width
	 , Default_Depth
	 , Scroll_Border;

Cursor DefaultCursor = NULL;
Pixmap GravityOn_Pixmap
     , GravityOff_Pixmap;


/************************************************************************/
/*									*/
/*		     B e f o r e _ C r e a t e G r a v			*/
/*									*/
/*									*/
/*									*/
/************************************************************************/

Before_CreateGrav( parent, child )
MyWindow *parent
       , *child;
  {
    TPRINT(( "TRACE: Before_CreateGrav()\n" ));

    { int i;
      for( i=0; i<2; i++)
	{ int j;
	  for( j=0; j<2; j++ )
	    {
	      if( child == &Grav_Window[i*2+j] )
		{
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



/************************************************************************/
/*									*/
/*			A f t e r _ C r e a t e G r a v			*/
/*									*/
/*									*/
/*									*/
/************************************************************************/

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

    TPRINT(( "TRACE: After_CreateGrav()\n" ));
	
    if( !DefaultCursor )
      {
	set_Xcursor( Xdisplay,
		    (char*)default_cursor.cuimage
			, (int)default_cursor.cuhotspotx
			, (int)(15 - default_cursor.cuhotspoty)
			, &DefaultCursor );
      } /* end if */

#ifdef NEVER
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

#else
    if (!GravityOn_Pixmap)
      GravityOn_Pixmap = XCreatePixmapFromBitmapData(Xdisplay,
						 Lisp_Window.win,
						 check_bits,
						 16, 16, 1, 0,
						 Default_Depth);

    if (!GravityOff_Pixmap)
      GravityOff_Pixmap = XCreatePixmapFromBitmapData(Xdisplay,
						  Lisp_Window.win,
						  plain_bits,
						  16, 16, 1, 0, 
						  Default_Depth);
#endif /* NEVER */


    if( Bit_Gravity == NorthWestGravity ) win = North_West;
    if( Bit_Gravity == NorthEastGravity ) win = North_East;
    if( Bit_Gravity == SouthWestGravity ) win = South_West;
    if( Bit_Gravity == SouthEastGravity ) win = South_East;

    if( child == &Grav_Window[win] )
      {
	XSetWindowBackgroundPixmap( Xdisplay
				, child->win
				, GravityOn_Pixmap );
      }
    else
      {
	XSetWindowBackgroundPixmap( Xdisplay
					, child->win
					, GravityOff_Pixmap );
      } /* end if */

    XMapWindow( Xdisplay, child->win );
    Add_WindowList( child );

    DefineCursor( Xdisplay, child, &DefaultCursor );	

  } /* end After_CreatGrav */



/************************************************************************/
/*									*/
/*									*/
/*									*/
/*									*/
/*									*/
/************************************************************************/

Before_ResizeGrav( window )
  MyWindow *window;
  {
    int i;

    TPRINT(( "TRACE: Before_ResizeGrav()\n" ));

    for( i=0; i<2; i++ )
      { int j;
	for( j=0; j<2; j++ )
	  {
	    if( window == &Grav_Window[i*2+j] )
	      {
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

} /* Before_ResizeGrav */



/************************************************************************/
/*									*/
/*									*/
/*									*/
/*									*/
/*									*/
/************************************************************************/

After_ResizeGrav( window )
  MyWindow *window;
  {
    TPRINT(( "TRACE: After_ResizeGrav()\n" ));
  } /* After_ResizeGrav */

