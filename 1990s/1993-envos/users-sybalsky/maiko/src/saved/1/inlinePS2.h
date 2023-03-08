/* %Z% %M% Version %I% (%G%). copyright Venue  */


/************************************************************************/
/*									*/
/*	(C) Copyright 1991 Venue. All Rights Reserved.			*/
/*	Manufactured in the United States of America.			*/
/*									*/
/*	The contents of this file are proprietary information 		*/
/*	belonging to Venue, and are provided to you under license.	*/
/*	They may not be further distributed or disclosed to third	*/
/*	parties without the specific permission of Venue.		*/
/*									*/
/************************************************************************/

/************************************************************************/
/*									*/
/*			   I N L I N E P S 2 . H			*/
/*									*/
/*	INLINE definitions for 386 machines, compiled with gcc.		*/
/*									*/
/*	This file consists of 3 sections:				*/
/*									*/
/*		inline static functions for use anywhere in Medley	*/
/*		(e.g., the byte-swapping functions)			*/
/*									*/
/*		#defines and static inline functions for the dispatch	*/
/*		loop (e.g., IDIFFERENCE), relying on the register	*/
/*		conventions that hold in that part of the code		*/
/*									*/
/*		#defines and static inline functions for other		*/
/*		specific files (e.g., the arithmetic functions,		*/
/*		free-variable lookup, etc.), relying on the register	*/
/*		conventions in the respective files.			*/
/*									*/
/*									*/
/*									*/
/*									*/
/*									*/
/*									*/
/*									*/
/*									*/
/*									*/
/*									*/
/*		   R E G I S T E R   C O N V E N T I O N S		*/
/*									*/
/*	The following register conventions hold in the dispatch loop,	*/
/*	and are set up by register ... asm("...") decls in xc.c:	*/
/*									*/
/*		esi	pccache	- the current PC			*/
/*		edi	cspcache - the current lisp stack ptr.		*/
/*		ebx	tscache - the top-of-stack item.		*/
/*									*/
/*									*/
/*	Rgister conventions within arithmetic functions in the files	*/
/*	arith2.c - arith4.c, etc.:					*/
/*									*/
/*		esi	first argument to the function			*/
/*		edi	second argument to the function			*/
/*									*/
/************************************************************************/


/************************************************************************/
/*									*/
/*    G E N E R A L - P U R P O S E   I N L I N E   F U N C T I O N S	*/
/*									*/
/*	These functions don't rely on register conventions.		*/
/*									*/
/************************************************************************/


#undef SWAP_WORDS
#define SWAP_WORDS swapx


extern inline const unsigned int swapx (unsigned int word)
 {
    asm("roll	$16,%0" : "=g" (word) : "0" (word));
    return(word);
 }



extern inline const unsigned int word_swap_longword (unsigned int word)
 {
    asm("roll	$16,%0" : "=r" (word) : "0" (word));

    return(word);
  }



extern inline const unsigned short byte_swap_word (unsigned short word)
 {
    asm("rolw	$8,%0" : "=r" (word) : "0" (word));

    return(word);
  }



extern inline const void word_swap_page(unsigned short * page, int count)
  {
   asm volatile("\
	pushl %edi					\n\
	pushl %esi					\n\
	pushl %ecx					\n\
	cld");
    asm volatile("
	movl %0,%%esi	// word pointer.		\n\
	movl %%esi,%%edi				\n\
	movl %1,%%ecx	// count" : : "g" (page), "g" (count));
    asm volatile("
	lodsl						\n\
	rolw	$8,%ax					\n\
	roll	$16,%eax				\n\
	rolw	$8,%ax					\n\
	stosl						\n\
	loop	.-13					\n\
							\n\
	// epilogue.					\n\
	popl %ecx					\n\
	popl %esi					\n\
	popl %edi
	");

  }



/************************************************************************/
/*									*/
/*									*/
/*									*/
/*									*/
/*									*/
/************************************************************************/

	/* undefine these macros so we use the 386i inline code */

#undef Get_BYTE_PCMAC0
#undef Get_BYTE_PCMAC1
#undef Get_BYTE_PCMAC2
#undef Get_BYTE_PCMAC3

#define Get_BYTE_PCMAC0 Get_BYTE_PCMAC0fn(pccache)
#define Get_BYTE_PCMAC1 Get_BYTE_PCMAC1fn(pccache)
#define Get_BYTE_PCMAC2 Get_BYTE_PCMAC2fn(pccache)
#define Get_BYTE_PCMAC3 Get_BYTE_PCMAC3fn(pccache)

extern inline const unsigned int Get_BYTE_PCMAC0fn (pccache)
unsigned int pccache;
 {
    register unsigned int word;
    asm("leal	-1(%1),%0 \n\
	xorl	$3,%0 \n\
	movzbl	(%0),%0 \n\
	" : "=r" (word) : "r" (pccache) );
    return(word);
 }

extern inline const unsigned int Get_BYTE_PCMAC1fn (pccache)
unsigned int pccache;
 {
    register unsigned int word;
    asm("movl	%1,%0 \n\
	xorl	$3,%0 \n\
	movzbl	(%0),%0 \n\
	" : "=r" (word) : "r" (pccache) );
    return(word);
 }

extern inline const unsigned int Get_BYTE_PCMAC2fn (pccache)
unsigned int pccache;
 {
    register unsigned int word;
    asm("leal	1(%1),%0 \n\
	xorl	$3,%0 \n\
	movzbl	(%0),%0 \n\
	" : "=r" (word) : "r" (pccache) );
    return(word);
 }

extern inline const unsigned int Get_BYTE_PCMAC3fn (pccache)
unsigned int pccache;
 {
    register unsigned int word;
    asm("leal	2(%1),%0 \n\
	xorl	$3,%0 \n\
	movzbl	(%0),%0 \n\
	" : "=r" (word) : "r" (pccache) );
    return(word);
 }


#undef Get_DLword_PCMAC0
#undef Get_DLword_PCMAC1
#undef Get_DLword_PCMAC2
#undef Get_DLword_PCMAC3


#define Get_DLword_PCMAC0 Get_DLword_PCMAC0fn(pccache)
#define Get_DLword_PCMAC1 Get_DLword_PCMAC1fn(pccache)
#define Get_DLword_PCMAC2 Get_DLword_PCMAC2fn(pccache)
#define Get_DLword_PCMAC3 Get_DLword_PCMAC3fn(pccache)

extern inline const unsigned int Get_DLword_PCMAC0fn(pccache)
unsigned int pccache;
 {
    register unsigned int word asm("ax");
    asm("movl	%1,%%edx \n\
	xorb	$3,%%dl \n\
	movzbl	(%%edx),%%eax \n\
	leal	-1(%1),%%edx	\n\
	xorb	$3,%%dl	\n\
	movb	(%%edx),%%ah	\n\
	" : "=r" (word) : "r" (pccache) : "dx" );
    return(word);
 }

extern inline const unsigned int Get_DLword_PCMAC1fn(pccache)
unsigned int pccache;
 {
    register unsigned int word asm("ax");
    asm("leal	1(%1),%%edx \n\
	xorb	$3,%%dl \n\
	movzbl	(%%edx),%%eax \n\
	leal	(%1),%%edx	\n\
	xorb	$3,%%dl	\n\
	movb	(%%edx),%%ah	\n\
	" : "=r" (word) : "r" (pccache) : "dx" );
    return(word);
 }


extern inline const unsigned int Get_DLword_PCMAC2fn(pccache)
unsigned int pccache;
 {
    register unsigned int word asm("ax");
    asm("leal	2(%1),%%edx \n\
	xorb	$3,%%dl \n\
	movzbl	(%%edx),%%eax \n\
	leal	1(%1),%%edx	\n\
	xorb	$3,%%dl	\n\
	movb	(%%edx),%%ah	\n\
	" : "=r" (word) : "r" (pccache) : "dx" );
    return(word);
 }

extern inline const unsigned int Get_DLword_PCMAC3fn(pccache)
unsigned int pccache;
 {
    register unsigned int word asm("ax");
    asm("leal	3(%1),%%edx \n\
	xorb	$3,%%dl \n\
	movzbl	(%%edx),%%eax \n\
	leal	2(%1),%%edx	\n\
	xorb	$3,%%dl	\n\
	movb	(%%edx),%%ah	\n\
	" : "=r" (word) : "r" (pccache) : "dx" );
    return(word);
 }


#undef Get_Pointer_PCMAC0
#undef Get_Pointer_PCMAC1
#undef Get_Pointer_PCMAC2

#define Get_Pointer_PCMAC0 Get_Pointer_PCMAC0fn(pccache)
#define Get_Pointer_PCMAC1 Get_Pointer_PCMAC1fn(pccache)
#define Get_Pointer_PCMAC2 Get_Pointer_PCMAC2fn(pccache)


extern inline const unsigned int Get_Pointer_PCMAC0fn(pccache)
unsigned int pccache;
 {
    register unsigned int word asm("ax");
    asm("leal	-1(%1),%%edx	\n\
	xorb	$3,%%dl		\n\
	movzbl	(%%edx),%%eax	\n\
	shll	$16,%%eax	\n\
	leal	1(%1),%%edx	\n\
	xorb	$3,%%dl		\n\
	movb	(%%edx),%%al	\n\
	leal	(%1),%%edx	\n\
	xorb	$3,%%dl		\n\
	movb	(%%edx),%%ah	\n\
	" : "=r" (word) : "r" (pccache) : "dx" );
    return(word);
 }

extern inline const unsigned int Get_Pointer_PCMAC1fn(pccache)
unsigned int pccache;
 {
    register unsigned int word asm("ax");
    asm("leal	(%1),%%edx	\n\
	xorb	$3,%%dl		\n\
	movzbl	(%%edx),%%eax	\n\
	shll	$16,%%eax	\n\
	leal	2(%1),%%edx	\n\
	xorb	$3,%%dl		\n\
	movb	(%%edx),%%al	\n\
	leal	1(%1),%%edx	\n\
	xorb	$3,%%dl		\n\
	movb	(%%edx),%%ah	\n\
	" : "=r" (word) : "r" (pccache) : "dx" );
    return(word);
 }


extern inline const unsigned int Get_Pointer_PCMAC2fn(pccache)
unsigned int pccache;
 {
    register unsigned int word asm("ax");
    asm("leal	1(%1),%%edx	\n\
	xorb	$3,%%dl		\n\
	movzbl	(%%edx),%%eax	\n\
	shll	$16,%%eax	\n\
	leal	3(%1),%%edx	\n\
	xorb	$3,%%dl		\n\
	movb	(%%edx),%%al	\n\
	leal	2(%1),%%edx	\n\
	xorb	$3,%%dl		\n\
	movb	(%%edx),%%ah	\n\
	" : "=r" (word) : "r" (pccache) : "dx" );
    return(word);
 }



#undef DIFFERENCE
#undef IDIFFERENCE

#define DIFFERENCE {						\
	fast_op_difference(POP_TOS_1);				\
	fast1_dispatcher();						\
diff_err:							\
	asm volatile("diff_err:");					\
	asm volatile("addb $7,%bl");					\
	asm volatile("rorl $15,%ebx");					\
	N_OP_POPPED_CALL_2(N_OP_difference, GET_POPPED);	\
	}

extern inline const void fast_op_difference(LispPTR value)
  {
    asm volatile("\
	movl	%0,%%eax	\n\
	roll	$15,%%ebx	\n\
	subb	$7,%%bl	\n\
	jne	diff_err	\n\
	roll	$15,%%eax	\n\
	subb	$7,%%al	\n\
	jne	diff_err	\n\
	subl	%%ebx,%%eax	\n\
	jo	diff_err	\n\
	rorl	$15,%%eax	\n\
	orl	$917504,%%eax	\n\
	movl	%%eax,%%ebx	\
    " :  : "g" (value) : "ax" );

  }

#define IDIFFERENCE {						\
	fast_op_idifference(POP_TOS_1);				\
	fast1_dispatcher();						\
idiff_err:							\
	asm volatile("idiff_err:");				\
	asm volatile("addb $7,%bl");					\
	asm volatile("rorl $15,%ebx");					\
	N_OP_POPPED_CALL_2(N_OP_idifference, GET_POPPED);	\
	}

