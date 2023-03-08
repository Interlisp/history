/* %Z% %M% Version %I% (%G%). copyright envos & Fuji Xerox  */
static char *id = "%Z% %M%	%I% %G%";
/*** ADOPTED NEW VERSION ***/

/*
 *	Copyright (C) 1987 by Fuji Xerox Co., Ltd. All rights reserved.
 *
 *	Author	:	Osamu Nakamura
 */
#include <stdio.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/file.h>
#include <sundev/kbd.h>
#include <sundev/kbio.h>
#include <sunwindow/window_hs.h>


#include "lispemul.h"

/****************************************************
 *
 *	KB_enable() entry of SUBRCALL 82 1
 *			called from (\KB_enable X)
 *
 ****************************************************/
extern struct screen LispScreen;
extern int LispWindowFd,
	   LispReadFds;

extern int errno;

KB_enable( args )
LispPTR	*args;		/* args[0] :	ON/OFF flag
			 *		T -- ON
			 *		NIL -- OFF
			 */
{
	if( args[0] == ATOM_T )
#ifdef SUNDISPLAY
		LispReadFds |= 1<< LispWindowFd;
#endif SUNDISPLAY
#ifdef XWINDOW
		enable_Xkeyboard();
#endif XWINDOW
	else if( args[0] == NIL )
#ifdef SUNDISPLAY
		LispReadFds &= ~(1 << LispWindowFd);
#endif SUNDISPLAY
#ifdef XWINDOW
		disable_Xkeyboard();
#endif XWINDOW
	else{
		error("KB_enable: illegal arg \n");
		printf("KB_enable: arg = %d\n", args[0] );
	}
}



/****************************************************
 *
 *	KB_beep() entry of SUBRCALL 80 2
 *			called from (\KB_beep SW FREQ)
 *
 ****************************************************/
/*
struct timeval belltime ={
	0,100
};
*/
extern int LispKbdFd;

KB_beep( args )
LispPTR	*args;		/* args[0] :	ON/OFF flag
			 *		T -- ON
			 *		NIL -- OFF
			 * args[1] :	frequency
			 */
{
	int keycommand;

#ifdef SUNDISPLAY
/*	belltime.tv_usec = args[1] & 0xffff;
	win_bell(LispWindowFd, belltime, 0);
*/
	if( (LispKbdFd = open( LispScreen.scr_kbdname, O_RDWR)) == -1)
		fprintf( stderr, "can't open %s, errno=%d\n",
			LispScreen.scr_kbdname, errno);

	if( args[0] == ATOM_T ){
		keycommand = KBD_CMD_BELL;	/* Turn on the bell */
		if(ioctl( LispKbdFd, KIOCCMD, &keycommand)== -1)
			fprintf( stderr, "Error at ioctl errno =%d\n", errno);
	}
	else{
		keycommand = KBD_CMD_NOBELL;	/* Turn off the bell */
		if(ioctl( LispKbdFd, KIOCCMD, &keycommand)== -1)
			fprintf( stderr, "Error at ioctl errno =%d\n", errno);
	}

	close( LispKbdFd );
#endif SUNDISPLAY

#ifdef XWINDOW
	if( args[0] == ATOM_T ) 
		beep_Xkeyboard();
#endif XWINDOW


}



/****************************************************
 *
 *	KB_setmp() entry of SUBRCALL 81 1
 *			called from (\KB_setMP MPCODE)
 *
 ****************************************************/

KB_setmp( args )
LispPTR	*args;		/* args[0] :	MPCODE	*/
{

#ifdef  DEBUG
	printf("MP: %d\n", args[0] & 0xffff );
#endif
}

