# 1 "../src/xc.c" 

static char *id = "@(#) xc.c	1.33 2/8/93	(venue & Fuji Xerox)";






















# 1 "/usr/include/sys/types.h" 1















# 1 "/usr/include/sys/sysmacros.h" 1


















# 17 "/usr/include/sys/types.h" 2

typedef	unsigned char	u_char;
typedef	unsigned short	u_short;
typedef	unsigned int	u_int;
typedef	unsigned long	u_long;
typedef	unsigned short	ushort;		
typedef	unsigned int	uint;		

# 30 "/usr/include/sys/types.h" 

# 36 "/usr/include/sys/types.h" 


typedef struct  _physadr { int r[1]; } *physadr;
typedef struct label_t {
	int     val[2];
} label_t;

# 48 "/usr/include/sys/types.h" 

typedef	struct	_quad { long val[2]; } quad;
typedef	long	daddr_t;
typedef	char *	caddr_t;
typedef	u_long	ino_t;
typedef	long	swblk_t;
typedef	int	size_t;
typedef	long	time_t;
typedef	short	dev_t;
typedef	long	off_t;
typedef	u_short	uid_t;
typedef	u_short	gid_t;
typedef	long	key_t;












typedef	long	fd_mask;


# 78 "/usr/include/sys/types.h" 





typedef	struct fd_set {
	fd_mask	fds_bits[(((256)+(( (sizeof(fd_mask) * 8))-1))/( (sizeof(fd_mask) * 8)))];
} fd_set;

typedef	char *	addr_t;






# 107 "/usr/include/sys/types.h" 



# 26 "../src/xc.c" 2
# 1 "/usr/include/sys/time.h" 1















struct timeval {
	long	tv_sec;		
	long	tv_usec;	
};

struct timezone {
	int	tz_minuteswest;	
	int	tz_dsttime;	
};































struct	itimerval {
	struct	timeval it_interval;	
	struct	timeval it_value;	
};


# 1 "/usr/include/time.h" 1





struct tm {
	int	tm_sec;
	int	tm_min;
	int	tm_hour;
	int	tm_mday;
	int	tm_mon;
	int	tm_year;
	int	tm_wday;
	int	tm_yday;
	int	tm_isdst;
	char	*tm_zone;
	long	tm_gmtoff;
};

extern	struct tm *gmtime(), *localtime();
extern	char *asctime(), *ctime();
extern	void tzset(), tzsetwall();
# 63 "/usr/include/sys/time.h" 2



# 27 "../src/xc.c" 2
# 1 "/usr/include/stdio.h" 1





extern	struct	_iobuf {
	int	_cnt;
	unsigned char *_ptr;
	unsigned char *_base;
	int	_bufsiz;
	short	_flag;
	char	_file;		
} _iob[];



















# 36 "/usr/include/stdio.h" 

















extern struct _iobuf	*fopen();
extern struct _iobuf	*fdopen();
extern struct _iobuf	*freopen();
extern struct _iobuf	*popen();
extern struct _iobuf	*tmpfile();
extern long	ftell();
extern char	*fgets();
extern char	*gets();
# 63 "/usr/include/stdio.h" 

extern char	*ctermid();
extern char	*cuserid();
extern char	*tempnam();
extern char	*tmpnam();






# 28 "../src/xc.c" 2


# 1 "../inc//lispemul.h" 1























# 33 "../inc//lispemul.h" 


# 37 "../inc//lispemul.h" 


# 41 "../inc//lispemul.h" 





	
	
	
	
	
	
	
	
	
	
	
	

	




typedef char s_char;



	





# 79 "../inc//lispemul.h" 



# 85 "../inc//lispemul.h" 


# 95 "../inc//lispemul.h" 


# 99 "../inc//lispemul.h" 


# 104 "../inc//lispemul.h" 


# 115 "../inc//lispemul.h" 


# 122 "../inc//lispemul.h" 


# 126 "../inc//lispemul.h" 



	
	
	





	
typedef struct {unsigned char code;} BYTECODE;
typedef char ByteCode;
typedef unsigned short  DLword;
typedef char  DLbyte;
typedef unsigned int  LispPTR;

typedef DLword mds_page;  
typedef (*CFuncPTR)();


typedef struct  consstr
  {
    unsigned cdr_code  : 4;
    unsigned car_field : 28;
  } ConsCell;

typedef struct ufn_entry
  {
    DLword atom_name;   
    unsigned byte_num : 8; 
    unsigned arg_num  : 8; 
  } UFN;

typedef struct closure_type
  {
    unsigned nil1    :  4;
    unsigned def_ptr : 28; 
    unsigned nil2    :  4;
    unsigned env_ptr : 28; 
  } Closure;

# 190 "../inc//lispemul.h" 


typedef struct interrupt_state
  { 
    unsigned LogFileIO		:1; 
    unsigned ETHERInterrupt	:1; 
    unsigned IOInterrupt	:1; 
    unsigned gcdisabled		:1;
    unsigned vmemfull		:1;
    unsigned stackoverflow	:1;
    unsigned storagefull	:1;
    unsigned waitinginterrupt	:1;
    unsigned nil	:8;	    
    DLword   intcharcode;
  } INTSTAT;

typedef struct interrupt_state_2
  { 
    unsigned pendingmask	:8;
    unsigned handledmask	:8;
    DLword   nil;
  } INTSTAT2;

struct state
  {
    DLword		*ivar;		
    DLword		*pvar;		
    DLword		*csp;		
    LispPTR	 	tosvalue;	
    ByteCode 		*currentpc;	
    struct fnhead 	*currentfunc;	
    DLword 		*endofstack;	
    int 		irqcheck;	
    int 		irqend;		
    LispPTR		scratch_cstk;	
    int			errorexit;	
  };




# 233 "../inc//lispemul.h" 






# 243 "../inc//lispemul.h" 









# 254 "../inc//lispemul.h" 




typedef	struct wbits
  {
    unsigned short xMSB :1;
    unsigned short B1  :1;
    unsigned short B2	 :1;
    unsigned short B3	 :1;
    unsigned short B4	 :1;
    unsigned short B5  :1;
    unsigned short B6	 :1;
    unsigned short B7	 :1;
    unsigned short B8	 :1;
    unsigned short B9	 :1;
    unsigned short B10 :1;
    unsigned short B11 :1;
    unsigned short B12 :1;
    unsigned short B13 :1;
    unsigned short B14 :1;
    unsigned short LSB :1;
  }WBITS;

typedef	struct lbits
  {
    unsigned xMSB	:1;
    unsigned MIDDLE	:30;
    unsigned LSB	:1;
  }LBITS;

# 411 "../inc//lispemul.h" 




	
	




extern struct state MachineState;
















# 1 "../inc//ifpage.h" 1
























	
typedef struct ifpage {
	DLword    currentfxp;
	DLword    resetfxp;
	DLword    subovfxp;
	DLword    kbdfxp;
	DLword    hardreturnfxp;
	DLword    gcfxp;
	DLword    faultfxp;
	DLword    endofstack;
	DLword    lversion;
	DLword    minrversion;
	DLword    minbversion;
	DLword    rversion;
	DLword    bversion;
	DLword    machinetype;
	DLword    miscfxp;
	DLword    key;
	DLword    serialnumber;
	DLword    emulatorspace;
	DLword    screenwidth;
	DLword    nxtpmaddr;
	DLword    ex_nactivepages;
	DLword    ex_ndirtypages;
	DLword    filepnpmp0;
	DLword    filepnpmt0;
	DLword    teleraidfxp;
	DLword    filler1;
	DLword    filler2;
	DLword    filler3;
	DLword    usernameaddr;
	DLword    userpswdaddr;
	DLword    stackbase;
	DLword    faulthi;
	DLword    faultlo;
	DLword    devconfig;
	DLword    rptsize;
	DLword    rpoffset;
	DLword    wasrptlast;
	DLword    embufvp;
	DLword    nshost0;
	DLword    nshost1;
	DLword    nshost2;
	DLword    mdszone;
	DLword    mdszonelength;
	DLword    emubuffers;
	DLword    emubuflength;

	DLword    ex_process_size; 
	DLword    storagefullstate;  
# 78 "../inc//ifpage.h" 

	DLword    isfmap;
	


	LispPTR   miscstackfn;
	LispPTR   miscstackarg1;
	LispPTR   miscstackarg2;
	LispPTR   miscstackresult;
	DLword    nrealpages;
	DLword    lastlockedfilepage;
	DLword    lastdominofilepage;
	DLword    fptovpstart;
	DLword    fakemousebits;
	DLword    dl24bitaddressable;
	LispPTR   realpagetableptr;
	DLword    ex_dllastvmempage;
	DLword    fullspaceused;
	DLword    fakekbdad4;
	DLword    fakekbdad5;
	DLword	d1nil1;
	DLword	dlnil2;
	DLword	dlnil3;
	DLword	dlnil4;
	DLword	dlnil5;
	DLword	dlnil6;
	LispPTR	dlnilp1;
	LispPTR	dlnilp2;
	LispPTR	dlnilp3;
	int    dllastvmempage;
	int	    nactivepages;
	int    ndirtypages;
	int    process_size; 
} IFPAGE;
# 187 "../inc//ifpage.h" 

# 361 "../inc//ifpage.h" 


# 439 "../inc//lispemul.h" 2


# 1 "../inc//iopage.h" 1




















typedef struct iopage {
	DLword	 dummy0[022];
	DLword   dlmaintpanel;
        DLword   dlfloppycmd;
        DLword   dlttyportcmd;
        DLword   dlprocessorcmd;
        DLword   newmousestate;
        DLword   dlbeepcmd;
        DLword   dlrs232cmisccommand;
        DLword   dlrs232cputflag;
	DLword   dlrs232cgetflag;
	DLword   dummy1[6];
	DLword   dlfloppy;
	DLword   dlttyout;
	DLword   dummy2;
	DLword   dlttyin;
	DLword   dummy3;
	DLword   dlprocessor2;
	DLword   dlprocessor1;
	DLword   dlprocessor0;
	DLword   newmousex;
	DLword   newmousey;
	DLword   dlbeepfreq;
	DLword   dlrs232cparametercsblo;
	DLword   dlrs232cparametercsbhi;
	DLword   dlrs232csetrs366status[3];
	DLword   dlrs232cputcsblo;
	DLword   dlrs232cputcsbhi;
	DLword   dlrs232cgetcsblo;
	DLword   dlrs232cgetcsbhi;
	DLword   dlrs232cdevicestatus;
	DLword   dlrs232cparameteroutcome;
	DLword   dltodvalid;
	DLword   dltodlo;
	DLword   dltodhi;
	DLword   dltodlo2;
	DLword   dlmousex;
	DLword   dlmousey;
	DLword   dlutilin;
	DLword   dlkbdad0;
	DLword   dlkbdad1;
	DLword   dlkbdad2;
	DLword   dlkbdad3;
	DLword   dlkbdad4;
	DLword   dlkbdad5;
	DLword   dllsepimagecsb[040];
	DLword   dliophardwareconfig;
	DLword   dummy4[013];
	DLword   dlrs232cparametercsblo_11;
	DLword   dlrs232cparametercsbhi_11;
	DLword   dlrs232csetrs366status_11[016] ;
	DLword   dummy5[074];
	DLword   dlmagtape[4];
	DLword   dlethernet[014];
	DLword   dummy6[037];
	DLword   dldispinterrupt;
	DLword   dldispcontrol;
	DLword   dldispborder;
	DLword   dlcursorx;
	DLword   dlcursory;
	DLword   dlcursorbitmap[020];
} IOPAGE;
# 154 "../inc//iopage.h" 



# 442 "../inc//lispemul.h" 2



# 1 "../inc//miscstat.h" 1




















typedef struct  misc 
  {
    int	starttime;
    int	totaltime;
    int	swapwaittime;
    int	pagefaults;
    int	swapwrites;
    int	diskiotime;
    int	diskops;
    int	keyboardwaittime;
    int	gctime;
    int	netiotime;
    int	netioops;
    int	swaptemp0;
    int	swaptemp1;
    unsigned int	rclksecond;
    unsigned int	secondsclock;
    unsigned int	millisecondsclock;
    unsigned int	baseclock;
    unsigned int	rclktemp0;
    unsigned int	secondstmp;
    unsigned int	millisecondstmp;
    unsigned int	basetmp;
    int	excesstimetmp;
    int	clocktemp0;
    int	disktemp0;
    int	disktemp1;
    int	teleraidtemp1;
    int	teleraidtemp2;
    int	teleraidtemp3;
    int	lastuseraction;
    int	dlmousetimer;
    int	dlmousetemp;
  } MISCSTATS;
# 446 "../inc//lispemul.h" 2




























































































# 540 "../inc//lispemul.h" 














		
















































# 609 "../inc//lispemul.h" 













typedef struct newatom
  {
    LispPTR na_pname;	
    LispPTR na_value;	
    LispPTR na_defn;	
    LispPTR na_plist;	
	LispPTR na_flags;	
  } NEWATOM;

  






  

















# 660 "../inc//lispemul.h" 


# 31 "../src/xc.c" 2
# 1 "../inc//emlglob.h" 1





































# 32 "../src/xc.c" 2
# 1 "../inc//address.h" 1






















































# 59 "../inc//address.h" 

# 33 "../src/xc.c" 2
# 1 "../inc//adr68k.h" 1















































# 50 "../inc//adr68k.h" 

















# 70 "../inc//adr68k.h" 

# 34 "../src/xc.c" 2
# 1 "../inc//stack.h" 1




























































	
	
	
typedef struct fnhead{
	DLword		stkmin;	
	short		na;	
	short		pv;	
	DLword		startpc;
			
	unsigned	native		: 1;	
	unsigned	byteswapped	: 1;	
	unsigned	argtype		: 2;	

	unsigned	framename	:28;	
# 79 "../inc//stack.h" 

	DLword		ntsize;			
	unsigned	nlocals		: 8;	
	unsigned	fvaroffset	: 8;
			
	
} FNHEAD;


typedef struct frameex1{
	unsigned	flags	:3;
	unsigned	fast	:1;
	unsigned	native	:1;	
	unsigned	incall	:1;
	unsigned	validnametable	:1;
			

	unsigned	nopush	:1;
	unsigned	usecount :8;
	DLword	alink;		

	LispPTR fnheader;	
# 105 "../inc//stack.h" 

	DLword	nextblock;	
	DLword	pc;		

	LispPTR nametable;	
# 114 "../inc//stack.h" 

	DLword	blink;		
	DLword	clink;		
} FX;

typedef struct frameex2{
	unsigned	flags	:3;
	unsigned	fast	:1;
	unsigned	native	:1;	
	unsigned	incall	:1;
	unsigned	validnametable	:1;
			

	unsigned	nopush	:1;
	unsigned	usecount :8;
	DLword	alink;		
	LispPTR	fnheader;	
	DLword	nextblock;	
	DLword	pc;		
	LispPTR	nametable;	
	DLword	blink;		
	DLword	clink;		
} FX2;




typedef struct fxblock {
	unsigned	flagbyte	: 8;
	unsigned	nil		: 23;
	unsigned	slowp		: 1;
} FXBLOCK;

typedef struct basic_frame {
	unsigned	flags	: 3;
	unsigned	nil	: 3;
	unsigned	residual: 1;
	unsigned	padding : 1;
	unsigned	usecnt  : 8;
	DLword		ivar;

} Bframe;

typedef struct stkword {
		unsigned short flags	 :3;
		unsigned short nil	 :5;
		unsigned short usecount :8;
 } StackWord;


 typedef struct stack_block {
		DLword flagword;
		DLword size;
 } STKBLK;


typedef struct stackp {
		DLword stackp0;
		DLword edfxp;
} STACKP;


	
	
	



# 316 "../inc//stack.h" 











































# 361 "../inc//stack.h" 























# 420 "../inc//stack.h" 
























# 35 "../src/xc.c" 2
# 1 "../inc//dbprint.h" 1
















# 1 "/usr/include/stdio.h" 1


# 73 "/usr/include/stdio.h" 

# 18 "../inc//dbprint.h" 2





















	

# 44 "../inc//dbprint.h" 






	

# 55 "../inc//dbprint.h" 








	

# 68 "../inc//dbprint.h" 






	

# 79 "../inc//dbprint.h" 






	

# 90 "../inc//dbprint.h" 





# 36 "../src/xc.c" 2

# 1 "../inc//lspglob.h" 1
















































 extern  DLword *Atomspace; 		
 extern  DLword *Stackspace;		
 extern  DLword *Plistspace;		
 extern  DLword *DTDspace;		
 extern  DLword *MDStypetbl;		
 extern  DLword *AtomHT;		
 extern  DLword *Pnamespace;		
 extern  DLword *Defspace;		
 extern  DLword *Valspace;		
 extern  DLword *Spospspace;		
 extern  DLword *Snegspace;		
 


extern LispPTR *FPtoVP;
# 66 "../inc//lspglob.h" 

extern DLword *PAGEMap;
extern DLword *PageMapTBL ;
extern DLword *LockedPageTable;


extern DLword *IOCBPage ;
extern IOPAGE *IOPage ;
extern IFPAGE *InterfacePage ;
extern MISCSTATS *MiscStats ;


extern DLword *UFNTable ;



 extern  LispPTR *HTmain;
 extern  LispPTR *HToverflow;
 extern  LispPTR *HTbigcount;
 extern  LispPTR *HTcoll;
# 91 "../inc//lspglob.h" 




 extern DLword *DisplayRegion ;



 extern  DLword *Arrayspace;  
 extern  DLword *MDS_space_bottom;  
 extern  DLword *PnCharspace ;	

 extern  struct dtd *ListpDTD ;	
 extern  DLword *Next_Array ;	
 extern  DLword *Next_MDSpage;	
  
 


  extern DLword *Lisp_world;  
 



extern LispPTR *Next_MDSpage_word;
extern LispPTR *Next_Array_word;
extern LispPTR *MDS_free_page_word;

extern LispPTR *Reclaim_cnt_word ;


extern int FileIOFlag, TimerFlag;



extern LispPTR *GcDisabled_word;
extern LispPTR *CdrCoding_word;
extern LispPTR *FreeBlockBuckets_word;
extern LispPTR *Array_Block_Checking_word;
extern LispPTR *ArrayMerging_word;
extern LispPTR *ArraySpace_word;
extern LispPTR *ArraySpace2_word;
extern LispPTR *ArrayFrLst_word;
extern LispPTR *ArrayFrLst2_word;
extern LispPTR *Hunk_word;
extern LispPTR *System_Buffer_List_word;




extern LispPTR *GcMess_word;
extern LispPTR *ReclaimMin_word;
extern LispPTR *GcTime1_word;
extern LispPTR *GcTime2_word;
extern LispPTR *MaxTypeNumber_word;




extern LispPTR *Package_from_Index_word;
extern LispPTR *Package_from_Name_word;
extern LispPTR *Keyword_Package_word;
extern LispPTR *Deleted_Implicit_Hash_Slot_word;
extern LispPTR *Closure_Cache_Enabled_word;
extern LispPTR *Closure_Cache_word;
extern LispPTR First_index;



extern LispPTR *STORAGEFULLSTATE_word;
extern LispPTR *STORAGEFULL_word;
extern LispPTR *PENDINGINTERRUPT_word;
extern LispPTR *LeastMDSPage_word;
extern LispPTR *SecondMDSPage_word;
extern LispPTR *SecondArrayPage_word;
extern LispPTR *INTERRUPTSTATE_word;
extern LispPTR *SYSTEMCACHEVARS_word;
extern LispPTR *MACHINETYPE_word;

