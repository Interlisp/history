/* %Z% %M% Version %I% (%G%). copyright venue & Fuji Xerox  */
static char *id = "%Z% %M%	%I% %G%	(venue & Fuji Xerox)";
/*
*
*
* Copyright (C) 1988 by Fuji Xerox Co.,Ltd. All rights reserved.
*
*		Author: Mitsunori Matsuda
*		Date  : June 5, 1988
*
*/



/************************************************************************/
/*									*/
/*	Copyright 1989, 1990 Venue, Fuji Xerox Co., Ltd, Xerox Corp.	*/
/*									*/
/*	This file is work-product resulting from the Xerox/Venue	*/
/*	Agreement dated 18-August-1989 for support of Medley.		*/
/*									*/
/************************************************************************/


#include <stdio.h>

#ifdef ISC
#include <strings.h>
#else
#include <string.h>
#endif /* ISC */

#include "XVersion.h"
#include "Xdefaults.h"
#include "dbprint.h"

#define FALSE 0
#define TRUE  !FALSE

char *Lisp_Window_Geom 
   , *Display_Name;
char *Lisp_Screen_Size="";

int Auto_Repeat = FALSE; /* Turn on Auto-repeat? */
int Def_Auto_Repeat = FALSE;
int Lisp_Border = DEF_BDRWIDE;

#ifdef ISC
	/* Need to define putc for X11 library's use */
#undef putc
putc(ch, f) int ch,f; {fputc(ch,f); };
#endif ISC




/************************************************************************/
/*									*/
/*			r e a d _ X o p t i o n				*/
/*									*/
/*	Parse command-line options related to X windows.		*/
/*									*/
/************************************************************************/

read_Xoption( argc, argv ) 
  int argc;
  char *argv[];
  {
    int i
      , option
      , pos;

    TPRINT(( "TRACE: read_Xoption()\n" ));

    for( i=1; i<argc; i++ )
      {
	if( (strcmp(argv[i], "-help") == 0)
	   || (strcmp(argv[i], "-h"   ) == 0) )
	  {
	    print_lispusage( argv[0] );
	    print_Xusage( argv[0] );
	    exit(1);
	  }
      }

    option = ((argc > 1) && (argv[1][0] != '-')) ? 2 : 1;
	
    for( i=option ; i<argc; i++ )
      {

#ifdef XV11R1
	if (argv[i][0] == '=') {
			Lisp_Window_Geom = argv[i];
			continue;
		}
#else XV11R1 
	if( (strcmp(argv[i], "-g") == 0 )
		 || (strcmp(argv[i], "-geometry") == 0 ) ) {
			Lisp_Window_Geom = argv[++i];
			continue;
		}
#endif XV11R1

	pos = index( argv[i], ':' ); 

	if(pos != NULL) {
			Display_Name = argv[i];
			continue;
		}

#ifndef XV11R1
	if( (strcmp(argv[i], "-d") == 0 )
		 || (strcmp(argv[i], "-display") == 0 ) ) {
			pos = index( argv[++i], ':' ); 
			if(pos != NULL) {
				Display_Name = argv[i];
			}
			continue;
		}
#endif XV11R1
	/* Border Width */
	if(strcmp(argv[i], "-bw") == 0) {
			if (++i >= argc) {
                        	print_lispusage( argv[0] );
                        	print_Xusage( argv[0] );
                                exit(1);
                        }
			Lisp_Border = atoi( argv[i] );
			continue;
		} 

	/* Keyboad Auto Repeat */
	if( (strcmp(argv[i], "-a") == 0 )
		 || (strcmp(argv[i], "-autorepeat") == 0 ) ) {
			Auto_Repeat = TRUE;
			Def_Auto_Repeat = TRUE;
			if( (++i < argc) && (argv[i][0] != '-') ) {

				if( strcmp(argv[i], "on" ) == 0 ) {
					Auto_Repeat = TRUE;
				} /* end if */

				if( strcmp(argv[i], "off" ) == 0 ) {
					Auto_Repeat = FALSE;
				} /* end if */

			} else {
				i--;
			} /* end if(i) */

			continue;
		} /* end if */

	/* ScreenBitMap Size */
	if( (strcmp(argv[i], "-sc") == 0 )
		 || (strcmp(argv[i], "-screen") == 0 ) ) {
			Lisp_Screen_Size = argv[++i];
			continue;
		} /* end if */

	/* skip Lisp Opition */
	if(strcmp(argv[i], "-t") == 0) {
			i += 1;
			continue;
		} 
	if(strcmp(argv[i], "-m") == 0) {
			i += 1;
			continue;
		} 
	if(strcmp(argv[i], "-NF") == 0) {
			i += 1;
			continue;
		} 
	if(strcmp(argv[i], "-k") == 0) {
			i += 1;
			continue;
		} 
	if(strcmp(argv[i], "-E") == 0) {
			i += 1;
			continue;
		} 
	print_lispusage( argv[0] );
	print_Xusage( argv[0] );
	exit( 1 );		
      } /* end for */
  } /* end readXoption */



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
#else XV11R1
    fprintf(stderr," [-bw <pixels>] [-h[elp]]" );
    fprintf(stderr," [[-d[isplay]] [<host>][:<vs>]]");
    fprintf(stderr,"\n\t");
    fprintf(stderr," [-g[eometry] <geom>] [-a[utorepeat] [on/off]]");
    fprintf(stderr," [-sc[reen]] <w>x<h>]\n");	
#endif XV11R1

  } /* end print_Xusage() */
