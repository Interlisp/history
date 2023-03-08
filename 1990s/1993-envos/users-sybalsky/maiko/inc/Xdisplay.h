/* @(#) Xdisplay.h Version 1.3 (4/21/92). copyright Venue & Fuji Xerox  */
/*
*
*
* Copyright (C) 1988 by Fuji Xerox co.,Ltd. All rights reserved.
*
*		Author: Mitsunori Matsuda
*		Date  : July 26,1988
*/


/************************************************************************/
/*									*/
/*	Copyright 1989, 1990 Venue, Fuji Xerox Co., Ltd, Xerox Corp.	*/
/*									*/
/*	This file is work-product resulting from the Xerox/Venue	*/
/*	Agreement dated 18-August-1989 for support of Medley.		*/
/*									*/
/************************************************************************/


typedef struct
  {
    char *name;		/* name of this window */
    Window win;          	/* window id */
    int    x,y;          	/* x and y cordinates */
    int    width,height; 	/* window size */
    int    border;       	/* border width */
    GC     *gc; 
    unsigned logn event_mask;
    Cursor *cursor;      	/* current cursor */
    int    (*func)();    	/* Event Function */
  } MyWindow;


typedef struct
  {
    int type;     /* Event type */
    int (*func)();/* Event function */
  } MyEvent;


typedef struct 
  {
    int left_x;  /* x coordinate of upper-left corner */
    int top_y;   /* y coordinate of upper-lert corner */
    int right_x; /* x coordinate of lower-right corner */
    int bottom_y;/* y coordinate of lower-right corner */
  } DisplayArea;

