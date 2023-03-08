/* @(#) perrno.c Version 1.2 (4/22/92). copyright venue & Fuji Xerox  */
static char *id = "@(#) perrno.c	1.2 4/22/92	(venue & Fuji Xerox)";




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

	
#include	<stdio.h>
#include	"osmsg.h"



/************************************************************************/
/*									*/
/*			p e r r o r n					*/
/*									*/
/*	Print the error message to go with a given error number.	*/
/*									*/
/************************************************************************/

extern int errno;
int sys_nerr;
extern char *sys_errlist[];

perrorn(s, n)
  char	*s;
  int	n;
{
  if ( s != NULL && *s != '\0' ) {
    fprintf(stderr, "%s: ",s);
  }
  if (n > 0 && n < sys_nerr) {
    fprintf(stderr, "%s\n", sys_errlist[n]);
  } else {
    fprintf(stderr, "???\n");
  }
}



/************************************************************************/
/*									*/
/*				e r r _ m e s s				*/
/*									*/
/*	Print an error message and call 'perror' to get the		*/
/*	canonical error explanation.  Called by emulator I/O code.	*/
/*									*/
/************************************************************************/

err_mess(from, no)
  char	*from;
  int	no;
  {
    int	save_errno=errno;	/* Save errno around OSMESSAGE_PRINT */


    OSMESSAGE_PRINT({fprintf(stderr,
			     "System call error: %s errno=%d ",
			     from, no); perror("");});

    errno=save_errno;

  }
