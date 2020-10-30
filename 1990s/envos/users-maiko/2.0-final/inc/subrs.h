/* @(#) subrs.h Version 2.25 (8/26/91). copyright venue & Fuji Xerox  *//* Do not edit this file! Instead, edit the list \initsubrs *//* on the lisp file LLSUBRS and then call WRITECALLSUBRS to  *//* generate a new version.                                   */#define sb_BACKGROUNDSUBR	06#define sb_CHECKBCPLPASSWORD	07#define sb_DISKPARTITION	010#define sb_DSPBOUT	011#define sb_DSPRATE	012#define sb_GATHERSTATS	013#define sb_GETPACKETBUFFER	014#define sb_LISPFINISH	015#define sb_MOREVMEMFILE	016#define sb_RAID	017#define sb_READRAWPBI	020#define sb_WRITERAWPBI	021#define sb_SETSCREENCOLOR	022#define sb_SHOWDISPLAY	023#define sb_PUPLEVEL1STATE	024#define sb_WRITESTATS	025#define sb_CONTEXTSWITCH	026#define sb_COPYSYS0SUBR	027#define sb_WRITEMAP	030#define sb_UFS_GETFILENAME	042#define sb_UFS_DELETEFILE	043#define sb_UFS_RENAMEFILE	044#define sb_COM_READPAGES	045#define sb_COM_WRITEPAGES	046#define sb_COM_TRUNCATEFILE	047#define sb_UFS_DIRECTORYNAMEP	051#define sb_COM_GETFREEBLOCK	055#define sb_SETUNIXTIME	060#define sb_GETUNIXTIME	061#define sb_COPYTIMESTATS	062#define sb_UNIX_USERNAME	063#define sb_UNIX_FULLNAME	064#define sb_UNIX_GETENV	065#define sb_UNIX_GETPARM	066#define sb_CHECK_SUM	067#define sb_ETHER_SUSPEND	070#define sb_ETHER_RESUME	071#define sb_ETHER_AVAILABLE	072#define sb_ETHER_RESET	073#define sb_ETHER_GET	074#define sb_ETHER_SEND	075#define sb_ETHER_SETFILTER	076#define sb_ETHER_CHECK	077#define sb_DSPCURSOR	0100#define sb_SETMOUSEXY	0101#define sb_DSP_VIDEOCOLOR	0102#define sb_DSP_SCREENWIDTH	0103#define sb_DSP_SCREENHEIGHT	0104#define sb_BITBLTSUB	0105#define sb_BLTCHAR	0106#define sb_TEDIT_BLTCHAR	0107#define sb_BITBLT_BITMAP	0110#define sb_BLTSHADE_BITMAP	0111#define sb_KEYBOARDBEEP	0120#define sb_KEYBOARDMAP	0121#define sb_KEYBOARDSTATE	0122#define sb_VMEMSAVE	0131#define sb_LISP_FINISH	0132#define sb_NEWPAGE	0133#define sb_DORECLAIM	0134#define sb_DUMMY_135Q	0135#define sb_NATIVE_MEMORY_REFERENCE	0136#define sb_OLD_COMPILE_LOAD_NATIVE	0137#define sb_DISABLEGC    0140#define sb_COM_SETFILEINFO	0147#define sb_COM_OPENFILE	0150#define sb_COM_CLOSEFILE	0151#define sb_DSK_GETFILENAME	0152#define sb_DSK_DELETEFILE	0153#define sb_DSK_RENAMEFILE	0154#define sb_COM_NEXT_FILE	0156#define sb_COM_FINISH_FINFO	0157#define sb_COM_GEN_FILES	0160#define sb_DSK_DIRECTORYNAMEP	0161#define sb_COM_GETFILEINFO	0162#define sb_COM_CHANGEDIR	0164#define sb_UNIX_HANDLECOMM	0165#define sb_RPC_CALL	0167#define sb_MESSAGE_READP	0170#define sb_MESSAGE_READ	0171#define sb_MONITOR_CONTROL	0200#define sb_GET_NATIVE_ADDR_FROM_LISP_PTR	0203#define sb_GET_LISP_PTR_FROM_NATIVE_ADDR	0204#define sb_LOAD_NATIVE_FILE	0205#define sb_SUSPEND_LISP	0206#define sb_NEW_BLTCHAR	0207#define sb_COLOR_INIT	0210#define sb_COLOR_SCREENMODE	0211#define sb_COLOR_MAP	0212#define sb_COLOR_BASE	0213#define sb_C_SlowBltChar	0214#define sb_TCP_OP	0220#define sb_WITH_SYMBOL		0221#define sb_OPEN_SOCKET	0240	/* For CLX */#define sb_CLOSE_SOCKET	0241#define sb_READ_SOCKET	0242#define sb_WRITE_SOCKET	0243#define sb_CHAR_OPENFILE	0310#define sb_CHAR_BIN	0311#define sb_CHAR_BOUT	0312#define sb_CHAR_IOCTL	0313#define sb_CHAR_CLOSEFILE	0314#define sb_CHAR_EOFP	0315#define sb_CHAR_READP	0316#define sb_CHAR_BINS	0317#define sb_CHAR_BOUTS	0320#define sb_CHAR_FILLBUFFER	0321/* MISCN opcodes */#define miscn_USER_SUBR	00#define miscn_VALUES	01#define miscn_SXHASH	02#define miscn_EQLHASHBITSFN	03#define miscn_STRINGHASHBITS	04#define miscn_STRING_EQUAL_HASHBITS	05#define miscn_VALUES_LIST	06#define miscn_LCFetchMethod	07#define miscn_LCFetchMethodOrHelp	010#define miscn_LCFindVarIndex	011#define miscn_LCGetIVValue	012#define miscn_LCPutIVValue	013/* Assigned USER SUBR numbers */#define user_subr_DUMMY	012#define user_subr_SAMPLE_USER_SUBR	00