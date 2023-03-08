/* %Z% %M% Version %I% (%G%). copyright venue & Fuji Xerox  */
static char *id = "%Z% %M%	%I% %G%	(venue & Fuji Xerox)";



/************************************************************************/
/*									*/
/*	Copyright 1989, 1990 Venue, Fuji Xerox Co., Ltd, Xerox Corp.	*/
/*									*/
/*	This file is work-product resulting from the Xerox/Venue	*/
/*	Agreement dated 18-August-1989 for support of Medley.		*/
/*									*/
/************************************************************************/

/*************************************************************************/
/*************************************************************************/
/*	Copyright (C) 1987 by Fuji Xerox Co., Ltd. All rights reserved.	 */
/*************************************************************************/
/*                                                                       */
/*                       File Name : gcfinal.c                      */
/*                                                                       */
/*************************************************************************/
/*                                                                       */
/*                      Creation Date : Sep-25-1987                      */
/*                      Written by Tomoru Teruuchi                       */
/*                                                                       */
/*************************************************************************/
/*                                                                       */
/*           Functions :                                                 */
/*                       reclaimstackp();                                */
/*                       reclaimarrayblock(ptr);                         */
/*                       reclaimcodeblock() is in another file           */
/*                       releasingvmempage();                            */
/*			 deleteblock();					 */
/*			 linkblock();					 */
/*			 mergeforward();				 */
/*			 mergebackward();				 */
/*			 arrayblockmerger();				 */
/*			 checkarrayblock();				 */
/*			 findptrsbuffer();				 */
/*                                                                       */
/*                                                                       */
/*                                                                       */
/*************************************************************************/
/*           Description :                                               */
/*                                                                       */
/*  									 */
/*                                                                       */
/*************************************************************************/
/*                                                               \Tomtom */
/*************************************************************************/

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

#define GetSegnuminColl(entry1) ((entry1 & 0x01fe) >> 1)
#define GetLinkptr(entry)	(entry & 0x0fffe)
#define GetCountinColl(entry1)  ((entry1 & 0x0fc00) >> 10)
#define Oddp(num) (((num % 2) != 0)?1:0)
#define Evenp(num) 		(((num % 2) != 0)?0:1)
#define STK_HI		1	/* This value also */
#define WORDSPERCELL	2
#define PADDING	4
#define Boundp(frame_field)	((frame_field == 0)?1:0)

#define min(a,b)		((a > b)?b:a)
#define Trailer(ldatum,datum68)	(ldatum+2*(datum68->arlen - \
					ARRAYBLOCKTRAILERCELLS))
#define BucketIndex(n)		min(integerlength(n),MAXBUCKETINDEX)
#define FreeBlockChainN(n)	((0xffffff & *FreeBlockBuckets_word)+ \
					2*BucketIndex(n))

#ifndef BYTESWAP
struct buf {
	LispPTR		filepage;
	LispPTR		vmempage;
	LispPTR		buffernext;
	unsigned	noreference :1;
	unsigned	usermapped :1;
	unsigned	iodirty :1;
	unsigned	unused :5;
	unsigned	sysnext :24;
};
#else
struct buf {
	LispPTR		filepage;
	LispPTR		vmempage;
	LispPTR		buffernext;
	unsigned	sysnext :24;
	unsigned	unused :5;
	unsigned	iodirty :1;
	unsigned	usermapped :1;
	unsigned	noreference :1;
};
#endif BYTESWAP

/************* The following procedure is common !! **************************/

integerlength(n)
unsigned int	n;
{int	cnt;
   if (n <= 2)
	return(n);
   else
     {cnt = 1;
      do    
	{cnt++;
	 n = (n >> 1);
	}while(n != 1);
      return(cnt);
     };
}

/************* The above procedure is common !! **************************/



/************************************************************************/
/*									*/
/*			f i n d p t r s b u f f e r			*/
/*									*/
/*	Given a pointer to a VMEMPAGEP, see if it is pointed to by	*/
/*	any BUFFER.  If so, return the BUFFER's pointer. Otherwise,	*/
/*	return NIL.							*/
/*									*/
/************************************************************************/

