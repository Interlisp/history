	.file	"byteswapfns.c"
	.version	"sun386-1.0"
	.optim
        .text
	.stabn	0104,0,1,.LL0
.LL0:
	.stabs	"../src/byteswapfns.c",0144,0,0,.LL1
.LL1:
/     1	/* @(#) byteswapfns.c Version 1.5 (3/23/89). copyright envos & Fuji Xerox  */
        .data
        .text
	.stabn	0104,0,2,.LL2
.LL2:
	.stabs	"int:t(0,1)=r(0,1);-2147483648;2147483647;",0x80,0,0,0
	.stabs	"char:t(0,2)=r(0,2);0;127;",0x80,0,0,0
	.stabs	"long:t(0,3)=r(0,1);-2147483648;2147483647;",0x80,0,0,0
	.stabs	"short:t(0,4)=r(0,1);-32768;32767;",0x80,0,0,0
	.stabs	"unsigned char:t(0,5)=r(0,1);0;255;",0x80,0,0,0
	.stabs	"unsigned short:t(0,6)=r(0,1);0;65535;",0x80,0,0,0
	.stabs	"unsigned long:t(0,7)=r(0,1);0;-1;",0x80,0,0,0
	.stabs	"unsigned int:t(0,8)=r(0,1);0;-1;",0x80,0,0,0
	.stabs	"float:t(0,9)=r(0,1);4;0;",0x80,0,0,0
	.stabs	"double:t(0,10)=r(0,1);8;0;",0x80,0,0,0
	.stabs	"void:t(0,11)=(0,11)",0x80,0,0,0
	.stabs	"???:t(0,12)=(0,1)",0x80,0,0,0
        .data
        .text
	.stabs	"id:S(0,13)=*(0,2)",0x26,0,1,id
        .data
	.align	4
id:
        .data
	.long	.L12
        .text
.LL3:
	.stabn	0104,0,1,.LL4
.LL4:
	.stabs	"/usr/include/stdio.h",0202,0,0,0
        .data
        .text
	.stabn	0104,0,13,.LL5
.LL5:
	.stabs	"_iobuf:T(1,1)=s20_cnt:(0,1),0,32;_ptr:(1,2)=*(0,5),32,32;_base:(1,2),64,32;_bufsiz:(0,1),96,32;_flag:(0,4),128,16;_file:(0,2),144,8;;",0x80,0,20,-1275
        .data
        .text
.LL6:
	.stabn	0104,0,14,.LL7
.LL7:
	.stabn	0242,0,0,0
        .data
        .text
.LL8:
	.stabn	0104,0,1,.LL9
.LL9:
	.stabs	"/usr/include/sys/file.h",0202,0,0,0
        .data
        .text
.LL10:
	.stabs	"/usr/include/sys/fcntlcom.h",0202,0,0,0
        .data
        .text
	.stabn	0104,0,69,.LL11
.LL11:
	.stabs	"flock:T(3,1)=s16l_type:(0,4),0,16;l_whence:(0,4),16,16;l_start:(0,1),32,32;l_len:(0,1),64,32;l_pid:(0,4),96,16;l_xxx:(0,4),112,16;;",0x80,0,16,-1275
        .data
        .text
.LL12:
	.stabn	0104,0,40,.LL13
.LL13:
	.stabn	0242,0,0,0
        .data
        .text
.LL14:
	.stabn	0104,0,15,.LL15
.LL15:
	.stabn	0242,0,0,0
        .data
        .text
.LL16:
	.stabn	0104,0,1,.LL17
.LL17:
	.stabs	"/usr/include/sys/types.h",0202,0,0,0
        .data
        .text
.LL18:
	.stabs	"/usr/include/sys/sysmacros.h",0202,0,0,0
        .data
        .text
.LL19:
	.stabn	0104,0,17,.LL20
.LL20:
	.stabn	0242,0,0,0
        .data
        .text
	.stabn	0104,0,18,.LL21
.LL21:
	.stabs	"u_char:t(0,5)",0x80,0,1,-1275
        .data
        .text
	.stabn	0104,0,19,.LL22
.LL22:
	.stabs	"u_short:t(0,6)",0x80,0,2,-1275
        .data
        .text
	.stabn	0104,0,20,.LL23
.LL23:
	.stabs	"u_int:t(0,8)",0x80,0,4,-1275
        .data
        .text
	.stabn	0104,0,21,.LL24
.LL24:
	.stabs	"u_long:t(0,8)",0x80,0,4,-1275
        .data
        .text
	.stabn	0104,0,22,.LL25
.LL25:
	.stabs	"ushort:t(0,6)",0x80,0,2,-1275
        .data
        .text
	.stabn	0104,0,23,.LL26
.LL26:
	.stabs	"uint:t(0,8)",0x80,0,4,-1275
        .data
        .text
	.stabn	0104,0,44,.LL27
.LL27:
	.stabs	"_physadr:T(4,1)=s2r:(4,2)=ar(0,1);0;0;(0,4),0,16;;",0x80,0,2,-1275
        .data
        .text
	.stabs	"physadr:t(4,3)=*(4,1)",0x80,0,2,-1275
        .data
        .text
	.stabn	0104,0,47,.LL28
.LL28:
	.stabs	"label_t:T(4,4)=s32val:(4,5)=ar(0,1);0;7;(0,1),0,256;;",0x80,0,32,-1275
        .data
        .text
	.stabs	"label_t:t(4,4)",0x80,0,32,-1275
        .data
        .text
	.stabn	0104,0,49,.LL29
