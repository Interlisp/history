/* This is G-file @(#) osmessage.h Version 1.2 (6/4/90). copyright Venue & Fuji Xerox  */


/*************************************************
	This is OSMESSAGE stuf.

	Print a console message.
*************************************************/


/************************************************************************/
/*									*/
/*	Copyright 1989, 1990 Venue, Fuji Xerox Co., Ltd, Xerox Corp.	*/
/*									*/
/*	This file is work-product resulting from the Xerox/Venue	*/
/*	Agreement dated 18-August-1989 for support of Medley.		*/
/*									*/
/************************************************************************/


#define	OSMESSAGE_PRINT(print_exp)		\
  {						\
    flush_pty();				\
    print_exp;					\
  }

