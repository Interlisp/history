/* @(#) car-cdr.h Version 1.4 (4/21/92). copyright venue & Fuji Xerox  */
/*
 *	Copyright (C) 1987 by Fuji Xerox Co., Ltd. All rights reserved.
 *
 *	Author :  Takeshi Shimizu, Naoyuki Mitani
 *
 */



/************************************************************************/
/*									*/
/*	Copyright 1989, 1990 Venue, Fuji Xerox Co., Ltd, Xerox Corp.	*/
/*									*/
/*	This file is work-product resulting from the Xerox/Venue	*/
/*	Agreement dated 18-August-1989 for support of Medley.		*/
/*									*/
/************************************************************************/



/***********************************************************************/
/*
		File Name :	car-cdrmacro.h

		Desc	:	car-cdr management

				ORIGINAL	Date :		Apr 24, 1987
				Changed : 4 Dec. 87 Takeshi

		Including :
				OPCAR
				OPCDR
				OPRPLACA
				OPRPLACD
*/
/**********************************************************************/
/* #define DATUM68K	((ConsCell *)wordp) */
/* #define TEMP68K		((ConsCell *)cellp) */
#define OPCAR \
 if (Listp(TOPOFSTACK))\
 {\
 register ConsCell *DATUM68K = (ConsCell *)(Addr68k_from_LADDR(TOPOFSTACK));\
	if (DATUM68K->cdr_code == CDR_INDIRECT)\
	{\
		TOPOFSTACK = ((LispPTR)((ConsCell *)Addr68k_from_LADDR(DATUM68K->car_field))->car_field);\
	}\
	else \
	{ \
		TOPOFSTACK = ((LispPTR)DATUM68K->car_field);\
  } \
  nextop1; \
  }\
 else	if (TOPOFSTACK == NIL_PTR)\
		{ nextop1; } \
	else if ( TOPOFSTACK == ATOM_T)\
		{ nextop1; } \
	else \
	  {\
		goto op_ufn; \
	  } /* end of OPCAR */

/**********************************************************************/


#define OPCDR  { \
 if (Listp(TOPOFSTACK))\
 {\
register ConsCell *DATUM68K = (ConsCell *)(Addr68k_from_LADDR(TOPOFSTACK));\
register DLword CDRCODEX = DATUM68K->cdr_code;\
	if (CDRCODEX == CDR_NIL)\
		/* cdr-nil */\
		TOPOFSTACK = (NIL_PTR);\
	else if (CDRCODEX> CDR_ONPAGE)\
		/* cdr-samepage */\
		TOPOFSTACK = (POINTER_PAGEBASE(TOPOFSTACK) + \
		((CDRCODEX & 127) << 1));\
	else if (CDRCODEX == CDR_INDIRECT)	/* CDRCODEX < CDR_ONPAGE */\
		/* cdr-indirect */\
		TOPOFSTACK = (cdr ((LispPTR)(DATUM68K->car_field)));\
	else\
	{\
		/* cdr-differentpage */\
		TOPOFSTACK = (LispPTR)((ConsCell *)(Addr68k_from_LADDR \
		(POINTER_PAGEBASE(TOPOFSTACK) + (CDRCODEX << 1)))\
											->car_field);\
	}\
	nextop1; \
  }\
 else	if (TOPOFSTACK == NIL_PTR)\
		{ nextop1; } \
	else\
	 {\
		goto op_ufn; \
	 }\
} /* end of OPCDR */

/**********************************************************************/

#ifdef NOWAY
#define RPLACA	{ \
register LispPTR DATAX = *((LispPTR *)(CurrentStackPTR));\
 CurrentStackPTR -= 2;\
 if (Listp(DATAX) == NIL)\
 {\
	if (DATAX == NIL_PTR)\
	{\
		if (TOPOFSTACK != NIL_PTR)\
			goto op_ufn; \
			/* error("Attempt to RPLACA NIL"); */ \
	}\
	else\
		goto op_ufn; \
		/* error("ARG not List"); */\
 }\
 else \
 {\
	register ConsCell *X68K = (ConsCell *)Addr68k_from_LADDR(DATAX);\
	GCLOOKUP(car(DATAX), DELREF);	/* set up reference count */\
	GCLOOKUP(TOPOFSTACK, ADDREF);\
	if (X68K->cdr_code == CDR_INDIRECT)\
	{\
		((ConsCell *)Addr68k_from_LADDR((LispPTR)X68K->car_field))\
			->car_field = TOPOFSTACK;\
	}\
	else\
		X68K->car_field = TOPOFSTACK ;\
	TOPOFSTACK = DATAX;\
 }\
 nextop1; \
} /* end of OPRPLACA */

