/* @(#) RasterOps.c Version 1.3 (4/23/92). copyright venue & Fuji Xerox  */
static char *id = "@(#) RasterOps.c	1.3 4/23/92	(venue & Fuji Xerox)";

/*  (c) CopyRight Fuji Xerox 1991  Maiko for VISION Project */
/* FILE: RasterOps.c REL.1 SCCSID:1.1  */
/* SCCS file: /tmp_mnt/net/vogue/project1/emul/SCCS/s.RasterOps.c  */

/*
*
*
* Copyright (C) 1990 by Fuji Xerox co.,Ltd.. All rights reserved.
*
*               Author: Mitsunori Matsuda
*               Date  : May 14, 1991
*/

#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sun/fbio.h>

#include <sunwindow/rect.h>
#include <suntool/pip.h>
#include <sun/pipio.h>

#
#define FALSE  0
#define TRUE  !FALSE

#define NTSC_SIGNAL_LEFT	100
#define NTSC_SIGNAL_TOP		16
#define NTSC_MAX_WIDTH		640
#define NTSC_MAX_HEIGHT		480

#define PAL_SIGNAL_LEFT		134
#define PAL_SIGNAL_TOP		22
#define PAL_MAX_WIDTH		768
#define PAL_MAX_HEIGHT		576

int Video_Fd;
int Video_OnOff_Flg = FALSE;
int Inited_Video = FALSE;

int
Video_Initialize( fd )
int fd;
{
	int type = PIP_NTSC;

	if( Inited_Video ) {
		printf( "Video_Initialize: Picture in picture has already initialized.\n" );
		return( FALSE );
	} /* end Inited_Video */
/*
	Video_Fd = fd;
*/
	Video_Fd = open( "/dev/cgeight0", O_RDWR );

	ioctl( Video_Fd, PIPIO_S_INITIALIZE, &type );

	Video_Signal( PIP_NTSC );

	Video_OnOff_Flg = TRUE;
	Video_OnOff( FALSE );
	Video_SourceType( PIP_COMPOSITE );
	Video_SignalRegion( 0, 0, 0, 0 );

	Inited_Video = TRUE;

	return( TRUE );

} /* end Video_Initialize */

Video_Close() 
{
	Video_OnOff( FALSE );
	Video_SignalRegion( 0, 0, 0, 0 );
	close( Video_Fd );
	Video_Fd = -1;
	Inited_Video = FALSE;

} /* end Video_Close */

int VideoSignalLeft
  , VideoSignalTop
  , VideoSignalMaxWidth
  , VideoSignalMaxHeight;

int Video_Signal( type )
int type;
{
	switch( type ) {
	case PIP_NTSC: /* = 1 */
		VideoSignalLeft      = NTSC_SIGNAL_LEFT;
		VideoSignalTop       = NTSC_SIGNAL_TOP;
		VideoSignalMaxWidth  = NTSC_MAX_WIDTH;
		VideoSignalMaxHeight = NTSC_MAX_HEIGHT;
		ioctl( Video_Fd, PIPIO_S_INITIALIZE, &type );
		return( TRUE );
		break;
	case PIP_PAL: /* = 2 */
		VideoSignalLeft      = PAL_SIGNAL_LEFT;
		VideoSignalTop       = PAL_SIGNAL_TOP;
		VideoSignalMaxWidth  = PAL_MAX_WIDTH;
		VideoSignalMaxHeight = PAL_MAX_HEIGHT;
		ioctl( Video_Fd, PIPIO_S_INITIALIZE, &type );
		return( TRUE );
		break;
	defaults:
		return( FALSE );
		break;
	} /* end switch */
} /* end Video_Signal */

int
Video_SourceType( type )
int type;
{
	if( (type >=0) && (type <=2) ) {
		ioctl( Video_Fd, PIPIO_S_SOURCE, &type );
			/*				*/
			/*	0 is COMPOSIT input.	*/
			/*	1 is S-VIDEO input.	*/
			/*	2 is R-G-B input.	*/
			/*				*/
		return( TRUE );
	} else {
		return( FALSE );
	} /* end if( type ) */
} /* end Video_SourceType */

