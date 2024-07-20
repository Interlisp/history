/* @(#) Kdebugtools.c Version 2.6 (3/30/89). copyright envos & Fuji Xerox  */
static char *id = "@(#) Kdebugtools.c	2.6 3/30/89";


/************************************************************************/
/*									*/
/*	Copyright 1989, 1990 Venue, Fuji Xerox Co., Ltd, Xerox Corp.	*/
/*									*/
/*	This file is work-product resulting from the Xerox/Venue	*/
/*	Agreement dated 18-August-1989 for support of Medley.		*/
/*									*/
/************************************************************************/

/***************************************************************/
/*
	file name :	 Kdebugtools.c

	For Debugging Aids

	Including :
		get_ivar_name(fx_addr68k , offset)

		date :   25 Aug 1987	NMitani
		changed: 09 Sep 1987 NMitani

*/
/***************************************************************/
#include <stdio.h>
#include  <setjmp.h>
#include "lispemul.h"
#include "lispmap.h"
#include "address68k.h"
#include "lisptypes.h"
#include "lispglobal.h"
#include "emulglobal.h"
#include "cell.h"
#include "stack.h"

#define	LOCAL_PVAR	0xFFFF
#define	VTY_IVAR	0x0000
#define	VTY_PVAR	0x8000
#define VTY_FVAR	0xC000

#define URMAXFXNUM		2000
#define URSCAN_ALINK		0
#define URSCAN_CLINK		1
extern int URaid_scanlink;
extern int URaid_currentFX;
extern FX *URaid_FXarray[];
extern int URaid_ArrMAXIndex;
int BT_lines;
int BT_temp;
jmp_buf BT_jumpbuf;
#define BTMAXLINE 30
#define BT_morep if(++BT_lines>BTMAXLINE){\
			 printf("Press Return(to quit Esc and Ret):");\
			 BT_temp=getchar();\
			 fflush(stdin);\
			 BT_lines=0; \
			 if(BT_temp==27)longjmp(BT_jumpbuf,1) ; \
		}



/***************************************************************/
/*
	Func Name :	get_ivar_name

	Desc :		returns atom index of ivar on the given
			FX.
			If ivar is localvars then set *localivar
			1 otherwize 0.

	Changed		25 Aug 1987	NMitani

*/
/***************************************************************/

LispPTR get_ivar_name(fx_addr68k , offset , localivar)
  struct frameex1 *fx_addr68k ;
  DLword offset ;
  int *localivar ;
  {
    DLword		*first_table;
    DLword		*second_table;
    struct fnhead	*fnobj;
    int		i;

    fnobj = (struct fnhead *)Addr68k_from_LADDR(
		((int)(fx_addr68k)->hi2fnheader << 16) | (fx_addr68k)->lofnheader);

    if (fnobj->ntsize > 0)
      {
	/* name table exists */
	first_table = (DLword *)(fnobj + 1);
	second_table = first_table + fnobj->ntsize;
	for(i = 0; (i < fnobj->ntsize) && (GETWORD(second_table) != offset) ;
	first_table++ , second_table++ , i++) ;
	if ((i < fnobj->ntsize) && (GETWORD(first_table) != 0))
	  {
	    /* target ivar was in name table */
	    *localivar = 0 ;
	    return((LispPTR)(GETWORD(first_table)));
	  }
	else
	  {
	    /* Target ivar is in locar vars table */
	    first_table = (DLword *)(fnobj + 1) + (fnobj->ntsize << 1);
	    second_table = first_table + (((DLword *)fnobj +
				(fnobj->startpc >> 1) - first_table) >> 1);
	  }
      }
    else
      {
	/* name table doesn't exist, so all ivars are in locar vars table */
	first_table = (DLword *)(fnobj + 1) +  4;
	second_table = first_table +
	(((DLword *)fnobj + (fnobj->startpc >> 1) - first_table) >> 1);
      }
    while (GETWORD(second_table) != (VTY_IVAR |offset))
      {
	first_table++ ;
	second_table++ ;
      }
    *localivar = 1 ;
    return((LispPTR)(GETWORD(first_table)));

 }/* end get_ivar_name */



