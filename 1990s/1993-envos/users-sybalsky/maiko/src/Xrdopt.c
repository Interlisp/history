/* @(#) Xrdopt.c Version 1.6 (2/8/93). copyright venue & Fuji Xerox  */
static char *id = "@(#) Xrdopt.c	1.6 2/8/93	(venue & Fuji Xerox)";
/*
*
*
*
*		Author: Mitsunori Matsuda
*		Date  : June 5, 1988
*
*		Modified Jarl Nilsson 1-apr-92 -Made the Xrm stuff work.
*/



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

#include <stdio.h>
#include <string.h>
#include <sys/file.h>
#include <sys/time.h>
#ifndef NOETHER
#include <sys/types.h>
#include <net/nit.h>	/* needed for Ethernet stuff below */
#endif /* NOETHER */

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xresource.h>

#include "XVersion.h"
#include "MyWindow.h"
#include "Xdeflt.h"
#include "dbprint.h"

#define FALSE 0
#define TRUE  !FALSE

Display *Xdisplay;
XrmDatabase commandlineDB, applicationDB, serverDB, homeDB, rDB;
int opTableEntries = 30;
extern int Display_Width;
extern int Display_Height;

XrmOptionDescRec opTable[] = {
      {"-help",		"*help",	XrmoptionIsArg, (caddr_t) "help"},
      {"-h",		"*help",	XrmoptionIsArg, (caddr_t) "help"},
      {"-sysout",	"*sysout",	XrmoptionSepArg, (caddr_t) NULL},
      {"-display",	"*display",	XrmoptionSepArg, (caddr_t) NULL},
      {"-d",		"*display",	XrmoptionSepArg, (caddr_t) NULL},
      {"-borderWidth",	"*borderWidth",	XrmoptionSepArg, (caddr_t) NULL},
      {"-bw",		"*borderWidth",	XrmoptionSepArg, (caddr_t) NULL},
      {"-screen",	"*geometry",	XrmoptionSepArg, (caddr_t) NULL},
      {"-sc",		"*geometry",	XrmoptionSepArg, (caddr_t) NULL},
      {"-geometry",	"*geometry",	XrmoptionSepArg, (caddr_t) NULL},
      {"-g",		"*geometry",	XrmoptionSepArg, (caddr_t) NULL},
      {"-foreground",	"*foreground",	XrmoptionSepArg, (caddr_t) NULL},
      {"-fg",		"*foreground",	XrmoptionSepArg, (caddr_t) NULL},
      {"-background",	"*background",	XrmoptionSepArg, (caddr_t) NULL},
      {"-bg",		"*background",	XrmoptionSepArg, (caddr_t) NULL},
      {"-title",	"*title",	XrmoptionSepArg, (caddr_t) NULL},
      {"-t",		"*title",	XrmoptionSepArg, (caddr_t) NULL},
      {"-icontitle",	"*iconTitle",	XrmoptionSepArg, (caddr_t) NULL},
      {"-it",		"*iconTitle",	XrmoptionSepArg, (caddr_t) NULL},
      {"-iconbitmap",	"*iconbitmap",	XrmoptionSepArg, (caddr_t) NULL},
      {"-ibm",		"*iconbitmap",	XrmoptionSepArg, (caddr_t) NULL},
      {"-key",		"*key",		XrmoptionSepArg, (caddr_t) NULL},
      {"-k",		"*key",		XrmoptionSepArg, (caddr_t) NULL},
      {"-timer",	"*timer",	XrmoptionSepArg, (caddr_t) NULL},
      {"-maxpages",	"*maxpages",	XrmoptionSepArg, (caddr_t) NULL},
      {"-memory",	"*memory",	XrmoptionSepArg, (caddr_t) NULL},
      {"-NF",		"*NoFork",	XrmoptionIsArg,  (caddr_t) NULL},
      {"-INIT",		"*Init",	XrmoptionIsArg, (caddr_t) NULL},
      {"-EtherNet",	"*EtherNet",	XrmoptionSepArg, (caddr_t) NULL},
      {"-E",		"*EtherNet",	XrmoptionSepArg, (caddr_t) NULL},
      {"-autorepeat",	"*autorepeat",	XrmoptionSepArg, (caddr_t) NULL},
    };
      /* autorepeat is a global setting for X, not anything that
       Medley has to be concerned with. Item kept for historical
       reasons /jarl
       */

char Display_Name[128];
int Lisp_Border = 2;
char Window_Title[255];
char Icon_Title[255];
extern char iconpixmapfile[];
extern MyWindow Lisp_Window;
extern char sysout_name[], keystring[];
extern int sysout_size, for_makeinit, please_fork, Scroll_Border;
		/* diagnostic flag for sysout dumping */
extern int maxpages;

