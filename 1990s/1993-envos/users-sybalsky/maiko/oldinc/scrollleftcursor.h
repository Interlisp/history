/* @(#) scrollleftcursor.h Version 1.2 (4/19/90). copyright Venue & Fuji Xerox  */
/*
*
*
* Copyright (C) 1988 by Fuji Xerox co.,Ltd. All rights reserved.
*
*		Author: Mitsunori Matsuda
*		Date  : August 30, 1988
*/
char scrollleftcursor_bitmap[]={
	  0x00, 0x00
	, 0x00, 0x00
	, 0x00, 0x00
	, 0x00, 0x00
	, 0x00, 0x00
	, 0x00, 0x00
	, 0x00, 0x80
	, 0x03, 0x80
	, 0x0F, 0x80
	, 0x3F, 0x80
	, 0xFF, 0xFF
	, 0xFF, 0xFF
	, 0x3F, 0x80
	, 0x0F, 0x80
	, 0x03, 0x80
	, 0x00, 0x80
};

LISP_CURSOR scrollleft_cursor = {
		  1
		, scrollleftcursor_bitmap
		, scrollleftcursor_bitmap
		, 8
		, 5
		, NULL
};
	