/**********************************************************************/

#define RPLACD  { \
 extern struct conspage *next_conspage();\
 register LispPTR DATAX = *((LispPTR *)(CurrentStackPTR));\
 CurrentStackPTR -= 2;\
 if (Listp(DATAX) == NIL)\
 {\
	if (DATAX == NIL_PTR)\
	{\
		if (TOPOFSTACK != NIL_PTR)\
			goto op_ufn; \
			/* error("Attempt to RPLACD NIL"); */\
		else\
			TOPOFSTACK = NIL_PTR;	\
	}\
	else\
		goto op_ufn; \
		/* error("ARG not List"); */\
 }\
 else \
 {\
	register ConsCell *X68K = (ConsCell *)Addr68k_from_LADDR(DATAX);\
	register CDRCODEX = X68K->cdr_code;\
	register LispPTR RP_PAGE = X68K->car_field;\
	GCLOOKUP(cdr(DATAX), DELREF);	/* set up reference count */\
	GCLOOKUP(TOPOFSTACK, ADDREF);\
	if (CDRCODEX == CDR_INDIRECT)\
	{\
		/* cdr-indirect */\
		register LispPTR CDR_CELL = POINTER_PAGEBASE(RP_PAGE) + \
				(((ConsCell *)Addr68k_from_LADDR(RP_PAGE))->cdr_code << 1);\
		*(LispPTR *)((ConsCell *)Addr68k_from_LADDR(CDR_CELL)) = \
				TOPOFSTACK & 0xffffff;\
			/* CDRCODEX is set to 0 */\
	}\
	else if (CDRCODEX <= CDR_MAXINDIRECT)\
	{\
		/* cdr-differentpage */\
		register LispPTR CDR_CELL = POINTER_PAGEBASE(DATAX) + (CDRCODEX << 1);\
		*(LispPTR *)((ConsCell *)Addr68k_from_LADDR(CDR_CELL)) = \
				TOPOFSTACK & 0xffffff;\
			/* CDRCODEX is set to 0 */\
	}\
	else if (TOPOFSTACK == NIL_PTR)\
		/* cdr-samepage & TOPOFSTACK is nil */\
		X68K->cdr_code = CDR_NIL;\
	else if ((RP_PAGE = POINTER_PAGEBASE(DATAX )) == \
					POINTER_PAGEBASE(TOPOFSTACK))\
		/* cdr-samepage & x and TOPOFSTACK are on same page */\
		X68K->cdr_code = CDR_ONPAGE + ((TOPOFSTACK & 0xff) >> 1);\
	else\
	{\
		/* cdr-samepage & x and TOPOFSTACK are on different page */\
		register struct conspage *cons68k = (struct conspage *)Addr68k_from_LADDR(RP_PAGE);\
		register ConsCell *CDR_CELL68K; \
		if (cons68k->count > 0)\
		{\
			/* at least one free-cell on x's conspage */\
			CDR_CELL68K = GetNewCell_68k(cons68k);\
			cons68k->count--;\
			cons68k->next_cell = CDR_CELL68K->cdr_code;\
			*(LispPTR *)CDR_CELL68K = TOPOFSTACK & 0xffffff;\
				/* cdr_code is set to 0 */\
			X68K->cdr_code = (LADDR_from_68k(CDR_CELL68K) - \
			RP_PAGE) >> 1;\
		}\
		else\
		{\
			/* no more free-cell on x's conspage */\
			register ConsCell *temp68k; \
			cons68k = next_conspage();\
			CDR_CELL68K = GetNewCell_68k(cons68k);\
			cons68k->next_cell = CDR_CELL68K->cdr_code;\
			temp68k = GetNewCell_68k(cons68k);\
			cons68k->next_cell = temp68k->cdr_code ;\
			/* cons68k->next_cell = CDR_CELL68K->cdr_code;*/\
			cons68k->count -= 2;\
			*(LispPTR *)CDR_CELL68K = TOPOFSTACK & 0xffffff;\
				/* cdr_code is set to 0 */\
			temp68k->car_field = X68K->car_field;\
			(LispPTR)X68K->car_field = LADDR_from_68k(temp68k);\
			temp68k->cdr_code = (LADDR_from_68k(CDR_CELL68K) \
			& 0xff) >> 1;\
			X68K->cdr_code = CDR_INDIRECT;\
		}\
	}\
 }\
 TOPOFSTACK = DATAX;\
 nextop1; \
}/* end of OPRPLACD */
#endif
