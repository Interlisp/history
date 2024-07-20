/* %Z% %M% Version %I% (%G%). copyright envos & Fuji Xerox  */
static char *id = "%Z% %M%	%I% %G%";

/*************************************************************************/
/*	Copyright (C) 1987 by Fuji Xerox Co.,Ltd. All rights reserved.   */
/*************************************************************************/
/*                                                                       */
/*                      File Name : gcarrayops.c                       */
/*                      Written by Tomoru Teruuchi                       */
/*                                                                       */
/*************************************************************************/
/*                                                                       */
/*           Functions :                                                 */
/*                       LispPTR aref1(array, index);                    */
/*			 DLword find_symbol(char_base,offset,            */
/*						 length,hashtbl);        */
/*                       DLword get_package_atom(                        */
/*                               char_base,charlen,packname,             */
/*                                            packlen,externalp);        */
/*                                                                       */
/*************************************************************************/
/*           Description :                                               */
/*                                                                       */
/* The function "aref1" is the accessor of oned_array.                   */
/* The functions "find_symbol" and "get_package_atom" are implemented    */
/*     to access the atom through the package mechanism.                 */
/*									 */
/*************************************************************************/
/*                                                               \Tomtom */
/*************************************************************************/

/* THESE FUNCTIONS ARE NOW USED BY SYSOUT START AND URAID ONLY */

#include "lispemul.h"
#include "lisptypes.h"
#include "address.h"
#include "address68k.h"
#include "lispglobal.h"
#include "stack.h"
#include "cell.h"
#include "ifpage.h"
#include "gc.h"
#include "array.h"
#include "debug.h"
#include "lispmap.h"

/*** not currently used -FS
	#define min(a,b)		((a > b)?b:a)
	#define Trailer(ldatum,datum68)	(ldatum+2*(datum68->arlen - ARRAYBLOCKTRAILERCELLS))
	#define BucketIndex(n)		min(integerlength(n),MAXBUCKETINDEX)
	#define FreeBlockChainN(n)	((0xffffff & *FreeBlockBuckets_word)+2*BucketIndex(n))
 ***/

#define Rehash_factor(hash,tablelen)   \
           (((hash) % ((tablelen) - 2)) + 1)
#define Symbol_hash_reprobe(hash,rehashfactor,tablelen) \
               (((hash) + (rehashfactor)) % (tablelen))
#define Entry_hash(strlen,sxhash) \
           (((((((strlen)^(sxhash))^((sxhash) >> 8))  \
	       ^((sxhash) >> 16))^((sxhash) >> 19)) % 254) + 2)

struct hashtable {
  LispPTR      table;
  LispPTR      hash;
  LispPTR      size;
  LispPTR      free;
  LispPTR      deleted;
};

/* The end of macros & structure for medley version */

/*  ================================================================  */

LispPTR aref1(array, index)
  LispPTR array;
  int     index;
  {
    register LispPTR retval;
    register LispPTR base;
    register short   typenumber;
    register ONED_ARRAY  *actarray;

    actarray = (ONED_ARRAY *)Addr68k_from_LADDR(array);
    if (index >= actarray->TOTAL_SIZE)
      {
	printf("Invalid index in GC's AREF1:  0x%x\n", index);
	printf(" Array size limit:  0x%x\n", actarray->TOTAL_SIZE);
	printf(" Array ptr: 0x%x\n", (unsigned int)array);
	printf(" Array 68K ptr: 0x%x\n", (unsigned int) actarray);
	printf("base:     0x%x\n", actarray->BASE);
	printf("offset:   0x%x\n", actarray->OFFSET);
	printf("type #:   0x%x\n", actarray->TYPE_NUMBER);
	printf("fill ptr: 0x%x\n", actarray->FILL_POINTER);
	error("index out of range in GC's AREF1.");
      }
    index += actarray->OFFSET;
    typenumber = actarray->TYPE_NUMBER;
    base = actarray->BASE;
    switch(typenumber)
      {
	case  3: /* unsigned 8bits */
		/* the following code confuses the Apollo compiler;	*/
		/* its equivalent doesn't				*/
#ifndef APOLLO
		 retval = (GETBYTE(((char *)Addr68k_from_LADDR(base))
				 + index)) & 0x0ff;
#else
		{
		  register char *eightbitbase =
			(char *)Addr68k_from_LADDR(base);
		  retval = GETBYTE(eightbitbase + index) & 0xff;
		}
#endif
	        retval |= S_POSITIVE;
	        break;
	 case 4: /* unsigned 16bits */
		retval = (GETWORD(((DLword *)Addr68k_from_LADDR(base))
			 + index)) & 0x0ffff;
		retval |= S_POSITIVE;
		break;
	 case 38:
		retval = (*(((LispPTR *)Addr68k_from_LADDR(base))
			 + index));
		break;
	 default:  error("Not Implemented in gc's aref1 (other types)");
      };
    return(retval);
  }