.LL29:
	.stabs	"_quad:T(4,6)=s8val:(4,7)=ar(0,1);0;1;(0,1),0,64;;",0x80,0,8,-1275
        .data
        .text
	.stabs	"quad:t(4,6)",0x80,0,8,-1275
        .data
        .text
	.stabn	0104,0,50,.LL30
.LL30:
	.stabs	"daddr_t:t(0,1)",0x80,0,4,-1275
        .data
        .text
	.stabn	0104,0,51,.LL31
.LL31:
	.stabs	"caddr_t:t(0,13)",0x80,0,1,-1275
        .data
        .text
	.stabn	0104,0,52,.LL32
.LL32:
	.stabs	"ino_t:t(0,8)",0x80,0,4,-1275
        .data
        .text
	.stabn	0104,0,53,.LL33
.LL33:
	.stabs	"swblk_t:t(0,1)",0x80,0,4,-1275
        .data
        .text
	.stabn	0104,0,54,.LL34
.LL34:
	.stabs	"size_t:t(0,1)",0x80,0,4,-1275
        .data
        .text
	.stabn	0104,0,55,.LL35
.LL35:
	.stabs	"time_t:t(0,1)",0x80,0,4,-1275
        .data
        .text
	.stabn	0104,0,56,.LL36
.LL36:
	.stabs	"dev_t:t(0,4)",0x80,0,2,-1275
        .data
        .text
	.stabn	0104,0,57,.LL37
.LL37:
	.stabs	"off_t:t(0,1)",0x80,0,4,-1275
        .data
        .text
	.stabn	0104,0,58,.LL38
.LL38:
	.stabs	"uid_t:t(0,6)",0x80,0,2,-1275
        .data
        .text
	.stabn	0104,0,59,.LL39
.LL39:
	.stabs	"gid_t:t(0,6)",0x80,0,2,-1275
        .data
        .text
	.stabn	0104,0,60,.LL40
.LL40:
	.stabs	"key_t:t(0,1)",0x80,0,4,-1275
        .data
        .text
	.stabn	0104,0,73,.LL41
.LL41:
	.stabs	"fd_mask:t(0,1)",0x80,0,4,-1275
        .data
        .text
	.stabn	0104,0,85,.LL42
.LL42:
	.stabs	"fd_set:T(4,8)=s32fds_bits:(4,5),0,256;;",0x80,0,32,-1275
        .data
        .text
	.stabs	"fd_set:t(4,8)",0x80,0,32,-1275
        .data
        .text
	.stabn	0104,0,87,.LL43
.LL43:
	.stabs	"addr_t:t(0,13)",0x80,0,1,-1275
        .data
        .text
.LL44:
	.stabn	0104,0,16,.LL45
.LL45:
	.stabn	0242,0,0,0
        .data
        .text
.LL46:
	.stabn	0104,0,1,.LL47
.LL47:
	.stabs	"/usr/include/sys/stat.h",0202,0,0,0
        .data
        .text
	.stabn	0104,0,25,.LL48
.LL48:
	.stabs	"stat:T(6,1)=s64st_dev:(0,4),0,16;st_ino:(0,8),32,32;st_mode:(0,6),64,16;st_nlink:(0,4),80,16;st_uid:(0,4),96,16;st_gid:(0,4),112,16;st_rdev:(0,4),128,16;st_size:(0,1),160,32;\\",0x80,0,64,-1275
	.stabs	"st_atime:(0,1),192,32;st_spare1:(0,1),224,32;st_mtime:(0,1),256,32;st_spare2:(0,1),288,32;st_ctime:(0,1),320,32;st_spare3:(0,1),352,32;st_blksize:(0,1),384,32;st_blocks:(0,1),416,32;st_spare4:(4,7),448,64;;",0x80,0,64,-1275
        .data
        .text
.LL49:
	.stabn	0104,0,17,.LL50
.LL50:
	.stabn	0242,0,0,0
        .data
        .text
.LL51:
	.stabn	0104,0,1,.LL52
.LL52:
	.stabs	"/usr/include/errno.h",0202,0,0,0
        .data
        .text
.LL53:
	.stabs	"/usr/include/sys/errno.h",0202,0,0,0
        .data
        .text
.LL54:
	.stabn	0104,0,8,.LL55
.LL55:
	.stabn	0242,0,0,0
        .data
        .text
	.stabs	"errno:G(0,1)",0x20,0,4,0
        .data
        .text
.LL56:
	.stabn	0104,0,18,.LL57
.LL57:
	.stabn	0242,0,0,0
        .data
        .text
.LL58:
	.stabn	0104,0,1,.LL59
.LL59:
	.stabs	"../inc//machineconfig.h",0202,0,0,0
        .data
        .text
.LL60:
	.stabn	0104,0,20,.LL61
.LL61:
	.stabn	0242,0,0,0
        .data
        .text
.LL62:
	.stabn	0104,0,1,.LL63
.LL63:
	.stabs	"../inc//lispemul.h",0202,0,0,0
        .data
        .text
	.stabn	0104,0,141,.LL64
.LL64:
	.stabs	"BYTECODE:t(10,1)=s4code:(0,8),0,8;;",0x80,0,4,-1275
        .data
        .text
	.stabn	0104,0,142,.LL65
.LL65:
	.stabs	"ByteCode:t(0,2)",0x80,0,1,-1275
        .data
        .text
	.stabn	0104,0,143,.LL66
.LL66:
	.stabs	"DLword:t(0,6)",0x80,0,2,-1275
        .data
        .text
	.stabn	0104,0,144,.LL67
.LL67:
	.stabs	"DLbyte:t(0,2)",0x80,0,1,-1275
        .data
        .text
	.stabn	0104,0,145,.LL68
.LL68:
	.stabs	"LispPTR:t(0,8)",0x80,0,4,-1275
        .data
        .text
	.stabn	0104,0,147,.LL69
