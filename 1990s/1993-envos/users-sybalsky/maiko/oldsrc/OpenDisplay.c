/* @(#) OpenDisplay.c Version 1.9 (9/27/91). copyright venue & Fuji Xerox  */
static char *id = "@(#) OpenDisplay.c	1.9 9/27/91	(venue & Fuji Xerox)";


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
#include <sys/types.h>
#include <sys/file.h>

#include "lispemul.h"
#include "dbprint.h"

#include "XVersion.h"
#include "MyWindow.h"

#ifdef HPUX
#define FASYNC O_NONBLOCK
#endif HPUX
#include <sys/fcntl.h>
#include <sys/ioctl.h>
#include <stropts.h>
#ifdef ISC
#define FASYNC O_NONBLOCK
#define SIGIO SIGPOLL
#endif ISC

#define FALSE 0
#define TRUE  !FALSE

#define DISPLAY_MAX 65536*16*2		/* same magic number is */
					/* in loadsysout.c      */

extern char *Display_Name;
extern int Auto_Repeat;
extern int Def_Auto_Repeat;
extern char *Lisp_Screen_Size;

Display *Xdisplay;
Screen *Xscreen;
Bool Backing_Store
   , Save_Unders;
char *Server_Vendor;
int Version
  , Revision
  , Screen_Number
  , Byte_Order
  , Bitmap_Bit_Order
  , Bitmap_Pad
  , Bitmap_Unit
  , Default_Depth
  , Display_Height
  , Display_Width
  , LispDisplayWidth
  , LispDisplayHeight;

unsigned long Black_Pixel
            , White_Pixel;

Colormap Colors;

MyWindow Root_Window;

int Xfd;  /* The fd for the socket to the server */
extern int LispReadFds;


/************************************************************************/
/*									*/
/*			O p e n _ D i s p l a y				*/
/*									*/
/*	Open the connection to the X client/window manager display,	*/
/*	gather information from it that we'll need (pixel depth, etc),	*/
/*	and initialize the lisp display-bank size to fit the screen.	*/
/*									*/
/*									*/
/************************************************************************/

Open_Display()
  {

    TPRINT(( "TRACE: Open_Display()\n" ));

    if( (Xdisplay = XOpenDisplay( Display_Name )) == NULL )
      {
	fprintf( stderr, "Open_Display: cannot connect to display %s."
			,XDisplayName(Display_Name));
	exit(-1);
      }

    Xfd = ConnectionNumber(Xdisplay);
    LispReadFds |= (1 << Xfd);
#ifndef ISC
    fcntl(Xfd, F_SETOWN, getpid());
#endif ISC

#ifdef DEBUG
    /****************************************************/
    /* If debugging, set the X connection so that	*/
    /* we run synchronized--so a debugger can		*/
    /* 'stop in _XError' and know EXACTLY where		*/
    /* an error got caused.				*/
    /****************************************************/
    XSynchronize(Xdisplay, 1);
#endif DEBUG

    Version          = ProtocolVersion( Xdisplay );
    Revision         = ProtocolRevision( Xdisplay );
    Server_Vendor    = ServerVendor( Xdisplay );
    Byte_Order       = ImageByteOrder( Xdisplay );
    Bitmap_Bit_Order = BitmapBitOrder( Xdisplay );
    Bitmap_Pad       = BitmapPad( Xdisplay );
    Bitmap_Unit      = BitmapUnit( Xdisplay );

    Screen_Number    = DefaultScreen( Xdisplay );
    Xscreen          = ScreenOfDisplay( Xdisplay, Screen_Number );

    Backing_Store    = DoesBackingStore( Xscreen );
    Save_Unders      = DoesSaveUnders( Xscreen );
    Default_Depth	 = DefaultDepthOfScreen( Xscreen );
    Black_Pixel      = BlackPixelOfScreen( Xscreen );
    White_Pixel      = WhitePixelOfScreen( Xscreen );
    Colors           = DefaultColormapOfScreen( Xscreen );
    Root_Window.win  = RootWindowOfScreen( Xscreen );
    Display_Width    = WidthOfScreen( Xscreen );
    Display_Height   = HeightOfScreen( Xscreen );

    /************************************************************/
    /* 		Set the size of ScreenBitMap			*/
    /* The display's width is rounded to a 32-bit multiple,	*/
    /* so that little-Endian machines can display right.	*/
    /************************************************************/

    LispDisplayWidth  = Display_Width  * PERCENT_OF_SCREEN / 100;
    LispDisplayWidth = ((LispDisplayWidth+31) >> 5) << 5;
    LispDisplayHeight = Display_Height * PERCENT_OF_SCREEN / 100; 

    if( Lisp_Screen_Size[0] != '\0' )
      { /* specified in command line */
	int bitmask
	  , temp_x
	  , temp_y;
	bitmask = XParseGeometry( Lisp_Screen_Size
					, &temp_x
					, &temp_y
					, &LispDisplayWidth
					, &LispDisplayHeight );
      } /* end if */

    /* adjust word boundary */
#ifdef NEVER
    LispDisplayWidth += (BITSPER_DLWORD -1);
    LispDisplayWidth -= (LispDisplayWidth % BITSPER_DLWORD);
#else
    LispDisplayWidth += (Bitmap_Pad -1);
    LispDisplayWidth -= (LispDisplayWidth % Bitmap_Pad);
#endif NEVER

    if( (LispDisplayWidth * LispDisplayHeight ) > DISPLAY_MAX )
      {
	LispDisplayHeight = DISPLAY_MAX / LispDisplayWidth;
      } /* end if */

    /* Keyboard Auto Repeat */
    if( Def_Auto_Repeat )
      {
	if( Auto_Repeat ) XAutoRepeatOn( Xdisplay );
	else XAutoRepeatOff( Xdisplay );
      }

} /* end OpenDisplay */
