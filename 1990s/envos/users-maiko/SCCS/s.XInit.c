h15301s 00000/00000/00038d D 1.6 93/02/08 14:42:45 sybalsky 6 5c Big VM (and new CDR coding) changes for 3.0 \nes 00004/00003/00034d D 1.5 92/04/27 18:41:39 nilsson 5 4c Fix of Xdisplay deps.es 00004/00013/00033d D 1.4 92/04/23 16:28:10 nilsson 4 3c New short name regimen. Improved X commandline handlinges 00000/00000/00046d D 1.3 92/04/21 16:59:02 sybalsky 3 2c shortening file names for DOS \nes 00013/00002/00033d D 1.2 90/04/20 01:13:27 sybalsky 2 1c tening file names, bulk change.es 00035/00000/00000d D 1.1 90/04/19 23:18:35 sybalsky 1 0c date and time created 90/04/19 23:18:35 by sybalskyeuUf e 0tTI 1/* %Z% %M% Version %I% (%G%). copyright venue & Fuji Xerox  */static char *id = "%Z% %M%	%I% %G%	(venue & Fuji Xerox)";D 2/* %Z% %M% Version %I% (%G%). copyright venue & Fuji Xerox  */static char *id = "%Z% %M%	%I% %G%	(venue & Fuji Xerox)";E 2I 2/************************************************************************//*									*//*	Copyright 1989, 1990 Venue, Fuji Xerox Co., Ltd, Xerox Corp.	*//*									*//*	This file is work-product resulting from the Xerox/Venue	*//*	Agreement dated 18-August-1989 for support of Medley.		*//*									*//************************************************************************/E 2/**** Copyright (C) 1988 by Fuji Xerox co.,Ltd. All rights reserved.**		Author: Mitsunori Matsuda*		Date  : August 10, 1988*/#include <stdio.h>D 5E 5I 5#include <X11/Xlib.h>E 5#define FALSE 0 #define TRUE  !FALSED 4int Lisp_Xinitialized = FALSE;E 4I 4extern int Lisp_Xinitialized;E 4D 5init_Xdisplay()E 5I 5init_Xdisplay(display)     Display *display;E 5{D 4#ifdef TRACE        printf( "TRACE: init_Xdisplay()\n" );#endif        if( !Lisp_Xinitialized ) {		Open_Display();		/* Connect to Window-Server */		Create_LispWindow();	/* Make Window for Lisp */		Lisp_Xinitialized = TRUE;	} /* end if */E 4I 4D 5  Create_LispWindow();	/* Make the main window */E 5I 5  Create_LispWindow(display);	/* Make the main window */E 5  Lisp_Xinitialized = TRUE;E 4} /* end init_Xdisplay() */I 4E 4E 1