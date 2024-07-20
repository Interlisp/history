/* @(#) lispXdisplay.h Version 1.2 (4/19/90). copyright Venue & Fuji Xerox  */
/*
*
*
* Copyright (C) 1988 by Fuji Xerox co.,Ltd. All rights reserved.
*
*		Author: Mitsunori Matsuda
*		Date  : July 26,1988
*/

typedef struct {
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

typedef struct {
	int type;     /* Event type */
	int (*func)();/* Event function */
} MyEvent;

typedef struct {
	int left_x;  /* x cordinate of upperleft corner */
	int top_y;   /* y cordinate of upperlert corner */
	int right_x; /* x cordinate of lowerright corner */
	int bottom_y;/* y cordinate of lowerright corner */
} DisplayArea;
