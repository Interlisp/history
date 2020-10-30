/* This is G-file @(#) uraid.c Version 1.21 (9/19/88). copyright Xerox & Fuji Xerox  */static char *id = "@(#) uraid.c	1.21 9/19/88";#include <stdio.h>#include "lispemul.h"#include "lispmap.h"#include "address68k.h"#include "lisptypes.h"#include "lispglobal.h"#include "emulglobal.h"#include "cell.h"#include "stack.h"#include "ifpage.h"#include "debug.h"#include <sys/file.h>#include <sys/types.h>#include <sys/param.h>#include <sys/ioctl.h>#include <fcntl.h>#include <sundev/kbd.h>#include <sundev/kbio.h>#include <errno.h>#include <sunwindow/window_hs.h>#include <sunwindow/win_ioctl.h>#include <pixrect/pixrect_hs.h>#include <sunwindow/win_cursor.h>#include <sunwindow/cms.h>#include <sys/mman.h>/***********************************************************************//*	File name : uraid.c	Written by : Takeshi Shimizu(Take)	Date:   6-May-1988	This File Supports the following commands:**URAID commands summary**<<Displaying a Stack>>c                       Checks all user stack contentsf number                Displays Frame extension for the number(decimal)k type                  Changes the type of stack link following.(a|c)l [type]                Back Trace for Specified type stack.(k|m|r|g|p|u)<CR>                    Display next frame.<<Displaying the Memory contents>>a litatom               Displays the top-level value of the litatomd litatom               Displays the Definition Cell for the litatomM                       Displays TOS,CSP,PVAR,IVAR,PCm func1 func2           MOVED func1 to func2t Xaddress              Displays the type of this objectp litatom               Displays the Property list of the litatomw                       Displays the current function-name and PCx Xaddress [xnum]       Hex-Dump xnum word(16-bits) starting at Xaddress@ litatom val           Sets TOPVAL of litatom to Decimal-val< Xaddress val          Sets the word(16-bits) at the address to val<<Return or Exit>>e                       Exit to UNIXh                       Context switch to HARDRESETq                       Returns from URAID with NO-change<<Misc>>s                       Invoke Shellv filename              Save the virtual memory on the filename(Not Bootable)( [num]                 Sets Print level!			Prints the error message passed from the emulator?                       Display this summary*//************************************************************************/extern unsigned int LispReadFds,LispWindowFd,LispKbdFd;extern struct pixrect *ScreenBitMap,*CursorBitMap,*InvisibleCursorBitMap;extern struct screen LispScreen;extern int DisplayWidth,DisplayHeight;extern DLword *DisplayRegion68k;extern int FrameBufferFd,ether_fd,RS232C_Fd;LispPTR RadiAtomIndex;LispPTR RaidPackageIndex;struct pixrect *HideBitMap;char *HideDisp68k;char *URaid_summary = {"**URAID commands summary**\n\<<Displaying a Stack>>\n\c\t\t\tChecks all user stack contents\n\f number\t\tDisplays Frame extension for the number(decimal)\n\k type\t\t\tChanges the type of stack link following.(a|c)\n\l [type]\t\tBack Trace for Specified type stack.(k|m|r|g|p|u|<null>)\n\<CR>\t\t\tDisplay next frame.\n<<Displaying the Memory contents>>\n\a litatom\t\tDisplays the top-level value of the litatom\n\d litatom\t\tDisplays the Definition Cell for the litatom\n\M\t\t\tDisplays TOS,CSP,PVAR,IVAR,PC\nm func1 func2\t\tMOVED func1 to func2\n\t Xaddress\t\tDisplays the type of this object\n\p litatom\t\tDisplays the Property list of the litatom\n\w\t\t\tDisplays the current function-name and PC\n\x Xaddress [xnum]\tHex-Dump xnum word(16-bits) starting at Xaddress\n\@ litatom val\t\tSets TOPVAL of litatom to Decimal-val\n\< Xaddress val\t\tSets the word(16-bits) at the address to Xval\n\<<Return or Exit>>\n\e\t\t\tExit to UNIX\n\h\t\t\tContext switch to HARDRESET\n\q\t\t\tReturns from URAID with NO-change\n\<<Misc>>\ns\t\t\tInvoke Shell\n\v filename\t\tSave the virtual memory on the filename(Not Bootable)\n\( [num]\t\t\tSets Print level\n\!\t\t\tPrints the error message passed from the emulator\n\?\t\t\tDisplay this summary"};/****OBSOLATE#define HEXNUMP(str,err)	if(((*str < '0') || (*str > '9')) \				&&((*str < 'A') || (*str > 'F'))){ \			 	printf("Illegal argument, %s\n",err); \			  	return(T); }*****/			#define ADD_RANGEP(address)		if((address < 0) || (0xFFFFFF < address)) \				 { \					printf("Address out of range.\n"); \					return(T); \				 }extern int get_package_atom();#define URMAXCOMM		512#define URMAXFXNUM		100#define URSCAN_ALINK		0#define URSCAN_CLINK		1/*** URaid G vals ***/ int URaid_scanlink= URSCAN_ALINK; int URaid_currentFX=URMAXFXNUM +1; FX *URaid_FXarray[URMAXFXNUM]; int URaid_ArrMAXIndex; char URaid_inputstring[URMAXCOMM]; char URaid_comm; char URaid_arg1[URMAXCOMM/2]; char URaid_arg2[URMAXCOMM/2]; int URaid_argnum; char *URaid_errmess;	 extern int PrintMaxLevel; /* for print level *//***********************************************************************//*	func name : parse_atomstring(string)	Written by : Takeshi Shimizu	Date:   6-May-1988	Pass the atomstring(e.g. "XCL:EVAL")	 Then Returns atomindex .	If fail to find,return -1	If there is no package prefix,it will be treated as IL:*//***********************************************************************/LispPTR parse_atomstring(string) char *string; {  char *start,*packageptr,*nameptr;  int flag=0;  int packagelen=0;  int namelen=0;  int cnt;  LispPTR aindex;  LispPTR make_atom(); for(cnt=0,start=string; *string != '\0' ; string++,cnt++)  {	if(*string ==':')	{		packagelen= cnt;		packageptr=start;		nameptr=string+1;		cnt=0;		*string=0;	}  } if(packagelen==0) { /* treat as IL: */	nameptr=start;	namelen = cnt; } else	namelen = cnt -1;if((packagelen == 0) || (strncmp(packageptr, "IL",packagelen ) == 0))  {/* default IL: */	aindex=make_atom(nameptr,0,namelen,T);	if(aindex == 0xffffffff)	 {  printf("try IL:\n");		aindex = get_package_atom(nameptr,namelen,"INTERLISP",9,0);	 } }else	aindex = get_package_atom(nameptr,namelen,packageptr,packagelen,0);if(aindex== 0xffffffff) return(0xffffffff);printf("INDEX : %d \n",aindex& 0xffff);return(aindex & 0xffff);}/***********************************************************************//*	func name : uraid_commclear()	Written by : Takeshi Shimizu	Date:   6-May-1988		Clear Command buffer	*//***********************************************************************/uraid_commclear(){ /****OBSOLATE register int i;  for(i=0;i <URMAXCOMM ; i++)	URaid_inputstring[i]=0;  for(i=0;i < URMAXCOMM/2 ; i++){	URaid_arg1[URMAXCOMM/2]=0; 	URaid_arg2[URMAXCOMM/2]=0;  }******/  bzero(URaid_inputstring,URMAXCOMM);  bzero(URaid_arg1,URMAXCOMM/2);  bzero(URaid_arg2,URMAXCOMM/2);  URaid_comm=0;  URaid_argnum=0;}/***********************************************************************//*	func name : uraid_commands()	Written by : Takeshi Shimizu	Date:   6-May-1988		Execute URaid commands		To continue, return T		To exit, return NIL*//***********************************************************************/uraid_commands(){ int num,address,val,tmp; LispPTR index; DefCell *defcell68k;  if(URaid_argnum == -1){	/* disp next FX */	if(URaid_currentFX > URaid_ArrMAXIndex)	{	  printf("There is no more stack.\n");	  return(T);	}	else	{	  sf(URaid_FXarray[URaid_currentFX++]); 	  return(T);	}  }  switch(URaid_comm)  {	/*** Displaying STACK stuff */	case 'c' :	stack_check(0);			break;	case 'C' :	all_stack_dump(0,0,T);			break;	case 'f' :	/**if((URaid_arg1[0] < '0') || (URaid_arg1[0] > '9')){			   printf("Illegal argument,Not number\n");			    return(T);			}**/			if(URaid_argnum==1) /* f comm only */			{			  printf("DUMP-STACK: f decmal-FXnumber\n");			  return(T);			}			if( sscanf(URaid_arg1,"%d",&num) <= 0)			{ /* com read fails */			  printf("Illegal argument, not decimal number\n");			  return(T);			}			if((num > URaid_ArrMAXIndex) || (num < 0))			{			  printf("Such frame doesn't exist.\n");			  return(T);			}			sf(URaid_FXarray[num]);			URaid_currentFX = num+1;			break;	case 'k' :	if((URaid_arg1[0] == 'A')||(URaid_arg1[0] == 'a'))			URaid_scanlink =URSCAN_ALINK;			else if((URaid_arg1[0] == 'C')||(URaid_arg1[0] == 'c'))				URaid_scanlink = URSCAN_CLINK;			else 				printf("Link type should be A or C\n");			break;	case 'l' :	if(URaid_argnum ==1)			{				bt(); /* default case CURRENTFX */				return(T);			}			switch(URaid_arg1[0])			{			 case 'k' :	printf("IFP->KBDFXP :\n");					bt1(Addr68k_from_StkOffset(InterfacePage->kbdfxp));					break;			 case 'm' :	printf("IFP->MISCFXP :\n");					bt1(Addr68k_from_StkOffset(InterfacePage->miscfxp));					break;			 case 'r' :	printf("IFP->RESETFXP :\n");					bt1(Addr68k_from_StkOffset(InterfacePage->resetfxp));					break;			 case 'g' :	printf("IFP->GCFXP :\n");					bt1(Addr68k_from_StkOffset(InterfacePage->gcfxp));					break;			 case 'p' :	printf("IFP->FAULTFXP :\n");					bt1(Addr68k_from_StkOffset(InterfacePage->faultfxp));					break;			 case 'u' :	bt(); 					break;			 default :	printf("2nd argument should be k,m,r,g,p,u or null.\n");					break;			} /* switch end */		break;	/* Displaying the memory contents stuff */	case 'a' :	 /* GETTOPVAL */				if(URaid_argnum != 2)				{					printf("GETTOPVAL: a litatom\n");					return(T);				}				if((index = parse_atomstring(URaid_arg1))==						0xffffffff ){					printf("No such atom\n");					return(T);				}				print(*((LispPTR*)GetVALCELL68k(index)));				break;	case 'd' : /* DEFCELL */				if(URaid_argnum != 2){					printf("GETD: d litatom\n");					return(T);				}				if((index = parse_atomstring(URaid_arg1))==						0xffffffff){					printf("No such atom\n");					return(T);				}				defcell68k= (DefCell*)GetDEFCELL68k(index);				if(defcell68k->ccodep) {				  printf("{CCODEP}0x%x \n",defcell68k->defpointer);				  return(T);				}				else{				  print(defcell68k->defpointer);				  return(T);				}				break;	case 'M' :	 /* Machine States */				printf("TOS   : 0x%x \n",TopOfStack);				printf("CSTKP : 0x%x \n",LADDR_from_68k(CurrentStackPTR));				printf("PVAR  : 0x%x \n",LADDR_from_68k(PVar));				printf("IVAR  : 0x%x \n",LADDR_from_68k(IVar));				printPC(); putchar('\n');				break;	case 'm' :	/* MOVED */				if(URaid_argnum != 3){					printf("MOVED: m <from funcname> <to funcname>\n");					return(T);				}				{ DefCell *fromfunc,*tofunc;				  LispPTR fromindex,toindex;					if((fromindex = parse_atomstring(URaid_arg1))==0xffffffff){					printf("No such function (from)\n");					return(T);					}					if((toindex = parse_atomstring(URaid_arg2))==0xffffffff){					printf("No such function (to)\n");					return(T);					}					fromfunc= (DefCell*)GetDEFCELL68k(fromindex);					tofunc= (DefCell*)GetDEFCELL68k(toindex);					tofunc->defpointer = fromfunc->defpointer;					print(toindex);					printf(" is smashed with ");					print(fromindex);putchar('\n');				}								break;	case 'O' :		{ /* print instance from Laddr. Not documented */					int objaddr;					if(URaid_argnum ==1)					{						printf("PRINT-INSTANCE: O HEX-LispAddress\n");						return(T);					}					if(sscanf(URaid_arg1,"%x",&objaddr)						<=0) {						printf("Arg not HEX number\n");						return(T);					}					print(objaddr);				}				break;	case 't' :   /* Object TYPE */				if(URaid_argnum != 2){					printf("PRINTTYPENAME: t Xaddress\n");					return(T);				}				/**HEXNUMP(URaid_arg1,"Not Address");**/				if(sscanf(URaid_arg1,"%x",&address)<=0)				{					printf("Arg not HEX number\n");					return(T);				}				ADD_RANGEP(address);				switch(address >> 16) {				 case ATOMS_HI : printf("{ATOM}");						 printf("0x%x\n",address);						 break;				 case STK_HI : printf("{STK}");						 printf("0x%x\n",address);						 break;					 case PLIS_HI : printf("{PLIST}");						 printf("0x%x\n",address);						 break;					 case FPTOVP_HI : printf("{FPTOVP}");						 printf("0x%x\n",address);						 break;					 case PNP_HI : printf("{PNP}");						 printf("0x%x\n",address);						 break;					 case DEFS_HI : printf("{DEF}");						 printf("0x%x\n",address);						 break;					 case VALS_HI : printf("{VAL}");						 printf("0x%x\n",address);						 break;				 case DISPALY_HI :				 case DISPALY_HI+1 :printf("{DISPLAY}");						 printf("0x%x\n",address);						 break;				 default:					num= GetTypeNumber(address);					putchar('{');					print_atomname((DLword)GetDTD(num));					putchar('}');					break;				} /* switch end */				break;#define GetPROPCELL68k(index)	((LispPTR *)Plistspace + (index) )	case 'p' :	 /* propaty lisp */				if(URaid_argnum != 2){					printf("GETPROPLIST : p litatom\n");					return(T);				}				if((index = parse_atomstring(URaid_arg1)) ==						0xffffffff){					printf("No such atom\n");					return(T);				}				print(*(GetPROPCELL68k(index)) & 0xffffff );				break;	case 'w' :  /* Disp CurrentFunc name & PC */				doko();				break;#define XDUMPW 8	case 'x' :	  /* HEX dump "x Xaddress Xnum" */				/* Obsolate 				HEXNUMP(URaid_arg1,"Not Address");				HEXNUMP(URaid_arg2,"Not number");				***/				if(URaid_argnum==1)				{ /* for help */				  printf("HEX-DUMP: x Xaddress [Xnum]\n");				  return(T);				}				if(sscanf(URaid_arg1,"%x",&address)<=0)				{ /* arg1 not HEX */				  printf("Arg(Xaddress) not Xaddress\n");				  return(T);				}				switch(sscanf(URaid_arg2,"%x",&num))				{				  case -1 :  /* Use defaultval for word-num */				 	    num = XDUMPW;					    break;				  case 0  : /* Illegal number */					    printf("Arg(Xnum) not Xnum\n");					    return(T);					    break;				  default : break;				}				if(num < 0)				{				  printf("Dump words num should be positive\n");				  return(T);				}				/* Address range check */				ADD_RANGEP(address);				ADD_RANGEP(address+num);				{ int i;				  DLword *ptr,*endptr;					ptr=(DLword*)Addr68k_from_LADDR(address);					endptr=ptr+num;					while(ptr < endptr)					{						printf("0x%x : ",LADDR_from_68k(ptr));						for(i=0;							((ptr <endptr)&& (i<XDUMPW)) ;ptr++,i++) 						{							printf("%4x ",*ptr);						}						putchar('\n');					}				}				break;	case '@' :		/* SETTOPVAL */				if(URaid_argnum != 3){					printf("SETTOPVAL: @ litatom Decimal-val\n");					return(T);				}				if((index = parse_atomstring(URaid_arg1))						== 0xffffffff){					printf("No such atom\n");					return(T);				}				if (strncmp(URaid_arg2, "NIL",3 ) == 0)					{val=NIL;}				else if (*URaid_arg2== 'T')  val=ATOM_T;				else { 					if(sscanf(URaid_arg2,"%d",&val) == -1){						printf(" Bad value \n");						return(T);					}					else {						if((val < -65536)||(65535 < val)){							printf("Bad Val range\n"); 							return(T);						}						if(val >=0)							val |= S_POSITIVE;						else {  val = val & 0xffff;							val |= S_NEGATIVE;						}					}				}				printf("Old value is ");				print(*((LispPTR*)GetVALCELL68k(index)));				putchar('\n');				*((LispPTR*)GetVALCELL68k(index)) =(LispPTR) val;				print(val);				break;		case '<' :		if(URaid_argnum != 3){					printf("Mem modify: < Xaddre Xval\n");					return(T);				}				/* Assignment */				/* OBSOLATE				HEXNUMP(URaid_arg1,"Not Address");				HEXNUMP(URaid_arg2,"Not Proper Value");				***/				if(sscanf(URaid_arg1,"%x",&address) <=0)				{				  printf("Arg(Xaddress) not Xaddress\n");				  return(T);				}				if(sscanf(URaid_arg2,"%x",&val) <=0)				{				  printf("Arg(Xval) not Xaddress\n");				  return(T);				}				ADD_RANGEP(address);				if(val <0 || val > 0xffff){					printf("Xval invalid (16 bit range exceeded).\n");					return(T);				}				{ DLword *ptr;					ptr =(DLword*)Addr68k_from_LADDR(address);					*ptr=val;					printf("0x%x : 0x%x\n",address,*ptr);				}				break;/****MISC ****/	case 'q' :		/* return with do Nothing */				printf("Return to Lisp?[confirm](Y or N)<");				{int c;				  c= getchar();				  if((c=='Y')||(c=='y')) {					/*TopOfStack = NIL;*/					return(NIL);				   }				}				fflush(stdin);				URaid_currentFX=URMAXFXNUM +1;				return(T);				break;	case 'h' :		/* HARDRESET */				printf("HARDRESET?[confirm](Y or N)<");				{ int c;				  c= getchar();				  if((c=='Y')||(c=='y'))				  {					/*PC+= 3; for currentfx->pc ajust:MOve to subr */					contextsw(ResetFXP,2,0);					/*PC -= 3;  in subr.c it increments by 3 */					fflush(stdin);					return(NIL); /* return to dispatch */				  }				}				fflush(stdin);				break;	case 'e' :		/* exit to UNIX */				printf("Exit to UNIX?[confirm](Y or N)<");				{ int c;				  c= getchar();				  if((c=='Y')||(c=='y'))					exit(0);				}				fflush(stdin);				URaid_currentFX=URMAXFXNUM +1;				break;	case 's' :		/* SHELL */				system("/bin/sh -i");				return(T);				break;	case 'v' :		if(URaid_argnum != 2){					printf("VMEMSAVE: v filename (it's NOT bootable)\n");					return(T);				}				pr_rop(ScreenBitMap,0,0,DisplayWidth,					DisplayHeight,PIX_CLR,ScreenBitMap,0,0);				pr_rop( ScreenBitMap, 0, 0, DisplayWidth, 					DisplayHeight,PIX_SRC | PIX_DST,						HideBitMap, 0, 0);				if(vmem_save(URaid_arg1) != NIL){				  pr_rop(ScreenBitMap,0,0,DisplayWidth,					DisplayHeight,PIX_CLR,ScreenBitMap,0,0);				  printf("VMEMSAVE fails\n");				}				else {				  pr_rop(ScreenBitMap,0,0,DisplayWidth,					DisplayHeight,PIX_CLR,ScreenBitMap,0,0);				  printf("VMEMSAVE finished, but it's not bootable\n");				}				break;	case '(' :		if(URaid_argnum==1) num = 2;								else if((URaid_arg1[0] < '0') || (URaid_arg1[0] > '9')){					printf("Illegal argument, not number\n");			 		return(T);				}				else 					sscanf(URaid_arg1,"%d",&num);						PrintMaxLevel = num;				printf("PrintLevel is set to %d.",num);				break;	case '?' :		printf("%s\n",URaid_summary);				break;	case '!' :		printf("Error message is: %s \n",URaid_errmess);				break;	default :  printf("Unsupported command.\n");			break;  } /* switch end */return(T);}/***********************************************************************//*	func name :  device_before_raid()	Written by : Takeshi Shimizu	Date:  	 6-May-1988	This shoul be calld before invoking URaid.*//***********************************************************************/device_before_raid(){	int keytrans;	int size;	int munmapstat;	struct pixrect *fb;	extern char *alloc_hideDISP();	char *valloc();		int_timer_off();	win_setcursor(LispWindowFd, &InvisibleCursorBitMap);#ifdef KBINT	int_io_close(LispWindowFd);#endif#ifdef ETHERINT	int_io_close(ether_fd);#endif#ifdef RS232INT	int_io_close(RS232C_Fd);#endif	mess_reset();	if( (LispKbdFd = open( LispScreen.scr_kbdname , O_RDWR)) == -1){		fprintf( stderr, "can't open %s\n", LispScreen.scr_kbdname);		return( -1 );	}	keytrans = TR_EVENT;	/* keyboard encodes key */	if(ioctl( LispKbdFd, KIOCTRANS, &keytrans)== -1){		fprintf( stderr, "Error at ioctl errnoo =%d\n", errno);		return( -1 );	}	close( LispKbdFd );        close( LispWindowFd ); 	size = ((DisplayWidth * DisplayHeight / 8 + (getpagesize()-1) ) 			& -getpagesize());	if((HideDisp68k= valloc(size)) == 0){		  printf("can't valloc hide space\n");		  return(-1);	}	HideBitMap= mem_point(DisplayWidth,DisplayHeight,1,HideDisp68k);	pr_rop( HideBitMap, 0,0,DisplayWidth,DisplayHeight,PIX_SRC,		ScreenBitMap,0,0);	pr_rop(ScreenBitMap,0,0,DisplayWidth,DisplayHeight,		PIX_CLR,ScreenBitMap,0,0);	return(0);}/**char *alloc_hideDISP(size)int size;{ char *retaddr; switch(*STORAGEFULLSTATE_word & 0xffff)  {	case SFS_NOTSWITCHABLE :		if((retaddr =valloc(size)) ==0){			fprintf(stderr,"can't alloc hide disp\n");		 }		break;	case 0 :	case SFS_SWITCHABLE :		retaddr = 		 (char*)Addr68k_from_LADDR((*ArraySpace2_word) & 0xffffff);		printf("Hidespace inside Lisp(2)\n");		break;	case SFS_ARRAYSWITCHED :		retaddr=(char*)Addr68k_from_LADDR(*Next_Array_word & 0xffff);;		printf("Hidespace inside Lisp(3)\n");		break;	case SFS_FULLYSWITCHED :		if((int)Addr68k_from_LADDR(*Next_MDSpage_word & 0xffff) 			- (int)Addr68k_from_LADDR(*Next_Array_word & 0xffff)		 >size) {			retaddr= (char*)Addr68k_from_LADDR(*Next_Array_word & 0xffff);			printf("Hidespace inside Lisp(4)\n");		 }		else if((retaddr=valloc(size)) ==0){			fprintf(stderr,"can't alloc hide disp\n");			 }			printf("Hidespace new\n");		break;	default : printf("Illegal data in STORAGEFULLSTATE\n");		  retaddr=0;		 break;  }  return(retaddr);}****//***********************************************************************//*	func name : device_after_raid()	Written by : Takeshi Shimizu	Date:   6-May-1988 	This should be called when returning LISP.	*//***********************************************************************/#define KB_ALLUP		0xffffdevice_after_raid(){extern DLword  *EmMouseX68K, *EmMouseY68K, *EmKbdAd068K, *EmRealUtilin68K;extern DLword  *EmKbdAd168K,*EmKbdAd268K,*EmKbdAd368K,*EmKbdAd468K,*EmKbdAd568K;	LispReadFds = 0;	if(re_init_display(DISPALY_OFFSET,65536 * 16 *2)== -1)		return(-1);	set_cursor();	init_keyboard();	init_ether();	int_init(); 	LispReadFds |= (1 << LispWindowFd) ;	int_timer_on(); *EmKbdAd068K= *EmRealUtilin68K= *EmKbdAd168K= *EmKbdAd268K= *EmKbdAd368K= *EmKbdAd468K= *EmKbdAd568K=KB_ALLUP ; return(0);} /* device_after_raid *//***********************************************************************//*	func name :re_init_display(lisp_display_addr, display_max)			int lisp_display_addr, display_max;	Written by : Takeshi Shimizu	Date:   6-May-1988 	This should be called when returning LISP.	Only called by device_after_raid	*//***********************************************************************/re_init_display(lisp_display_addr, display_max)	int lisp_display_addr, display_max;{	int mmapstat, size;	mess_init();	if( (LispWindowFd = win_screennew( &LispScreen )) == -1){		fprintf( stderr, "init_display: can't create LispWindow\n");		return( -1 );	}	else {#ifdef KBINT		int_io_open(LispWindowFd);		fcntl(LispWindowFd, F_SETFL, fcntl(LispWindowFd, F_GETFL, 0)| FNDELAY);#endif	}	init_cursor(); 	size = ((DisplayWidth * DisplayHeight / 8 + (getpagesize()-1) ) 			& -getpagesize());	mmapstat = 		mmap( DisplayRegion68k,		      size,		      PROT_READ | PROT_WRITE, MAP_SHARED, FrameBufferFd, 0 );		if(mmapstat != 0){		fprintf( stderr, "re_init_display: ERROR at mmap system call\n");		fprintf( stderr, "errno = %d\n\n", errno );		return( 0 );	}	pr_rop(ScreenBitMap,0,0,DisplayWidth,DisplayHeight,PIX_CLR,		ScreenBitMap,0,0);	pr_rop( ScreenBitMap, 0, 0, DisplayWidth, DisplayHeight,PIX_SRC | PIX_DST,		HideBitMap, 0, 0);	pr_close(HideBitMap);	free(HideDisp68k);	return(0);}