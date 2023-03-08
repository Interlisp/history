/* This is G-file %Z% %M% Version %I% (%G%). copyright Xerox & Fuji Xerox  */




/************************************************************************/
/*									*/
/*	Copyright 1989, 1990 Venue, Fuji Xerox Co., Ltd, Xerox Corp.	*/
/*									*/
/*	This file is work-product resulting from the Xerox/Venue	*/
/*	Agreement dated 18-August-1989 for support of Medley.		*/
/*									*/
/************************************************************************/
/** made obsolete, reneamed to intcall.c for AIX compatibility **/
#illegal

static char *id = "%Z% %M%	%I% %G%";
#include "lispemul.h"
#include "address.h"
#include "address68k.h"
#include "lisptypes.h"
#include "lispmap.h"
#include "stack.h"
#include "return.h"
#include "emulglobal.h"
#include "lispglobal.h"
#include "initatoms.h"
#include "cell.h"

cause_interruptcall(atom_index)
  register unsigned int atom_index;   /* Atomindex for Function you want to invoke */
{
  register struct definition_cell *defcell68k ;  /* Definition Cell PTR */
  register short pv_num ; /* scratch for pv */
  register struct fnhead *tmp_fn;
  int rest ;  /* use for arignments */

  CURRENTFX->nopush = T;
  CURRENTFX->nextblock=StkOffset_from_68K(CurrentStackPTR)+4; 
  PushCStack ;  /* save TOS */

  /* Setup IVar */
  IVar = Addr68k_from_StkOffset(CURRENTFX->nextblock) ;

  /* Set PC to the Next Instruction and save into pre-FX */
  CURRENTFX->pc = ((unsigned int)PC - (unsigned int)FuncObj) ; 


  /* Get DEFCELL 68k address */
  defcell68k =(struct definition_cell *) GetDEFCELL68k(atom_index) ;

 /* Interrupt FN should be compiled code */
  tmp_fn = (struct fnhead *)Addr68k_from_LADDR( defcell68k->defpointer ) ;

if((unsigned int)(CurrentStackPTR + tmp_fn->stkmin +STK_SAFE) >=  (unsigned int)EndSTKP )
	{

		/*printf("Intrrupt:$$ STKOVER when ");
		print(atom_index);
		printf(" was called  *****\n");*/
		DOSTACKOVERFLOW(0,-1);
	}
  FuncObj = tmp_fn  ; 
 if( FuncObj->na >= 0 )
  {
	/* This Function is Spread Type */
	/* Arguments on Stack Adjustment  */
	rest = 0 - (FuncObj->na) ;
	
	while(rest <0) { 
	  PushStack(NIL_PTR) ;
	  rest++;
	}
	CurrentStackPTR -= (rest<<1) ;
  } /* if end */

 /* Set up BF */
CurrentStackPTR+=2;
 GETWORD(CurrentStackPTR) = BF_MARK ;
 GETWORD(CurrentStackPTR+1) = CURRENTFX->nextblock ;
CurrentStackPTR+=2;

 /* Set up FX */
 GETWORD(CurrentStackPTR) = FX_MARK;

 /* Now SET new FX */
 /* Make it SLOWP */
 ((FX*)CurrentStackPTR)->alink = StkOffset_from_68K(PVar) + 1;
 ((FX*)CurrentStackPTR)->blink = StkOffset_from_68K(DUMMYBF(CurrentStackPTR));
 ((FX*)CurrentStackPTR)->clink = StkOffset_from_68K(PVar) ;
 PVar = (DLword *)CurrentStackPTR + FRAMESIZE;
 ((FX*)CurrentStackPTR)->lofnheader = 
	(defcell68k->defpointer) & 0x0ffff ;
 ((FX*)CurrentStackPTR)->hi2fnheader = 
	((defcell68k->defpointer) & 0x0ff0000) >> 16 ;

 CurrentStackPTR = PVar ;

 /* Set up PVar area */
 pv_num = FuncObj->pv+1 ;
 while(pv_num > 0) {
	*((LispPTR *)CurrentStackPTR) = 0x0ffffffff ;
	CurrentStackPTR += DLWORDSPER_CELL ;
	*((LispPTR *)CurrentStackPTR) = 0x0ffffffff ;
	CurrentStackPTR += DLWORDSPER_CELL ;
	pv_num--;
  }

 /* Set PC points New Function's first OPCODE */
 PC = (ByteCode *)FuncObj + FuncObj->startpc ;
 CURRENTFX->nextblock = StkOffset_from_68K(CurrentStackPTR);
 MAKEFREEBLOCK(CurrentStackPTR , ((int)EndSTKP - (int)CurrentStackPTR) >> 1);
} /* end */
