/* %Z% %M% Version %I% (%G%). copyright envos & Fuji Xerox  */
static char *id = "%Z% %M%	%I% %G%		(envos & Fuji Xerox)";

/*
 *	Copyright (C) 1987, 1989 by Fuji Xerox Co., Ltd.,
 *				    Venue, and Envos Corporation.
 *		  All rights reserved.
 *
 *	Author	:	Osamu Nakamura
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
#include <sys/types.h>
#include <sys/file.h>
#include <sundev/kbd.h>
#include <sundev/kbio.h>
#include <fcntl.h>
#include <sunwindow/window_hs.h>
#include <sunwindow/cms.h>
#include <sys/ioctl.h>
#include <sunwindow/win_ioctl.h>
#include <pixrect/pixrect_hs.h>

#include "lispemul.h"
#include "lispmap.h"
#include "lispglobal.h"
#include "address68k.h"
#include "address.h"

#include "devconfig.h"
#include "iopage.h"
#include "ifpage.h"

extern struct screen LispScreen;
extern int LispWindowFd;
int LispKbdFd;
extern int errno;

/*   for debug    */
int	DebugKBD = NIL;
FILE	*KBlog;

u_int LispReadFds = 0;
struct inputmask LispEventMask;


IOPAGE	*IOPage68K;

DLword	*EmMouseX68K;
DLword	*EmMouseY68K;
DLword	*EmCursorX68K;
DLword	*EmCursorY68K;
DLword	*EmRealUtilin68K;
DLword	*EmUtilin68K;
DLword	*EmKbdAd068K;
DLword	*EmKbdAd168K;
DLword	*EmKbdAd268K;
DLword	*EmKbdAd368K;
DLword	*EmKbdAd468K;
DLword	*EmKbdAd568K;
DLword	*EmDispInterrupt68K;
DLword	*EmCursorBitMap68K;

/*u_char SUNLispKeyMap[128];*/
u_char *SUNLispKeyMap;

/* keymap for type3 */
u_char SUNLispKeyMap_for3[128] = {

/* 0 */	  -1,  61,  -1,  91,  -1,  97,  99,  -1,
/* 8 */  100,  -1,  67,  -1,  68,  -1, 101,  -1,
/* 16*/   66, 104,  80,  47,  -1,  73,  74,  75,
/* 24*/   -1,  92,  63,  -1,  -1,  33,  32,  17,
/* 32*/   16,   1,   0,   2,   4,  53,  22,   8,
/* 40*/	  10,  59,  45,  13,  -1,  81,  82,  83,
/* 48*/   -1,  14,  -1,  62,  -1,  34,  19,  18,
/* 56*/    3,  48,  49,  51,   6,  23,  25,  11,
/* 64*/   58,  29,  15,  -1,  84,  85,  87,  -1,
/* 72*/  111,  89,  -1,  -1,  36,  21,  20,   5,
/* 80*/	  35,  50,  52,  38,   9,  26,  43,  28,
/* 88*/  105,  44,  -1,  94,  69,  70,  -1,  90,
/* 96*/   -1,  46,  -1,  41,  40,  24,  37,   7,
/*104*/   39,  54,  55,  27,  42,  12,  60,  71,
/*112*/   98,  76,  72,  -1,  -1,  -1,  -1,  56,
/*120*/	  31,  57,  93,  -1,  -1,  -1,  -1,  -1,
 };

/* for type4 */

u_char SUNLispKeyMap_for4[128] = {

/* 0 */   -1,  61,  -1,  91,  -1,  97,  99, 106,
/* 8 */  100, 107,  67, 108,  68,  47, 101,  -1,
/* 16*/   66, 104,  80,  31,  -1,  75, 110,  74,
/* 24*/   -1, 109,  63,  -1,  -1,  33,  32,  17,
/* 32*/   16,   1,   0,   2,   4,  53,  22,   8,
/* 40*/   10,  59,  45,  15,  -1,  64,  65,  95,
/* 48*/   -1,  14,  13,  89,  -1,  34,  19,  18,
/* 56*/    3,  48,  49,  51,   6,  23,  25,  11,
/* 64*/   58,  29,  13,  93,  81,  82,  83,  96,
/* 72*/  111,  62,  -1,  -1,  36,  21,  20,   5,
/* 80*/   35,  50,  52,  38,   9,  26,  43,  28,
/* 88*/  105,  44,  76,  84,  85,  87,  98,  90,
/* 96*/   -1,  46,  73,  41,  40,  24,  37,   7,
/*104*/   39,  54,  55,  27,  42,  12,  60,  71,
/*112*/   94,  69,  70,  -1,  -1,  -1,  92,  56,
/*120*/   86,  57,  88,  -1,  -1, 102,  -1,  -1,
 };

/* for jle */

