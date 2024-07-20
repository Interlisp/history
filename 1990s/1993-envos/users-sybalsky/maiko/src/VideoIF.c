/* @(#) VideoIF.c Version 1.4 (2/8/93). copyright venue & Fuji Xerox  */
static char *id = "@(#) VideoIF.c	1.4 2/8/93	(venue & Fuji Xerox)";

/*  (c) CopyRight Fuji Xerox 1991  Maiko for VISION Project */
/* FILE: VideoIF.c REL.1 SCCSID:1.1  */
/* SCCS file: /tmp_mnt/net/vogue/project1/emul/SCCS/s.VideoIF.c  */

/*
*
*
* Copyright (C) 1991 by Fuji Xerox co.,Ltd.. All rights reserved.
*
*               Author: Mitsunori Matsuda
*               Date  : May 17, 1991
*/

#include <stdio.h>

#include "lispemul.h"
#include "lispmap.h"
#include "lsptypes.h"
#include "lspglob.h"
#include "adr68k.h"
#include "arith.h"

#define FALSE 0
#define TRUE  !FALSE

#define VIDEO_INIT		0
#define VIDEO_SOURCETYPE	1
#define VIDEO_SIGNALREGION	2
#define VIDEO_OUTREGION		3
#define VIDEO_ONOFF		4
#define VIDEO_CONTRAST		5
#define VIDEO_HUE		6
#define VIDEO_BRIGHTNESS	7
#define VIDEO_SATURATION	8
#define VIDEO_FLIPH		9
#define VIDEO_FLIPV		10
#define VIDEO_SIGNAL		11

extern int FrameBufferFd
	 , DisplayHeight;
extern int VideoSignalMaxHeight;

LispPTR
Video_Op( args )
LispPTR *args;
{
	int op;
	int ret_value = FALSE;

	op = (DLword) args[0];

	switch( op ) {
	case VIDEO_INIT: 
		ret_value = Video_Initialize( FrameBufferFd );
		break;
	case VIDEO_SOURCETYPE: {
		int type;
		N_GETNUMBER( args[1], type, bad_arg );
		ret_value = Video_SourceType( type );
		}
		break;
	case VIDEO_SIGNALREGION: {
/*
		int width
		  , height;
		width = (DLword) args[1];
		height = (DLword) args[2];
		ret_value = Video_SignalSize( width, height );
*/
		if( args[1] != NIL_PTR ) {
			LispPTR region
			      , value;
			int left
			  , top
			  , bottom 
			  , width
			  , height;
			/* get lisp region elements */
			region = args[1];
			value = car( region );
			N_GETNUMBER( value, left, bad_arg );
			region = cdr( region );
			value = car( region );
			N_GETNUMBER( value, bottom, bad_arg );
			region = cdr( region );
			value = car( region );
			N_GETNUMBER( value, width, bad_arg );
			region = cdr( region );
                        value = car( region );
	                N_GETNUMBER( value, height, bad_arg );
			top = VideoSignalMaxHeight - ( bottom + height );

		        ret_value = Video_SignalRegion( left, top
							, width, height );
		} /* end if( args[1] ) */
		}
		break;
	case VIDEO_OUTREGION: {

		if( args[1] != NIL_PTR ) {
			LispPTR region
			      , value;
			int left
			  , top
			  , bottom 
			  , width
			  , height;
			/* get lisp region elements */
			region = args[1];
			value = car( region );
			N_GETNUMBER( value, left, bad_arg );
			region = cdr( region );
			value = car( region );
			N_GETNUMBER( value, bottom, bad_arg );
			region = cdr( region );
			value = car( region );
			N_GETNUMBER( value, width, bad_arg );
			region = cdr( region );
                        value = car( region );
	                N_GETNUMBER( value, height, bad_arg );
			top = DisplayHeight - ( bottom + height );

			ret_value = Video_OutputRegion( left, top
							, width, height );
		} /* end if( args[1] ) */
		}
		break;
	case VIDEO_ONOFF: {
		if( args[1] != NIL_PTR ) {
			ret_value = Video_OnOff( TRUE );
		} else {
			ret_value = Video_OnOff( FALSE );
		} /* end if( args[1] ) */
		}
		break;
	case VIDEO_CONTRAST: {
		int level;
		N_GETNUMBER( args[1], level, bad_arg );
		ret_value = Video_Contrast( level );
		} 
		break;
	case VIDEO_HUE: {
		int level;
		N_GETNUMBER( args[1], level, bad_arg );
		ret_value = Video_Hue( level );
		}
		break;
	case VIDEO_SATURATION: {
		int level;
		N_GETNUMBER( args[1], level, bad_arg );
		ret_value = Video_Saturation( level );
		}
		break;
	case VIDEO_BRIGHTNESS: {
		int level;
		N_GETNUMBER( args[1], level, bad_arg );
		ret_value = Video_Brightness( level );
		}
		break;
	case VIDEO_FLIPH:
		if( args[1] == ATOM_T ) {
			ret_value = Video_FlipHorizontal( TRUE );
		} else {
			ret_value = Video_FlipHorizontal( FALSE );
		} /* end if( args[1] ) */
		break;
	case VIDEO_FLIPV:
		if( args[1] == ATOM_T ) {
			ret_value = Video_FlipVertical( TRUE );
		} else {
			ret_value = Video_FlipVertical( FALSE );
		} /* end if( args[1] ) */
		break;
	case VIDEO_SIGNAL:  {
		int type;
		N_GETNUMBER( args[1], type, bad_arg );
		ret_value = Video_Signal( type );
		}
		break;
	defaults:
		break;
	} /* end switch( op ) */
	
bad_arg:

	if( ret_value ) { /* normal rejurn */
		return( ATOM_T );
	} else { /* error return */
		return( NIL );
	} /* end if( ret_value ) */

} /* end Vidoe_Op */