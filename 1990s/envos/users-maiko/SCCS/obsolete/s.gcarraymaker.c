h31854s 00001/00001/00241d D 2.8 89/03/30 20:31:22 sybalsky 14 13c find_symbol was using strncmp, rather than comapre_chars -- can't do that with Lisp strings.es 00051/00054/00191d D 2.7 89/03/20 17:10:42 shih 13 12c wrong sense of strncmp, lots of cosmetic cleanupes 00130/00113/00115d D 2.6 89/03/17 13:34:04 sybalsky 12 11c Byte order dependencieses 00007/00000/00221d D 2.5 88/11/15 14:32:47 bane 11 10c Added an ifdef APOLLO to substitute code for brain-dead Apollo cces 00024/00002/00197d D 2.4 88/06/23 10:14:08 shimizu 10 9c Fix:find_symbol returns correct indexes 00025/00008/00174d D 2.3 88/06/09 19:54:13 shimizu 9 8c For URAID command,try to find symbol EXT & INTes 00005/00066/00177d D 2.2 88/06/02 13:36:01 masinter 8 7c remove unused elt function (use code in array.c instead)es 00000/00000/00243d D 2.1 88/05/17 09:24:22 hayata 7 6c Version up to 2.1es 00004/00006/00239d D 1.6 88/05/08 10:34:14 shimizu 6 5c for URaid modifyes 00024/00007/00221d D 1.5 88/05/05 10:54:02 shimizu 5 4c Fix getting package indexes 00001/00001/00227d D 1.4 88/04/29 02:06:41 masinter 4 3c add missing includees 00122/00015/00106d D 1.3 88/04/29 00:50:26 masinter 3 2c tomtom's Medley GC changes; defs for elt, aref1, find_symbol for initializationes 00002/00002/00119d D 1.2 88/03/13 14:48:11 hayata 2 1c Add SCCS key id (%Z%)es 00121/00000/00000d D 1.1 88/02/24 16:56:59 hayata 1 0c date and time created 88/02/24 16:56:59 by hayataeuUtTI 1D 2/* This is G-file %M% Version %I% (%G%). copyright Xerox & Fuji Xerox  */static char *id = "%M%	%I% %G%";E 2I 2D 13/* This is G-file %Z% %M% Version %I% (%G%). copyright Xerox & Fuji Xerox  */E 13I 13/* %Z% %M% Version %I% (%G%). copyright envos & Fuji Xerox  */E 13static char *id = "%Z% %M%	%I% %G%";I 13E 13E 2D 3E 3/*************************************************************************/D 13/*************************************************************************/E 13/*	Copyright (C) 1987 by Fuji Xerox Co.,Ltd. All rights reserved.   *//*************************************************************************//*                                                                       */D 13/*                       File Name : gcarraymaker.c                      *//*                                                                       *//*************************************************************************//*                                                                       *//*                      Creation Date : Oct-9-1987                       */E 13I 13/*                      File Name : gcarraymaker.c                       */E 13/*                      Written by Tomoru Teruuchi                       *//*                                                                       *//*************************************************************************//*                                                                       *//*           Functions :                                                 */D 8/*                       LispPTR elt(ary, num);                          */E 8I 3/*                       LispPTR aref1(array, index);                    */D 13/*                   	 DLword find_symbol(char_base,offset             *//*			 			 ,length,hashtbl);       */E 13I 13/*			 DLword find_symbol(char_base,offset,            *//*						 length,hashtbl);        */E 13/*                       DLword get_package_atom(                        *//*                               char_base,charlen,packname,             *//*                                            packlen,externalp);        */E 3/*                                                                       */D 3/*                   		                                         *//*                                                                       *//*                                                                       *//*                                                                       *//*                                                                       */E 3/*************************************************************************/D 8/*           Descreption :                                               */E 8I 8/*           Description :                                               */E 8/*                                                                       */D 8/*  The function "elt" is an accessor of the array type data.            *//*  Its arguments are as following :					 *//*  	ary : this is the Lisp pointer of the target array		 *//*      num : this is the index number of the target instance in array   *//*  And, the return value is the Lisp pointer of the target instance of  *//*  the specified array.						 *//*  									 *//*  Caution :								 *//* 	This function is implemented in order to implement the Garbage   *//*      Collection by C. Therefore, don't use this function for other	 *//*      meaning. There is no garantee in so usage.(Especially, there is  *//*      explict pitholl that the floating-point instance is not 	 */D 3/*	implemented.)							 */E 3I 3/*	implemented.)                                                    */ /*               							 */E 8/* The function "aref1" is the accessor of oned_array.                   *//* The functions "find_symbol" and "get_package_atom" are implemented    */D 13/*     for  the method to access the atom through the package mechanisum.*/E 13I 13/*     to access the atom through the package mechanism.                 */E 13E 3/*									 *//*************************************************************************//*                                                               \Tomtom *//*************************************************************************/I 8/* THESE FUNCTIONS ARE NOW USED BY SYSOUT START AND URAID ONLY */D 13E 13E 8#include "lispemul.h"#include "lisptypes.h"#include "address.h"#include "address68k.h"#include "lispglobal.h"#include "stack.h"#include "cell.h"#include "ifpage.h"#include "gc.h"#include "array.h"I 3#include "debug.h"E 3D 4E 4I 4#include "lispmap.h"E 4I 13/*** not currently used -FS	#define min(a,b)		((a > b)?b:a)	#define Trailer(ldatum,datum68)	(ldatum+2*(datum68->arlen - ARRAYBLOCKTRAILERCELLS))	#define BucketIndex(n)		min(integerlength(n),MAXBUCKETINDEX)	#define FreeBlockChainN(n)	((0xffffff & *FreeBlockBuckets_word)+2*BucketIndex(n)) ***/E 13D 3#define GetSegnuminColl(entry1) ((entry1 & 0x01fe) >> 1)#define GetLinkptr(entry)	(entry & 0x0fffe)#define GetCountinColl(entry1)  ((entry1 & 0x0fc00) >> 10)#define Oddp(num) (((num % 2) != 0)?1:0)#define STK_HI		1	/* This value also */#define WORDSPERCELL	2#define PADDING	4#define Boundp(frame_field)	((frame_field == 0)?1:0)E 3D 13#define min(a,b)		((a > b)?b:a)#define Trailer(ldatum,datum68)	(ldatum+2*(datum68->arlen - ARRAYBLOCKTRAILERCELLS))#define BucketIndex(n)		min(integerlength(n),MAXBUCKETINDEX)#define FreeBlockChainN(n)	((0xffffff & *FreeBlockBuckets_word)+2*BucketIndex(n))I 3D 8/* The following macros are for Medley version  Apr-28,1988 Tomtom*/E 8E 3E 13I 3#define Rehash_factor(hash,tablelen)   \           (((hash) % ((tablelen) - 2)) + 1)#define Symbol_hash_reprobe(hash,rehashfactor,tablelen) \               (((hash) + (rehashfactor)) % (tablelen))#define Entry_hash(strlen,sxhash) \           (((((((strlen)^(sxhash))^((sxhash) >> 8))  \	       ^((sxhash) >> 16))^((sxhash) >> 19)) % 254) + 2)struct hashtable {  LispPTR      table;  LispPTR      hash;  LispPTR      size;  LispPTR      free;  LispPTR      deleted;};/* The end of macros & structure for medley version */D 8E 3/****************************************************************************//*									    *//*	The following procedure "elt" is the accessor to the indecated      *//*	 array. (This procedure will make the same behavior as the Lisp     *//*	 Function "ELT".						    *//*									    *//****************************************************************************/LispPTR elt(ary, num)LispPTR		ary;DLword		num;{Arrayp		*abase; LispPTR		base, retval; LispPTR		*rettmp; DLword			no;   abase = (Arrayp *)Addr68k_from_LADDR(ary);   base  = abase->base;   no    = num - abase->orig;   if ((no < 0) || (no >= abase->length))	error("Illegal ARG.\n");   no = no + abase->offst;   switch(abase->typ)	{case ST_PTR:	 case ST_PTR2:	   {rettmp = (LispPTR *)Addr68k_from_LADDR(base + 2*no);	    retval = *rettmp;	    break;};	 case ST_INT32:	   {base = base + 2*no;	    retval = VAG2(*(DLword *)Addr68k_from_LADDR(base),			  *(DLword *)Addr68k_from_LADDR(base+1));	    break;};	 case ST_POS16:	   {retval = 0x00ffff & (*(DLword *)Addr68k_from_LADDR(base+no));	    break;	   };	 case ST_BIT:	   {retval = 0x0ff & ((*(DLword *)Addr68k_from_LADDR(base+(no >> 8)))						>> (15 - (no % 16)));	    break;	   };	 case ST_FLOAT:	   error("Not Implemented type in ELT.\n");	 default:	   error("Illegal ARG.\n");	};   return(retval);}E 8I 3I 13/*  ================================================================  */E 13LispPTR aref1(array, index)D 12LispPTR array;int     index;{register LispPTR retval; register LispPTR base; register short   typenumber; register DLword  *actarray; actarray = Addr68k_from_LADDR(array); if (index >= *((DLword *)(actarray + 5)))   error("Invalid index in gc's aref1"); index += *((DLword *)(actarray + 3)); typenumber = 0x0ffff & *((DLword *)(actarray + 2)); base = *((LispPTR *)(actarray)); switch(typenumber) { case  3: /* unsigned 8bits */I 11 /* the following code confuses the Apollo compiler; its equivalent doesn't */E 12I 12  LispPTR array;  int     index;  {    register LispPTR retval;    register LispPTR base;    register short   typenumber;    register ONED_ARRAY  *actarray;I 13E 13    actarray = (ONED_ARRAY *)Addr68k_from_LADDR(array);    if (index >= actarray->TOTAL_SIZE)      {	printf("Invalid index in GC's AREF1:  0x%x\n", index);	printf(" Array size limit:  0x%x\n", actarray->TOTAL_SIZE);	printf(" Array ptr: 0x%x\n", (unsigned int)array);	printf(" Array 68K ptr: 0x%x\n", (unsigned int) actarray);	printf("base:     0x%x\n", actarray->BASE);	printf("offset:   0x%x\n", actarray->OFFSET);	printf("type #:   0x%x\n", actarray->TYPE_NUMBER);	printf("fill ptr: 0x%x\n", actarray->FILL_POINTER);	error("index out of range in GC's AREF1.");      }    index += actarray->OFFSET;    typenumber = actarray->TYPE_NUMBER;    base = actarray->BASE;    switch(typenumber)      {	case  3: /* unsigned 8bits */D 13 		/* the following code confuses the Apollo compiler;	*/E 13I 13		/* the following code confuses the Apollo compiler;	*/E 13		/* its equivalent doesn't				*/E 12#ifndef APOLLOE 11D 12   retval = (*(((char *)Addr68k_from_LADDR(base))		 + index)) & 0x0ff;E 12I 12		 retval = (GETBYTE(((char *)Addr68k_from_LADDR(base))				 + index)) & 0x0ff;E 12I 11#elseD 12	{register char *eightbitbase = (char *)Addr68k_from_LADDR(base);	 retval = *(eightbitbase + index) & 0xff;	}E 12I 12		{		  register char *eightbitbase =			(char *)Addr68k_from_LADDR(base);		  retval = GETBYTE(eightbitbase + index) & 0xff;		}E 12#endifE 11D 12      retval |= S_POSITIVE;      break; case 4: /* unsigned 16bits */   retval = (*(((DLword *)Addr68k_from_LADDR(base))		 + index)) & 0x0ffff;      retval |= S_POSITIVE;      break; case 38:D 9   retval = (*(((int *)Addr68k_from_LADDR(base))E 9I 9   retval = (*(((LispPTR *)Addr68k_from_LADDR(base))E 9		 + index));      break; default :   error("Not Implemented in gc's aref1 (other types)"); }; return(retval);}E 12I 12D 13 	        retval |= S_POSITIVE; 	        break;E 13I 13	        retval |= S_POSITIVE;	        break;E 13	 case 4: /* unsigned 16bits */D 13		   retval = (GETWORD(((DLword *)Addr68k_from_LADDR(base))E 13I 13		retval = (GETWORD(((DLword *)Addr68k_from_LADDR(base))E 13			 + index)) & 0x0ffff;D 13 	 	    retval |= S_POSITIVE; 		     break;E 13I 13		retval |= S_POSITIVE;		break;E 13	 case 38:D 13		   retval = (*(((LispPTR *)Addr68k_from_LADDR(base))E 13I 13		retval = (*(((LispPTR *)Addr68k_from_LADDR(base))E 13			 + index));D 13		      break;E 13I 13		break;E 13	 default:  error("Not Implemented in gc's aref1 (other types)");      };    return(retval);  }E 12I 13/*  ================================================================  */E 13D 6DLword find_symbol(char_base, offset, length, hashtbl)E 6I 6D 9int find_symbol(char_base, offset, length, hashtbl)E 9I 9LispPTR find_symbol(char_base, offset, length, hashtbl)E 9E 6D 12char *char_base;DLword offset;DLword length;LispPTR hashtbl;{DLword hashval, ehashval, h2, ehash, indexvar; int arraylen; struct hashtable *hashtbladdr; LispPTR vec,hash; struct arrayheader *vec68k; hashval = compute_hash(char_base,offset, length); ehashval = Entry_hash(length, hashval); hashtbladdr = (struct hashtable *)Addr68k_from_LADDR(hashtbl); vec = hashtbladdr->table; vec68k = (struct arrayheader *)Addr68k_from_LADDR(vec); hash = hashtbladdr->hash; arraylen = vec68k->totalsize;I 10 if(arraylen==0) return(0xffffffff);/*kludge TAKE*/E 10 h2 = Rehash_factor(hashval, arraylen); indexvar = (hashval % arraylen);E 12I 12  char *char_base;  DLword offset;  DLword length;  LispPTR hashtbl;  {    DLword hashval, ehashval, h2, ehash, indexvar;    int arraylen;    struct hashtable *hashtbladdr;    LispPTR vec,hash;    struct arrayheader *vec68k;I 13E 13    hashval = compute_hash(char_base,offset, length);    ehashval = Entry_hash(length, hashval);    hashtbladdr = (struct hashtable *)Addr68k_from_LADDR(hashtbl);    vec = hashtbladdr->table;    vec68k = (struct arrayheader *)Addr68k_from_LADDR(vec);    hash = hashtbladdr->hash;    arraylen = vec68k->totalsize;    if(arraylen==0) return(0xffffffff);/*kludge TAKE*/    h2 = Rehash_factor(hashval, arraylen);    indexvar = (hashval % arraylen);E 12I 10retry:E 10D 12 while (ehashval != (ehash = aref1(hash,indexvar)))I 9 {   if(ehash==NIL) return(0xffffffff);E 9   indexvar = Symbol_hash_reprobe(indexvar, h2, arraylen);I 9 }E 9D 10 if (indexvar != NIL)   return(aref1(vec,indexvar));E 10I 10 if ((indexvar&0xffff) != NIL){   LispPTR index;     PNCell *pnptr ;   char *pname_base ;   index=aref1(vec,indexvar);   pnptr = (PNCell *)GetPnameCell(index&0xffff);   pname_base= (char *)Addr68k_from_LADDR(pnptr->pnamebase) ;   if((length == *pname_base) && 	(compare_chars(char_base,(pname_base+1),length)))   {    	 return(index&0xffff);   }   else     { 	indexvar = Symbol_hash_reprobe(indexvar, h2, arraylen);	goto retry;E 12I 12D 13    while (ehashval != (ehash = aref1(hash,indexvar)))E 13I 13    while (ehashval != (ehash = aref1(hash, indexvar)))E 13    {      if(ehash==NIL) return(0xffffffff);      indexvar = Symbol_hash_reprobe(indexvar, h2, arraylen);E 12    }I 12    if ((indexvar&0xffff) != NIL)      {D 13	LispPTR index;  	PNCell *pnptr ;	char *pname_base ;E 13I 13	LispPTR index;	PNCell *pnptr;	char *pname_base;E 13E 12D 12 }E 10 else D 6   return(NIL);E 6I 6D 9   return(-1); /* can't find */E 9I 9   return(0xffffffff); /* can't find */E 9E 6}E 12I 12D 13	index=aref1(vec,indexvar); 	 pnptr = (PNCell *)GetPnameCell(index&0xffff); 	 pname_base= (char *)Addr68k_from_LADDR(pnptr->pnamebase) ;	if((length == GETBYTE(pname_base)) && 	   (compare_chars((pname_base+1),char_base,length)))	  {    E 13I 13	index = aref1(vec, indexvar);	pnptr = (PNCell *)GetPnameCell(index&0xffff);	pname_base= (char *)Addr68k_from_LADDR(pnptr->pnamebase);	if((length == GETBYTE(pname_base)) &&D 14	   (0 == strncmp((pname_base+1), char_base, length)))E 14I 14	   (T == compare_chars((pname_base+1), char_base, length)))E 14	  {E 13	    return(index&0xffff);	  }D 13	else 	  { E 13I 13	else	  {E 13	    indexvar = Symbol_hash_reprobe(indexvar, h2, arraylen);	    goto retry;	  }D 13E 13      }    else return(0xffffffff); /* can't find */  }E 12I 9/*******************************************************************//*	Func name : get_package_atomD 13			If find symbol ,retrun index.			Else retrun 0xFFFFFFFFE 13I 13			If find symbol, return index.			Else return 0xFFFFFFFFE 13*//*******************************************************************/E 9D 6DLword get_package_atom(char_base, charlen, packname, packlen, externalp)E 6I 6D 9int get_package_atom(char_base, charlen, packname, packlen, externalp)E 9I 9LispPTR get_package_atom(char_base, charlen, packname, packlen, externalp)E 9E 6D 12char *char_base;DLword charlen;char *packname;DLword packlen;int    externalp; {int packindex;D 6 DLword atmindex;E 6 PACKAGE *packaddr; LispPTR hashtbladdr;I 5D 9 extern int find_package_from_name();E 9I 9 LispPTR index; extern LispPTR find_package_from_name();E 9E 12I 12  char *char_base;  DLword charlen;  char *packname;  DLword packlen;D 13  int    externalp; E 13I 13  int    externalp;E 13  {    int packindex;    PACKAGE *packaddr;    LispPTR hashtbladdr;    LispPTR index;    extern LispPTR find_package_from_name();E 12/** for some NICKNAME compatibility */E 5D 12 if (compare_chars(packname, "XCL", packlen) == T)D 5   packindex = 4;E 5I 5   packindex = find_package_from_name("XEROX-COMMON-LISP",17); E 5 else if (compare_chars(packname, "SI", packlen) == T)D 5   packindex = 5; else if (compare_chars(packname, "KEYWORD", packlen) == T)   packindex = 7; if (packindex != 7)E 5I 5   packindex = find_package_from_name("SYSTEM",6); else if (compare_chars(packname, "CL", packlen) == T)   packindex = find_package_from_name("LISP",4); else if (compare_chars(packname, "XCLC", packlen) == T)   packindex = find_package_from_name("COMPILER",8);E 12I 12D 13    if (strncmp(packname, "XCL", packlen))      packindex = find_package_from_name("XEROX-COMMON-LISP",17);     else if (strncmp(packname, "SI", packlen))E 13I 13    if (0 == strncmp(packname, "XCL", packlen))      packindex = find_package_from_name("XEROX-COMMON-LISP",17);    else if (0 == strncmp(packname, "SI", packlen))E 13      packindex = find_package_from_name("SYSTEM",6);D 13    else if (strncmp(packname, "CL", packlen))E 13I 13    else if (0 == strncmp(packname, "CL", packlen))E 13      packindex = find_package_from_name("LISP",4);D 13    else if (strncmp(packname, "XCLC", packlen))E 13I 13    else if (0 == strncmp(packname, "XCLC", packlen))E 13      packindex = find_package_from_name("COMPILER",8);E 12D 12/**** else if (compare_chars(packname, "KEYWORD", packlen) == T)   packindex = 7;***/E 12I 12D 13/**** else if (strncmp(packname, "KEYWORD", packlen))E 13I 13/**** else if (0 == strncmp(packname, "KEYWORD", packlen))E 13    packindex = 7;***/E 12D 12 else   packindex=find_package_from_name(packname,packlen);E 12I 12D 13    else packindex=find_package_from_name(packname,packlen);E 13I 13    else packindex=find_package_from_name(packname, packlen);E 13E 12D 12if (packindex <0) {	 printf("getting package index is failed \n");D 9	 return(0xffff);E 9I 9	 return(0xffffffff);E 9 }E 12I 12    if (packindex <0)      {	printf("getting package index is failed \n");	return(0xffffffff);      }E 12/* if (packindex != 7)  Not necessary (Take)*/E 5D 12   packaddr = (PACKAGE *)Addr68k_from_LADDR(E 12I 12    packaddr = (PACKAGE *)Addr68k_from_LADDR(E 12			  aref1(*Package_from_Index_word, packindex));D 5 else packaddr = (PACKAGE *)Addr68k_from_LADDR(			*Keyword_Package_word);		       E 5I 5/* else packaddr = (PACKAGE *)Addr68k_from_LADDR(D 13			*Keyword_Package_word);	*/	       E 5D 9 hashtbladdr = 	((externalp == T)?(packaddr->EXTERNAL_SYMBOLS):E 9I 9/* hashtbladdr = 	((externalp == T)?(packaddr->EXTERNAL_SYMBOLS):E 13I 13			*Keyword_Package_word);	*//* hashtbladdr =	((externalp == T)?(packaddr->EXTERNAL_SYMBOLS):E 13E 9			 (packaddr->INTERNAL_SYMBOLS));D 6 atmindex = find_symbol(char_base, 0, charlen, hashtbladdr); return(atmindex);E 6I 6D 9 return( find_symbol(char_base, 0, charlen, hashtbladdr) );E 9I 9 return( find_symbol(char_base, 0, charlen, hashtbladdr) );*/D 12 if ((index=find_symbol(char_base, 0, charlen,packaddr->EXTERNAL_SYMBOLS)) != E 12I 12D 13    if ((index=find_symbol(char_base, 0, charlen,packaddr->EXTERNAL_SYMBOLS)) != E 13I 13    if ((index=find_symbol(char_base, 0, charlen,packaddr->EXTERNAL_SYMBOLS)) !=E 13E 12				0xffffffff)D 12	return(index); else	return(find_symbol(char_base, 0, charlen,packaddr->INTERNAL_SYMBOLS));E 12I 12      return(index);    else      return(find_symbol(char_base, 0, charlen,packaddr->INTERNAL_SYMBOLS));E 12I 10E 10E 9E 6}D 13E 13E 3E 1