LispPTR findptrsbuffer(ptr)
LispPTR		ptr;
{ struct buf *bptr;
	bptr = (struct buf *)Addr68k_from_LADDR(*System_Buffer_List_word);
	while(LADDR_from_68k(bptr) != NIL)
	  {if (ptr == bptr->vmempage)
		return(LADDR_from_68k(bptr));
	   else bptr = (struct buf *)Addr68k_from_LADDR(bptr->sysnext);};
	return(NIL);
}



/************************************************************************/
/*									*/
/*		    r e l e a s i n g v m e m p a g e			*/
/*									*/
/*	Called when ptr, a VMEMPAGEP, is about to be reclaimed by the	*/
/*	GC.  Returns T if it is NOT OK TO RECLAIM THE VMEMPAGEP.	*/
/*	Otherwise, returns NIL.  It won't be OK to reclaim when		*/
/*	the VMEMPAGEP is being used as a buffer.			*/
/*									*/
/************************************************************************/

LispPTR releasingvmempage(ptr)
  LispPTR ptr;
  { 
    register struct buf *bptr;
    register LispPTR bufferptr = findptrsbuffer(ptr);

    if (bufferptr == NIL) return(NIL); /* Not in use, OK to reclaim it */

    bptr = (struct buf *)Addr68k_from_LADDR(bufferptr);
    bptr->noreference = T; /* Mark the buffer free to use ?? */
    return(ATOM_T);
  }



/************************************************************************/
/*									*/
/*									*/
/*									*/
/*									*/
/*									*/
/************************************************************************/

LispPTR checkarrayblock(base,free,onfreelist)
LispPTR		base;
LispPTR		free;
LispPTR		onfreelist;
{struct arrayblock 	*bbase, *btrailer;
 struct arrayblock	*bfwd, *bbwd, *rbase;
 LispPTR		fbl;
 LispPTR		*rover, *tmprover;
#ifdef CHECK
   if (T)
#else
   if (*Array_Block_Checking_word != NIL)
#endif
	{bbase = (struct arrayblock *)Addr68k_from_LADDR(base);
	 btrailer=(struct arrayblock *)Addr68k_from_LADDR(Trailer(base,bbase));
	 bfwd = (struct arrayblock *)Addr68k_from_LADDR(bbase->fwd);
	 bbwd = (struct arrayblock *)Addr68k_from_LADDR(bbase->bkwd);
	 if (bbase->password != ARRAYBLOCKPASSWORD)
		error("ARRAYBLOCK password wrong\n");
	 else if (bbase->inuse == free)
		error("ARRAYBLOCK INUSE bit set wrong\n");
	 else if (btrailer->password != ARRAYBLOCKPASSWORD)
		error("ARRAYBLOCK trailer password wrong\n");
	 else if (bbase->arlen != btrailer->arlen)
		error("ARRAYBLOCK Header and Trailer length don't match\n");
	 else if (btrailer->inuse == free)
			/* This is not original source.(in original, 
			   btrailer -> bbase) maybe, this is correction. */
		error("ARRAYBLOCK Trailer INUSE bit set wrong\n");
	 else if (!onfreelist || (bbase->arlen < MINARRAYBLOCKSIZE))
			/* Remaining tests only for free list. */
		return(NIL);
	 else if ((bbwd->fwd != base) || (bfwd->bkwd != base))
		error("ARRAYBLOCK links fouled\n");
	 else
	   {fbl = FreeBlockChainN(bbase->arlen);
	    rover = tmprover = (LispPTR *)Addr68k_from_LADDR(fbl);
			/* GETBASEPTR */
	    if ((*rover & 0x0ffffff) == NIL)
		error("Free Block's bucket empty\n");
	    do
		{if ((*rover & 0x0ffffff) == base)
			return(NIL);
		 checkarrayblock((*rover & 0x0ffffff), T, NIL);
		 rbase = (struct arrayblock *)Addr68k_from_LADDR(
						*rover & 0x0ffffff);
		}while(((*rover = rbase->fwd)& 0x0ffffff) != 
						(*tmprover & 0x0ffffff));
	    return(NIL);
	   }; 
	};
   return(NIL);
}