extern LispPTR STORAGEFULLSTATE_index;

extern LispPTR *LASTVMEMFILEPAGE_word;
extern LispPTR *VMEM_FULL_STATE_word;


extern int native_load_address;
extern LispPTR native_closure_env;


extern LispPTR *STACKOVERFLOW_word;
extern LispPTR *GuardStackAddr_word;
extern LispPTR *LastStackAddr_word;
extern LispPTR *NeedHardreturnCleanup_word;


extern int UnixPipeIn;
extern int UnixPipeOut;
extern int UnixPID;


extern LispPTR MVLIST_index;
# 38 "../src/xc.c" 2
# 1 "../inc//lsptypes.h" 1












































































































































# 191 "../inc//lsptypes.h" 





	

struct dtd {
	unsigned unuse	:2 ;
	unsigned dtd_obsolate :1 ;
	unsigned dtd_finalizable :1 ;
	unsigned dtd_name: 28 ;	
	DLword dtd_cnt0 ;
	DLword dtd_size ;
	LispPTR dtd_free ;		
	unsigned dtd_lockedp : 1 ;
	unsigned dtd_hunkp : 1 ;
	unsigned dtd_gctype :2 ;
	unsigned dtd_descrs: 28;
	LispPTR dtd_typespecs;
	LispPTR dtd_ptrs ;
	int  dtd_oldcnt;
	int dtd_nextpage ;
	DLword dtd_typeentry ;
	DLword dtd_supertype ;
};

typedef  struct stringp {

	unsigned origin			: 1 ;
	unsigned substringed		: 1 ;
	unsigned readonly		: 1 ;
	unsigned nil			: 1 ;

	unsigned base			: 28 ;
	unsigned type			: 4 ;
	unsigned   length: 28 ;
	LispPTR   offset ;
 } STRINGP ;

typedef struct oned_array {
		unsigned int nil1 : 4 ;
		unsigned int base : 28  ;
		unsigned int readonlyp :1 ;
		unsigned int indirectp : 1; 
		unsigned int bitp :1 ;
		unsigned int stringp : 1;
		unsigned int ajustablep : 1; 
		unsigned int displacedp : 1;
		unsigned int fillpointerp :1;
		unsigned int extendablep : 1;
		unsigned int typenumber : 8 ;
		DLword offset;
		LispPTR fillpointer ;
		LispPTR totalsize ; } OneDArray;

typedef struct oned_array NEWSTRINGP;

typedef struct general_array {
		unsigned int nil1 : 4 ;
		unsigned int base : 28  ;
		unsigned int readonlyp :1 ;
		unsigned int indirectp : 1; 
		unsigned int bitp :1 ;
		unsigned int stringp : 1;
		unsigned int ajustablep : 1; 
		unsigned int displacedp : 1;
		unsigned int fillpointerp :1;
		unsigned int extendablep : 1;
		unsigned int typenumber : 8 ;
		LispPTR Dim0;
		LispPTR Dim1 ;
		LispPTR Dim2 ; } LispArray;

typedef struct compiled_closure {
		unsigned int nil1	: 4 ;
		unsigned int def_ptr	: 28; 
		unsigned int nil2	: 4 ;
		unsigned int env_ptr	: 28; 
  } CClosure ;
# 346 "../inc//lsptypes.h" 



 struct system_dtd_contents {
	char   *dtd_name ;  
	DLword  name_len ;  
	DLword  dtd_size ;
};

typedef struct{
	LispPTR	bmbase;
	DLword	bmrasterwidth;
	DLword	bmheight;
	DLword	bmwidth;
	DLword	bmbitperpixel;
}BITMAP;


	
	
	
	
	
	
	
	




  





# 505 "../inc//lsptypes.h" 






































# 545 "../inc//lsptypes.h" 





# 561 "../inc//lsptypes.h" 










	
	
	
	
	
	
	
	
typedef
  struct
    {
      LispPTR host;
      LispPTR device;
      LispPTR directory;
      LispPTR name;
      LispPTR type;
      LispPTR version;
    } PATHNAME;
  
	
	
	
	
	
	
	
	
typedef
  struct
    {
      LispPTR real;
      LispPTR imaginary;
    } COMPLEX;


	
	
	
	
	
	
	
	
typedef
  struct
    {
      LispPTR numerator;
      LispPTR denominator;
    } RATIO;


	
	
	
	
	
	
	
	
typedef
  struct
    {
      LispPTR contents;	
			
    } BIGNUM;

# 39 "../src/xc.c" 2
# 1 "../inc//lispmap.h" 1

















































 





























# 84 "../inc//lispmap.h" 










# 99 "../inc//lispmap.h" 



































    



# 142 "../inc//lispmap.h" 






















































# 215 "../inc//lispmap.h" 









# 228 "../inc//lispmap.h" 


# 231 "../inc//lispmap.h" 

















# 40 "../src/xc.c" 2
# 1 "../inc//cell.h" 1
































  
  









# 53 "../inc//cell.h" 











struct
  conspage
    {
      unsigned count: 8;	
      unsigned next_cell: 8;	
      unsigned nil:16;
      LispPTR  next_page;	
    };
# 80 "../inc//cell.h" 

# 101 "../inc//cell.h" 



















  
typedef struct freec
  {
    unsigned next_free: 8;	
    unsigned nil: 24;
  } freecons;

# 135 "../inc//cell.h" 















	
	
	



typedef
  struct new_atom
      {
	unsigned dfccodep: 1 ;	
	unsigned dffastp: 1 ;
	unsigned dfargtype: 2 ;
	unsigned pncell: 28;	
	unsigned nil2: 4;	
	unsigned valcell: 28;	
	unsigned nil3: 4;	
	unsigned defcell: 28;	
	unsigned nil4: 4;	
	unsigned plcell: 28;	
	unsigned pnpkg: 8;	
	unsigned dfnil1: 4 ;	
	unsigned dfpseudo: 1 ;
	unsigned dfswapped: 1 ;	
	unsigned dfnil:	2 ;
	unsigned plunused: 1;	
	unsigned plgensymp: 1;
	unsigned plfatpnamep: 1;
	unsigned plnil: 5;
	unsigned nil5: 8;	
      } NewAtom;


typedef
  struct definition_cell
    {
      unsigned	ccodep	:	1 ;
      unsigned	fastp	:	1 ;
      unsigned	argtype	:	2 ;
      unsigned	defpointer :	28;
	LispPTR nil_PL;	
	unsigned nilpkg:8;	
      unsigned	nil2	:	4 ;
      unsigned	pseudocodep :	1 ;
      unsigned	byteswapped :	1 ;	
	unsigned nil_last: 18;

    } DefCell ;

typedef
  struct pname_cell
    {
      unsigned	nil	:	4 ;
      unsigned	pnamebase : 28 ;
	LispPTR nil_val;
	LispPTR nil_def;
	LispPTR nil_plist;
      unsigned	pkg_index : 8 ;
	unsigned nil2: 24;
    } PNCell ;

typedef
  struct proplist_cell
    {
      unsigned nil: 4;
      unsigned propbase: 28;
	unsigned nilpkg: 8;
	unsigned nildef: 8;
      unsigned unused: 1;
      unsigned gensymp: 1;
      unsigned fatpnamep: 1;
      unsigned nil2: 5;
	unsigned nil3:	8;

    } PLCell;


struct xpointer{
	unsigned	flags:4;
	unsigned	addr:28;
};

# 349 "../inc//cell.h" 


# 393 "../inc//cell.h" 





struct
  cadr_cell
    {
      LispPTR car_cell;	
      LispPTR cdr_cell;	
    };













# 429 "../inc//cell.h" 

  
















  









# 462 "../inc//cell.h" 


  





















# 41 "../src/xc.c" 2
# 1 "../inc//initatms.h" 1













































# 42 "../src/xc.c" 2
# 1 "../inc//gc.h" 1































  




# 43 "../inc//gc.h" 




   


   









   










  


























































	
	
	

struct	 hashentry
  { 
    unsigned short count	:15;
    unsigned short stackref	:1;
    unsigned short segnum	:15;
    unsigned short collision	:1;
  };

struct  htlinkptr
  {	
    LispPTR	contents;
  };

struct	htcoll
  { 
    LispPTR	free_ptr ;
    LispPTR	next_free ;
  };

struct	gc_ovfl
  {
    LispPTR	  ovfl_ptr ;
    unsigned int  ovfl_cnt ;
  };

struct  htoverflow 
  {	
    unsigned	pcase	:4;
    unsigned	ptr	:28;
  };
# 195 "../inc//gc.h" 


# 266 "../inc//gc.h" 

# 43 "../src/xc.c" 2
# 1 "../inc//arith.h" 1





































































# 99 "../inc//arith.h" 




























































































	


# 211 "../inc//arith.h" 














































# 271 "../inc//arith.h" 


# 44 "../src/xc.c" 2
# 1 "../inc//stream.h" 1


















	
	
	
typedef struct	stream{
	DLword	COFFSET;
     DLword	CBUFSIZE;
# 33 "../inc//stream.h" 

     unsigned	PEEKEDCHARP	:1;
	unsigned  ACCESS	:3;
     unsigned	CBUFPTR		:28;

     DLbyte	BYTESIZE;
     DLbyte	CHARSET;
     DLword	PEEKEDCHAR;
     DLword	CHARPOSITION;
     DLword	CBUFMAXSIZE;
     unsigned	NONDEFAULTDATEFLG	:1;
     unsigned	REVALIDATEFLG	:1;
     unsigned	MULTIBUFFERHINT	:1;
     unsigned	USERCLOSEABLE	:1;
# 52 "../inc//stream.h" 

     unsigned	FULLFILENAME	:28;


     unsigned	BINABLE	:1;
     unsigned	BOUTABLE	:1;
     unsigned	EXTENDABLE	:1;
     unsigned	CBUFDIRTY	:1;
     unsigned	DEVICE: 28;
# 63 "../inc//stream.h" 


     unsigned	USERVISIBLE	:1;
     unsigned	EOLCONVENTION	:2;
     unsigned	NIL1	:1;
     unsigned	VALIDATION: 28;
# 71 "../inc//stream.h" 

     LispPTR	CPAGE;
     LispPTR	EPAGE;
     DLword	EOFFSET;
     DLword	LINELENGTH;
     LispPTR	F1;
     LispPTR	F2;
     LispPTR	F3;
     LispPTR	F4;
     LispPTR	F5;
     DLword	FW6;
     DLword	FW7;
     DLword	FW8;
     DLword	FW9;
     LispPTR	F10;
     LispPTR	STRMBINFN;
     LispPTR	STRMBOUTFN;
     LispPTR	OUTCHARFN;
     LispPTR	ENDOFSTREAMOP;
     LispPTR	OTHERPROPS;
     LispPTR	IMAGEOPS;
     LispPTR	IMAGEDATA;
     LispPTR	BUFFS;
     DLword	MAXBUFFERS;
     DLword	NIL2;
     LispPTR	EXTRASTREAMOP;
}Stream;

# 157 "../inc//stream.h" 


# 45 "../src/xc.c" 2

# 1 "../inc//tos1defs.h" 1






























	
	
	















# 69 "../inc//tos1defs.h" 





























# 103 "../inc//tos1defs.h" 































# 47 "../src/xc.c" 2
# 1 "../inc//tosret.h" 1


































# 38 "../inc//tosret.h" 






# 56 "../inc//tosret.h" 




































# 48 "../src/xc.c" 2
# 1 "../inc//tosfns.h" 1



































# 38 "../inc//tosfns.h" 




# 68 "../inc//tosfns.h" 

# 71 "../inc//tosfns.h" 























































# 142 "../inc//tosfns.h" 



















# 186 "../inc//tosfns.h" 




































# 321 "../inc//tosfns.h" 
















































































































































































































































































































































	
	
	
	
	
	
    
# 667 "../inc//tosfns.h" 










# 726 "../inc//tosfns.h" 



























































# 49 "../src/xc.c" 2
# 1 "../inc//inlineC.h" 1










































	



	






# 57 "../inc//inlineC.h" 

# 63 "../inc//inlineC.h" 















































































# 179 "../inc//inlineC.h" 





































































































# 283 "../inc//inlineC.h" 












# 306 "../inc//inlineC.h" 
















































# 356 "../inc//inlineC.h" 
















































































































































































































































































































# 677 "../inc//inlineC.h" 




































# 720 "../inc//inlineC.h" 













































# 795 "../inc//inlineC.h" 































































































































































































































































# 1061 "../inc//inlineC.h" 







# 50 "../src/xc.c" 2

# 56 "../src/xc.c" 



# 64 "../src/xc.c" 



	
	

# 1 "../inc//inlnSPARC.h" 1


































































































































 















































# 71 "../src/xc.c" 2



# 76 "../src/xc.c" 


# 1 "../inc//fast_dsp.h" 1












































# 137 "../inc//fast_dsp.h" 






























# 79 "../src/xc.c" 2
# 1 "../inc//profile.h" 1



















# 22 "../inc//profile.h" 

# 26 "../inc//profile.h" 








































































































































































































































































# 80 "../src/xc.c" 2













typedef struct conspage ConsPage;
typedef ByteCode *InstPtr;

extern DLword *createcell68k();


# 101 "../src/xc.c" 






# 113 "../src/xc.c" 


int dbgflag = 0;

int	extended_frame;		


int n_mask_array[16] = {	1, 3, 7, 0xf, 
			0x1f, 0x3f, 0x7f, 0xff,
			0x1ff, 0x3ff, 0x7ff, 0xfff,
			0x1fff, 0x3fff, 0x7fff, 0xffff};

extern int TIMER_INTERVAL;


