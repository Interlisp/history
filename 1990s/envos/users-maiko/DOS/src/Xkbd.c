/* @(#) Xkbd.c Version 1.4 (5/27/92). copyright venue & Fuji Xerox  */static char *id = "@(#) Xkbd.c	1.4 5/27/92	(venue & Fuji Xerox)";/************************************************************************//*									*//*	(C) Copyright 1989-92 Venue. All Rights Reserved.		*//*	Manufactured in the United States of America.			*//*									*//*	The contents of this file are proprietary information 		*//*	belonging to Venue, and are provided to you under license.	*//*	They may not be further distributed or disclosed to third	*//*	parties without the specific permission of Venue.		*//*									*//************************************************************************//****		Author: Mitsunori Matsuda*		Date  : August 18, 1988**/#include <stdio.h>#include <X11/Xlib.h>#include <X11/Xutil.h>#include "lispemul.h"#include "ldeXdefs.h"#include "XVersion.h"#include "dspif.h"