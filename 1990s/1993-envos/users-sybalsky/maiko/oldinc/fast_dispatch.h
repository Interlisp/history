/* This is G-file @(#) fast_dispatch.h Version 2.6 (10/19/88). copyright Xerox & Fuji Xerox  */
/* 	fast_dispatch.h */
/* 	Bob Krivacic 3/2/88 */


/* 	These are the Macros Used to generate fast dispatch inline code. 
*/




#ifdef OPDISP
#ifdef mc68020
#undef nextop0
#undef nextop1
#undef nextop2
#undef nextop3
#undef nextop4
/* JRB - fast case is now nextop1 */
#define nextop0 { fast0_dispatcher(); goto nextopcode; }
#define nextop1 { fast1_dispatcher(); goto nextopcode; }
#define nextop2 { fast1_dispatcher2(); }
#define nextop3 { PCMACL += 2; nextop1; }
#define nextop4 { PCMACL += 3; nextop1; }
#endif

#ifdef I386
#undef nextop0
#undef nextop1
#undef nextop2
#undef nextop3
#undef nextop4
/* JRB - fast case is now nextop1 */
#define nextop0 { fast0_dispatcher(); goto nextopcode; }
#define nextop1 { fast1_dispatcher(); goto nextopcode; }
#define nextop2 { fast2_dispatcher(); }
#define nextop3 { PCMACL += 2; nextop1; }
#define nextop4 { PCMACL += 3; nextop1; }
#endif
#endif



#ifdef SPARCDISP
#undef nextop0
#undef nextop1
#undef nextop2
#undef nextop3
#undef nextop4
#define nextop0 { fast_dispatcher(table, Get_BYTE(PCMAC)); goto nextopcode; }
#define nextop_n(n) {							\
	PCMACL += n;							\
	nextop0; 							\
}
#define nextop1 { nextop_n(1); }
#define nextop2 { nextop_n(2); }
#define nextop3 { nextop_n(3); }
#define nextop4 { nextop_n(4); }
#endif