.LL69:
	.stabs	"mds_page:t(0,6)",0x80,0,2,-1275
        .data
        .text
	.stabn	0104,0,148,.LL70
.LL70:
	.stabs	"CFuncPTR:t(10,2)=*(10,3)=f(0,1)",0x80,0,4,-1275
        .data
        .text
	.stabn	0104,0,154,.LL71
.LL71:
	.stabs	"consstr:T(10,4)=s4car_field:(0,8),0,24;cdr_code:(0,8),24,8;;",0x80,0,4,-1275
        .data
        .text
	.stabs	"ConsCell:t(10,4)",0x80,0,4,-1275
        .data
        .text
	.stabn	0104,0,161,.LL72
.LL72:
	.stabs	"ufn_entry:T(10,5)=s4arg_num:(0,8),0,8;byte_num:(0,8),8,8;atom_name:(0,6),16,16;;",0x80,0,4,-1275
        .data
        .text
	.stabs	"UFN:t(10,5)",0x80,0,4,-1275
        .data
        .text
	.stabn	0104,0,169,.LL73
.LL73:
	.stabs	"closure_type:T(10,6)=s8def_ptr:(0,8),0,24;nil1:(0,8),24,8;env_ptr:(0,8),32,24;nil2:(0,8),56,8;;",0x80,0,8,-1275
        .data
        .text
	.stabs	"Closure:t(10,6)",0x80,0,8,-1275
        .data
        .text
	.stabn	0104,0,183,.LL74
.LL74:
	.stabs	"interrupt_state:T(10,7)=s4intcharcode:(0,6),0,16;nil2:(0,8),16,8;waitinginterrupt:(0,8),24,1;storagefull:(0,8),25,1;stackoverflow:(0,8),26,1;vmemfull:(0,8),27,1;gcdisabled:(0,8),28,1;IOInterrupt:(0,8),29,1;\\",0x80,0,4,-1275
	.stabs	"ETHERInterrupt:(0,8),30,1;LogFileIO:(0,8),31,1;;",0x80,0,4,-1275
        .data
        .text
	.stabs	"INTSTAT:t(10,7)",0x80,0,4,-1275
        .data
        .text
	.stabn	0104,0,198,.LL75
.LL75:
	.stabs	"state:T(10,8)=s44ivar:(10,10)=*(0,6),0,32;pvar:(10,10),32,32;csp:(10,10),64,32;tosvalue:(0,8),96,32;currentpc:(0,13),128,32;currentfunc:(10,11)=*(10,9)=xsfnhead:,160,32;endofstack:(10,10),192,32;irqcheck:(0,1),224,32;\\",0x80,0,44,-1275
	.stabs	"irqend:(0,1),256,32;scratch_cstk:(0,8),288,32;errorexit:(0,1),320,32;;",0x80,0,44,-1275
        .data
        .text
	.stabn	0104,0,222,.LL76
.LL76:
	.stabs	"wbits:T(10,12)=s4LSB:(0,8),0,1;B14:(0,8),1,1;B13:(0,8),2,1;B12:(0,8),3,1;B11:(0,8),4,1;B10:(0,8),5,1;B9:(0,8),6,1;B8:(0,8),7,1;\\",0x80,0,4,-1275
	.stabs	"B7:(0,8),8,1;B6:(0,8),9,1;B5:(0,8),10,1;B4:(0,8),11,1;B3:(0,8),12,1;B2:(0,8),13,1;B1:(0,8),14,1;MSB:(0,8),15,1;;",0x80,0,4,-1275
        .data
        .text
	.stabs	"WBITS:t(10,12)",0x80,0,4,-1275
        .data
        .text
	.stabn	0104,0,229,.LL77
.LL77:
	.stabs	"lbits:T(10,13)=s4LSB:(0,8),0,1;MIDDLE:(0,8),1,30;MSB:(0,8),31,1;;",0x80,0,4,-1275
        .data
        .text
	.stabs	"LBITS:t(10,13)",0x80,0,4,-1275
        .data
        .text
	.stabn	0104,0,240,.LL78
.LL78:
	.stabs	"MachineState:G(10,8)",0x20,0,44,0
        .data
        .text
.LL79:
	.stabn	0104,0,1,.LL80
.LL80:
	.stabs	"../inc//ifpage.h",0202,0,0,0
        .data
        .text
	.stabn	0104,0,160,.LL81