extern inline const void fast_op_idifference(LispPTR value)
  {
    asm volatile("\
	movl	%0,%%eax	\n\
	roll	$15,%%ebx	\n\
	subb	$7,%%bl	\n\
	jne	idiff_err	\n\
	roll	$15,%%eax	\n\
	subb	$7,%%al	\n\
	jne	idiff_err	\n\
	subl	%%ebx,%%eax	\n\
	jo	idiff_err	\n\
	rorl	$15,%%eax	\n\
	orl	$917504,%%eax	\n\
	movl	%%eax,%%ebx	\n\
    " :  : "g" (value) : "ax" );

  }

#undef IDIFFERENCE_N
#define IDIFFERENCE_N(n) {					\
	fast_op_idifferencen(n);				\
	fast2_dispatcher();						\
idiffn_err:							\
	asm("idiffn_err:");					\
	asm("addw $7,%bx");					\
	asm("rorl $15,%ebx");					\
	N_OP_CALL_1d(N_OP_idifferencen, n);			\
	}

extern inline const void fast_op_idifferencen(LispPTR value)
  {
    asm volatile("\
	movl	%0,%%eax
	roll	$15,%%eax
	roll	$15,%%ebx
	subb	$7,%%bl
	jne	idiffn_err
	subl	%%eax,%%ebx
	jo	idiffn_err
	rorl	$15,%%ebx
	orl	$917504,%%ebx
    " :  : "g" (value) : "ax" );

  }

#undef PLUS2
#undef IPLUS2

#define PLUS2 {							\
	fast_op_plus(POP_TOS_1);				\
	fast1_dispatcher();						\
plus_err:							\
	asm volatile("plus_err:");					\
	asm volatile("addw $7,%bx");					\
	asm volatile("rorl $15,%ebx");					\
	N_OP_POPPED_CALL_2(N_OP_plus2, GET_POPPED);		\
	}
extern inline const void fast_op_plus(LispPTR value)
  {
    asm volatile("\
	movl	%0,%%eax	\n\
	roll	$15,%%ebx	\n\
	subb	$7,%%bl	\n\
	jne	plus_err	\n\
	roll	$15,%%eax	\n\
	subb	$7,%%al	\n\
	jne	plus_err	\n\
	addl	%%ebx,%%eax	\n\
	jo	plus_err	\n\
	rorl	$15,%%eax	\n\
	orl	$917504,%%eax	\n\
	movl	%%eax,%%ebx	\n\
    " :  : "g" (value) : "ax" );

  }


#define IPLUS2 {						\
	fast_op_iplus(POP_TOS_1);				\
	fast1_dispatcher();						\
iplus_err:							\
	asm volatile("iplus_err:");					\
	asm volatile("addw $7,%bx");					\
	asm volatile("rorl $15,%ebx");					\
	N_OP_POPPED_CALL_2(N_OP_iplus2, GET_POPPED);		\
	}
extern inline const void fast_op_iplus(LispPTR value)
  {
    asm volatile("\
	movl	%0,%%eax	\n\
	roll	$15,%%ebx	\n\
	subb	$7,%%bl	\n\
	jne	iplus_err	\n\
	roll	$15,%%eax	\n\
	subb	$7,%%al	\n\
	jne	iplus_err	\n\
	addl	%%ebx,%%eax	\n\
	jo	iplus_err	\n\
	rorl	$15,%%eax	\n\
	orl	$917504,%%eax	\n\
	movl	%%eax,%%ebx	\n\
    " :  : "g" (value) : "ax" );

  }


#undef IPLUS_N
#define IPLUS_N(n) {						\
	fast_op_iplusn(n);					\
	fast2_dispatcher();						\
iplusn_err:							\
	asm("iplusn_err:");					\
	asm("addw $7,%bx");					\
	asm("rorl $15,%ebx");					\
	N_OP_CALL_1d(N_OP_iplusn, n);				\
	}

extern inline const void fast_op_iplusn(LispPTR value)
  {
    asm volatile("\
	movl	%0,%%eax	\n\
	roll	$15,%%eax	\n\
	roll	$15,%%ebx	\n\
	subb	$7,%%bl	\n\
	jne	iplusn_err	\n\
	addl	%%ebx,%%eax	\n\
	jo	iplusn_err	\n\
	rorl	$15,%%eax	\n\
	orl	$917504,%%eax	\n\
	movl	%%eax,%%ebx	\n\
    " :  : "g" (value) : "ax" );

  }


#undef GREATERP 
#define	GREATERP {						\
	fast_op_greaterp(POP_TOS_1);				\
	fast1_dispatcher();						\
greaterp_err:							\
	asm("greaterp_err:");					\
	N_OP_POPPED_CALL_2(N_OP_greaterp, GET_POPPED);		\
	}

