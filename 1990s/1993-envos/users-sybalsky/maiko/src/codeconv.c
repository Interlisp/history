/* @(#) codeconv.c Version 1.2 (4/21/92). copyright venue & Fuji Xerox  */
static char *id = "@(#) codeconv.c	1.2 4/21/92	(venue & Fuji Xerox)";
static char *id = "@(#) codeconv.c 1.3  7/1/91 13:49:02 ";
/*  (c) CopyRight Fuji Xerox 1991  Maiko for VISION Project */
/* FILE: codeconv.c REL.1 SCCSID:1.3  */
/* SCCS file: /medley/project1/emul/SCCS/s.codeconv.c  */

/* @(#) dbh.pc Version 1.0 (3/23/90). copyright Fuji Xerox  */

/*
 * Copyright (C) 1990 by Fuji Xerox Co., Ltd. All rights reserved.
 * 
 * Author	:	Shinichi Miyamoto
 */

/*************************************************/
/* NSFatchar string <-> EUC character string	 */
/* conversion program 				 */
/* file name : char_codes.c			 */
/* 26,Jun,'89					 */
/* 5,Aug,'89					 */
/* by Shinichi Miyamoto				 */
/* 10,Jan,'91					 */
/* 27,Feb,'91					 */
/* by Sumie Kurihara (FXIS)			 */
/*************************************************/

#include <stdio.h>

#define EUCMASK		0x80
#define EUCUNMASK	0x7F
#define MASK8BIT	0x00FF
#define TABLESIZE	256

int 
FatcharNStoEUC(ns_ptr, ns_len, euc_ptr)
	unsigned char  *ns_ptr, *euc_ptr;
	int             ns_len;
{
	int             i;
	int             euc_len;
	unsigned short  ns, euc;
	unsigned short  ns_euc();

#ifdef DEBUG
	unsigned char  *ptr;
	ptr = euc_ptr;
	printf("FatcharNStoEUC start\n");
	printf("ns_len = %d\n", ns_len);
	for (i = 0; i < ns_len*2; i++)
		printf("%x ", ns_ptr[i]);
	printf("\n");
#endif

	/* ns_len convert to byte count */
	ns_len *= 2;

	for (i = euc_len = 0; i < ns_len; i += 2) {
		ns = *ns_ptr++ * TABLESIZE;
		ns += *ns_ptr++;
		euc = ns_euc(ns);
		if (euc / TABLESIZE) {
			/* 16 bit charactor */
			*euc_ptr++ = euc / TABLESIZE;
			*euc_ptr++ = euc % TABLESIZE;
			euc_len += 2;
		} else {
			/* ASCII charactor */
			*euc_ptr++ = euc % TABLESIZE;
			++euc_len;
		}
	}

	*euc_ptr++ = '\0';

#ifdef DEBUG
	printf("FatcharNStoEUC end\n");
	printf("euc_len = %d\n", euc_len);
	for (i = 0; i < euc_len; i++)
		printf("%x ", ptr[i]);
	printf("\n");
#endif

	return (euc_len);
}

int 
ThincharNStoEUC(ns_ptr, ns_len, euc_ptr)
	unsigned char  *ns_ptr, *euc_ptr;
	int             ns_len;
{
	int             i;
	int             euc_len = 0;
	unsigned short  ns, euc;
	unsigned short  ns_euc();

#ifdef DEBUG
	unsigned char  *ptr;
	ptr = euc_ptr;
	printf("ThincharNStoEUC start\n");
	printf("ns_len = %d\n", ns_len);
	for (i = 0; i < ns_len; i++)
		printf("%x ", ns_ptr[i]);
	printf("\n");
#endif

	/* ns_len convert to byte count */
	for (i = euc_len = 0; i < ns_len; i++) {
		ns = *ns_ptr++;
		euc = ns_euc(ns);
		if (euc / TABLESIZE) {
			/* 16 bit charactor */
			*euc_ptr++ = euc / TABLESIZE;
			*euc_ptr++ = euc % TABLESIZE;
			euc_len += 2;
		} else {
			/* ASCII charactor */
			*euc_ptr++ = euc % TABLESIZE;
			++euc_len;
		}
	}

	*euc_ptr++ = '\0';

#ifdef DEBUG
	printf("ThincharNStoEUC end\n");
	printf("euc_len = %d\n", euc_len);
	for (i = 0; i < euc_len; i++)
		printf("%x ", ptr[i]);
	printf("\n");
#endif

	return (euc_len);
}

int 
EUCtoFatcharNS(euc_ptr, ns_ptr)
	unsigned char  *euc_ptr, *ns_ptr;
{
	int             i;
	int             ns_len;
	unsigned short  euc, ns;
	unsigned short  euc_ns();

#ifdef DEBUG
	printf("EUCtoFatcharNS start\n");
	for (i = 0; i < strlen(euc_ptr); i++)
		printf("%x ", euc_ptr[i]);
	printf("\n");
#endif

	i = 0;
	while (euc = *euc_ptr++) {
		if (euc & EUCMASK) {
			/* 16 bit charactor */
			euc *= TABLESIZE;
			euc += *euc_ptr++;
		}

		ns = euc_ns(euc);

		ns_ptr[i++] = ns / TABLESIZE;
		ns_ptr[i++] = ns % TABLESIZE;
	}
	ns_len = i / 2;

#ifdef DEBUG
	printf("EUCtoFatcharNS end\n");
	printf("ns_len = %d\n", ns_len);
	for (i = 0; i < ns_len*2; i++)
		printf("%x ", ns_ptr[i]);
	printf("\n");
#endif

	return (ns_len);
}

int 
EUCstrlen(euc_ptr)
	char           *euc_ptr;
{
	int             len = 0;

#ifdef DEBUG
	int	i;

	printf("EUCstrlen start\n");
	for (i = 0; i < strlen(euc_ptr); i++)
		printf("%x ", euc_ptr[i]);
	printf("\n");
#endif

	while (*euc_ptr)
		if (*euc_ptr & EUCMASK) {
			/* 16 bit charactor */
			len += 2;
			*euc_ptr++;
			*euc_ptr++;
		} else {
			/* ASCII charactor */
			len++;
			*euc_ptr++;
		}

#ifdef DEBUG
	printf("EUCstrlen end\n");
	printf("len = %d\n", len);
#endif

	return (len);
}