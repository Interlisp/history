/* @(#) Xevinit.c Version 1.2 (2/8/93). copyright venue & Fuji Xerox  */
static char *id = "@(#) Xevinit.c	1.2 2/8/93	(venue & Fuji Xerox)";



/*
*
*
*		Author: Mitsunori Matsuda
*		Date  : August 18, 1988
*/




/************************************************************************/
/*									*/
/*	(C) Copyright 1989-92 Venue. All Rights Reserved.		*/
/*	Manufactured in the United States of America.			*/
/*									*/
/*	The contents of this file are proprietary information 		*/
/*	belonging to Venue, and are provided to you under license.	*/
/*	They may not be further distributed or disclosed to third	*/
/*	parties without the specific permission of Venue.		*/
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