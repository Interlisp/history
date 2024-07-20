/* @(#) rawrs232c.h Version 1.2 (4/21/92). copyright Venue & Fuji Xerox  */
/*  (c) CopyRight Fuji Xerox 1989  Maiko Project */
/* FILE: rawrs232c.h REL.1 SCCSID:1.1 Date: 4/12/91 10:59:23 */
/* SCCS file: /medley/project1/emul/SCCS/s.rawrs232c.h  */

/*****************************************************/
/*
	rawrs232c.h

	By Takeshi Shimizu

	CopyRight Fuji Xerox Co_,LTD 1991


*/
/*****************************************************/

typedef struct raw232cparam {
LispPTR BauRate;
LispPTR BitsPerChar;
LispPTR Parity;
LispPTR LocalLine;
LispPTR NoOfStopBits;
LispPTR FlowCnt;
LispPTR InEOL;
LispPTR OutEOL;
LispPTR InputMaxBell;
LispPTR Canon;
LispPTR Echo;
LispPTR ModemStatusLine;
LispPTR RTSCTSCnt;
} RawRSParam;


#define RAW_RS_NONE 	1
#define RAW_RS_ODD 	2
#define RAW_RS_EVEN 	3
#define RAW_RS_XON 	2
#define RAW_RS_CR 	1
#define RAW_RS_LF 	2
#define RAW_RS_CRLF 	3
 