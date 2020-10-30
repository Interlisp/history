/* This is G-file @(#) pilotbbt.h Version 1.2 (3/13/88). copyright Xerox & Fuji Xerox  *//* *	Copyright (C) 1987 by Fuji Xerox Co., Ltd. All rights reserved. * *	Auther	:	Osamu Nakamura *//**************************************************************** *								* *	pilotbbt.h		July 6, 1987 by Osamu Nakamura	* *								* ****************************************************************/typedef struct pilotbbt{ 	DLword	pbtdestlo;        DLword  pbtdesthi;        DLword  pbtdestbit;	/* destination bit address */        short   pbtdestbpl;     /* destination bits per line         			 *  -- distance in bits to move between items */        DLword  pbtsourcelo;        DLword  pbtsourcehi;        DLword  pbtsourcebit;	/* source bit address */        short   pbtsourcebpl;	/* source bits per line */        DLword  pbtwidth;	/* width of an item in bits */        DLword  pbtheight;	/* number of items -- height in scanlines */        unsigned 	pbtbackward : 1;         unsigned        pbtdisjoint : 1;        unsigned        pbtdisjointitems : 1;        unsigned        pbtusegray  : 1;        unsigned        pbtsourcetype : 1;        unsigned        pbtoperation : 2;        unsigned        nil  : 9;        DLword  dummy[5];	/* unused, needed to make 16-alignment */} PILOTBBT;typedef struct texturebbt{	DLword	pbtdestlo;        DLword  pbtdesthi;        DLword  pbtdestbit;     /* destination bit address */         short   pbtdestbpl;     /* destination bits per line        			 * -- distance in bits to move between items */        DLword  pbtsourcelo;        DLword  pbtsourcehi;        DLword  pbtsourcebit;	/* source bit address */        unsigned 	dummy2 : 4;        			/* overlay on pbtsourcebpl when pbtusegray */        unsigned  	pbtgrayoffset : 4;        			/* offset in gray block where bitblt should start */        unsigned  	pbtgraywidthlessone : 4; 				/* width-1 of gray block in words */        unsigned  	pbtgrayheightlessone : 4;                   				/* height-1 of gray block */        DLword  pbtwidth;	/* width of an item in bits */        DLword  pbtheight;	/* number of items -- height in scanlines */        unsigned 	pbtbackward : 1;         unsigned        pbtdisjoint : 1;        unsigned        pbtdisjointitems : 1;        unsigned        pbtusegray  : 1;        unsigned        pbtsourcetype : 1;        unsigned        pbtoperation : 2;        unsigned        nil  : 9;        DLword  dummy[5];	/* unused, needed to make 16-alignment */} TEXTUREBBT;                                        