extern inline const void fast_op_greaterp(LispPTR value)
  {
    asm volatile("\
	movl	%0,%%eax	\n\
	movl	%%ebx,%%edx	\n\
	roll	$15,%%edx	\n\
	subb	$7,%%dl	\n\
	jne	greaterp_err	\n\
	roll	$15,%%eax	\n\
	subb	$7,%%al	\n\
	jne	greaterp_err	\n\
	xorl	%%ebx,%%ebx	\n\
	cmpl	%%edx,%%eax	\n\
	jle	greater_no	\n\
	movl	$76,%%ebx	\n\
greater_no:    " :  : "g" (value)  );

  }


#undef IGREATERP
#define	IGREATERP {						\
	fast_op_igreaterp(POP_TOS_1);				\
	fast1_dispatcher();						\
igreaterp_err:							\
	asm("igreaterp_err: ");			\
	N_OP_POPPED_CALL_2(N_OP_igreaterp, GET_POPPED);		\
	}

extern inline const void fast_op_igreaterp(LispPTR value)
  {
    asm volatile("\
	movl	%0,%%eax	\n\
	movl	%%ebx,%%edx	\n\
	roll	$15,%%edx	\n\
	subb	$7,%%dl	\n\
	jne	igreaterp_err	\n\
	roll	$15,%%eax	\n\
	subb	$7,%%al	\n\
	jne	igreaterp_err	\n\
	xorl	%%ebx,%%ebx	\n\
	cmpl	%%edx,%%eax	\n\
	jle	igreater_no	\n\
	movl	$76,%%ebx	\n\
igreater_no:    " : : "g" (value)  );

  }


#undef LRSH8
#define LRSH8 {							\
    asm volatile("\
	movl	%%ebx,%%eax	\n\
	roll	$16,%%eax	\n\
	cmpw	$0xe,%%ax	\n\
	jne	lrsh8_err	\n\
	shrw	$8,%%bx	\n\
    " : : : "ax" );	\
	fast1_dispatcher();						\
lrsh8_err:							\
	asm("lrsh8_err: ");					\
	N_OP_CALL_1(N_OP_lrsh8);				\
	}

#undef LRSH1
#define LRSH1 {							\
    asm volatile("\
	movl	%%ebx,%%eax	\n\
	roll	$16,%%eax	\n\
	cmpw	$0xe,%%ax	\n\
	jne	lrsh1_err	\n\
	shrw	$1,%%bx	\n\
    " : : : "ax" );	\
	fast1_dispatcher();						\
lrsh1_err:							\
	asm("lrsh1_err: ");					\
	N_OP_CALL_1(N_OP_lrsh1);				\
	}

#undef LLSH8
#define LLSH8 {							\
    asm volatile("\
	movl	%%ebx,%%eax	\n\
	roll	$16,%%eax	\n\
	cmpw	$0xe,%%ax	\n\
	jne	llsh8_err	\n\
	shlw	$8,%%bx	\n\
    " : : : "ax" );	\
	fast1_dispatcher();						\
llsh8_err:							\
	asm("llsh8_err: ");					\
	N_OP_CALL_1(N_OP_llsh8);				\
	}

#undef LLSH1
#define LLSH1 {							\
    asm volatile("\
	movl	%%ebx,%%eax	\n\
	roll	$16,%%eax	\n\
	cmpw	$0xe,%%ax	\n\
	jne	llsh1_err	\n\
	shlw	$1,%%bx	\n\
    " : : : "ax" );	\
	fast1_dispatcher();						\
llsh1_err:							\
	asm("llsh1_err: ");					\
	N_OP_CALL_1(N_OP_llsh1);				\
	}


#undef LOGOR
#define LOGOR { 						\
	fast_op_logor(POP_TOS_1);				\
	fast1_dispatcher();						\
logor_err:							\
	asm("logor_err:");					\
	asm("rorl $15,%ebx");					\
	N_OP_POPPED_CALL_2(N_OP_logor, GET_POPPED);		\
	}

extern inline const void fast_op_logor(LispPTR value)
  {
    asm volatile("\
	movl	%0,%%eax	\n\
	roll	$15,%%ebx	\n\
	cmpb	$7,%%bl	\n\
	jne	logor_err	\n\
	roll	$15,%%eax	\n\
	cmpb	$7,%%al	\n\
	jne	logor_err	\n\
	orl	%%eax,%%ebx	\n\
	rorl	$15,%%ebx	\n\
    " :  : "g" (value) : "ax" );

  }

 
#undef LOGAND
#define LOGAND {						\
	fast_op_logand(POP_TOS_1);				\
	fast1_dispatcher();						\
logand_err:							\
	asm("logand_err: ");					\
	asm("rorl $15,%ebx");					\
	N_OP_POPPED_CALL_2(N_OP_logand, GET_POPPED);		\
	}

extern inline const void fast_op_logand(LispPTR value)
  {
    asm volatile("\
	movl	%0,%%eax	\n\
	roll	$15,%%ebx	\n\
	cmpb	$7,%%bl	\n\
	jne	logand_err	\n\
	roll	$15,%%eax	\n\
	cmpb	$7,%%al	\n\
	jne	logand_err	\n\
	andl	%%eax,%%ebx	\n\
	rorl	$15,%%ebx	\n\
    " : : "g" (value) : "ax" );

  }


#undef LOGXOR
#define LOGXOR { 						\
	fast_op_logxor(POP_TOS_1);				\
	fast1_dispatcher();						\
logxor_err:							\
	asm("logxor_err:");					\
	asm("rorl $15,%ebx");					\
	N_OP_POPPED_CALL_2(N_OP_logxor, GET_POPPED);		\
	}

extern inline const void fast_op_logxor(LispPTR value)
  {
    asm volatile("\
	movl	%0,%%eax	\n\
	roll	$15,%%ebx	\n\
	cmpb	$7,%%bl	\n\
	jne	logxor_err	\n\
	roll	$15,%%eax	\n\
	subb	$7,%%al	\n\
	jne	logxor_err	\n\
	xorl	%%eax,%%ebx	\n\
	rorl	$15,%%ebx	\n\
    " :  : "g" (value) : "ax" );

  }



#undef N_OP_ADDBASE 
#define N_OP_ADDBASE {						\
	fast_op_addbase(POP_TOS_1);				\
	fast1_dispatcher();						\
addbase_err:							\
	asm("addbase_err: ");					\
	asm("rorl $15,%ebx");					\
	N_OP_POPPED_CALL_2(N_OP_addbase, GET_POPPED);		\
	}
extern inline const void fast_op_addbase(LispPTR value)
  {
    asm volatile("\
	movl	%0,%%eax	\n\
	roll	$15,%%ebx	\n\
	cmpb	$7,%%bl	\n\
	jne	addbase_err	\n\
	sarl	$15,%%ebx	\n\
	andl	$0xFFFFFF,%%eax	\n\
	addl	%%eax,%%ebx	\n\
    " : : "g" (value) : "ax" );

  }




#undef N_OP_LOLOC
#define N_OP_LOLOC	{  \
    asm volatile(" \
	andl	$0x0000FFFF,%0 \n\
	orl	$0x000E0000,%0" : "=r" (tscache) : "0" (tscache)); \
     nextop1; }

#undef N_OP_HILOC
#define N_OP_HILOC	{ \
    asm volatile(" \
	shrl	$16,%0	\n\
	andl	$0x0000FFFF,%0 \n\
	orl	$0x000E0000,%0" : "=r" (tscache) : "0" (tscache)); \
     nextop1; }

#undef N_OP_VAG2
#define N_OP_VAG2						\
  {								\
    asm("	subl	$4,%edi");				\
    asm("	movl	(%edi),%eax");				\
    asm("	roll	$16,%ebx");				\
    asm("	movw	%ax,%bx");				\
    asm("	rorl	$16,%ebx");				\
    nextop1; }


