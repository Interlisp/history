/* @(#) display.h Version 2.9 (11/25/92). copyright Venue  */





/************************************************************************/
/*									*/
/*	(C) Copyright 1989-92 Venue. All Rights Reserved.		*/
/*	Manufactured in the United States of America.			*/
/*									*/
/*	The contents of this file are proprietary information 		*/
/*	belonging to Venue, and are provided to you under license.	*/
/*	They may not be further distributed or disclosed to third	*/
/*	parties without the specific permission of Venue.		*/
/*									*/
/************************************************************************/

#define BCPLDISPLAY	stdout


#define	CURSORWIDTH	16
#define	CURSORHEIGHT	16

/* Max address for HI-RES DISPLAY */
/* Osamu '90/02/08
 * Change into variable for efficiency
#define DISP_MAX_Address  (DisplayRegion68k + 1600*1280/8)
 */
extern DLword *DISP_MAX_Address;

	/* Is the bitmap in the display region? */

#define IN_DISPLAY_BANK(hiaddr) (((hiaddr)==DISPLAY_HI)|((hiaddr)==(DISPLAY_HI+1)))

#define DLWORD_PERLINE	(DisplayWidth/16)
#define HARD_CURSORWIDTH 16
#define HARD_CURSORHEIGHT 16
#define COLOR_BITSPER_PIXEL 8
#define MONO_SCREEN 0
#define COLOR_SCREEN 1
#define COLOR_MAX_Address (ColorDisplayRegion68k + 1152 * 900)

/* Replicate a 4-bit pattern to fill a word */
#define Expand4Bit(BITS)	\
		((BITS) | ((BITS) << 4) | ((BITS) << 8) | ((BITS) << 12))

#ifdef XWINDOW
#define DISPLAYBUFFER
#endif /* XWINDOW */


#ifdef DISPLAYBUFFER
/************************************************************************/
/*									*/
/*		    i n _ d i s p l a y _ s e g m e n t			*/
/*									*/
/*	Returns T if the base address for this bitblt is in the 	*/
/*	display segment.						*/
/*									*/
/************************************************************************/
/* Osamu '90/02/08
 * This definition is moved from initdsp.c
 * Change into macro for efficiency.
 * And also DISP_MAX_Address is changed as variable
 * to avoid same calicuration every time it uses.
 *********************************************************************/
extern DLword *DisplayRegion68k;

#define in_display_segment(baseaddr)  \
            (((DisplayRegion68k <= baseaddr) && \
	      (baseaddr <=DISP_MAX_Address)) ? T :NIL )
#endif

#ifdef XWINDOW
#undef DISPLAYBUFFER
#endif /* XWINDOW */