/***************************************************************/
/*
	Func Name :	get_pvar_name

	Desc :		returns atom index of pvar on the given
			FX or LOCAL_PVAR if that pvar is localvars.

	Changed		26 Aug 1987	NMitani

*/
/***************************************************************/

LispPTR get_pvar_name(fx_addr68k , offset)
  struct frameex1 *fx_addr68k ;
  DLword offset ;
  {
    DLword		*first_table;
    DLword		*second_table;
    struct fnhead	*fnobj;
    int		i;

    fnobj = (struct fnhead *)Addr68k_from_LADDR(
	     ((int)(fx_addr68k)->hi2fnheader << 16) | (fx_addr68k)->lofnheader);

    first_table = (DLword *)(fnobj + 1);
    second_table = first_table + fnobj->ntsize;
    if (first_table == second_table) return(LOCAL_PVAR);  /* no name table */

    for(i = 0;
        i < fnobj->ntsize && GETWORD(second_table) != (VTY_PVAR | offset);
	first_table++ , second_table++ , i++) /* Do nothing */;

    if (i < fnobj->ntsize) return((LispPTR)GETWORD(first_table));
    else return(LOCAL_PVAR);	/* Pvar was local */
  }/* end get_pvar_name */




/***************************************************************/
/*
	Func Name :	get_fvar_name

	Desc :		returns atom index of fvar on the given
			FX.

	Changed		26 Aug 1987	NMitani

*/
/***************************************************************/

LispPTR get_fvar_name(fx_addr68k , offset)
  struct frameex1 *fx_addr68k ;
  DLword offset ;
  {
    DLword		*first_table;
    DLword		*second_table;
    struct fnhead	*fnobj;

    fnobj = (struct fnhead *)Addr68k_from_LADDR(
	    ((int)(fx_addr68k)->hi2fnheader << 16) | (fx_addr68k)->lofnheader);

    first_table = (DLword *)fnobj + fnobj->fvaroffset;
    second_table = first_table + fnobj->ntsize;

    while (GETWORD(second_table) != (VTY_FVAR | offset))
      {
	first_table++ ;
	second_table++;
      }

    return((LispPTR)GETWORD(first_table));

  }/* end get_fvar_name */



/************************************************************************/
/*									*/
/*				s f					*/
/*									*/
/*	Dump the contents of a single frame, given the address of 	*/
/*	the frame as a NATIVE address.					*/
/*									*/
/*									*/
/*									*/
/************************************************************************/

sf(fx_addr68k)
  struct frameex1 *fx_addr68k ;
{
  Bframe *bf;
  DLword *next68k ;
  DLword *ptr ;
  DLword *ptrhi ;
  DLword *ptrlo ;
  LispPTR atomindex ;
  int i;
  DLword npvar;
  DLword max_npvar;
  LispPTR pvarindex ;
  DLword nfvar;
  struct fnhead	*fnobj;
  int localivar;
  LispPTR ivarindex ;

  BT_lines=0;
 if((int)fx_addr68k == 0) return(-1);
 if((fx_addr68k)->flags != STK_FX){
	printf("Invalid FX 0x%x, flags = 0x%x.\n",
		LADDR_from_68k(fx_addr68k),
		(fx_addr68k)->flags);
	return(-1);
 }

 if(((fx_addr68k)->alink & 1)==0)
  {   /* FAST */
	bf = (Bframe *)(((DLword *)fx_addr68k)  - 2 );
  }
  else
  {   /* SLOW */
	bf =(Bframe *) Addr68k_from_LADDR(((fx_addr68k)->blink+ STK_OFFSET)) ;
  }

/* Print IVARs */
  printf("IVAR -------\n");BT_morep;

