/* @(#) syscallmsg.c Version 1.7 (9/18/90). copyright venue & Fuji Xerox  */
static char *id = "@(#) syscallmsg.c	1.7 9/18/90	(venue & Fuji Xerox)";


/************************************************************************/
/*									*/
/*	Copyright 1989, 1990 Venue, Fuji Xerox Co., Ltd, Xerox Corp.	*/
/*									*/
/*	This file is work-product resulting from the Xerox/Venue	*/
/*	Agreement dated 18-August-1989 for support of Medley.		*/
/*									*/
/************************************************************************/


#include	<stdio.h>
#include	"osmessage.h"



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