dispatch()
{
	register InstPtr pccache;

# 134 "../src/xc.c" 


# 138 "../src/xc.c" 

register InstPtr *table;




# 145 "../src/xc.c" 

	register LispPTR *cspcache;
	register LispPTR tscache;



	register struct state *stateptrcache = (&MachineState);




# 158 "../src/xc.c" 

# 161 "../src/xc.c" 



# 166 "../src/xc.c" 




    DefCell *fn_defcell;
    LispPTR fn_atom_index;
    int fn_opcode_size;
    int fn_num_args;
    int fn_apply;
    LispPTR fn_loc_defcell;

	{ pccache=stateptrcache->currentpc+1; {(cspcache) = ((LispPTR *) stateptrcache->csp)+1;}; tscache = stateptrcache->tosvalue; }; 
	{stateptrcache->irqcheck = ( (int)(stateptrcache->irqend = (int) stateptrcache->endofstack) - (( stateptrcache->currentfunc->stkmin ) << 1) ); };


# 183 "../src/xc.c" 





	table = (InstPtr *) compute_dispatch_table();


# 193 "../src/xc.c" 


# 197 "../src/xc.c" 

# 208 "../src/xc.c" 

	goto nextopcode;








	;


	unwind_err: (cspcache) = (LispPTR *) stateptrcache->csp; stateptrcache->errorexit = 0; goto op_ufn; ufn_2d: (cspcache) += 1; goto fix_tos_ufn; ufn_2d2:(cspcache) += 1; goto fix_tos_ufn; ufn_2: (cspcache) += 1; goto fix_tos_ufn; exception_2 : stateptrcache->errorexit = 0; (cspcache) += 1; tscache = stateptrcache->tosvalue; if(!stateptrcache->irqend){ goto check_interrupt; } else goto op_ufn; exception_2C : stateptrcache->errorexit = 0; tscache = stateptrcache->tosvalue; *(cspcache) = stateptrcache->scratch_cstk; (cspcache) += 1; if(!stateptrcache->irqend){ goto check_interrupt; } else { goto op_ufn; } fix_tos_ufn: tscache = stateptrcache->tosvalue; stateptrcache->errorexit = 0; goto op_ufn;;

op_ufn:	
{
# 227 "../src/xc.c" 

   register UFN *entry68k;						

	entry68k = (UFN *)(((UFN *)UFNTable) + ((((BYTECODE *)((pccache-1)))->code)));	
   fn_num_args = entry68k->arg_num;					
   fn_opcode_size = entry68k->byte_num+1;				
   fn_atom_index = entry68k->atom_name;					
   if (fn_atom_index == 0x14e)
	 printf("unk ufn\n.");
   fn_defcell = (DefCell *) (((fn_atom_index & 0xfff0000) != 0) ? (LispPTR *)((Lisp_world + (fn_atom_index))+4) : ((LispPTR *)Pnamespace + (5*(fn_atom_index))+2) );		
   fn_apply = 2 + entry68k->byte_num; 
   goto op_fn_common;							
};



	op_fn_common: ; { register struct fnhead *LOCFNCELL; register DefCell *defcell;  CClosure *closure; LispPTR closure_env = (LispPTR) 0xffffffff; {register int NEXTBLOCK = 0; defcell = fn_defcell; if( (defcell->ccodep == 0) ) if((( (* (MDStypetbl+((defcell->defpointer)>>9))) ) & 0x7ff)==13) {  closure=(CClosure *)(Lisp_world + (defcell->defpointer)); defcell=(DefCell *)closure;  if(closure->env_ptr ) {closure_env = (LispPTR) (closure->env_ptr); } }  else {  defcell = (DefCell *)(((256 & 0xfff0000) != 0) ? (LispPTR *)((Lisp_world + (256))+4) : ((LispPTR *)Pnamespace + (5*(256))+2) ); NEXTBLOCK = 1; }  LOCFNCELL = (struct fnhead *)(Lisp_world + (defcell->defpointer)); ((struct frameex2 *)((DLword *) ((LispPTR *) stateptrcache->pvar) - 10))->pc = ((unsigned int)(pccache-1) - (unsigned int)stateptrcache->currentfunc) + fn_opcode_size; ;  if ((int)((LispPTR *) cspcache) > (stateptrcache->irqcheck=(stateptrcache->irqend-((LOCFNCELL->stkmin ) << 1)))) goto check_interrupt;; { switch (fn_apply) { case 0: break;  case 1: tscache = *(--(cspcache)); tscache = *(--(cspcache)); break;  case 2: break;  case 3: {*((cspcache)++) = tscache; tscache = 0xE0000 | (((BYTECODE *)((pccache-1)+1))->code);}; break; case 4: {*((cspcache)++) = tscache; tscache = 0xE0000 | (((((BYTECODE *)((pccache-1)+1))->code) <<8) | (((BYTECODE *)((pccache-1)+1+1))->code));}; break; case 6:  case 5: { unsigned int atm = (((((BYTECODE *)((pccache-1) + 1))->code) << 24) | ((((BYTECODE *)((pccache-1) + 1+1))->code) << 16) | ((((BYTECODE *)((pccache-1) + 1+2))->code) << 8) | (((BYTECODE *)((pccache-1) + 1+3))->code)); if (atm & 0xfff0000) {*((cspcache)++) = tscache; tscache = atm;}  else {*((cspcache)++) = tscache; tscache = 0xE0000 | atm;};  } break; default: error("Storage error: invalid UFN entry"); } if (NEXTBLOCK) {*((cspcache)++) = tscache; tscache = fn_atom_index;}; }; {register int newivar; newivar = (int)(stateptrcache->ivar = (DLword *) (((LispPTR *) cspcache)+(1-fn_num_args-NEXTBLOCK))); ((struct frameex2 *)((DLword *) ((LispPTR *) stateptrcache->pvar) - 10))->nextblock = NEXTBLOCK = (((unsigned int)(newivar) - (unsigned int)Stackspace) >>1); } *((cspcache)++) = tscache;  if( LOCFNCELL->na >= 0 ) {register int RESTARGS; RESTARGS = fn_num_args - LOCFNCELL->na; while(RESTARGS <0) { *((cspcache)++) = 0; RESTARGS++; } (cspcache) -= (RESTARGS); }   *((cspcache)++) = 0x80000000 | NEXTBLOCK; }  *((LispPTR *)((LispPTR *) cspcache)) = (0xc000 << 16) | ((((unsigned int)(((LispPTR *) stateptrcache->pvar)) - (unsigned int)Stackspace) >>1)); ((struct frameex2 *)((LispPTR *) cspcache))->fnheader = (defcell->defpointer); (cspcache) = (LispPTR *) (((DLword *)((LispPTR *) cspcache)) + 10); stateptrcache->pvar = (DLword *) ((LispPTR *) cspcache); {register int result; register LispPTR unboundval; unboundval = (LispPTR) 0xffffffff; result = LOCFNCELL->pv; *((cspcache)++) = closure_env; *((cspcache)++) = unboundval; for (; --result >= 0;) { *((cspcache)++) = unboundval; *((cspcache)++) = unboundval; } }  (cspcache) += 1; pccache = (ByteCode *)LOCFNCELL + LOCFNCELL->startpc + 1; stateptrcache->currentfunc = LOCFNCELL; ;  {if((int)((LispPTR *) cspcache) > stateptrcache->irqcheck) goto check_interrupt;}; { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; }; };



nextopcode :
# 252 "../src/xc.c" 


  ;
# 257 "../src/xc.c" 



# 266 "../src/xc.c" 




switch ((((BYTECODE *)((pccache-1)))->code)) {
 
 case 000 : ; case000: { goto op_ufn; } 
 case 001 : ; case001: if (((( (* (MDStypetbl+((tscache)>>9))) ) & 0x7ff) == 5)) { register ConsCell *DATUM68K = (ConsCell *)((Lisp_world + (tscache))); if (DATUM68K->cdr_code == 0) { tscache = ((LispPTR)((ConsCell *)(Lisp_world + (DATUM68K->car_field)))->car_field); { { pccache += 1; { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; }; }; }; } else { tscache = ((LispPTR)DATUM68K->car_field); { { pccache += 1; { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; }; }; }; } } else if (tscache == 0) { { { pccache += 1; { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; }; }; }; } else if ( tscache == 0114) { { { pccache += 1; { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; }; }; }; } else { goto op_ufn; };
 case 002 : ; case002: if (((( (* (MDStypetbl+((tscache)>>9))) ) & 0x7ff) == 5)) {register ConsCell *DATUM68K = (ConsCell *)((Lisp_world + (tscache)));register int CDRCODEX = DATUM68K->cdr_code; if (CDRCODEX == 8) {  tscache = (0); { { pccache += 1; { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; }; }; }; } else if (CDRCODEX> 8) {  tscache = ((tscache) + ((CDRCODEX & 7) << 1)); { { pccache += 1; { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; }; }; }; } else if (CDRCODEX == 0) {   tscache = (cdr ((LispPTR)(DATUM68K->car_field))); { { pccache += 1; { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; }; }; }; } else {  tscache = ((ConsCell *)((Lisp_world + ((tscache) + (CDRCODEX << 1)))) )->car_field; { { pccache += 1; { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; }; }; }; } } else if (tscache == 0) { { { pccache += 1; { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; }; }; }; } else { goto op_ufn; };
 case 003 : ; case003: { if((DLword)(( (* (MDStypetbl+((tscache)>>9))) ) & 0x7ff) != 5) tscache = 0; { { pccache += 1; { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; }; }; }; };
 case 004 : ; case004: { tscache = 0xE0000 | (DLword)((( (* (MDStypetbl+((tscache)>>9))) ) & 0x7ff)); { { pccache += 1; { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; }; }; }; };
 case 005 : ; case005: { if((DLword)(( (* (MDStypetbl+((tscache)>>9))) ) & 0x7ff) != (((BYTECODE *)((pccache-1)+1))->code)) tscache = 0; { { pccache += 2; { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; }; }; }; };
 case 056 : ; case056: 
 case 006 : ; case006: { register int atom_index; register struct dtd *dtd68k ; atom_index = (((((BYTECODE *)((pccache-1) + 1))->code) << 24) | ((((BYTECODE *)((pccache-1) + 1+1))->code) << 16) | ((((BYTECODE *)((pccache-1) + 1+2))->code) << 8) | (((BYTECODE *)((pccache-1) + 1+3))->code)); for(dtd68k=(struct dtd *) (DTDspace + (((( (* (MDStypetbl+((tscache)>>9))) ) & 0x7ff))<<4)+(((( (* (MDStypetbl+((tscache)>>9))) ) & 0x7ff))<<1)); atom_index != dtd68k->dtd_name ; dtd68k=(struct dtd *) (DTDspace + ((dtd68k->dtd_supertype)<<4)+((dtd68k->dtd_supertype)<<1))) { if( dtd68k->dtd_supertype == 0) { goto op_ufn; } } {pccache += 5; { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; }; }; };
 case 007 : ; case007: { if ((int)((cspcache) = (LispPTR *) N_OP_unwind(((LispPTR *) cspcache), tscache, (((BYTECODE *)((pccache-1)+1))->code),  (((BYTECODE *)((pccache-1)+2))->code))) < 0) goto unwind_err; tscache = *(--(cspcache)); { { pccache += 3; { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; }; }; }; };
# 285 "../src/xc.c" 

 case 010 : ; case010: { {  register struct fnhead *LOCFNCELL; register int defcell_word; register int NEXTBLOCK; ; ; fn_defcell = (DefCell *)(((fn_atom_index = (((((BYTECODE *)((pccache-1) + 1))->code) << 24) | ((((BYTECODE *)((pccache-1) + 1+1))->code) << 16) | ((((BYTECODE *)((pccache-1) + 1+2))->code) << 8) | (((BYTECODE *)((pccache-1) + 1+3))->code)) & 0xfff0000) != 0) ? (LispPTR *)((Lisp_world + (fn_atom_index = (((((BYTECODE *)((pccache-1) + 1))->code) << 24) | ((((BYTECODE *)((pccache-1) + 1+1))->code) << 16) | ((((BYTECODE *)((pccache-1) + 1+2))->code) << 8) | (((BYTECODE *)((pccache-1) + 1+3))->code))))+4) : ((LispPTR *)Pnamespace + (5*(fn_atom_index = (((((BYTECODE *)((pccache-1) + 1))->code) << 24) | ((((BYTECODE *)((pccache-1) + 1+1))->code) << 16) | ((((BYTECODE *)((pccache-1) + 1+2))->code) << 8) | (((BYTECODE *)((pccache-1) + 1+3))->code))))+2) ); defcell_word = *(int *)fn_defcell; if(!(fn_defcell->ccodep)) {  fn_num_args = 0; fn_opcode_size = 5; fn_apply = 0; goto op_fn_common; } LOCFNCELL = (struct fnhead *)(Lisp_world + ((defcell_word &= 0xfffffff))); ((struct frameex2 *)((DLword *) ((LispPTR *) stateptrcache->pvar) - 10))->pc = ((unsigned int)(pccache-1) - (unsigned int)stateptrcache->currentfunc) + 5; ; if ((int)((LispPTR *) cspcache) > (stateptrcache->irqcheck=(stateptrcache->irqend-((LOCFNCELL->stkmin ) << 1)))) goto check_interrupt;; {register int newivar; newivar = (int) (stateptrcache->ivar = (DLword *)(((LispPTR *) cspcache)-0+1)); ((struct frameex2 *)((DLword *) ((LispPTR *) stateptrcache->pvar) - 10))->nextblock = NEXTBLOCK = (((unsigned int)(newivar) - (unsigned int)Stackspace) >>1); } *((cspcache)++) = tscache;  if( LOCFNCELL->na >= 0 ) {register int RESTARGS; RESTARGS = 0 - LOCFNCELL->na; while(RESTARGS <0) { *((cspcache)++) = 0; RESTARGS++; } (cspcache) -= (RESTARGS); }   *((cspcache)++) = 0x80000000 | NEXTBLOCK; *((LispPTR *)((LispPTR *) cspcache)) = (0xc000 << 16) | ((((unsigned int)(((LispPTR *) stateptrcache->pvar)) - (unsigned int)Stackspace) >>1)); ((struct frameex2 *)((LispPTR *) cspcache))->fnheader = (defcell_word); (cspcache) = (LispPTR *)(((DLword *)((LispPTR *) cspcache)) + 10); stateptrcache->pvar = (DLword *) ((LispPTR *) cspcache); {register int result; result = LOCFNCELL->pv; if (result >= 0) {register LispPTR unboundval; unboundval = (LispPTR) 0xffffffff; *((cspcache)++) = unboundval; *((cspcache)++) = unboundval; if (result > 0) {*((cspcache)++) = unboundval; *((cspcache)++) = unboundval; result-=1; for (; --result >= 0;) { *((cspcache)++) = unboundval; *((cspcache)++) = unboundval; } } } } (cspcache) += 1; pccache = (ByteCode *)LOCFNCELL + LOCFNCELL->startpc + 1; stateptrcache->currentfunc = LOCFNCELL; { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; }; }; };
# 291 "../src/xc.c" 

 case 011 : ; case011: { {  register struct fnhead *LOCFNCELL; register int defcell_word; register int NEXTBLOCK; ; ; fn_defcell = (DefCell *)(((fn_atom_index = (((((BYTECODE *)((pccache-1) + 1))->code) << 24) | ((((BYTECODE *)((pccache-1) + 1+1))->code) << 16) | ((((BYTECODE *)((pccache-1) + 1+2))->code) << 8) | (((BYTECODE *)((pccache-1) + 1+3))->code)) & 0xfff0000) != 0) ? (LispPTR *)((Lisp_world + (fn_atom_index = (((((BYTECODE *)((pccache-1) + 1))->code) << 24) | ((((BYTECODE *)((pccache-1) + 1+1))->code) << 16) | ((((BYTECODE *)((pccache-1) + 1+2))->code) << 8) | (((BYTECODE *)((pccache-1) + 1+3))->code))))+4) : ((LispPTR *)Pnamespace + (5*(fn_atom_index = (((((BYTECODE *)((pccache-1) + 1))->code) << 24) | ((((BYTECODE *)((pccache-1) + 1+1))->code) << 16) | ((((BYTECODE *)((pccache-1) + 1+2))->code) << 8) | (((BYTECODE *)((pccache-1) + 1+3))->code))))+2) ); defcell_word = *(int *)fn_defcell; if(!(fn_defcell->ccodep)) {  fn_num_args = 1; fn_opcode_size = 5; fn_apply = 0; goto op_fn_common; } LOCFNCELL = (struct fnhead *)(Lisp_world + ((defcell_word &= 0xfffffff))); ((struct frameex2 *)((DLword *) ((LispPTR *) stateptrcache->pvar) - 10))->pc = ((unsigned int)(pccache-1) - (unsigned int)stateptrcache->currentfunc) + 5; ; if ((int)((LispPTR *) cspcache) > (stateptrcache->irqcheck=(stateptrcache->irqend-((LOCFNCELL->stkmin ) << 1)))) goto check_interrupt;; {register int newivar; newivar = (int) (stateptrcache->ivar = (DLword *)(((LispPTR *) cspcache)-1+1)); ((struct frameex2 *)((DLword *) ((LispPTR *) stateptrcache->pvar) - 10))->nextblock = NEXTBLOCK = (((unsigned int)(newivar) - (unsigned int)Stackspace) >>1); } *((cspcache)++) = tscache;  if( LOCFNCELL->na >= 0 ) {register int RESTARGS; RESTARGS = 1 - LOCFNCELL->na; while(RESTARGS <0) { *((cspcache)++) = 0; RESTARGS++; } (cspcache) -= (RESTARGS); }   *((cspcache)++) = 0x80000000 | NEXTBLOCK; *((LispPTR *)((LispPTR *) cspcache)) = (0xc000 << 16) | ((((unsigned int)(((LispPTR *) stateptrcache->pvar)) - (unsigned int)Stackspace) >>1)); ((struct frameex2 *)((LispPTR *) cspcache))->fnheader = (defcell_word); (cspcache) = (LispPTR *)(((DLword *)((LispPTR *) cspcache)) + 10); stateptrcache->pvar = (DLword *) ((LispPTR *) cspcache); {register int result; result = LOCFNCELL->pv; if (result >= 0) {register LispPTR unboundval; unboundval = (LispPTR) 0xffffffff; *((cspcache)++) = unboundval; *((cspcache)++) = unboundval; if (result > 0) {*((cspcache)++) = unboundval; *((cspcache)++) = unboundval; result-=1; for (; --result >= 0;) { *((cspcache)++) = unboundval; *((cspcache)++) = unboundval; } } } } (cspcache) += 1; pccache = (ByteCode *)LOCFNCELL + LOCFNCELL->startpc + 1; stateptrcache->currentfunc = LOCFNCELL; { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; }; }; };
# 297 "../src/xc.c" 

 case 012 : ; case012: { {  register struct fnhead *LOCFNCELL; register int defcell_word; register int NEXTBLOCK; ; ; fn_defcell = (DefCell *)(((fn_atom_index = (((((BYTECODE *)((pccache-1) + 1))->code) << 24) | ((((BYTECODE *)((pccache-1) + 1+1))->code) << 16) | ((((BYTECODE *)((pccache-1) + 1+2))->code) << 8) | (((BYTECODE *)((pccache-1) + 1+3))->code)) & 0xfff0000) != 0) ? (LispPTR *)((Lisp_world + (fn_atom_index = (((((BYTECODE *)((pccache-1) + 1))->code) << 24) | ((((BYTECODE *)((pccache-1) + 1+1))->code) << 16) | ((((BYTECODE *)((pccache-1) + 1+2))->code) << 8) | (((BYTECODE *)((pccache-1) + 1+3))->code))))+4) : ((LispPTR *)Pnamespace + (5*(fn_atom_index = (((((BYTECODE *)((pccache-1) + 1))->code) << 24) | ((((BYTECODE *)((pccache-1) + 1+1))->code) << 16) | ((((BYTECODE *)((pccache-1) + 1+2))->code) << 8) | (((BYTECODE *)((pccache-1) + 1+3))->code))))+2) ); defcell_word = *(int *)fn_defcell; if(!(fn_defcell->ccodep)) {  fn_num_args = 2; fn_opcode_size = 5; fn_apply = 0; goto op_fn_common; } LOCFNCELL = (struct fnhead *)(Lisp_world + ((defcell_word &= 0xfffffff))); ((struct frameex2 *)((DLword *) ((LispPTR *) stateptrcache->pvar) - 10))->pc = ((unsigned int)(pccache-1) - (unsigned int)stateptrcache->currentfunc) + 5; ; if ((int)((LispPTR *) cspcache) > (stateptrcache->irqcheck=(stateptrcache->irqend-((LOCFNCELL->stkmin ) << 1)))) goto check_interrupt;; {register int newivar; newivar = (int) (stateptrcache->ivar = (DLword *)(((LispPTR *) cspcache)-2+1)); ((struct frameex2 *)((DLword *) ((LispPTR *) stateptrcache->pvar) - 10))->nextblock = NEXTBLOCK = (((unsigned int)(newivar) - (unsigned int)Stackspace) >>1); } *((cspcache)++) = tscache;  if( LOCFNCELL->na >= 0 ) {register int RESTARGS; RESTARGS = 2 - LOCFNCELL->na; while(RESTARGS <0) { *((cspcache)++) = 0; RESTARGS++; } (cspcache) -= (RESTARGS); }   *((cspcache)++) = 0x80000000 | NEXTBLOCK; *((LispPTR *)((LispPTR *) cspcache)) = (0xc000 << 16) | ((((unsigned int)(((LispPTR *) stateptrcache->pvar)) - (unsigned int)Stackspace) >>1)); ((struct frameex2 *)((LispPTR *) cspcache))->fnheader = (defcell_word); (cspcache) = (LispPTR *)(((DLword *)((LispPTR *) cspcache)) + 10); stateptrcache->pvar = (DLword *) ((LispPTR *) cspcache); {register int result; result = LOCFNCELL->pv; if (result >= 0) {register LispPTR unboundval; unboundval = (LispPTR) 0xffffffff; *((cspcache)++) = unboundval; *((cspcache)++) = unboundval; if (result > 0) {*((cspcache)++) = unboundval; *((cspcache)++) = unboundval; result-=1; for (; --result >= 0;) { *((cspcache)++) = unboundval; *((cspcache)++) = unboundval; } } } } (cspcache) += 1; pccache = (ByteCode *)LOCFNCELL + LOCFNCELL->startpc + 1; stateptrcache->currentfunc = LOCFNCELL; { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; }; }; };
# 303 "../src/xc.c" 

 case 013 : ; case013: { {  register struct fnhead *LOCFNCELL; register int defcell_word; register int NEXTBLOCK; ; ; fn_defcell = (DefCell *)(((fn_atom_index = (((((BYTECODE *)((pccache-1) + 1))->code) << 24) | ((((BYTECODE *)((pccache-1) + 1+1))->code) << 16) | ((((BYTECODE *)((pccache-1) + 1+2))->code) << 8) | (((BYTECODE *)((pccache-1) + 1+3))->code)) & 0xfff0000) != 0) ? (LispPTR *)((Lisp_world + (fn_atom_index = (((((BYTECODE *)((pccache-1) + 1))->code) << 24) | ((((BYTECODE *)((pccache-1) + 1+1))->code) << 16) | ((((BYTECODE *)((pccache-1) + 1+2))->code) << 8) | (((BYTECODE *)((pccache-1) + 1+3))->code))))+4) : ((LispPTR *)Pnamespace + (5*(fn_atom_index = (((((BYTECODE *)((pccache-1) + 1))->code) << 24) | ((((BYTECODE *)((pccache-1) + 1+1))->code) << 16) | ((((BYTECODE *)((pccache-1) + 1+2))->code) << 8) | (((BYTECODE *)((pccache-1) + 1+3))->code))))+2) ); defcell_word = *(int *)fn_defcell; if(!(fn_defcell->ccodep)) {  fn_num_args = 3; fn_opcode_size = 5; fn_apply = 0; goto op_fn_common; } LOCFNCELL = (struct fnhead *)(Lisp_world + ((defcell_word &= 0xfffffff))); ((struct frameex2 *)((DLword *) ((LispPTR *) stateptrcache->pvar) - 10))->pc = ((unsigned int)(pccache-1) - (unsigned int)stateptrcache->currentfunc) + 5; ; if ((int)((LispPTR *) cspcache) > (stateptrcache->irqcheck=(stateptrcache->irqend-((LOCFNCELL->stkmin ) << 1)))) goto check_interrupt;; {register int newivar; newivar = (int) (stateptrcache->ivar = (DLword *)(((LispPTR *) cspcache)-3+1)); ((struct frameex2 *)((DLword *) ((LispPTR *) stateptrcache->pvar) - 10))->nextblock = NEXTBLOCK = (((unsigned int)(newivar) - (unsigned int)Stackspace) >>1); } *((cspcache)++) = tscache;  if( LOCFNCELL->na >= 0 ) {register int RESTARGS; RESTARGS = 3 - LOCFNCELL->na; while(RESTARGS <0) { *((cspcache)++) = 0; RESTARGS++; } (cspcache) -= (RESTARGS); }   *((cspcache)++) = 0x80000000 | NEXTBLOCK; *((LispPTR *)((LispPTR *) cspcache)) = (0xc000 << 16) | ((((unsigned int)(((LispPTR *) stateptrcache->pvar)) - (unsigned int)Stackspace) >>1)); ((struct frameex2 *)((LispPTR *) cspcache))->fnheader = (defcell_word); (cspcache) = (LispPTR *)(((DLword *)((LispPTR *) cspcache)) + 10); stateptrcache->pvar = (DLword *) ((LispPTR *) cspcache); {register int result; result = LOCFNCELL->pv; if (result >= 0) {register LispPTR unboundval; unboundval = (LispPTR) 0xffffffff; *((cspcache)++) = unboundval; *((cspcache)++) = unboundval; if (result > 0) {*((cspcache)++) = unboundval; *((cspcache)++) = unboundval; result-=1; for (; --result >= 0;) { *((cspcache)++) = unboundval; *((cspcache)++) = unboundval; } } } } (cspcache) += 1; pccache = (ByteCode *)LOCFNCELL + LOCFNCELL->startpc + 1; stateptrcache->currentfunc = LOCFNCELL; { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; }; }; };
# 309 "../src/xc.c" 

 case 014 : ; case014: { {  register struct fnhead *LOCFNCELL; register int defcell_word; register int NEXTBLOCK; ; ; fn_defcell = (DefCell *)(((fn_atom_index = (((((BYTECODE *)((pccache-1) + 1))->code) << 24) | ((((BYTECODE *)((pccache-1) + 1+1))->code) << 16) | ((((BYTECODE *)((pccache-1) + 1+2))->code) << 8) | (((BYTECODE *)((pccache-1) + 1+3))->code)) & 0xfff0000) != 0) ? (LispPTR *)((Lisp_world + (fn_atom_index = (((((BYTECODE *)((pccache-1) + 1))->code) << 24) | ((((BYTECODE *)((pccache-1) + 1+1))->code) << 16) | ((((BYTECODE *)((pccache-1) + 1+2))->code) << 8) | (((BYTECODE *)((pccache-1) + 1+3))->code))))+4) : ((LispPTR *)Pnamespace + (5*(fn_atom_index = (((((BYTECODE *)((pccache-1) + 1))->code) << 24) | ((((BYTECODE *)((pccache-1) + 1+1))->code) << 16) | ((((BYTECODE *)((pccache-1) + 1+2))->code) << 8) | (((BYTECODE *)((pccache-1) + 1+3))->code))))+2) ); defcell_word = *(int *)fn_defcell; if(!(fn_defcell->ccodep)) {  fn_num_args = 4; fn_opcode_size = 5; fn_apply = 0; goto op_fn_common; } LOCFNCELL = (struct fnhead *)(Lisp_world + ((defcell_word &= 0xfffffff))); ((struct frameex2 *)((DLword *) ((LispPTR *) stateptrcache->pvar) - 10))->pc = ((unsigned int)(pccache-1) - (unsigned int)stateptrcache->currentfunc) + 5; ; if ((int)((LispPTR *) cspcache) > (stateptrcache->irqcheck=(stateptrcache->irqend-((LOCFNCELL->stkmin ) << 1)))) goto check_interrupt;; {register int newivar; newivar = (int) (stateptrcache->ivar = (DLword *)(((LispPTR *) cspcache)-4+1)); ((struct frameex2 *)((DLword *) ((LispPTR *) stateptrcache->pvar) - 10))->nextblock = NEXTBLOCK = (((unsigned int)(newivar) - (unsigned int)Stackspace) >>1); } *((cspcache)++) = tscache;  if( LOCFNCELL->na >= 0 ) {register int RESTARGS; RESTARGS = 4 - LOCFNCELL->na; while(RESTARGS <0) { *((cspcache)++) = 0; RESTARGS++; } (cspcache) -= (RESTARGS); }   *((cspcache)++) = 0x80000000 | NEXTBLOCK; *((LispPTR *)((LispPTR *) cspcache)) = (0xc000 << 16) | ((((unsigned int)(((LispPTR *) stateptrcache->pvar)) - (unsigned int)Stackspace) >>1)); ((struct frameex2 *)((LispPTR *) cspcache))->fnheader = (defcell_word); (cspcache) = (LispPTR *)(((DLword *)((LispPTR *) cspcache)) + 10); stateptrcache->pvar = (DLword *) ((LispPTR *) cspcache); {register int result; result = LOCFNCELL->pv; if (result >= 0) {register LispPTR unboundval; unboundval = (LispPTR) 0xffffffff; *((cspcache)++) = unboundval; *((cspcache)++) = unboundval; if (result > 0) {*((cspcache)++) = unboundval; *((cspcache)++) = unboundval; result-=1; for (; --result >= 0;) { *((cspcache)++) = unboundval; *((cspcache)++) = unboundval; } } } } (cspcache) += 1; pccache = (ByteCode *)LOCFNCELL + LOCFNCELL->startpc + 1; stateptrcache->currentfunc = LOCFNCELL; { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; }; }; };
# 315 "../src/xc.c" 

 case 015 : ; case015: { { register struct fnhead *LOCFNCELL; register DefCell *defcell;  register int NEXTBLOCK; int num_args = (((BYTECODE *)((pccache-1)+1))->code); defcell = (DefCell *) ((((((((BYTECODE *)((pccache-1) + 2))->code) << 24) | ((((BYTECODE *)((pccache-1) + 2+1))->code) << 16) | ((((BYTECODE *)((pccache-1) + 2+2))->code) << 8) | (((BYTECODE *)((pccache-1) + 2+3))->code)) & 0xfff0000) != 0) ? (LispPTR *)((Lisp_world + ((((((BYTECODE *)((pccache-1) + 2))->code) << 24) | ((((BYTECODE *)((pccache-1) + 2+1))->code) << 16) | ((((BYTECODE *)((pccache-1) + 2+2))->code) << 8) | (((BYTECODE *)((pccache-1) + 2+3))->code))))+4) : ((LispPTR *)Pnamespace + (5*((((((BYTECODE *)((pccache-1) + 2))->code) << 24) | ((((BYTECODE *)((pccache-1) + 2+1))->code) << 16) | ((((BYTECODE *)((pccache-1) + 2+2))->code) << 8) | (((BYTECODE *)((pccache-1) + 2+3))->code))))+2) ); ; ; if( defcell->ccodep == 0 ) { fn_defcell = defcell; fn_num_args = num_args; fn_opcode_size = 6; fn_atom_index = (((((BYTECODE *)((pccache-1) + 2))->code) << 24) | ((((BYTECODE *)((pccache-1) + 2+1))->code) << 16) | ((((BYTECODE *)((pccache-1) + 2+2))->code) << 8) | (((BYTECODE *)((pccache-1) + 2+3))->code)); fn_apply = 0; goto op_fn_common; } LOCFNCELL = (struct fnhead *)(Lisp_world + (defcell->defpointer)); ((struct frameex2 *)((DLword *) ((LispPTR *) stateptrcache->pvar) - 10))->pc = ((unsigned int)(pccache-1) - (unsigned int)stateptrcache->currentfunc) + 6; ; if ((int)((LispPTR *) cspcache) > (stateptrcache->irqcheck=(stateptrcache->irqend-((LOCFNCELL->stkmin ) << 1)))) goto check_interrupt;; {register int newivar; newivar = (int)(stateptrcache->ivar = (DLword *)(((LispPTR *) cspcache)-num_args+1)); ((struct frameex2 *)((DLword *) ((LispPTR *) stateptrcache->pvar) - 10))->nextblock = NEXTBLOCK = (((unsigned int)(newivar) - (unsigned int)Stackspace) >>1); } *((cspcache)++) = tscache;  if( LOCFNCELL->na >= 0 ) {register int RESTARGS; RESTARGS = num_args - LOCFNCELL->na; while(RESTARGS <0) { *((cspcache)++) = 0; RESTARGS++; } (cspcache) -= (RESTARGS); }   *((cspcache)++) = 0x80000000 | NEXTBLOCK; *((LispPTR *)((LispPTR *) cspcache)) = (0xc000 << 16) | ((((unsigned int)(((LispPTR *) stateptrcache->pvar)) - (unsigned int)Stackspace) >>1)); ((struct frameex2 *)((LispPTR *) cspcache))->fnheader = (defcell->defpointer); (cspcache) = (LispPTR *) (((DLword *)((LispPTR *) cspcache)) + 10); stateptrcache->pvar = (DLword *) ((LispPTR *) cspcache); {register int result; result = LOCFNCELL->pv; if (result >= 0) {register LispPTR unboundval; unboundval = (LispPTR) 0xffffffff; *((cspcache)++) = unboundval; *((cspcache)++) = unboundval; if (result > 0) {*((cspcache)++) = unboundval; *((cspcache)++) = unboundval; result-=1; for (; --result >= 0;) { *((cspcache)++) = unboundval; *((cspcache)++) = unboundval; } } } } (cspcache) += 1; pccache = (ByteCode *)LOCFNCELL + LOCFNCELL->startpc + 1; stateptrcache->currentfunc = LOCFNCELL; }; { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; }; };
# 321 "../src/xc.c" 

 case 016 : ; case016: { { if ( *((DLword *)(((LispPTR *) cspcache) - 1)) == 14 ) { fn_num_args = *((DLword *)(((LispPTR *) cspcache) - 1)+1); fn_opcode_size = 1; fn_apply = 1; fn_atom_index = tscache; ; ; if ( (0xfff0000 & tscache) == 0) { fn_defcell = (DefCell *) ((LispPTR *)Pnamespace + (5*(tscache))+2); goto op_fn_common; } else switch ((( (* (MDStypetbl+((tscache)>>9))) ) & 0x7ff)) { case 21: fn_defcell = (DefCell *) (LispPTR *)((Lisp_world + (tscache))+4); goto op_fn_common; case 13: stateptrcache->tosvalue=tscache; fn_defcell = (DefCell *) &stateptrcache->tosvalue; goto op_fn_common; default: fn_defcell = (DefCell *) (((0 & 0xfff0000) != 0) ? (LispPTR *)((Lisp_world + (0))+4) : ((LispPTR *)Pnamespace + (5*(0))+2) ); goto op_fn_common; }  } goto op_ufn; };};

 case 017 : ; case017: { { register DefCell *defcell; defcell = (DefCell *) (((tscache & 0xffff & 0xfff0000) != 0) ? (LispPTR *)((Lisp_world + (tscache & 0xffff))+4) : ((LispPTR *)Pnamespace + (5*(tscache & 0xffff))+2) ); if (!( defcell->ccodep && ((tscache & 0xfff0000) == 0) && ( ( defcell->argtype == 0 ) || ( defcell->argtype == 2 ) ) ) ) goto op_ufn; }; { { pccache += 1; { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; }; }; }; };
 case 020 : ; case020: { { register struct frameex2 *returnFX ; register int alink; alink = ((struct frameex2 *) ((struct frameex2 *)((DLword *) ((LispPTR *) stateptrcache->pvar) - 10)))->alink; ; if (alink & 1) { { stateptrcache->currentpc=pccache-1; stateptrcache->tosvalue=tscache; {stateptrcache->csp = (DLword *) (((LispPTR *) cspcache)-1);}; }; if(slowreturn()) goto stackoverflow_help; { pccache=stateptrcache->currentpc+1; {(cspcache) = ((LispPTR *) stateptrcache->csp)+1;}; tscache = stateptrcache->tosvalue; }; stateptrcache->irqcheck = ( (int)stateptrcache->endofstack - ((stateptrcache->currentfunc->stkmin ) << 1) ); if (((int)(((LispPTR *) cspcache)) > stateptrcache->irqcheck) || (stateptrcache->irqend <= 0)) { ; goto check_interrupt; } stateptrcache->irqend = (int) stateptrcache->endofstack; ; goto retxit; }; (cspcache) = (LispPTR *) ((LispPTR *) stateptrcache->ivar); returnFX = (struct frameex2 *) ((DLword *) (stateptrcache->pvar = (DLword *) (Stackspace + (alink))) - 10); stateptrcache->ivar = (DLword *) (Stackspace + ((* ((DLword *)returnFX -1))));  pccache = returnFX->pc + (ByteCode *) (stateptrcache->currentfunc = (struct fnhead *) (Lisp_world + ((returnFX->fnheader) & 0xfffffff))) + 1; stateptrcache->irqcheck = ( (int)stateptrcache->endofstack - ((stateptrcache->currentfunc->stkmin ) << 1) ); ; if (((int)(((LispPTR *) cspcache)) > stateptrcache->irqcheck) || (stateptrcache->irqend <= 0)) { ; goto check_interrupt; } stateptrcache->irqend = (int) stateptrcache->endofstack; ; retxit: {} }; { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; }; };

 case 021 : ; case021: {register int n1; register int n2; register LispPTR *ppvar; register int i; n1 = (((BYTECODE *)((pccache-1)+1))->code) >> 4; n2 = (((BYTECODE *)((pccache-1)+1))->code) & 0xf; ppvar = (LispPTR *)((LispPTR *) stateptrcache->pvar) + 1 + (((BYTECODE *)((pccache-1)+2))->code); for(i=n1; --i >= 0;){ *--ppvar = 0; } if(n2 == 0){ *(cspcache)++ = tscache; }else{ *--ppvar = tscache; for(i=1; i<n2; i++) { *--ppvar = *(--(cspcache)); } } i = ~(n1 + n2); tscache = (i<<16) | ((((BYTECODE *)((pccache-1)+2))->code)<<1); { { pccache += 3; { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; }; }; }; };
 case 022 : ; case022: {register int num; register LispPTR *ppvar; register int i; register LispPTR value; for(; ( ((int)*--(cspcache)) >= 0 );); value = *((LispPTR *) cspcache); num = (~value)>>16; ppvar = (LispPTR *)((DLword *)((LispPTR *) stateptrcache->pvar) + 2 + ((DLword)(value))); for(i=num; --i >= 0;){*--ppvar = 0xffffffff;} { { pccache += 1; { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; }; }; }; };
 case 023 : ; case023: {register int num; register LispPTR *ppvar; register int i; register LispPTR value; if((int)tscache < 0){ num =(~tscache)>>16; if(num != 0){ ppvar = (LispPTR *)((DLword *)((LispPTR *) stateptrcache->pvar) + 2 + ((DLword)(tscache))); for(i=num; --i >= 0;) { *--ppvar = 0xffffffff; } } }else{ for(; ( ((int)*--(cspcache)) >= 0 );); value = *((LispPTR *) cspcache); num = (~value)>>16; ppvar = (LispPTR *)((DLword *)((LispPTR *) stateptrcache->pvar) + 2 + ((DLword)(value))); for(i=num; --i >= 0;) { *--ppvar = 0xffffffff; } } tscache = *(--(cspcache)); { { pccache += 1; { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; }; }; }; };
 case 024 : ; case024: { tscache = N_OP_rplptr(*(--(cspcache)), tscache, (((BYTECODE *)((pccache-1)+1))->code)); { { pccache += 2; { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; }; }; }; };
 case 025 : ; case025: { { if ((!(( (* (MDStypetbl+(((tscache))>>9))) ) & 0x8000) && (*GcDisabled_word != 0114))) { if (*Reclaim_cnt_word != 0)  tscache = htfind(tscache,  (((BYTECODE *)((pccache-1)+1))->code)); else  tscache = rec_htfind(tscache,  (((BYTECODE *)((pccache-1)+1))->code)); } else  tscache = 0; }; { { pccache += 2; { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; }; }; };};
 case 026 : ; case026: {if ((int)(tscache = (LispPTR)N_OP_assoc(*(--(cspcache)), tscache)) < 0) goto exception_2; { { pccache += 1; { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; }; }; };;};
 case 027 : ; case027:
		     { N_OP_gvar_(tscache, (((((BYTECODE *)((pccache-1) + 1))->code) << 24) | ((((BYTECODE *)((pccache-1) + 1+1))->code) << 16) | ((((BYTECODE *)((pccache-1) + 1+2))->code) << 8) | (((BYTECODE *)((pccache-1) + 1+3))->code))); {pccache += 5; { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; }; }; };
 case 030 : ; case030: {if ((int)(tscache = (LispPTR)N_OP_rplaca(*(--(cspcache)), tscache)) < 0) goto ufn_2; { { pccache += 1; { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; }; }; };;};
 case 031 : ; case031: {if ((int)(tscache = (LispPTR)N_OP_rplacd(*(--(cspcache)), tscache)) < 0) goto ufn_2; { { pccache += 1; { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; }; }; };;};
 case 032 : ; case032: { tscache = N_OP_cons(*(--(cspcache)), tscache); { { pccache += 1; { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; }; }; }; };
 case 033 : ; case033: {if ((int)(tscache = (LispPTR)N_OP_classoc(*(--(cspcache)), tscache)) < 0) goto exception_2; { { pccache += 1; { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; }; }; };;};
 case 034 : ; case034: {if ((int)(tscache = (LispPTR)N_OP_fmemb(*(--(cspcache)), tscache)) < 0) goto exception_2; { { pccache += 1; { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; }; }; };;};
 case 035 : ; case035: {if ((int)(tscache = (LispPTR)N_OP_clfmemb(*(--(cspcache)), tscache)) < 0) goto exception_2; { { pccache += 1; { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; }; }; };;};
 case 036 : ; case036: { tscache = N_OP_findkey(tscache, (((BYTECODE *)((pccache-1)+1))->code)); { { pccache += 2; { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; }; }; }; };
 case 037 : ; case037: {if ((int)(tscache = (LispPTR)N_OP_createcell(tscache)) < 0) goto fix_tos_ufn;{ { pccache += 1; { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; }; }; };;};
 case 040 : ; case040: { register Stream *stream68k;  register char *buff68k;  if ( (( (* (MDStypetbl+((tscache)>>9))) ) & 0x7ff) == 11 ) { stream68k=(Stream *) (Lisp_world + (tscache)); if( ( !stream68k->BINABLE ) || ( stream68k->COFFSET >= stream68k->CBUFSIZE ) ) goto op_ufn;  buff68k =(char *)(Lisp_world + (stream68k->CBUFPTR));  tscache = (0xE0000 | ((((BYTECODE *)(buff68k + (stream68k->COFFSET)++))->code)) ); { { pccache += 1; { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; }; }; }; } else goto op_ufn; };
 case 041 : ; case041: { goto op_ufn; } 
 case 042 : ; case042: { goto op_ufn; } 
 case 043 : ; case043: {tscache = N_OP_restlist(*(--(cspcache)), tscache, (((BYTECODE *)((pccache-1)+1))->code)); { { pccache += 2; { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; }; }; };};
 case 044 : ; case044: { { stateptrcache->currentpc=pccache-1; stateptrcache->tosvalue=tscache; {stateptrcache->csp = (DLword *) (((LispPTR *) cspcache)-1);}; }; if (OP_miscn((((BYTECODE *)((pccache-1)+1))->code), (((BYTECODE *)((pccache-1)+2))->code))) { { pccache=stateptrcache->currentpc+1; {(cspcache) = ((LispPTR *) stateptrcache->csp)+1;}; tscache = stateptrcache->tosvalue; };  goto op_ufn; } { pccache=stateptrcache->currentpc+1; {(cspcache) = ((LispPTR *) stateptrcache->csp)+1;}; tscache = stateptrcache->tosvalue; }; { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; }; };
 case 045 : ; case045: { goto op_ufn; }  
 case 046 : ; case046: {if ((int)(tscache = (LispPTR)N_OP_rplcons(*(--(cspcache)), tscache)) < 0) goto ufn_2; { { pccache += 1; { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; }; }; };;};
 case 047 : ; case047: {if ((int)(tscache = (LispPTR)N_OP_listget(*(--(cspcache)), tscache)) < 0) goto exception_2C; { { pccache += 1; { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; }; }; };;};
 case 050 : ; case050: { goto op_ufn; }  
 case 051 : ; case051: { goto op_ufn; }  
 case 052 : ; case052: { goto op_ufn; }  
 case 053 : ; case053: { goto op_ufn; }  
 case 054 : ; case054: { LispPTR scratch; register LispPTR work; register LispPTR lookuped;  switch(tscache & 0xfff0000) { case 0xE0000: case 0xF0000: { { pccache += 1; { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; }; }; }; case 0x00000: if( (tscache==0) ||(tscache==0114)) goto Hack_Label; nnewframe(((struct frameex1 *)(((DLword *) stateptrcache->pvar) - 10)),&scratch, tscache & 0xffff); work = ((scratch & 0xffff0000)>> 16) | ((scratch & 0x0fff) <<16); lookuped = *((LispPTR *) ((Lisp_world + (work)))); if(lookuped==1) goto op_ufn; tscache = lookuped; Hack_Label: { { pccache += 1; { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; }; }; }; default: switch((( (* (MDStypetbl+((tscache)>>9))) ) & 0x7ff)) { case 2 : case 3 : case 7 : case 14 : case 16 : { { pccache += 1; { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; }; }; }; case 5 : fn_atom_index = 248; fn_num_args = 1; fn_opcode_size = 1; fn_defcell = (DefCell *) (((248 & 0xfff0000) != 0) ? (LispPTR *)((Lisp_world + (248))+4) : ((LispPTR *)Pnamespace + (5*(248))+2) ); fn_apply = 0; goto op_fn_common; case 21: nnewframe(((struct frameex1 *)(((DLword *) stateptrcache->pvar) - 10)), &scratch, tscache); work = 0xfffffff & swapx(scratch); lookuped = *((LispPTR *) ((Lisp_world + (work)))); if(lookuped==1) goto op_ufn; tscache = lookuped; { { pccache += 1; { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; }; }; }; default : goto op_ufn; } }  };
# 360 "../src/xc.c" 

 case 055 : ; case055: { { register struct fnhead *LOCFNCELL; register int NEXTBLOCK; register LispPTR closure_env = tscache; register int num_args; register LispPTR Fn_DefCell= *(((LispPTR *) cspcache) - 1); LOCFNCELL = (struct fnhead *)(Lisp_world + (Fn_DefCell)); ; ; {  num_args = *(((LispPTR *) cspcache) - 2);  switch(0xfff0000 &  num_args){ case 0xE0000:  num_args = 0xFFFF & ( num_args); break; case 0xF0000:  num_args = 0xFFFF0000 | ( num_args); break; default: if ((( (* (MDStypetbl+((  num_args )>>9))) ) & 0x7ff) != 2) { goto  op_ufn; }  num_args = *((int *)(Lisp_world + ( num_args))); } }; ((struct frameex2 *)((DLword *) ((LispPTR *) stateptrcache->pvar) - 10))->pc = ((unsigned int)(pccache-1) - (unsigned int)stateptrcache->currentfunc) + 1; ; if ((int)((LispPTR *) cspcache) > (stateptrcache->irqcheck=(stateptrcache->irqend-((LOCFNCELL->stkmin ) << 1)))) goto check_interrupt;; (cspcache) -= 2; {register int newivar; newivar = (int) (stateptrcache->ivar = (DLword *) (((LispPTR *) cspcache)-num_args)); ((struct frameex2 *)((DLword *) ((LispPTR *) stateptrcache->pvar) - 10))->nextblock = NEXTBLOCK = (((unsigned int)(newivar) - (unsigned int)Stackspace) >>1); } if( LOCFNCELL->na >= 0 ) {register int RESTARGS; RESTARGS = num_args - LOCFNCELL->na; while(RESTARGS <0) { *((cspcache)++) = 0; RESTARGS++; } (cspcache) -= (RESTARGS); }   *((cspcache)++) = 0x80000000 | NEXTBLOCK; *((LispPTR *)((LispPTR *) cspcache)) = (0xc000 << 16) | ((((unsigned int)(((LispPTR *) stateptrcache->pvar)) - (unsigned int)Stackspace) >>1)); ((struct frameex2 *)((LispPTR *) cspcache))->fnheader = (Fn_DefCell); (cspcache) = (LispPTR *)(((DLword *)((LispPTR *) cspcache)) + 10); stateptrcache->pvar = (DLword *) ((LispPTR *) cspcache); {register int result; result = LOCFNCELL->pv; if (result >= 0) {register LispPTR unboundval; unboundval = (LispPTR) 0xffffffff; if (closure_env == 0) *((cspcache)++) = unboundval; else *((cspcache)++) = closure_env; *((cspcache)++) = unboundval; if (result > 0) {*((cspcache)++) = unboundval; *((cspcache)++) = unboundval; result-=1; for (; --result >= 0;) { *((cspcache)++) = unboundval; *((cspcache)++) = unboundval; } } } } (cspcache) += 1; pccache = (ByteCode *)LOCFNCELL + LOCFNCELL->startpc + 1; stateptrcache->currentfunc = LOCFNCELL; ; }; { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; }; };


 case 057 : ; case057: {tscache = N_OP_stkscan(tscache); { { pccache += 1; { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; }; }; }; };
 case 060 : ; case060: { goto op_ufn; } 
 case 061 : ; case061: { goto op_ufn; } 
 case 062 : ; case062: {tscache = N_OP_ubfloat3(*(((LispPTR *) cspcache)-2), *(((LispPTR *) cspcache)-1), tscache,  (((BYTECODE *)((pccache-1)+1))->code)); if (stateptrcache->errorexit) goto fix_tos_ufn; (cspcache) -= 2; { { pccache += 2; { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; }; }; };;};
 case 063 : ; case063: { if( ( ((DLword)( (* (MDStypetbl+((tscache)>>9))) )) & ( (DLword)(((BYTECODE *)((pccache-1)+1))->code) << 8)) == 0) tscache = 0; { { pccache += 2; { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; }; }; }; };
 case 064 : ; case064: { goto op_ufn; } 
 case 065 : ; case065: { goto op_ufn; } 
 case 066 : ; case066: { goto op_ufn; } 
 case 067 : ; case067: { goto op_ufn; } 
 case 070 : ; case070: {if ((int)(tscache = (LispPTR)N_OP_misc7( *(((LispPTR *) cspcache)-6), *(((LispPTR *) cspcache)-5), *(((LispPTR *) cspcache)-4), *(((LispPTR *) cspcache)-3), *(((LispPTR *) cspcache)-2), *(((LispPTR *) cspcache)-1), tscache,  (((BYTECODE *)((pccache-1)+1))->code))) < 0) goto fix_tos_ufn; (cspcache) -= 6; { { pccache += 2; { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; }; }; };;};	   
 case 071 : ; case071: { goto op_ufn; } 
 case 072 : ; case072: {if ((int)(tscache = (LispPTR)N_OP_eqlop(*(--(cspcache)), tscache)) < 0) goto ufn_2; { { pccache += 1; { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; }; }; };;};
 case 073 : ; case073: {if ((int)(tscache = (LispPTR)N_OP_drawline( *(((LispPTR *) cspcache)-8), *(((LispPTR *) cspcache)-7), *(((LispPTR *) cspcache)-6), *(((LispPTR *) cspcache)-5), *(((LispPTR *) cspcache)-4), *(((LispPTR *) cspcache)-3), *(((LispPTR *) cspcache)-2), *(((LispPTR *) cspcache)-1), tscache )) < 0) goto fix_tos_ufn; (cspcache) -= 8; { { pccache += 1; { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; }; }; };;};
 case 074 : ; case074: { *(((LispPTR *) cspcache) - (((((BYTECODE *)((pccache-1)+1))->code)+2) >> 1)) = tscache; { { pccache += 2; { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; }; }; }; };
 case 075 : ; case075: { {*((cspcache)++) = tscache; tscache = *(((LispPTR *) cspcache) - (((((BYTECODE *)((pccache-1)+1))->code)+2) >> 1));}; { { pccache += 2; { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; }; }; }; };
 case 076 : ; case076: { goto op_ufn; } 
 case 077 : ; case077: { goto op_ufn; } 



 case 0100 : ; case100:  { register LispPTR *var = (LispPTR *)stateptrcache->ivar; *((cspcache)++) = tscache; {register unsigned char opcode; opcode = *(unsigned char *)((pccache-1)+1); tscache = *(var + 0); pccache += 1; fast_dispatcher(table, opcode);} goto nextopcode; };  
 case 0101 : ; case101:  { register LispPTR *var = (LispPTR *)stateptrcache->ivar; *((cspcache)++) = tscache; {register unsigned char opcode; opcode = *(unsigned char *)((pccache-1)+1); tscache = *(var + 1); pccache += 1; fast_dispatcher(table, opcode);} goto nextopcode; };  
 case 0102 : ; case102:  { register LispPTR *var = (LispPTR *)stateptrcache->ivar; *((cspcache)++) = tscache; {register unsigned char opcode; opcode = *(unsigned char *)((pccache-1)+1); tscache = *(var + 2); pccache += 1; fast_dispatcher(table, opcode);} goto nextopcode; };  
 case 0103 : ; case103:  { register LispPTR *var = (LispPTR *)stateptrcache->ivar; *((cspcache)++) = tscache; {register unsigned char opcode; opcode = *(unsigned char *)((pccache-1)+1); tscache = *(var + 3); pccache += 1; fast_dispatcher(table, opcode);} goto nextopcode; };  
 case 0104 : ; case104:  { register LispPTR *var = (LispPTR *)stateptrcache->ivar; *((cspcache)++) = tscache; {register unsigned char opcode; opcode = *(unsigned char *)((pccache-1)+1); tscache = *(var + 4); pccache += 1; fast_dispatcher(table, opcode);} goto nextopcode; };  
 case 0105 : ; case105:  { register LispPTR *var = (LispPTR *)stateptrcache->ivar; *((cspcache)++) = tscache; {register unsigned char opcode; opcode = *(unsigned char *)((pccache-1)+1); tscache = *(var + 5); pccache += 1; fast_dispatcher(table, opcode);} goto nextopcode; };  
 case 0106 : ; case106:  { register LispPTR *var = (LispPTR *)stateptrcache->ivar; *((cspcache)++) = tscache; {register unsigned char opcode; opcode = *(unsigned char *)((pccache-1)+1); tscache = *(var + 6); pccache += 1; fast_dispatcher(table, opcode);} goto nextopcode; };   
 case 0107 : ; case107:  { {*((cspcache)++) = tscache; tscache = (*((int *) ((DLword *)((LispPTR *) stateptrcache->ivar) + (((BYTECODE *)((pccache-1)+1))->code))));}; { { pccache += 2; { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; }; }; }; };   

 case 0110 : ; case110:  { register LispPTR *var = (LispPTR *)stateptrcache->pvar; *((cspcache)++) = tscache; {register unsigned char opcode; opcode = *(unsigned char *)((pccache-1)+1); tscache = *(var + 0); pccache += 1; fast_dispatcher(table, opcode);} goto nextopcode; };  
 case 0111 : ; case111:  { register LispPTR *var = (LispPTR *)stateptrcache->pvar; *((cspcache)++) = tscache; {register unsigned char opcode; opcode = *(unsigned char *)((pccache-1)+1); tscache = *(var + 1); pccache += 1; fast_dispatcher(table, opcode);} goto nextopcode; }; 
 case 0112 : ; case112:  { register LispPTR *var = (LispPTR *)stateptrcache->pvar; *((cspcache)++) = tscache; {register unsigned char opcode; opcode = *(unsigned char *)((pccache-1)+1); tscache = *(var + 2); pccache += 1; fast_dispatcher(table, opcode);} goto nextopcode; };  
 case 0113 : ; case113:  { register LispPTR *var = (LispPTR *)stateptrcache->pvar; *((cspcache)++) = tscache; {register unsigned char opcode; opcode = *(unsigned char *)((pccache-1)+1); tscache = *(var + 3); pccache += 1; fast_dispatcher(table, opcode);} goto nextopcode; };  
 case 0114 : ; case114:  { register LispPTR *var = (LispPTR *)stateptrcache->pvar; *((cspcache)++) = tscache; {register unsigned char opcode; opcode = *(unsigned char *)((pccache-1)+1); tscache = *(var + 4); pccache += 1; fast_dispatcher(table, opcode);} goto nextopcode; };  
 case 0115 : ; case115:  { register LispPTR *var = (LispPTR *)stateptrcache->pvar; *((cspcache)++) = tscache; {register unsigned char opcode; opcode = *(unsigned char *)((pccache-1)+1); tscache = *(var + 5); pccache += 1; fast_dispatcher(table, opcode);} goto nextopcode; };  
 case 0116 : ; case116:  { register LispPTR *var = (LispPTR *)stateptrcache->pvar; *((cspcache)++) = tscache; {register unsigned char opcode; opcode = *(unsigned char *)((pccache-1)+1); tscache = *(var + 6); pccache += 1; fast_dispatcher(table, opcode);} goto nextopcode; };    

 case 0117 : ; case117: { {*((cspcache)++) = tscache; tscache = (*((int *) ((DLword *)((LispPTR *) stateptrcache->pvar) + (((BYTECODE *)((pccache-1)+1))->code))));}; { { pccache += 2; { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; }; }; }; };

 case 0120 : ; case120: { register LispPTR *chain; chain = (LispPTR *) (stateptrcache->pvar + 0); if(((WBITS *) (chain))->LSB){ {*((cspcache)++) = tscache; tscache = (*((int *) ((Lisp_world + ( 0xfffffff & swapx(native_newframe(0 >> 1)))))));}; { { pccache += 1; { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; }; }; }; } {*((cspcache)++) = tscache; tscache = (*((int *) ((Lisp_world + (0xfffffff & swapx(*chain))))));}; { { pccache += 1; { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; }; }; }; };
 case 0121 : ; case121: { register LispPTR *chain; chain = (LispPTR *) (stateptrcache->pvar + 2); if(((WBITS *) (chain))->LSB){ {*((cspcache)++) = tscache; tscache = (*((int *) ((Lisp_world + ( 0xfffffff & swapx(native_newframe(2 >> 1)))))));}; { { pccache += 1; { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; }; }; }; } {*((cspcache)++) = tscache; tscache = (*((int *) ((Lisp_world + (0xfffffff & swapx(*chain))))));}; { { pccache += 1; { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; }; }; }; };
 case 0122 : ; case122: { register LispPTR *chain; chain = (LispPTR *) (stateptrcache->pvar + 4); if(((WBITS *) (chain))->LSB){ {*((cspcache)++) = tscache; tscache = (*((int *) ((Lisp_world + ( 0xfffffff & swapx(native_newframe(4 >> 1)))))));}; { { pccache += 1; { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; }; }; }; } {*((cspcache)++) = tscache; tscache = (*((int *) ((Lisp_world + (0xfffffff & swapx(*chain))))));}; { { pccache += 1; { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; }; }; }; };
 case 0123 : ; case123: { register LispPTR *chain; chain = (LispPTR *) (stateptrcache->pvar + 6); if(((WBITS *) (chain))->LSB){ {*((cspcache)++) = tscache; tscache = (*((int *) ((Lisp_world + ( 0xfffffff & swapx(native_newframe(6 >> 1)))))));}; { { pccache += 1; { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; }; }; }; } {*((cspcache)++) = tscache; tscache = (*((int *) ((Lisp_world + (0xfffffff & swapx(*chain))))));}; { { pccache += 1; { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; }; }; }; };
 case 0124 : ; case124: { register LispPTR *chain; chain = (LispPTR *) (stateptrcache->pvar + 8); if(((WBITS *) (chain))->LSB){ {*((cspcache)++) = tscache; tscache = (*((int *) ((Lisp_world + ( 0xfffffff & swapx(native_newframe(8 >> 1)))))));}; { { pccache += 1; { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; }; }; }; } {*((cspcache)++) = tscache; tscache = (*((int *) ((Lisp_world + (0xfffffff & swapx(*chain))))));}; { { pccache += 1; { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; }; }; }; };
 case 0125 : ; case125: { register LispPTR *chain; chain = (LispPTR *) (stateptrcache->pvar + 10); if(((WBITS *) (chain))->LSB){ {*((cspcache)++) = tscache; tscache = (*((int *) ((Lisp_world + ( 0xfffffff & swapx(native_newframe(10 >> 1)))))));}; { { pccache += 1; { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; }; }; }; } {*((cspcache)++) = tscache; tscache = (*((int *) ((Lisp_world + (0xfffffff & swapx(*chain))))));}; { { pccache += 1; { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; }; }; }; };
 case 0126 : ; case126: { register LispPTR *chain; chain = (LispPTR *) (stateptrcache->pvar + 12); if(((WBITS *) (chain))->LSB){ {*((cspcache)++) = tscache; tscache = (*((int *) ((Lisp_world + ( 0xfffffff & swapx(native_newframe(12 >> 1)))))));}; { { pccache += 1; { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; }; }; }; } {*((cspcache)++) = tscache; tscache = (*((int *) ((Lisp_world + (0xfffffff & swapx(*chain))))));}; { { pccache += 1; { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; }; }; }; };
 case 0127 : ; case127: { register int nn = (((BYTECODE *)((pccache-1)+1))->code); register LispPTR *chain; chain = (LispPTR *) (stateptrcache->pvar + nn); if(((WBITS *) (chain))->LSB){ {*((cspcache)++) = tscache; tscache = (*((int *) ((Lisp_world + ( 0xfffffff & swapx(native_newframe(nn >> 1)))))));}; { { pccache += 2; { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; }; }; }; } {*((cspcache)++) = tscache; tscache = (*((int *) ((Lisp_world + (0xfffffff & swapx(*chain))))));}; { { pccache += 2; { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; }; }; }; };
		
 case 0130 : ; case130: {((LispPTR *) stateptrcache->pvar)[0] = tscache; { { pccache += 1; { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; }; }; };}; 
 case 0131 : ; case131: {((LispPTR *) stateptrcache->pvar)[1] = tscache; { { pccache += 1; { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; }; }; };}; 
 case 0132 : ; case132: {((LispPTR *) stateptrcache->pvar)[2] = tscache; { { pccache += 1; { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; }; }; };};
 case 0133 : ; case133: {((LispPTR *) stateptrcache->pvar)[3] = tscache; { { pccache += 1; { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; }; }; };}; 
 case 0134 : ; case134: {((LispPTR *) stateptrcache->pvar)[4] = tscache; { { pccache += 1; { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; }; }; };}; 
 case 0135 : ; case135: {((LispPTR *) stateptrcache->pvar)[5] = tscache; { { pccache += 1; { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; }; }; };}; 
 case 0136 : ; case136: {((LispPTR *) stateptrcache->pvar)[6] = tscache; { { pccache += 1; { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; }; }; };}; 

 case 0137 : ; case137: { *((LispPTR *)((DLword *)((LispPTR *) stateptrcache->pvar)+(((BYTECODE *)((pccache-1)+1))->code)))=tscache; { { pccache += 2; { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; }; }; };};
 
 case 0140 : ; case140: { register int tx = (((((BYTECODE *)((pccache-1) + 1))->code) << 24) | ((((BYTECODE *)((pccache-1) + 1+1))->code) << 16) | ((((BYTECODE *)((pccache-1) + 1+2))->code) << 8) | (((BYTECODE *)((pccache-1) + 1+3))->code)); if (tx & 0xfff0000) { {*((cspcache)++) = tscache; tscache = (*((int *) ( (Lisp_world + ((tx)+2)))));}; } else {*((cspcache)++) = tscache; tscache = (*((int *) ((LispPTR *)Pnamespace + (tx*5) + 1)));}; {pccache += 5; { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; }; }; };
 case 0141 : ; case141: {if ((int)(tscache = (LispPTR)N_OP_arg0(tscache)) < 0) goto fix_tos_ufn;{ { pccache += 1; { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; }; }; };;};
 case 0142 : ; case142: { *((LispPTR *)((DLword *)((LispPTR *) stateptrcache->ivar)+(((BYTECODE *)((pccache-1)+1))->code)))=tscache; { { pccache += 2; { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; }; }; };};
 case 0143 : ; case143: {tscache = N_OP_fvar_(tscache, (((BYTECODE *)((pccache-1)+1))->code)); { { pccache += 2; { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; }; }; }; };
 case 0144 : ; case144: { *((cspcache)++) = tscache; { { pccache += 1; { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; }; }; }; };
 case 0145 : ; case145: { register int arg_num; if (( ((struct frameex1 *)(((DLword *) stateptrcache->pvar) - 10))->alink & 1) == 0) arg_num = (int)((LispPTR *)(((struct frameex1 *)(((DLword *) stateptrcache->pvar) - 10))) - 1); else arg_num = (int)(Stackspace + ((struct frameex1 *)(((DLword *) stateptrcache->pvar) - 10))->blink); {*((cspcache)++) = tscache; tscache =  (DLword)((arg_num - (int)stateptrcache->ivar) >> 2) | 0xE0000;}; { { pccache += 1; { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; }; }; }; };
 case 0146 : ; case146: { {*((cspcache)++) = tscache; tscache = ((( ((struct frameex1 *)(((DLword *) stateptrcache->pvar) - 10))->alink) & 0xfffe)-10) | 0xE0000;}; { { pccache += 1; { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; }; }; }; };


 case 0147 : ; case147: { {*((cspcache)++) = tscache; tscache = (((((BYTECODE *)((pccache-1) + 1))->code) << 24) | ((((BYTECODE *)((pccache-1) + 1+1))->code) << 16) | ((((BYTECODE *)((pccache-1) + 1+2))->code) << 8) | (((BYTECODE *)((pccache-1) + 1+3))->code));}; {pccache += 5; { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; }; };}
 case 0150 : ; case150: { {{*((cspcache)++) = tscache; tscache = 0     ;}; { { pccache += 1; { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; }; }; };}; }
 case 0151 : ; case151: { {{*((cspcache)++) = tscache; tscache = 0114      ;}; { { pccache += 1; { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; }; }; };}; }
 case 0152 : ; case152: { {{*((cspcache)++) = tscache; tscache = 0xE0000  ;}; { { pccache += 1; { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; }; }; };}; } 
 case 0153 : ; case153: { {{*((cspcache)++) = tscache; tscache = 0xE0001     ;}; { { pccache += 1; { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; }; }; };}; } 


 case 0154 : ; case154: {	
 		{*((cspcache)++) = tscache; tscache = 0xE0000 | (((BYTECODE *)((pccache-1)+1))->code);};
 		{ { pccache += 2; { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; }; }; };
		}


 case 0155 : ; case155: { 	
		{*((cspcache)++) = tscache; tscache = 0xF0000 | 0xff00 | (((BYTECODE *)((pccache-1)+1))->code);};
 		{ { pccache += 2; { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; }; }; };
		}


 case 0156 : ; case156:{ 	
 		{*((cspcache)++) = tscache; tscache = 0xE0000 | (((((BYTECODE *)((pccache-1)+1))->code) <<8) | (((BYTECODE *)((pccache-1)+1+1))->code));};
 		{ { pccache += 3; { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; }; }; };
		}


 case 0157 : ; case157: {
		{*((cspcache)++) = tscache; tscache = (((((BYTECODE *)((pccache-1) + 1))->code) << 24) | ((((BYTECODE *)((pccache-1) + 1+1))->code) << 16) | ((((BYTECODE *)((pccache-1) + 1+2))->code) << 8) | (((BYTECODE *)((pccache-1) + 1+3))->code));};
		{pccache += 5; { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; }; };
		}
 
 case 0160 : ; case160: { goto op_ufn; } 
 case 0161 : ; case161: { goto op_ufn; } 
 case 0162 : ; case162: { goto op_ufn; } 
 case 0163 : ; case163: { goto op_ufn; } 
 case 0164 : ; case164: { goto op_ufn; } 
 case 0165 : ; case165: { goto op_ufn; } 

 case 0166 : ; case166: {tscache = N_OP_pilotbitblt(*(--(cspcache)), tscache); { { pccache += 1; { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; }; }; }; };
 case 0167 : ; case167: { tscache = N_OP_rclk(tscache); { { pccache += 1; { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; }; }; }; };
 case 0170 : ; case170: { goto op_ufn; } 
 case 0171 : ; case171: { goto op_ufn; } 
 case 0172 : ; case172: { goto op_ufn; };
 case 0173 : ; case173: { tscache=gcscan1(tscache & 0xffff); if (tscache) {tscache |= 0xE0000; };{ { pccache += 1; { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; }; }; };};
 case 0174 : ; case174: { tscache=gcscan2(tscache & 0xffff); if (tscache) {tscache |=0xE0000; };{ { pccache += 1; { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; }; }; };};
 case 0175 : ; case175: { { stateptrcache->currentpc=pccache-1; stateptrcache->tosvalue=tscache; {stateptrcache->csp = (DLword *) (((LispPTR *) cspcache)-1);}; }; OP_subrcall((((BYTECODE *)((pccache-1)+1))->code), (((BYTECODE *)((pccache-1)+2))->code)); { pccache=stateptrcache->currentpc+1; {(cspcache) = ((LispPTR *) stateptrcache->csp)+1;}; tscache = stateptrcache->tosvalue; }; { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; }; };
 case 0176 : ; case176: { { { stateptrcache->currentpc=pccache-1; stateptrcache->tosvalue=tscache; {stateptrcache->csp = (DLword *) (((LispPTR *) cspcache)-1);}; }; OP_contextsw(); { pccache=stateptrcache->currentpc+1; {(cspcache) = ((LispPTR *) stateptrcache->csp)+1;}; tscache = stateptrcache->tosvalue; };  {stateptrcache->irqcheck = ( (int)(stateptrcache->irqend = (int) stateptrcache->endofstack) - (( stateptrcache->currentfunc->stkmin ) << 1) ); }; { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; }; }; }
 case 0177 : ; case177: { goto op_ufn; } 



 case 0200 : ; case200: { {{if((int)((LispPTR *) cspcache) > stateptrcache->irqcheck) goto check_interrupt;}; pccache += 2; { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; };}; }
 case 0201 : ; case201: { {{if((int)((LispPTR *) cspcache) > stateptrcache->irqcheck) goto check_interrupt;}; pccache += 3; { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; };}; }
 case 0202 : ; case202: { {{if((int)((LispPTR *) cspcache) > stateptrcache->irqcheck) goto check_interrupt;}; pccache += 4; { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; };}; }
 case 0203 : ; case203: { {{if((int)((LispPTR *) cspcache) > stateptrcache->irqcheck) goto check_interrupt;}; pccache += 5; { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; };}; }
 case 0204 : ; case204: { {{if((int)((LispPTR *) cspcache) > stateptrcache->irqcheck) goto check_interrupt;}; pccache += 6; { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; };}; }
 case 0205 : ; case205: { {{if((int)((LispPTR *) cspcache) > stateptrcache->irqcheck) goto check_interrupt;}; pccache += 7; { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; };}; }
 case 0206 : ; case206: { {{if((int)((LispPTR *) cspcache) > stateptrcache->irqcheck) goto check_interrupt;}; pccache += 8; { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; };}; }
 case 0207 : ; case207: { {{if((int)((LispPTR *) cspcache) > stateptrcache->irqcheck) goto check_interrupt;}; pccache += 9; { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; };}; }
 case 0210 : ; case210: { {{if((int)((LispPTR *) cspcache) > stateptrcache->irqcheck) goto check_interrupt;}; pccache += 10; { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; };}; }
 case 0211 : ; case211: { {{if((int)((LispPTR *) cspcache) > stateptrcache->irqcheck) goto check_interrupt;}; pccache += 11; { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; };}; }
 case 0212 : ; case212: { {{if((int)((LispPTR *) cspcache) > stateptrcache->irqcheck) goto check_interrupt;}; pccache += 12; { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; };}; }
 case 0213 : ; case213: { {{if((int)((LispPTR *) cspcache) > stateptrcache->irqcheck) goto check_interrupt;}; pccache += 13; { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; };}; }
 case 0214 : ; case214: { {{if((int)((LispPTR *) cspcache) > stateptrcache->irqcheck) goto check_interrupt;}; pccache += 14; { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; };}; }
 case 0215 : ; case215: { {{if((int)((LispPTR *) cspcache) > stateptrcache->irqcheck) goto check_interrupt;}; pccache += 15; { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; };}; }
 case 0216 : ; case216: { {{if((int)((LispPTR *) cspcache) > stateptrcache->irqcheck) goto check_interrupt;}; pccache += 16; { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; };}; }
 case 0217 : ; case217: { {{if((int)((LispPTR *) cspcache) > stateptrcache->irqcheck) goto check_interrupt;}; pccache += 17; { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; };}; }




 case 0220 : ; case220: { {if(tscache != 0) {goto PopNextop1 ; } {{if((int)((LispPTR *) cspcache) > stateptrcache->irqcheck) goto check_interrupt;}; tscache = *(--(cspcache)); pccache += 2; { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; };} }; }
 case 0221 : ; case221: { {if(tscache != 0) {goto PopNextop1 ; } {{if((int)((LispPTR *) cspcache) > stateptrcache->irqcheck) goto check_interrupt;}; tscache = *(--(cspcache)); pccache += 3; { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; };} }; }
 case 0222 : ; case222: { {if(tscache != 0) {goto PopNextop1 ; } {{if((int)((LispPTR *) cspcache) > stateptrcache->irqcheck) goto check_interrupt;}; tscache = *(--(cspcache)); pccache += 4; { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; };} }; }
 case 0223 : ; case223: { {if(tscache != 0) {goto PopNextop1 ; } {{if((int)((LispPTR *) cspcache) > stateptrcache->irqcheck) goto check_interrupt;}; tscache = *(--(cspcache)); pccache += 5; { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; };} }; }
 case 0224 : ; case224: { {if(tscache != 0) {goto PopNextop1 ; } {{if((int)((LispPTR *) cspcache) > stateptrcache->irqcheck) goto check_interrupt;}; tscache = *(--(cspcache)); pccache += 6; { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; };} }; }
 case 0225 : ; case225: { {if(tscache != 0) {goto PopNextop1 ; } {{if((int)((LispPTR *) cspcache) > stateptrcache->irqcheck) goto check_interrupt;}; tscache = *(--(cspcache)); pccache += 7; { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; };} }; }
 case 0226 : ; case226: { {if(tscache != 0) {goto PopNextop1 ; } {{if((int)((LispPTR *) cspcache) > stateptrcache->irqcheck) goto check_interrupt;}; tscache = *(--(cspcache)); pccache += 8; { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; };} }; }
 case 0227 : ; case227: { {if(tscache != 0) {goto PopNextop1 ; } {{if((int)((LispPTR *) cspcache) > stateptrcache->irqcheck) goto check_interrupt;}; tscache = *(--(cspcache)); pccache += 9; { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; };} }; }
 case 0230 : ; case230: { {if(tscache != 0) {goto PopNextop1 ; } {{if((int)((LispPTR *) cspcache) > stateptrcache->irqcheck) goto check_interrupt;}; tscache = *(--(cspcache)); pccache += 10; { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; };} }; }
 case 0231 : ; case231: { {if(tscache != 0) {goto PopNextop1 ; } {{if((int)((LispPTR *) cspcache) > stateptrcache->irqcheck) goto check_interrupt;}; tscache = *(--(cspcache)); pccache += 11; { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; };} }; }
 case 0232 : ; case232: { {if(tscache != 0) {goto PopNextop1 ; } {{if((int)((LispPTR *) cspcache) > stateptrcache->irqcheck) goto check_interrupt;}; tscache = *(--(cspcache)); pccache += 12; { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; };} }; }
 case 0233 : ; case233: { {if(tscache != 0) {goto PopNextop1 ; } {{if((int)((LispPTR *) cspcache) > stateptrcache->irqcheck) goto check_interrupt;}; tscache = *(--(cspcache)); pccache += 13; { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; };} }; }
 case 0234 : ; case234: { {if(tscache != 0) {goto PopNextop1 ; } {{if((int)((LispPTR *) cspcache) > stateptrcache->irqcheck) goto check_interrupt;}; tscache = *(--(cspcache)); pccache += 14; { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; };} }; }
 case 0235 : ; case235: { {if(tscache != 0) {goto PopNextop1 ; } {{if((int)((LispPTR *) cspcache) > stateptrcache->irqcheck) goto check_interrupt;}; tscache = *(--(cspcache)); pccache += 15; { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; };} }; }
 case 0236 : ; case236: { {if(tscache != 0) {goto PopNextop1 ; } {{if((int)((LispPTR *) cspcache) > stateptrcache->irqcheck) goto check_interrupt;}; tscache = *(--(cspcache)); pccache += 16; { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; };} }; }
 case 0237 : ; case237: { {if(tscache != 0) {goto PopNextop1 ; } {{if((int)((LispPTR *) cspcache) > stateptrcache->irqcheck) goto check_interrupt;}; tscache = *(--(cspcache)); pccache += 17; { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; };} }; }



 case 0240 : ; case240: { {if(tscache == 0) {goto PopNextop1 ; } {{if((int)((LispPTR *) cspcache) > stateptrcache->irqcheck) goto check_interrupt;}; tscache = *(--(cspcache)); pccache += 2; { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; };} }; }
 case 0241 : ; case241: { {if(tscache == 0) {goto PopNextop1 ; } {{if((int)((LispPTR *) cspcache) > stateptrcache->irqcheck) goto check_interrupt;}; tscache = *(--(cspcache)); pccache += 3; { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; };} }; }
 case 0242 : ; case242: { {if(tscache == 0) {goto PopNextop1 ; } {{if((int)((LispPTR *) cspcache) > stateptrcache->irqcheck) goto check_interrupt;}; tscache = *(--(cspcache)); pccache += 4; { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; };} }; }
 case 0243 : ; case243: { {if(tscache == 0) {goto PopNextop1 ; } {{if((int)((LispPTR *) cspcache) > stateptrcache->irqcheck) goto check_interrupt;}; tscache = *(--(cspcache)); pccache += 5; { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; };} }; }
 case 0244 : ; case244: { {if(tscache == 0) {goto PopNextop1 ; } {{if((int)((LispPTR *) cspcache) > stateptrcache->irqcheck) goto check_interrupt;}; tscache = *(--(cspcache)); pccache += 6; { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; };} }; }
 case 0245 : ; case245: { {if(tscache == 0) {goto PopNextop1 ; } {{if((int)((LispPTR *) cspcache) > stateptrcache->irqcheck) goto check_interrupt;}; tscache = *(--(cspcache)); pccache += 7; { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; };} }; }
 case 0246 : ; case246: { {if(tscache == 0) {goto PopNextop1 ; } {{if((int)((LispPTR *) cspcache) > stateptrcache->irqcheck) goto check_interrupt;}; tscache = *(--(cspcache)); pccache += 8; { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; };} }; }
 case 0247 : ; case247: { {if(tscache == 0) {goto PopNextop1 ; } {{if((int)((LispPTR *) cspcache) > stateptrcache->irqcheck) goto check_interrupt;}; tscache = *(--(cspcache)); pccache += 9; { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; };} }; }
 case 0250 : ; case250: { {if(tscache == 0) {goto PopNextop1 ; } {{if((int)((LispPTR *) cspcache) > stateptrcache->irqcheck) goto check_interrupt;}; tscache = *(--(cspcache)); pccache += 10; { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; };} }; }
 case 0251 : ; case251: { {if(tscache == 0) {goto PopNextop1 ; } {{if((int)((LispPTR *) cspcache) > stateptrcache->irqcheck) goto check_interrupt;}; tscache = *(--(cspcache)); pccache += 11; { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; };} }; }
 case 0252 : ; case252: { {if(tscache == 0) {goto PopNextop1 ; } {{if((int)((LispPTR *) cspcache) > stateptrcache->irqcheck) goto check_interrupt;}; tscache = *(--(cspcache)); pccache += 12; { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; };} }; }
 case 0253 : ; case253: { {if(tscache == 0) {goto PopNextop1 ; } {{if((int)((LispPTR *) cspcache) > stateptrcache->irqcheck) goto check_interrupt;}; tscache = *(--(cspcache)); pccache += 13; { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; };} }; }
 case 0254 : ; case254: { {if(tscache == 0) {goto PopNextop1 ; } {{if((int)((LispPTR *) cspcache) > stateptrcache->irqcheck) goto check_interrupt;}; tscache = *(--(cspcache)); pccache += 14; { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; };} }; }
 case 0255 : ; case255: { {if(tscache == 0) {goto PopNextop1 ; } {{if((int)((LispPTR *) cspcache) > stateptrcache->irqcheck) goto check_interrupt;}; tscache = *(--(cspcache)); pccache += 15; { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; };} }; }
 case 0256 : ; case256: { {if(tscache == 0) {goto PopNextop1 ; } {{if((int)((LispPTR *) cspcache) > stateptrcache->irqcheck) goto check_interrupt;}; tscache = *(--(cspcache)); pccache += 16; { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; };} }; }
 case 0257 : ; case257: { {if(tscache == 0) {goto PopNextop1 ; } {{if((int)((LispPTR *) cspcache) > stateptrcache->irqcheck) goto check_interrupt;}; tscache = *(--(cspcache)); pccache += 17; { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; };} }; }


 case 0260 : ; case260: {
		{if((int)((LispPTR *) cspcache) > stateptrcache->irqcheck) goto check_interrupt;};
		pccache += (* ((s_char *)(pccache-1)+1)); { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; }; 
		}


 case 0261 : ; case261: {
		{if((int)((LispPTR *) cspcache) > stateptrcache->irqcheck) goto check_interrupt;};
		pccache += ((* ((s_char *)(pccache-1)+1))<<8) | (((BYTECODE *)((pccache-1)+2))->code); { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; }; 
		}


 case 0262 : ; case262: {
    if(tscache != 0) {goto PopNextop2;}
	{if((int)((LispPTR *) cspcache) > stateptrcache->irqcheck) goto check_interrupt;};
	tscache = *(--(cspcache));
	pccache += (* ((s_char *)(pccache-1)+1));
	{ fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; }; 
	}



 case 0263 : ; case263: {
	if(tscache == 0) {goto PopNextop2;}
	{if((int)((LispPTR *) cspcache) > stateptrcache->irqcheck) goto check_interrupt;};
	tscache = *(--(cspcache));
	pccache += (* ((s_char *)(pccache-1)+1));
	{ fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; }; 
	}



 case 0264 : ; case264: {
	if(tscache != 0) {goto PopNextop2;}
	{if((int)((LispPTR *) cspcache) > stateptrcache->irqcheck) goto check_interrupt;};
	pccache += (* ((s_char *)(pccache-1)+1));
	{ fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; }; 
	}



 case 0265 : ; case265: {
	if(tscache == 0) {goto PopNextop2;}
	{if((int)((LispPTR *) cspcache) > stateptrcache->irqcheck) goto check_interrupt;};
	pccache += (* ((s_char *)(pccache-1)+1));
	{ fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; }; 
	}

 case 0266 : ; case266:	{ LispPTR arrayarg; register LispPTR baseL; register int index; register OneDArray *arrayblk; DLword *createcell68k(); ; arrayarg = *(--(cspcache)); if ((( (* (MDStypetbl+((arrayarg)>>9))) ) & 0x7ff) != 14) goto aref_ufn; arrayblk = (OneDArray *)(Lisp_world + (arrayarg)); if ((tscache & 0xfff0000) != 0xE0000) goto aref_ufn; index = tscache & 0xFFFF; if (index >= arrayblk->totalsize) goto aref_ufn; index += arrayblk->offset; baseL = arrayblk->base; switch (arrayblk->typenumber) { case 38:  tscache = *(((int *)(Lisp_world + (baseL))) + index); { { pccache += 1; { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; }; }; }; case 20:  tscache = ((* (((DLword *)(Lisp_world + (baseL))) + index))) & 0xFFFF; if (tscache & 0x8000) tscache |= 0xF0000; else tscache |= 0xE0000; { { pccache += 1; { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; }; }; }; case 67:  tscache = 0x70000 | (((* (((char *)(Lisp_world + (baseL))) + index))) & 0xFF); { { pccache += 1; { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; }; }; }; case 22:  tscache = *(((int *)(Lisp_world + (baseL))) + index); switch(tscache & 0xFFFF0000){ case 0: tscache |= 0xE0000; break; case (unsigned)0xFFFF0000: tscache &= 0xF0000; break; default:{register DLword *wordp; wordp = createcell68k(2); *((int *)wordp) = tscache; tscache = (LispPTR)(((unsigned int)(wordp) - (unsigned int)Lisp_world) >>1); } } { { pccache += 1; { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; }; }; }; case 0:  tscache = 0xE0000 | ((((* (((char *)(Lisp_world + (baseL))) + (index >> 3)))) >> (7 - (index & 7))) & 1); { { pccache += 1; { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; }; }; }; case 3:  tscache = 0xE0000 | (((* (((char *)(Lisp_world + (baseL))) + index))) & 0xFF); { { pccache += 1; { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; }; }; }; case 4:  tscache = 0xE0000 | (((* (((DLword *)(Lisp_world + (baseL))) + index))) & 0xFFFF); { { pccache += 1; { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; }; }; }; case 54: {register DLword *wordp; wordp = createcell68k(3); *((int *)wordp) = *(((int *)(Lisp_world + (baseL))) + index); tscache = (LispPTR)(((unsigned int)(wordp) - (unsigned int)Lisp_world) >>1); } { { pccache += 1; { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; }; }; }; case 68:  tscache = 0x70000 | (((* (((DLword *)(Lisp_world + (baseL))) + index))) & 0xFFFF); { { pccache += 1; { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; }; }; }; case 86:  tscache = *(((int *)(Lisp_world + (baseL))) + index); { { pccache += 1; { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; }; }; }; default:  goto aref_ufn; } aref_ufn: if ((int)(tscache = (LispPTR)N_OP_aref1( arrayarg, tscache)) < 0) goto ufn_2; { { pccache += 1; { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; }; }; };; };
 case 0267 : ; case267:	{if ((int)(tscache = (LispPTR)N_OP_aset1( *(((LispPTR *) cspcache)-2), *(((LispPTR *) cspcache)-1), tscache)) < 0) goto fix_tos_ufn; (cspcache) -= 2; { { pccache += 1; { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; }; }; };;};

 case 0270 : ; case270:	{((LispPTR *) stateptrcache->pvar)[0] = tscache; tscache = *(--(cspcache)); { { pccache += 1; { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; }; }; };};
 case 0271 : ; case271:	{((LispPTR *) stateptrcache->pvar)[1] = tscache; tscache = *(--(cspcache)); { { pccache += 1; { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; }; }; };};
 case 0272 : ; case272:	{((LispPTR *) stateptrcache->pvar)[2] = tscache; tscache = *(--(cspcache)); { { pccache += 1; { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; }; }; };};
 case 0273 : ; case273:	{((LispPTR *) stateptrcache->pvar)[3] = tscache; tscache = *(--(cspcache)); { { pccache += 1; { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; }; }; };};
 case 0274 : ; case274:	{((LispPTR *) stateptrcache->pvar)[4] = tscache; tscache = *(--(cspcache)); { { pccache += 1; { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; }; }; };};
 case 0275 : ; case275:	{((LispPTR *) stateptrcache->pvar)[5] = tscache; tscache = *(--(cspcache)); { { pccache += 1; { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; }; }; };};
 case 0276 : ; case276:	{((LispPTR *) stateptrcache->pvar)[6] = tscache; tscache = *(--(cspcache)); { { pccache += 1; { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; }; }; };};

 case 0277 : ; case277: 	{ tscache = *(--(cspcache)); { { pccache += 1; { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; }; }; }; }

 case 0300 : ; case300:  {tscache = *((cspcache) -= (((((BYTECODE *)((pccache-1)+1))->code))+1)); { { pccache += 2; { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; }; }; }; };
 case 0301 : ; case301: 	{ register int nn = (((BYTECODE *)((pccache-1)+1))->code); if (0==((unsigned int)tscache & 0xfff0000)) {  switch (nn) { case 3:  tscache = (8 << 16) + (10*(unsigned int)tscache) + 6; break; case 8:  tscache = (8 << 16) + (10*(unsigned int)tscache) + 0; break; case 12:  tscache = (8 << 16) + (10*(unsigned int)tscache) + 2; break; case 10:  tscache = (8 << 16) + (10*(unsigned int)tscache) + 4; break; default: goto op_ufn; } { { pccache += 2; { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; }; }; }; } else if (21 == (( (* (MDStypetbl+((tscache)>>9))) ) & 0x7ff)) {  switch (nn) { case 3:  tscache = tscache + 6; break; case 8:  tscache = tscache + 0; break; case 12:  tscache = tscache + 2; break; case 10:  tscache = tscache + 4; break; default: goto op_ufn; } { { pccache += 2; { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; }; }; }; } else goto op_ufn; };
 case 0302 : ; case302: 	{switch( (0xfff0000 & tscache) ){ case 0xE0000: tscache &= 0x0000FFFF; break; case 0xF0000: tscache |= 0xFFFF0000; break; default: if( (( (* (MDStypetbl+((tscache)>>9))) ) & 0x7ff) == 2 ) tscache = *((int *)(Lisp_world + (tscache))); else goto op_ufn; } tscache = (0xFF & ((* ((char*)(Lisp_world + ((0xfffffff & (*(--(cspcache)))))) + tscache)))) | 0xE0000; { { pccache += 1; { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; }; }; }; };
 case 0303 : ; case303:  { tscache = N_OP_instancep(tscache,(((((BYTECODE *)((pccache-1) + 1))->code) << 24) | ((((BYTECODE *)((pccache-1) + 1+1))->code) << 16) | ((((BYTECODE *)((pccache-1) + 1+2))->code) << 8) | (((BYTECODE *)((pccache-1) + 1+3))->code))); {pccache += 5; { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; }; }; };
 case 0304 : ; case304:  {if ((int)(tscache = (LispPTR)N_OP_blt( *(((LispPTR *) cspcache)-2), *(((LispPTR *) cspcache)-1), tscache)) < 0) goto fix_tos_ufn; (cspcache) -= 2; { { pccache += 1; { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; }; }; };;};
 case 0305 : ; case305:  {goto op_ufn; } 
 case 0306 : ; case306:  {goto op_ufn; } 
 case 0307 : ; case307:	{ register int byteoffset; register char *p_data; if(((0xfff0000 & tscache) != 0xE0000) || ((unsigned short)tscache >= 256)) goto op_ufn; byteoffset = *(((LispPTR *) cspcache) - 1); switch( (0xfff0000 & byteoffset) ){ case 0xE0000: byteoffset &= 0x0000FFFF; break; case 0xF0000: byteoffset |= 0xFFFF0000; break; default: goto op_ufn;  } --(cspcache); p_data = (char*)(Lisp_world + (0xfffffff & (*(--(cspcache))))) + byteoffset; (* (p_data)) = 0xFF & tscache; { { pccache += 1; { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; }; }; }; };
 case 0310 : ; case310:	{ tscache = (0xE0000 | (* ((DLword *) (Lisp_world + ((0xfffffff & tscache) + (((BYTECODE *)((pccache-1)+1))->code)))))); { { pccache += 2; { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; }; }; }; };
 case 0311 : ; case311:	{ tscache = (0xfffffff & *((LispPTR *) (Lisp_world + ((0xfffffff & tscache) + (((BYTECODE *)((pccache-1)+1))->code))))); { { pccache += 2; { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; }; }; }; };
 case 0312 : ; case312:	{register int temp, bb =  (((BYTECODE *)((pccache-1)+2))->code); temp = 0xF & bb; tscache = 0xE0000 | (( ((* ((Lisp_world + (0xfffffff & (tscache+(((BYTECODE *)((pccache-1)+1))->code))))))) >> (16 - ( (0xF & (bb >> 4)) + temp + 1)) ) & n_mask_array[temp] ); { { pccache += 3; { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; }; }; }; };
 case 0313 : ; case313:  {goto op_ufn; } 
 case 0314 : ; case314:	{if ((int)(tscache = (LispPTR)N_OP_clequal(*(--(cspcache)), tscache)) < 0) goto ufn_2; { { pccache += 1; { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; }; }; };;};
 case 0315 : ; case315:	{ register int base; if (((DLword)((tscache)>>16)) != (0xE0000 >> 16)) goto op_ufn; base = 0xfffffff & *(--(cspcache)); (* ((DLword *)(Lisp_world + (base + (((BYTECODE *)((pccache-1)+1))->code))))) = ((DLword)(tscache)); tscache = base; { { pccache += 2; { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; }; }; }; };
 case 0316 : ; case316:	{ register int base; base = 0xfffffff & *(--(cspcache)); *((LispPTR *)(Lisp_world + (base + (((BYTECODE *)((pccache-1)+1))->code)))) = tscache; tscache = base; { { pccache += 2; { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; }; }; }; };
 case 0317 : ; case317:	{ int base; register int bb =  (((BYTECODE *)((pccache-1)+2))->code); register DLword *pword; register int shift_size, field_size, fmask; if( (0xfff0000 & tscache) != 0xE0000 ){ goto op_ufn; }; base = 0xfffffff & *(--(cspcache)); pword = (DLword*)(Lisp_world + ( base + (((BYTECODE *)((pccache-1)+1))->code) )); field_size = 0xF & bb; shift_size = 15 - (0xF & (bb >> 4)) - field_size; fmask = n_mask_array[field_size] << shift_size; (* (pword)) = ( (tscache << shift_size) & fmask) | ((* (pword)) & (~fmask)); tscache = base; { { pccache += 3; { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; }; }; }; };

 case 0320 : ; case320:	{if ((int)(tscache = (LispPTR)N_OP_addbase(*(--(cspcache)), tscache)) < 0) goto ufn_2; { { pccache += 1; { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; }; }; };;};
 case 0321 : ; case321:	{ tscache = (*(((LispPTR *) cspcache) - 1) << 16) | (0xFFFF & tscache); (cspcache)--; { { pccache += 1; { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; }; }; }; };
 case 0322 : ; case322:	{ tscache = ((DLword)((tscache)>>16)) | 0xE0000; { { pccache += 1; { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; }; }; }; };
 case 0323 : ; case323:	{ tscache = ((DLword)(tscache)) | 0xE0000; { { pccache += 1; { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; }; }; }; };
 case 0324 : ; case324: 	{register int arg1, arg2, result; arg1 = *(((LispPTR *) cspcache) - 1);  if(!(((tscache) >> 17) ^ 7) && !(((arg1) >> 17) ^ 7)) { arg2 = ( ((int)tscache << 15) >> 15 ); arg1 = ( ((int)arg1 << 15) >> 15 ); result = arg1 + arg2; { if ((((result << 15) >>15) ^ result)) {register LispPTR *wordp; wordp = (LispPTR *) createcell68k(2); *((int *)wordp) = result;  tscache = ((((unsigned int)(wordp) - (unsigned int)Lisp_world) >>1)); } else  tscache = (( (unsigned)result <<15) >>15) | 0xE0000;}; *(--(cspcache)); { { pccache += 1; { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; }; }; };} if ((int)(tscache = (LispPTR) N_OP_plus2(*(--(cspcache)), tscache)) < 0) goto ufn_2; { { pccache += 1; { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; }; }; };; }; 
 case 0325 : ; case325:  {register int arg1, arg2, result; arg1 = *(((LispPTR *) cspcache) - 1);  if(!(((tscache) >> 17) ^ 7) && !(((arg1) >> 17) ^ 7)) { arg2 = ( ((int)tscache << 15) >> 15 ); arg1 = ( ((int)arg1 << 15) >> 15 ); result = arg1 - arg2; { if ((((result << 15) >>15) ^ result)) {register LispPTR *wordp; wordp = (LispPTR *) createcell68k(2); *((int *)wordp) = result;  tscache = ((((unsigned int)(wordp) - (unsigned int)Lisp_world) >>1)); } else  tscache = (( (unsigned)result <<15) >>15) | 0xE0000;}; *(--(cspcache)); { { pccache += 1; { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; }; }; };} if ((int)(tscache = (LispPTR) N_OP_difference(*(--(cspcache)), tscache)) < 0) goto ufn_2; { { pccache += 1; { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; }; }; };; };		
 case 0326 : ; case326:	{if ((int)(tscache = (LispPTR)N_OP_times2(*(--(cspcache)), tscache)) < 0) goto ufn_2; { { pccache += 1; { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; }; }; };;}; 
 case 0327 : ; case327:  {if ((int)(tscache = (LispPTR)N_OP_quot(*(--(cspcache)), tscache)) < 0) goto ufn_2; { { pccache += 1; { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; }; }; };;} 
 case 0330 : ; case330:  {register int arg1, arg2, result; arg1 = *(((LispPTR *) cspcache) - 1);  if(!(((tscache) >> 17) ^ 7) && !(((arg1) >> 17) ^ 7)) { arg2 = ( ((int)tscache << 15) >> 15 ); arg1 = ( ((int)arg1 << 15) >> 15 ); result = arg1 + arg2; { if ((((result << 15) >>15) ^ result)) {register LispPTR *wordp; wordp = (LispPTR *) createcell68k(2); *((int *)wordp) = result;  tscache = ((((unsigned int)(wordp) - (unsigned int)Lisp_world) >>1)); } else  tscache = (( (unsigned)result <<15) >>15) | 0xE0000;}; *(--(cspcache)); { { pccache += 1; { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; }; }; };} if ((int)(tscache = (LispPTR) N_OP_iplus2(*(--(cspcache)), tscache)) < 0) goto ufn_2; { { pccache += 1; { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; }; }; };; }; 
 case 0331 : ; case331:  {register int arg1, arg2, result; arg1 = *(((LispPTR *) cspcache) - 1);  if(!(((tscache) >> 17) ^ 7) && !(((arg1) >> 17) ^ 7)) { arg2 = ( ((int)tscache << 15) >> 15 ); arg1 = ( ((int)arg1 << 15) >> 15 ); result = arg1 - arg2; { if ((((result << 15) >>15) ^ result)) {register LispPTR *wordp; wordp = (LispPTR *) createcell68k(2); *((int *)wordp) = result;  tscache = ((((unsigned int)(wordp) - (unsigned int)Lisp_world) >>1)); } else  tscache = (( (unsigned)result <<15) >>15) | 0xE0000;}; *(--(cspcache)); { { pccache += 1; { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; }; }; };} if ((int)(tscache = (LispPTR) N_OP_idifference(*(--(cspcache)), tscache)) < 0) goto ufn_2; { { pccache += 1; { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; }; }; };; }; 
 case 0332 : ; case332:	{if ((int)(tscache = (LispPTR)N_OP_itimes2(*(--(cspcache)), tscache)) < 0) goto ufn_2; { { pccache += 1; { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; }; }; };;}; 
 case 0333 : ; case333:	{if ((int)(tscache = (LispPTR)N_OP_iquot(*(--(cspcache)), tscache)) < 0) goto ufn_2; { { pccache += 1; { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; }; }; };;}; 
 case 0334 : ; case334:	{if ((int)(tscache = (LispPTR)N_OP_iremainder(*(--(cspcache)), tscache)) < 0) goto ufn_2; { { pccache += 1; { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; }; }; };;};
 case 0335 : ; case335:	{if ((int)(tscache = (LispPTR)N_OP_iplusn(tscache,  (((BYTECODE *)((pccache-1)+1))->code))) < 0) goto fix_tos_ufn;{ { pccache += 2; { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; }; }; };};
 case 0336 : ; case336:	{if ((int)(tscache = (LispPTR)N_OP_idifferencen(tscache,  (((BYTECODE *)((pccache-1)+1))->code))) < 0) goto fix_tos_ufn;{ { pccache += 2; { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; }; }; };;};
 case 0337 : ; case337:  { goto op_ufn; } 
 case 0340 : ; case340:  { register int arg, result; { if ((((tscache) >> 17) ^ 7)) if ((( (* (MDStypetbl+((tscache)>>9))) ) & 0x7ff) != 2)  goto op_ufn; else   arg = *((int *)(Lisp_world + (tscache))); else   arg = ( ((int)tscache << 15) >> 15 );};; result = arg << 1; if ( (arg < 0)) goto op_ufn; { if ((((result << 15) >>15) ^ result)) {register LispPTR *wordp; wordp = (LispPTR *) createcell68k(2); *((int *)wordp) = result;  tscache = ((((unsigned int)(wordp) - (unsigned int)Lisp_world) >>1)); } else  tscache = (( (unsigned)result <<15) >>15) | 0xE0000;}; { { pccache += 1; { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; }; }; };};
 case 0341 : ; case341:  { register int arg, result; { if ((((tscache) >> 17) ^ 7)) if ((( (* (MDStypetbl+((tscache)>>9))) ) & 0x7ff) != 2)  goto op_ufn; else   arg = *((int *)(Lisp_world + (tscache))); else   arg = ( ((int)tscache << 15) >> 15 );};; result = arg << 8; if ( ((arg >> 24)!=0)) goto op_ufn; { if ((((result << 15) >>15) ^ result)) {register LispPTR *wordp; wordp = (LispPTR *) createcell68k(2); *((int *)wordp) = result;  tscache = ((((unsigned int)(wordp) - (unsigned int)Lisp_world) >>1)); } else  tscache = (( (unsigned)result <<15) >>15) | 0xE0000;}; { { pccache += 1; { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; }; }; };};
 case 0342 : ; case342:  { register int arg, result; { if ((((tscache) >> 17) ^ 7)) if ((( (* (MDStypetbl+((tscache)>>9))) ) & 0x7ff) != 2)  goto op_ufn; else   arg = *((int *)(Lisp_world + (tscache))); else   arg = ( ((int)tscache << 15) >> 15 );};; result = (unsigned)arg >> 1; if ( 0) goto op_ufn; { if ((((result << 15) >>15) ^ result)) {register LispPTR *wordp; wordp = (LispPTR *) createcell68k(2); *((int *)wordp) = result;  tscache = ((((unsigned int)(wordp) - (unsigned int)Lisp_world) >>1)); } else  tscache = (( (unsigned)result <<15) >>15) | 0xE0000;}; { { pccache += 1; { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; }; }; };};
 case 0343 : ; case343:  { register int arg, result; { if ((((tscache) >> 17) ^ 7)) if ((( (* (MDStypetbl+((tscache)>>9))) ) & 0x7ff) != 2)  goto op_ufn; else   arg = *((int *)(Lisp_world + (tscache))); else   arg = ( ((int)tscache << 15) >> 15 );};; result = (unsigned)arg >> 8; if ( 0) goto op_ufn; { if ((((result << 15) >>15) ^ result)) {register LispPTR *wordp; wordp = (LispPTR *) createcell68k(2); *((int *)wordp) = result;  tscache = ((((unsigned int)(wordp) - (unsigned int)Lisp_world) >>1)); } else  tscache = (( (unsigned)result <<15) >>15) | 0xE0000;}; { { pccache += 1; { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; }; }; };};
 case 0344 : ; case344:  { register int arg1, arg2, result; arg1 = *(((LispPTR *) cspcache) - 1);  { if ((((tscache) >> 17) ^ 7)) if ((( (* (MDStypetbl+((tscache)>>9))) ) & 0x7ff) != 2)  goto op_ufn; else   arg2 = *((int *)(Lisp_world + (tscache))); else   arg2 = ( ((int)tscache << 15) >> 15 );};; { if ((((arg1) >> 17) ^ 7)) if ((( (* (MDStypetbl+((arg1)>>9))) ) & 0x7ff) != 2)  goto op_ufn; else   arg1 = *((int *)(Lisp_world + (arg1))); else   arg1 = ( ((int)arg1 << 15) >> 15 );};; result = arg1 | arg2; if ( 0) goto op_ufn; { if ((((result << 15) >>15) ^ result)) {register LispPTR *wordp; wordp = (LispPTR *) createcell68k(2); *((int *)wordp) = result;  tscache = ((((unsigned int)(wordp) - (unsigned int)Lisp_world) >>1)); } else  tscache = (( (unsigned)result <<15) >>15) | 0xE0000;}; *(--(cspcache)); { { pccache += 1; { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; }; }; };};
 case 0345 : ; case345:  { register int arg1, arg2, result; arg1 = *(((LispPTR *) cspcache) - 1);  { if ((((tscache) >> 17) ^ 7)) if ((( (* (MDStypetbl+((tscache)>>9))) ) & 0x7ff) != 2)  goto op_ufn; else   arg2 = *((int *)(Lisp_world + (tscache))); else   arg2 = ( ((int)tscache << 15) >> 15 );};; { if ((((arg1) >> 17) ^ 7)) if ((( (* (MDStypetbl+((arg1)>>9))) ) & 0x7ff) != 2)  goto op_ufn; else   arg1 = *((int *)(Lisp_world + (arg1))); else   arg1 = ( ((int)arg1 << 15) >> 15 );};; result = arg1 & arg2; if ( 0) goto op_ufn; { if ((((result << 15) >>15) ^ result)) {register LispPTR *wordp; wordp = (LispPTR *) createcell68k(2); *((int *)wordp) = result;  tscache = ((((unsigned int)(wordp) - (unsigned int)Lisp_world) >>1)); } else  tscache = (( (unsigned)result <<15) >>15) | 0xE0000;}; *(--(cspcache)); { { pccache += 1; { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; }; }; };};
 case 0346 : ; case346:  { register int arg1, arg2, result; arg1 = *(((LispPTR *) cspcache) - 1);  { if ((((tscache) >> 17) ^ 7)) if ((( (* (MDStypetbl+((tscache)>>9))) ) & 0x7ff) != 2)  goto op_ufn; else   arg2 = *((int *)(Lisp_world + (tscache))); else   arg2 = ( ((int)tscache << 15) >> 15 );};; { if ((((arg1) >> 17) ^ 7)) if ((( (* (MDStypetbl+((arg1)>>9))) ) & 0x7ff) != 2)  goto op_ufn; else   arg1 = *((int *)(Lisp_world + (arg1))); else   arg1 = ( ((int)arg1 << 15) >> 15 );};; result = arg1 ^ arg2; if ( 0) goto op_ufn; { if ((((result << 15) >>15) ^ result)) {register LispPTR *wordp; wordp = (LispPTR *) createcell68k(2); *((int *)wordp) = result;  tscache = ((((unsigned int)(wordp) - (unsigned int)Lisp_world) >>1)); } else  tscache = (( (unsigned)result <<15) >>15) | 0xE0000;}; *(--(cspcache)); { { pccache += 1; { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; }; }; };};
 case 0347 : ; case347:  {if ((int)(tscache = (LispPTR)N_OP_lsh(*(--(cspcache)), tscache)) < 0) goto ufn_2; { { pccache += 1; { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; }; }; };;};
 case 0350 : ; case350:  {if ((int)(tscache = (LispPTR)N_OP_fplus2(*(--(cspcache)), tscache)) < 0) goto ufn_2; { { pccache += 1; { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; }; }; };;};
 case 0351 : ; case351:  {if ((int)(tscache = (LispPTR)N_OP_fdifference(*(--(cspcache)), tscache)) < 0) goto ufn_2; { { pccache += 1; { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; }; }; };;};
 case 0352 : ; case352:  {if ((int)(tscache = (LispPTR)N_OP_ftimes2(*(--(cspcache)), tscache)) < 0) goto ufn_2; { { pccache += 1; { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; }; }; };;};
 case 0353 : ; case353:  {if ((int)(tscache = (LispPTR)N_OP_fquotient(*(--(cspcache)), tscache)) < 0) goto ufn_2; { { pccache += 1; { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; }; }; };;};
 case 0354 : ; case354:  {tscache = N_OP_ubfloat2(*(--(cspcache)), tscache,  (((BYTECODE *)((pccache-1)+1))->code)); if (stateptrcache->errorexit) goto ufn_2d; { { pccache += 2; { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; }; }; };;};
 case 0355 : ; case355:  {tscache = N_OP_ubfloat1(tscache,  (((BYTECODE *)((pccache-1)+1))->code)); if (stateptrcache->errorexit) goto fix_tos_ufn; { { pccache += 2; { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; }; }; };;};
 case 0356 : ; case356:  {if ((int)(tscache = (LispPTR)N_OP_aref2( *(((LispPTR *) cspcache)-2), *(((LispPTR *) cspcache)-1), tscache)) < 0) goto fix_tos_ufn; (cspcache) -= 2; { { pccache += 1; { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; }; }; };;};
 case 0357 : ; case357:  {if ((int)(tscache = (LispPTR)N_OP_aset2( *(((LispPTR *) cspcache)-3), *(((LispPTR *) cspcache)-2), *(((LispPTR *) cspcache)-1), tscache)) < 0) goto fix_tos_ufn; (cspcache) -= 3; { { pccache += 1; { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; }; }; };;};

 case 0360 : ; case360: {
		if(tscache == *(--(cspcache)))
			tscache = 0114;
		else	tscache = 0;
		{ { pccache += 1; { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; }; }; };
		}

 case 0361 : ; case361:  { register int arg1, arg2, result; arg1 = *(((LispPTR *) cspcache) - 1);  { if ((((tscache) >> 17) ^ 7)) if ((( (* (MDStypetbl+((tscache)>>9))) ) & 0x7ff) != 2)  goto op_ufn; else   arg2 = *((int *)(Lisp_world + (tscache))); else   arg2 = ( ((int)tscache << 15) >> 15 );};; { if ((((arg1) >> 17) ^ 7)) if ((( (* (MDStypetbl+((arg1)>>9))) ) & 0x7ff) != 2)  goto op_ufn; else   arg1 = *((int *)(Lisp_world + (arg1))); else   arg1 = ( ((int)arg1 << 15) >> 15 );};; tscache = (arg1>arg2? 0114 : 0); *(--(cspcache)); { { pccache += 1; { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; }; }; };}; 	
 case 0362 : ; case362:  {if ((int)(tscache = (LispPTR)N_OP_fgreaterp(*(--(cspcache)), tscache)) < 0) goto ufn_2; { { pccache += 1; { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; }; }; };;};
 case 0363 : ; case363:	{ register int arg1, arg2, result; arg1 = *(((LispPTR *) cspcache) - 1);  { if ((((tscache) >> 17) ^ 7)) if ((( (* (MDStypetbl+((tscache)>>9))) ) & 0x7ff) != 2)  goto op_ufn; else   arg2 = *((int *)(Lisp_world + (tscache))); else   arg2 = ( ((int)tscache << 15) >> 15 );};; { if ((((arg1) >> 17) ^ 7)) if ((( (* (MDStypetbl+((arg1)>>9))) ) & 0x7ff) != 2)  goto op_ufn; else   arg1 = *((int *)(Lisp_world + (arg1))); else   arg1 = ( ((int)arg1 << 15) >> 15 );};; tscache = (arg1>arg2? 0114 : 0); *(--(cspcache)); { { pccache += 1; { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; }; }; };};
 case 0364 : ; case364:  {if ((int)(tscache = (LispPTR)N_OP_equal(*(--(cspcache)), tscache)) < 0) goto ufn_2; { { pccache += 1; { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; }; }; };;};
 case 0365 : ; case365:	{if ((int)(tscache = (LispPTR)N_OP_makenumber(*(--(cspcache)), tscache)) < 0) goto ufn_2; { { pccache += 1; { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; }; }; };;};
 case 0366 : ; case366:	{if ((int)(tscache = (LispPTR)N_OP_boxiplus(*(--(cspcache)), tscache)) < 0) goto ufn_2; { { pccache += 1; { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; }; }; };;};
 case 0367 : ; case367:	{if ((int)(tscache = (LispPTR)N_OP_boxidiff(*(--(cspcache)), tscache)) < 0) goto ufn_2; { { pccache += 1; { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; }; }; };;};
 case 0370 : ; case370:  { goto op_ufn; } 
 case 0371 : ; case371:  { goto op_ufn; } 
 case 0372 : ; case372: 	{if ((int)(tscache = (LispPTR)N_OP_misc3( *(((LispPTR *) cspcache)-2), *(((LispPTR *) cspcache)-1), tscache,  (((BYTECODE *)((pccache-1)+1))->code))) < 0) goto fix_tos_ufn; (cspcache) -= 2; { { pccache += 2; { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; }; }; };;};
 case 0373 : ; case373: 	{if ((int)(tscache = (LispPTR)N_OP_misc4( *(((LispPTR *) cspcache)-3), *(((LispPTR *) cspcache)-2), *(((LispPTR *) cspcache)-1), tscache,  (((BYTECODE *)((pccache-1)+1))->code))) < 0) goto fix_tos_ufn; (cspcache) -= 3; { { pccache += 2; { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; }; }; };;};
 case 0374 : ; case374:  { goto op_ufn; } 
 case 0375 : ; case375: 	{ register LispPTR temp; temp = *(((LispPTR *) cspcache) - 1); *(((LispPTR *) cspcache) - 1) = tscache; tscache = temp; { { pccache += 1; { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; }; }; }; };
 case 0376 : ; case376: 	{ { { pccache += 1; { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; }; }; }; };
 case 0377 : ; case377: 	{ register int arg2; ; arg2 = *(--(cspcache)); if ((tscache & 0xfff0000) == 0xE0000) { if (arg2 == tscache) {tscache = 0114; { { pccache += 1; { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; }; }; };} if ((arg2 & 0xfff0000) == 0xE0000) {tscache = 0; { { pccache += 1; { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; }; }; };} } if ((int)(tscache = (LispPTR)N_OP_eqq( arg2, tscache)) < 0) goto ufn_2; { { pccache += 1; { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; }; }; };; };
# 676 "../src/xc.c" 




# 699 "../src/xc.c" 

 	
 default: 	error("should not default");

	 }	

# 766 "../src/xc.c" 


native_check: 

# 772 "../src/xc.c" 

		goto nextopcode;





check_interrupt:
# 782 "../src/xc.c" 


	if ( (int)((LispPTR *) cspcache) > (int)stateptrcache->endofstack )
		{{ stateptrcache->currentpc=pccache-1; stateptrcache->tosvalue=tscache; {stateptrcache->csp = (DLword *) (((LispPTR *) cspcache)-1);}; };
		 error("Unrecoverable Stack Overflow");
	         { pccache=stateptrcache->currentpc+1; {(cspcache) = ((LispPTR *) stateptrcache->csp)+1;}; tscache = stateptrcache->tosvalue; };
		}

	

{register int need_irq;
 static int period_cnt=60;
extern int KBDEventFlg;
extern int ETHEREventCount;
extern LispPTR DOBUFFEREDTRANSITION_index;
extern LispPTR INTERRUPTFRAME_index;
extern LispPTR *KEYBUFFERING68k;
extern LispPTR *PENDINGINTERRUPT68k;
extern LispPTR ATOM_STARTED;
extern LispPTR *PERIODIC_INTERRUPT68k;
extern LispPTR *PERIODIC_INTERRUPT_FREQUENCY68k;
extern LispPTR PERIODIC_INTERRUPTFRAME_index;
extern LispPTR *Reclaim_cnt_word;
extern LispPTR DORECLAIM_index;
extern int URaid_req;

	

re_check_stack:
	need_irq = 0;
	if ( 	((int)(((LispPTR *) cspcache)+1) > stateptrcache->irqcheck) && 
		(stateptrcache->irqend > 0) && 
		(stateptrcache->irqcheck > 0) )
		{
	 	 *((cspcache)++) = tscache;
		 { stateptrcache->currentpc=pccache-1; stateptrcache->tosvalue=tscache; {stateptrcache->csp = (DLword *) (((LispPTR *) cspcache)-1);}; };
		 extended_frame = 0;
		 if (do_stackoverflow(0)) { 
stackoverflow_help:
			period_cnt=60; need_irq = 1;
			error("Stack Overflow, MUST HARDRESET!"); 
			{ pccache=stateptrcache->currentpc+1; {(cspcache) = ((LispPTR *) stateptrcache->csp)+1;}; tscache = stateptrcache->tosvalue; }; tscache = 0; 
			}
		 else { { pccache=stateptrcache->currentpc+1; {(cspcache) = ((LispPTR *) stateptrcache->csp)+1;}; tscache = stateptrcache->tosvalue; }; tscache = *(--(cspcache)); }
		 stateptrcache->irqcheck = (int)stateptrcache->endofstack-((stateptrcache->currentfunc->stkmin ) << 1);
		 need_irq = (stateptrcache->irqend == 0)  || extended_frame;
		 *PENDINGINTERRUPT68k |= extended_frame; 
		 stateptrcache->irqend = (int) stateptrcache->endofstack;
		}

	

	if ((stateptrcache->irqend <= 0) || (stateptrcache->irqcheck <= 0) || need_irq) {
		if ((((unsigned int)(((LispPTR *) cspcache)) - (unsigned int)Stackspace) >>1) > InterfacePage->stackbase) {

			
# 840 "../src/xc.c" 

			{ stateptrcache->currentpc=pccache-1; stateptrcache->tosvalue=tscache; {stateptrcache->csp = (DLword *) (((LispPTR *) cspcache)-1);}; }; 
			update_timer(); 

			if(URaid_req ==1){
				URaid_req=0;
				error("Call URaid by User Interrupt");
			}
			else if((KBDEventFlg>0)&&(*KEYBUFFERING68k==0114)) {
				*KEYBUFFERING68k= ATOM_STARTED;
				cause_interruptcall(DOBUFFEREDTRANSITION_index);
				KBDEventFlg --;
				}
			else if(*Reclaim_cnt_word == 0xE0000) {  
				*Reclaim_cnt_word=0;
				cause_interruptcall(DORECLAIM_index);
				}
			else if (*PENDINGINTERRUPT68k!=0)
			  { INTSTAT2 * intstate = ((INTSTAT2 *)(Lisp_world + (*INTERRUPTSTATE_word)));
			    unsigned char newints = (intstate->pendingmask) & ~(intstate->handledmask);
			 
			      {
				intstate->handledmask |= intstate->pendingmask;
				*PENDINGINTERRUPT68k=0;
				cause_interruptcall(INTERRUPTFRAME_index);
			      }
			  }
			else if (ETHEREventCount>0)
			  { INTSTAT * intstate = ((INTSTAT *)(Lisp_world + (*INTERRUPTSTATE_word)));
			    if (!(intstate->ETHERInterrupt) &&
				!(((INTSTAT2 *)intstate)->handledmask & 0x40))
			      {
				intstate->ETHERInterrupt=1;
				((INTSTAT2 *)intstate)->handledmask |=
				    ((INTSTAT2 *)intstate)->pendingmask;
				cause_interruptcall(INTERRUPTFRAME_index);
				ETHEREventCount--;
			      }
			    else *PENDINGINTERRUPT68k = 0114;
			  }
			else if(*PERIODIC_INTERRUPT68k!=0) {
				if(period_cnt>0)  period_cnt--;
				else {
					cause_interruptcall(PERIODIC_INTERRUPTFRAME_index);
					if(*PERIODIC_INTERRUPT_FREQUENCY68k==0)
						period_cnt=0;
					else
						period_cnt=(*PERIODIC_INTERRUPT_FREQUENCY68k & 0xffff) *(1000000/60) /TIMER_INTERVAL;
	





					}
				}
			{ pccache=stateptrcache->currentpc+1; {(cspcache) = ((LispPTR *) stateptrcache->csp)+1;}; tscache = stateptrcache->tosvalue; };
			{stateptrcache->irqcheck = ( (int)(stateptrcache->irqend = (int) stateptrcache->endofstack) - (( stateptrcache->currentfunc->stkmin ) << 1) ); };
			} 
		else {
			

			{stateptrcache->irqcheck = ( (int)(stateptrcache->irqend = (int) stateptrcache->endofstack) - (( stateptrcache->currentfunc->stkmin ) << 1) ); };
			goto re_check_stack;
			}
		}

}

	{ fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; };





PopNextop1:
	tscache = *(--(cspcache)); 
	{ { pccache += 1; { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; }; }; };

PopNextop2:
	tscache = *(--(cspcache)); 
	{ { pccache += 2; { fast_dispatcher(table, (((BYTECODE *)((pccache-1)))->code)); goto nextopcode; }; }; };









# 1462 "../src/xc.c" 


 
    }


int retfun() {return(0);}
do_brk() {}