u_char SUNLispKeyMap_jle[128] = {

/* 0 */   -1,  61,  -1,  91,  -1,  97,  99, 106,
/* 8 */  100, 107,  67, 108,  68,  47, 101,  71,
/* 16*/   66, 104,  80,  31,  -1,  75, 110,  74,
/* 24*/   -1, 109,  63,  -1,  -1,  33,  32,  17,
/* 32*/   16,   1,   0,   2,   4,  53,  22,   8,
/* 40*/   59,  45,  30,  15,  -1,  64,  65,  95,
/* 48*/   -1,  14,  13,  89,  -1,  34,  19,  18,
/* 56*/    3,  48,  49,  51,   6,  23,  25,  11,
/* 64*/   58,  29,  13,  93,  81,  82,  83,  96,
/* 72*/  111,  62,  -1,  -1,  36,  21,  20,   5,
/* 80*/   35,  50,  52,  38,   9,  26,  43,  28,
/* 88*/  105,  44,  76,  84,  85,  87,  98,  90,
/* 96*/   -1,  46,  73,  41,  40,  24,  37,   7,
/*104*/   39,  54,  55,  27,  42,  12,  60,  10,
/*112*/   94,  69,  70,  72, 103, 109,  92,  56,
/*120*/   86,  57,  88,  -1,  -1, 102,  -1,  -1,
 };
/* [40] 10->59  */
/* [41] 59->45  */
/* [42] 45->30  */
/* [111] 71->10 */
/* [115] -1 -> 72  Kakutei */
/* [116] -1 -> 103 Henkan */
/* [117] -1 -> 109 Nihongo On-Off */

/*  ----------------------------------------------------------------*/

init_keyboard(flg)
  int flg ; /* if 0 init else re-init */
  {
    int keytrans;

    set_kbd_iopointers();

#ifdef SUNDISPLAY
    if( (LispKbdFd = open( LispScreen.scr_kbdname , O_RDWR)) == -1)
      {
	fprintf( stderr, "can't open %s\n", LispScreen.scr_kbdname);
	exit( -1 );
      }
#endif SUNDISPLAY

    if(flg==0)
      {
	keyboardtype(LispKbdFd);
      }

#ifdef SUNDISPLAY
    keytrans = TR_UNTRANS_EVENT;	/* keyboard does not encode key */
    if(ioctl( LispKbdFd, KIOCTRANS, &keytrans)== -1)
      {
	fprintf( stderr, "Error at ioctl errnoo =%d\n", errno);
	exit( -1 );
      }
    close( LispKbdFd );

    seteventmask( &LispEventMask );
#endif SUNDISPLAY

#ifdef XWINDOW
    init_Xevent();
#endif XWINDOW
}

/*  ----------------------------------------------------------------*/

device_before_exit()
{
#ifdef SUNDISPLAY
	int keytrans;

	if( (LispKbdFd = open( LispScreen.scr_kbdname , O_RDWR)) == -1){
		fprintf( stderr, "can't open %s\n", LispScreen.scr_kbdname);
		exit( -1 );
	}

	keytrans = TR_EVENT;	/* keyboard encodes key */
	if(ioctl( LispKbdFd, KIOCTRANS, &keytrans)== -1){
		fprintf( stderr, "Error at ioctl errnoo =%d\n", errno);
			exit( -1 );
	}
	close( LispKbdFd );
#endif SUNDISPLAY
	display_before_exit();
}

/*  ----------------------------------------------------------------*/

set_kbd_iopointers()
{
	IOPage68K       = (IOPAGE *)IOPage;
	EmMouseX68K     = (DLword *) &(IOPage68K->dlmousex);
	EmMouseY68K     = (DLword *) &(IOPage68K->dlmousey);
	EmCursorX68K    = (DLword *) &(IOPage68K->dlcursorx);
	EmCursorY68K    = (DLword *) &(IOPage68K->dlcursory);
	EmRealUtilin68K = (DLword *) &(IOPage68K->dlutilin);
	/* EmUtilin68K is for KEYDOWNP1 macro or etc. */
	EmUtilin68K = (DLword *) &(InterfacePage->fakemousebits);
	EmKbdAd068K = (DLword *) &(IOPage68K->dlkbdad0);
	EmKbdAd168K = (DLword *) &(IOPage68K->dlkbdad1);
	EmKbdAd268K = (DLword *) &(IOPage68K->dlkbdad2);
	EmKbdAd368K = (DLword *) &(IOPage68K->dlkbdad3);
	EmKbdAd468K = (DLword *) &(IOPage68K->dlkbdad4);
	EmKbdAd568K = (DLword *) &(IOPage68K->dlkbdad5);
	EmDispInterrupt68K = (DLword *) &(IOPage68K->dldispinterrupt);
	EmCursorBitMap68K  = (DLword *)  (IOPage68K->dlcursorbitmap);
}

/*  ----------------------------------------------------------------*/

#ifdef SUNDISPLAY
seteventmask( eventmask )
struct inputmask *eventmask;
{
	input_imnull( eventmask );
	eventmask->im_flags  |=  IM_ASCII | IM_NEGASCII | IM_NEGEVENT;

