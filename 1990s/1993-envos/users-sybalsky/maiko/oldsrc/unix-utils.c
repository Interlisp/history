/* @(#) unix-utils.c Version 1.25 (3/20/92). copyright Venue & Fuji Xerox  */
static char *id = "@(#) unix-utils.c	1.25 3/20/92";


/************************************************************************/
/*									*/
/*	Copyright 1989, 1990 Venue, Fuji Xerox Co., Ltd, Xerox Corp.	*/
/*									*/
/*	This file is work-product resulting from the Xerox/Venue	*/
/*	Agreement dated 18-August-1989 for support of Medley.		*/
/*									*/
/************************************************************************/


/* unix utilities subrs */

#include <pwd.h>
#include <signal.h>
#include <sys/time.h>
#ifndef HPUX
#include <strings.h>
#endif HPUX
#include <stdio.h>
#include "lispemul.h"
#include "address68k.h"
#include "lisptypes.h"
#include "lispglobal.h"
#include "osmessage.h"
#include "keyboard.h"


/************************************************************************/
/*									*/
/*		l i s p _ s t r i n g _ t o _ c _ s t r i n g		*/
/*									*/
/*	converts lisp string up to maximum length; returns 0 if it	*/
/*	succeeds, -1 if error (not a simple string, or too long, or	*/
/*	contains NS characters outside charset 0).			*/
/*									*/
/************************************************************************/

int lisp_string_to_c_string(Lisp, C, length)
	LispPTR Lisp;
	char	*C;
	int	length;
{
	register OneDArray	*arrayp;
	register char	*base;

	if (GetTypeNumber(Lisp) != TYPE_ONED_ARRAY) {return (-1);}

	arrayp = (OneDArray *)(Addr68k_from_LADDR(Lisp));
	if (arrayp->fillpointer >= length) {return(-1);} /* too long */

	switch(arrayp->typenumber){
	case THIN_CHAR_TYPENUMBER:
		base = ((char *)(Addr68k_from_LADDR(arrayp->base))) +
		       ((int)(arrayp->offset));
#ifndef BYTESWAP
		strncpy(C, base, arrayp->fillpointer);
#else
	{  register int i,length ;
	   register char *dp;
		for(i=0,dp=C, length = arrayp->fillpointer;
			i<length;i++)				
		{*dp++ =(char)(GETBYTE(base++));}
	}
#endif BYTESWAP
		C[arrayp->fillpointer] = '\0';
		return 0;
	default:
		return -1;
	}
}



/************************************************************************/
/*									*/
/*		c _ s t r i n g _ t o _ l i s p _ s t r i n g		*/
/*									*/
/*	copies a C string into an existing Lisp string (it does not 	*/
/*	create a new Lisp string).  Returns 0 if succeeds, -1 if	*/
/*	error (Lisp string is not a simple string, or not long enough,	*/
/*	or is FATP).  The string will end with a null, which the	*/
/*	length must include.						*/
/*									*/
/************************************************************************/

int c_string_to_lisp_string(C, Lisp)
	LispPTR Lisp;
	char	*C;
{
	register OneDArray	*arrayp;
	char	*base;
	register int	length;

	length = strlen(C);
	if (GetTypeNumber(Lisp) != TYPE_ONED_ARRAY) {return (-1);}

	arrayp = (OneDArray *)(Addr68k_from_LADDR(Lisp));
	if (arrayp->totalsize < length+1) {return(-1);}
	    /* too short for C string */

	switch(arrayp->typenumber){
	case THIN_CHAR_TYPENUMBER:
		base = ((char *)(Addr68k_from_LADDR(arrayp->base))) +
		       ((int)(arrayp->offset));
#ifndef BYTESWAP
		strcpy(base, C);
#else
	{ register int i;
	  register char *dp;
		for(i=0,dp = C;i<length + 1;i++)
		{
			GETBYTE(base++) = *dp++;
		}
	}
#endif BYTESWAP
		return 0;
	default:
		return -1;
	}
}



/************************************************************************/
/*									*/
/*		    c h e c k _ u n i x _ p a s s w o r d		*/
/*									*/
/*	Check this guy's password against what he gave us.		*/
/*									*/
/************************************************************************/

