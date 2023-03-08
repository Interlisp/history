/* This is G-file @(#) lowlevel2.c Version 2.9 (4/20/90). copyright Xerox & Fuji Xerox  */
static char *id = "@(#) lowlevel2.c	2.9 4/20/90";
/*
 *	Copyright (C) 1987 by Fuji Xerox Co., Ltd. All rights reserved.
 *
 *	Author	:	Hiroshi Hayata
 */
#include <stdio.h>
#include "lispemul.h"
#include "lispglobal.h"
#include "address68k.h"
#include "lispmap.h"
#include "lisptypes.h"
#include "emulglobal.h"

/*** NOTE: these routines likely not called (see inlinedefsC.h) ***/

/************************************************************
 N_OP_addbase
	entry		ADDBASE		OPCODE[0320]

	1.	<<Enter>>
		TopOfStack: offset
		*(CurrentStackPTR): base address
	2.	if High word of TopOfStack is SMALLPL or SMALLNEG,
		then add base address and offset and set result to TopOfStack.
		else call ufn2incs.
	4.	<<Exit>>
		return: new address

***********************************************************/

LispPTR N_OP_addbase(base, offset)
	register int base, offset;
{
	base = 0xFFFFFF & base;
	switch( (0xFFFF0000 & offset) ){
	case S_POSITIVE:
		return(base + (offset & 0x0000FFFF));
	case S_NEGATIVE:
		return(base + (offset | 0xFFFF0000));
	default:
		switch( (GetTypeNumber(offset)) ){
		case TYPE_FIXP:
			/* overflow or underflow isn't check */
			return(base + *(int *)Addr68k_from_LADDR(offset));
		default:	/* floatp also */
			ERROR_EXIT(offset);
		}/* end switch */
	}/* end switch */
}

/************************************************************
 N_OP_getbasebyte
	entry		GETBASEBYTE		OPCODE[0302]

	1.	<<Enter>>
		*(--CurrentStackPTR): base address.
		TopOfStack:	Low word - byte offset.
	2.	if high word of TopOfStack is not SMALLPL,
		then	call ufn2incS.
		else	fetch 8 bits word at (base address + byte offset).
	4.	<<Exit>>
		return:		Least Low Byte - fetched data

***********************************************************/

N_OP_getbasebyte(base_addr, byteoffset)
	register LispPTR base_addr;
	register int byteoffset;
{
	switch( (0xFFFF0000 & byteoffset) ){
	case S_POSITIVE:
		byteoffset =  byteoffset & 0x0000FFFF;
		break;
	case S_NEGATIVE:
		byteoffset = byteoffset | 0xFFFF0000;
		break;
	default:
		switch( (GetTypeNumber(byteoffset)) ){
		case TYPE_FIXP:
			byteoffset = *((int *)Addr68k_from_LADDR(byteoffset));
			break;
		default:	/* floatp also fall thru */
			ERROR_EXIT(byteoffset);
			}/* end switch */
		break;
	}/* end switch */
	return((0xFF & (GETBYTE((char*)Addr68k_from_LADDR((0xFFFFFF & base_addr)) + byteoffset))) | S_POSITIVE);
}

/************************************************************
 N_OP_putbasebyte
	entry		PUTBASEBYTE		OPCODE[0307]

	1.	<<Enter>>
		TopOfStack:	Least Low Byte - replace data.
		*((int *)(CurrentStackPTR-1)): byte offset.
		*((int *)(CurrentStackPTR-2)): base address.
	4.	<<Exit>>
		return:		Least Low Byte - replace data ?

***********************************************************/

N_OP_putbasebyte(base_addr, byteoffset, tos)
	register LispPTR base_addr;
	register int byteoffset;
	register int tos;
{
	if(((0xFFFF0000 & tos ) != S_POSITIVE) || ((unsigned short)tos >= 256))
		ERROR_EXIT(tos);
	switch( (0xFFFF0000 & byteoffset) ){
	case S_POSITIVE:
		byteoffset &=  0x0000FFFF;
		break;
	case S_NEGATIVE:
		byteoffset |=  0xFFFF0000;
		break;
	default:
	/* ucode and ufn don't handle displacement not smallp */
		ERROR_EXIT(tos);
	}/* end switch */
	GETBYTE(((char*)Addr68k_from_LADDR(0xFFFFFF & base_addr)) + byteoffset) = 0xFF & tos;
	return ( tos );
}


