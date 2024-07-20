/* @(#) tosfuncallmacro.h Version 2.21 (3/22/90). copyright envos & Fuji Xerox  */
#illegal
/*****************************************************************/
/*****************************************************************/
/*    OBSOLETE:  REPLACED BY TOSFUNCALL.H 4/17/90                */
/*****************************************************************/
/*****************************************************************/

/***
	tosfuncallmacro.h
	By Takeshi	3-Dec-87


***/



/****************************************************************/
/******		 CURRENT Stack Overflow checks		 ********/
/****************************************************************/

#define  FN_STACK_CHECK			\
  if ((int)CSTKPTR > (Irq_Stk_Check=(Irq_Stk_End-STK_MIN(LOCFNCELL))))	\
     goto check_interrupt;


/****************************************************************/
/******			 LOCAL MACROS			 ********/
/****************************************************************/



#ifdef NATIVETRAN
#define	FN_CALL_NATIVE_CHECK(fncell, args, extra_code)			\
{									\
  if (fncell->native)							\
	{								\
	 extra_code;							\
	 FuncObj = fncell;						\
	 HARD_PUSH(TOPOFSTACK);						\
	 CALL_NATIVE(fncell, args);					\
	}								\
}

#define	FN_CALL_NATIVE_CHECK2(fncell, args, extra_code)			\
{									\
  if (fncell->native)							\
	{								\
	 extra_code;							\
	 (int) PC = args;						\
	 FuncObj = fncell;						\
	 HARD_PUSH(TOPOFSTACK);						\
	 CALL_NATIVE2(fncell, args);					\
	}								\
}

#define ASM_LABEL_OF_FN_COMMON asm_label_op_fn_common()

#else
#define FN_CALL_NATIVE_CHECK(fncell, args, extra_code)
#define	FN_CALL_NATIVE_CHECK2(fncell, args, extra_code)
#define ASM_LABEL_OF_FN_COMMON
#endif

#define APPLY_POP_PUSH_TEST {						\
	 switch (fn_apply) {						\
		case 0:	break; /* do nothing */				\
		case 1: POP; POP;  break; /* from apply */		\
		case 2: break; /* ufn 0 args */				\
		case 3: PUSH(S_POSITIVE | Get_BYTE_PCMAC1); break;	\
		case 4: PUSH(S_POSITIVE | Get_DLword_PCMAC1); break;	\
		default: error("Storage error: invalid UFN entry");	\
		}							\
	 if (needpush) PUSH(fn_atom_index);				\
	}

#define N_APPLY_POP_PUSH_TEST {						\
	APPLY_POP_PUSH_TEST;						\
	native_closure_env=closure_env;					\
	}

#define N_ENVCALL_POP_TEST {						\
	CSTKPTR -=2;							\
	native_closure_env=closure_env;					\
	}



/****************************************************************/
/******			 OPAPPLY			 ********/
/****************************************************************/

#define OPAPPLY	{							\
  if ( GET_TOS_1_HI  == SPOS_HI ) {					\
	fn_num_args = GET_TOS_1_LO;					\
	fn_opcode_size = 1;						\
	fn_apply = 1;							\
	fn_atom_index = TOPOFSTACK;					\
	if ( (0xffff0000 & TOPOFSTACK) == 0)				\
	     {	fn_defcell = (DefCell *) GetDEFCELL68k(TOPOFSTACK);	\
		goto op_fn_common;					\
	     }								\
	else								\
	if (GetTypeNumber(TOPOFSTACK)==TYPE_COMPILED_CLOSURE)		\
	     {	TopOfStack=TOPOFSTACK;					\
		fn_defcell = (DefCell *) &TopOfStack;			\
		goto op_fn_common;					\
	     }								\
	else {	fn_defcell = (DefCell *) GetDEFCELL68k(NIL_PTR);	\
		goto op_fn_common;					\
	     }								\
	}								\
  goto op_ufn;								\
} /* OPAPPLY */



/****************************************************************/
/******			 OPFN(x)			 ********/
/****************************************************************/

#if (defined(SUN3_OS3_OR_OS4_IL) &&  !(defined(NOASMFNCALL)) )