	win_setinputcodebit  ( eventmask, MS_LEFT );
	win_setinputcodebit  ( eventmask, MS_MIDDLE );
	win_setinputcodebit  ( eventmask, MS_RIGHT );
	win_setinputcodebit  ( eventmask, LOC_MOVE );
	win_unsetinputcodebit( eventmask, LOC_STILL );
	win_unsetinputcodebit( eventmask, LOC_MOVEWHILEBUTDOWN );
	win_unsetinputcodebit( eventmask, LOC_WINENTER );
	win_unsetinputcodebit( eventmask, LOC_WINEXIT );

	win_setinputmask( LispWindowFd, eventmask, eventmask, WIN_NULLLINK);
}
#endif SUNDISPLAY


char* getenv();		/*  ---- external entry points --------*/

#define MIN_KEYTYPE 3
#define KB_AS3000J (7 + MIN_KEYTYPE)

/* KB_SUN4 not defined in older OS versions */
#ifndef KB_SUN4
#define KB_SUN4 4
#endif

/* For the JLE keyboard */
#define KB_JLE 5

/*  ----------------------------------------------------------------*/
/*********************************************************/
/*
	keyboardtype(fd)

	Determine the keyboard type
	by checking LDEKBDTYPE
	If it is not set,then print the message
	and exit to SHELL (for Fuji).
	If LDEKBDTYPE's value doesn't match then
	it is treated as type3
*/
/*********************************************************/
keyboardtype(fd)
int fd;
{
 int type;
 int i;
 char *key;

 for(i=0;i<5000;i++){/* IDLE LOOP */}

 /* clear the keyboard field in devconfig */
 InterfacePage->devconfig &= 0xfff8;

/************************************************************
 Due to the problems of SunOS 4.0 & 4.0.1
 calling ioctl never return the correct keyboard type.
 So,these 2 lines are commented out ...(Take)->AR11100
*************************************************************/

/* Get keytype from LDEKBDTYPE  */
 if ((key = getenv("LDEKBDTYPE")) == 0) {
#ifdef XWINDOW
#define FUJI
#endif XWINDOW
#ifdef FUJI
	/* obnoxious behavior */
	mess_reset();
	printf("!!CAUTION: LDEKBDTYPE is not set.\n");
	printf("Please retry after setting LDEKBDTYPE correctly.\n");
	printf("Usage: setenv LDEKBDTYPE <kbdtype>\n");
	printf("       (one of type2, type3, type4, jle, or as3000j)");
	exit(0); /* exit to shell */
#else
  	if(ioctl(fd,KIOCTYPE,&type) !=0) {
		error("keyboardtype:IOCTL(KIOCTYPE) fails (cont. w. type-3");
		type = KB_SUN3;
		}	/* otherwise, type is set */
#endif
#ifdef XWINDOW
#undef FUJI
#endif XWINDOW
 }/* if end */
 else {
	if      (strcmp("as3000j", key)==0) type = KB_AS3000J;
	else if (strcmp("type4",   key)==0) type = KB_SUN4;
	else if (strcmp("type2",   key)==0) type = KB_SUN2;
        else if (strcmp("jle",     key)==0) type = KB_JLE;
	else     type = KB_SUN3;           /* default */
       }


 switch(type) {
	case KB_SUN2 : /* type2, we still use keymap for type3 */
		SUNLispKeyMap = SUNLispKeyMap_for3;
		/* MIN_KEYTYPE is 3,so we can't set devconfig correctly */
		/* Therefore type2 may treat as type3 */
		InterfacePage->devconfig |= 0;
		break;
	case KB_SUN3 : /* type3 */
		SUNLispKeyMap = SUNLispKeyMap_for3;
		InterfacePage->devconfig |= type-MIN_KEYTYPE;
		break;
	case KB_SUN4 : /* type4 */
		SUNLispKeyMap = SUNLispKeyMap_for4;
		InterfacePage->devconfig |= type-MIN_KEYTYPE;
		break;
	case KB_JLE : /* JLE */
		/*printf("jle\n"); */
		SUNLispKeyMap=SUNLispKeyMap_jle;
		InterfacePage->devconfig |= type-MIN_KEYTYPE;
		/* InterfacePage->devconfig |= 4-MIN_KEYTYPE; */
		break;
	case KB_AS3000J : /* for AS, use type4 map */
		SUNLispKeyMap = SUNLispKeyMap_for4;
		InterfacePage->devconfig |= type-MIN_KEYTYPE;/* 7 */
		break;
	default: { char errmsg [ 200 ];
		sprintf ( errmsg, "Unsupported keyboard type: %d", type);
                printf ( "%s\n", errmsg);
                printf ( "Configuring keyboard for type-3\n", errmsg);
                SUNLispKeyMap = SUNLispKeyMap_for3;
                InterfacePage->devconfig |= KB_SUN3-MIN_KEYTYPE;
		break;
		}
	}

}/* end keyboardtype*/

