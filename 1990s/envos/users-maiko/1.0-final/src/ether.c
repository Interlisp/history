/* This is G-file @(#) ether.c Version 2.6 (7/18/88). copyright Xerox & Fuji Xerox  */static char *id = "@(#) ether.c	2.6 7/18/88";/* * *	ether.c, Tue Oct 27 17:24:13 1987 *	Copyright (C) 1987 by Fuji Xerox Co., Ltd. All rights reserved. */#include <stdio.h>#include <ctype.h>#include <sys/file.h>#include <sys/types.h>#include <sys/time.h>#include <sys/socket.h>#include <net/if.h>#include <netdb.h>#include <netinet/in.h>#include <netinet/if_ether.h>#include <net/nit.h>#include <sys/ioctl.h>#include <sys/mbuf.h>#include <nlist.h>#include "lispemul.h"#include "lispmap.h"#include "emulglobal.h"#include "lispglobal.h"#include "address68k.h"#include "ether.h"u_int	EtherReadFds;int ether_fd = -1;	/* file descriptor for ether socket */u_char ether_host[6] = {0,0,0,0,0,0};	/* 48 bit address of this node */u_char broadcast[6] = {255, 255, 255, 255, 255, 255};int ether_bsize = 0;	/* if nonzero then a receive is pending */u_char *ether_buf;	/* address of receive buffer */u_char nit_buf[2000];	/* the current chunk read from NIT (one packet) */#define	PacketTypeIP	0x0800#define	PacketTypeARP	0x0806#define	PacketTypeRARP	0x8035#define	PacketTypeXNS	0x0600#define	PacketTypePUP	0x0200#define	PacketType3TO10	0x0201int ether_in = 0;	/* number of packets received */int ether_out = 0;	/* number of packets sent */static struct nit_ioc nioc;/********************************************************************** *	ether_suspend(args) 175/70/0 *	suspend nit socket not to receive any packets **********************************************************************/ether_suspend(args)LispPTR	  args[];{	if (ether_fd == -1)		return(NIL);	nioc.nioc_typetomatch = NT_NOTYPES;	if ( ioctl(ether_fd, SIOCSNIT, &nioc) != 0) {		printf("ether_suspend: ioctl failed\n");		close(ether_fd);		ether_fd = -1;	}	return(ATOM_T);} /* ether_suspend *//********************************************************************** *	ether_resume(args) 175/71/0 *	resume nit socket to receive all types of packets **********************************************************************/ether_resume(args)LispPTR	  args[];{	if (ether_fd == -1)		return(NIL);	nioc.nioc_typetomatch = NT_ALLTYPES;	if ( ioctl(ether_fd, SIOCSNIT, &nioc) != 0) {		printf("ether_resume: ioctl failed\n");		close(ether_fd);		ether_fd = -1;	}	return(ATOM_T);} /* ether_resume *//********************************************************************** *	ether_ctrlr(args) 175/72/0 *	return T if ether controller is available **********************************************************************/ether_ctrlr(args)LispPTR	  args[];{	if (ether_fd < 0) return(NIL);	return(ATOM_T);} /* ether_ctrlr *//********************************************************************** *	ether_reset(args) 175/73/0 *	reset ether controller and disable receipt of packets **********************************************************************/ether_reset(args)LispPTR	  args[];{	/*	 *	Reset the Ethernet controller	 *	Disable receipt of Ethernet packets.	 */	int i;	char hostnumber[6];	if (ether_fd < 0) {return(NIL);}	/* JRB - host number check removed here; if ether_fd is open here,		net is on... */	ether_bsize = 0;	/* deactivate receiver */	return(ATOM_T);} /* ether_reset *//********************************************************************** *	ether_get(args) 175/74/2 max_words,buffer_addr *	active the reciever **********************************************************************/ether_get(args)LispPTR	args[]; {	/*	 *	Set up the Ethernet driver to receive a packet.  The driver	 *	will copy the next incoming packet	 *	into the packet buffer pointed to by	 *	BufferAddr. If the Ethernet driver has buffered an	 *	incoming packet, the icb may be signalled immediately.	 *	Any incoming packets which are too big to fit in the buffer	 *	will be discarded.	 *	args[0] : MaxWordCount	 *	args[1] : LispBufferAddr	 */	LispPTR MaxByteCount;	MaxByteCount = 2 * (0xFFFF & args[0]); /* words to bytes */	if (ether_fd >= 0 && (MaxByteCount > 0)) {		ether_bsize = MaxByteCount;		ether_buf = (u_char *)Addr68k_from_LADDR(args[1]);	}    return (ATOM_T);} /* ether_get *//********************************************************************** *	ether_send(args) 175/75/2 max_words,buffer_addr *	send a packet **********************************************************************/ether_send(args)LispPTR	args[];{	/*	 *	Send a packet.	 */	struct sockaddr sa;	int offset = sizeof (sa.sa_data);	LispPTR MaxByteCount;	char *BufferAddr; /* buffer address pointer(in native address) */	MaxByteCount = 2 * (0xFFFF & args[0]); /* words to bytes */	BufferAddr = (char *)Addr68k_from_LADDR(args[1]);	if (ether_fd >= 0) {		sa.sa_family = AF_UNSPEC; /* required for the NIT protocol */		bcopy(BufferAddr, sa.sa_data, offset);		if ( sendto(ether_fd, BufferAddr+offset, MaxByteCount-offset, 0,			&sa, sizeof(sa)) == (MaxByteCount-offset) );		else perror("Lisp Ether: sendto");		ether_out++;	}	return(ATOM_T);} /* ether_send *//********************************************************************** *	ether_setfilter(args) 175/75/1 filterbits *	check whether a packet has come. if does, notify iocb **********************************************************************/ether_setfilter(args)LispPTR	args[];{	return(NIL);} /* ether_setfilter *//********************************************************************** *	ether_debug() *	returns the ethernet statistics. **********************************************************************/int estat[3];int *ether_debug(){	estat[0] = 0;	if (ether_fd < 0) return(NIL);	printf("fd %d bsize %d buf %X icb %X in %d out %d\n ",ether_fd,ether_bsize,(int)ether_buf,IOPage->dlethernet[3],ether_in,ether_out);	return(estat);} /* end ether_debug */static	struct timeval	EtherTimeout = {	0, 0	};/********************************************************************** *	check_ether() *	checks an incomming packet **********************************************************************/check_ether(){	/*	 *	If receiver active then check if any packets are	 *	available from the ethernet.  If so, read the packet	 *	and signal the icb and return T.	 */        static int  rfds;	int result, fromlen;	struct nit_hdr header;	int posi, i;  rfds = EtherReadFds;  if( select(32, &rfds, NULL, NULL, &EtherTimeout) >= 0 ){    if( (ether_fd >= 0) && (rfds & (1 << ether_fd)) ){	if (ether_bsize > 0) { 	 result = read (ether_fd, nit_buf, sizeof(nit_buf));	 /* enumerate the NIT headers until the packet is found */	 posi = 0;	 while (posi < result) {		bcopy(&nit_buf[posi], &header, sizeof(header));		posi += sizeof(header);		switch (header.nh_state) {		case NIT_CATCH:			fromlen = header.nh_datalen;			if (check_filter(&nit_buf[posi])) {			   bcopy(&nit_buf[posi], &ether_buf[0], fromlen);			   ether_bsize = 0; /* deactivate receiver */			   ether_in++;			   IOPage->dlethernet[3] = fromlen;			   return(ATOM_T);			}			posi += fromlen;			break;		case NIT_QUIET:		case NIT_NOMBUF:	/* ignor all the other header types */		case NIT_NOCLUSTER:		case NIT_NOSPACE:		case NIT_SEQNO: break;		}	 }	}    }  }  return(NIL);} /* end check_ether *//********************************************************************** *	chech_filter(buffer) *	see if this packet passes the current filter setting **********************************************************************/check_filter(buffer)u_char* buffer;{	/* braodcast packets */	if (ether_addr_equal(buffer, broadcast))		switch(((short*)buffer)[6]) {			case PacketTypeIP: return(0);			case PacketTypeARP: return(0);			default: return(1);		};	/* my address */	if (ether_addr_equal(buffer, ether_host))		switch(((short*)buffer)[6]) {			case PacketTypeIP: return(0);			case PacketTypeARP: return(0);			default: return(1);		};	return(0);}/********************************************************************** *	ether_addr_equal(add1, add2) *	checks ethernet addresses equality **********************************************************************/ether_addr_equal(add1, add2)u_char add1[], add2[];{	register int i;	for(i=0; i<6; i++)		if (add1[i] != add2[i]) return(0);	return(1);}/********************************************************************** *	init_uid() *	sets effective user-id to real user-id **********************************************************************/init_uid(){	int rid;	rid = getuid();	seteuid(rid);}/********************************************************************** *	init_ether() *	open nit socket, called from main before starting BCE. *      init_ifpage_ether() *      sets Lisp's idea of \my.nsaddress. Clears it if ether not *      enabled **********************************************************************/init_ifpage_ether(){ InterfacePage->nshost0 = (DLword)((ether_host[0] << 8) + ether_host[1]); InterfacePage->nshost1 = (DLword)((ether_host[2] << 8) + ether_host[3]); InterfacePage->nshost2 = (DLword)((ether_host[4] << 8) + ether_host[5]);}/* this needs to be a global so the name can be set by main() in Ctest */struct sockaddr_nit snit;init_ether(){/* JRB - This code will have to be a bit different for SUN 4.0; the		probable differences are in commented-out code below	(not ifdefed because they're untested...)*/if (ether_fd < 0) {	/* it's not open yet, try and open it;		if it's already open here, it was opened by lispgo and		all the appropriate stuff was done to snit by Ctest.	*/	if (getuid() != geteuid()){		if ((ether_fd = socket(AF_NIT, SOCK_RAW, NITPROTO_RAW)) >= 0) {		/* 4.0: socket -> open("/dev/nit", O_BOTH) */		/* it's open, now query it and find out its name and address */		/* JRB - must document that Maiko uses the first net board as		found by SIOCGIFCONF (see if(4)).  Maybe we need an option to		specify which net board (suspect more than one net board on a		Maiko machine will be rare, but...).		*/		struct ifconf if_data;		struct ifreq ifbuf[20];			if_data.ifc_len = sizeof(ifbuf);		if_data.ifc_req = ifbuf;		/* 4.0 - before the SIOCGIFCONF, do:			bzero(ifbuf, sizeof(ifbuf))		*/		if(ioctl(ether_fd, SIOCGIFCONF, &if_data) < 0) {			perror("Couldn't GIFCONF socket; Net is off");			close(ether_fd);			ether_fd = -1;			return(NIL);		}		/* got its name, copy it into snit */		strcpy(snit.snit_ifname, if_data.ifc_req[0].ifr_name);		/* 4.0, before the SIOCGIFADDR, do:			ioctl(ether_fd, NIOCBIND, &if_data.ifc_req[0])		*/		/* now for the address */		if(ioctl(ether_fd, SIOCGIFADDR, &if_data.ifc_req[0]) < 0) {			perror("Couldn't GIFADDR socket: Net is off");			close(ether_fd);			ether_fd = -1;			return(NIL);		}		bcopy(if_data.ifc_req[0].ifr_addr.sa_data, ether_host, 6);		init_uid();		}	}}if (ether_fd >= 0) {	/* bind the socket to an interface */	snit.snit_family = AF_NIT;	bind(ether_fd, &snit, sizeof(snit));	/* establish the operating modes */	bzero(&nioc, sizeof(nioc));	nioc.nioc_bufspace = 20000;	nioc.nioc_chunksize = 50; /* small chunks so each packet read */	nioc.nioc_typetomatch = NT_ALLTYPES;	nioc.nioc_snaplen = 32767;	nioc.nioc_flags = 0;	if (ioctl(ether_fd, SIOCSNIT, &nioc) != 0) {		printf("init_ether: ioctl failed\n");	    close(ether_fd);	    ether_fd = -1;	    return(NIL);	}	EtherReadFds |= (1 << ether_fd);#ifdef  DEBUG	printf("init_ether: **** Ethernet starts ****\n");#endif}}#define MASKWORD1	0xffffcheck_sum(args) register LispPTR *args; /* args[0] LispPTR base; */ /* args[1] LispPTR nwords; */ /* args[2] LispPTR initsum; */{  register  LispPTR checksum;  register  DLword *address;  register int nwords; address=(DLword*)Addr68k_from_LADDR(*args++); nwords = *args ++; if( *args != NIL)	checksum = (*args) & MASKWORD1; else	checksum = 0; for(;nwords > (S_POSITIVE); address++,nwords--)  {	checksum= checksum + *address;	if(checksum > 0xffff) 		checksum = (checksum & 0xffff) +1; /* add carry */			if(checksum >0x7fff) /* ROTATE LEFT 1 */		checksum= ((checksum & 0x7fff)<<1) | 1 ;	else		checksum = checksum << 1;  } if(checksum == MASKWORD1) return(S_POSITIVE);/* ret 0 */ else return(S_POSITIVE|checksum);} /*check_sum */