/* This is G-file @(#) bin.c Version 2.2 (5/31/88). copyright Xerox & Fuji Xerox  */static char *id = "@(#) bin.c	2.2 5/31/88";/* *	Copyright (C) 1987 by Fuji Xerox Co., Ltd. All rights reserved. * *	Author :  Takeshi Shimizu * *//***********************************************************************//* 		File Name :	bin.c		Desc	:	  				Date :		Jul. 22, 1987 				Edited by :	Takeshi Shimizu				Changed :	 		Including :	OP_bin							*//**********************************************************************/#include "lispemul.h"#include "lispmap.h"#include "emulglobal.h"#include "lispglobal.h"#include "lisptypes.h"#include "address.h"#include "address68k.h"#include "cell.h" #include "stream.h"  #ifdef C_ONLY/**********************************************************************//*		Func name :	OP_bin			Date :		Jul. 22, 1987			Edited by :	Take			changed by :	HAYATA(Sep-01-87)*//**********************************************************************/OP_bin(){register Stream *stream68k; /* stream instance on TOS */register  char *buff68k;     /* pointer to BUFF */  if(GetTypeNumber(TopOfStack) == TYPE_STREAM)   {	stream68k=(Stream *) Addr68k_from_LADDR(TopOfStack);	if(!stream68k->BINABLE){		ufn(040);		return;	}	if(stream68k->COFFSET >= stream68k->CBUFSIZE){		/* end of stream */		ufn(040);		return;	}	/* get BUFFER instance */	buff68k =(char *)Addr68k_from_LADDR(stream68k->CBUFPTR);	/* get BYTE data and set it to TOS */	TopOfStack= S_POSITIVE | (Get_BYTE(buff68k + stream68k->COFFSET)) ;	stream68k->COFFSET++; /* increment offset */	PC++;   }  else  {	ufn(040);	return;  }}#elseN_OP_bin(tos, error_addr)	register int tos;	int *error_addr;{register Stream *stream68k; /* stream instance on TOS */register  char *buff68k;     /* pointer to BUFF */  if(GetTypeNumber(tos) == TYPE_STREAM)   {	stream68k=(Stream *) Addr68k_from_LADDR(tos);	if(!stream68k->BINABLE) ERROR_EXIT(error_addr);	if(stream68k->COFFSET >= stream68k->CBUFSIZE) ERROR_EXIT(error_addr);		/* get BUFFER instance */	buff68k =(char *)Addr68k_from_LADDR(stream68k->CBUFPTR);	/* get BYTE data and set it to TOS */	return(S_POSITIVE | (Get_BYTE(buff68k + (stream68k->COFFSET)++)) );   }  else ERROR_EXIT(error_addr);  }#endif