/* This is G-file @(#) initkeyboard.c Version 2.6 (9/14/88). copyright Xerox & Fuji Xerox  */static char *id = "@(#) initkeyboard.c	2.6 9/14/88";/*** ADOPTED NEW VERSION ***//* *	Copyright (C) 1987 by Fuji Xerox Co., Ltd. All rights reserved. * *	Auther	:	Osamu Nakamura	 */#include <stdio.h>#include <sys/types.h>#include <sys/file.h>#include <sundev/kbd.h>#include <sundev/kbio.h>#include <fcntl.h>#include <sunwindow/window_hs.h>#include <sunwindow/cms.h>#include <sys/ioctl.h>#include <sunwindow/win_ioctl.h>#include <pixrect/pixrect_hs.h>#include "lispemul.h"#include "lispmap.h"#include "lispglobal.h"#include "address68k.h"#include "address.h"#include "iopage.h"#include "ifpage.h"extern struct screen LispScreen;extern int LispWindowFd;int LispKbdFd;extern int errno;/*   for debug    */int 	DebugKBD = NIL;FILE	*KBlog;u_int LispReadFds = 0;struct inputmask LispEventMask;int	Intrdisable = NIL;IOPAGE	*IOPage68K;DLword	*EmMouseX68K;DLword	*EmMouseY68K;DLword	*EmCursorX68K;DLword	*EmCursorY68K;DLword	*EmRealUtilin68K;DLword	*EmUtilin68K;DLword	*EmKbdAd068K;DLword	*EmKbdAd168K;DLword	*EmKbdAd268K;DLword	*EmKbdAd368K;DLword	*EmKbdAd468K;DLword	*EmKbdAd568K;DLword	*EmDispInterrupt68K;DLword	*EmCursorBitMap68K;u_char SUNLispKeyMap[128] = {/* 0 */	  -1,  61,  -1,  91,  -1,  97,  99,  -1,/* 8 */  100,  -1,  67,  -1,  68,  -1,  101, -1,/* 16*/   66, 104,  80,  47,  -1,  73,  74,  75,/* 24*/   -1,  92,  63,  -1,  -1,  33,  32,  17,/* 32*/   16,   1,   0,   2,   4,  53,  22,   8,	 /* 40*/	  10,  59,  45,  13,  -1,  81,  82,  83,/* 48*/   -1,  14,  -1,  62,  -1,  34,  19,  18,/* 56*/    3,  48,  49,  51,   6,  23,  25,  11,/* 64*/   58,  29,  15,  -1,  84,  85,  87,  -1,/* 72*/   111,  89,  -1,  -1,  36,  21,  20,   5,/* 80*/	  35,  50,  52,  38,   9,  26,  43,  28,/* 88*/  105,  44,  -1,  94,  69,  70,  -1,  90,/* 96*/   -1,  46,  -1,  41,  40,  24,  37,   7,/*104*/   39,  54,  55,  27,  42,  12,  60,  71,   /*112*/   98,  76,  72,  -1,  -1,  -1,  -1,  56,/*120*/	  31,  57,  93,  -1,  -1,  -1,  -1,  -1,	      }; init_keyboard(){	int keytrans;	set_kbd_iopointers();	if( (LispKbdFd = open( LispScreen.scr_kbdname , O_RDWR)) == -1){		fprintf( stderr, "can't open %s\n", LispScreen.scr_kbdname);		exit( -1 );	}	keytrans = TR_UNTRANS_EVENT;	/* keyboard does not encode key */	if(ioctl( LispKbdFd, KIOCTRANS, &keytrans)== -1){		fprintf( stderr, "Error at ioctl errnoo =%d\n", errno);			exit( -1 );	}	close( LispKbdFd );	seteventmask( &LispEventMask );}device_before_exit(){	int keytrans;		if( (LispKbdFd = open( LispScreen.scr_kbdname , O_RDWR)) == -1){		fprintf( stderr, "can't open %s\n", LispScreen.scr_kbdname);		exit( -1 );	}	keytrans = TR_EVENT;	/* keyboard encodes key */	if(ioctl( LispKbdFd, KIOCTRANS, &keytrans)== -1){		fprintf( stderr, "Error at ioctl errnoo =%d\n", errno);			exit( -1 );	}	close( LispKbdFd );	display_before_exit();}set_kbd_iopointers(){	IOPage68K = (IOPAGE *)IOPage;	EmMouseX68K = (DLword *) &(IOPage68K->dlmousex);	EmMouseY68K = (DLword *) &(IOPage68K->dlmousey);	EmCursorX68K = (DLword *) &(IOPage68K->dlcursorx);	EmCursorY68K = (DLword *) &(IOPage68K->dlcursory);	EmRealUtilin68K = (DLword *) &(IOPage68K->dlutilin);	/* EmUtilin68K is for KEYDOWNP1 macro or etc. */	EmUtilin68K = (DLword *) &(InterfacePage->fakemousebits);	EmKbdAd068K = (DLword *) &(IOPage68K->dlkbdad0);	EmKbdAd168K = (DLword *) &(IOPage68K->dlkbdad1);	EmKbdAd268K = (DLword *) &(IOPage68K->dlkbdad2);	EmKbdAd368K = (DLword *) &(IOPage68K->dlkbdad3);	EmKbdAd468K = (DLword *) &(IOPage68K->dlkbdad4);	EmKbdAd568K = (DLword *) &(IOPage68K->dlkbdad5);	EmDispInterrupt68K = (DLword *) &(IOPage68K->dldispinterrupt);	EmCursorBitMap68K = (DLword *) (IOPage68K->dlcursorbitmap);}seteventmask( eventmask )struct inputmask *eventmask;{	input_imnull( eventmask );	eventmask->im_flags  |=  IM_ASCII | IM_NEGASCII | IM_NEGEVENT;				win_setinputcodebit( eventmask, MS_LEFT);	win_setinputcodebit( eventmask, MS_MIDDLE);	win_setinputcodebit(  eventmask, MS_RIGHT);	win_setinputcodebit( eventmask, LOC_MOVE);	win_unsetinputcodebit( eventmask, LOC_STILL);	win_unsetinputcodebit( eventmask, LOC_MOVEWHILEBUTDOWN);	win_unsetinputcodebit(  eventmask, LOC_WINENTER);	win_unsetinputcodebit( eventmask, LOC_WINEXIT);	win_setinputmask( LispWindowFd, eventmask, eventmask, WIN_NULLLINK);}