check_unix_password(args)
     LispPTR args[];
{
  struct passwd *pwd;
  char *password, *getpass();
  char salt[3];
  char name[100], pass[100];

  if (lisp_string_to_c_string(args[0], name, sizeof name)) {return NIL;}
  if (lisp_string_to_c_string(args[1], pass, sizeof pass)) {return NIL;}

  if ((pwd = getpwnam(name)) == 0) {
    return(NIL);	/* can't find entry for name */
  }
  salt[0] = pwd->pw_passwd[0];
  salt[1] = pwd->pw_passwd[1];
  salt[2] = '\0';
  if (strcmp(crypt(pass, salt), pwd->pw_passwd) == 0)
    return(ATOM_T);
  else
    return(NIL);
}



/************************************************************************/
/*									*/
/*									*/
/*									*/
/*									*/
/*									*/
/************************************************************************/

unix_username(args)
     LispPTR args[];
{
  struct passwd *pwd;

  if ((pwd = getpwuid(getuid())) == NULL)
    return NIL;
  if (c_string_to_lisp_string(pwd->pw_name, args[0]))
    return NIL;
  return ATOM_T;
}



/************************************************************************/
/*									*/
/*			u n i x _ g e t p a r m				*/
/*									*/
/*	Given a string name for a configuration parameter, return	*/
/*	a string with the value for that parameter.			*/
/*									*/
/*	PARAMETER	MEANING/VALUES					*/
/*									*/
/*	MACH		What kind of processor we're running on		*/
/*			(sparc, mc68020, or i386 possible)		*/
/*									*/
/*	ARCH		The kind of machine we're running on		*/
/*			(sun4, sun386, sun3 possible)			*/
/*									*/
/*	DISPLAY		What kind of display we're running with		*/
/*			(X, BUFFERED, DIRECT possible)			*/
/*									*/
/*	HOSTNAME	Name of the machine we're running on.		*/
/*									*/
/*	LOGNAME		Login ID of the user running Lisp.		*/
/*									*/
/*	FULLUSERNAME	??						*/
/*									*/
/*	HOSTID		Machine serial# or Ether ID.			*/
/*									*/
/*									*/
/************************************************************************/

char* getenv();

unix_getparm(args)
  LispPTR         args[];
  {
    char            envname[20], result[128], *envvalue;
    if (lisp_string_to_c_string(args[0], envname, sizeof envname))
    	return NIL;
    if (strcmp(envname, "MACH") == 0)
      {
#if defined(sparc)
	envvalue = "sparc";
#else
#if defined(I386)
	envvalue = "i386";
#else
#ifdef RS6000
	envvalue = "rs/6000";
#else
#ifdef HP9000
	envvalue = "hp9000";
#else
#ifdef ISC
	envvalue = "i386";
#ifdef RISCOS
	envvalue = "mips";
#else
	envvalue = "mc68020";
#endif
#endif
#endif
#endif
#endif
#endif
      }
    else if (strcmp(envname, "ARCH") == 0)
      {
#if defined(sparc)
	envvalue = "sun4";
#else
#if defined(I386)
	envvalue = "sun386";
#else
#ifdef RS6000
	envvalue = "rs/6000";
#else
#ifdef HP9000
	envvalue = "hp9000";
#else
#ifdef ISC
	envvalue = "i386";
#ifdef RISCOS
	envvalue = "mips";
#else	
	envvalue = "sun3";
#endif
#endif
#endif
#endif
#endif
#endif
      } 
    else if (strcmp(envname, "DISPLAY") == 0)
      {
#if defined(XWINDOW)
	envvalue = "X";
#else
#if defined(DISPLAYBUFFER)
	envvalue = "BUFFERED";
#else	
	envvalue = "DIRECT";
#endif DISPLAYBUFFER
#endif XWINDOW

      } 
    else if (strcmp(envname, "HOSTNAME") == 0) 
      {
	if (gethostname(result, sizeof result)) return NIL;
	envvalue = result;
      } 
    else if (strcmp(envname, "LOGNAME") == 0)
      {
	struct passwd  *pwd;
	if ((pwd = getpwuid(getuid())) == NULL) return NIL;
	envvalue = pwd->pw_name;
      } 
    else if (strcmp(envname, "FULLUSERNAME") == 0)
      {
	struct passwd  *pwd;
	if ((pwd = getpwuid(getuid())) == NULL) return NIL;
	envvalue = pwd->pw_gecos;
      }
    else if (strcmp(envname, "HOSTID") == 0)
      {
	sprintf(result, "%x", gethostid());
	envvalue = result;
      }
    else return NIL;

    if (c_string_to_lisp_string(envvalue, args[1])) return NIL;
    return ATOM_T;
  }