LispPTR deleteblock(base)
LispPTR		base;
{  struct arrayblock 	*bbase, *fbbase, *bbbase;
   LispPTR		fwd,bkwd,fbl,freeblocklsp;
   LispPTR		*freeblock;
   bbase = (struct arrayblock *)Addr68k_from_LADDR(base);
   if ((bbase->arlen >= MINARRAYBLOCKSIZE) && (bbase->fwd != NIL))
	{fwd = bbase->fwd;
	 fbbase = (struct arrayblock *)Addr68k_from_LADDR(fwd);
	 bkwd = bbase->bkwd;
	 bbbase = (struct arrayblock *)Addr68k_from_LADDR(bkwd);
	 fbl = FreeBlockChainN(bbase->arlen);
	 freeblock = (LispPTR *)Addr68k_from_LADDR(fbl);
	 freeblocklsp = 0xffffff & *freeblock;
	 if (base == fwd)
	   {if (base == freeblocklsp)
		*freeblock = NIL;	
	    else error("GC error:deleting last list # FREEBLOCKLIST\n");
	    return(NIL);
	   }
         else
	   if (base == freeblocklsp)
		*freeblock = fwd;
	fbbase->bkwd = bkwd;
	bbbase->fwd  = fwd;
	}
   return(NIL);
}

LispPTR linkblock(base)
LispPTR		base;
{  struct arrayblock 	*bbase,*fbbase,*tmpbase;
   LispPTR 		fbl,freeblocklsp;
   LispPTR		*freeblock;
   if (*FreeBlockBuckets_word != NIL) 
	{ bbase = (struct arrayblock *)Addr68k_from_LADDR(base);
	  if (bbase->arlen < MINARRAYBLOCKSIZE)
		checkarrayblock(base, T, NIL);
	  else
	    {fbl = FreeBlockChainN(bbase->arlen);
	     freeblock = (LispPTR *)Addr68k_from_LADDR(0x0ffffff & fbl);
	     freeblocklsp = 0x0ffffff & (*freeblock);
	     if (freeblocklsp == NIL)
		{bbase->fwd = base;
		 bbase->bkwd = base;
		}
	     else
		{fbbase = (struct arrayblock *)Addr68k_from_LADDR(freeblocklsp);
		 bbase->fwd = freeblocklsp;
		 bbase->bkwd = fbbase->bkwd;
		 tmpbase = (struct arrayblock *)
				Addr68k_from_LADDR(fbbase->bkwd);
		 tmpbase->fwd = base;
		 fbbase->bkwd = base;
		};
	     *freeblock = base;
	     checkarrayblock(base, T, T);
	    };
	};
	return(base);
}




LispPTR makefreearrayblock(block, length)
LispPTR		block;
DLword		length;
{ LispPTR		trailer;
  struct arrayblock 	*bbase;
  struct abdum		*dbase;
   bbase = (struct arrayblock *)Addr68k_from_LADDR(block);
   dbase = (struct abdum *)WORDPTR(bbase);
   dbase->abflags = FREEARRAYFLAGWORD;
   bbase->arlen   = length;
   trailer = Trailer(block,bbase); 
   bbase = (struct arrayblock *)Addr68k_from_LADDR(trailer);
   dbase = (struct abdum *)WORDPTR(bbase);
   dbase->abflags = FREEARRAYFLAGWORD;
   bbase->arlen   = length;
   return(block);
}




LispPTR arrayblockmerger(base, nbase)
LispPTR		base, nbase;
{   DLword arlens, narlens, secondbite, minblocksize, shaveback;
    struct arrayblock 	*bbase, *bnbase;
    bbase = (struct arrayblock *)Addr68k_from_LADDR(base);
    bnbase = (struct arrayblock *)Addr68k_from_LADDR(nbase);
    arlens = bbase->arlen;
    narlens = bnbase->arlen;
    secondbite = MAXARRAYBLOCKSIZE - arlens;
    if (narlens > secondbite)
	{arlens = MAXARRAYBLOCKSIZE;
	 narlens = narlens - secondbite;
	 minblocksize = ((*Hunk_word == ATOM_T) ? 
			   (ARRAYBLOCKOVERHEADCELLS+MAXCELLSPERHUNK) : 
			   MINARRAYBLOCKSIZE);
	 if (narlens < minblocksize)
	    {shaveback = narlens - minblocksize;
	     narlens = minblocksize;
	     arlens += shaveback;
	     secondbite += shaveback;
	    };
	linkblock(makefreearrayblock(nbase+2*secondbite, narlens));
	narlens = 0;
	};
    return(linkblock(makefreearrayblock(base, arlens+narlens)));
}