int
Video_Contrast( level )
int level;
{
	if( (level >= 0) && (level <=63 ) ) {
		ioctl( Video_Fd, PIPIO_S_DAC_CONTRAST, &level );
		return( TRUE );
	} else {
		return( FALSE );
	} /* end if( level ) */
} /* end Video_Contrast */

int
Video_Brightness( level )
int level;
{
	if( (level >= 0) && (level <=63 ) ) {
		ioctl( Video_Fd, PIPIO_S_DAC_BRIGHTNESS, &level );
		return( TRUE );
	} else {
		return( FALSE );
	} /* end if( level ) */
} /* end Video_Brightness */

int
Video_Hue( level )
int level;
{
	if( (level >= 0) && (level <=63 ) ) {
		ioctl( Video_Fd, PIPIO_S_DAC_HUE, &level );
		return( TRUE );
	} else {
		return( FALSE );
	} /* end if( level ) */
} /* end Video_Hue */

int
Video_Saturation( level )
int level;
{
	if( (level >= 0) && (level <=63 ) ) {
		ioctl( Video_Fd, PIPIO_S_DAC_SATURATION, &level );
		return( TRUE );
	} else {
		return( FALSE );
	} /* end if( level ) */
} /* end Video_Saturation */

#define VideoOn		1
#define VideoOff	0

int
Video_OnOff( on )
int on;
{
	int status;

	if( ( Video_OnOff_Flg && !on ) 
	 || ( !Video_OnOff_Flg && on ) ) { /* (VideoOnOff_Flg XOR on) */
		Video_OnOff_Flg = ( on ? VideoOn : VideoOff );
		ioctl( Video_Fd, PIPIO_S_PIP_ON_OFF, &Video_OnOff_Flg );

		/* wait for completion of hardware */
		ioctl( Video_Fd, PIPIO_G_PIP_ACTIVE, &status );
		while( (status != Video_OnOff_Flg ) )
			ioctl( Video_Fd, PIPIO_G_PIP_ACTIVE, &status );

	} /* end if */
	return( TRUE );

} /* end Video_OnOff */


int
Video_SignalRegion( left, top, width, height )
int width
  , height;
{
	struct rect video_signal;

	if( (width>=0) && (width<=VideoSignalMaxWidth)
	 && (height>=0) && (height<=VideoSignalMaxHeight) ) {

		video_signal.r_left   = VideoSignalLeft + left;
		video_signal.r_top    = VideoSignalTop + top;
		video_signal.r_width  = width;
		video_signal.r_height = height;

		ioctl( Video_Fd, PIPIO_S_SIGRECT, &video_signal );
		return( TRUE );
	} else { 
		return( FALSE );
	} /* enf if() */
	
} /* end Video_SignalRegion */

int 
Video_OutputRegion( left, top, width, height )
int left
  , top
  , width
  , height;
{
	struct rect video_output;

	video_output.r_left   = left;
	video_output.r_top    = top;
	video_output.r_width  = width;
	video_output.r_height = height;

	ioctl( Video_Fd, PIPIO_S_OUTRECT, &video_output );
	return( TRUE );

} /* Video_OutputRegion */

#define DO_FLIP    1
#define DONOT_FLIP 0

int
Video_FlipHorizontal( flg )
int flg;
{
	int on_off;

	on_off = ( flg ? DO_FLIP : DONOT_FLIP );
	ioctl( Video_Fd, PIPIO_S_FLIP_HORIZONTAL, &on_off );
	return( TRUE );
} /* end Video_FlipHorizontal */

int
Video_FlipVertical( flg  )
int flg;
{
	int on_off;

	on_off = ( flg ? DO_FLIP : DONOT_FLIP );
	ioctl( Video_Fd, PIPIO_S_FLIP_VERTICAL, &on_off );
	return( TRUE );
} /* end Video_FlipVirtical */