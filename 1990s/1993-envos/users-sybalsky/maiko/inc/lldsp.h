/* @(#) lldsp.h Version 1.3 (2/8/93). copyright Venue  */



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


/***************************************************************/
/*
		lldsp.h
		By Takeshi Shimizu

		typedef for 
			FONTDESC,CHARSETINFO,SCREEN,WINDOW

*/
/***************************************************************/
#ifndef BYTESWAP
#ifdef BIGVM
typedef struct {
		LispPTR		FONTDEVICE;
		LispPTR		FONTFAMILY;
		LispPTR		FONTSIZE;
		LispPTR		FONTFACE;
		DLword		SFAscent;
		DLword		SFDescent;
		DLword		SFHeight;
		DLword		ROTATION;
		short		FBBOX;
		short		FBBOY;
		short		FBBDX;
		short		FBBDY;
		LispPTR	SFLKerns;
		LispPTR		SFRWidths;
		LispPTR		FONTDEVICESPEC;
		LispPTR		OTHERDEVICEFONTPROPS;
		LispPTR		FONTSCALE;
		unsigned	SFFACECODE		: 8;
		unsigned	nil		: 8;
		DLword		FONTAVGCHARWIDTH;
		LispPTR		FONTIMAGEWIDTHS;
		LispPTR		FONTCHARSETVECTOR;
		LispPTR		FONTEXTRAFIELD2;
} FONTDESC;
#else
typedef struct {
		LispPTR		FONTDEVICE;
		LispPTR		SFObsolete1;
		LispPTR		FONTFAMILY;
		LispPTR		FONTSIZE;
		LispPTR		FONTFACE;
		LispPTR		SFObsolete2;
		LispPTR		SFObsolete3;
		LispPTR		SFObsolete4;
		DLword		SFObsolete5;
		DLword		SFObsolete6;
		DLword		SFAscent;
		DLword		SFDescent;
		DLword		SFHeight;
		DLword		ROTATION;
		short		FBBOX;
		short		FBBOY;
		short		FBBDX;
		short		FBBDY;
		unsigned	SFFACECODE		: 8;
		unsigned	SFLKerns		:24;
		LispPTR		SFRWidths;
		LispPTR		FONTDEVICESPEC;
		LispPTR		OTHERDEVICEFONTPROPS;
		LispPTR		FONTSCALE;
		DLword		FONTAVGCHARWIDTH;
		DLword		dum;
		LispPTR		FONTIMAGEWIDTHS;
		LispPTR		FONTCHARSETVECTOR;
		LispPTR		FONTEXTRAFIELD2;
} FONTDESC;
#endif /* BIGVM */
typedef struct {
		LispPTR	WIDTHS;
		LispPTR	OFFSETS;
		LispPTR	IMAGEWIDTHS;
		LispPTR	CHARSETBITMAP;
		LispPTR	YWIDTHS;
		DLword	CHARSETASCENT;
		DLword	CHARSETDESCENT;
		LispPTR	LEFTKERN;
 } CHARSETINFO;

#else /* BYTESWAP */
#ifdef BIGVM
typedef struct {
		LispPTR		FONTDEVICE;
		LispPTR		SFObsolete1;
		LispPTR		FONTFAMILY;
		LispPTR		FONTSIZE;
		LispPTR		FONTFACE;
		LispPTR		SFObsolete2;
		LispPTR		SFObsolete3;
		LispPTR		SFObsolete4;
		DLword		SFObsolete6;
		DLword		SFObsolete5;
		DLword		SFDscent;
		DLword		SFAescent;
		DLword		ROTATION;
		DLword		SFHeight;
		short		FBBOY;
		short		FBBOX;
		short		FBBDY;
		short		FBBDX;
		unsigned	SFLKerns		:24;
		LispPTR		SFRWidths;
		LispPTR		FONTDEVICESPEC;
		LispPTR		OTHERDEVICEFONTPROPS;
		LispPTR		FONTSCALE;
		DLword		FONTAVGCHARWIDTH;
		unsigned	nil		: 8;
		unsigned	SFFACECODE		: 8;
		LispPTR		FONTIMAGEWIDTHS;
		LispPTR		FONTCHARSETVECTOR;
		LispPTR		FONTEXTRAFIELD2;
} FONTDESC;
#else
typedef struct {
		LispPTR		FONTDEVICE;
		LispPTR		SFObsolete1;
		LispPTR		FONTFAMILY;
		LispPTR		FONTSIZE;
		LispPTR		FONTFACE;
		LispPTR		SFObsolete2;
		LispPTR		SFObsolete3;
		LispPTR		SFObsolete4;
		DLword		SFObsolete6;
		DLword		SFObsolete5;
		DLword		SFDscent;
		DLword		SFAescent;
		DLword		ROTATION;
		DLword		SFHeight;
		short		FBBOY;
		short		FBBOX;
		short		FBBDY;
		short		FBBDX;
		unsigned	SFLKerns		:24;
		unsigned	SFFACECODE		: 8;
		LispPTR		SFRWidths;
		LispPTR		FONTDEVICESPEC;
		LispPTR		OTHERDEVICEFONTPROPS;
		LispPTR		FONTSCALE;
		DLword		dum;
		DLword		FONTAVGCHARWIDTH;
		LispPTR		FONTIMAGEWIDTHS;
		LispPTR		FONTCHARSETVECTOR;
		LispPTR		FONTEXTRAFIELD2;
} FONTDESC;
#endif /* BIGVM */
typedef struct {
		LispPTR	WIDTHS;
		LispPTR	OFFSETS;
		LispPTR	IMAGEWIDTHS;
		LispPTR	CHARSETBITMAP;
		LispPTR	YWIDTHS;
		DLword	CHARSETDESCENT;
		DLword	CHARSETASCENT;
		LispPTR	LEFTKERN;
 } CHARSETINFO;

#endif /* BYTESWAP */



typedef struct {
		LispPTR SCONOFF;
		LispPTR SCDESTINATION;
		LispPTR SCWIDTH;
		LispPTR SCHEIGHT;
		LispPTR SCTOPW;
		LispPTR SCTOPWDS;
		LispPTR SCTITLEDS;
		LispPTR SCFDEV;
		LispPTR SCDS;
		LispPTR SCDATA;
 } SCREEN;
typedef struct {
		LispPTR DSP;
		LispPTR NEXTW;
		LispPTR SAVE;
		LispPTR REG;
		LispPTR BUTTONEVENTFN;
		LispPTR RIGHTBUTTONFN;
		LispPTR CURSORINFN;
		LispPTR CURSOROUTFN;
		LispPTR CURSORMOVEFN;
		LispPTR REPAINTFN;
		LispPTR RESHAPEFN;
		LispPTR EXTENT;
		LispPTR USERDATA;
		LispPTR VERTSCROLLREG;
		LispPTR HORIZSCROLLREG;
		LispPTR SCROLLFN;
		LispPTR VERTSCROLLWINDOW;
		LispPTR HORIZSCROLLWINDOW;
		LispPTR CLOSEFN;
		LispPTR MOVEFN;
		LispPTR WTITLE;
		LispPTR NEWREGION;
		LispPTR WBORDER;
		LispPTR PROCESS;
		LispPTR WINDOWENTRYFN;
		LispPTR SCREEN;
} WINDOW;