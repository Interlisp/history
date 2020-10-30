/* This is G-file @(#) Ctest.c Version 2.16 (7/27/88). copyright Xerox & Fuji Xerox  */static char *id = "@(#) Ctest.c	2.16 7/27/88";/* *	Copyright (C) 1987 by Fuji Xerox Co., Ltd. All rights reserved. *//* *	Ctest.c *	This file includes main() * * */#include "lispemul.h"#include "emulglobal.h"#include "address.h"#include "address68k.h"#include "stack.h"#include "return.h"#include "lispglobal.h"#include "lispmap.h"#include "ifpage.h"#include "iopage.h"#include "debug.h"#include        <sys/time.h>#include 	<setjmp.h>#include	<sys/types.h>#include	<net/nit.h>	/* needed for Ethernet stuff below *//* For Time Out Service */#include <signal.h>#include <errno.h>#include <stdio.h>#include        <sys/file.h>int	timeout_error();DLword	*Lisp_world;		/* lispworld *//********** 68k address for Lisp Space **********/DLword	*Atomspace;DLword	*Stackspace;DLword	*Plistspace;DLword	*DTDspace;DLword	*MDStypetbl;DLword	*AtomHT;DLword	*Pnamespace;DLword	*Defspace;DLword	*Valspace;DLword	*Spospspace;DLword	*Snegspace;/********** For Virtual Memory Management **********/DLword	*FPtoVP;DLword	*PAGEMap;DLword	*PageMapTBL;DLword	*LockedPageTable;/********** For Interface to LispMicro/Device **********/DLword	*IOCBPage;IOPAGE	*IOPage;IFPAGE	*InterfacePage;MISCSTATS	*MiscStats;/********** UFN Table **********/DLword	*UFNTable;/********** Tables for GC **********/DLword	*HTmain;DLword	*HToverflow;DLword	*HTbigcount;DLword	*HTcoll;/********** Display **********/DLword	*DisplayRegion;int DisplayInitialized = NIL;int loop; /* for contextsw loop count OBSOLATE */DLword	*Arrayspace;DLword	*MDS_space_bottom;DLword	*PnCharspace;struct dtd	*ListpDTD;/********** Display **********/extern int Intrdisable;/********** For Lisp Emulator **********/LispPTR	TopOfStack;DLword	*CurrentStackPTR;/*Change to MachineState and MState:	DLword	*IVar;	DLword	*PVar; */struct	state	MachineState;struct	state	*MState;ByteCode	*PC;/* struct frameex1	*CurrentFX; */struct fnhead	*FuncObj;DLword *EndSTKP ;DLword *LastStackAddr;/**********************************//*** Share val with LISP code ******/DLword *MDS_free_page;DLword *Next_MDSpage;DLword *Next_Array;/*******************************************//** CACHE LISP SYSVAL ***/LispPTR *Next_MDSpage_word;LispPTR *Next_Array_word;LispPTR *MDS_free_page_word;LispPTR *Reclaim_cnt_word ;/*** Cache Values for reclaimer by Tomtom 30-Sep-1987 ***/LispPTR *GcDisabled_word;LispPTR *CdrCoding_word;LispPTR *FreeBlockBuckets_word;LispPTR *Array_Block_Checking_word;LispPTR *ArrayMerging_word;LispPTR *ArraySpace_word;LispPTR *ArraySpace2_word;LispPTR *ArrayFrLst_word;LispPTR *ArrayFrLst2_word;LispPTR *Hunk_word;LispPTR *System_Buffer_List_word;/*** The end of the addition of cache values on reclaimer ***//*** UNKNOWN if NEEDED ??? ***/LispPTR *RclkMilliSecond_word;LispPTR *RclkSecond_word;/*** cache values for the top level reclaimer's implementation ***/LispPTR *GcMess_word;LispPTR *ReclaimMin_word;LispPTR *GcTime1_word;LispPTR *GcTime2_word;LispPTR *MaxTypeNumber_word;/*** The end of the addition of cache values for top reclaimer by Tomtom						15-Oct-1987             ***//*  Pointers for closure caching */LispPTR *Package_from_Index_word;             /*** added Apr-28,88 Tomtom ***/LispPTR *Package_from_Name_word;              /*** added Apr-28,88 Tomtom ***/LispPTR *Keyword_Package_word;                /*** added Apr-28,88 Tomtom ***/LispPTR *Closure_Cache_Enabled_word;LispPTR *Closure_Cache_word;LispPTR *Deleted_Implicit_Hash_Slot_word;LispPTR First_index;                         /*** added Apr-28,88 Tomtom ***/  /*** The end of Pointers for closure caching ***/ /* CACHE values for 32Mb MDS/Array by Take */LispPTR *STORAGEFULLSTATE_word;LispPTR *STORAGEFULL_word;LispPTR *PENDINGINTERRUPT_word;LispPTR *LeastMDSPage_word;LispPTR *SecondMDSPage_word;LispPTR *SecondArrayPage_word;LispPTR *INTERRUPTSTATE_word;LispPTR *SYSTEMCACHEVARS_word;LispPTR *MACHINETYPE_word;LispPTR STORAGEFULLSTATE_index;/******* 7-Oct-87 take********/LispPTR *LASTVMEMFILEPAGE_word;LispPTR *VMEM_FULL_STATE_word ;/** Array for N-tran **/int native_load_address;LispPTR native_closure_env = NOBIND_PTR;/** Pipes for Unix Interface **/int UnixPipeIn;int UnixPipeOut;int UnixPID;/*** STACK handle staff(Takeshi) **/LispPTR *STACKOVERFLOW_word;LispPTR *GuardStackAddr_word;LispPTR *LastStackAddr_word;LispPTR *NeedHardreturnCleanup_word;/*** Ethernet stuff (JRB) **/extern int ether_fd;extern u_char ether_host[6];extern struct sockaddr_nit snit;main(argc, argv)int	argc ;char	**argv ;{	int i;	int sysout_size = 32;	int please_fork = 1;	extern int TIMER_INTERVAL;	char *keystring, sysout_name[1024], *envname, *getenv();#ifdef PROFILE	moncontrol(0); /* initially stop sampling */#endif PROFILE/* Sysout is found as follows:	If the first argument doesn't begin with '-', assume it's the sysout	Look at the environment variable LDESOURCESYSOUT if that fails	Look for ~/lisp.virtualmem if that fails	Barf and print the command line if tha fails*/	i=1;	if(argc > 1 && argv[1][0] != '-') {		strcpy(sysout_name, argv[1]);		i++;	} else if((envname = getenv("LDESOURCESYSOUT")) != NULL)		strcpy(sysout_name, envname);	else if(!makepathname("~/lisp.virtualmem", sysout_name)		 || access(sysout_name, R_OK)) {			fprintf(stderr, "Coudn't find a sysout to run; \either setenv LDESOURCESYSOUT or do:\n");			fprintf(stderr, "lisp sysout [-k access-key] [-E <ethernet-info>]\n" );			exit(1);		}/* OK, sysout name is now in sysout_name, and i is moved past a supplied name */	for ( ; i < argc; i += 1 ) { /* step by 1 in case of typo */	/* -t and -m are undocumented and somewhat dangerous... */	    if (! strcmp(argv[i], "-t")) {	/**** timer interval	****/			if(argc > ++i) TIMER_INTERVAL = atoi(argv[i]);			else fprintf(stderr, "Missing argument after -t\n");		}        if (! strcmp(argv[i], "-m")) {	/**** sysout size	****/			if(argc > ++i) sysout_size = atoi(argv[i]);			else fprintf(stderr, "Missing argument after -m\n");		}        if (! strcmp(argv[i], "-NF")) {	/****  Don't fork (for dbxing)	****/			please_fork = 0;		}        if (! strcmp(argv[i], "-k")) {	/**** security key	****/			if(argc > ++i) keystring = argv[i];			else fprintf(stderr, "Missing argument after -k\n");		}	    if (! strcmp(argv[i], "-E")) {	/**** ethernet info	****/			int b0, b1, b2, b3, b4, b5;			if(argc > ++i && sscanf(argv[i],"%d:%x:%x:%x:%x:%x:%x:%s",&ether_fd,				&b0, &b1, &b2, &b3, &b4, &b5, snit.snit_ifname) == 8) {				ether_host[0] = b0; ether_host[1] = b1;				ether_host[2] = b2; ether_host[3] = b3;				ether_host[4] = b4; ether_host[5] = b5;			} else {				fprintf(stderr, "Missing or bogus -E argument\n");				ether_fd = -1;			}			}	}#ifdef UNPROTECTED	fprintf(stderr, "Copy protection disabled.", keystring);#else	if ( keytester(keystring) ) {	    fprintf (stderr, "Sorry, invalid or expired access key.\n" );	    exit();	    }#endif   	init_ether();			/* modified by kiuchi Nov. 4 */	/* Fork Unix Interface subprocess before we create anything big */	/* interrupts need to be blocked here so subprocess won't see them */	/* This should actually live in the kickstarter... */	int_block();#ifndef NOFORK	if(please_fork) fork_Unix();#endif	/* load sysout to VM space */	sysout_loader(sysout_name, sysout_size);	/* built up map */	build_lisp_map();	/* initialize IFPAGE */	init_ifpage(sysout_size);	/* initialize IOPAGE */	init_iopage();	/* initialize MISCSTATS */	init_miscstats();	/* device initialize */	/* init_display(); */		/* modified by osamu Sep. 3 */	set_cursor();			/* modified by osamu Feb. 10 */	/* Get OS message to ~/lisp.log and print the message to prompt window */        mess_init();	init_keyboard();	rs232c_init();	tty_init();   	/* Set signal for "file access timeout */	if( signal(SIGALRM, timeout_error) == BADSIG){		err_mess("signal", errno);		fprintf(stderr, "Time Out Service does not work!!\n");	}		/* now start up lisp */	start_lisp();}start_lisp(){ register int time; DLword *tmp; LispPTR func; DLword *freeptr,*next68k; MState = &MachineState; TopOfStack=0;  MState->pvar=(DLword *)Addr68k_from_LADDR(STK_OFFSET | InterfacePage->currentfxp) + FRAMESIZE;freeptr = next68k = Addr68k_from_LADDR(STK_OFFSET | CURRENTFX->nextblock);RTNI:	if (*next68k != STK_FSB_WORD)		error("initial: MP9316");while(*freeptr==STK_FSB_WORD)  EndSTKP = freeptr = freeptr + *(freeptr+1);  CurrentStackPTR =next68k -2;	  FastRetCALL;  LastStackAddr=(DLword *)Addr68k_from_LADDR(STK_OFFSET | 0xffff);/* JRB - The interrupt intitialization must be done right before entering   the bytecode dispatch loop; interrupts get unblocked here */	int_init();	dispatch();}/*****************************************************************timeout_error	Error handling routine for SIGALRM.	When TIMEOUT spend TIMEOUT_TIME (10 sec), this rouitne is called.*****************************************************************/jmp_buf	jmpbuf;timeout_error(){	fprintf(stderr, "File access timed out.\n");	longjmp(jmpbuf, 1);}