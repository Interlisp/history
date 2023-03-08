/* @(#) lisp2c.c Version 1.3 (4/21/92). copyright venue & Fuji Xerox  */
static char *id = "@(#) lisp2c.c	1.3 4/21/92	(venue & Fuji Xerox)";
/* File containing the conversion functions between lisp and C */
/* -jarl */

#include "lispemul.h"
#include "lspglob.h"
#include "emlglob.h"
#include "adr68k.h"
#include "lispmap.h"
#include "lsptypes.h"
#include "fp.h"
#include "arith.h"


int LispStringLenght (lispstring)
     LispPTR *lispstring;
{
  OneDArray	*arrayp;

  arrayp = (OneDArray *)(Addr68k_from_LADDR((unsigned int)lispstring));
  return(arrayp->fillpointer);
}

LispStringToCStr (lispstring, cstring)
     LispPTR lispstring;
     char cstring[];

{
  OneDArray *arrayp;
  char	*base;
  short	*sbase;
  int	i, Len;

  arrayp = (OneDArray *)(Addr68k_from_LADDR((unsigned int)lispstring));
  Len = arrayp->fillpointer;

  switch(arrayp->typenumber)
    {
    case THIN_CHAR_TYPENUMBER:
      base = ((char *)
	      (Addr68k_from_LADDR((unsigned int)arrayp->base)))
	+ ((int)(arrayp->offset));
      for(i=0;i<Len;i++)
	cstring[i] = base[i];
      cstring[Len] = '\0';
      break;

    case FAT_CHAR_TYPENUMBER:
      sbase = ((short *)
	       (Addr68k_from_LADDR((unsigned int)arrayp->base)))
	+ ((int)(arrayp->offset));
      base = (char *)sbase;
      for(i=0;i<Len*2;i++)
	cstring[i] = base[i];
      cstring[Len*2] = '\0';
      break;

    default:
      error("LStringToCString can not handle\n");
    }
}

int LispIntToCInt (lispint)
     LispPTR lispint;
{
  switch( (0xFFFF0000 & lispint) ){
  case S_POSITIVE:
    return(lispint & 0xFFFF);
    break;
  case S_NEGATIVE:
    return(lispint | 0xFFFF0000);
    break;
  default:
    if( GetTypeNumber(lispint) == TYPE_FIXP ) {
      return( *((int *)Addr68k_from_LADDR(lispint)));
    } else {
      printf("LispIntToCInt: Arg not Lispint.\n");
    }
    break;
  }
}

LispPTR CIntToLispInt(cint)
     int cint;
{
  if (abs(cint) > 0xFFFF) {	/* its a fixp! */
    register LispPTR *wordp;
    wordp = (LispPTR *) createcell68k(TYPE_FIXP);
    *((int *)wordp) = cint;
    return(LADDR_from_68k(wordp));
  } else if (cint >= 0) {	/* its a positive smallp! */
    return(S_POSITIVE | cint);
  } else {			/* its a negative smallp! */
    return(S_NEGATIVE | (0xFFFF & cint));
  }
}