/************************************************************************/
/*									*/
/*									*/
/*									*/
/*									*/
/*									*/
/************************************************************************/

unix_getenv(args)
	LispPTR         args[];
{
	char            envname[20], *envvalue;
	if (lisp_string_to_c_string(args[0], envname, sizeof envname))
		return NIL;
	envvalue = getenv(envname);
	if (!envvalue)
		return NIL;
	if (c_string_to_lisp_string(envvalue, args[1]))
		return NIL;
	return ATOM_T;
}



/************************************************************************/
/*									*/
/*									*/
/*									*/
/*									*/
/*									*/
/************************************************************************/

unix_fullname(args)
     LispPTR args[];
{
  struct passwd *pwd;

  if ((pwd = getpwuid(getuid())) == NULL)
    return NIL;
  if (c_string_to_lisp_string(pwd->pw_gecos, args[0]))
    return NIL;
  return ATOM_T;
}




/************************************************************************/
/*									*/
/*			s u s p e n d _ l i s p				*/
/*									*/
/*	Suspend execution, ala ^Z from the shell.			*/
/*									*/
/************************************************************************/

extern DLword  *EmMouseX68K, *EmMouseY68K, *EmKbdAd068K, 
	       *EmRealUtilin68K,*EmUtilin68K;
extern DLword  *EmKbdAd168K,*EmKbdAd268K,*EmKbdAd368K,
	       *EmKbdAd468K,*EmKbdAd568K;

suspend_lisp(args)
  LispPTR args[];
  {
    extern DLword *CTopKeyevent;
    extern LispPTR *KEYBUFFERING68k;

    DLword w, r;
    KBEVENT *kbevent;


    if(device_before_raid() < 0)
      {
	OSMESSAGE_PRINT( printf("Can't suspend\n") );
	return NIL;
      }

    OSMESSAGE_PRINT( printf("suspending...\n") );

  /* Send a terminal-stop signal to the whole process-group, not
     just this process, so that if we are running as part of a
     C-shell file the shell will be suspended too. */
#ifdef SYSVONLY
    kill(0, SIGTSTP);
#else
    killpg(getpgrp(0), SIGTSTP);
#endif SYSVONLY


    OSMESSAGE_PRINT( printf("resuming\n") );
    device_after_raid();

    r=RING_READ(CTopKeyevent);
    w=RING_WRITE(CTopKeyevent);

   /*NO CARE about event queue FULL */

    GETWORD(EmKbdAd068K)= KB_ALLUP;
    GETWORD(EmKbdAd168K)= KB_ALLUP;
    GETWORD(EmKbdAd268K)= KB_ALLUP;
    GETWORD(EmKbdAd368K)= KB_ALLUP;
    GETWORD(EmKbdAd468K)= KB_ALLUP;
    GETWORD(EmKbdAd568K)= KB_ALLUP;
    GETWORD(EmRealUtilin68K)= KB_ALLUP;

    kbevent=(KBEVENT*)(CTopKeyevent+ w);

/*    RCLK(kbevent->time); */

    kbevent->W0= GETWORD(EmKbdAd068K);
    kbevent->W1= GETWORD(EmKbdAd168K);
    kbevent->W2= GETWORD(EmKbdAd268K);
    kbevent->W3= GETWORD(EmKbdAd368K);
    kbevent->W4= GETWORD(EmKbdAd468K);
    kbevent->W5= GETWORD(EmKbdAd568K);
    kbevent->WU= GETWORD(EmRealUtilin68K);

    if(r==0) /* Queue was empty */
	((RING*)CTopKeyevent)->read=w;

    if(w >= MAXKEYEVENT)
	((RING*)CTopKeyevent)->write = MINKEYEVENT;
    else
	((RING*)CTopKeyevent)->write = w + KEYEVENTSIZE;

    return ATOM_T;
  }
