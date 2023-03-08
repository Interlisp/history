/* @(#) Xwinman.c Version 1.3 (4/27/92). copyright venue & Fuji Xerox  */
static char *id = "@(#) Xwinman.c	1.3 4/27/92	(venue & Fuji Xerox)";


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
*		Date  : August 22, 1988
*/

#include <stdio.h>

#include <X11/Xlib.h>
#include <X11/Xutil.h>

#include "XVersion.h"
#include "MyWindow.h"
#include "dbprint.h"

#define FALSE 0
#define TRUE  !FALSE

extern XAnyEvent report;
extern MyWindow *Head_of_Windows;

/* int Next_Event_req;	removed JDS 7/6/90 keyboard speedup */



/************************************************************************/
/*									*/
/*									*/
/*									*/
/*									*/
/*									*/
/************************************************************************/

Add_WindowList( window )
MyWindow *window;
{
	MyWindow *temp;

	TPRINT(( "TRACE: Add_Window()\n" ));

	if( !Head_of_Windows ) {
		Head_of_Windows = window;
	} else {
		temp = Head_of_Windows;
		while( temp->next ) {
			temp = temp->next;
		}
		temp->next = window;
	} /* end if */
	window->next = NULL;

} /* end Add_Window */



/************************************************************************/
/*									*/
/*									*/
/*									*/
/*									*/
/*									*/
/************************************************************************/

AddTop_WindowList( window )
MyWindow *window;
{
	TPRINT(( "TRACE: AddTop_Window()\n" ));

	window->next = Head_of_Windows;
	Head_of_Windows = window;

} /* end AddTop_Window */




/************************************************************************/
/*									*/
/*									*/
/*									*/
/*									*/
/*									*/
/************************************************************************/

Remove_WindowList( window )
MyWindow *window;
{
	MyWindow *temp1
	       , *temp2;

	TPRINT(( "TRACE: Remove_Window()\n" ));

	if( Head_of_Windows ) {
		if( Head_of_Windows == window ) {
			Head_of_Windows = window->next;
			window->next = NULL;
		} else {
			temp2 = Head_of_Windows;
			temp1 = Head_of_Windows->next;
			while( temp1 ) {
				if( temp1 == window ) {
					temp2->next = temp1->next;
					window->next = NULL;
					break;
				}
				temp2 = temp1;
				temp1 = temp1->next;
			} /* end while */
		} /* end if */
	} /* end if */

} /* end Remove_Window */



/************************************************************************/
/*									*/
/*									*/
/*									*/
/*									*/
/*									*/
/************************************************************************/

getXsignaldata(display)
     Display *display;
  {
    MyWindow *window;
    TPRINT(( "TRACE: getXsignaldata()\n" ));
    /* Next_Event_req = TRUE; removed JDS 7/6/90 keybaord speedup */
    while(/* Next_Event_req &&*/ XPending( display ) )
      {
	/* Next_Event_req = FALSE; removed JDS 7/6/90 keybaord speedup */
	XNextEvent( display, &report );
	window = Head_of_Windows;
	while( window )
	  {
	    if( report.window == window->win )
	      {
		if( window->event_func )
		    (window->event_func)(&report,window);
		break; /* exit while */
	      } /* end if */
	    window = window->next;
	  } /* end while */
      } /* end if */

  } /* end getXsignaldata() */



/************************************************************************/
/*									*/
/*									*/
/*									*/
/*									*/
/*									*/
/************************************************************************/

DispatchXhandler( event, window ) /* General event handler */
  XAnyEvent *event;
  MyWindow *window;
  {
    MyEvent *temp;

    TPRINT(( "TRACE: DispatchXhandler()\n" ));

    temp = window->event_head;

    while( temp )
      {
	if( event->type == temp->type )
	  {
	    if( temp->func )
	      {
		(temp->func)( event, window );
	      }
	    /* break; */
	    return;
	  } /* end if */
	temp = temp->next;
      } /* end while */

    DBPRINT(( "DispatchXhandler(): Unexpected event type %d\n",
	      event->type ));

  } /* end DispatchXhandler */



/************************************************************************/
/*									*/
/*									*/
/*									*/
/*									*/
/*									*/
/************************************************************************/

Bool isXeventtype( display, event, type )
  Display *display;
  XEvent *event;
  {

    TPRINT(( "TRACE: isXeventtype()\n" ));

    if( event->type == type ) return( True );
    else return( False );

  } /* end isXeventtype */

