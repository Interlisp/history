h08254s 00004/00000/00233d D 1.5 91/09/27 01:59:58 sybalsky 5 4c Retrofit of ISC port changeses 00073/00061/00160d D 1.4 90/09/18 23:28:32 sybalsky 4 3c Retrofit changes from AIX, DEC3100, PS/2es 00058/00021/00163d D 1.3 90/07/06 12:14:07 sybalsky 3 2c Bane change: Remove 1-event-per timer-int limit, speeding up keyboard in X version.es 00013/00002/00171d D 1.2 90/04/20 01:13:53 sybalsky 2 1c ning file names, bulk change.es 00173/00000/00000d D 1.1 90/04/19 23:18:38 sybalsky 1 0c date and time created 90/04/19 23:18:38 by sybalskyeuUf e 0tTI 1/* %Z% %M% Version %I% (%G%). copyright venue & Fuji Xerox  */static char *id = "%Z% %M%	%I% %G%	(venue & Fuji Xerox)";D 2/* %Z% %M% Version %I% (%G%). copyright venue & Fuji Xerox  */static char *id = "%Z% %M%	%I% %G%	(venue & Fuji Xerox)";E 2I 2/************************************************************************//*									*//*	Copyright 1989, 1990 Venue, Fuji Xerox Co., Ltd, Xerox Corp.	*//*									*//*	This file is work-product resulting from the Xerox/Venue	*//*	Agreement dated 18-August-1989 for support of Medley.		*//*									*//************************************************************************/E 2/**** Copyright (C) 1988 by Fuji Xerox co.,Ltd. All rights reserved.**		Author: Mitsunori Matsuda*		Date  : June 5, 1988**/#include <stdio.h>#include <X11/Xlib.h>#include <X11/Xutil.h>I 5#ifdef ISC#include <sys/bsdtypes.h>#endif ISCE 5#include "lispemul.h"#include "XVersion.h"#include "MyWindow.h"I 3#include "dbprint.h"E 3#define FALSE 0#define TRUE  !FALSE#define KEYCODE_OFFSET 7	/* Sun Keycode offset */#define	MOUSE_LEFT	13#define	MOUSE_MIDDLE	15#define	MOUSE_RIGHT	14D 4#define MouseMove(x,y) {(*((DLword *)EmMouseX68K)) = x;\			(*((DLword *)EmMouseY68K)) = y;}E 4I 4#define MouseMove(x,y) 					\  {							\    (*((DLword *)EmMouseX68K)) = x;			\    (*((DLword *)EmMouseY68K)) = y;			\  }E 4#define TrackCursor(cx,cy) { \		*CLastUserActionCell68k = MiscStats->secondstmp; \		*EmCursorX68K = cx; \		*EmCursorY68K = cy; \}#define PUTBASEBIT68K(base68k, offset, bitvalue ) { \	if( bitvalue) \		*((DLword*)(base68k) + (((u_short)(offset))>>4 )) \			|= 1<<(15-((u_short)(offset))%BITSPER_DLWORD); \	else	 \		*((DLword*)(base68k) + (((u_short)(offset))>>4 ))  \			&= ~(1<<(15-((u_short)(offset)) %BITSPER_DLWORD)); \	}extern DLword  *EmCursorX68K	     , *EmCursorY68K;extern DLword  *EmMouseX68K             , *EmMouseY68K	     , *EmKbdAd068K	     , *EmRealUtilin68K;extern LispPTR *CLastUserActionCell68k;extern MISCSTATS *MiscStats;extern Display *Xdisplay;extern MyWindow Display_Window;extern DisplayArea ScreenRegion;extern u_char *SUNLispKeyMap;D 3extern int Next_Event_req;E 3I 3/* extern int Next_Event_req;  removed JDS 7/6/90 keyboard speedup */E 3extern int KBDEventFlg;I 3/************************************************************************//*									*//*			l i s p _ X k e y b o a r d			*//*									*//*	The keyboard handler, when we're running X.  Turn an X event	*//*	into a key transition event for Lisp.				*//*									*//************************************************************************/E 3lisp_Xkeyboard( event, window )D 3XKeyEvent *event;MyWindow *window;{	int kn;E 3I 3  XKeyEvent *event;  MyWindow *window;  {    int kn;E 3D 4#ifdef TRACED 3	printf( "TRACE: lisp_Xkeyboard()\n" );E 3I 3    printf( "TRACE: lisp_Xkeyboard()\n" );E 3#endifE 4I 4    TPRINT(( "TRACE: lisp_Xkeyboard()\n" ));    /* Uncomment this if you need to figure out an */    /* X client's key-code mapping by typing at the keyboard. */    /*  if (event->type != KeyRelease)      printf("Key down:  %d.\n", event->keycode); */E 4I 4E 4D 3	if( (kn = SUNLispKeyMap[(event->keycode)-KEYCODE_OFFSET]) > -1 ) {		kb_trans( kn, ((event->type) == KeyRelease) );	} else {		printf( "lisp_Xkeyboard: unknown key = %d\n", event->keycode );	}E 3I 3    if( (kn = SUNLispKeyMap[(event->keycode)-KEYCODE_OFFSET]) > -1 )      {	kb_trans( kn, ((event->type) == KeyRelease) );      }    else       {	printf( "lisp_Xkeyboard: unknown key = %d\n", event->keycode );      }E 3D 3	DoRing();	if((KBDEventFlg += 1) > 0) {		/* immidiately request for IRQ check */		Irq_Stk_End=Irq_Stk_Check=0;	}E 3I 3    DoRing();I 4E 4    if((KBDEventFlg += 1) > 0)      {	/* Immediately request for IRQ check */	Irq_Stk_End=Irq_Stk_Check=0;      }E 3D 3} /* end lisp_Xkeyboard */E 3I 3  } /* end lisp_Xkeyboard */E 3I 3/************************************************************************//*									*//*			l i s p _ X b u t t o n				*//*									*//*	X button-event handler. 					*//*									*//************************************************************************/E 3lisp_Xbutton( event, window )D 4XButtonEvent *event;MyWindow *window;{#ifdef TRACE 	printf( "TRACE: lisp_Xbutton()\n" );#endifE 4I 4  XButtonEvent *event;  MyWindow *window;  {    TPRINT(( "TRACE: lisp_Xbutton()\n" ));E 4D 4	if( (event->button & 0xFF) == Button1 ) {		PUTBASEBIT68K( EmRealUtilin68KE 4I 4    if( (event->button & 0xFF) == Button1 )      {	PUTBASEBIT68K( EmRealUtilin68KE 4			, MOUSE_LEFT			, (event->type == ButtonRelease) );D 4	}	else if( (event->button & 0xFF) == Button2 ) {		PUTBASEBIT68K( EmRealUtilin68KE 4I 4      }    else if( (event->button & 0xFF) == Button2 )      {	PUTBASEBIT68K( EmRealUtilin68KE 4			, MOUSE_MIDDLE			, (event->type == ButtonRelease) );D 4	}	else if( (event->button & 0xFF) == Button3 ) {		PUTBASEBIT68K( EmRealUtilin68KE 4I 4      }    else if( (event->button & 0xFF) == Button3 )      {	PUTBASEBIT68K( EmRealUtilin68KE 4			, MOUSE_RIGHT			, (event->type == ButtonRelease) );D 4	}E 4I 4      }E 4D 4	DoRing();	if((KBDEventFlg += 1) > 0) {		/* immidiately request for IRQ check */		Irq_Stk_End=Irq_Stk_Check=0;	}E 4I 4    DoRing();E 4I 4    if((KBDEventFlg += 1) > 0)      {	/* immediately ask for IRQ check */	Irq_Stk_End=Irq_Stk_Check=0;      }E 4D 4} /* end lisp_Xbutton */E 4I 4  } /* end lisp_Xbutton */E 4D 3int lisp_Xmotion( event, window )XMotionEvent *event;MyWindow *window;E 3I 3/************************************************************************//*									*//*			l i s p _ X m o t i o n				*//*									*//*	Mouse tracking for X-windows LDE.				*//*									*//************************************************************************/int lisp_Xmotion( event, window )  XMotionEvent *event;  MyWindow *window;E 3{D 4	short mouse_x	    , mouse_y;	int x	  , y	  , read_ahead;	Window event_window;E 4I 4    short mouse_x        , mouse_y;    int x      , y      , read_ahead;    Window event_window;E 4D 4#ifdef TRACE	printf( "TRACE: lisp_Xmotion()\n" );#endifE 4I 4    TPRINT(( "TRACE: lisp_Xmotion()\n" ));E 4D 4	x = event->x;	y = event->y;E 4I 4    x = event->x;    y = event->y;E 4D 4	event_window = event->window;	read_ahead = FALSE;E 4I 4    event_window = event->window;    read_ahead = FALSE;E 4D 4	while( !read_ahead && XPending( Xdisplay ) ) {		XNextEvent( Xdisplay, event );		if( (event->type == MotionNotify)		 && (event->window == event_window)   ) {			x = event->x;			y = event->y;		} else {			read_ahead = TRUE;			XPutBackEvent( Xdisplay, event );E 4I 4    while( !read_ahead && XPending( Xdisplay ) )      {	XNextEvent( Xdisplay, event );	if( (event->type == MotionNotify)	    && (event->window == event_window)   )	  {	    x = event->x;	    y = event->y;	  }	else	  {	    read_ahead = TRUE;	    XPutBackEvent( Xdisplay, event );E 4D 4		} /*end if */	} /* end while */E 4I 4	  } /*end if */      } /* end while */E 4D 4	mouse_x = (short) ((x + ScreenRegion.left_x)&0xFFFF);	mouse_y = (short) ((y + ScreenRegion.top_y )&0xFFFF);E 4I 4    mouse_x = (short) ((x + ScreenRegion.left_x)&0xFFFF);    mouse_y = (short) ((y + ScreenRegion.top_y )&0xFFFF);E 4D 4	MouseMove(  mouse_x, mouse_y );	TrackCursor( mouse_x, mouse_y );	DoRing();	if(( KBDEventFlg ) > 0) {		/* immidiately request for IRQ check */		Irq_Stk_End=Irq_Stk_Check=0;	}E 4I 4    MouseMove(  mouse_x, mouse_y );    TrackCursor( mouse_x, mouse_y );    DoRing();    if(( KBDEventFlg ) > 0)      {	/* immidiately request for IRQ check */	Irq_Stk_End=Irq_Stk_Check=0;      }E 4/*D 4	return( read_ahead );E 4I 4    return( read_ahead );E 4*/D 4} /* end lisp_Xmotion */E 4I 4  } /* end lisp_Xmotion */E 4E 1