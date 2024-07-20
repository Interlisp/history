/* %Z% %M% Version %I% (%G%). copyright venue & Fuji Xerox  */
static char *id = "%Z% %M%	%I% %G%	(venue & Fuji Xerox)";
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

#define FALSE 0
#define TRUE  !FALSE

extern Display *Xdisplay;
extern XAnyEvent report;
extern MyWindow *Head_of_Windows;

int Next_Event_req;

Add_WindowList( window )
MyWindow *window;
{
	MyWindow *temp;
#ifdef TRACE
	printf( "TRACE: Add_Window()\" );
#endif

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

AddTop_WindowList( window )
MyWindow *window;
{
#ifdef TRACE
	printf( "TRACE: AddTop_Window()\" );
#endif

	window->next = Head_of_Windows;
	Head_of_Windows = window;

} /* end AddTop_Window */

Remove_WindowList( window )
MyWindow *window;
{
	MyWindow *temp1
	       , *temp2;
#ifdef TRACE
	printf( "TRACE: Remove_Window()\" );
#endif
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

getXsignaldata()
{
	MyWindow *window;
#ifdef TRACE
	printf( "TRACE: getXsignaldata()\n" );
#endif
	Next_Event_req = TRUE;
	while( Next_Event_req && XPending( Xdisplay ) ) {
		Next_Event_req = FALSE;
		XNextEvent( Xdisplay, &report );
		window = Head_of_Windows;
		while( window ) {
			if( report.window == window->win ) {
				if( window->event_func ) {
					(window->event_func)(&report,window);
				}
				break; /* exit while */
			} /* end if */
			window = window->next;
		} /* end while */
	} /* end if */

} /* end getXsignaldata() */

DispatchXhandler( event, window ) /* General event handler */
XAnyEvent *event;
MyWindow *window;
{
	MyEvent *temp;
#ifdef TRACE
	printf( "TRACE: DispatchXhandler()\" );
#endif
	temp = window->event_head;

	while( temp ) {
		if( event->type == temp->type ) {
			if( temp->func ) {
				(temp->func)( event, window );
			}
			/*
			break;
			*/
			return;
		} /* end if */
		temp = temp->next;
	} /* end while */
/*
	printf( "DispatchXhandler(): Unexpected event type %d\n", event->type );
*/
} /* end DispatchXhandler */

Bool
isXeventtype( display, event, type )
Display *display;
XEvent *event;
{
#ifdef TRACE
        printf( "TRACE: isXeventtype()\n" );
#endif

        if( event->type == type )
                return( True );
        else 
                return( False );

} /* end isXeventtype */