/***********/
/* Fast function call */
#define asm_label_check_interrupt() asm volatile("check_interrupt:");
#undef FN0
#define FN0 \
  {									\
  struct fnhead *LOCFNCELL;					\
  int defcell_word;						\
  int NEXTBLOCK;						\
  int result;							\
  int RESTARGS;						\
    asm volatile("								\n\
	movl %%esi,%%eax	// fn_atom_index = 			\n\
	xorb $3,%%al		// get_AtomNo_PCMAC1			\n\
	movzbl (%%eax),%%edx						\n\
//	movl %%eax,%0							\n\
//	sall $16,%0							\n\
	sall $16,%%edx							\n\
	leal 1(%%esi),%%eax						\n\
	xorb $3,%%al							\n\
	movb (%%eax),%%dh						\n\
//	sall $8,%%ecx							\n\
//	orl %%ecx,%0							\n\
	leal 2(%%esi),%%eax						\n\
	xorb $3,%%al							\n\
	movb (%%eax),%%dl						\n\
	movl %%edx,%0	// to -80					\n\
	" : "=g" (fn_atom_index) : : "ax", "cx", "dx");			\
									\
    asm volatile("								\n\
//	movl %1,%%eax	// fn_defcell = 				\n\
//	movl %%eax,%0							\n\
//	movl %%edx,%0							\n\
	testl $16711680,%%edx						\n\
	je .0L118							\n\
	addl %%edx,%%edx	// new atom case			\n\
	addl Lisp_world,%%edx						\n\
//	movl %%edx,%0							\n\
//	addl $8,%0							\n\
	addl $8,%%edx							\n\
	jmp .0L119							\n\
	.align 4							\n\
.0L118:									\n\
//	movl %0,%%ecx	// old atom case				\n\
	sall $2,%%edx							\n\
	addl Defspace,%%edx						\n\
//	movl %%ecx,%0							\n\
.0L119:									\n\
//	movl %0,%%edx							\n\
	movl %%edx,%0	// to -92					\n\
	" : "=g" (fn_defcell) : "g" (fn_atom_index) : "ax", "cx", "dx"); \
									\
    asm volatile("							\n\
//	movl %1,%%eax	// defcell_word = 				\n\
	movl (%%edx),%%eax						\n\
	movl %%eax,%0	// to -32 (must remain, it's used by C below)	\n\
	testl %%eax,%%eax	// if defcell_word>0			\n\
	jl .0L120							\n\
	" : "=g" (defcell_word) : "g" (fn_defcell) : "ax", "dx");	\
									\
	{ /* it's not a CCODEP */					\
	  fn_num_args = 0	/* argcount*/;				\
	  fn_opcode_size = FN_OPCODE_SIZE;				\
	  fn_apply = 0;							\
	  goto op_fn_common;						\
	}								\
L0120:									\
    asm volatile("							\n\
	.align 4							\n\
//.0L120:				// fn is compiled.		\n\
//	andl $16777215,%1	// LOCFNCELL=				\n\
//	movl %1,%%ecx							\n\
.0L120:	andl $16777215,%%eax						\n\
	movl %%eax,%1							\n\
	addl %%eax,%%eax						\n\
	addl Lisp_world,%%eax						\n\
	movl %%eax,%0		// to -80				\n\
	" : "=g" (LOCFNCELL), "=g" (defcell_word) : : "cx");		\
									\
    asm volatile("								\n\
	movw MachineState+20,%%dx	// currentfx pc =		\n\
	incw %%dx							\n\
	movl %%esi,%%ecx		// PCMAC -			\n\
	subw %%dx,%%cx		// funcobj				\n\
	addw $4,%%cx		// + opcode size			\n\
	movl MachineState+4,%%edx					\n\
	movw %%cx,-12(%%edx)	// save in frame			\n\
//	movl %0,%%edx	// FN_STACK_CHECK				\n\
	movzwl 2(%%eax),%%edx						\n\
	addl %%edx,%%edx						\n\
	movl MachineState+32,%%eax					\n\
	subl %%edx,%%eax						\n\
//	movl %%eax,-84(%%ebp)						\n\
	movl %%eax,MachineState+28 // Irq_Stk_Check =			\n\
	cmpl %%eax,%%edi						\n\
	jg check_interrupt	//goto check_interrupt			\n\
	" :  : "g" (LOCFNCELL) : "ax", "dx", "cx");			\
									\
    asm volatile("								\n\
	leal 4(%%edi),%%ecx	// newivar = CSTKPTR-argcount+1		\n\
//	movl %%ecx,-84(%%ebp)						\n\
	movl %%ecx,MachineState						\n\
	subl Stackspace,%%ecx						\n\
	shrl $1,%%ecx	// NEXTBLOCK in -88				\n\
	movl %%ecx,%0							\n\
//	movw %0,%%ax							\n\
	movl MachineState+4,%%edx					\n\
	movw %%cx,-10(%%edx)	// currentfx->nextblock =		\n\
	movl %%ebx,(%%edi)	// HARD_PUSH tos			\n\
	addl $4,%%edi							\n\
	" : "=g" (NEXTBLOCK) : : "ax", "dx", "cx");			\
									\
    asm volatile("								\n\
	movl %1,%%ecx	// if LOCFNCELL->na				\n\
	cmpw $0,(%%ecx)		//  >= 0				\n\
	jl .0L122							\n\
				// then					\n\
	movswl (%%ecx),%%ecx	// RESTARGS = #args(0)			\n\
	movl %%ecx,%0							\n\
	negl %0		// - na.  in -92.				\n\
	jns .0L124	// if > 0, skip loop.				\n\
	.align 4							\n\
.0L125:			// while RESTARGS<0				\n\
	movl $0,(%%edi)	// HARD_PUSH NIL				\n\
	addl $4,%%edi							\n\
	incl %0	// RESTARGS++						\n\
	js .0L125	// loop.					\n\
.0L124:									\n\
	movl %0,%%edx	// CSTKPTRL -=					\n\
	sall $2,%%edx		//   RESTARGS				\n\
	movl %%edi,%%eax						\n\
	subl %%edx,%%eax						\n\
//	movl %%eax,-84(%%ebp)						\n\
//	movl -84(%%ebp),%%edi						\n\
	movl %%eax,%%edi	// replace above 2 lns.			\n\
	" : "=g" (RESTARGS) : "g" (LOCFNCELL) : "ax", "dx", "cx");	\
									\
    asm volatile("								\n\
.0L122:				// na <0 ??				\n\
	movl %1,%%ecx	// HARDPUSH(BFMARK | NEXTBLOCK)			\n\
	orl $-2147483648,%%ecx						\n\
	movl %%ecx,(%%edi)						\n\
	addl $4,%%edi							\n\
	movl MachineState+4,%%edx	// * CSTKPTR =			\n\
	subl Stackspace,%%edx	// FXMARK<<16 |				\n\
	shrl $1,%%edx	// StkOffsetfrom68k(PVAR).			\n\
	orl $-1073741824,%%edx						\n\
	movl %%edx,(%%edi)						\n\
									\n\
	movl %3,%%eax	// fnheader =				\n\
/APP									\n\
	roll	$16,%%eax	// swapx(defcell_word)			\n\
/NO_APP									\n\
	movl %%eax,4(%%edi)						\n\
	leal 20(%%edi),%%ecx	// CSTKPTRL = 				\n\
//	movl %%ecx,-84(%%ebp)						\n\
//	movl -84(%%ebp),%%edi	// CSTKPTR+frame size			\n\
	movl %%ecx,%%edi						\n\
	movl %%edi,MachineState+4 // PVAR = CSTKPTR			\n\
									\n\
	movl %2,%%edx	// result =					\n\
	movswl 6(%%edx),%%edx	// LOCFNCELL->pv			\n\
//	movl %%edx,%0	// result in -88				\n\
	testl %%edx,%%edx	// if result >= 0			\n\
	jl .0L127							\n\
			// then...					\n\
	movl $-1,(%%edi)	// HARD PUSH unboundval			\n\
	addl $4,%%edi							\n\
	movl $-1,(%%edi)	// HARD PUSH unboundval			\n\
	addl $4,%%edi							\n\
//	cmpl $0,%0	// if result>0					\n\
	cmpl $0,%%edx							\n\
	jle .0L127							\n\
	movl $-1,(%%edi)	// hard push unbound			\n\
	addl $4,%%edi							\n\
	movl $-1,(%%edi)	// hard push unbound			\n\
	addl $4,%%edi							\n\
//	addl $-2,%0 // result -= 1					\n\
	addl $-2,%%edx							\n\
	js .0L127							\n\
	.align 4							\n\
.0L132:		// while --result >= 0 (-- is above)			\n\
	movl $-1,(%%edi)	// hard push				\n\
	addl $4,%%edi							\n\
	movl $-1,(%%edi)	// hard push				\n\
	addl $4,%%edi							\n\
	decl %%edx								\n\
	jns .0L132							\n\
.0L127:									\n\
	leal 4(%%edi),%%eax	// CSTKPTRL += 1			\n\
//	movl %%eax,-84(%%ebp)						\n\
//	movl -84(%%ebp),%%edi						\n\
	movl %%eax,%%edi	// replace above 2 inst			\n\
	movl %2,%%ecx	// PCMACL = LOCFNCELL				\n\
	movzwl 4(%%ecx),%%ecx	// + LOCFNCELL-> startpc		\n\
//	movl %%ecx,-84(%%ebp)						\n\
	movl %2,%%edx							\n\
	leal 1(%%ecx,%%edx),%%edx					\n\
//	movl %%edx,-84(%%ebp)						\n\
//	movl -84(%%ebp),%%esi						\n\
	movl %%edx,%%esi	//replace above 2 inst			\n\
	movl %2,%%eax	//FuncObj = LOCFNCELL				\n\
	movl %%eax,MachineState+20					\n\
	" : "=&g" (result) : "g" (NEXTBLOCK),  "g" (LOCFNCELL),		\
	"g" (defcell_word) : "ax", "dx", "cx");				\
									\
    nextop0;								\
}


