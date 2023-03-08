/* @(#) allocmds.c Version 2.6 (4/21/92). copyright envos & Fuji Xerox  */
static char *id = "@(#) allocmds.c	2.6 4/21/92";


/************************************************************************/
/*									*/
/*	Copyright 1989, 1990 Venue, Fuji Xerox Co., Ltd, Xerox Corp.	*/
/*									*/
/*	This file is work-product resulting from the Xerox/Venue	*/
/*	Agreement dated 18-August-1989 for support of Medley.		*/
/*									*/
/************************************************************************/

/*
 *	Copyright (C) 1987 by Fuji Xerox Co., Ltd. All rights reserved.
 *
 *	Author : Takeshi Shimizu
 *
 */

/**********************************************************************/
/*
		File Name :	allocmds.c

		Allocate Data Type(MDS)

				Date :		August 18, 1987
				Edited by :	Takeshi Shimizu

		Including :	initmdspage
				alloc_mdspage

*/
/**********************************************************************/

#include "lispemul.h"
#include "address.h"
#include "adr68k.h"
#include "lsptypes.h"
#include "cell.h"
#include "lispmap.h"
#include "initatms.h"
#include "sysatms.h"
#include "lspglob.h"

/* I consider that there is no case the variable named \GCDISABLED is set to T */
#define Make_MDSentry(page,pattern)  GETWORD((DLword *)MDStypetbl+(page>>1)) = (DLword)pattern




/**********************************************************************/
/*
	Func name :	initmdspage

		Write the specified MDSTT entry with specified pattern.
		returns Top entry for free chain lisp address

				Date :		December 24, 1986
				Edited by :	Takeshi Shimizu
				Changed :	Jun. 5 87 take

*/
/**********************************************************************/

LispPTR initmdspage(base , size , prev)
  register  LispPTR *base; /* MDS page base */
  register DLword size;  /* object cell size you need (WORD) */
  register LispPTR prev; /* keeping top of previous MDS cell */

  {
    extern DLword *MDStypetbl;

    register int remain_size;  /* (IREMAINDER WORDSPERPAGE SIZE) */
    register short num_pages;
    register int limit;
    int used;   /* used space in MDS page */
     register int i;

#ifdef TRACE2
	printf("TRACE: initmdspage()\n");
#endif

    remain_size = DLWORDSPER_PAGE % size;

   if(  (remain_size != 0)
      && (remain_size < (size >> 1) 
      && (size < DLWORDSPER_PAGE)))
      {
	num_pages = MDSINCREMENT / DLWORDSPER_PAGE;  /* on 1121 maybe 2 */
	limit = DLWORDSPER_PAGE;
      }
    else
      {
	num_pages = 1;
	limit = MDSINCREMENT;
      }

    for(i=0; i< num_pages; i++)
      {
	used=0;
	while((used += size)<= limit)
	  {
	    *base = prev; /* write prev MDS address to the top of MDS page */
	    prev =LADDR_from_68k( base );	/* exchanging pointers */
	    base = (LispPTR *)((DLword *)base + size);
	  } /* while end */

	base = (LispPTR *)((DLword *)base + remain_size );

      } /* for end */

    return (prev);
  } /* initmdspage end */



/**********************************************************************/
/*
		Func name :	alloc_mdspage

			This version works only for KATANA-SUN

			Date :		January 13, 1987
			Edited by :	Takeshi Shimizu
			Changed :	3-Apr-87 (take)
					20-Aug-87(take) ifdef
					08-Oct-87(take) checkfull
					22-Dec-87(Take)

*/
/**********************************************************************/
/*** For KATANA version ***/
/** Rev. 12-Oct-87 take *****/
/** Add. newpage 13-Oct-87 take **/

LispPTR *alloc_mdspage(type)
  register short type;
  {
    /* It contains Free MDS page number */
    extern LispPTR *MDS_free_page_word;
    /* It contains next vacant(new) MDS page */
    extern DLword *Next_MDSpage;
    extern LispPTR *Next_MDSpage_word;
    extern LispPTR *Next_Array_word;

    LispPTR newpage();

    register LispPTR *ptr;  /* points Top 32 bit of the MDS page */
    LispPTR next_page;

   /* Next_Array=(DLword *)Addr68k_from_LADDR(((*Next_Array_word)& 0xffff ) << 8); */


    if(LOLOC(*MDS_free_page_word )!=NIL)
      {
	ptr= (LispPTR *)Addr68k_from_LPAGE(LOLOC(*MDS_free_page_word ));

	if( ((next_page= LOLOC(*ptr))!=0 )
	   && (GetTypeNumber((*ptr))!= TYPE_SMALLP))
		error("alloc_mdspage: Bad Free Page Link");
	else {
		*MDS_free_page_word = S_POSITIVE | next_page;
	     }
      }
    else
      {
	/* I guess Next_MDSpage is redundant */
	checkfor_storagefull(NIL);
	Next_MDSpage= (DLword *)Addr68k_from_LADDR(((*Next_MDSpage_word)& 0xffff ) << 8);

	ptr = (LispPTR *)Next_MDSpage; /* Get Pointer to First Page */
	Next_MDSpage -= DLWORDSPER_PAGE * 2;  /* decrement MDS count */
	*Next_MDSpage_word=S_POSITIVE| LPAGE_from_68k(Next_MDSpage);

	newpage(newpage(LADDR_from_68k(ptr)) + DLWORDSPER_PAGE);
      }

    Make_MDSentry(LPAGE_from_68k(ptr),type);
    return (ptr);
  } /* alloc_mdspage end */