#ifdef NATIVETRAN

#define OPFN(x, num_args_fn, fn_xna_args, fn_native)			\
{    /* asm inlines for fn call (much care put into keeping optimizer	\
	from moving things around). */					\
	fn_section1();							\
	fn_section2();							\
	num_args_fn();							\
	fn_native_test();						\
	fn_section3();							\
	fn_xna_args();							\
	fn_section4();							\
	fast1_dispatcher();		/* nextop0 don't work here */	\
	fn_native();							\
	fn_section5();							\
			/* asm code jumps here when not ccodep */	\
	{ fn_atom_index = Get_DLword_PCMAC1;				\
	  fn_defcell = (DefCell *) GetDEFCELL68k(fn_atom_index);	\
	  fn_num_args = x;						\
	  fn_opcode_size = 3;						\
	  fn_apply = 0;							\
	  goto op_fn_common;						\
	}								\
}

#define OPFNX								\
{    /* asm inlines for fn call (much care put into keeping optimizer	\
	from moving things around.	*/				\
	fnx_section1();							\
	fn_section2();							\
	fnx_args();							\
	fn_native_test();						\
	fn_section3();							\
	fnx_xna();							\
	fn_section4();							\
	fast1_dispatcher();		/* nextop0 don't work here */	\
	fnx_native();							\
	fn_section5();							\
	fn_atom_index = Get_DLword(PCMAC+2);				\
	fn_defcell = (DefCell *) GetDEFCELL68k(fn_atom_index);		\
	fn_num_args = Get_BYTE_PCMAC1;				\
	fn_opcode_size = 4;						\
	fn_apply = 0;							\
	goto op_fn_common;						\
		/* *** these carefully arranged to satisfy optimizer */ \
label1:	fast1_dispatcher();						\
label2:	to_native_label();						\
									\
}
#else

#define OPFN(x, num_args_fn, fn_xna_args, fn_native)			\
{    /* asm inlines for fn call (much care put into keeping optimizer	\
	from moving things around). */					\
	fn_section1();							\
	fn_section2();							\
	num_args_fn();							\
	fn_section3();							\
	fn_xna_args();							\
	fn_section4();							\
	fast1_dispatcher();		/* nextop0 don't work here */	\
	fn_section5();							\
			/* asm code jumps here when not ccodep */	\
	{ fn_atom_index = Get_DLword_PCMAC1;				\
	  fn_defcell = (DefCell *) GetDEFCELL68k(fn_atom_index);	\
	  fn_num_args = x;						\
	  fn_opcode_size = 3;						\
	  fn_apply = 0;							\
	  goto op_fn_common;						\
	}								\
}

#define OPFNX								\
{    /* asm inlines for fn call (much care put into keeping optimizer	\
	from moving things around.	*/				\
	fnx_section1();							\
	fn_section2();							\
	fnx_args();							\
	fn_section3();							\
	fnx_xna();							\
	fn_section4();							\
	fast1_dispatcher();		/* nextop0 don't work here */	\
	fn_section5();							\
	fn_atom_index = Get_DLword(PCMAC+2);				\
	fn_defcell = (DefCell *) GetDEFCELL68k(fn_atom_index);		\
	fn_num_args = Get_BYTE_PCMAC1;				\
	fn_opcode_size = 4;						\
	fn_apply = 0;							\
	goto op_fn_common;						\
		/* *** these carefully arranged to satisfy optimizer */ \
label1:	fast1_dispatcher();						\
									\
}

#endif

#else