LispPTR mergebackward(base)
LispPTR 	base;
{  LispPTR 		pbase;
   struct arrayblock 	*ptrailer; 

   ptrailer = (struct arrayblock *)Addr68k_from_LADDR(base -
					ARRAYBLOCKTRAILERWORDS);
   if (base == NIL)
	return(NIL);
   else if ((*ArrayMerging_word == NIL) || ((base == *ArraySpace_word) || 
	     ((base == *ArraySpace2_word) || (ptrailer->inuse == T))))
	    return(linkblock(base));
   pbase = base - 2*ptrailer->arlen;
   checkarrayblock(pbase, T,NIL);
   deleteblock(pbase);
   return(arrayblockmerger(pbase, base));
}




LispPTR mergeforward(base)
LispPTR 	base;
{   LispPTR	nbase, nbinuse;
    struct arrayblock 	*bbase, *bnbase;
    bbase = (struct arrayblock *)Addr68k_from_LADDR(base);
    nbase = base + 2*(bbase->arlen);
    bnbase = (struct arrayblock *)Addr68k_from_LADDR(nbase);
    if ((*ArrayMerging_word == NIL) || ((base == NIL)
	 || (checkarrayblock(base, T, T) || ((nbase == *ArrayFrLst_word) ||
	 ((nbase == *ArrayFrLst2_word) || 
	 (checkarrayblock(nbase, (! (nbinuse = bnbase->inuse)),NIL) || 
	 nbinuse))))))
	return(NIL);
    deleteblock(nbase);
    deleteblock(base);
    return(arrayblockmerger(base, nbase));
}




LispPTR reclaimarrayblock(ptr)
LispPTR ptr;
{ LispPTR		tmpptr, btrailer;
  struct arrayblock 	*base;
  LispPTR		*tmpp;
  int			reclaim_p;

     reclaim_p = T;
#ifdef CHECK
     checkarrayblock(ptr-ARRAYBLOCKHEADERWORDS, NIL, NIL);
#endif
     base = (struct arrayblock *)Addr68k_from_LADDR(ptr-ARRAYBLOCKHEADERWORDS);

     if ((HILOC(ptr) < FIRSTARRAYSEGMENT) ||
	   ((ARRAYBLOCKPASSWORD != base->password) ||
	    (base->inuse == NIL)))
	   {error(
          "Bad array block reclaimed--continue with 'Q' but save state ASAP. \n");
	    return(T);
	   }; 

     switch(base->gctype)
	  {
	   case PTRBLOCK_GCT:
		{btrailer = (ptr-2)+2*(base->arlen - ARRAYBLOCKTRAILERCELLS);
		 tmpptr = ptr;
		 do
		   {
		    tmpp = (LispPTR *)Addr68k_from_LADDR(tmpptr);
		    GCLOOKUP(0x8000,DELREF, *tmpp); /* added 8-Oct-87 TT */
		    *tmpp = NIL;
		    tmpptr += 2;
		   } while (tmpptr != btrailer);
		 break;	
		};
	   case CODEBLOCK_GCT:
		reclaim_p = ((reclaimcodeblock(ptr) == NIL)?T:NIL); 


       /* default:   No Action */
	  };
     if (reclaim_p == T)
	mergeforward(mergebackward(makefreearrayblock(
						ptr-ARRAYBLOCKHEADERWORDS
							,base->arlen)));
     return(T);
}




LispPTR reclaimstackp (ptr)		/* This is the entry function */
LispPTR		ptr;			/*  in stack reclaiming */
{
 register STACKP *stkp;
 register FX	*fxp;
 stkp = (STACKP*)Addr68k_from_LADDR(ptr);
 fxp = (FX*)Addr68k_from_StkOffset( stkp->edfxp );
 decusecount68k(fxp);
 return(NIL);
}



