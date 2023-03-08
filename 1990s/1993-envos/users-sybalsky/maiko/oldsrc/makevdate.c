/* @(#) makevdate.c Version 1.10 (7/5/91). copyright venue & Fuji Xerox  */
static char *id = "@(#) makevdate.c	1.10 7/5/91	(venue & Fuji Xerox)";

/************************************************************************/
/*									*/
/*	Copyright 1987, 1990 Venue, Fuji Xerox Co., Ltd, Xerox Corp.	*/
/*									*/
/*	This file is work-product resulting from the Xerox/Venue	*/
/*	Agreement dated 18-August-1989 for support of Medley.		*/
/*									*/
/************************************************************************/


/************************************************************************/
/*									*/
/*			m a k e v d a t e . c 				*/
/*									*/
/*	Make the version number to place in the emulator.  That number	*/
/*	will be smashed into the running sysout at the field		*/
/*	InterfacePage->rversion.  The version number is the number	*/
/*	of whole days since 12:00 13-Oct-87 (Takeshi's birthday).	*/
/*									*/
/*	This program prints a single line:				*/
/*		long MDate = <the version number>			*/
/*									*/
/*	That output is redirected to create the file vdate.c, which	*/
/*	is then compiled as part of the emulator MAKE.			*/
/*									*/
/************************************************************************/




#include	<stdio.h>
#ifdef SYSVONLY
#include	<time.h>
#else
#include	<sys/time.h>
#endif SYSVONLY

#ifdef SYSVONLY
	/* RISCOS doesn't have the BSD time functions */
main()
  {
    int dtime;
    time(&dtime);
    fprintf(stderr, "Mdate :%d\n", dtime);
    printf("long MDate= %d;\n", dtime);
    exit(0);
  }
#else
	/* Version for every other Unix */
main()
  {
    struct timeval time;

    gettimeofday(&time, NULL);
    fprintf(stderr, "Mdate :%d\n", time.tv_sec);
    fprintf(stderr, "Version: %s\n", ctime(&time.tv_sec));

    printf("long MDate= %d;\n", time.tv_sec);
    exit(0);
  }

#endif SYSVONLY