  ptr = Addr68k_from_LADDR( STK_OFFSET + bf->ivar);
 i=0;
 while(ptr!=(DLword *)bf)
{
  ptrhi = ptr;
  ptrlo = ptr + 1 ;
  printf(" %6x : 0x%4x  0x%4x  ",LADDR_from_68k(ptr), GETWORD(ptr) , GETWORD(ptrlo));
  ivarindex = get_ivar_name(fx_addr68k , i++ , &localivar);
  if (localivar == 1)
	printf("*local* ");
  print_atomname(ivarindex);
  printf("  ");
  print(*(LispPTR *)ptr);
  putchar('\n');BT_morep;
  ptr += 2 ;
}
 putchar('\n');BT_morep;
 printf("## STACK BF at 0x%x ##\n",(LispPTR)LADDR_from_68k(bf));BT_morep;
/* print BF  */
 if(bf->flags != 4)
	{printf("Invalid frame, NOT a BX\n");return(-1);}
 putchar('[');
  if (bf->residual)	printf("Res, ");
  if (bf->padding)	printf("Pad, ");
  printf("cnt=%d ]\n",bf->usecnt);BT_morep;
  printf("ivar : 0x%x\n",bf->ivar);BT_morep;

    printf(">> Bf's ivar says 0x%x vs. IVar says 0x%x\n",bf->ivar+STK_OFFSET,LADDR_from_68k(IVar));BT_morep;


  atomindex = get_framename(fx_addr68k);
  printf("Fname is ");
  print_atomname(atomindex);
  printf("\n");BT_morep;

/***** printout FX ****/
  printf("## STACK FX at 0x%x ##\n",LADDR_from_68k(fx_addr68k));BT_morep;

  if((fx_addr68k)->flags != 6)
   { printf("Invalid frame, NOT FX\n");return(-1);}

 putchar('[');
  if((fx_addr68k)->fast)		printf("F, ");
  if((fx_addr68k)->incall)	printf("incall, ");
  if(fx_addr68k->validnametable)	printf("V, ");
  printf("cnt = %d ]\n",fx_addr68k->usecount);BT_morep;

  printf(" #alink           0x%x ",fx_addr68k->alink);
  if(fx_addr68k->alink & 1)
  printf("[SLOWP]\n");
  else printf("\n");

 BT_morep;

  printf(" fnheadlo         0x%x \n",fx_addr68k->lofnheader);BT_morep;
  printf(" hi1,hi2 fnhead   0x%x , 0x%x \n",fx_addr68k->hi1fnheader,fx_addr68k->hi2fnheader);BT_morep;
  printf(" nextblock        0x%x \n",fx_addr68k->nextblock);BT_morep;
  printf(" pc               0x%x \n",fx_addr68k->pc);BT_morep;
  printf(" lonametbl        0x%x \n",fx_addr68k->lonametable);BT_morep;
  printf(" hi1,hi2 nametbl  0x%x , 0x%x  \n",fx_addr68k->hi1nametable,fx_addr68k->hi2nametable);BT_morep;
  printf(" #blink           0x%x \n",fx_addr68k->blink);BT_morep;
  printf(" #clink           0x%x \n",fx_addr68k->clink);BT_morep;

/* added by NMitani 26 Aug 87 */

