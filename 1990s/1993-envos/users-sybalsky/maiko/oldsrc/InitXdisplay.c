/* %Z% %M% Version %I% (%G%). copyright venue & Fuji Xerox  */
static char *id = "%Z% %M%	%I% %G%	(venue & Fuji Xerox)";
/*
*
*
* Copyright (C) 1988 by Fuji Xerox co.,Ltd. All rights reserved.
*
*		Author: Mitsunori Matsuda
*		Date  : August 10, 1988
*/

#include <stdio.h>

#define FALSE 0 
#define TRUE  !FALSE

int Lisp_Xinitialized = FALSE;

init_Xdisplay()
{
#ifdef TRACE
        printf( "TRACE: init_Xdisplay()\n" );
#endif

        if( !Lisp_Xinitialized ) {

		Open_Display();		/* Connect to Window-Server */
		Create_LispWindow();	/* Make Window for Lisp */

		Lisp_Xinitialized = TRUE;
	} /* end if */

} /* end init_Xdisplay() */