.LL81:
	.stabs	"ifpage:T(11,1)=s136resetfxp:(0,6),0,16;currentfxp:(0,6),16,16;kbdfxp:(0,6),32,16;subovfxp:(0,6),48,16;gcfxp:(0,6),64,16;hardreturnfxp:(0,6),80,16;endofstack:(0,6),96,16;faultfxp:(0,6),112,16;\\",0x80,0,136,-1275
	.stabs	"minrversion:(0,6),128,16;lversion:(0,6),144,16;rversion:(0,6),160,16;minbversion:(0,6),176,16;machinetype:(0,6),192,16;bversion:(0,6),208,16;key:(0,6),224,16;miscfxp:(0,6),240,16;\\",0x80,0,136,-1275
	.stabs	"emulatorspace:(0,6),256,16;serialnumber:(0,6),272,16;nxtpmaddr:(0,6),288,16;screenwidth:(0,6),304,16;ndirtypages:(0,6),320,16;nactivepages:(0,6),336,16;filepnpmt0:(0,6),352,16;filepnpmp0:(0,6),368,16;\\",0x80,0,136,-1275
	.stabs	"filler1:(0,6),384,16;teleraidfxp:(0,6),400,16;filler3:(0,6),416,16;filler2:(0,6),432,16;userpswdaddr:(0,6),448,16;usernameaddr:(0,6),464,16;faulthi:(0,6),480,16;stackbase:(0,6),496,16;\\",0x80,0,136,-1275
	.stabs	"devconfig:(0,6),512,16;faultlo:(0,6),528,16;rpoffset:(0,6),544,16;rptsize:(0,6),560,16;embufvp:(0,6),576,16;wasrptlast:(0,6),592,16;nshost1:(0,6),608,16;nshost0:(0,6),624,16;\\",0x80,0,136,-1275
	.stabs	"mdszone:(0,6),640,16;nshost2:(0,6),656,16;emubuffers:(0,6),672,16;mdszonelength:(0,6),688,16;lastnumchars:(0,6),704,16;emubuflength:(0,6),720,16;isfmap:(0,6),736,16;sysdisk:(0,6),752,16;\\",0x80,0,136,-1275
	.stabs	"miscstackfn:(0,8),768,32;miscstackarg1:(0,8),800,32;miscstackarg2:(0,8),832,32;miscstackresult:(0,8),864,32;lastlockedfilepage:(0,6),896,16;nrealpages:(0,6),912,16;fptovpstart:(0,6),928,16;lastdominofilepage:(0,6),944,16;\\",0x80,0,136,-1275
	.stabs	"dl24bitaddressable:(0,6),960,16;fakemousebits:(0,6),976,16;realpagetableptr:(0,8),992,32;fullspaceused:(0,6),1024,16;dllastvmempage:(0,6),1040,16;fakekbdad5:(0,6),1056,16;fakekbdad4:(0,6),1072,16;;",0x80,0,136,-1275
        .data
        .text
	.stabs	"IFPAGE:t(11,1)",0x80,0,136,-1275
        .data
        .text
.LL82:
	.stabn	0104,0,258,.LL83
.LL83:
	.stabn	0242,0,0,0
        .data
        .text
.LL84:
	.stabn	0104,0,1,.LL85
.LL85:
	.stabs	"../inc//iopage.h",0202,0,0,0
        .data
        .text
	.stabn	0104,0,150,.LL86
.LL86:
	.stabs	"iopage:T(12,1)=s512dummy0:(12,2)=ar(0,1);0;17;(0,6),0,288;dlfloppycmd:(0,6),288,16;dlmaintpanel:(0,6),304,16;dlprocessorcmd:(0,6),320,16;dlttyportcmd:(0,6),336,16;dlbeepcmd:(0,6),352,16;newmousestate:(0,6),368,16;dlrs232cputflag:(0,6),384,16;\\",0x80,0,512,-1275
	.stabs	"dlrs232cmisccommand:(0,6),400,16;dummy1b:(0,6),416,16;dlrs232cgetflag:(0,6),432,16;dummy1:(12,3)=ar(0,1);0;3;(0,6),448,64;dlfloppy:(0,6),512,16;dummy1a:(0,6),528,16;dummy2:(0,6),544,16;dlttyout:(0,6),560,16;\\",0x80,0,512,-1275
	.stabs	"dummy3:(0,6),576,16;dlttyin:(0,6),592,16;dlprocessor1:(0,6),608,16;dlprocessor2:(0,6),624,16;newmousex:(0,6),640,16;dlprocessor0:(0,6),656,16;dlbeepfreq:(0,6),672,16;newmousey:(0,6),688,16;\\",0x80,0,512,-1275
	.stabs	"dlrs232cparametercsbhi:(0,6),704,16;dlrs232cparametercsblo:(0,6),720,16;dlrs232csetrs366status:(12,4)=ar(0,1);0;1;(0,6),736,32;dlrs232cputcsblo:(0,6),768,16;dlrs232csetrs366statusa:(0,6),784,16;dlrs232cgetcsblo:(0,6),800,16;dlrs232cputcsbhi:(0,6),816,16;dlrs232cdevicestatus:(0,6),832,16;\\",0x80,0,512,-1275
	.stabs	"dlrs232cgetcsbhi:(0,6),848,16;dltodvalid:(0,6),864,16;dlrs232cparameteroutcome:(0,6),880,16;dltodhi:(0,6),896,16;dltodlo:(0,6),912,16;dlmousex:(0,6),928,16;dltodlo2:(0,6),944,16;dlutilin:(0,6),960,16;\\",0x80,0,512,-1275
	.stabs	"dlmousey:(0,6),976,16;dlkbdad1:(0,6),992,16;dlkbdad0:(0,6),1008,16;dlkbdad3:(0,6),1024,16;dlkbdad2:(0,6),1040,16;dlkbdad5:(0,6),1056,16;dlkbdad4:(0,6),1072,16;dllsepimagecsb:(12,5)=ar(0,1);0;31;(0,6),1088,512;\\",0x80,0,512,-1275
	.stabs	"dummy4a:(0,6),1600,16;dliophardwareconfig:(0,6),1616,16;dummy4:(12,6)=ar(0,1);0;9;(0,6),1632,160;dlrs232cparametercsbhi_11:(0,6),1792,16;dlrs232cparametercsblo_11:(0,6),1808,16;dlrs232csetrs366status_11:(12,7)=ar(0,1);0;13;(0,6),1824,224;dummy5:(12,8)=ar(0,1);0;59;(0,6),2048,960;dlmagtape:(12,3),3008,64;\\",0x80,0,512,-1275
	.stabs	"dlethernet:(12,9)=ar(0,1);0;11;(0,6),3072,192;dummy6:(12,10)=ar(0,1);0;29;(0,6),3264,480;dldispinterrupt:(0,6),3744,16;dummy6a:(0,6),3760,16;dldispborder:(0,6),3776,16;dldispcontrol:(0,6),3792,16;dlcursory:(0,6),3808,16;dlcursorx:(0,6),3824,16;dlcursorbitmap:(12,11)=ar(0,1);0;15;(0,6),3840,256;;",0x80,0,512,-1275
        .data
        .text
	.stabs	"IOPAGE:t(12,1)",0x80,0,512,-1275
        .data
        .text