extern char keystring[];

/*** Ethernet stuff (JRB) **/
#ifndef NOETHER
extern int ether_fd;
extern u_char ether_host[6];
extern struct sockaddr_nit snit;
#endif /* NOETHER */



/************************************************************************/
/*									*/
/*			r e a d _ X o p t i o n				*/
/*									*/
/*	Parse command-line options related to X windows.		*/
/*									*/
/************************************************************************/

void read_Xoption( argc, argv ) 
  int *argc;
  char **argv;
  {
    int bitmask;
    XrmValue value;
    char *str_type[30], tmp[1024], *envname;


    (void)XrmInitialize();
    /* If the first argv lacks '-' in front it is the sysout. */
    XrmParseCommand(&commandlineDB, opTable, opTableEntries, argv[0], argc, argv);

    if (XrmGetResource(commandlineDB, "ldex.help", "Ldex.Help",
		       str_type, &value) == TRUE) {
      print_Xusage( argv[0] );
      exit(0);
    }

    if(*argc == 2)		/* There was probably a sysoutarg */
      {
	sysout_name[0] = '\0';
	(void)strcat(sysout_name, argv[1]);
      }
    else if ((envname = (char *)getenv("LDESRCESYSOUT")) != NULL)
      {
	strcpy(sysout_name, envname);
      }
    else if ((envname = (char *)getenv("LDESOURCESYSOUT")) != NULL)
      strcpy(sysout_name, envname);
    else {
      envname = (char *)getenv("HOME");
      (void)strcat(sysout_name, envname);
      (void)strcat(sysout_name, "/lisp.virtualmem");

      if( access(sysout_name, R_OK) != 0)
	{
	  (void)strcat(sysout_name, "");
	}
    }
    if (XrmGetResource(commandlineDB,
		       "ldex.display", "Ldex.Display",
		       str_type, &value) == True) {
      (void) strncpy(Display_Name, value.addr, (int)value.size);
    } else {
      (void) strcpy(Display_Name, "unix:0.0");
    }

    /* In order to access other DB's we have to open the main display now */
    Open_Display(Display_Name);

	/* read the other databases */
    /* Start with app-defaults/medley */
    (void)strcpy(tmp, "/usr/lib/X11/app-defaults/");
    (void)strcat(tmp, "medley");
    applicationDB = XrmGetFileDatabase(tmp);
    if (applicationDB != NULL){
      (void)XrmMergeDatabases(applicationDB, &rDB);
    }
    /* Then try the displays defaults */
    if (XResourceManagerString(Xdisplay) != NULL) {
      serverDB = XrmGetStringDatabase(XResourceManagerString(Xdisplay));
      if (serverDB != NULL){
	(void)XrmMergeDatabases(serverDB, &rDB);
      }
    }
    envname = (char *)getenv("HOME");
    (void)strcat(tmp, envname);
    (void)strcat(tmp, "/.Xdefaults");
    if( access(tmp, R_OK) != 0) {
      serverDB = XrmGetFileDatabase(tmp);
      if (serverDB != NULL){
	(void)XrmMergeDatabases(serverDB, &rDB);
      }
    }

    /* Now for the commandline */
    (void)XrmMergeDatabases(commandlineDB, &rDB);

    if (XrmGetResource(rDB,
		       "ldex.borderWidth",
		       "Ldex.BorderWidth",
		       str_type, &value) == True) {
	(void)strncpy(tmp, value.addr, (int)value.size);
	Lisp_Window.border = atoi(tmp);
	Scroll_Border = atoi(tmp);
	if (Lisp_Window.border < 1){
	  Lisp_Window.border = 1;
	  Scroll_Border = 1;

	}
    }
	
    if (XrmGetResource(rDB,
		       "ldex.geometry",
		       "Ldex.geometry",
		       str_type, &value) == True) {
      /* Get Geometry */
      (void)strncpy(tmp, value.addr, (int)value.size);
    } else {
      (void)strcpy(tmp, "");	/* Clear the string */
    }
    Lisp_Window.width = DEF_WIN_WIDTH;
    Lisp_Window.height = DEF_WIN_HEIGHT;
    Lisp_Window.x = DEF_WIN_X;
    Lisp_Window.y = DEF_WIN_Y;
    bitmask = XParseGeometry(tmp , &(Lisp_Window.x) , &(Lisp_Window.y)
			     , &(Lisp_Window.width) , &(Lisp_Window.height) );

    if (Lisp_Window.x < 0) {
      Lisp_Window.x += Display_Width - (Lisp_Window.width - 1);
    }
    if (Lisp_Window.y < 0) {
      Lisp_Window.y += Display_Height - (Lisp_Window.height - 1);
    }
    if (XrmGetResource(rDB,
		       "ldex.sysout",
		       "Ldex.Sysout",
		       str_type, &value) == True) {
      /* Get Sysout */
      (void)strncpy(sysout_name, value.addr, (int)value.size);
    }
    if (sysout_name == NULL) {
      fprintf(stderr, "Coudn't find a sysout to run;\n");
      print_Xusage( argv[0] );
      exit(1);
    }

    if (XrmGetResource(rDB,
		       "ldex.title",
		       "Ldex.Title",
		       str_type, &value) == True) {
      (void)strncpy(Window_Title, value.addr, (int)value.size);
    } else {
      (void)strcpy(Window_Title,
		   "Medley (C) Copyright 1980-92 by Venue and Fuji Xerox");
    }
    if (XrmGetResource(rDB,
		       "ldex.iconTitle",
		       "Ldex.iconTitle",
		       str_type, &value) == True) {
      (void)strncpy(Icon_Title, value.addr, (int)value.size);
    } else {
      (void)strcpy(Icon_Title, "Medley");
    }

    if (XrmGetResource(rDB,
		       "ldex.iconbitmap",
		       "Ldex.Iconbitmap",
		       str_type, &value) == True) {
      (void)strncpy(iconpixmapfile, value.addr, (int)value.size);
    }

    if (XrmGetResource(rDB,
		       "ldex.NF",
		       "Ldex.NF",
		       str_type, &value) == True) {
      please_fork = 0;
    }

    if (XrmGetResource(rDB,
		       "ldex.maxpages",
		       "Ldex.maxpages",
		       str_type, &value) == True) {
      (void)strncpy(tmp, value.addr, (int)value.size);
      maxpages = atoi(tmp);
    }

    if (XrmGetResource(rDB,
		       "ldex.memory",
		       "Ldex.memory",
		       str_type, &value) == True) {
      (void)strncpy(tmp, value.addr, (int)value.size);
      sysout_size = atoi(tmp);
    }

    if (XrmGetResource(rDB,
		       "ldex.INIT",
		       "Ldex.INIT",
		       str_type, &value) == True) {
      for_makeinit = 1;
    }

    if (XrmGetResource(rDB,
		       "ldex.key",
		       "Ldex.key",
		       str_type, &value) == True) {
      (void)strncpy(keystring, value.addr, (int)value.size);
    }

#ifdef NOETHER
#else
    if (XrmGetResource(rDB,
		       "ldex.EtherNet",
		       "Ldex.EtherNet",
		       str_type, &value) == True) {
      int b0, b1, b2, b3, b4, b5;
      (void)strncpy(tmp, value.addr, (int)value.size);
      if (sscanf(tmp,"%d:%x:%x:%x:%x:%x:%x:%s",&ether_fd,
		 &b0, &b1, &b2, &b3, &b4, &b5, snit.snit_ifname) == 8)
      {
	ether_host[0] = b0; ether_host[1] = b1;
	ether_host[2] = b2; ether_host[3] = b3;
	ether_host[4] = b4; ether_host[5] = b5;
      } else {
	fprintf(stderr, "Missing or bogus -E argument\n");
	ether_fd = -1;
	exit(1);
      }
    }
#endif /* NOETHER */

  }				/* end readXoption */