 fnobj = (struct fnhead *)Addr68k_from_LADDR(
		((int)fx_addr68k->hi2fnheader << 16) | fx_addr68k->lofnheader);
 max_npvar = npvar = fnobj->nlocals;	/* npvar is number of Pvars */
 if (fnobj->fvaroffset)
  nfvar = GETWORD((DLword *)fnobj + fnobj->fvaroffset + fnobj->ntsize) & 0xFF;
 else
  nfvar = 0;
 if (fx_addr68k == CURRENTFX) {
	ptr=PVar;
	i = 0;
	while(npvar-- > 0){
		ptrhi = ptr;
		ptrlo = ptr + 1 ;
		printf(" %6x : 0x%4x  0x%4x  ",LADDR_from_68k(ptr),GETWORD(ptrhi) ,
			GETWORD(ptrlo));
		if ((pvarindex = get_pvar_name(fx_addr68k , i++)) == LOCAL_PVAR)
			printf("*local* [pvar%d] " , (i - 1));
		else
			print_atomname(pvarindex);
		if (GETWORD(ptr) == 0xFFFF){
			printf("  [variable not bound]\n");BT_morep;
		}
		else{
			printf("  ");
			print(*(LispPTR *)ptr);
			putchar('\n');		BT_morep;
		}
		ptr += 2 ;
	}
	i = max_npvar;
	while(nfvar && nfvar-- >= max_npvar){
		ptrhi = ptr;
		ptrlo = ptr + 1 ;
		printf(" %6x : 0x%4x  0x%4x  ",LADDR_from_68k(ptr),GETWORD(ptrhi) ,
			GETWORD(ptrlo));
		if (0xFFFF == GETWORD(ptrhi)){
			printf("[not looked up]  ");
			print_atomname(get_fvar_name(fx_addr68k , i));
			putchar('\n');BT_morep;
		}
		else if ((0xFFFF & GETWORD(ptrlo)) == 1){
			printf("[fvar  ");
			print_atomname(get_fvar_name(fx_addr68k , i));
			printf("  on stack]  ");
			print(*(LispPTR *)(Addr68k_from_LADDR(((int)(0x0F & GETWORD(ptrlo)) << 16) | GETWORD(ptrhi))));
			putchar('\n');BT_morep;
		}
		else{
			printf("[fvar  ");
			print_atomname(get_fvar_name(fx_addr68k , i));
			printf("  top value ]   ");
			print(*(LispPTR *)(Addr68k_from_LADDR(((int)(0x0F & GETWORD(ptrlo)) << 16) | GETWORD(ptrhi))));
			putchar('\n');BT_morep;
		}
		ptr += 2 ;
		i++;
	}
	if (fx_addr68k->alink == 11)  /* for contextsw */
		next68k = (DLword *)Addr68k_from_LADDR((fx_addr68k->nextblock+STK_OFFSET)) ;

	else
		next68k = CurrentStackPTR;
	while(ptr < next68k)
	{
		ptrhi = ptr;
		ptrlo = ptr + 1 ;
		printf(" %6x : 0x%4x  0x%4x  ",LADDR_from_68k(ptr),GETWORD(ptrhi) ,
			GETWORD(ptrlo));
		print(*(LispPTR *)ptr);
		ptr += 2 ;
		putchar('\n');BT_morep;
	}
  printf("this frame is last !!\n");BT_morep;
  return(-1);
 }

 next68k = (DLword *)Addr68k_from_LADDR((fx_addr68k->nextblock+STK_OFFSET)) ;
 ptr =(DLword *)(fx_addr68k+1) ;

 i = 0;
 while(npvar-- > 0){
		ptrhi = ptr;
		ptrlo = ptr + 1 ;
		printf(" %6x : 0x%4x  0x%4x  ",LADDR_from_68k(ptr),GETWORD(ptrhi) ,
			GETWORD(ptrlo));
		if ((pvarindex = get_pvar_name(fx_addr68k , i++)) == LOCAL_PVAR)
			printf("*local* [pvar%d] " , (i - 1));
		else
			print_atomname(pvarindex);
		if (GETWORD(ptr) == 0xFFFF){
			printf("  [variable not bound]\n");BT_morep;
		}
		else{
			printf("  ");
			print(*(LispPTR *)ptr);
			putchar('\n');		BT_morep;
		}
		ptr += 2 ;
	}
 i = max_npvar;
	while(nfvar && nfvar-- >= max_npvar){
		ptrhi = ptr;
		ptrlo = ptr + 1 ;
		printf(" %6x : 0x%4x  0x%4x  ",LADDR_from_68k(ptr),GETWORD(ptrhi) ,
			GETWORD(ptrlo));
		if (0xFFFF == GETWORD(ptrhi)){
			printf("[not looked up]  ");
			print_atomname(get_fvar_name(fx_addr68k , i));
			putchar('\n');BT_morep;
		}
		else if ((0xFFFF & GETWORD(ptrlo)) == 1){
			printf("[fvar  ");
			print_atomname(get_fvar_name(fx_addr68k , i));
			printf("  on stack]  ");
			print(*(LispPTR *)(Addr68k_from_LADDR(((int)(0x0F & GETWORD(ptrlo)) << 16) | GETWORD(ptrhi))));
			putchar('\n');BT_morep;
		}
		else{
			printf("[fvar  ");
			print_atomname(get_fvar_name(fx_addr68k , i));
			printf("  top value ]   ");
			print(*(LispPTR *)(Addr68k_from_LADDR(((int)(0x0F & GETWORD(ptrlo)) << 16) | GETWORD(ptrhi))));
			putchar('\n');BT_morep;
		}
		ptr += 2 ;
		i++;
	}
 while(next68k > ptr)
  {
	printf(" %6x : 0x%4x  0x%4x  ",LADDR_from_68k(ptr),GETWORD(ptr++) ,
		GETWORD(ptr++));
	putchar('\n');BT_morep;
  }
return (0);

}