#define OPFN(x, num_args_fn, fn_xna_args, fn_native)			\
{	 /* x is a number of the arguments on stack */			\
  register struct fnhead *LOCFNCELL;					\
  register int defcell_word;						\
  register int NEXTBLOCK;						\
  if((defcell_word = *((int *) GetDEFCELL68k(Get_DLword(PCMAC+1)))) >= 0)\
	{ /* it's not a CCODEP (what a test^!! */			\
	  fn_defcell = (DefCell *) GetDEFCELL68k(Get_DLword(PCMAC+1));	\
	  fn_num_args = x;						\
	  fn_opcode_size = 3;						\
	  fn_atom_index = Get_DLword(PCMAC+1);				\
	  fn_apply = 0;							\
	  goto op_fn_common;						\
	}								\
  LOCFNCELL = (struct fnhead *)Addr68k_from_LADDR((defcell_word &= 0xffffff));\
  BCE_CURRENTFX->pc = ((unsigned int)PCMAC - (unsigned int)FuncObj) + 3;\
  FN_CALL_NATIVE_CHECK(LOCFNCELL,-x,{});				\
  FN_STACK_CHECK;							\
  {register int newivar;						\
	(LispPTR *) newivar = IVAR = CSTKPTR-x+1;			\
	BCE_CURRENTFX->nextblock =					\
	NEXTBLOCK =							\
		StkOffset_from_68K(newivar);				\
  }									\
  HARD_PUSH(TOPOFSTACK);  /* save TOS */				\
  if( LOCFNCELL->na >= 0 )						\
  {register int RESTARGS;						\
	RESTARGS = x - LOCFNCELL->na;					\
	while(RESTARGS <0) {						\
	  HARD_PUSH(NIL_PTR);						\
	  RESTARGS++;							\
	}								\
	CSTKPTR -= (RESTARGS);						\
  } /* if end */							\
 /* Set up BF */							\
 HARD_PUSH(BF_MARK32 | NEXTBLOCK);					\
 *((LispPTR *)CSTKPTR) = (FX_MARK << 16) | (StkOffset_from_68K(PVAR));	\
 ((struct frameex2 *)CSTKPTR)->fnheader = SWAP_WORDS(defcell_word);\
  ((DLword *) CSTKPTR) += FRAMESIZE;					\
  PVAR = (LispPTR *) CSTKPTR;						\
  {register int result;							\
	result = LOCFNCELL->pv;						\
	if (result >= 0)						\
	  {register LispPTR unboundval;					\
	   unboundval = (LispPTR) 0xffffffff;				\
	   HARD_PUSH(unboundval);					\
	   HARD_PUSH(unboundval);					\
	   if (result > 0)						\
	    {HARD_PUSH(unboundval);					\
	     HARD_PUSH(unboundval);					\
	     result-=1;							\
	     for (; --result >= 0;) {					\
	       HARD_PUSH(unboundval);					\
	       HARD_PUSH(unboundval);					\
	     }								\
	   }								\
	 }								\
 }									\
 CSTKPTR += 1;								\
 PCMACL = (ByteCode *)LOCFNCELL + LOCFNCELL->startpc + 1;		\
 FuncObj = LOCFNCELL;							\
 nextop0;								\
} /* end OPFN */


