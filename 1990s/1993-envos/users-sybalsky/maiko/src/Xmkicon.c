/* @(#) Xmkicon.c Version 1.3 (4/27/92). copyright venue & Fuji Xerox  */
static char *id = "@(#) Xmkicon.c	1.3 4/27/92	(venue & Fuji Xerox)";

/************************************************************************/
/*									*/
/*	Copyright 1989, 1990, 1991 Venue				*/
/*									*/
/*	This file was work-product resulting from the Xerox/Venue	*/
/*	Agreement dated 18-August-1989 for support of Medley.		*/
/*									*/
/************************************************************************/




#include <stdio.h>

#include <X11/Xlib.h>
#include <X11/Xutil.h>

#include "dbprint.h"

#include "XVersion.h"
#include "MyWindow.h"
/* #include "Xicon.h" <<-- Not used any more /jarl*/

extern MyWindow Lisp_Window;
extern int Bitmap_Pad
		 , Default_Depth;

extern Pixmap IconPixmap;
char *iconpixmapfile[1024];

/************************************************************************/
/*									*/
/*			m a k e _ X i c o n				*/
/*									*/
/*	Make the icon for the shrunken Medley window.			*/
/*									*/
/************************************************************************/

make_Xicon(display)
     Display *display;
  {
    unsigned int width, height;
    int value, x_hot, y_hot;
    char *getenv();
    
#ifdef TRACE 
	printf( "In make_Xicon().\n" );
#endif

    if (iconpixmapfile == 0) {
      mess_reset();
      printf("!!CAUTION: icon pixmap fileis not set.\n");
      printf("Please retry after setting icon pixmap file correctly.\n");
      exit(0);			/* exit to shell */
    }
    value = XReadBitmapFile(display, RootWindow(display, 0),
			    iconpixmapfile,
			    &width, &height,
			    &IconPixmap,
			    &x_hot, &y_hot);
    if (value == BitmapFileInvalid)
      fprintf(stderr, "Iconpixmapfile %s contains invalid bitmap data\n", iconpixmapfile);
    else if (value == BitmapOpenFailed)
      fprintf(stderr, "Iconpixmapfile %s could not be opened\n", iconpixmapfile);
    else if (value == BitmapNoMemory)
      fprintf(stderr, "Not enough memory to allocate icon pixmap\n");

  } /* end make_Xicon */