.LL87:
	.stabn	0104,0,261,.LL88
.LL88:
	.stabn	0242,0,0,0
        .data
        .text
.LL89:
	.stabn	0104,0,1,.LL90
.LL90:
	.stabs	"../inc//miscstats.h",0202,0,0,0
        .data
        .text
	.stabn	0104,0,40,.LL91
.LL91:
	.stabs	"misc:T(13,1)=s124starttime:(0,1),0,32;totaltime:(0,1),32,32;swapwaittime:(0,1),64,32;pagefaults:(0,1),96,32;swapwrites:(0,1),128,32;diskiotime:(0,1),160,32;diskops:(0,1),192,32;keyboardwaittime:(0,1),224,32;\\",0x80,0,124,-1275
	.stabs	"gctime:(0,1),256,32;netiotime:(0,1),288,32;netioops:(0,1),320,32;swaptemp0:(0,1),352,32;swaptemp1:(0,1),384,32;rclksecond:(0,8),416,32;secondsclock:(0,8),448,32;millisecondsclock:(0,8),480,32;\\",0x80,0,124,-1275
	.stabs	"baseclock:(0,8),512,32;rclktemp0:(0,8),544,32;secondstmp:(0,8),576,32;millisecondstmp:(0,8),608,32;basetmp:(0,8),640,32;excesstimetmp:(0,1),672,32;clocktemp0:(0,1),704,32;disktemp0:(0,1),736,32;\\",0x80,0,124,-1275
	.stabs	"disktemp1:(0,1),768,32;teleraidtemp1:(0,1),800,32;teleraidtemp2:(0,1),832,32;teleraidtemp3:(0,1),864,32;lastuseraction:(0,1),896,32;dlmousetimer:(0,1),928,32;dlmousetemp:(0,1),960,32;;",0x80,0,124,-1275
        .data
        .text
	.stabs	"MISCSTATS:t(13,1)",0x80,0,124,-1275
        .data
        .text
.LL92:
	.stabn	0104,0,265,.LL93
.LL93:
	.stabn	0242,0,0,0
        .data
        .text
.LL94:
	.stabn	0104,0,21,.LL95
.LL95:
	.stabn	0242,0,0,0
        .data
        .text
.LL96:
	.stabn	0104,0,1,.LL97
.LL97:
	.stabs	"../inc//lispmap.h",0202,0,0,0
        .data
        .text
.LL98:
	.stabn	0104,0,22,.LL99
.LL99:
	.stabn	0242,0,0,0
        .data
        .text
.LL100:
	.stabn	0104,0,1,.LL101
.LL101:
	.stabs	"../inc//lisptypes.h",0202,0,0,0
        .data
        .text
	.stabn	0104,0,262,.LL102
.LL102:
	.stabs	"dtd:T(15,1)=s32dtd_size:(0,6),0,16;dtd_name:(0,6),16,16;dtd_free:(0,8),32,32;dtd_descrs:(0,8),64,24;dtd_gctype:(0,8),88,2;dtd_hunkp:(0,8),90,1;dtd_lockedp:(0,8),91,1;dtd_finalizable:(0,8),92,1;\\",0x80,0,32,-1275
	.stabs	"dtd_obsolate:(0,8),93,1;unuse:(0,8),94,2;dtd_typespecs:(0,8),96,32;dtd_ptrs:(0,8),128,32;dtd_oldcnt:(0,1),160,32;dtd_nextpage:(0,6),192,16;dtd_cnt0:(0,6),208,16;dtd_supertype:(0,6),224,16;dtd_typeentry:(0,6),240,16;;",0x80,0,32,-1275
        .data
        .text
	.stabn	0104,0,274,.LL103
.LL103:
	.stabs	"stringp:T(15,2)=s8base:(0,8),0,24;type:(0,8),24,4;nil:(0,8),28,1;readonly:(0,8),29,1;substringed:(0,8),30,1;origin:(0,8),31,1;offset:(0,6),32,16;length:(0,6),48,16;;",0x80,0,8,-1275
        .data
        .text
	.stabs	"STRINGP:t(15,2)",0x80,0,8,-1275
        .data
        .text
	.stabn	0104,0,292,.LL104
.LL104:
	.stabs	"oned_array:T(15,3)=s12base:(0,8),0,24;nil1:(0,8),24,8;offset:(0,6),32,16;typenumber:(0,8),48,8;extendablep:(0,8),56,1;fillpointerp:(0,8),57,1;displacedp:(0,8),58,1;ajustablep:(0,8),59,1;\\",0x80,0,12,-1275
	.stabs	"stringp:(0,8),60,1;bitp:(0,8),61,1;indirectp:(0,8),62,1;readonlyp:(0,8),63,1;totalsize:(0,6),64,16;fillpointer:(0,6),80,16;;",0x80,0,12,-1275
        .data
        .text
	.stabs	"OneDArray:t(15,3)",0x80,0,12,-1275
        .data
        .text
	.stabn	0104,0,294,.LL105
.LL105:
	.stabs	"NEWSTRINGP:t(15,3)",0x80,0,12,-1275
        .data
        .text
	.stabn	0104,0,312,.LL106