#undef FN1
#define FN1 \
  {									\
  struct fnhead *LOCFNCELL;					\
  int defcell_word;						\
  int NEXTBLOCK;						\
  int result;							\
  int RESTARGS;						\
    asm volatile("								\n\
	movl %%esi,%%eax	// fn_atom_index = 			\n\
	xorb $3,%%al		// get_AtomNo_PCMAC1			\n\
	movzbl (%%eax),%%edx						\n\
//	movl %%eax,%0							\n\
//	sall $16,%0							\n\
	sall $16,%%edx							\n\
	leal 1(%%esi),%%eax						\n\
	xorb $3,%%al							\n\
	movb (%%eax),%%dh						\n\
//	sall $8,%%ecx							\n\
//	orl %%ecx,%0							\n\
	leal 2(%%esi),%%eax						\n\
	xorb $3,%%al							\n\
	movb (%%eax),%%dl						\n\
	movl %%edx,%0	// to -80					\n\
	" : "=g" (fn_atom_index) : : "ax", "cx", "dx");			\
									\
    asm volatile("								\n\
//	movl %1,%%eax	// fn_defcell = 				\n\
//	movl %%eax,%0							\n\
//	movl %%edx,%0							\n\
	testl $16711680,%%edx						\n\
	je .1L118							\n\
	addl %%edx,%%edx	// new atom case			\n\
	addl Lisp_world,%%edx						\n\
//	movl %%edx,%0							\n\
//	addl $8,%0							\n\
	addl $8,%%edx							\n\
	jmp .1L119							\n\
	.align 4							\n\
.1L118:									\n\
//	movl %0,%%ecx	// old atom case				\n\
	sall $2,%%edx							\n\
	addl Defspace,%%edx						\n\
//	movl %%ecx,%0							\n\
.1L119:									\n\
//	movl %0,%%edx							\n\
	movl %%edx,%0	// to -92					\n\
	" : "=g" (fn_defcell) : "g" (fn_atom_index) : "ax", "cx", "dx"); \
									\
    asm volatile("							\n\
//	movl %1,%%eax	// defcell_word = 				\n\
	movl (%%edx),%%eax						\n\
	movl %%eax,%0	// to -32 (must remain, it's used by C below)	\n\
	testl %%eax,%%eax	// if defcell_word>0			\n\
	jl .1L120							\n\
	" : "=g" (defcell_word) : "g" (fn_defcell) : "ax", "dx");	\
									\
	{ /* it's not a CCODEP */					\
	  fn_num_args = 1	/* argcount*/;				\
	  fn_opcode_size = FN_OPCODE_SIZE;				\
	  fn_apply = 0;							\
	  goto op_fn_common;						\
	}								\
L1120:									\
    asm volatile("							\n\
	.align 4							\n\
//.1L120:				// fn is compiled.		\n\
//	andl $16777215,%1	// LOCFNCELL=				\n\
//	movl %1,%%ecx							\n\
.1L120:	andl $16777215,%%eax						\n\
	movl %%eax,%1							\n\
	addl %%eax,%%eax						\n\
	addl Lisp_world,%%eax						\n\
	movl %%eax,%0		// to -80				\n\
	" : "=g" (LOCFNCELL), "=g" (defcell_word) : : "cx");		\
									\
    asm volatile("								\n\
	movw MachineState+20,%%dx	// currentfx pc =		\n\
	incw %%dx							\n\
	movl %%esi,%%ecx		// PCMAC -			\n\
	subw %%dx,%%cx		// funcobj				\n\
	addw $4,%%cx		// + opcode size			\n\
	movl MachineState+4,%%edx					\n\
	movw %%cx,-12(%%edx)	// save in frame			\n\
//	movl %0,%%edx	// FN_STACK_CHECK				\n\
	movzwl 2(%%eax),%%edx						\n\
	addl %%edx,%%edx						\n\
	movl MachineState+32,%%eax					\n\
	subl %%edx,%%eax						\n\
//	movl %%eax,-84(%%ebp)						\n\
	movl %%eax,MachineState+28 // Irq_Stk_Check =			\n\
	cmpl %%eax,%%edi						\n\
	jg check_interrupt	//goto check_interrupt			\n\
	" :  : "g" (LOCFNCELL) : "ax", "dx", "cx");			\
									\
    asm volatile("								\n\
	leal (%%edi),%%ecx	// newivar = CSTKPTR-argcount+1		\n\
//	movl %%ecx,-84(%%ebp)						\n\
	movl %%ecx,MachineState						\n\
	subl Stackspace,%%ecx						\n\
	shrl $1,%%ecx	// NEXTBLOCK in -88				\n\
	movl %%ecx,%0							\n\
//	movw %0,%%ax							\n\
	movl MachineState+4,%%edx					\n\
	movw %%cx,-10(%%edx)	// currentfx->nextblock =		\n\
	movl %%ebx,(%%edi)	// HARD_PUSH tos			\n\
	addl $4,%%edi							\n\
	" : "=g" (NEXTBLOCK) : : "ax", "dx", "cx");			\
									\
    asm volatile("								\n\
	movl %1,%%ecx	// if LOCFNCELL->na				\n\
	cmpw $0,(%%ecx)		//  >= 0				\n\
	jl .1L122							\n\
				// then					\n\
	movswl (%%ecx),%%ecx	// RESTARGS = #args(0)			\n\
	movl %%ecx,%0							\n\
	decl %0								\n\
	negl %0		// - na.  in -92.				\n\
	jns .1L124	// if > 0, skip loop.				\n\
	.align 4							\n\
.1L125:			// while RESTARGS<0				\n\
	movl $0,(%%edi)	// HARD_PUSH NIL				\n\
	addl $4,%%edi							\n\
	incl %0	// RESTARGS++						\n\
	js .1L125	// loop.					\n\
.1L124:									\n\
	movl %0,%%edx	// CSTKPTRL -=					\n\
	sall $2,%%edx		//   RESTARGS				\n\
	movl %%edi,%%eax						\n\
	subl %%edx,%%eax						\n\
//	movl %%eax,-84(%%ebp)						\n\
//	movl -84(%%ebp),%%edi						\n\
	movl %%eax,%%edi	// replace above 2 lns.			\n\
	" : "=g" (RESTARGS) : "g" (LOCFNCELL) : "ax", "dx", "cx");	\
									\
    asm volatile("								\n\
.1L122:				// na <0 ??				\n\
	movl %1,%%ecx	// HARDPUSH(BFMARK | NEXTBLOCK)			\n\
	orl $-2147483648,%%ecx						\n\
	movl %%ecx,(%%edi)						\n\
	addl $4,%%edi							\n\
	movl MachineState+4,%%edx	// * CSTKPTR =			\n\
	subl Stackspace,%%edx	// FXMARK<<16 |				\n\
	shrl $1,%%edx	// StkOffsetfrom68k(PVAR).			\n\
	orl $-1073741824,%%edx						\n\
	movl %%edx,(%%edi)						\n\
									\n\
	movl %3,%%eax	// fnheader =				\n\
/APP									\n\
	roll	$16,%%eax	// swapx(defcell_word)			\n\
/NO_APP									\n\
	movl %%eax,4(%%edi)						\n\
	leal 20(%%edi),%%ecx	// CSTKPTRL = 				\n\
//	movl %%ecx,-84(%%ebp)						\n\
//	movl -84(%%ebp),%%edi	// CSTKPTR+frame size			\n\
	movl %%ecx,%%edi						\n\
	movl %%edi,MachineState+4 // PVAR = CSTKPTR			\n\
									\n\
	movl %2,%%edx	// result =					\n\
	movswl 6(%%edx),%%edx	// LOCFNCELL->pv			\n\
//	movl %%edx,%0	// result in -88				\n\
	testl %%edx,%%edx	// if result >= 0			\n\
	jl .1L127							\n\
			// then...					\n\
	movl $-1,(%%edi)	// HARD PUSH unboundval			\n\
	addl $4,%%edi							\n\
	movl $-1,(%%edi)	// HARD PUSH unboundval			\n\
	addl $4,%%edi							\n\
//	cmpl $0,%0	// if result>0					\n\
	cmpl $0,%%edx							\n\
	jle .1L127							\n\
	movl $-1,(%%edi)	// hard push unbound			\n\
	addl $4,%%edi							\n\
	movl $-1,(%%edi)	// hard push unbound			\n\
	addl $4,%%edi							\n\
//	addl $-2,%0 // result -= 1					\n\
	addl $-2,%%edx							\n\
	js .1L127							\n\
	.align 4							\n\
.1L132:		// while --result >= 0 (-- is above)			\n\
	movl $-1,(%%edi)	// hard push				\n\
	addl $4,%%edi							\n\
	movl $-1,(%%edi)	// hard push				\n\
	addl $4,%%edi							\n\
	decl %%edx								\n\
	jns .1L132							\n\
.1L127:									\n\
	leal 4(%%edi),%%eax	// CSTKPTRL += 1			\n\
//	movl %%eax,-84(%%ebp)						\n\
//	movl -84(%%ebp),%%edi						\n\
	movl %%eax,%%edi	// replace above 2 inst			\n\
	movl %2,%%ecx	// PCMACL = LOCFNCELL				\n\
	movzwl 4(%%ecx),%%ecx	// + LOCFNCELL-> startpc		\n\
//	movl %%ecx,-84(%%ebp)						\n\
	movl %2,%%edx							\n\
	leal 1(%%ecx,%%edx),%%edx					\n\
//	movl %%edx,-84(%%ebp)						\n\
//	movl -84(%%ebp),%%esi						\n\
	movl %%edx,%%esi	//replace above 2 inst			\n\
	movl %2,%%eax	//FuncObj = LOCFNCELL				\n\
	movl %%eax,MachineState+20					\n\
	" : "=&g" (result) : "g" (NEXTBLOCK),  "g" (LOCFNCELL),		\
	"g" (defcell_word) : "ax", "dx", "cx");				\
									\
    nextop0;								\
}