/*************** OPFNX *************/
#define OPFNX	{							\
  register struct fnhead *LOCFNCELL;					\
  register DefCell *defcell;	/* this reg is not allocated */		\
  register int NEXTBLOCK;						\
  int num_args = Get_BYTE_PCMAC1;					\
  defcell = (DefCell *) GetDEFCELL68k(Get_DLword(PCMAC+2));		\
  if( defcell->ccodep == 0 )						\
	{ fn_defcell = defcell;						\
	  fn_num_args = num_args;					\
	  fn_opcode_size = 4;						\
	  fn_atom_index = Get_DLword(PCMAC+2);				\
	  fn_apply = 0;							\
	  goto op_fn_common;						\
	}								\
  LOCFNCELL = (struct fnhead *)Addr68k_from_LADDR(defcell->defpointer);	\
  BCE_CURRENTFX->pc = ((unsigned int)PCMAC - (unsigned int)FuncObj) + 4;\
  FN_CALL_NATIVE_CHECK2(LOCFNCELL, - num_args, {});			\
  FN_STACK_CHECK;							\
  {register int newivar;						\
	(LispPTR *) newivar = IVAR = CSTKPTR-num_args+1;		\
	BCE_CURRENTFX->nextblock =					\
	NEXTBLOCK =							\
		StkOffset_from_68K(newivar);				\
  }									\
  HARD_PUSH(TOPOFSTACK);  /* save TOS */				\
  if( LOCFNCELL->na >= 0 )						\
  {register int RESTARGS;						\
	RESTARGS = num_args - LOCFNCELL->na;				\
	while(RESTARGS <0) {						\
	  HARD_PUSH(NIL_PTR);						\
	  RESTARGS++;							\
	}								\
	CSTKPTR -= (RESTARGS);						\
  } /* if end */							\
 /* Set up BF */							\
 HARD_PUSH(BF_MARK32 | NEXTBLOCK);					\
 *((LispPTR *)CSTKPTR) = (FX_MARK << 16) | (StkOffset_from_68K(PVAR));	\
 ((struct frameex2 *)CSTKPTR)->fnheader = SWAP_WORDS(defcell->defpointer);\
  ((DLword *) CSTKPTR) += FRAMESIZE;					\
  PVAR = (LispPTR *) CSTKPTR;						\
  {register int result;							\
	result = LOCFNCELL->pv;						\
	if (result >= 0)						\
	  {register LispPTR unboundval;					\
	   unboundval = (LispPTR) 0xffffffff;				\
	   HARD_PUSH(unboundval);					\
	   HARD_PUSH(unboundval);					\
	   if (result > 0)						\
	    {HARD_PUSH(unboundval);					\
	     HARD_PUSH(unboundval);					\
	     result-=1;							\
	     for (; --result >= 0;) {					\
	       HARD_PUSH(unboundval);					\
	       HARD_PUSH(unboundval);					\
	     }								\
	   }								\
	 }								\
 }									\
 CSTKPTR += 1;								\
 PCMACL = (ByteCode *)LOCFNCELL + LOCFNCELL->startpc + 1;		\
 FuncObj = LOCFNCELL;							\
} /* end OPFN */


#endif


/****************************************************************/
/******			 OPCHECKAPPLY			 ********/
/****************************************************************/

#define OPCHECKAPPLY {							\
  register DefCell *defcell;						\
  defcell = (DefCell *) GetDEFCELL68k(TOPOFSTACK & 0xffff);		\
  if  (!(  defcell->ccodep  && ((TOPOFSTACK & 0xffff0000) == 0)	&&	\
	( ( defcell->argtype == 0 ) || ( defcell->argtype == 2 ) ) ) )	\
	goto op_ufn;							\
}

/****************************************************************/
/*		UFN_COMMON at op_ufn				 /
/****************************************************************/
#define GetUFNEntry(num)	(((UFN *)UFNTable) + (num))

#define	UFN_COMMON							\
op_ufn:		 use code in XC.c					\
{ register UFN *entry68k;						\
   entry68k = (UFN *)GetUFNEntry(Get_BYTE_PCMAC0);			\
   fn_num_args = entry68k->arg_num;					\
   fn_opcode_size = entry68k->byte_num+1;				\
   fn_atom_index = entry68k->atom_name;					\
   fn_defcell = (DefCell *) GetDEFCELL68k(fn_atom_index);		\
   fn_apply = 0;							\
   goto op_fn_common;							\
  };



