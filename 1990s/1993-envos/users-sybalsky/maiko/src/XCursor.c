/* @(#) XCursor.c Version 1.4 (9/18/90). copyright venue & Fuji Xerox  */
static char *id = "@(#) XCursor.c	1.4 9/18/90	(venue & Fuji Xerox)";



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
*		Date  : August 12, 1988
*/

#include <stdio.h>

#include <X11/Xlib.h>
#include <X11/Xutil.h>

#include "lispemul.h"
#include "iopage.h"
#include "display.h"
#include "dbprint.h"

#include "XVersion.h"
#include "MyWindow.h"

extern IOPAGE   *IOPage;
extern Display  *Xdisplay;
extern MyWindow Lisp_Window;

/* a simple linked list to remember X cursors */
struct MXCURSOR {
  struct MXCURSOR *next;
  DLword bitmap[CURSORHEIGHT];
  Cursor Xid;
} *cursorlist = NULL;

/*
Cursor LispCursor[2];
int    cursor_sw;
*/


/************************************************************************/
/*									*/
/*			I n i t _ X C u r s o r				*/
/*									*/
/*	Initial setup for X cursor handling--create an initial		*/
/*	cursor, and get it displayed.					*/
/*									*/
/************************************************************************/

Init_XCursor()
  {
  int i;
  DLword *newbm = (DLword *) (IOPage->dlcursorbitmap);

    TPRINT(( "TRACE: Init_DisplayCursor()\n" ));
/*
    cursor_sw = 0;
    set_Xcursor( Xdisplay, (char*) (IOPage->dlcursorbitmap)
		 , 0, 0, &LispCursor[cursor_sw], 1 );
    DefineCursor( &Lisp_Window, &LispCursor[cursor_sw] );
    cursor_sw += 1;
*/

  /* this is guaranteed to be our first cursor, isn't it? */
  cursorlist = (struct MXCURSOR *) malloc(sizeof(struct MXCURSOR));
  cursorlist->next = NULL;
  for(i=0; i<CURSORHEIGHT; i++)
    cursorlist->bitmap[i] = newbm[i];
  set_Xcursor( Xdisplay, newbm, 0, 0, &(cursorlist->Xid), 1);
  DefineCursor(Xdisplay, &Lisp_Window, &(cursorlist->Xid));
  
  } /* end Init_XCursor */






/************************************************************************/
/*									*/
/*			S e t _ X C u r s o r				*/
/*									*/
/*	Set the X cursor from the Lisp bitmap, and move it to (x, y).	*/
/*									*/
/************************************************************************/

Set_XCursor( x, y )
  int x, y;
  {
/*
    Cursor *old_cursor;
*/
  /* compare cursor in IOPage memory with cursors we've seen before */
  register struct MXCURSOR *clp, *clbp;
  register DLword *newbm = ((DLword *) (IOPage->dlcursorbitmap));
  register int i;

    TPRINT(( "TRACE: Set_DisplayCursor()\n" ));
/*
    old_cursor = Lisp_Window.cursor;

    set_Xcursor( Xdisplay, (char*) (IOPage->dlcursorbitmap)
		 , 0, 0, &LispCursor[cursor_sw], 1 );
    DefineCursor( &Lisp_Window, &LispCursor[cursor_sw] );
    XFreeCursor( Xdisplay, *old_cursor );

    cursor_sw = cursor_sw ? 0 : 1;
*/
  XLOCK;	/* No signals while setting the cursor */
  for(clp = cursorlist; clp != NULL; clbp = clp, clp = clp->next) {
    for(i=0; i< CURSORHEIGHT; i++)
      if(clp->bitmap[i] != newbm[i]) break;
    if(i == CURSORHEIGHT) break;
  }

  if(clp == NULL) {    /* it isn't there, push on a new one */
    clp = (struct MXCURSOR *) malloc(sizeof (struct MXCURSOR));
    /* and fill it up with the current new cursor */
    for(i=0; i< CURSORHEIGHT; i++)
      clp->bitmap[i] = newbm[i];
    set_Xcursor( Xdisplay, newbm, 0, 0, &(clp->Xid), 1);
    clp->next = cursorlist;
    cursorlist = clp;
  }
  else
    /* found it, move it to the front of the list
       (this should reduce search time on the average by keeping
       the popular cursors near the front of the list)
       */
    if(clp != cursorlist) {  /* don't move if it's already there */
      clbp->next = clp->next;
      clp->next = cursorlist;
      cursorlist = clp;
    }
    DefineCursor(Xdisplay, &Lisp_Window, &(clp->Xid));
    XUNLOCK;	/* Signals OK now */

  } /* end Set_XCursor */