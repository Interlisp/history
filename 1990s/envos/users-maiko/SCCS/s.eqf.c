h61930s 00001/00003/00308d D 2.15 93/02/08 14:50:58 sybalsky 19 18c Big VM (and new CDR coding) changes for 3.0 \nes 00004/00004/00307d D 2.14 92/04/21 17:10:45 sybalsky 18 17c shortening file names for DOS \nes 00151/00108/00160d D 2.13 91/02/07 20:41:21 sybalsky 17 16c Fix numeric type test to use type mask constant names, instead of 0xconstant.  Reformat code.es 00000/00000/00268d D 2.12 90/04/20 01:28:28 sybalsky 16 15c  file names, bulk change.es 00001/00000/00267d D 2.11 90/03/21 12:25:08 takeshi 15 14c includes fp.hes 00004/00003/00263d D 2.10 90/03/16 11:41:51 takeshi 14 13c N_OP_eqq use GetTypeEntryes 00020/00004/00246d D 2.9 90/03/02 11:13:24 sybalsky 13 12c Reformat code, add comments, check for byte swap needs.es 00005/00005/00245d D 2.8 89/10/19 17:59:05 sybalsky 12 11c punt EQUAL changeses 00003/00003/00247d D 2.7 89/03/27 15:44:37 sybalsky 11 10c Word-ptr fixup for MDStypetbl, plus changed some constants to named type-mask values.es 00017/00016/00233d D 2.6 88/11/30 19:17:25 shih 10 9c restored sccs stamp, minor cleanupes 00019/00023/00230d D 2.5 88/10/12 14:41:56 krivacic 9 8c new out-of-line interfacees 00000/00004/00253d D 2.4 88/09/27 16:44:36 krivacic 8 7c sun 4 merge, remove tracees 00009/00006/00248d D 2.3 88/06/24 19:12:50 charnley 7 6c fixed ar 10532 -- = op ufning too frequently.es 00147/00067/00107d D 2.2 88/05/31 19:55:35 masinter 6 5c Fix many bugs in equal ops, merge equal.c herees 00000/00000/00174d D 2.1 88/05/17 09:23:33 hayata 5 4c Version up to 2.1es 00002/00002/00172d D 1.4 88/05/13 10:09:02 hayata 4 3c Add SCCS keyides 00058/00036/00116d D 1.3 88/05/11 13:09:05 shih 3 2c Corrected bugs in cl:=es 00010/00008/00142d D 1.2 88/05/10 13:34:12 charnley 2 1c fixed bug in FIXP and FLOATP eq tests.es 00150/00000/00000d D 1.1 88/05/06 16:20:03 charnley 1 0c date and time created 88/05/06 16:20:03 by charnleyeuUtTI 1D 2/* This is G-file %Z% %M% Version %I% (%G%). copyright Xerox & Fuji Xerox  */static char *id = "%Z% %M%	%I% %G%";E 2I 2D 4/* This is G-file @(#) eqf.c Version 1.1 (5/6/88). copyright Xerox & Fuji Xerox  */static char *id = "@(#) eqf.c	1.1 5/6/88";E 4I 4D 7/* This is G-file %Z% %M% Version %I% (%G%). copyright Xerox & Fuji Xerox  */static char *id = "%Z% %M%	%I% %G%";E 7I 7D 10/* This is G-file @(#) eqf.c Version 2.2 (5/31/88). copyright Xerox & Fuji Xerox  */static char *id = "@(#) eqf.c	2.2 5/31/88";E 10I 10D 12/* %Z% %M% Version %I% (%G%). copyright envos & Fuji Xerox  */static char *id = "%Z% %M%	%I% %G%		(envos & Fuji Xerox)";E 12I 12D 13/* @(#) eqf.c Version 2.6 (11/30/88). copyright envos & Fuji Xerox  */static char *id = "@(#) eqf.c	2.6 11/30/88		(envos & Fuji Xerox)";E 13I 13/* %Z% %M% Version %I% (%G%). copyright venue & Fuji Xerox  */static char *id = "%Z% %M%	%I% %G%	(venue & Fuji Xerox)";E 13E 12E 10E 7E 4E 2D 13/*	eqf.c */E 13I 13/************************************************************************//*									*//*									*//*									*//*									*//*									*//************************************************************************//************************************************************************//*									*//*	Copyright 1989, 1990 Venue, Fuji Xerox Co., Ltd, Xerox Corp.	*//*									*//*	This file is work-product resulting from the Xerox/Venue	*//*	Agreement dated 18-August-1989 for support of Medley.		*//*									*//************************************************************************/E 13#include <stdio.h>#include "lispemul.h"D 18#include "lispglobal.h"#include "address68k.h"E 18I 18#include "lspglob.h"#include "adr68k.h"E 18#include "lispmap.h"D 18#include "lisptypes.h"E 18I 18#include "lsptypes.h"E 18I 15#include "fp.h"E 15#include "my.h"I 6#include "arith.h"E 6I 7D 10#define GetTypeWord(address)  (*(MDStypetbl +(((address) & 0x0ffff00)>>9)))   E 10I 10D 11#define GetTypeWord(address)  (*(MDStypetbl +(((address) & 0x0ffff00)>>9)))E 11I 11D 12#define GetTypeWord(address)  (GETWORD(MDStypetbl +(((address) & 0x0ffff00)>>9)))E 12I 12D 14#define GetTypeWord(address)  (*(MDStypetbl +(((address) & 0x0ffff00)>>9)))E 14I 14D 18/* Instead of using this, use GetTypeEntry in lisptypes.h */E 18I 18D 19/* Instead of using this, use GetTypeEntry in lsptypes.h */E 18/*#define GetTypeWord(address)  (*(MDStypetbl +(((address) & 0x0ffff00)>>9)))*/E 19E 14E 12E 11E 10E 7/************************************************************D 6N_OP_eqlop    -- op 072      EQL    --  elsewhereN_OP_clequal  -- op 0314     CL:EQUALN_OP_eq       -- op 0360     EQ     --  elsewhereN_OP_equal    -- op 0364     IL:EQUALN_OP_eqq      -- op 0377     CL:=E 6I 6D 10op 072   N_OP_eqlop   	EQL E 10I 10op 072   N_OP_eqlop	EQLE 10op 0314  N_OP_clequal   CL:EQUALD 10op 0360  (inline)   	EQop 0364  N_OP_equal  	IL:EQUALop 0377  N_OP_eqq   	CL:=E 10I 10op 0360  (inline)	EQop 0364  N_OP_equal	IL:EQUALop 0377  N_OP_eqq	CL:=E 10E 6***********************************************************/D 6/***	current stateE 6I 6/* differences between these operations:E 6D 6 case 072 : case072: EQLOP;#define EQLOP	{							\		 TOPOFSTACK = N_OP_eqlop(POP_TOS_1, TOPOFSTACK, ufn_2);	\		 nextop1;						\		} case 0314 : case0314:	CLEQUAL;#define CLEQUAL		{ goto op_ufn; } case 0360 : case0360: {		if(TOPOFSTACK == POP_TOS_1)			TOPOFSTACK = ATOM_T;		else	TOPOFSTACK = NIL_PTR;		nextop1;		} case 0364 : case0364:  ILEQUAL;#define ILEQUAL		{ goto op_ufn; } case 0377 : case0377: 	CLARITHEQUAL;#define CLARITHEQUAL	{ goto op_ufn; }***/E 6I 6EQ is a strict pointer comparision, equivalent to C's ==E 6I 6EQL (common lisp) does no conversions before comparision, but will	compare equal FIXPs or equal FLOATPs.E 6D 6N_OP_clequal(arg1, arg2, error_addr) /* opcode 0314 */E 6I 6CL:=  will do a numeric comparison      and will compare floats. If given integers, it will convertD 10 	to floating point first.E 10I 10	to floating point first.E 10IL:EQUAL  is a recursive comparison which will compare 1 = 1.0	  it work like code with CL:= for the most partCL:EQUAL is a recursive comparision which uses EQL at the leavesInterlisp operations IEQP, FEQP have no opcodes, although thereis an unboxed FEQP.number types include:SMALLP	(immediate with S_POSITIVE or S_NEGATIVE)FIXP	(32 bit boxed value, handled in C. Usually canonical, i.e.,	 will be SMALLP. (IPLUS x 0) will always canonicallize.)FLOATP  (32 bit boxed value, handled in C, usually)RATIO	(a/b. Always canonical, i.e., b doesn't divide a evenly)COMPLEX (a+bi. Not handled in C)BIGNUM  (integer that can't be represented bigger than 32 bits)*/D 10#define IF_IMMEDIATE(arg, doit, doitsmall) 		\E 10I 10#define IF_IMMEDIATE(arg, doit, doitsmall)		\E 10D 19   switch(0xFFFF0000 & arg) {				\E 19I 19   switch(SEGMASK & arg) {				\E 19	case ATOMS_OFFSET:	doit;			\	case S_CHARACTER:	doit;			\	case S_POSITIVE:	doitsmall;		\	case S_NEGATIVE:	doitsmall;		\	}D 17/************************************************************Common Lisp EQUAL.  Opcode 0314***********************************************************/E 17I 17/************************************************************************//*									*//*			N _ O P _ c l e q u a l				*//*									*//*	Common Lisp EQUAL, opcode 0314.					*//*									*//************************************************************************/E 17D 9int N_OP_clequal(arg1, arg2, error_addr)E 9I 9int N_OP_clequal(arg1, arg2)E 9E 6register int arg1, arg2;D 9int error_addr;E 9D 17{register int type;E 17I 17  {    register int type;E 17D 6#ifdef	TRACE	printPC();	printf("TRACE: N_OP_clequal()\n");#endifE 6I 6D 17  if (arg2 == arg1) return(ATOM_T);  IF_IMMEDIATE(arg1, return(NIL), return(NIL));  IF_IMMEDIATE(arg2, return(NIL), return(NIL));E 17I 17    if (arg2 == arg1) return(ATOM_T);    IF_IMMEDIATE(arg1, return(NIL), return(NIL));    IF_IMMEDIATE(arg2, return(NIL), return(NIL));E 17E 6I 6D 17/* CL:EQUAL is true for two strings that have different Interlisp   type numbers; cannot currently handle it here. */E 17I 17    /* CL:EQUAL is true for two strings that have different Interlisp      type numbers; cannot currently handle it here. */E 17D 17/* can return NIL if one is a number and the other isn't */E 17I 17    /* can return NIL if one is a number and the other isn't */E 17D 17  if (IsNumber(arg1)) { if(!IsNumber(arg2)) return(NIL); }  else {if (IsNumber(arg2)) {return(NIL);}D 9	else ERROR_EXIT(error_addr)}E 9I 9	else ERROR_EXIT(arg2)}E 17I 17    if (IsNumber(arg1)) { if(!IsNumber(arg2)) return(NIL); }    else {if (IsNumber(arg2)) {return(NIL);}    else ERROR_EXIT(arg2)}E 17E 9D 17/* now we know both are numbers */E 17I 17    /* now we know both are numbers */E 17D 17  if ((type = GetTypeNumber(arg1)) != (GetTypeNumber(arg2))) return(NIL);E 17I 17    if ((type = GetTypeNumber(arg1)) != (GetTypeNumber(arg2))) return(NIL);E 17D 17/* now we know both are the same type. Shouldn't see any SMALLPs */E 17I 17    /* now we know both are the same type. Shouldn't see any SMALLPs */E 17D 17  switch (type) {	case TYPE_FIXP:	if (FIXP_VALUE(arg1) == FIXP_VALUE(arg2)) {return(ATOM_T);}E 17I 17    switch (type)      {	case TYPE_FIXP:	if (FIXP_VALUE(arg1) == FIXP_VALUE(arg2))			  {return(ATOM_T);}E 17			return(NIL);	case TYPE_FLOATP: if(FLOATP_VALUE(arg1) == FLOATP_VALUE(arg2))D 17				{return(ATOM_T);}E 17I 17			    {return(ATOM_T);}E 17			  return(NIL);D 9	default: ERROR_EXIT(error_addr);E 9I 9	default: ERROR_EXIT(arg2);E 9D 17	}E 17I 17      }E 17I 17  }/* end N_OP_clequal */E 17D 17}/* end N_OP_clequal */E 17D 17/************************************************************Common Lisp EQL.  Either EQ, but will compare FIXPs and FLOATPs too***********************************************************/E 17I 17/************************************************************************//*									*//*			N _ O P _ e q l o p				*//*									*//*	Common Lisp EQL.						*//*									*//************************************************************************/E 17D 9int N_OP_eqlop(arg1, arg2, error_addr)E 9I 9int N_OP_eqlop(arg1, arg2)E 9D 17register int arg1, arg2;D 9int error_addr;E 9{register int type;E 17I 17  register int arg1, arg2;  {    register int type;E 17E 6D 3  if (arg2 == arg1) goto retT;E 3I 3D 17  if (arg2 == arg1) return(ATOM_T);E 3D 6  switch (0xFFFF0000 & arg1) {D 3    case S_CHARACTER:  goto retNIL;    case ATOMS_OFFSET: goto retNIL;E 3I 3    case S_CHARACTER:  return(NIL);    case ATOMS_OFFSET: return(NIL);E 3  }  if (!IsNumber(arg1)) ERROR_EXIT(error_addr);D 3  if (!IsNumber(arg2)) goto retNIL;  if ((type = GetTypeNumber(arg1)) != (GetTypeNumber(arg2))) goto retNIL;E 3I 3  if (!IsNumber(arg2)) return(NIL);E 6I 6  IF_IMMEDIATE(arg1, return(NIL), return(NIL));  IF_IMMEDIATE(arg2, return(NIL), return(NIL));E 17I 17    if (arg2 == arg1) return(ATOM_T);    IF_IMMEDIATE(arg1, return(NIL), return(NIL));    IF_IMMEDIATE(arg2, return(NIL), return(NIL));E 17D 17/* EQL is true if EQ or both are numbers, the same type, and EQUAL */E 17I 17    /* EQL is true if EQ or both are numbers, the same type, and EQUAL */E 17D 17/* can return NIL if one is a number and the other isn't */E 17I 17    /* can return NIL if one is a number and the other isn't */E 17E 6D 17  if ((type = GetTypeNumber(arg1)) != (GetTypeNumber(arg2))) return(NIL);E 17I 17    if ((type = GetTypeNumber(arg1)) != (GetTypeNumber(arg2))) return(NIL);E 17E 3D 6  if (type == TYPE_SMALLP) ERROR_EXIT(error_addr);  if ((type != TYPE_FIXP) && (type != TYPE_FLOATP)) ERROR_EXIT(error_addr);D 2  if ((*(int *)arg1) == (*(int *)arg2)) goto retT;E 2I 2D 3  if ((*(int *)Addr68k_from_LADDR(arg1)) == (*(int *)Addr68k_from_LADDR(arg2))) goto retT;E 3I 3  if ((*(int *)Addr68k_from_LADDR(arg1)) == (*(int *)Addr68k_from_LADDR(arg2))) return(ATOM_T);E 6E 3E 2D 6  retNIL: return(NIL);E 6I 6D 17/* now we know both are the same type. Shouldn't see any SMALLPs */E 17I 17    /* now we know both are the same type. Shouldn't see any SMALLPs */E 17E 6D 6  retT:  return(ATOM_T);E 6I 6D 17  switch (type) {	case TYPE_FIXP:	if (FIXP_VALUE(arg1) == FIXP_VALUE(arg2)) {return(ATOM_T);}E 17I 17    switch (type)      {	case TYPE_FIXP:	if (FIXP_VALUE(arg1) == FIXP_VALUE(arg2))			  {return(ATOM_T);}E 17			return(NIL);E 6I 6	case TYPE_FLOATP: if(FLOATP_VALUE(arg1) == FLOATP_VALUE(arg2))D 17				{return(ATOM_T);}E 17I 17			    {return(ATOM_T);}E 17			  return(NIL);D 9	default: if(IsNumber(arg1)) {ERROR_EXIT(error_addr); }E 9I 9	default: if(IsNumber(arg1)) {ERROR_EXIT(arg2); }E 9		 else return(NIL);D 17	}E 17I 17      }E 17I 17  }  /* end N_OP_eqlop */E 17E 6D 17}/* end N_OP_clequal */E 17D 9N_OP_equal(arg1, arg2, error_addr) /* IL:EQUAL    opcode 0364 */E 9I 9D 17N_OP_equal(arg1, arg2) /* IL:EQUAL    opcode 0364 */E 9register int arg1, arg2;D 9int error_addr;E 9{register int type, type2;E 17D 6#ifdef	TRACE	printPC();	printf("TRACE: N_OP_equal()\n");#endifE 6D 3  if (arg2 == arg1) goto retT;E 3I 3D 17  if (arg2 == arg1) return(ATOM_T);E 3D 6  switch (0xFFFF0000 & arg1) {D 3    case S_POSITIVE:   goto retNIL;    case S_NEGATIVE:   goto retNIL;    case S_CHARACTER:  goto retNIL;    case ATOMS_OFFSET: goto retNIL;E 3I 3    case S_POSITIVE:   return(NIL);    case S_NEGATIVE:   return(NIL);    case S_CHARACTER:  return(NIL);    case ATOMS_OFFSET: return(NIL);E 3  }  if (!IsNumber(arg1)) ERROR_EXIT(error_addr);D 3  if (!IsNumber(arg2)) goto retNIL;E 3I 3  if (!IsNumber(arg2)) return(NIL);E 6I 6  IF_IMMEDIATE(arg1, return(NIL), goto arg1_small);  IF_IMMEDIATE(arg2, return(NIL), goto arg2_small);  goto arg2_small;E 17I 17/************************************************************************//*									*//*			N _ O P _ e q u a l				*//*									*//*	IL:EQUAL, opcode 0364.						*//*									*//************************************************************************/N_OP_equal(arg1, arg2)  register int arg1, arg2;   {    register int type, type2;    if (arg2 == arg1) return(ATOM_T);    IF_IMMEDIATE(arg1, return(NIL), goto arg1_small);    IF_IMMEDIATE(arg2, return(NIL), goto arg2_small);    goto arg2_small;E 17arg1_small:D 17  IF_IMMEDIATE(arg2, return(NIL), return(NIL));	/* arg2 atom or both small */E 17I 17    IF_IMMEDIATE(arg2, return(NIL), return(NIL)); /* arg2 atom or both small */E 17arg2_small:D 17  if (IsNumber(arg1)) { if(!IsNumber(arg2)) return(NIL) ;}  else {if (IsNumber(arg2)) {return(NIL);}D 9	else ERROR_EXIT(error_addr)}E 9I 9	else ERROR_EXIT(arg2)}E 17I 17    if (IsNumber(arg1)) { if(!IsNumber(arg2)) return(NIL) ;}    else {if (IsNumber(arg2)) {return(NIL);}    else ERROR_EXIT(arg2)}E 17E 9D 17/* now we know both are numbers */E 17I 17    /* now we know both are numbers */E 17E 6E 3D 17  type = GetTypeNumber(arg1);  type2 = GetTypeNumber(arg2);E 17I 17    type = GetTypeNumber(arg1);    type2 = GetTypeNumber(arg2);E 17D 6  if (type == type2)    if (type == TYPE_FIXP) {D 2      if ((*(int *)arg1) == (*(int *)arg2)) goto retT;E 2I 2D 3      if ((*(int *)Addr68k_from_LADDR(arg1)) == (*(int *)Addr68k_from_LADDR(arg2))) goto retT;E 2      else goto retNIL;E 3I 3      if ((*(int *)Addr68k_from_LADDR(arg1)) == (*(int *)Addr68k_from_LADDR(arg2))) return(ATOM_T);      else return(NIL);E 3  }E 6I 6D 17  if (type == type2) {	switch (GetTypeNumber(arg1)) {	  case TYPE_SMALLP:	return(NIL);	  case TYPE_FIXP:	if(FIXP_VALUE(arg1)==FIXP_VALUE(arg2))E 17I 17    if (type == type2)      {	switch (GetTypeNumber(arg1))	  {	    case TYPE_SMALLP:	return(NIL);	    case TYPE_FIXP:	if(FIXP_VALUE(arg1)==FIXP_VALUE(arg2))E 17					{return(ATOM_T);}				return(NIL);D 17	  case TYPE_FLOATP:	if(FLOATP_VALUE(arg1)==FLOATP_VALUE(arg2))E 17I 17	    case TYPE_FLOATP:	if(FLOATP_VALUE(arg1)==FLOATP_VALUE(arg2))E 17					{return(ATOM_T);}				return(NIL);D 9	  default:		ERROR_EXIT(error_addr);E 9I 9D 17	  default:		ERROR_EXIT(arg2);E 17I 17	    default:		ERROR_EXIT(arg2);E 17E 9D 10  	}}E 10I 10D 17	}}E 17I 17	  }      }E 17E 10E 6D 17  if ((type == TYPE_FLOATP) || (type2 == TYPE_FLOATP)) {    register float f1, f2;D 9    N_MakeFloat(arg1, f1, error_addr);    N_MakeFloat(arg2, f2, error_addr);E 9I 9    N_MakeFloat(arg1, f1, arg2);    N_MakeFloat(arg2, f2, arg2);E 9D 3    if ((f1 + 0.0) == (f2 + 0.0)) goto retT;    else goto retNIL;E 3I 3    if ((f1 + 0.0) == (f2 + 0.0)) return(ATOM_T);    else return(NIL);E 3  }D 6  else ERROR_EXIT(error_addr);E 6I 6  else return(NIL); /* neither is float, types are different */E 17I 17    if ((type == TYPE_FLOATP) || (type2 == TYPE_FLOATP))      {	register float f1, f2;	N_MakeFloat(arg1, f1, arg2);	N_MakeFloat(arg2, f2, arg2);	if ((f1 + 0.0) == (f2 + 0.0)) return(ATOM_T);	else return(NIL);      }    else return(NIL); /* neither is float, types are different */E 17E 6D 6  retNIL: return(NIL);  retT:  return(ATOM_T);E 6D 17}/* end N_OP_equal */E 17I 17  } /* end N_OP_equal */E 17I 6D 17/************************************************************Common Lisp =.  Numeric comparison, will convert representations***********************************************************/E 17I 17/************************************************************************//*									*//*			N _ O P _ e q q					*//*									*//*	Common Lisp =, opcode 0377.  Numeric compare, will convert	*//*				     among representations as needed.	*//*									*//************************************************************************/E 17E 6D 9N_OP_eqq(arg1, arg2, error_addr) /* CL:=    opcode 0377 */E 9I 9N_OP_eqq(arg1, arg2) /* CL:=    opcode 0377 */E 9D 17register int arg1, arg2;D 9int error_addr;E 9{D 3register int type;E 3I 3register int type1, type2;register float f1, f2;E 17I 17  register int arg1, arg2;  {    register int type1, type2;    register float f1, f2;E 17E 3D 8#ifdef	TRACE	printPC();	printf("TRACE: N_OP_eqq()\n");#endifE 8D 7  if (!IsNumber(arg1)) ERROR_EXIT(error_addr);  if (!IsNumber(arg2)) ERROR_EXIT(error_addr);E 7I 7D 9  if (!((type1 = GetTypeWord(arg1)) & 0x1000)) ERROR_EXIT(error_addr);E 9I 9D 11  if (!((type1 = GetTypeWord(arg1)) & 0x1000)) ERROR_EXIT(arg2);E 11I 11D 12  if (!((type1 = GetTypeWord(arg1)) & TT_NUMBERP)) ERROR_EXIT(arg2);E 12I 12D 14  if (!((type1 = GetTypeWord(arg1)) & 0x1000)) ERROR_EXIT(arg2);E 14I 14D 17  if (!((type1 = GetTypeEntry(arg1)) & 0x1000)) ERROR_EXIT(arg2);E 14E 12E 11E 9E 7D 3  if (arg2 == arg1) goto retT;  type = GetTypeNumber(arg1);  if (type == TYPE_SMALLP) goto retNIL;  if ((type) == (GetTypeNumber(arg2)))    if (type == TYPE_FIXP) {D 2      if ((*(int *)arg1) == (*(int *)arg2)) goto retT;      else goto retNIL;E 2I 2      if ((*(int *)Addr68k_from_LADDR(arg1)) == (*(int *)Addr68k_from_LADDR(arg2))) return(ATOM_T);      else return(NIL);E 2  }  if ((type == TYPE_FLOATP) || ((GetTypeNumber(arg2)) == TYPE_FLOATP)) {    register float f1, f2;E 3I 3  if (arg2 == arg1) return(ATOM_T);D 7  type1 = GetTypeNumber(arg1);  type2 = GetTypeNumber(arg2);E 7I 7D 9  if (!((type2 = GetTypeWord(arg2)) & 0x1000)) ERROR_EXIT(error_addr);E 9I 9D 11  if (!((type2 = GetTypeWord(arg2)) & 0x1000)) ERROR_EXIT(arg2);E 11I 11D 12  if (!((type2 = GetTypeWord(arg2)) & TT_NUMBERP)) ERROR_EXIT(arg2);E 12I 12D 14  if (!((type2 = GetTypeWord(arg2)) & 0x1000)) ERROR_EXIT(arg2);E 14I 14  if (!((type2 = GetTypeEntry(arg2)) & 0x1000)) ERROR_EXIT(arg2);E 14E 12E 11E 9  type1 &= 0x7ff;  type2 &= 0x7ff;E 17I 17    if (!((type1 = GetTypeEntry(arg1)) & TT_NUMBERP)) ERROR_EXIT(arg2);    if (arg2 == arg1) return(ATOM_T);    if (!((type2 = GetTypeEntry(arg2)) & TT_NUMBERP)) ERROR_EXIT(arg2);    type1 &= 0x7ff;    type2 &= 0x7ff;E 17E 7D 17  switch ( type1 ) {      case TYPE_SMALLP : {	 switch ( type2 ) {I 7	    case TYPE_SMALLP : return(NIL);E 7	    case TYPE_FIXP   : return(NIL);	    case TYPE_FLOATP : goto checkfloats;D 9	    default          : ERROR_EXIT(error_addr);E 9I 9	    default          : ERROR_EXIT(arg2);E 17I 17    switch ( type1 )      {	case TYPE_SMALLP :	  switch ( type2 )	    {	      case TYPE_SMALLP : return(NIL);	      case TYPE_FIXP   : return(NIL);	      case TYPE_FLOATP : goto checkfloats;	      default          : ERROR_EXIT(arg2);E 17E 9D 10 	    }  	 } E 10I 10	    }D 17	 }E 10      case TYPE_FIXP : {	 switch ( type2 ) {	    case TYPE_SMALLP : return(NIL);	    case TYPE_FIXP   : {E 17I 17	case TYPE_FIXP : 	  switch ( type2 )	    {	      case TYPE_SMALLP : return(NIL);	      case TYPE_FIXP   :E 17D 6		 if ((*(int *)Addr68k_from_LADDR(arg1)) ==		     (*(int *)Addr68k_from_LADDR(arg2))    )E 6I 6		 if (FIXP_VALUE(arg1) == FIXP_VALUE(arg2))E 6			 return(ATOM_T);		    else return(NIL);D 17		 }	    case TYPE_FLOATP : goto checkfloats;D 9	    default          : ERROR_EXIT(error_addr);E 9I 9	    default          : ERROR_EXIT(arg2);E 17I 17	      case TYPE_FLOATP : goto checkfloats;	      default          : ERROR_EXIT(arg2);E 17E 9D 10 	    }  	 } E 10I 10	    }D 17	 }E 10      case TYPE_FLOATP : {	 switch ( type2 ) {	    case TYPE_SMALLP : goto checkfloats;	    case TYPE_FIXP   : goto checkfloats;	    case TYPE_FLOATP : goto checkfloats;D 9	    default          : ERROR_EXIT(error_addr);E 9I 9	    default          : ERROR_EXIT(arg2);E 17I 17	case TYPE_FLOATP : 	  switch ( type2 )	    {	      case TYPE_SMALLP : goto checkfloats;	      case TYPE_FIXP   : goto checkfloats;	      case TYPE_FLOATP : goto checkfloats;	      default          : ERROR_EXIT(arg2);E 17E 9D 10 	    }  	 } E 10I 10	    }D 17	 }E 10D 9      default : ERROR_EXIT(error_addr);E 9I 9      default : ERROR_EXIT(arg2);E 17I 17        default : ERROR_EXIT(arg2);E 17E 9      }  checkfloats:E 3D 9    N_MakeFloat(arg1, f1, error_addr);    N_MakeFloat(arg2, f2, error_addr);E 9I 9    N_MakeFloat(arg1, f1, arg2);    N_MakeFloat(arg2, f2, arg2);E 9D 2    if ((f1 + 0.0) == (f2 + 0.0)) goto retT;    else goto retNIL;E 2I 2    if (f1 == f2) return(ATOM_T);D 3    if ((f1 == -0.0) && (f2 == 0.0)) return(ATOM_T);    if ((f1 == 0.0) && (f2 == -0.0)) return(ATOM_T);E 3I 3    if ((f1 == -0.0) && (f2 ==  0.0)) return(ATOM_T);    if ((f1 ==  0.0) && (f2 == -0.0)) return(ATOM_T);E 3    return(NIL);E 2D 3  }  else ERROR_EXIT(error_addr);  retNIL: return(NIL);  retT:  return(ATOM_T);E 3D 17}/* end N_OP_eqq() */E 17I 17  }  /* end N_OP_eqq() */E 17D 6	/*  end module  */E 6I 6E 6E 1