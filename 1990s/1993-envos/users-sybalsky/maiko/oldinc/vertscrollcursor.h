/* @(#) vertscrollcursor.h Version 1.2 (4/19/90). copyright Venue & Fuji Xerox  */
/* 
*
*
* Copyright (C) 1988 by Fuji Xerox co.,Ltd. All rights reserved.
*
*		Author: Mitsunori Matsuda
*		Date  : August 30, 1988
*/
char vertscrollcursor_bitmap[]={
		  0x01, 0x00
		, 0x03, 0x80
		, 0x03, 0x80
		, 0x07, 0xC0	
		, 0x07, 0xC0	
		, 0x0F, 0xE0
		, 0x03, 0x80
		, 0x03, 0x80
		, 0x03, 0x80
		, 0x03, 0x80
		, 0x0F, 0xE0
		, 0x07, 0xC0	
		, 0x07, 0xC0	
		, 0x03, 0x80
		, 0x03, 0x80
		, 0x01, 0x00
};

LISP_CURSOR vertscroll_cursor = {
		  1
		, vertscrollcursor_bitmap
		, vertscrollcursor_bitmap
		, 7
		, 15
		, NULL
};
	