.LL106:
	.stabs	"general_array:T(15,4)=s12base:(0,8),0,24;nil1:(0,8),24,8;Dim0:(0,6),32,16;typenumber:(0,8),48,8;extendablep:(0,8),56,1;fillpointerp:(0,8),57,1;displacedp:(0,8),58,1;ajustablep:(0,8),59,1;\\",0x80,0,12,-1275
	.stabs	"stringp:(0,8),60,1;bitp:(0,8),61,1;indirectp:(0,8),62,1;readonlyp:(0,8),63,1;Dim2:(0,6),64,16;Dim1:(0,6),80,16;;",0x80,0,12,-1275
        .data
        .text
	.stabs	"LispArray:t(15,4)",0x80,0,12,-1275
        .data
        .text
	.stabn	0104,0,320,.LL107
.LL107:
	.stabs	"compiled_closure:T(15,5)=s8def_ptr:(0,8),0,24;nil1:(0,8),24,8;env_ptr:(0,8),32,24;nil2:(0,8),56,8;;",0x80,0,8,-1275
        .data
        .text
	.stabs	"CClosure:t(15,5)",0x80,0,8,-1275
        .data
        .text
	.stabn	0104,0,329,.LL108
.LL108:
	.stabs	"system_dtd_contents:T(15,6)=s8dtd_name:(0,13),0,32;dtd_size:(0,6),32,16;name_len:(0,6),48,16;;",0x80,0,8,-1275
        .data
        .text
	.stabn	0104,0,338,.LL109
.LL109:
	.stabs	"BITMAP:t(15,7)=s12bmbase:(0,8),0,32;bmheight:(0,6),32,16;bmrasterwidth:(0,6),48,16;bmbitperpixel:(0,6),64,16;bmwidth:(0,6),80,16;;",0x80,0,12,-1275
        .data
        .text
	.stabn	0104,0,418,.LL110
.LL110:
	.stabs	"PATHNAME:t(15,8)=s24host:(0,8),0,32;device:(0,8),32,32;directory:(0,8),64,32;name:(0,8),96,32;type:(0,8),128,32;version:(0,8),160,32;;",0x80,0,24,-1275
        .data
        .text
	.stabn	0104,0,433,.LL111
.LL111:
	.stabs	"COMPLEX:t(15,9)=s8real:(0,8),0,32;imaginary:(0,8),32,32;;",0x80,0,8,-1275
        .data
        .text
	.stabn	0104,0,449,.LL112
.LL112:
	.stabs	"RATIO:t(15,10)=s8numerator:(0,8),0,32;denominator:(0,8),32,32;;",0x80,0,8,-1275
        .data
        .text
	.stabn	0104,0,465,.LL113
.LL113:
	.stabs	"BIGNUM:t(15,11)=s4contents:(0,8),0,32;;",0x80,0,4,-1275
        .data
        .text
.LL114:
	.stabn	0104,0,23,.LL115
.LL115:
	.stabn	0242,0,0,0
        .data
        .text
	.stabn	0104,0,32,.LL116
.LL116:
	.stabs	"swapx:F(0,8)",0x24,0,4,swapx
/    33	   {
	.stabs	"word:p(0,8)",0xa0,0,4,8
	.globl	swapx
swapx:
	jmp	.L31
.L30:
/    34	      return( ((word>>16)&0xffff)+((word&0xffff)<<16) ); };
	.stabn	0104,0,34,.LL117
.LL117:
	movl	8(%ebp),%eax
	shrl	$16,%eax
	andl	$65535,%eax
	movl	8(%ebp),%edx
	andl	$65535,%edx
	shll	$16,%edx
	addl	%edx,%eax
	jmp	.L29
.L29:
	leave
	ret
.L31:
	pushl	%ebp
	movl	%esp,%ebp
	jmp	.L30
/FUNCEND
        .data
        .text
	.stabn	0104,0,43,.LL118
.LL118:
	.stabs	"byte_swap_word:F(0,6)",0x24,0,2,byte_swap_word
/    44	   {
	.stabs	"word:p(0,6)",0xa0,0,2,8
	.globl	byte_swap_word
byte_swap_word:
	jmp	.L35
.L34:
/    45	      return( ((word>>8)&0xff)+((word&0xff)<<8) ); };
	.stabn	0104,0,45,.LL119
.LL119:
	movzwl	8(%ebp),%eax
	shrl	$8,%eax
	andl	$255,%eax
	movzwl	8(%ebp),%edx
	andl	$255,%edx
	shll	$8,%edx
	addl	%edx,%eax
	movzwl	%ax,%eax
	jmp	.L33
.L33:
	leave
	ret
.L35:
	pushl	%ebp
	movl	%esp,%ebp
	jmp	.L34
/FUNCEND
        .data
        .text
	.stabn	0104,0,71,.LL120
.LL120:
	.stabs	"byte_swap_page:F(0,1)",0x24,0,4,byte_swap_page
/    72	   {
	.stabs	"page:p(10,10)",0xa0,0,2,8
	.stabs	"wordcount:p(0,1)",0xa0,0,4,12
	.globl	byte_swap_page
byte_swap_page:
	jmp	.L39
.L38:
/    73	    int i;
	.stabs	"i:(0,1)",0x80,0,4,-4
/    74	    for (i = 0; i < wordcount; i++)
	.stabn	0300,0,2,.LL121
.LL121:
	.stabn	0104,0,74,.LL122
.LL122:
	movl	$0,-4(%ebp)
.L42:
	movl	12(%ebp),%eax
	cmpl	%eax,-4(%ebp)
	jge	.L41
/    75	      {
/    76	        *(page+i) = byte_swap_word(*(page+i));
	.stabn	0104,0,76,.LL123
.LL123:
	movl	8(%ebp),%eax
	movl	-4(%ebp),%edx
	movzwl	(%eax,%edx,2),%eax
	pushl	%eax
	movl	0(%esp),%eax
	rolw	$8,%ax
	popl	%ecx
	movl	8(%ebp),%edx
	movl	-4(%ebp),%ecx
	movw	%ax,(%edx,%ecx,2)
/    77	      };
.L40:
	.stabn	0104,0,74,.LL124
.LL124:
	incl	-4(%ebp)
	jmp	.L42
.L41:
/    78	    };
	.stabn	0340,0,2,.LL125