/****************************************************************/
/******			 OP_FN_COMMON			 ********/
/* vars:							*/
/*	fn_atom_index						*/
/*	fn_num_args						*/
/*	fn_opcode_size						*/
/*	fn_defcell						*/
/*	fn_apply						*/
/*								*/
/* All Closure Calls go through here				*/
/****************************************************************/
#define needpush NEXTBLOCK
#define OP_FN_COMMON							\
op_fn_common:								\
	ASM_LABEL_OF_FN_COMMON;						\
{ register struct fnhead *LOCFNCELL;					\
  register DefCell *defcell;	/* this reg is not allocated */		\
  CClosure *closure;							\
  LispPTR closure_env = (LispPTR) 0xffffffff;				\
 {register int NEXTBLOCK = NIL;						\
  defcell = fn_defcell;							\
  if( (defcell->ccodep == 0)  )						\
    if(GetTypeNumber(defcell->defpointer)==TYPE_COMPILED_CLOSURE)	\
	 { /* setup closure */						\
		closure=(CClosure *)Addr68k_from_LADDR(defcell->defpointer);\
		defcell=(DefCell *)closure;				\
		/* not  a closure if closure's env is NIL */		\
		if(closure->env_ptr )					\
			{closure_env =  (LispPTR) (closure->env_ptr);	\
			}						\
	 } /* if end */							\
	else {								\
	/* NOT compiled object . We must use Interpreter*/		\
	defcell = (DefCell *)GetDEFCELL68k(ATOM_INTERPRETER);		\
	needpush = 1;							\
	 } /*else end */						\
  LOCFNCELL = (struct fnhead *)Addr68k_from_LADDR(defcell->defpointer);	\
  BCE_CURRENTFX->pc = ((unsigned int)PCMAC - (unsigned int)FuncObj) + fn_opcode_size;\
  FN_CALL_NATIVE_CHECK2(LOCFNCELL, -fn_num_args, N_APPLY_POP_PUSH_TEST)	\
  FN_STACK_CHECK;							\
  APPLY_POP_PUSH_TEST;							\
 {register int newivar;							\
	(LispPTR *) newivar = IVAR = CSTKPTR+(1-fn_num_args-needpush);	\
	BCE_CURRENTFX->nextblock =					\
	NEXTBLOCK =							\
		StkOffset_from_68K(newivar);				\
  }									\
  HARD_PUSH(TOPOFSTACK);  /* save TOS */				\
  if( LOCFNCELL->na >= 0 )						\
  {register int RESTARGS;						\
	RESTARGS = fn_num_args - LOCFNCELL->na;				\
	while(RESTARGS <0) {						\
	  HARD_PUSH(NIL_PTR);						\
	  RESTARGS++;							\
	}								\
	CSTKPTR -= (RESTARGS);						\
  } /* if end */							\
 /* Set up BF */							\
 HARD_PUSH(BF_MARK32 | NEXTBLOCK);					\
 } /* NEXTBLOCK BLOCK */						\
 *((LispPTR *)CSTKPTR) = (FX_MARK << 16) | (StkOffset_from_68K(PVAR));	\
 ((struct frameex2 *)CSTKPTR)->fnheader = SWAP_WORDS(defcell->defpointer);\
  ((DLword *) CSTKPTR) += FRAMESIZE;					\
  PVAR = (LispPTR *) CSTKPTR;						\
  {register int result;							\
   register LispPTR unboundval;						\
   unboundval = (LispPTR) 0xffffffff;					\
   result = LOCFNCELL->pv;						\
   HARD_PUSH(closure_env);						\
   HARD_PUSH(unboundval);						\
   for (; --result >= 0;) {						\
       HARD_PUSH(unboundval);						\
       HARD_PUSH(unboundval);						\
       }								\
 }	/* result, unboundval block */					\
 CSTKPTR += 1;								\
 PCMACL = (ByteCode *)LOCFNCELL + LOCFNCELL->startpc + 1;		\
 FuncObj = LOCFNCELL;							\
 CHECK_INTERRUPT;							\
 nextop0;								\
} /* end OP_FN_COMMON */


/************************************************************************/
/*									*/
/*			O P _ E N V C A L L				*/
/*									*/
/*	Environment call on a code object.  Takes an arg count on	*/
/*	the stack, along with a pointer to an environment.  If non-	*/
/*	NIL, the environment is stuffed into the PVAR0 slot of the	*/
/*	frame. [This NIL check is in the UFN, and seems to be meant	*/
/*	to allow closures to be called without an environment, without	*/
/*	the compiler having to emit special code.]			*/
/*									*/
/************************************************************************/