/*  ================================================================  */

LispPTR find_symbol(char_base, offset, length, hashtbl)
  char *char_base;
  DLword offset;
  DLword length;
  LispPTR hashtbl;
  {
    DLword hashval, ehashval, h2, ehash, indexvar;
    int arraylen;
    struct hashtable *hashtbladdr;
    LispPTR vec,hash;
    struct arrayheader *vec68k;

    hashval = compute_hash(char_base,offset, length);
    ehashval = Entry_hash(length, hashval);
    hashtbladdr = (struct hashtable *)Addr68k_from_LADDR(hashtbl);
    vec = hashtbladdr->table;
    vec68k = (struct arrayheader *)Addr68k_from_LADDR(vec);
    hash = hashtbladdr->hash;
    arraylen = vec68k->totalsize;
    if(arraylen==0) return(0xffffffff);/*kludge TAKE*/
    h2 = Rehash_factor(hashval, arraylen);
    indexvar = (hashval % arraylen);

retry:
    while (ehashval != (ehash = aref1(hash, indexvar)))
    {
      if(ehash==NIL) return(0xffffffff);
      indexvar = Symbol_hash_reprobe(indexvar, h2, arraylen);
    }
    if ((indexvar&0xffff) != NIL)
      {
	LispPTR index;
	PNCell *pnptr;
	char *pname_base;

	index = aref1(vec, indexvar);
	pnptr = (PNCell *)GetPnameCell(index&0xffff);
	pname_base= (char *)Addr68k_from_LADDR(pnptr->pnamebase);
	if((length == GETBYTE(pname_base)) &&
	   (T == compare_chars((pname_base+1), char_base, length)))
	  {
	    return(index&0xffff);
	  }
	else
	  {
	    indexvar = Symbol_hash_reprobe(indexvar, h2, arraylen);
	    goto retry;
	  }
      }
    else return(0xffffffff); /* can't find */
  }


/*******************************************************************/
/*
	Func name : get_package_atom
			If find symbol, return index.
			Else return 0xFFFFFFFF
*/
/*******************************************************************/

LispPTR get_package_atom(char_base, charlen, packname, packlen, externalp)
  char *char_base;
  DLword charlen;
  char *packname;
  DLword packlen;
  int    externalp;
  {
    int packindex;
    PACKAGE *packaddr;
    LispPTR hashtbladdr;
    LispPTR index;
    extern LispPTR find_package_from_name();
/** for some NICKNAME compatibility */
    if (0 == strncmp(packname, "XCL", packlen))
      packindex = find_package_from_name("XEROX-COMMON-LISP",17);
    else if (0 == strncmp(packname, "SI", packlen))
      packindex = find_package_from_name("SYSTEM",6);
    else if (0 == strncmp(packname, "CL", packlen))
      packindex = find_package_from_name("LISP",4);
    else if (0 == strncmp(packname, "XCLC", packlen))
      packindex = find_package_from_name("COMPILER",8);

/**** else if (0 == strncmp(packname, "KEYWORD", packlen))
    packindex = 7;***/

    else packindex=find_package_from_name(packname, packlen);

    if (packindex <0)
      {
	printf("getting package index is failed \n");
	return(0xffffffff);
      }

/* if (packindex != 7)  Not necessary (Take)*/
    packaddr = (PACKAGE *)Addr68k_from_LADDR(
			  aref1(*Package_from_Index_word, packindex));
/* else packaddr = (PACKAGE *)Addr68k_from_LADDR(
			*Keyword_Package_word);	*/
/* hashtbladdr =	((externalp == T)?(packaddr->EXTERNAL_SYMBOLS):
			 (packaddr->INTERNAL_SYMBOLS));
 return( find_symbol(char_base, 0, charlen, hashtbladdr) );*/

    if ((index=find_symbol(char_base, 0, charlen,packaddr->EXTERNAL_SYMBOLS)) !=
				0xffffffff)
      return(index);
    else
      return(find_symbol(char_base, 0, charlen,packaddr->INTERNAL_SYMBOLS));

}
