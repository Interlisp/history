h52192s 00012/00001/00153d D 2.9 90/06/04 13:01:18 sybalsky 19 18c reformat, copyrightes 00003/00000/00151d D 2.8 89/04/28 16:56:17 sybalsky 18 17c es 00001/00001/00150d D 2.7 88/12/12 18:37:08 hayata 17 16c Add SCCS key ides 00000/00003/00151d D 2.6 88/12/12 18:35:12 hayata 16 15c To fix AR10945, obsolete extern declaration is removed. (AtomFrLst, Next_PnChar, PnChar_end)es 00001/00007/00153d D 2.5 88/10/10 14:13:16 krivacic 15 14c sun3/4 mergees 00003/00000/00157d D 2.4 88/10/05 17:02:35 krivacic 14 13c sun 3 / 4 mergees 00000/00000/00157d D 2.3 88/10/04 14:02:09 krivacic 13 12c srces 00006/00001/00151d D 2.2 88/05/31 13:10:53 masinter 12 11c Add interrupt flags to global declarationes 00000/00000/00152d D 2.1 88/05/17 09:18:22 hayata 11 10c Version up to 2.1es 00001/00000/00151d D 1.10 88/05/02 09:56:49 krivacic 10 9c add native closure hashes 00005/00011/00146d D 1.9 88/04/29 01:08:51 masinter 9 8c merge tomtom's changes for new GCes 00000/00001/00157d D 1.8 88/04/25 12:25:31 krivacic 8 7c remove Native_Hashes 00001/00003/00157d D 1.7 88/04/22 19:21:15 krivacic 7 6c inlinedefs re-arrangement & ni removales 00007/00000/00153d D 1.6 88/04/21 18:19:40 masinter 6 5c merge new GC codees 00005/00000/00148d D 1.5 88/04/05 11:14:10 jmturn 5 4c Added Unix Interface varses 00001/00000/00147d D 1.4 88/03/31 11:03:33 shimizu 4 3c Add NeedHardreturnCleanup_wordes 00005/00000/00142d D 1.3 88/03/23 18:02:54 shimizu 3 2c Add global vars for stackhandlinges 00001/00001/00141d D 1.2 88/03/13 13:22:43 hayata 2 1c Add SCCS key id (%Z%)es 00142/00000/00000d D 1.1 88/02/23 18:36:47 hayata 1 0c date and time created 88/02/23 18:36:47 by hayataeuUtTI 1D 2/* This is G-file %M% Version %I% (%G%). copyright Xerox & Fuji Xerox  */E 2I 2D 15/* This is G-file %Z% %M% Version %I% (%G%). copyright Xerox & Fuji Xerox  */E 15I 15D 17/* This is G-file @(#) lispglobal.h Version 2.4 (10/5/88). copyright Xerox & Fuji Xerox  */E 17I 17D 19/* This is G-file %Z% %M% Version %I% (%G%). copyright Xerox & Fuji Xerox  */E 19I 19/* This is G-file %Z% %M% Version %I% (%G%). copyright Venue & Fuji Xerox  */E 19E 17E 15E 2D 9E 9/* *	Copyright (C) 1987 by Fuji Xerox Co., Ltd. All rights reserved. *D 12 *	Auther	:	Takeshi ShimizuE 12I 12 *	Author	:	Takeshi ShimizuE 12 *			Hiroshi Hayata	D 9 * MERGED AT AISE 9 *//**********************************************************************//* 		File Name :	lispglobal.h		Global variables for LispSYSOUT  					Date :		December 16, 1986 					Edited by :	Takeshi Shimizu 					Changed : Jan 13 1987 Take.					Changed : Feb 16 1987 Take.					Changed : Mar 25 1987 Take.					Changed : Apr 24 1987 take					Changed : Jul 02 1987 take*//**********************************************************************/I 19/************************************************************************//*									*//*	Copyright 1989, 1990 Venue, Fuji Xerox Co., Ltd, Xerox Corp.	*//*									*//*	This file is work-product resulting from the Xerox/Venue	*//*	Agreement dated 18-August-1989 for support of Medley.		*//*									*//************************************************************************/E 19 extern  DLword *Atomspace; 		/* ATOMSPACE */ extern  DLword *Stackspace;		/* STACKSPACE*/ extern  DLword *Plistspace;		/* PLISTSPACE */ extern  DLword *DTDspace;		/* DTDSPACE */ extern  DLword *MDStypetbl;		/* MDSTT  */ extern  DLword *AtomHT;		/* AtomHashTable */ extern  DLword *Pnamespace;		/* PNSPACE */ extern  DLword *Defspace;		/* DEFSPACE */ extern  DLword *Valspace;		/* VALSPACE */ extern  DLword *Spospspace;		/* POSITIVE Smallp */ extern  DLword *Snegspace;		/* NEGATIVE Smallp */ /* For Virtual Mem Management */extern DLword *FPtoVP ;extern DLword *PAGEMap;extern DLword *PageMapTBL ;extern DLword *LockedPageTable;/* For Interface to Micro or Device */extern DLword *IOCBPage ;extern IOPAGE *IOPage ;extern IFPAGE *InterfacePage ;extern MISCSTATS *MiscStats ;/* UFN Tbl */extern DLword *UFNTable ;/* Internal Hash Table for GC */ extern  DLword *HTmain; extern  DLword *HToverflow; extern  DLword *HTbigcount; extern  DLword *HTcoll;/* DISPLAY */ extern DLword *DisplayRegion ;/* FLEX STORAGES */ extern  DLword *Arrayspace;  /* Start of ARRAYSPACE */ extern  DLword *MDS_space_bottom;  /* Start of MDS (pre -2) */ extern  DLword *PnCharspace ;	/* Space for PN char codes (Thin only) */D 15 extern  DLword *LastStackAddr ; /* Last Stack */E 15 extern  struct dtd *ListpDTD ;	/* DTD for LISTP chang. 25-mar-87 take */ extern  DLword *Next_Array ;	/* Next available ARRAY space */ extern  DLword *Next_MDSpage;	/* Next available MDS space */D 16 extern  DLword *PnChar_end ;	/* End of PN char codes space */ extern  DLword *Next_PnChar ;	/* Next available PnChar space */E 16   /* Pointers in Cell or any object means DLword offset from Lisp_world. So, 24 bit Lisp pointers can points 32Mbyte area. But, ATOMSPACE may be treated as special index space for LITATOM. In another way, it means that the Pointers points ATOMSPACE has no allocated memory, and Thease are used as index for access one of ATOM's prop. */  extern DLword *Lisp_world;  /* Lisp Start BASE  */ D 16 extern DLword AtomFrLst ;  /* keep number of how many atoms in this SYSOUT */E 16/******* CACHE 68k address for LISP SYSVAL *******/extern LispPTR *Next_MDSpage_word;extern LispPTR *Next_Array_word;extern LispPTR *MDS_free_page_word;extern LispPTR *Reclaim_cnt_word ;I 12D 15/* for interrupt handling */I 14#ifndef MVECE 14extern int Irq_Stk_Check, Irq_Stk_End;I 14#endifE 15E 14extern int FileIOFlag, TimerFlag;E 12/*** cache values for array reclaimer by Tomtom 30-Sep-1987 ***/extern LispPTR *GcDisabled_word;extern LispPTR *CdrCoding_word;extern LispPTR *FreeBlockBuckets_word;extern LispPTR *Array_Block_Checking_word;extern LispPTR *ArrayMerging_word;extern LispPTR *ArraySpace_word;extern LispPTR *ArraySpace2_word;extern LispPTR *ArrayFrLst_word;extern LispPTR *ArrayFrLst2_word;extern LispPTR *Hunk_word;extern LispPTR *System_Buffer_List_word;/*** The end of the addition of cache values for reclaimer by Tomtom ***/D 9/*** cashe values for code reclaimer by Tomtom 9-Oct-1987 ***/D 7extern LispPTR *OpCode_Array_word;extern LispPTR *OpCodes_word;extern LispPTR  Dopcode_index;E 7/*** The end of the addition of cache values for code reclaimer by Tomtom ***/E 9/*** cashe valuses for top level reclaimer Tomtom 15-Oct-1987 ***/extern LispPTR *GcMess_word;extern LispPTR *ReclaimMin_word;extern LispPTR *GcTime1_word;extern LispPTR *GcTime2_word;extern LispPTR *MaxTypeNumber_word;/*** The end of the addition of cashe values for the top level reclaimer ***/D 9/*** The addision of cashe values for GCClock 26-Oct-1987 by Tomtom ***/E 9I 6/*** The addition cache for closure-caching ***/I 9extern LispPTR *Package_from_Index_word;extern LispPTR *Package_from_Name_word;extern LispPTR *Keyword_Package_word;E 9extern LispPTR *Deleted_Implicit_Hash_Slot_word;extern LispPTR *Closure_Cache_Enabled_word;extern LispPTR *Closure_Cache_word;I 9extern LispPTR First_index;E 9/*** The end of cache value for closure-caching ***/E 6D 9extern LispPTR *RclkSecond_word;extern LispPTR *RclkMilliSecond_word;/*** The end of cashe values for GCClock ***/E 9/* CACHE values for 32Mb MDS/Array by Take */extern LispPTR *STORAGEFULLSTATE_word;extern LispPTR *STORAGEFULL_word;extern LispPTR *PENDINGINTERRUPT_word;extern LispPTR *LeastMDSPage_word;extern LispPTR *SecondMDSPage_word;extern LispPTR *SecondArrayPage_word;extern LispPTR *INTERRUPTSTATE_word;extern LispPTR *SYSTEMCACHEVARS_word;extern LispPTR *MACHINETYPE_word;extern LispPTR STORAGEFULLSTATE_index;/******* 7-Oct-87 take********/extern LispPTR *LASTVMEMFILEPAGE_word;extern LispPTR *VMEM_FULL_STATE_word;/* Array for N-tran */D 8extern CFuncPTR Native_Hash[];E 8I 7extern int native_load_address;I 10extern LispPTR native_closure_env;E 10E 7I 3/* Vars for Stack operations */extern LispPTR *STACKOVERFLOW_word;extern LispPTR *GuardStackAddr_word;extern LispPTR *LastStackAddr_word;I 4extern LispPTR *NeedHardreturnCleanup_word;I 5/* I/O Pipe for Unix Interface */extern int UnixPipeIn;extern int UnixPipeOut;extern int UnixPID;I 18/* Atom index for IL:\MVLIST, for the VALUES opcode */extern LispPTR MVLIST_index;E 18E 5E 4E 3E 1