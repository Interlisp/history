h31982s 00011/00001/00315d D 1.5 91/09/18 16:48:03 nilsson 5 4c Fixes the X_TCP_PORT problem we had in 2.0 /jalres 00062/00036/00254d D 1.4 91/09/16 17:09:49 sybalsky 4 3c es 00098/00052/00192d D 1.3 91/09/13 16:30:24 sybalsky 3 2c Fix open_socket to take only 2 args (and to pay attn to them right), and to take socket# as a server # (so connect_to_host adds 6000 to it.)es 00048/00013/00196d D 1.2 91/09/13 15:41:31 sybalsky 2 1c Make Open-socket return NIL if it fails, add our copyright, fix some formatting.es 00209/00000/00000d D 1.1 91/08/26 14:58:22 sybalsky 1 0c date and time created 91/08/26 14:58:22 by sybalskyeuUf e 0tTI 1/* %Z% %M% Version %I% (%G%). copyright venue & Fuji Xerox  */static char *id = "%Z% %M%	%I% %G%	(venue & Fuji Xerox)";/**** Copyright (C) 1988 by Fuji Xerox co.,Ltd.. Al rights reserved.**		Author: Mitsunori Matsuda*		Date  : November 2, 1988*/I 2/************************************************************************//*									*//*	(C) Copyright 1989, 1990, 1991 Venue. All Rights Reserved.	*//*	Manufactured in the United States of America.			*//*									*//*	The contents of this file are proprietary information 		*//*	belonging to Venue, and are provided to you under license.	*//*	They may not be further distributed or disclosed to third	*//*	parties without the specific permission of Venue.		*//*									*//************************************************************************/E 2#include <stdio.h>#include <sys/time.h>#include <sys/file.h>I 4#include <errno.h>I 5#include <X11/Xproto.h>E 5E 4#include "lispemul.h"#include "arith.h"#include "address68k.h"#include "lisptypes.h"#include "lispmap.h"#define min(x,y)  (((x) > (y)) ? (y) : (x))I 4	/***********************************************************/	/*	       L S t r i n g T o C S t r i n g		   */	/*							   */	/*  Convert a lisp string to a C string up to MaxLen long. */	/***********************************************************/E 4#define	LStringToCString(Lisp, C, MaxLen ,Len)				\  {									\    OneDArray	*arrayp;						\    char	*base;							\    short	*sbase;							\    int	i;								\									\    arrayp = (OneDArray *)(Addr68k_from_LADDR((unsigned int)Lisp));	\D 2    Len = min(MaxLen, arrayp->totalsize);				\E 2I 2    Len = min(MaxLen, arrayp->fillpointer);				\E 2									\    switch(arrayp->typenumber)						\      {									\        case THIN_CHAR_TYPENUMBER:					\	    base = ((char *)						\	            (Addr68k_from_LADDR((unsigned int)arrayp->base)))	\	           + ((int)(arrayp->offset));				\	    for(i=0;i<Len;i++)						\	        C[i] = base[i];						\	    C[Len] = '\0';						\	    break;							\									\        case FAT_CHAR_TYPENUMBER:					\	    sbase = ((short *)						\		     (Addr68k_from_LADDR((unsigned int)arrayp->base)))	\	           + ((int)(arrayp->offset));				\	    base = (char *)sbase;					\	    for(i=0;i<Len*2;i++)					\	        C[i] = base[i];						\	    C[Len*2] = '\0';						\	    break;							\									\        default:							\	    error("LStringToCString can not handle\n");			\      }									\  }I 5#define FGetNum(ptr, place) { \             if(((ptr) & 0xff0000)== S_POSITIVE) {(place) = ((ptr) & 0xffff);}\        else if(((ptr) & 0xff0000)== S_NEGATIVE) {(place) = (int)((ptr)| 0xffff0000);}\        else {return(NIL);}}E 5#define MAX_NAME_LEN 256D 4static char XServer_Name[MAX_NAME_LEN];static int XPort_Number = 0;E 4I 4static char XServer_Name[MAX_NAME_LEN];	/* Name of host with X server */static int XPort_Number = 0;		/* Display # to ask for on it */E 4D 4int XServer_Fd = -1;E 4I 4int XServer_Fd = -1;	/* The socket for the X server */E 4extern DLword *Lisp_world;I 2/************************************************************************//*									*/I 3/*			O p e n _ S o c k e t				*/E 3/*									*/I 3/*	Open a connection to an X server, by calling the CLX routine	*//*	"connect_to_server".  Returns T if successful, and NIL if not.	*//*	The socket's fd is left in XServer_Fd, a global, so only one	*//*	server connection can be open at one time (FIX THIS).		*/E 3/*									*/I 3/*	args[0] - The lisp string name of the host the server is on	*//*	args[1] - The SMALLP server-number we're connecting to.		*/E 3/*									*/D 3/*									*/E 3/************************************************************************/E 2Open_Socket( args )D 3LispPTR *args;{E 3I 3  LispPTR *args;  {E 3#ifdef TRACED 3	printf( "TRACE: Open_Socket()\n" );E 3I 3    printf( "TRACE: Open_Socket()\n" );E 3#endifD 2	int length;E 2I 2    int length;E 2D 2	LStringToCString( args[0], XServer_Name, MAX_NAME_LEN, length );	XPort_Number = (int) (0xff & args[2] );E 2I 2    LStringToCString( args[0], XServer_Name, MAX_NAME_LEN, length );D 3    XPort_Number = (int) (0xff & args[2] );E 3I 3D 5    XPort_Number = (int) (0xffff & args[1] );E 5I 5    FGetNum( args[1], XPort_Number );    XPort_Number -= X_TCP_PORT;E 5E 3E 2D 2	if( XServer_Fd == -1 ) {		XServer_Fd = connect_to_server( XServer_Name, XPort_Number );E 2I 2    if( XServer_Fd == -1 )      {	XServer_Fd = connect_to_server( XServer_Name, XPort_Number );E 2D 2		{ int res;		res = fcntl( XServer_Fd, F_GETFL );		res |= FNDELAY;		res = fcntl( XServer_Fd, F_SETFL, res );		}	} /* end if(XServer_Fd) */E 2I 2	if (XServer_Fd < 0) /* error in connect. */	  {	    perror("connecting to X server");	    return(NIL);	  }E 2D 2	return( ATOM_T );E 2I 2	{ /* Make it non-blocking I/O */	  int res;	  res = fcntl( XServer_Fd, F_GETFL );	  res |= FNDELAY;	  res = fcntl( XServer_Fd, F_SETFL, res );	}      } /* end if(XServer_Fd) */E 2I 2    return( ATOM_T );E 2}I 2I 3/************************************************************************//*									*/I 4/*			C l o s e _ S o c k e t				*/E 4/*									*/I 4/*	Close the socket connection to the X server.			*/E 4/*									*/D 4/*									*//*									*/E 4/************************************************************************/E 3E 2Close_Socket()D 3{	int stat;E 3I 3  {    int stat;E 3#ifdef TRACE D 3	printf( "TRACE: Close_Socket()\n" );E 3I 3    printf( "TRACE: Close_Socket()\n" );E 3#endifD 3	if( (stat = close( XServer_Fd )) == -1 ) {		XServer_Fd = -1;		return( NIL );	} else {		XServer_Fd = -1;		return( ATOM_T );	}E 3I 3    if( (stat = close( XServer_Fd )) == -1 )      { /* close failed; return NIL, but squash the old fd anyhow */	XServer_Fd = -1;I 5	perror("Close_socket");E 5	return( NIL );      }    else      { /* close succeeded; return T. */	XServer_Fd = -1;	return( ATOM_T );      }E 3} /* end Close_Socket */D 3typedef struct {		DLword nil[22]; /* Packet header */		DLword length;	/* Request byte lenght */		char   data[592]; /* Data body */} PACKET;E 3I 3/************************************************************************//*									*/I 4/*			   R e a d _ S o c k e t			*/E 4/*									*/I 4/*	Read up to 1 packet's worth from the X-server socket.		*/E 4/*									*/D 4/*									*//*									*/E 4/************************************************************************/typedef struct  { /* Format for an X-server packet */    DLword nil[22];     /* Packet header */    DLword length;	/* Request byte length */    char   data[592];   /* Data body */  } PACKET;E 3#define PACKET_DEFOFFSET 46#define PACKET_MAXSIZE   638Read_Socket( args )D 3LispPTR *args;{	PACKET *packet;	char   *buffer;	int    length	     , actlen;E 3I 3  LispPTR *args;  {    PACKET *packet;    char   *buffer;    int    length         , actlen;E 3#ifdef TRACED 3	printf( "TRACE: Read_Socket()\n" );E 3I 3    printf( "TRACE: Read_Socket()\n" );E 3#endifD 3	if( XServer_Fd >= 0 ) {E 3I 3    if( XServer_Fd >= 0 )      {E 3D 3		packet = (PACKET *) Addr68k_from_LADDR( args[0] );E 3I 3	packet = (PACKET *) Addr68k_from_LADDR( args[0] );E 3D 3		if( (length = (int)(packet->length)-PACKET_DEFOFFSET) > 0 ) {			buffer = &(packet->data[0]);E 3I 3	if( (length = (int)(packet->length)-PACKET_DEFOFFSET) > 0 )	  {	    buffer = &(packet->data[0]);E 3D 3			if( (actlen = read( XServer_Fd, buffer, length )) > 0 ) {				packet->length = (DLword)(actlen							+ PACKET_DEFOFFSET);				return(ATOM_T); E 3I 3	    if( (actlen = read( XServer_Fd, buffer, length )) > 0 )	      {		packet->length = (DLword)(actlen + PACKET_DEFOFFSET);		return(ATOM_T); 	      } /* end if(actlen) */I 4	    if(actlen < 0) /* error !*/	      {		if ((errno != EWOULDBLOCK) & (errno != EINTR))		  perror("reading X connection");		return(NIL);	      }E 4E 3D 3			} /* end if(actlen) */E 3I 3	  } /* end if(length) */E 3D 3		} /* end if(length) */E 3I 3      } /* end if( fd ) */E 3I 4E 4D 3	} /* end if( fd ) */E 3I 3    return( NIL );E 3D 3	return( NIL );E 3I 3  } /* end Read_Socket */E 3D 3} /* end Read_Socket */E 3I 3/************************************************************************//*									*/I 4/*			  W r i t e _ S o c k e t			*/E 4/*									*/I 4/*	Write a packet of information to the X server's socket.		*/E 4/*									*/D 4/*									*//*									*/E 4/************************************************************************/E 3Write_Socket( args )D 4LispPTR *args;{	PACKET *packet;	char *buffer;	int length	  , actlen;E 4I 4  LispPTR *args;  {    PACKET *packet;    char *buffer;    int length      , actlen;E 4#ifdef TRACED 4	printf( "TRACE: Write_Socket()\n" );E 4I 4    printf( "TRACE: Write_Socket()\n" );E 4#endifD 4	if( XServer_Fd >= 0 ) {E 4I 4    if( XServer_Fd >= 0 )      {E 4D 4		packet = (PACKET *) Addr68k_from_LADDR( args[0] );E 4I 4	packet = (PACKET *) Addr68k_from_LADDR( args[0] );E 4D 4		if( (length = (int)(packet->length)-PACKET_DEFOFFSET) > 0 ) {			buffer = &(packet->data[0]);E 4I 4	if( (length = (int)(packet->length)-PACKET_DEFOFFSET) > 0 )	  {	    buffer = &(packet->data[0]);E 4D 4			if( (actlen = write( XServer_Fd, buffer, length )) > 0 ) {				packet->length = (DLword)(actlen 							+ PACKET_DEFOFFSET);				return(ATOM_T); E 4I 4	    if( (actlen = write( XServer_Fd, buffer, length )) > 0 )	      {		packet->length = (DLword)(actlen + PACKET_DEFOFFSET);		return(ATOM_T); E 4D 4			} /* end if( actlen ) */E 4I 4	      } /* end if( actlen ) */	    if(actlen < 0) /* error !*/	      {		if (errno != EINTR) perror("writing X connection");		return(NIL);	      }E 4D 4		}  /* end if(length) */E 4D 4	}  /* end if( fd ) */E 4I 4	  }  /* end if(length) */E 4D 4	packet->length = 0;	return(NIL);E 4I 4      }  /* end if( fd ) */E 4D 4} /* end Write_Socket */E 4I 4    packet->length = 0;    return(NIL);E 4D 4extern int KBDEventFlg;E 4I 4  } /* end Write_Socket */E 4I 3I 4E 4/************************************************************************//*									*/D 4/*		K b d _ T r a n s i t i o n				*/E 4I 4/*		      K b d _ T r a n s i t i o n			*/E 4/*									*/I 4/*	Stuff a key transition into the C-level buffer from Lisp.	*/E 4/*									*/I 4/*	args[0] - the key number (in lisps terms? Not sure)		*//*	args[1] - upflg -- is it an up or down-transition? 		*/E 4/*									*//************************************************************************/I 4extern int KBDEventFlg;E 4E 3Kbd_Transition( args )D 3LispPTR *args;E 3I 3  LispPTR *args;I 5	/* args[0] is key-number */	/* args[1] is up-flg     */E 5E 3D 4	/* args[0] is key-number */	/* args[1] is up-flg     */E 4D 3{	DLword key_number;E 3I 3  {    DLword key_number;E 3	D 3	key_number = (DLword)(args[0] & 0xff);	if( args[1] ) 		kb_trans( key_number, 1 );	else 		kb_trans( key_number, 0 );E 3I 3D 4    key_number = (DLword)(args[0] & 0xff);E 4I 4    key_number = (DLword)(args[0] & 0xffff);E 4    if( args[1] ) kb_trans( key_number, 1 );    else kb_trans( key_number, 0 );E 3D 3	DoRing();	if( (KBDEventFlg += 1) > 0 ) {		Irq_Stk_End = Irq_Stk_Check = 0;	}E 3I 3    DoRing();I 4    /* If there's something for lisp to do, ask for an interrupt: */  E 4    if( (KBDEventFlg += 1) > 0 ) Irq_Stk_End = Irq_Stk_Check = 0;E 3D 4} /* end Kbd_Transition */E 4I 4  } /* end Kbd_Transition */E 4E 1