#define OP_ENVCALL	{						\
  register struct fnhead *LOCFNCELL;					\
  register int NEXTBLOCK;						\
  register LispPTR closure_env = TOPOFSTACK;				\
  register int num_args;						\
  register LispPTR Fn_DefCell=  GET_TOS_1;				\
  LOCFNCELL = (struct fnhead *)Addr68k_from_LADDR(Fn_DefCell);		\
  N_GETNUMBER(GET_TOS_2, num_args, op_ufn);				\
  BCE_CURRENTFX->pc = ((unsigned int)PCMAC - (unsigned int)FuncObj) + 1;\
  FN_CALL_NATIVE_CHECK2(LOCFNCELL, -num_args, N_ENVCALL_POP_TEST);	\
  FN_STACK_CHECK;							\
  CSTKPTR -= 2;								\
  {register int newivar;						\
	(LispPTR *) newivar = IVAR = CSTKPTR-num_args;			\
	BCE_CURRENTFX->nextblock =					\
	NEXTBLOCK =							\
		StkOffset_from_68K(newivar);				\
  }									\
  if( LOCFNCELL->na >= 0 )						\
  {register int RESTARGS;						\
	RESTARGS = num_args - LOCFNCELL->na;				\
	while(RESTARGS <0) {						\
	  HARD_PUSH(NIL_PTR);						\
	  RESTARGS++;							\
	}								\
	CSTKPTR -= (RESTARGS);						\
  } /* if end */							\
 /* Set up BF */							\
 HARD_PUSH(BF_MARK32 | NEXTBLOCK);					\
 *((LispPTR *)CSTKPTR) = (FX_MARK << 16) | (StkOffset_from_68K(PVAR));	\
 ((struct frameex2 *)CSTKPTR)->fnheader = SWAP_WORDS(Fn_DefCell);	\
  ((DLword *) CSTKPTR) += FRAMESIZE;					\
  PVAR = (LispPTR *) CSTKPTR;						\
  {register int result;							\
	result = LOCFNCELL->pv;						\
	if (result >= 0)						\
	  {register LispPTR unboundval;					\
	   unboundval = (LispPTR) 0xffffffff;				\
	   if (closure_env == NIL_PTR) HARD_PUSH(unboundval);		\
	     else HARD_PUSH(closure_env);				\
	   HARD_PUSH(unboundval);					\
	   if (result > 0)						\
	    {HARD_PUSH(unboundval);					\
	     HARD_PUSH(unboundval);					\
	     result-=1;							\
	     for (; --result >= 0;) {					\
	       HARD_PUSH(unboundval);					\
	       HARD_PUSH(unboundval);					\
	     }								\
	   }								\
	 }								\
 }									\
 CSTKPTR += 1;								\
 PCMACL = (ByteCode *)LOCFNCELL + LOCFNCELL->startpc + 1;		\
 FuncObj = LOCFNCELL;							\
} /* end OP_ENVCALL */


/****************************************************************/
/******			 EVAL				 ********/
/****************************************************************/

#define EVAL								\
{									\
 LispPTR scratch;							\
 register LispPTR work;							\
 register LispPTR lookuped; /* keep looked up value */			\
									\
  switch(TOPOFSTACK & 0x0ff0000) {					\
   case S_POSITIVE :							\
   case S_NEGATIVE :	nextop1;					\
									\
   case ATOMS_OFFSET : if((TOPOFSTACK==NIL_PTR)||(TOPOFSTACK==ATOM_T))	\
			goto Hack_Label;				\
			nnewframe(CURRENTFX,&scratch,TOPOFSTACK & 0xffff);\
			work =	((scratch & 0xffff0000)>> 16) |		\
				((scratch & 0x00ff) <<16);		\
			lookuped =					\
			  *((LispPTR *)(Addr68k_from_LADDR(work)));	\
			if(lookuped==NOBIND_PTR) goto op_ufn;		\
			TOPOFSTACK = lookuped;				\
Hack_Label:		nextop1;					\
									\
   default :		switch(GetTypeNumber(TOPOFSTACK)){		\
			  case TYPE_FIXP :				\
			  case TYPE_FLOATP :				\
			  case TYPE_STRINGP :				\
			  case TYPE_ONED_ARRAY :			\
			  case TYPE_GENERAL_ARRAY :	nextop1;	\
									\
			  case TYPE_LISTP :				\
				fn_atom_index = ATOM_EVALFORM;		\
				fn_num_args = 1;			\
				fn_opcode_size = 1;			\
				fn_defcell = (DefCell *)		\
					GetDEFCELL68k(ATOM_EVALFORM);	\
				fn_apply = 0;				\
				goto op_fn_common;			\
									\
			  default :	 goto op_ufn;			\
				}					\
									\
  } /* end switch */							\
									\
}/* EVAL end */
