/* This is G-file @(#) ubf3.c Version 1.1 (6/2/88). copyright Xerox & Fuji Xerox  */static char *id = "@(#) ubf3.c	1.1 6/2/88";/*	ubf3.c */#include <stdio.h>#include "lispemul.h"#include "lispglobal.h"#include "address68k.h"#include "lispmap.h"/************************************************************	N_OP_ubfloat3  -- op 062062/0	POLY***********************************************************/static int constant0 = 0;unsigned int fpstatus_();N_OP_ubfloat3(arg3, arg2, arg1, alpha, error_addr)int *error_addr;int arg3;int alpha;LispPTR arg1, arg2;{register float val;register float ans;register float *fptr;register int degree;int ret;float flot;#ifdef	TRACE  printPC();  printf("TRACE: N_OP_ubfloat3()\n");#endif  val = *(float *)&arg3;  if (alpha) ERROR_EXIT(error_addr);  fpstatus_(&constant0);  if ((arg1 & 0xFF0000) != S_POSITIVE) ERROR_EXIT(error_addr);  degree = 0xFFFF & arg1;  fptr = (float *)Addr68k_from_LADDR(arg2);   ans = *((float *)fptr);  while (degree--)  ans = (ans * val) + *((float *)(++fptr));  if (fpstatus_(&constant0) & 0xf0) ERROR_EXIT(error_addr);  flot = ans;  ret = *(int *)&flot;  return(ret);}/* end N_OP_ubfloat3() */	/* end module */