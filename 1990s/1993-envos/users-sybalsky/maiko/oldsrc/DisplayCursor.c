/* %Z% %M% Version %I% (%G%). copyright venue & Fuji Xerox  */
static char *id = "%Z% %M%	%I% %G%	(venue & Fuji Xerox)";
/*
*
*
* Copyright (C) 1988 by Fuji Xerox co.,Ltd. All rights reserved.
*
*		Author: Mitsunori Matsuda
*		Date  : August 12, 1988
*/

#include <stdio.h>

#include <X11/Xlib.h>
#include <X11/Xutil.h>

#include "lispemul.h"
#include "iopage.h"

#include "XVersion.h"
#include "MyWindow.h"

extern IOPAGE   *IOPage;
extern Display  *Xdisplay;
extern MyWindow Lisp_Window;

Cursor LispCursor[2];
int    cursor_sw;

Init_XCursor()
{
#ifdef TRACE
	printf( "TRACE: Init_DisplayCusrosr()\" );
#endif
	cursor_sw = 0;
	set_Xcursor( (char*) (IOPage->dlcursorbitmap)
			, 0, 0, &LispCursor[cursor_sw] );
	DefineCursor( &Lisp_Window
			, &LispCursor[cursor_sw] );
	cursor_sw += 1;

} /* end Init_XCursor */

Set_XCursor( x, y )
int x
  , y;
{
	Cursor *old_cursor;
#ifdef TRACE
	printf( "TRACE: Set_DisplayCusrosr()\" );
#endif
	old_cursor = Lisp_Window.cursor;

	set_Xcursor( (char*) (IOPage->dlcursorbitmap)
			, 0, 0, &LispCursor[cursor_sw] );
	DefineCursor( &Lisp_Window
			, &LispCursor[cursor_sw] );
	XFreeCursor( Xdisplay, *old_cursor );

	cursor_sw = cursor_sw ? 0 : 1;

} /* end Set_XCursor */