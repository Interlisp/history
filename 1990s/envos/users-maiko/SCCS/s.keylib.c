h13790s 00005/00001/00241d D 1.8 93/02/08 14:54:53 sybalsky 8 7c Big VM (and new CDR coding) changes for 3.0 \nes 00001/00001/00241d D 1.7 92/06/26 13:49:40 sybalsky 7 6c retrofit of 386 unix changes \nes 00000/00000/00242d D 1.6 92/04/21 17:17:13 sybalsky 6 5c shortening file names for DOS \nes 00000/00000/00242d D 1.5 90/04/20 01:44:46 sybalsky 5 4c AIX:  shortening file names, bulk change.es 00035/00026/00207d D 1.4 89/12/28 15:26:02 sybalsky 4 3c es 00002/00000/00231d D 1.3 88/10/06 16:37:47 krivacic 3 2c add SCCS stamp infoes 00007/00017/00224d D 1.2 88/05/20 18:41:15 sye 2 1c noes 00241/00000/00000d D 1.1 88/05/17 18:03:19 sye 1 0c date and time created 88/05/17 18:03:19 by syeeuUtTI 3/* This is G-file %Z% %M% Version %I% (%G%). copyright Xerox & Fuji Xerox  */static char *id = "%Z% %M%	%I% %G%";I 4/************************************************************************//*									*//*	Copyright 1989, 1990 Venue, Fuji Xerox Co., Ltd, Xerox Corp.	*//*									*//*	This file is work-product resulting from the Xerox/Venue	*//*	Agreement dated 18-August-1989 for support of Medlet.		*//*									*//************************************************************************/E 4E 3I 1D 2/* This is G-file %Z% %M% Version %I% (%G%). copyright Xerox & Fuji Xerox  */static char *id = "%Z% %M%	%I% %G%";E 2/* ==============================================================================	The functions defined in this file were called by KEYMAKER.C & KEYTESTER.C		Creation Date:  May, 1988   ============================================================================== */#include <stdio.h>#include <string.h>#include <ctype.h>D 4#define	GOLDEN_RATIO_HACK			-478700649#define	ULONG_MAX					4294967295E 4I 4#define	GOLDEN_RATIO_HACK	-478700649#define	ULONG_MAX		4294967295E 4D 2/*   meaning of the symbolic constants used:E 2I 2/*   meaning of symbolic constant used:E 2D 2		FAILURE1	invalid hostid 		FAILURE2	invalid date entered from terminal 		FAILURE3	invalid key 		FAILURE4	key expired           		FAILURE99	invalid date  (* this shouldn't happen unless string format returned by ctime got changed ) */E 2I 2D 4		FAILURE2	invalid date  */E 4I 4	FAILURE2	invalid date  */E 4E 2D 2#define	FAILURE1					-1E 2D 4#define	FAILURE2					-2E 4I 4#define	FAILURE2	-2E 4D 2#define	FAILURE3					-3#define	FAILURE4					-4#define 	FAILURE99					-99E 2D 2E 2unsigned long make_verification();unsigned long date_integer16();unsigned long idate();unsigned long modify();/* ===========================================================================	MAKE_VERIFICATION forms a new 32-bit integer by messaging the two input	long integers x and y.  The number was created from the lower bits toward	higher bits. =============================================================================*/unsigned long make_verification (x , y)	unsigned long x;	unsigned long y;D 4 {	return (imod64bit(x , y , 4)         | 		  (imod64bit(x , y , 6) << 3)   | 		  (imod64bit(x , y , 13) << 6)  |		  (imod64bit(x , y , 25) << 10) | 		  (imod64bit(x , y , 30) << 15) |		  (imod64bit(x , y , 63) << 20) | 		  (imod64bit(x , y , 5)  << 26) | 		  (imod64bit(x , y , 7)  << 29) ); }E 4I 4  {    return (imod64bit(x , y , 4)         | 	    (imod64bit(x , y , 6) << 3)   | 	    (imod64bit(x , y , 13) << 6)  |	    (imod64bit(x , y , 25) << 10) | 	    (imod64bit(x , y , 30) << 15) |	    (imod64bit(x , y , 63) << 20) | 	    (imod64bit(x , y , 5)  << 26) | 	    (imod64bit(x , y , 7)  << 29) );  }E 4/* ===========================================================================	IMOD64BIT computs (IMOD X Y).	X is a 64-bit integer; x1 is the higher 32-bit while x0 is the lower 32-bit.	Y is  less than 65535.D 2	(ULONG_MAX % y) + 1 ) % y) is equivalent to (expt 2 32) % yE 2I 2	(((ULONG_MAX % y) + 1 ) % y) is equivalent to (expt 2 32) % yE 2 =============================================================================*/imod64bit (x1,x0,y)D 4	unsigned long x1,x0,y;{	return (((x0 % y) + ((x1 % y) * (((ULONG_MAX % y) + 1 ) % y)  )) % y);}E 4I 4  unsigned long x1,x0,y;  {    return (((x0 % y) + ((x1 % y) * (((ULONG_MAX % y) + 1 ) % y)  )) % y);  }E 4/* ============================================================	DATE_INTEGER16 takes a date string  and return an intger   =============================================================*/unsigned long date_integer16 (date)D 4	char *date ; {	 unsigned long const1 , const2;E 4I 4  char *date ;  {    unsigned long const1 , const2;E 4D 4	 const1 = 17152 ;	 const2 = 86400 ;I 2E 2	 return ((idate(date) - const1 ) / const2);  }E 4I 4    const1 = 17152 ;    const2 = 86400 ;    return ((idate(date) - const1 ) / const2);   }E 4/* ===================================================================	IDATE takes a date string (dd-mmm-yy or dd mmm yy) and return an	integer.  			dd -  date in decimal digits			mmm - month name in alphabetic form or decimal digits			yy  - year in decimal digits ; can be 2 or 4 digits	If date1 is before date2 then (idate date1) < (idate date2).	If date string is not valid, FAILURE2 is returned.  =====================================================================*/unsigned long idate(str)	char *str;	 {	char ds[50];	char *decdigits = {"0123456789"};	char *tokendelimiters = {" -"};	char *yptr, *mptr, *dptr, *ptr1;	int  day, month, year, maxday;	int  i, len ,s;	unsigned long days_since_day0, sec, hour;	static char *month_name[13] = {"", "JAN", "FEB", "MAR", "APR", "MAY", "JUN", "JUL", "AUG",						 "SEP", "OCT", "NOV", "DEC"};	static int  days_each_month[13]   = {0,31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};	static int  days_since_jan1st[12] = {0,31,59,90,120,151,181,212,243,273,304,334} ;	/* copy input string to a local one */	ds[0] = '\0';	strcpy(ds,str);	/* get day, month, and year string tokens */	if ((dptr = strtok(ds,   tokendelimiters)) == NULL) return FAILURE2;	if ((mptr = strtok(NULL, tokendelimiters)) == NULL) return FAILURE2;	if ((yptr = strtok(NULL, tokendelimiters)) == NULL) return FAILURE2;	/* validate year and convert it to numeric form 19xx */	if (strspn (yptr, decdigits) != strlen(yptr)) return FAILURE2;	if ((year = atoi(yptr)) <= 100) year += 1900;D 2	if (year < 1900 || year > 2037) return FAILURE2;E 2I 2	if (year < 1970 || year > 2050) return FAILURE2;E 2	/* validate month and convert it to numeric form if necessary */	if (strspn (mptr,decdigits) == (len = (strlen(mptr))))		{			/* input month is in numeric form */			if ((month = atoi(mptr)) < 1  || month > 12) return FAILURE2;		}	else		{ 		     /* input month is in alphabetic  form */		  	/* we're only interested in the first 3 chars */			if  (len > 3)  *(mptr+3) = '\0';			ptr1 = mptr;						/* make sure month name is in upper case letters */			for (i = 0 ; (s = *(ptr1+i)) != '\0' ; ++i)				if (islower(s)) *(ptr1+i) = toupper(s);			/* find out its corresponding numeric value */			for (i = 1 ; i <= 12 ; ++i)				if ( strcmp(*(month_name+i), mptr) == 0) 					{ month = i ;					  break;					};			if (i == 13) return FAILURE2;		};	/* set up maxday to be the number of days of that month */	maxday = days_each_month[month];		/* watch out for leap year */D 2	if (month == 2 && (year % 4 == 0) && (year % 100 != 0) && (year % 400 == 0)) ++maxday;E 2I 2D 7	if (month == 2 && ((year % 4 == 0) && (year % 100 != 0) || (year % 400 == 0))) ++maxday;E 7I 7	if (month == 2 && (((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0))) ++maxday;E 7E 2	/* validate day */	if ( strspn(dptr,decdigits) != strlen(dptr) || (day = atoi(dptr)) < 1 || maxday < day)		return FAILURE2;		year -= 1901;  --month;	days_since_day0 = days_since_jan1st[month] + (day - 1) + (365 * year) + (year / 4);	if (month > 1  && year % 4 == 3 && year != -1) ++days_since_day0;	hour = (24 * days_since_day0) + 7;	sec = (60 * (60 * hour)) ^ -2147483648 ;D 2	/*  printf("\n days_since_day0: %ld  hour: %ld  sec: %ld\n", days_since_day0 , hour ,sec); */E 2I 2		/* printf("\n days_since_day0: %ld  hour: %ld  sec: %ld\n", days_since_day0 , hour ,sec); */E 2	return  sec; }/* ============================================================ 	MODIFY  turns on/off certain bits of the passed	in 32-bit hostid, depending on the value of (hostid % 16).  =============================================================*/unsigned long modify (hostid)	unsigned long   hostid;{	unsigned long dividor;D 8	E 8I 8#ifdef BIGVM	hostid ^= 0xa3f5069e;#endif /* BIGVM */E 8	dividor = 16;	switch (hostid % dividor)	{		case 0: hostid =  hostid | 0x48004802;			   break;		case 1: hostid =  hostid ^ 0xfedc5793;			   break;		case 2: hostid =  hostid ^ 0x9981afe3;			   break;		case 3: hostid =  hostid & 0xffcb6ffd;			   break;		case 4: hostid =  hostid ^ 0x3489dfa8;			   break;		case 5: hostid =  hostid | 0x77012877;			   break;		case 6: hostid =  hostid & 0xefc9fffd;			   break;		case 7: hostid =  hostid | 0x22311300;			   break;		case 8: hostid =  hostid & 0xdadf8871;			   break;		case 9: hostid =  hostid ^ 0xe8c948ad;			   break;		case 10: hostid = hostid | 0x12488412;			    break;		case 11: hostid = hostid & 0xeffdea87;			    break;		case 12: hostid = hostid ^ 0xad8ce639;			    break;		case 13: hostid = hostid | 0x88221144;			    break;		case 14: hostid = hostid & 0xfffb6edd;			    break;		default: hostid = hostid ^ 0xfffddeee;			    break;	};	/*  printf("\n ** new host id:  result: %x  ", hostid); */	return hostid;}E 1