/************************************************************************/
/*									*/
/*				b t					*/
/*									*/
/*	Print the names of the frames on the stack.  Equivalent to	*/
/*	the Lisp DEBUGGER's BT! command.				*/
/*									*/
/*		Changed		26 Aug 1987	NMitani			*/
/*		Changed   May 4, 1988	Take(for URaid)			*/
/*									*/
/************************************************************************/

bt()
  {
    bt1(CURRENTFX);
  }


bt1(startFX)
  FX *startFX;
  {
    FX	*fx ;
    struct fnhead	*fnobj;
    FX *get_nextFX();
    int fnum=0;
    BT_lines=0;
    fx = startFX ;
    URaid_FXarray[fnum]=fx;
    printf("%3d : ",fnum++);
    fnobj = (struct fnhead *)Addr68k_from_LADDR(
    	((int)fx->hi2fnheader << 16) | fx->lofnheader);
    printf("   0x%x : " , LADDR_from_68k(fx));
    print_atomname(fnobj->framename);
    putchar('\n');BT_morep;
    while((fnobj->framename != ATOM_T) && (fx->alink != 11))
      {
	if(fnum >URMAXFXNUM-1)
	  {
	   /* Internal buf overflow,more than 100 stacks */
	   printf("***There are more than 100 stack frames.\n");
	   printf("If you want to continue, Uraid will smash its internal table for FX pointer. Do you accept?(Y or N)\n");
	   {
	     int c;
	     c= getchar();fflush(stdin);
	     if((c=='Y')||(c=='y'))
	       {
		 fnum=0;
		 bzero(URaid_FXarray,URMAXFXNUM *4);
	       }
	     else goto bt1_exit;

	    }
	  }

	fx= get_nextFX(fx);
	fnobj = (struct fnhead *)Addr68k_from_LADDR(
	((int)fx->hi2fnheader << 16) | fx->lofnheader);
	URaid_FXarray[fnum]=fx;
	printf("%3d : ",fnum++);
	printf("   0x%x : " , LADDR_from_68k(fx));
	print_atomname(fnobj->framename);
	putchar('\n');BT_morep;
      }
   if (fnobj->framename != ATOM_T)
      {
	printf(">>root frame for contextsw<<\n");
	putchar('\n');BT_morep;
      }

bt1_exit: URaid_ArrMAXIndex=fnum-1;
	URaid_currentFX=0;
  }/* end bt */




/***************************************************************/
/*
	Func Name :	btvv

	Desc :		dumps the all stack frame name.

	Changed		4 Sep 1987	NMitani

*/
/***************************************************************/



/************************************************************************/
/*									*/
/*				b t v v					*/
/*									*/
/*	Print all stack frames, with variables.  Equivalent to the	*/
/*	Lisp DEBUGGER's BTV! command.					*/
/*									*/
/*									*/
/*									*/
/************************************************************************/

btvv()
{
	struct frameex1 *fx_addr68k;
	LispPTR atomindex ;
	FX *get_nextFX();

	fx_addr68k = CURRENTFX ;

	atomindex = get_framename(fx_addr68k);

	while((atomindex != ATOM_T) && (fx_addr68k->alink != 11))
	{
		sf(fx_addr68k);
		fx_addr68k= get_nextFX(fx_addr68k);
		atomindex = get_framename(fx_addr68k);

	}

	sf(fx_addr68k);

	printf("\n BTV! end ********\n");


} /*end btvv*/




/************************************************************************/
/*									*/
/*				s f f					*/
/*									*/
/*	Given the address of a lisp stack frame-extension (FX)		*/
/*	as a LISP (not native!) address, print the stack frame.		*/
/*									*/
/*									*/
/*							NMitani		*/
/************************************************************************/

sff(laddr)
  LispPTR laddr;
  {
    sf((FX *)Addr68k_from_LADDR(laddr));
  }
