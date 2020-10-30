h21802s 00011/00018/00145d D 2.8 92/11/25 20:19:13 sybalsky 10 9c Fixing extra text in endifs => comment.\nes 00000/00000/00163d D 2.7 92/04/21 16:29:20 sybalsky 9 8c shortening file names for DOSes 00012/00001/00151d D 2.6 90/06/04 13:00:39 sybalsky 8 7c reformat, copyrightes 00001/00001/00151d D 2.5 89/03/30 13:01:13 sybalsky 7 6c more byte swapping.es 00033/00028/00119d D 2.4 89/03/29 14:40:08 sybalsky 6 5c Added byte-swapped definition (which hadn't been byte-swapped before)es 00069/00002/00078d D 2.3 89/03/08 14:05:36 sybalsky 5 4c added byteswapped defn, which isn't really swapped yet.es 00002/00002/00078d D 2.2 89/01/09 17:51:59 shih 4 3c spellinges 00000/00000/00080d D 2.1 88/05/17 09:18:13 hayata 3 2c Version up to 2.1es 00001/00001/00079d D 1.2 88/03/13 13:22:01 hayata 2 1c Add SCCS key id (%Z%)es 00080/00000/00000d D 1.1 88/02/23 18:36:39 hayata 1 0c date and time created 88/02/23 18:36:39 by hayataeuUtTI 1D 2/* This is G-file %M% Version %I% (%G%). copyright Xerox & Fuji Xerox  */E 2I 2D 4/* This is G-file %Z% %M% Version %I% (%G%). copyright Xerox & Fuji Xerox  */E 4I 4D 8/* %Z% %M% Version %I% (%G%). copyright envos & Fuji Xerox  */E 8I 8D 10/* %Z% %M% Version %I% (%G%). copyright Venue & Fuji Xerox  */E 10I 10/* %Z% %M% Version %I% (%G%). copyright Venue   */E 10I 10E 10/************************************************************************//*									*/D 10/*	Copyright 1989, 1990 Venue, Fuji Xerox Co., Ltd, Xerox Corp.	*/E 10I 10/*	(C) Copyright 1989-92 Venue. All Rights Reserved.		*//*	Manufactured in the United States of America.			*/E 10/*									*/D 10/*	This file is work-product resulting from the Xerox/Venue	*//*	Agreement dated 18-August-1989 for support of Medley.		*/E 10I 10/*	The contents of this file are proprietary information 		*//*	belonging to Venue, and are provided to you under license.	*//*	They may not be further distributed or disclosed to third	*//*	parties without the specific permission of Venue.		*/E 10/*									*//************************************************************************/D 10E 8E 4E 2/* *	Copyright (C) 1987 by Fuji Xerox Co., Ltd. All rights reserved. *D 4 *	Auther	:	Osamu Nakamura	E 4I 4 *	Author	:	Osamu NakamuraE 4 *//**************************************************************** *								* *	iopage.h		July 6, 1987 by Osamu Nakamura	* *								* ****************************************************************/E 10#ifndef IOPAGE_DEFINED#define IOPAGE_DEFINED	(1)D 5E 5I 5#ifndef BYTESWAP/* Normal definition, for big-indian machines */E 5typedef struct iopage {	DLword	 dummy0[022];	DLword   dlmaintpanel;        DLword   dlfloppycmd;        DLword   dlttyportcmd;        DLword   dlprocessorcmd;        DLword   newmousestate;        DLword   dlbeepcmd;        DLword   dlrs232cmisccommand;        DLword   dlrs232cputflag;	DLword   dlrs232cgetflag;	DLword   dummy1[6];	DLword   dlfloppy;	DLword   dlttyout;	DLword   dummy2;	DLword   dlttyin;	DLword   dummy3;	DLword   dlprocessor2;	DLword   dlprocessor1;	DLword   dlprocessor0;	DLword   newmousex;	DLword   newmousey;	DLword   dlbeepfreq;	DLword   dlrs232cparametercsblo;	DLword   dlrs232cparametercsbhi;	DLword   dlrs232csetrs366status[3];	DLword   dlrs232cputcsblo;	DLword   dlrs232cputcsbhi;	DLword   dlrs232cgetcsblo;	DLword   dlrs232cgetcsbhi;	DLword   dlrs232cdevicestatus;	DLword   dlrs232cparameteroutcome;	DLword   dltodvalid;	DLword   dltodlo;	DLword   dltodhi;	DLword   dltodlo2;	DLword   dlmousex;	DLword   dlmousey;	DLword   dlutilin;	DLword   dlkbdad0;	DLword   dlkbdad1;	DLword   dlkbdad2;	DLword   dlkbdad3;	DLword   dlkbdad4;	DLword   dlkbdad5;	DLword   dllsepimagecsb[040];	DLword   dliophardwareconfig;	DLword   dummy4[013];	DLword   dlrs232cparametercsblo_11;	DLword   dlrs232cparametercsbhi_11;	DLword   dlrs232csetrs366status_11[016] ;	DLword   dummy5[074];	DLword   dlmagtape[4];	DLword   dlethernet[014];	DLword   dummy6[037];	DLword   dldispinterrupt;	DLword   dldispcontrol;	DLword   dldispborder;	DLword   dlcursorx;	DLword   dlcursory;	DLword   dlcursorbitmap[020];} IOPAGE;D 5E 5I 5#else	/***********************************************************/	/*       Byte-swapped/word-swapped version, for 386i       */	/***********************************************************/typedef struct iopage {	DLword	 dummy0[022];D 6	DLword   dlmaintpanel;E 6        DLword   dlfloppycmd;D 6        DLword   dlttyportcmd;E 6I 6	DLword   dlmaintpanel;	/* hi */E 6        DLword   dlprocessorcmd;D 6        DLword   newmousestate;E 6I 6        DLword   dlttyportcmd;	/* hi */E 6        DLword   dlbeepcmd;D 6        DLword   dlrs232cmisccommand;E 6I 6        DLword   newmousestate;	/* hi */E 6        DLword   dlrs232cputflag;D 6	DLword   dlrs232cgetflag;	DLword   dummy1[6];E 6I 6        DLword   dlrs232cmisccommand;	/* hi */D 7	DLword	 dummy0;E 7I 7	DLword	 dummy1b;E 7	DLword   dlrs232cgetflag;	/* hi */	DLword   dummy1[4];E 6	DLword   dlfloppy;D 6	DLword   dlttyout;E 6I 6	DLword	 dummy1a;	/* hi */E 6	DLword   dummy2;D 6	DLword   dlttyin;E 6I 6	DLword   dlttyout;	/* hi */E 6	DLword   dummy3;D 6	DLword   dlprocessor2;E 6I 6	DLword   dlttyin;	/* hi */E 6	DLword   dlprocessor1;D 6	DLword   dlprocessor0;E 6I 6	DLword   dlprocessor2;	/* hi */E 6	DLword   newmousex;D 6	DLword   newmousey;E 6I 6	DLword   dlprocessor0;	/* hi */E 6	DLword   dlbeepfreq;D 6	DLword   dlrs232cparametercsblo;E 6I 6	DLword   newmousey;	/* hi */E 6	DLword   dlrs232cparametercsbhi;D 6	DLword   dlrs232csetrs366status[3];E 6I 6	DLword   dlrs232cparametercsblo;	/* hi */	DLword   dlrs232csetrs366status[2];E 6	DLword   dlrs232cputcsblo;D 6	DLword   dlrs232cputcsbhi;E 6I 6	DLword	 dlrs232csetrs366statusa; /* hi */E 6	DLword   dlrs232cgetcsblo;D 6	DLword   dlrs232cgetcsbhi;E 6I 6	DLword   dlrs232cputcsbhi;	/* hi */E 6	DLword   dlrs232cdevicestatus;D 6	DLword   dlrs232cparameteroutcome;E 6I 6	DLword   dlrs232cgetcsbhi;	/* hi */E 6	DLword   dltodvalid;D 6	DLword   dltodlo;E 6I 6	DLword   dlrs232cparameteroutcome;	/* hi */E 6	DLword   dltodhi;D 6	DLword   dltodlo2;E 6I 6	DLword   dltodlo;	/* hi */E 6	DLword   dlmousex;D 6	DLword   dlmousey;E 6I 6	DLword   dltodlo2;	/* hi */E 6	DLword   dlutilin;D 6	DLword   dlkbdad0;E 6I 6	DLword   dlmousey;	/* hi */E 6	DLword   dlkbdad1;D 6	DLword   dlkbdad2;E 6I 6	DLword   dlkbdad0;	/* hi */E 6	DLword   dlkbdad3;D 6	DLword   dlkbdad4;E 6I 6	DLword   dlkbdad2;	/* hi */E 6	DLword   dlkbdad5;I 6	DLword   dlkbdad4;	/* hi */E 6	DLword   dllsepimagecsb[040];D 6	DLword   dliophardwareconfig;	DLword   dummy4[013];	DLword   dlrs232cparametercsblo_11;E 6I 6	DLword	 dummy4a;	DLword   dliophardwareconfig;	/* hi */	DLword   dummy4[012];E 6	DLword   dlrs232cparametercsbhi_11;I 6	DLword   dlrs232cparametercsblo_11;	/* hi */E 6	DLword   dlrs232csetrs366status_11[016] ;	DLword   dummy5[074];	DLword   dlmagtape[4];	DLword   dlethernet[014];D 6	DLword   dummy6[037];E 6I 6	DLword   dummy6[036];E 6	DLword   dldispinterrupt;D 6	DLword   dldispcontrol;E 6I 6	DLword	 dummy6a;E 6	DLword   dldispborder;D 6	DLword   dlcursorx;E 6I 6	DLword   dldispcontrol;	/* hi */E 6	DLword   dlcursory;I 6	DLword   dlcursorx;	/* hi */E 6	DLword   dlcursorbitmap[020];} IOPAGE;D 10#endif BYTESWAPE 10I 10#endif /* BYTESWAP */E 10E 5#endifE 1