/* @(#) defaultcursor.h Version 1.2 (4/19/90). copyright Venue & Fuji Xerox  */
/*
*
*
* Copyright (C) 1988 by Fuji Xerox co.,Ltd. All rights reserved.
*
*		Author: Mitsunori Matsuda
*		Date  : August 30, 1988
*/
char defaultcursor_bitmap[]={
	  0x80, 0, 0xc0, 0, 0xe0, 0, 0xf0, 0 
	, 0xf8, 0, 0xfc, 0, 0xfe, 0, 0xf0, 0
	, 0xd8, 0, 0x98, 0, 0x0c, 0, 0x0c, 0
	, 0x06, 0, 0x06, 0, 0x03, 0, 0x03, 0
};
	
LISP_CURSOR default_cursor = { 
		  1
		, defaultcursor_bitmap
		, defaultcursor_bitmap
		, 0
		, 15
		, NULL 
};