.LL125:
	.stabn	0104,0,78,.LL126
.LL126:
.L37:
	leave
	ret
.L39:
	pushl	%ebp
	movl	%esp,%ebp
	pushl	%eax
	jmp	.L38
/FUNCEND
        .data
        .text
	.stabn	0104,0,86,.LL127
.LL127:
	.stabs	"word_swap_page:F(0,1)",0x24,0,4,word_swap_page
/    87	   register int longwordcount;
	.stabs	"longwordcount:r(0,1)",0x40,0,4,4
/    88	   {
	.stabs	"page:p(10,10)",0xa0,0,2,8
	.stabs	"longwordcount:p(0,1)",0xa0,0,4,12
	.globl	word_swap_page
word_swap_page:
	jmp	.L46
.L45:
	movl	12(%ebp),%edi
/    89	    register int i;
	.stabs	"i:r(0,1)",0x40,0,4,5
/    90	    register unsigned int  *longpage;
	.stabs	"longpage:r(0,14)=*(0,8)",0x40,0,4,8
/    91	    longpage = page;
	.stabn	0300,0,2,.LL128
.LL128:
	.stabn	0104,0,91,.LL129
.LL129:
	movl	8(%ebp),%ebx
/    92	    for (i = 0; i < (longwordcount+longwordcount); i++)
	.stabn	0104,0,92,.LL130
.LL130:
	xorl	%esi,%esi
.L49:
	movl	%edi,%eax
	addl	%edi,%eax
	cmpl	%eax,%esi
	jge	.L48
/    93	      {
/    94	        *(page+i) = byte_swap_word(*(page+i));
	.stabn	0104,0,94,.LL131
.LL131:
	movl	8(%ebp),%eax
	movzwl	(%eax,%esi,2),%eax
	pushl	%eax
	movl	0(%esp),%eax
	rolw	$8,%ax
	popl	%ecx
	movl	8(%ebp),%edx
	movw	%ax,(%edx,%esi,2)
/    95	      };
.L47:
	.stabn	0104,0,92,.LL132
.LL132:
	incl	%esi
	jmp	.L49
.L48:
/    96	    for (i = 0; i < longwordcount; i++)
	.stabn	0104,0,96,.LL133
.LL133:
	xorl	%esi,%esi
.L52:
	cmpl	%edi,%esi
	jge	.L51
/    97	      {
/    98	        *(longpage+i) = word_swap_longword(*(longpage+i));
	.stabn	0104,0,98,.LL134
.LL134:
	pushl	(%ebx,%esi,4)
	movl	0(%esp),%eax
	rol	$16,%eax
	popl	%ecx
	movl	%eax,(%ebx,%esi,4)
/    99	      };
.L50:
	.stabn	0104,0,96,.LL135
.LL135:
	incl	%esi
	jmp	.L52
.L51:
/   100	    };
	.stabn	0340,0,2,.LL136
.LL136:
	.stabn	0104,0,100,.LL137
.LL137:
.L44:
/ASMQ
	movl	-12(%ebp),%ebx
	movl	-8(%ebp),%esi
	movl	-4(%ebp),%edi
/ASMEND
	leave
	ret
.L46:
	pushl	%ebp
	movl	%esp,%ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	jmp	.L45
/FUNCEND
        .data
        .text
	.stabn	0104,0,109,.LL138
.LL138:
	.stabs	"reversedbits:G(0,15)=ar(0,1);0;255;(0,5)",0x20,0,1,0
        .data
	.globl	reversedbits
reversedbits:
	.long	0xc0408000
	.long	0xe060a020
	.long	0xd0509010
	.long	0xf070b030
	.long	0xc8488808
	.long	0xe868a828
	.long	0xd8589818
	.long	0xf878b838
	.long	0xc4448404
	.long	0xe464a424
	.long	0xd4549414
	.long	0xf474b434
	.long	0xcc4c8c0c
	.long	0xec6cac2c
	.long	0xdc5c9c1c
	.long	0xfc7cbc3c
	.long	0xc2428202
	.long	0xe262a222
	.long	0xd2529212
	.long	0xf272b232
	.long	0xca4a8a0a
	.long	0xea6aaa2a
	.long	0xda5a9a1a
	.long	0xfa7aba3a
	.long	0xc6468606
	.long	0xe666a626
	.long	0xd6569616
	.long	0xf676b636
	.long	0xce4e8e0e
	.long	0xee6eae2e
	.long	0xde5e9e1e
	.long	0xfe7ebe3e
	.long	0xc1418101
	.long	0xe161a121
	.long	0xd1519111
	.long	0xf171b131
	.long	0xc9498909
	.long	0xe969a929
	.long	0xd9599919
	.long	0xf979b939
	.long	0xc5458505
	.long	0xe565a525
	.long	0xd5559515
	.long	0xf575b535
	.long	0xcd4d8d0d
	.long	0xed6dad2d
	.long	0xdd5d9d1d
	.long	0xfd7dbd3d
	.long	0xc3438303
	.long	0xe363a323
	.long	0xd3539313
	.long	0xf373b333
	.long	0xcb4b8b0b
	.long	0xeb6bab2b
	.long	0xdb5b9b1b
	.long	0xfb7bbb3b
	.long	0xc7478707
	.long	0xe767a727
	.long	0xd7579717
	.long	0xf777b737
	.long	0xcf4f8f0f
	.long	0xef6faf2f
	.long	0xdf5f9f1f
	.long	0xff7fbf3f
        .text
	.stabn	0104,0,169,.LL139