#undef FN2
#define FN2 \
  {									\
  struct fnhead *LOCFNCELL;					\
  int defcell_word;						\
  int NEXTBLOCK;						\
  int result;							\
  int RESTARGS;						\
    asm volatile("								\n\
	movl %%esi,%%eax	// fn_atom_index = 			\n\
	xorb $3,%%al		// get_AtomNo_PCMAC1			\n\
	movzbl (%%eax),%%edx						\n\
//	movl %%eax,%0							\n\
//	sall $16,%0							\n\
	sall $16,%%edx							\n\
	leal 1(%%esi),%%eax						\n\
	xorb $3,%%al							\n\
	movb (%%eax),%%dh						\n\
//	sall $8,%%ecx							\n\
//	orl %%ecx,%0							\n\
	leal 2(%%esi),%%eax						\n\
	xorb $3,%%al							\n\
	movb (%%eax),%%dl						\n\
	movl %%edx,%0	// to -80					\n\
	" : "=g" (fn_atom_index) : : "ax", "cx", "dx");			\
									\
    asm volatile("								\n\
//	movl %1,%%eax	// fn_defcell = 				\n\
//	movl %%eax,%0							\n\
//	movl %%edx,%0							\n\
	testl $16711680,%%edx						\n\
	je .2L118							\n\
	addl %%edx,%%edx	// new atom case			\n\
	addl Lisp_world,%%edx						\n\
//	movl %%edx,%0							\n\
//	addl $8,%0							\n\
	addl $8,%%edx							\n\
	jmp .2L119							\n\
	.align 4							\n\
.2L118:									\n\
//	movl %0,%%ecx	// old atom case				\n\
	sall $2,%%edx							\n\
	addl Defspace,%%edx						\n\
//	movl %%ecx,%0							\n\
.2L119:									\n\
//	movl %0,%%edx							\n\
	movl %%edx,%0	// to -92					\n\
	" : "=g" (fn_defcell) : "g" (fn_atom_index) : "ax", "cx", "dx"); \
									\
    asm volatile("							\n\
//	movl %1,%%eax	// defcell_word = 				\n\
	movl (%%edx),%%eax						\n\
	movl %%eax,%0	// to -32 (must remain, it's used by C below)	\n\
	testl %%eax,%%eax	// if defcell_word>0			\n\
	jl .2L120							\n\
	" : "=g" (defcell_word) : "g" (fn_defcell) : "ax", "dx");	\
									\
	{ /* it's not a CCODEP */					\
	  fn_num_args = 2	/* argcount*/;				\
	  fn_opcode_size = FN_OPCODE_SIZE;				\
	  fn_apply = 0;							\
	  goto op_fn_common;						\
	}								\
L2120:									\
    asm volatile("							\n\
	.align 4							\n\
//.2L120:				// fn is compiled.		\n\
//	andl $16777215,%1	// LOCFNCELL=				\n\
//	movl %1,%%ecx							\n\
.2L120:	andl $16777215,%%eax						\n\
	movl %%eax,%1							\n\
	addl %%eax,%%eax						\n\
	addl Lisp_world,%%eax						\n\
	movl %%eax,%0		// to -80				\n\
	" : "=g" (LOCFNCELL), "=g" (defcell_word) : : "cx");		\
									\
    asm volatile("								\n\
	movw MachineState+20,%%dx	// currentfx pc =		\n\
	incw %%dx							\n\
	movl %%esi,%%ecx		// PCMAC -			\n\
	subw %%dx,%%cx		// funcobj				\n\
	addw $4,%%cx		// + opcode size			\n\
	movl MachineState+4,%%edx					\n\
	movw %%cx,-12(%%edx)	// save in frame			\n\
//	movl %0,%%edx	// FN_STACK_CHECK				\n\
	movzwl 2(%%eax),%%edx						\n\
	addl %%edx,%%edx						\n\
	movl MachineState+32,%%eax					\n\
	subl %%edx,%%eax						\n\
//	movl %%eax,-84(%%ebp)						\n\
	movl %%eax,MachineState+28 // Irq_Stk_Check =			\n\
	cmpl %%eax,%%edi						\n\
	jg check_interrupt	//goto check_interrupt			\n\
	" :  : "g" (LOCFNCELL) : "ax", "dx", "cx");			\
									\
    asm volatile("								\n\
	leal -4(%%edi),%%ecx	// newivar = CSTKPTR-argcount+1		\n\
//	movl %%ecx,-84(%%ebp)						\n\
	movl %%ecx,MachineState						\n\
	subl Stackspace,%%ecx						\n\
	shrl $1,%%ecx	// NEXTBLOCK in -88				\n\
	movl %%ecx,%0							\n\
//	movw %0,%%ax							\n\
	movl MachineState+4,%%edx					\n\
	movw %%cx,-10(%%edx)	// currentfx->nextblock =		\n\
	movl %%ebx,(%%edi)	// HARD_PUSH tos			\n\
	addl $4,%%edi							\n\
	" : "=g" (NEXTBLOCK) : : "ax", "dx", "cx");			\
									\
    asm volatile("								\n\
	movl %1,%%ecx	// if LOCFNCELL->na				\n\
	cmpw $0,(%%ecx)		//  >= 0				\n\
	jl .2L122							\n\
				// then					\n\
	movswl (%%ecx),%%ecx	// RESTARGS = #args(0)			\n\
	movl %%ecx,%0							\n\
	decl %0								\n\
	decl %0								\n\
	negl %0		// - na.  in -92.				\n\
	jns .2L124	// if > 0, skip loop.				\n\
	.align 4							\n\
.2L125:			// while RESTARGS<0				\n\
	movl $0,(%%edi)	// HARD_PUSH NIL				\n\
	addl $4,%%edi							\n\
	incl %0	// RESTARGS++						\n\
	js .2L125	// loop.					\n\
.2L124:									\n\
	movl %0,%%edx	// CSTKPTRL -=					\n\
	sall $2,%%edx		//   RESTARGS				\n\
	movl %%edi,%%eax						\n\
	subl %%edx,%%eax						\n\
//	movl %%eax,-84(%%ebp)						\n\
//	movl -84(%%ebp),%%edi						\n\
	movl %%eax,%%edi	// replace above 2 lns.			\n\
	" : "=g" (RESTARGS) : "g" (LOCFNCELL) : "ax", "dx", "cx");	\
									\
    asm volatile("								\n\
.2L122:				// na <0 ??				\n\
	movl %1,%%ecx	// HARDPUSH(BFMARK | NEXTBLOCK)			\n\
	orl $-2147483648,%%ecx						\n\
	movl %%ecx,(%%edi)						\n\
	addl $4,%%edi							\n\
	movl MachineState+4,%%edx	// * CSTKPTR =			\n\
	subl Stackspace,%%edx	// FXMARK<<16 |				\n\
	shrl $1,%%edx	// StkOffsetfrom68k(PVAR).			\n\
	orl $-1073741824,%%edx						\n\
	movl %%edx,(%%edi)						\n\
									\n\
	movl %3,%%eax	// fnheader =				\n\
/APP									\n\
	roll	$16,%%eax	// swapx(defcell_word)			\n\
/NO_APP									\n\
	movl %%eax,4(%%edi)						\n\
	leal 20(%%edi),%%ecx	// CSTKPTRL = 				\n\
//	movl %%ecx,-84(%%ebp)						\n\
//	movl -84(%%ebp),%%edi	// CSTKPTR+frame size			\n\
	movl %%ecx,%%edi						\n\
	movl %%edi,MachineState+4 // PVAR = CSTKPTR			\n\
									\n\
	movl %2,%%edx	// result =					\n\
	movswl 6(%%edx),%%edx	// LOCFNCELL->pv			\n\
//	movl %%edx,%0	// result in -88				\n\
	testl %%edx,%%edx	// if result >= 0			\n\
	jl .2L127							\n\
			// then...					\n\
	movl $-1,(%%edi)	// HARD PUSH unboundval			\n\
	addl $4,%%edi							\n\
	movl $-1,(%%edi)	// HARD PUSH unboundval			\n\
	addl $4,%%edi							\n\
//	cmpl $0,%0	// if result>0					\n\
	cmpl $0,%%edx							\n\
	jle .2L127							\n\
	movl $-1,(%%edi)	// hard push unbound			\n\
	addl $4,%%edi							\n\
	movl $-1,(%%edi)	// hard push unbound			\n\
	addl $4,%%edi							\n\
//	addl $-2,%0 // result -= 1					\n\
	addl $-2,%%edx							\n\
	js .2L127							\n\
	.align 4							\n\
.2L132:		// while --result >= 0 (-- is above)			\n\
	movl $-1,(%%edi)	// hard push				\n\
	addl $4,%%edi							\n\
	movl $-1,(%%edi)	// hard push				\n\
	addl $4,%%edi							\n\
	decl %%edx								\n\
	jns .2L132							\n\
.2L127:									\n\
	leal 4(%%edi),%%eax	// CSTKPTRL += 1			\n\
//	movl %%eax,-84(%%ebp)						\n\
//	movl -84(%%ebp),%%edi						\n\
	movl %%eax,%%edi	// replace above 2 inst			\n\
	movl %2,%%ecx	// PCMACL = LOCFNCELL				\n\
	movzwl 4(%%ecx),%%ecx	// + LOCFNCELL-> startpc		\n\
//	movl %%ecx,-84(%%ebp)						\n\
	movl %2,%%edx							\n\
	leal 1(%%ecx,%%edx),%%edx					\n\
//	movl %%edx,-84(%%ebp)						\n\
//	movl -84(%%ebp),%%esi						\n\
	movl %%edx,%%esi	//replace above 2 inst			\n\
	movl %2,%%eax	//FuncObj = LOCFNCELL				\n\
	movl %%eax,MachineState+20					\n\
	" : "=&g" (result) : "g" (NEXTBLOCK),  "g" (LOCFNCELL),		\
	"g" (defcell_word) : "ax", "dx", "cx");				\
									\
    nextop0;								\
}

