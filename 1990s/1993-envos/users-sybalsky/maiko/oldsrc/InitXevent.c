/* @(#) InitXevent.c Version 1.3 (1/25/91). copyright venue & Fuji Xerox  */
static char *id = "@(#) InitXevent.c	1.3 1/25/91	(venue & Fuji Xerox)";
/*
*
*
* Copyright (C) 1988 by Fuji Xerox co.,Ltd. All rights reserved.
*
*		Author: Mitsunori Matsuda
*		Date  : August 18, 1988
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

#include "MyWindow.h"
#include "dbprint.h"

extern Display *Xdisplay;
extern MyWindow *Head_of_Windows;

init_Xevent()
  {	
    MyWindow *window;
    TPRINT(("TRACE: init_Xevent()\n"));
    window = Head_of_Windows;

    while (window)
      {
	XSelectInput(Xdisplay, window->win, window->event_mask);
	window = window->next;
      } /*end while */

    if (Head_of_Windows) XFlush(Xdisplay);

  } /*end init_Xevent */