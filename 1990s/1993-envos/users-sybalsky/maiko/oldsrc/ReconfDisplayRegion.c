/* %Z% %M% Version %I% (%G%). copyright venue & Fuji Xerox  */
static char *id = "%Z% %M%	%I% %G%	(venue & Fuji Xerox)";
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

#define FALSE  0
#define TRUE   !FALSE

extern DisplayArea ScreenRegion;
extern MyWindow Display_Window;
extern int Bit_Gravity
	 , LispDisplayWidth
	 , LispDisplayHeight;

static int vertical   = VERTICAL
         , horizontal = HORIZONTAL;

Reconf_ScreenRegion()
{
	int flag;

#ifdef TRACE
	printf( "TRACE: Reconf_ScreenRegion()\" );
#endif

	switch( Bit_Gravity ) {
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

	if( ScreenRegion.left_x < 0 ) {
		ScreenRegion.left_x = 0;
		ScreenRegion.right_x = Display_Window.width - 1;
		flag = TRUE;
	}
	if( ScreenRegion.top_y < 0 ) {
		ScreenRegion.top_y = 0;
		ScreenRegion.bottom_y = Display_Window.height - 1;
		flag = TRUE;
	}
	if( ScreenRegion.right_x >= LispDisplayWidth ) {
		ScreenRegion.right_x = LispDisplayWidth - 1;
		ScreenRegion.left_x = ScreenRegion.right_x 
					- Display_Window.width + 1;
		flag = TRUE;
	}
	if( ScreenRegion.bottom_y >= LispDisplayHeight ) {
		ScreenRegion.bottom_y = LispDisplayHeight - 1;
		ScreenRegion.top_y = ScreenRegion.bottom_y 
					- Display_Window.height + 1;
		flag = TRUE;
	}

	if( flag ) {
		refresh_Xscreen();
	} /* end if(flag) */

	Move_ScrollBar( vertical );
	Move_ScrollBar( horizontal );

} /* end Reconf_ScreenRegion */