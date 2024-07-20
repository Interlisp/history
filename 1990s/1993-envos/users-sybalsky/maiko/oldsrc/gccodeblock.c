/* @(#) gccode.c Version 1.5 (3/30/89). copyright Xerox & Fuji Xerox  */
static char *id = "@(#) gccode.c	1.5 3/30/89";
/************************************************************************/
/************************************************************************/
/* Copyright (C) 1987 by Fuji Xerox Co., Ltd. All rights reserved.	*/
/************************************************************************/
/* File Name : gccode.c						*/
/*									*/
/************************************************************************/
/*									*/
/* Creation Date : Sep-25-1987						*/
/* Written by Tomoru Teruuchi						*/
/* Edit by Larry Masinter						*/
/************************************************************************/
/*									*/
/* Functions :								*/
/* reclaimcodeblock();							*/
/*									*/
/*									*/
/*									*/
/************************************************************************/
/* \Tomtom								*/
/************************************************************************/

#include "lispemul.h"
#include "lisptypes.h"
#include "address.h"
#include "address68k.h"
#include "lispglobal.h"
#include "lispmap.h"
#include "stack.h"
#include "cell.h"
#include "ifpage.h"
#include "gc.h"
#include "array.h"

#define min(a,b)		((a > b)?b:a)


#define ENDOFX			0
#define GCONST			111

#define Reprobefn(bits, index)  (((bits^((bits) >> 8)) & min(63, index)) | 1)
#define Fn16bits(a, b)          ((a + b) & 0x0ffff)
#define Hashingbits(item)       (HILOC(item)^( \
	     ((LOLOC(item) & 0x1fff) << 3)^(LOLOC(item) >> 9)))
#define Getikvalue(base, index) \
        (*( LispPTR *)Addr68k_from_LADDR(base + (index << 1)))

#ifndef BYTESWAP
typedef
struct implicit_key_hash_table {
  LispPTR        base;
  unsigned       last_index : 16;
  unsigned       num_slots  : 16;
  unsigned       num_keys   : 16;
  unsigned       null_slots : 16;
  LispPTR        key_accessor;
} Ikhashtbl;
#else
typedef
struct implicit_key_hash_table {
  LispPTR        base;
  unsigned       num_slots  : 16;
  unsigned       last_index : 16;
  unsigned       null_slots : 16;
  unsigned       num_keys   : 16;
  LispPTR        key_accessor;
} Ikhashtbl;
#endif

unsigned int oplength[256] = {
0,0,0,0,0,1,2,2,
2,2,2,2,2,3,0,0,
0,2,0,0,1,1,0,2,
0,0,0,0,0,0,1,0,
0,0,0,1,2,9,0,0,
9,9,9,9,0,0,0,0,
1,1,1,1,0,0,0,0,
1,1,0,0,1,1,0,0,
0,0,0,0,0,0,0,1,
0,0,0,0,0,0,0,1,
0,0,0,0,0,0,0,1,
0,0,0,0,0,0,0,1,
2,0,1,1,0,0,0,2,
0,0,0,0,1,1,2,3,
9,0,0,0,0,0,0,0,
1,1,0,0,0,2,0,3,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
1,2,1,1,1,1,0,0,
0,0,0,0,0,0,0,0,
1,1,0,2,0,1,1,0,
1,1,2,9,0,1,1,2,
0,0,0,0,0,0,0,0,
0,0,0,0,0,1,1,0,
0,0,0,0,0,0,0,0,
0,0,0,0,1,1,0,0,
0,0,0,0,0,0,0,0,
1,0,1,1,0,0,0,0
};
typedef ByteCode *InstPtr;

map_code_pointers(codeblock, casep)
	LispPTR		codeblock;
	short		casep;
{
	InstPtr         codeptr;
	register unsigned int opnum;
	register unsigned int len;
	struct fnhead  *fnbase;
	fnbase = (struct fnhead *) Addr68k_from_LADDR(codeblock);
	codeptr = ((InstPtr) fnbase) + fnbase->startpc;
	while (T)
	 {
	   switch (opnum=Get_BYTE(codeptr))
	    {
	      case ENDOFX:	/* -X- */
		      return (NIL);
	      case GCONST:	/* GCONST */
		      {LispPTR reclaimed = (Get_BYTE(codeptr + 1) << 16) |
			       (Get_BYTE(codeptr + 2) << 8) |
			       Get_BYTE(codeptr + 3);
		      if (reclaimed != codeblock)
			      {htfind(reclaimed, casep);}
		      };
	    };
	  if ((len = oplength[opnum]) > 3)
	   {
	     char errtext[200];
	     sprintf(errtext,
		      "Unrecognized bytecode (0%o) in code block x%x,x%x; continue to use UFN length", opnum, (codeblock>>16)&0xFF, codeblock&0xFFFF);
	     error(errtext);
	     oplength[opnum] = len =(((UFN *)UFNTable) + (opnum))->byte_num;
	   }
	  codeptr += len + 1;
	};
}

/* JRB - These values are xpointers; their high bytes are not set and
	shouldn't be looked at */
#define getikkey(value) ((*(LispPTR *)Addr68k_from_LADDR(value)) & 0xffffff)

LispPTR remimplicitkeyhash(item, ik_hash_table)
LispPTR  item, ik_hash_table;
{Ikhashtbl *ik_htable;
 LispPTR   reprobe, bits, limits, index,
           base, value, key_accessor;
    ik_htable = (Ikhashtbl *)Addr68k_from_LADDR(ik_hash_table);
    bits   =  Hashingbits(item);
    limits = ik_htable->last_index;
    index  = (bits & limits);
    base   = ik_htable->base;
    value  = Getikvalue(base, index);
    if (value != *Deleted_Implicit_Hash_Slot_word)
      { if (value != NIL)
	  {if (item ==
	       getikkey(value))
	     {goto found;};
	 }
	else
	  return(NIL);
      };
    reprobe = Reprobefn(bits, limits);
 lp:
    index = Fn16bits(index, reprobe) & limits;
    value = Getikvalue(base, index);
    if (value != *Deleted_Implicit_Hash_Slot_word)
      { if (value != NIL)
	  {if (item ==
	       getikkey(value))
	     {goto found;};
	 }
	else
	  return(NIL);
      };
    goto lp;
 found:
    htfind(*Deleted_Implicit_Hash_Slot_word, ADDREF);
    htfind(Getikvalue(base, index), DELREF);
    Getikvalue(base, index) = *Deleted_Implicit_Hash_Slot_word;
      (ik_htable->num_keys)--;
    return (T);
}



LispPTR reclaimcodeblock(codebase)
LispPTR			codebase;
{struct fnhead		*fnbase;
   if ((*Closure_Cache_Enabled_word != NIL) &&
       (remimplicitkeyhash(codebase, *Closure_Cache_word) != NIL))
     { return(T);
     };
   fnbase = (struct fnhead *)Addr68k_from_LADDR(codebase);
   htfind((0x0ffffff & fnbase->framename), DELREF);
   if (fnbase->startpc != 0)
	map_code_pointers(codebase,DELREF);
   return(NIL);
}