/* This is G-file @(#) subr0374.c Version 2.3 (4/21/92). copyright Xerox & Fuji Xerox  */
static char *id = "@(#) subr0374.c	2.3 4/21/92";
/*
 *	Copyright (C) 1987 by Fuji Xerox Co., Ltd. All rights reserved.
 */
/********************************************************/
/*
	subr_k_trace()

		subr----0130 for katana trace
		first argument is base address of
		error message in Lisp.
		second argument is length of message.
*/
/********************************************************/

#include <stdio.h>
#include "lispemul.h"
#include "adr68k.h"
#include "lspglob.h"

subr_k_trace(args)
	LispPTR	args[];
{
	int	len;
	char	*base;

	len = 0xFFFF & args[1];
	base = (char *)Addr68k_from_LADDR(args[0]);
	while(len-- > 0)
		putc(*base++ , stderr);
	putc('\n', stderr);
	return(0);
}

