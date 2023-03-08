/* @(#) stream.h Version 2.7 (2/8/93). copyright Venue   */



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


#ifndef BYTESWAP
	/********************************/
	/* Normal byte-order definition */
	/********************************/
typedef struct	stream{
	DLword	COFFSET;
     DLword	CBUFSIZE;
#ifndef BIGVM
     unsigned	BINABLE	:1;
     unsigned	BOUTABLE	:1;
     unsigned	EXTENDABLE	:1;
     unsigned	CBUFDIRTY	:1;
     unsigned	PEEKEDCHARP	:1;
	unsigned  ACCESS	:3;
     unsigned	CBUFPTR		:24;
#else
     unsigned	PEEKEDCHARP	:1;
	unsigned  ACCESS	:3;
     unsigned	CBUFPTR		:28;
#endif /* BIGVM */
     DLbyte	BYTESIZE;
     DLbyte	CHARSET;
     DLword	PEEKEDCHAR;
     DLword	CHARPOSITION;
     DLword	CBUFMAXSIZE;
     unsigned	NONDEFAULTDATEFLG	:1;
     unsigned	REVALIDATEFLG	:1;
     unsigned	MULTIBUFFERHINT	:1;
     unsigned	USERCLOSEABLE	:1;
#ifndef BIGVM
     unsigned	USERVISIBLE	:1;
     unsigned	EOLCONVENTION	:2;
     unsigned	NIL1	:1;
     unsigned	FULLFILENAME	:24;
#else
     unsigned	FULLFILENAME	:28;
#endif /* BIGVM */
#ifdef BIGVM
     unsigned	BINABLE	:1;
     unsigned	BOUTABLE	:1;
     unsigned	EXTENDABLE	:1;
     unsigned	CBUFDIRTY	:1;
     unsigned	DEVICE: 28;
#else
     LispPTR	DEVICE;
#endif /* BIGVM */
#ifdef BIGVM
     unsigned	USERVISIBLE	:1;
     unsigned	EOLCONVENTION	:2;
     unsigned	NIL1	:1;
     unsigned	VALIDATION: 28;
#else
     LispPTR	VALIDATION;
#endif /* BIGVM */
     LispPTR	CPAGE;
     LispPTR	EPAGE;
     DLword	EOFFSET;
     DLword	LINELENGTH;
     LispPTR	F1;
     LispPTR	F2;
     LispPTR	F3;
     LispPTR	F4;
     LispPTR	F5;
     DLword	FW6;
     DLword	FW7;
     DLword	FW8;
     DLword	FW9;
     LispPTR	F10;
     LispPTR	STRMBINFN;
     LispPTR	STRMBOUTFN;
     LispPTR	OUTCHARFN;
     LispPTR	ENDOFSTREAMOP;
     LispPTR	OTHERPROPS;
     LispPTR	IMAGEOPS;
     LispPTR	IMAGEDATA;
     LispPTR	BUFFS;
     DLword	MAXBUFFERS;
     DLword	NIL2;
     LispPTR	EXTRASTREAMOP;
}Stream;

#else

	/***************************/
	/* Byte-swapped definition */
	/***************************/
typedef struct	stream
  {
     DLword	CBUFSIZE;
	DLword	COFFSET;
     unsigned	CBUFPTR		:24;
	unsigned  ACCESS	:3;
     unsigned	PEEKEDCHARP	:1;
     unsigned	CBUFDIRTY	:1;
     unsigned	EXTENDABLE	:1;
     unsigned	BOUTABLE	:1;
     unsigned	BINABLE	:1;
     DLword	PEEKEDCHAR;
     DLbyte	CHARSET;
     DLbyte	BYTESIZE;
     DLword	CBUFMAXSIZE;
     DLword	CHARPOSITION;
     unsigned	FULLFILENAME	:24;
     unsigned	NIL1	:1;
     unsigned	EOLCONVENTION	:2;
     unsigned	USERVISIBLE	:1;
     unsigned	USERCLOSEABLE	:1;
     unsigned	MULTIBUFFERHINT	:1;
     unsigned	REVALIDATEFLG	:1;
     unsigned	NONDEFAULTDATEFLG	:1;
     LispPTR	DEVICE;
     LispPTR	VALIDATION;
     LispPTR	CPAGE;
     LispPTR	EPAGE;
     DLword	LINELENGTH;
     DLword	EOFFSET;
     LispPTR	F1;
     LispPTR	F2;
     LispPTR	F3;
     LispPTR	F4;
     LispPTR	F5;
     DLword	FW7;
     DLword	FW6;
     DLword	FW9;
     DLword	FW8;
     LispPTR	F10;
     LispPTR	STRMBINFN;
     LispPTR	STRMBOUTFN;
     LispPTR	OUTCHARFN;
     LispPTR	ENDOFSTREAMOP;
     LispPTR	OTHERPROPS;
     LispPTR	IMAGEOPS;
     LispPTR	IMAGEDATA;
     LispPTR	BUFFS;
     DLword	NIL2;
     DLword	MAXBUFFERS;
     LispPTR	EXTRASTREAMOP;
}Stream;

#endif /* BYTESWAP */