#undef FN3
#define FN3 \
  {									\
  struct fnhead *LOCFNCELL;					\
  int defcell_word;						\
  int NEXTBLOCK;						\
  int result;							\
  int RESTARGS;						\
    asm volatile("								\n\
	movl %%esi,%%eax	// fn_atom_index = 			\n\
	xorb $3,%%al		// get_AtomNo_PCMAC1			\n\
	movzbl (%%eax),%%edx						\n\
//	movl %%eax,%0							\n\
//	sall $16,%0							\n\
	sall $16,%%edx							\n\
	leal 1(%%esi),%%eax						\n\
	xorb $3,%%al							\n\
	movb (%%eax),%%dh						\n\
//	sall $8,%%ecx							\n\
//	orl %%ecx,%0							\n\
	leal 2(%%esi),%%eax						\n\
	xorb $3,%%al							\n\
	movb (%%eax),%%dl						\n\
	movl %%edx,%0	// to -80					\n\
	" : "=g" (fn_atom_index) : : "ax", "cx", "dx");			\
									\
    asm volatile("								\n\
//	movl %1,%%eax	// fn_defcell = 				\n\
//	movl %%eax,%0							\n\
//	movl %%edx,%0							\n\
	testl $16711680,%%edx						\n\
	je .3L118							\n\
	addl %%edx,%%edx	// new atom case			\n\
	addl Lisp_world,%%edx						\n\
//	movl %%edx,%0							\n\
//	addl $8,%0							\n\
	addl $8,%%edx							\n\
	jmp .3L119							\n\
	.align 4							\n\
.3L118:									\n\
//	movl %0,%%ecx	// old atom case				\n\
	sall $2,%%edx							\n\
	addl Defspace,%%edx						\n\
//	movl %%ecx,%0							\n\
.3L119:									\n\
//	movl %0,%%edx							\n\
	movl %%edx,%0	// to -92					\n\
	" : "=g" (fn_defcell) : "g" (fn_atom_index) : "ax", "cx", "dx"); \
									\
    asm volatile("							\n\
//	movl %1,%%eax	// defcell_word = 				\n\
	movl (%%edx),%%eax						\n\
	movl %%eax,%0	// to -32 (must remain, it's used by C below)	\n\
	testl %%eax,%%eax	// if defcell_word>0			\n\
	jl .3L120							\n\
	" : "=g" (defcell_word) : "g" (fn_defcell) : "ax", "dx");	\
									\
	{ /* it's not a CCODEP */					\
	  fn_num_args = 3	/* argcount*/;				\
	  fn_opcode_size = FN_OPCODE_SIZE;				\
	  fn_apply = 0;							\
	  goto op_fn_common;						\
	}								\
L3120:									\
    asm volatile("							\n\
	.align 4							\n\
//.3L120:				// fn is compiled.		\n\
//	andl $16777215,%1	// LOCFNCELL=				\n\
//	movl %1,%%ecx							\n\
.3L120:	andl $16777215,%%eax						\n\
	movl %%eax,%1							\n\
	addl %%eax,%%eax						\n\
	addl Lisp_world,%%eax						\n\
	movl %%eax,%0		// to -80				\n\
	" : "=g" (LOCFNCELL), "=g" (defcell_word) : : "cx");		\
									\
    asm volatile("								\n\
	movw MachineState+20,%%dx	// currentfx pc =		\n\
	incw %%dx							\n\
	movl %%esi,%%ecx		// PCMAC -			\n\
	subw %%dx,%%cx		// funcobj				\n\
	addw $4,%%cx		// + opcode size			\n\
	movl MachineState+4,%%edx					\n\
	movw %%cx,-12(%%edx)	// save in frame			\n\
//	movl %0,%%edx	// FN_STACK_CHECK				\n\
	movzwl 2(%%eax),%%edx						\n\
	addl %%edx,%%edx						\n\
	movl MachineState+32,%%eax					\n\
	subl %%edx,%%eax						\n\
//	movl %%eax,-84(%%ebp)						\n\
	movl %%eax,MachineState+28 // Irq_Stk_Check =			\n\
	cmpl %%eax,%%edi						\n\
	jg check_interrupt	//goto check_interrupt			\n\
	" :  : "g" (LOCFNCELL) : "ax", "dx", "cx");			\
									\
    asm volatile("								\n\
	leal -8(%%edi),%%ecx	// newivar = CSTKPTR-argcount+1		\n\
//	movl %%ecx,-84(%%ebp)						\n\
	movl %%ecx,MachineState						\n\
	subl Stackspace,%%ecx						\n\
	shrl $1,%%ecx	// NEXTBLOCK in -88				\n\
	movl %%ecx,%0							\n\
//	movw %0,%%ax							\n\
	movl MachineState+4,%%edx					\n\
	movw %%cx,-10(%%edx)	// currentfx->nextblock =		\n\
	movl %%ebx,(%%edi)	// HARD_PUSH tos			\n\
	addl $4,%%edi							\n\
	" : "=g" (NEXTBLOCK) : : "ax", "dx", "cx");			\
									\
    asm volatile("								\n\
	movl %1,%%ecx	// if LOCFNCELL->na				\n\
	cmpw $0,(%%ecx)		//  >= 0				\n\
	jl .3L122							\n\
				// then					\n\
	movswl (%%ecx),%%ecx	// RESTARGS = #args(0)			\n\
	movl %%ecx,%0							\n\
	decl %0								\n\
	decl %0								\n\
	decl %0								\n\
	negl %0		// - na.  in -92.				\n\
	jns .3L124	// if > 0, skip loop.				\n\
	.align 4							\n\
.3L125:			// while RESTARGS<0				\n\
	movl $0,(%%edi)	// HARD_PUSH NIL				\n\
	addl $4,%%edi							\n\
	incl %0	// RESTARGS++						\n\
	js .3L125	// loop.					\n\
.3L124:									\n\
	movl %0,%%edx	// CSTKPTRL -=					\n\
	sall $2,%%edx		//   RESTARGS				\n\
	movl %%edi,%%eax						\n\
	subl %%edx,%%eax						\n\
//	movl %%eax,-84(%%ebp)						\n\
//	movl -84(%%ebp),%%edi						\n\
	movl %%eax,%%edi	// replace above 2 lns.			\n\
	" : "=g" (RESTARGS) : "g" (LOCFNCELL) : "ax", "dx", "cx");	\
									\
    asm volatile("								\n\
.3L122:				// na <0 ??				\n\
	movl %1,%%ecx	// HARDPUSH(BFMARK | NEXTBLOCK)			\n\
	orl $-2147483648,%%ecx						\n\
	movl %%ecx,(%%edi)						\n\
	addl $4,%%edi							\n\
	movl MachineState+4,%%edx	// * CSTKPTR =			\n\
	subl Stackspace,%%edx	// FXMARK<<16 |				\n\
	shrl $1,%%edx	// StkOffsetfrom68k(PVAR).			\n\
	orl $-1073741824,%%edx						\n\
	movl %%edx,(%%edi)						\n\
									\n\
	movl %3,%%eax	// fnheader =				\n\
/APP									\n\
	roll	$16,%%eax	// swapx(defcell_word)			\n\
/NO_APP									\n\
	movl %%eax,4(%%edi)						\n\
	leal 20(%%edi),%%ecx	// CSTKPTRL = 				\n\
//	movl %%ecx,-84(%%ebp)						\n\
//	movl -84(%%ebp),%%edi	// CSTKPTR+frame size			\n\
	movl %%ecx,%%edi						\n\
	movl %%edi,MachineState+4 // PVAR = CSTKPTR			\n\
									\n\
	movl %2,%%edx	// result =					\n\
	movswl 6(%%edx),%%edx	// LOCFNCELL->pv			\n\
//	movl %%edx,%0	// result in -88				\n\
	testl %%edx,%%edx	// if result >= 0			\n\
	jl .3L127							\n\
			// then...					\n\
	movl $-1,(%%edi)	// HARD PUSH unboundval			\n\
	addl $4,%%edi							\n\
	movl $-1,(%%edi)	// HARD PUSH unboundval			\n\
	addl $4,%%edi							\n\
//	cmpl $0,%0	// if result>0					\n\
	cmpl $0,%%edx							\n\
	jle .3L127							\n\
	movl $-1,(%%edi)	// hard push unbound			\n\
	addl $4,%%edi							\n\
	movl $-1,(%%edi)	// hard push unbound			\n\
	addl $4,%%edi							\n\
//	addl $-2,%0 // result -= 1					\n\
	addl $-2,%%edx							\n\
	js .3L127							\n\
	.align 4							\n\
.3L132:		// while --result >= 0 (-- is above)			\n\
	movl $-1,(%%edi)	// hard push				\n\
	addl $4,%%edi							\n\
	movl $-1,(%%edi)	// hard push				\n\
	addl $4,%%edi							\n\
	decl %%edx								\n\
	jns .3L132							\n\
.3L127:									\n\
	leal 4(%%edi),%%eax	// CSTKPTRL += 1			\n\
//	movl %%eax,-84(%%ebp)						\n\
//	movl -84(%%ebp),%%edi						\n\
	movl %%eax,%%edi	// replace above 2 inst			\n\
	movl %2,%%ecx	// PCMACL = LOCFNCELL				\n\
	movzwl 4(%%ecx),%%ecx	// + LOCFNCELL-> startpc		\n\
//	movl %%ecx,-84(%%ebp)						\n\
	movl %2,%%edx							\n\
	leal 1(%%ecx,%%edx),%%edx					\n\
//	movl %%edx,-84(%%ebp)						\n\
//	movl -84(%%ebp),%%esi						\n\
	movl %%edx,%%esi	//replace above 2 inst			\n\
	movl %2,%%eax	//FuncObj = LOCFNCELL				\n\
	movl %%eax,MachineState+20					\n\
	" : "=&g" (result) : "g" (NEXTBLOCK),  "g" (LOCFNCELL),		\
	"g" (defcell_word) : "ax", "dx", "cx");				\
									\
    nextop0;								\
}