.LL139:
	.stabs	"bit_reverse_region:F(0,1)",0x24,0,4,bit_reverse_region
	.stabs	"top:r(10,10)",0x40,0,2,4
/   170	  int width, height, rasterwidth;
/   171	  {
	.stabs	"top:p(10,10)",0xa0,0,2,8
	.stabs	"width:p(0,1)",0xa0,0,4,12
	.stabs	"height:p(0,1)",0xa0,0,4,16
	.stabs	"rasterwidth:p(0,1)",0xa0,0,4,20
	.globl	bit_reverse_region
bit_reverse_region:
	jmp	.L58
.L57:
	movl	8(%ebp),%edi
/   172	    register int i, j, wordwid = ((width+31)>>5)<<1;
	.stabs	"i:r(0,1)",0x40,0,4,5
	.stabs	"j:r(0,1)",0x40,0,4,8
	.stabs	"wordwid:(0,1)",0x80,0,4,-4
	.stabn	0104,0,172,.LL140
.LL140:
	movl	12(%ebp),%eax
	leal	31(%eax),%eax
	sarl	$5,%eax
	leal	(%eax,%eax),%eax
	movl	%eax,-4(%ebp)
/   173	    register unsigned short *word;
	.stabs	"word:(10,10)",0x80,0,2,-8
/   174	
/   175	    for (i = 0; i < height; i++)
	.stabn	0300,0,2,.LL141
.LL141:
	.stabn	0104,0,175,.LL142
.LL142:
	xorl	%esi,%esi
.L61:
	cmpl	16(%ebp),%esi
	jge	.L60
/   176	      {
/   177		word = top;
	.stabn	0104,0,177,.LL143
.LL143:
	movl	%edi,-8(%ebp)
/   178		for (j = 0; j < wordwid; j++)
	.stabn	0104,0,178,.LL144
.LL144:
	xorl	%ebx,%ebx
.L64:
	cmpl	-4(%ebp),%ebx
	jge	.L63
/   179		  {
/   180		    GETWORD(word+j) = reverse_bits(GETWORD(word+j));
	.stabn	0104,0,180,.LL145
.LL145:
	leal	(%ebx,%ebx),%eax
	movl	%eax,-12(%ebp)
	leal	(%ebx,%ebx),%eax
	movl	-8(%ebp),%edx
	addl	%eax,%edx
	movl	%edx,%eax
	xorl	$2,%eax
	leal	(%ebx,%ebx),%edx
	movl	-8(%ebp),%ecx
	addl	%edx,%ecx
	movl	%ecx,%edx
	xorl	$2,%edx
	movzwl	(%edx),%edx
	shrl	$8,%edx
	andl	$255,%edx
	movzbl	reversedbits(%edx),%edx
	shll	$8,%edx
	movl	-8(%ebp),%ecx
	addl	-12(%ebp),%ecx
	xorl	$2,%ecx
	movzwl	(%ecx),%ecx
	andl	$255,%ecx
	movzbl	reversedbits(%ecx),%ecx
	orl	%ecx,%edx
	movw	%dx,(%eax)
/   181		  }
.L62:
	.stabn	0104,0,178,.LL146
.LL146:
	incl	%ebx
	jmp	.L64
.L63:
/   182		word_swap_page((int)word&0xFFFFFFFE, (wordwid+1)>>1);
	.stabn	0104,0,182,.LL147
.LL147:
	movl	-4(%ebp),%eax
	incl	%eax
	sarl	$1,%eax
	pushl	%eax
	movl	-8(%ebp),%eax
	andl	$-2,%eax
	pushl	%eax
	movl	4(%esp),%ecx	/ word count into the loop counter
	movl	0(%esp),%edx	/ address of the block to swap
...0:	movl	0(%edx),%eak
	rolw	$8,%ax
	roll	$16,%eax
	rolw	$8,%ax
	movl	%eax,0(%edx)
	add	$4,%edx
	loop	...0
	addl	$8,%esp
/   183		top += rasterwidth;
	.stabn	0104,0,183,.LL148
.LL148:
	movl	20(%ebp),%eax
	leal	(%eax,%eax),%eax
	addl	%eax,%edi
/   184	      }
.L59:
	.stabn	0104,0,175,.LL149
.LL149:
	incl	%esi
	jmp	.L61
.L60:
/   185	
/   186	  }
	.stabn	0340,0,2,.LL150
.LL150:
	.stabn	0104,0,186,.LL151
.LL151:
.L56:
/ASMQ
	movl	-24(%ebp),%ebx
	movl	-20(%ebp),%esi
	movl	-16(%ebp),%edi
/ASMEND
	leave
	ret
.L58:
	pushl	%ebp
	movl	%esp,%ebp
	subl	$12,%esp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	jmp	.L57
/FUNCEND
        .data
.L12:

        .byte    0x40,0x28,0x23,0x29,0x20,0x62,0x79,0x74,0x65,0x73
        .byte    0x77,0x61,0x70,0x66,0x6e,0x73,0x2e,0x63,0x09,0x31
        .byte    0x2e,0x35,0x20,0x33,0x2f,0x32,0x33,0x2f,0x38,0x39
        .byte    0x09,0x09,0x28,0x65,0x6e,0x76,0x6f,0x73,0x20,0x26
        .byte    0x20,0x46,0x75,0x6a,0x69,0x20,0x58,0x65,0x72,0x6f
        .byte    0x78,0x29,0x00
