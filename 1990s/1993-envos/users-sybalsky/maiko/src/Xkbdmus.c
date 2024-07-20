/* @(#) Xkbdmus.c Version 1.4 (2/8/93). copyright venue & Fuji Xerox  */
static char *id = "@(#) Xkbdmus.c	1.4 2/8/93	(venue & Fuji Xerox)";


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
*		Date  : June 5, 1988
*
*/

#include <stdio.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>

#ifdef ISC
#include <sys/bsdtypes.h>
#endif /* ISC */


#include "lispemul.h"

#include "XVersion.h"
#include "MyWindow.h"
#include "dbprint.h"

#define FALSE 0
#define TRUE  !FALSE

#define KEYCODE_OFFSET 7	/* Sun Keycode offset */

#define	MOUSE_LEFT	13
#define	MOUSE_MIDDLE	15
#define	MOUSE_RIGHT	14

#define MouseMove(x,y) 					\
  {							\
    (*((DLword *)EmMouseX68K)) = x;			\
    (*((DLword *)EmMouseY68K)) = y;			\
  }

#define TrackCursor(cx,cy) { \
		*CLastUserActionCell68k = MiscStats->secondstmp; \
		*EmCursorX68K = cx; \
		*EmCursorY68K = cy; \
}

#define PUTBASEBIT68K(base68k, offset, bitvalue ) { \
	if( bitvalue) \
		*((DLword*)(base68k) + (((u_short)(offset))>>4 )) \
			|= 1<<(15-((u_short)(offset))%BITSPER_DLWORD); \
	else	 \
		*((DLword*)(base68k) + (((u_short)(offset))>>4 ))  \
			&= ~(1<<(15-((u_short)(offset)) %BITSPER_DLWORD)); \
	}

extern DLword  *EmCursorX68K
	     , *EmCursorY68K;
extern DLword  *EmMouseX68K
             , *EmMouseY68K
	     , *EmKbdAd068K
	     , *EmRealUtilin68K;
extern LispPTR *CLastUserActionCell68k;
extern MISCSTATS *MiscStats;

extern MyWindow Display_Window;
extern DisplayArea ScreenRegion;
extern u_char *SUNLispKeyMap;
/* extern int Next_Event_req;  removed JDS 7/6/90 keyboard speedup */
extern int KBDEventFlg;




/************************************************************************/
/*									*/
/*			l i s p _ X k e y b o a r d			*/
/*									*/
/*	The keyboard handler, when we're running X.  Turn an X event	*/
/*	into a key transition event for Lisp.				*/
/*									*/
/************************************************************************/

lisp_Xkeyboard( event, window )
  XKeyEvent *event;
  MyWindow *window;
  {
    int kn;

    TPRINT(( "TRACE: lisp_Xkeyboard()\n" ));
    /* Uncomment this if you need to figure out an */
    /* X client's key-code mapping by typing at the keyboard. */
    /*  if (event->type != KeyRelease)
      printf("Key down:  %d.\n", event->keycode); */


    if( (kn = SUNLispKeyMap[(event->keycode)-KEYCODE_OFFSET]) > -1 )
      {
	kb_trans( kn, ((event->type) == KeyRelease) );
      }
    else 
      {
	printf( "lisp_Xkeyboard: unknown key = %d\n", event->keycode );
      }

    DoRing();

    if((KBDEventFlg += 1) > 0)
      {
	/* Immediately request for IRQ check */
	Irq_Stk_End=Irq_Stk_Check=0;
      }

  } /* end lisp_Xkeyboard */



/************************************************************************/
/*									*/
/*			l i s p _ X b u t t o n				*/
/*									*/
/*	X button-event handler. 					*/
/*									*/
/************************************************************************/

lisp_Xbutton( event, window )
  XButtonEvent *event;
  MyWindow *window;
  {
    TPRINT(( "TRACE: lisp_Xbutton()\n" ));

    if( (event->button & 0xFF) == Button1 )
      {
	PUTBASEBIT68K( EmRealUtilin68K
			, MOUSE_LEFT
			, (event->type == ButtonRelease) );
      }
    else if( (event->button & 0xFF) == Button2 )
      {
	PUTBASEBIT68K( EmRealUtilin68K
			, MOUSE_MIDDLE
			, (event->type == ButtonRelease) );
      }
    else if( (event->button & 0xFF) == Button3 )
      {
	PUTBASEBIT68K( EmRealUtilin68K
			, MOUSE_RIGHT
			, (event->type == ButtonRelease) );
      }

    DoRing();

    if((KBDEventFlg += 1) > 0)
      {
	/* immediately ask for IRQ check */
	Irq_Stk_End=Irq_Stk_Check=0;
      }

  } /* end lisp_Xbutton */




/************************************************************************/
/*									*/
/*			l i s p _ X m o t i o n				*/
/*									*/
/*	Mouse tracking for X-windows LDE.				*/
/*									*/
/************************************************************************/

int lisp_Xmotion( event, window )
  XMotionEvent *event;
  MyWindow *window;
{
    short mouse_x
        , mouse_y;
    int x
      , y
      , read_ahead;
    Window event_window;

    TPRINT(( "TRACE: lisp_Xmotion()\n" ));

    x = event->x;
    y = event->y;

    event_window = event->window;
    read_ahead = FALSE;

    while( !read_ahead && XPending( event->display ) )
      {
	XNextEvent( event->display, event );
	if( (event->type == MotionNotify)
	    && (event->window == event_window)   )
	  {
	    x = event->x;
	    y = event->y;
	  }
	else
	  {
	    read_ahead = TRUE;
	    XPutBackEvent( event->display, event );

	  } /*end if */
      } /* end while */

    mouse_x = (short) ((x + ScreenRegion.left_x)&0xFFFF);
    mouse_y = (short) ((y + ScreenRegion.top_y )&0xFFFF);

    MouseMove(  mouse_x, mouse_y );
    TrackCursor( mouse_x, mouse_y );
    DoRing();
    if(( KBDEventFlg ) > 0)
      {
	/* immidiately request for IRQ check */
	Irq_Stk_End=Irq_Stk_Check=0;
      }

/*
    return( read_ahead );
*/
  } /* end lisp_Xmotion */