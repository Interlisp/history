h32893s 00002/00002/00033d D 2.3 92/04/21 17:24:51 sybalsky 5 4c shortening file names for DOS \nes 00000/00000/00035d D 2.2 90/04/20 01:53:45 sybalsky 4 3c shortening file names, bulk change.es 00000/00000/00035d D 2.1 88/05/17 09:26:55 hayata 3 2c Version up to 2.1es 00002/00002/00033d D 1.2 88/03/13 15:07:36 hayata 2 1c Add SCCS key id (%Z%)es 00035/00000/00000d D 1.1 88/02/24 16:58:37 hayata 1 0c date and time created 88/02/24 16:58:37 by hayataeuUtTI 1D 2/* This is G-file %M% Version %I% (%G%). copyright Xerox & Fuji Xerox  */static char *id = "%M%	%I% %G%";E 2I 2/* This is G-file %Z% %M% Version %I% (%G%). copyright Xerox & Fuji Xerox  */static char *id = "%Z% %M%	%I% %G%";E 2/* *	Copyright (C) 1987 by Fuji Xerox Co., Ltd. All rights reserved. *//********************************************************//*	subr_k_trace()		subr----0130 for katana trace		first argument is base address of		error message in Lisp.		second argument is length of message.*//********************************************************/#include <stdio.h>#include "lispemul.h"D 5#include "address68k.h"#include "lispglobal.h"E 5I 5#include "adr68k.h"#include "lspglob.h"E 5subr_k_trace(args)	LispPTR	args[];{	int	len;	char	*base;	len = 0xFFFF & args[1];	base = (char *)Addr68k_from_LADDR(args[0]);	while(len-- > 0)		putc(*base++ , stderr);	putc('\n', stderr);	return(0);}E 1