/************************************************************************/
/*									*/
/*			p r i n t _ l i s p u s a g e			*/
/*									*/
/*	Print out command-line usage info if user enters wrong stuff.	*/
/*									*/
/************************************************************************/

print_lispusage( prog )
  char *prog;
  {
    TPRINT(( "TRACE: print_lisp_usage()\n" ));

    /* Lisp Option */
    fprintf(stderr,"lde[ether] [sysout] [-k access-key]");
    fprintf(stderr," [-E <ethernet-info>]");
    fprintf(stderr,"\n");

  } /* end print_lisp_usage() */




/************************************************************************/
/*									*/
/*			p r i n t _ X u s a g e				*/
/*									*/
/*	Print out command-line options for X, to help user.		*/
/*									*/
/************************************************************************/

print_Xusage( prog )
  char *prog;
  {
    TPRINT(( "TRACE: print_Xusage()\n" ));

    fprintf(stderr,"\t");

    /* X Option */
#ifdef XV11R1
    fprintf(stderr," [-bw <pixels>] [-help] [[<host>]:[<vs>]]");
    fprintf(stderr," [=geometry]\n");
#else /* XV11R1 */

    fprintf(stderr," [-bw <pixels>] [-h[elp]]" );
    fprintf(stderr," [[-d[isplay]] [<host>][:<vs>]]");
    fprintf(stderr,"\n\t");
    fprintf(stderr," [-g[eometry] <geom>] [-sc[reen]] <w>x<h>]\n");	
#endif /* XV11R1 */


  } /* end print_Xusage() */
