/* @(#) XReconfig.c Version 1.4 (1/25/91). copyright venue & Fuji Xerox  */
static char *id = "@(#) XReconfig.c	1.4 1/25/91	(venue & Fuji Xerox)";




/************************************************************************/
/*									*/
/*	Copyright 1989, 1990 Venue, Fuji Xerox Co., Ltd, Xerox Corp.	*/
/*									*/
/*	This file is work-product resulting from the Xerox/Venue	*/
/*	Agreement dated 18-August-1989 for support of Medley.		*/
/*									*/
/************************************************************************/

/*
*
*
* Copyright (C) 1988 by Fuji Xerox co.,Ltd. All rights reserved.
*
*		Author: Mitsunori Matsuda
*		Date  : August 11, 1988
*/

#include <stdio.h>

#include <X11/Xlib.h>
#include <X11/Xutil.h>

#include "XVersion.h"
#include "MyWindow.h"
#include "dbprint.h"

#define FALSE  0
#define TRUE   !FALSE

extern DisplayArea ScreenRegion;
extern MyWindow Display_Window;
extern int Bit_Gravity
	 , Backing_Store
	 , LispDisplayWidth
	 , LispDisplayHeight;

static int vertical   = VERTICAL
         , horizontal = HORIZONTAL;



/************************************************************************/
/*									*/
/*									*/
/*	Reconfigure the screen-region, to account for window-size	*/
/*									*/
/*									*/
/************************************************************************/

Reconf_ScreenRegion()
{
    int flag;

    TPRINT(( "TRACE: Reconf_ScreenRegion()\n" ));

    switch( Bit_Gravity )
      {
	case NorthWestGravity:
		ScreenRegion.right_x = ScreenRegion.left_x 
					+ Display_Window.width - 1;
		ScreenRegion.bottom_y = ScreenRegion.top_y
					+ Display_Window.height - 1;
		break;
	case NorthEastGravity:
		ScreenRegion.left_x = ScreenRegion.right_x 
					- Display_Window.width + 1;
		ScreenRegion.bottom_y = ScreenRegion.top_y
					+ Display_Window.height - 1;
		break;
	case SouthWestGravity:
		ScreenRegion.right_x = ScreenRegion.left_x 
					+ Display_Window.width - 1;
		ScreenRegion.top_y = ScreenRegion.bottom_y
					- Display_Window.height + 1;
		break;
	case SouthEastGravity:
		ScreenRegion.left_x = ScreenRegion.right_x 
					- Display_Window.width + 1;
		ScreenRegion.top_y = ScreenRegion.bottom_y
					- Display_Window.height + 1;

		break;
	default:
		fprintf( stderr
			, "Reconf_ScreenRegion(): Undefined Gravity\n" );
		break;
      } /* end switch */

    /* Adjust Display Region */
    flag = FALSE;

    if( ScreenRegion.left_x < 0 )
      {
	ScreenRegion.left_x = 0;
	ScreenRegion.right_x = Display_Window.width - 1;
	flag = TRUE;
      }

    if( ScreenRegion.top_y < 0 )
      {
	ScreenRegion.top_y = 0;
	ScreenRegion.bottom_y = Display_Window.height - 1;
	flag = TRUE;
      }

    if( ScreenRegion.right_x >= LispDisplayWidth )
      {
	ScreenRegion.right_x = LispDisplayWidth - 1;
	ScreenRegion.left_x = ScreenRegion.right_x 
				- Display_Window.width + 1;
	flag = TRUE;
      }

    if( ScreenRegion.bottom_y >= LispDisplayHeight )
      {
	ScreenRegion.bottom_y = LispDisplayHeight - 1;
	ScreenRegion.top_y = ScreenRegion.bottom_y 
				- Display_Window.height + 1;
	flag = TRUE;
      }

    if (Backing_Store) flag = TRUE; /* always have to refresh, since */
				    /* we get no "Expose" Events. */

    if( flag ) refresh_Xscreen();

    Move_ScrollBar( vertical );
    Move_ScrollBar( horizontal );

  } /* end Reconf_ScreenRegion */