/* * * * *

#undef FN4
#define FN4 fast_FN4()

#undef FN5
#define FN5 fast_FN5()

#undef FN6
#define FN6 fast_FN6()

#undef FN7
#define FN7 fast_FN7()

#undef FN8
#define FN8 fast_FN8()

#undef FN9
#define FN9 fast_FN9()
*/


/************************************************************************/
/*									*/
/*									*/
/*									*/
/*									*/
/*									*/
/************************************************************************/
/* * * * *
#undef BIND
#define BIND			\
  {									\
    asm volatile("\n\
	movl	%esi,%ecx 			\n\
	xorl	$3,%ecx 			\n\
	movb	(%ecx),%cl 			\n\
	movb	%cl, %ch			\n\
	shrb $4,%ch		// ch = n1			\n\
			\n\
	andb $15,%cl		// cl = n2			\n\
	xorl	%eax,%eax					\n\
	movb	%cl,%al			\n\
	addb	%ch, %al			\n\
	notl	%eax			\n\
	shll	$16, %eax			\n\
			\n\
	leal	1(%esi),%edx 		// Get_Byte_PCMAC2			\n\
	xorl	$3,%edx 			\n\
	movzbl	(%edx),%edx 			\n\
			\n\
	movw	%dx,%ax			\n\
	shlw	$1,%ax			\n\
	pushl	%eax		//' eventual contents of ebx.			\n\
	movl	%ecx, %eax		// cl/ch now in al/ah			\n\
	leal 4(,%edx,4),%edx			\n\
	addl MachineState+4,%edx			\n\
//	movl %edx,-172(%ebp)		// edx is now ppvar			\n\
	movzbl %ah,%ecx			\n\
	decl %ecx			\n\
//	movl %ecx,-168(%ebp)			\n\
	js .Lbn1			\n\
.Lbn2:			\n\
//	movl -172(%ebp),%ecx			\n\
	leal -4(%edx),%edx			\n\
//	movl %edx,-172(%ebp)			\n\
	movl $0,(%edx)			\n\
//	decl -168(%ebp)			\n\
	decl %ecx			\n\
	jns .Lbn2			\n\
.Lbn1:			\n\
//	cmpl $0,-164(%ebp)			\n\
	cmpb $0, %al			\n\
	jne .Lbn3			\n\
	movl %ebx,(%edi)			\n\
	addl $4,%edi			\n\
	jmp .Lbnend			\n\
.Lbn3:			\n\
//	movl -172(%ebp),%ecx			\n\
	leal -4(%edx),%edx			\n\
//	movl %edx,-172(%ebp)			\n\
	movl %ebx,(%edx)			\n\
//	movl $1,-168(%ebp)			\n\
	movb $1, %ah			\n\
	jmp .Lbn5			\n\
.Lbn4:			\n\
//	movl -172(%ebp),%ecx			\n\
	leal -4(%edx),%edx			\n\
//	movl %edx,-172(%ebp)			\n\
	addl $-4,%edi			\n\
	movl (%edi),%ecx			\n\
	movl %ecx,(%edx)			\n\
//	incl -168(%ebp)			\n\
	incb	%ah			\n\
.Lbn5:			\n\
//	movl -164(%ebp),%ecx			\n\
//	cmpl -168(%ebp),%ecx			\n\
	cmpb %al, %ah			\n\
	jg .Lbn4			\n\
.Lbnend:			\n\
	popl %ebx");						\
  }
* * * * * * * * */

