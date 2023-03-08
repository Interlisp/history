/* %Z% %M% Version %I% (%G%). copyright Venue & Fuji Xerox  */

/************************************************************************/
/*									*/
/*			b i t b l t 3 8 6 i . s				*/
/*									*/
/*	Hand-tuned bitblt code for the Sun386i				*/
/*									*/
/************************************************************************/


/************************************************************************/
/*									*/
/*	Copyright 1990 Venue.						*/
/*									*/
/*	This file is work-product resulting from the Xerox/Venue	*/
/*	Agreement dated 18-August-1989 for support of Medley.		*/
/*									*/
/************************************************************************/


#define srcbase 8(%ebp)
#define dstbase 12(%ebp)
#define sx 16(%ebp)
#define dx 20(%ebp)
#define w 24(%ebp)
#define h 28(%ebp)
#define srcbpl 32(%ebp)
#define dstbpl 36(%ebp)
#define backwardflg 40(%ebp)
#define src_comp 44(%ebp)
#define op 48(%ebp)
#define gray 52(%ebp)
#define num_gray 56(%ebp)
#define curr_gray_line 60(%ebp)

#define num_lines_remaining -4(%ebp)
#define temp -8(%ebp)
#define dstnumL -12(%ebp)
#define src32lbit -16(%ebp)
#define src32Lshift -20(%ebp)
#define dst32lbit -24(%ebp)
#define srcRmask -28(%ebp)
#define dstold -32(%ebp)
#define dstdata -36(%ebp)
#define mask -40(%ebp)
#define x32byta -44(%ebp)
#define s32nbyt -48(%ebp)
#define x32ia -52(%ebp)
#define abc -56(%ebp)
#define dst32rbit -60(%ebp)
#define src32rbit -64(%ebp)
#define fwd -68(%ebp)
#define OrigSrcAddr -72(%ebp)
#define OrigDstAddr -76(%ebp)
#define bbfast -80(%ebp)
#define preloop_mask -84(%ebp)
#define postloop_mask -88(%ebp)
#define sdw_mask -92(%ebp)
#define dst32addr
#define src32addr
#define shS
#define savedS -96(%ebp)
#define newS -100(%ebp)
#define srcRshift -104(%ebp)
#define cnt -108(%ebp)


//	.file	"bitblt386i.s"
	.version	"sun386-1.0"
	.optim
.LL0:
        .data
	.data
	.align	4
.L58:
	.long	.L53
	.long	.L54
	.long	.L55
	.long	.L56
	.data
	.align	4
.L78:
	.long	.L61
	.long	.L65
	.long	.L69
	.long	.L73
	.data
	.align	4
.L95:
	.long	.L90
	.long	.L91
	.long	.L92
	.long	.L93
	.data
	.align	4
.L117:
	.long	.L100
	.long	.L104
	.long	.L108
	.long	.L112
	.data
	.align	4
.L138:
	.long	.L121
	.long	.L125
	.long	.L129
	.long	.L133
	.data
	.align	4
.L160:
	.long	.L143
	.long	.L147
	.long	.L151
	.long	.L155
	.data
	.align	4
.L181:
	.long	.L164
	.long	.L168
	.long	.L172
	.long	.L176
	.data
	.align	4
.L199:
	.long	.L194
	.long	.L195
	.long	.L196
	.long	.L197
	.data
	.align	4
.L221:
	.long	.L204
	.long	.L208
	.long	.L212
	.long	.L216
	.data
	.align	4
.L242:
	.long	.L225
	.long	.L229
	.long	.L233
	.long	.L237
	.data
	.align	4
.L264:
	.long	.L247
	.long	.L251
	.long	.L255
	.long	.L259
	.data
	.align	4
.L285:
	.long	.L268
	.long	.L272
	.long	.L276
	.long	.L280
	.data
	.align	4
.L297:
	.long	.L292
	.long	.L293
	.long	.L294
	.long	.L295
	.text
	.globl	bitblt
bitblt:
	pushl	%ebp
	movl	%esp,%ebp
	subl	$108,%esp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	movl	h,%eax
	movl	%eax,num_lines_remaining
	movl	backwardflg,%eax
	notl	%eax
	movl	%eax,fwd
	movl	srcbpl,%eax
	orl	dstbpl,%eax
	testl	$31,%eax
	jne	.L17
	movl	$1,%eax
	jmp	.L18
.L17:
	xorl	%eax,%eax
.L18:
	movl	%eax,bbfast
	cmpl	$0,gray
	je	.L19
	movl	dstbase,%edx
	cmpl	$0,dx
	jge	.L20
	movl	$7,%eax
	subl	dx,%eax
	sarl	$3,%eax
	subl	%eax,%edx
	jmp	..0
.L20:
	movl	dx,%eax
	sarl	$3,%eax
	addl	%eax,%edx
..0:
/	movl	%edx,x32byta
	movl	%edx,%eax
	andl	$3,%eax
	movl	%eax,s32nbyt
/	movl	x32byta,%eax
/	subl	s32nbyt,%eax
	subl	%eax,%edx
/	movl	%eax,x32ia
/	movl	%eax,%edi
	movl	%edx,%edi
/	movl	s32nbyt,%eax
	leal	(,%eax,8),%eax
	movl	dx,%edx
	andl	$7,%edx
	addl	%edx,%eax
	movl	%eax,dst32lbit
	addl	w,%eax
	decl	%eax
	andl	$31,%eax
	movl	%eax,dst32rbit
	movl	%edi,OrigDstAddr
	cmpl	$0,dst32lbit
	je	.L22
	movl	$32,%eax
	subl	dst32lbit,%eax
	movl	%eax,%ecx
	movl	$-1,%eax
	shll	%cl,%eax
	notl	%eax
	jmp	.L23
.L22:
	movl	$-1,%eax
.L23:
	movl	%eax,preloop_mask
	movl	$31,%eax
	subl	dst32rbit,%eax
	movl	%eax,%ecx
	movl	$-1,%eax
	shll	%cl,%eax
	movl	%eax,postloop_mask
	movl	preloop_mask,%eax
	andl	postloop_mask,%eax
	movl	%eax,sdw_mask
	movl	dst32lbit,%eax
	addl	w,%eax
	sarl	$5,%eax
	decl	%eax
	movl	%eax,dstnumL
	testl	$31,dstbpl
	jne	.L24
	movl	$1,%eax
	jmp	.L25
.L24:
	xorl	%eax,%eax
.L25:
	movl	%eax,bbfast
	movl	sx,%eax
	andl	$15,%eax
	movl	%eax,src32lbit
	jmp	.L26
..16:
	cmpl	$0,gray
	je	.L47
	movl	src32lbit,%eax
	subl	dst32lbit,%eax
	andl	$15,%eax
	movl	%eax,src32Lshift
	movl	srcbase,%eax
	movzwl	(%eax),%eax
	movl	%eax,%ebx
	shll	$16,%eax
	orl	%eax,%ebx
	movl	src32Lshift,%ecx
	shll	%cl,%ebx
	movl	%ebx,%eax
	shrl	$16,%eax
/	andl	$65535,%eax
	orl	%eax,%ebx
	cmpl	$0,src_comp
	je	.L48
/	movl	%ebx,%eax
/	notl	%eax
	notl	%ebx
/	movl	%eax,%ebx
.L48:
	movl	dst32lbit,%eax
	addl	w,%eax
	cmpl	$32,%eax
	jle	..1
	movl	preloop_mask,%eax
	movl	%eax,mask
	movl	(%edi),%eax
	movl	%eax,dstdata
	movl	mask,%eax
	notl	%eax
	movl	dstdata,%edx
	andl	%edx,%eax
	movl	%eax,dstold
	movl	op,%eax
/	cmpl	$3,%eax
/	ja	.L57
/	testl	%eax,%eax
/	jl	.L57
	jmp	*.L58(,%eax,4)
.L19:
	cmpl	$0,fwd
	je	.L27
	cmpl	$0,dx
	jge	.L28
	movl	$7,%eax
	subl	dx,%eax
	sarl	$3,%eax
	movl	dstbase,%edx
	subl	%eax,%edx
	jmp	..2
.L28:
	movl	dx,%eax
	sarl	$3,%eax
	movl	dstbase,%edx
	addl	%eax,%edx
..2:
/	movl	%edx,x32byta
	movl	%edx,%eax
	andl	$3,%eax
/	movl	%eax,s32nbyt
/	movl	x32byta,%eax
/	subl	s32nbyt,%eax
	subl	%eax,%edx
/	movl	%eax,x32ia
/	movl	%eax,%edi
	movl	%edx,%edi
/	movl	s32nbyt,%eax
	leal	(,%eax,8),%eax
	movl	dx,%edx
	andl	$7,%edx
	addl	%edx,%eax
	movl	%eax,dst32lbit
	addl	w,%eax
	decl	%eax
	andl	$31,%eax
	movl	%eax,dst32rbit
	movl	%edi,OrigDstAddr
	cmpl	$0,dst32lbit
	je	.L30
	movl	$32,%eax
	subl	dst32lbit,%eax
	movl	%eax,%ecx
	movl	$-1,%eax
	shll	%cl,%eax
	notl	%eax
	jmp	.L31
.L30:
	movl	$-1,%eax
.L31:
	movl	%eax,preloop_mask
	movl	$31,%eax
	subl	dst32rbit,%eax
	movl	%eax,%ecx
	movl	$-1,%eax
	shll	%cl,%eax
	movl	%eax,postloop_mask
	movl	preloop_mask,%eax
	andl	postloop_mask,%eax
	movl	%eax,sdw_mask
	movl	dst32lbit,%eax
	addl	w,%eax
	sarl	$5,%eax
	decl	%eax
	movl	%eax,dstnumL
	cmpl	$0,sx
	jge	.L32
	movl	$7,%eax
	subl	sx,%eax
	sarl	$3,%eax
	movl	srcbase,%edx
	subl	%eax,%edx
	jmp	..3
.L32:
	movl	sx,%eax
	sarl	$3,%eax
	movl	srcbase,%edx
	addl	%eax,%edx
..3:
/	movl	%edx,x32byta
	movl	%edx,%eax
	andl	$3,%eax
/	movl	%eax,s32nbyt
/	movl	x32byta,%eax
/	subl	s32nbyt,%eax
	subl	%eax,%edx
/	movl	%eax,x32ia
/	movl	%eax,%esi
	movl	%edx,%esi
/	movl	s32nbyt,%eax
	leal	(,%eax,8),%eax
	movl	sx,%edx
	andl	$7,%edx
	addl	%edx,%eax
	movl	%eax,src32lbit
	addl	w,%eax
	decl	%eax
	andl	$31,%eax
	movl	%eax,src32rbit
	movl	dst32lbit,%eax
	subl	src32lbit,%eax
	andl	$31,%eax
	movl	%eax,srcRshift
	movl	src32lbit,%eax
	subl	dst32lbit,%eax
	andl	$31,%eax
	movl	%eax,src32Lshift
	cmpl	$0,src32Lshift
	jne	..4
	movl	$-1,%eax
.L325:
.L35:
	movl	%eax,srcRmask
	movl	%esi,OrigSrcAddr
	jmp	.L36
.L27:
	movl	dx,%eax
	addl	w,%eax
	decl	%eax
	movl	%eax,abc
	cmpl	$0,abc
	jge	.L37
	movl	$7,%eax
	subl	abc,%eax
	sarl	$3,%eax
	movl	dstbase,%edx
	subl	%eax,%edx
	jmp	..5
.L37:
	movl	abc,%eax
	sarl	$3,%eax
	movl	dstbase,%edx
	addl	%eax,%edx
..5:
/	movl	%edx,x32byta
	movl	%edx,%eax
	andl	$3,%eax
/	movl	%eax,s32nbyt
/	movl	x32byta,%eax
/	subl	s32nbyt,%eax
	subl	%eax,%edx
/	movl	%eax,x32ia
/	movl	%eax,%edi
	movl	%edx,%edi
/	movl	s32nbyt,%eax
	leal	(,%eax,8),%eax
	movl	abc,%edx
	andl	$7,%edx
	addl	%edx,%eax
	movl	%eax,dst32rbit
	subl	w,%eax
	incl	%eax
	andl	$31,%eax
	movl	%eax,dst32lbit
	movl	%edi,OrigDstAddr
	movl	$31,%eax
	subl	dst32rbit,%eax
	movl	%eax,%ecx
	movl	$-1,%eax
	shll	%cl,%eax
	movl	%eax,preloop_mask
	movl	$32,%eax
	subl	dst32lbit,%eax
	movl	%eax,%ecx
	movl	$-1,%eax
	shll	%cl,%eax
	notl	%eax
	movl	%eax,postloop_mask
	movl	preloop_mask,%eax
	andl	postloop_mask,%eax
	movl	%eax,sdw_mask
	movl	w,%eax
	subl	dst32rbit,%eax
	decl	%eax
	jle	.L39
	movl	w,%eax
	subl	dst32rbit,%eax
	decl	%eax
	sarl	$5,%eax
	jmp	.L40
.L39:
	xorl	%eax,%eax
.L40:
	movl	%eax,dstnumL
	movl	sx,%eax
	addl	w,%eax
	decl	%eax
	movl	%eax,abc
	cmpl	$0,abc
	jge	.L41
	movl	$7,%eax
	subl	abc,%eax
	sarl	$3,%eax
	movl	srcbase,%edx
	subl	%eax,%edx
	jmp	..6
.L41:
	movl	abc,%eax
	sarl	$3,%eax
	movl	srcbase,%edx
	addl	%eax,%edx
..6:
/	movl	%edx,x32byta
	movl	%edx,%eax
	andl	$3,%eax
/	movl	%eax,s32nbyt
/	movl	x32byta,%eax
/	subl	s32nbyt,%eax
	subl	%eax,%edx
/	movl	%eax,x32ia
/	movl	%eax,%esi
	movl	%edx,%esi
/	movl	s32nbyt,%eax
	leal	(,%eax,8),%eax
	movl	abc,%edx
	andl	$7,%edx
	addl	%edx,%eax
	movl	%eax,src32rbit
	subl	w,%eax
	incl	%eax
	andl	$31,%eax
	movl	%eax,src32lbit
	movl	dst32lbit,%eax
	subl	src32lbit,%eax
	andl	$31,%eax
	movl	%eax,srcRshift
	movl	src32lbit,%eax
	subl	dst32lbit,%eax
	andl	$31,%eax
	movl	%eax,src32Lshift
	cmpl	$0,src32Lshift
	je	.L43
	jmp	..4
.L53:				// dstdata is in %edx starting here.
	movl	%ebx,%edx
	jmp	.L51
.L54:
/	movl	%ebx,%eax
/	andl	%eax,dstdata
	andl	%ebx,%edx
	jmp	.L51
.L55:
/	movl	%ebx,%eax
/	orl	%eax,dstdata
	orl	%ebx,%edx
	jmp	.L51
.L56:
/	movl	%ebx,%eax
/	xorl	%eax,dstdata
	xorl	%ebx,%edx
.L57:
.L51:
/	movl	mask,%eax
/	andl	%eax,%edx
	andl	mask,%edx
/	movl	dstold,%eax
/	orl	%eax,dstdata
	orl	dstold,%edx
/	movl	dstdata,%eax
/	movl	%eax,(%edi) 
	movl	%edx,(%edi)	// end of dstdata in %edx
	movl	op,%eax
	addl	$4,%edi
/	cmpl	$3,%eax
/	ja	.L77
/	testl	%eax,%eax
/	jl	.L77
	movl	dstnumL,%ecx	// cnt is in %ecx from here down
	inc	%ecx
	jmp	*.L78(,%eax,4)
/.L61:
/	movl	dstnumL,%eax
/	movl	%eax,cnt
.L64:
/	decl	cnt
/	jl	.L63
	movl	%ebx,(%edi)
	addl	$4,%edi
.L61:	loop	.L64
	jmp	.L63
/	jmp	.L64
/.L65:
/	movl	dstnumL,%eax
/	movl	%eax,cnt
.L68:
/	decl	cnt
/	jl	.L67
/	movl	%edi,%eax
/	movl	%ebx,%edx
	andl	%ebx,(%edi)
	addl	$4,%edi
/	andl	%edx,(%eax)
.L65:	loop	.L68
	jmp	.L67
/	jmp	.L68
/.L69:
/	movl	dstnumL,%eax
/	movl	%eax,cnt
/	jmp	.L72
..7:
/	movl	%edi,%eax
/	movl	%ebx,%edx
	orl	%ebx,(%edi)
	addl	$4,%edi
/	orl	%edx,(%eax)
.L72:
.L69:
/	decl	cnt
/	jge	..7
	loop	..7
	jmp	.L75
/.L73:
/	movl	dstnumL,%eax
/	movl	%eax,cnt
/	jmp	.L76
..8:
/	movl	%edi,%eax
/	movl	%ebx,%edx
	xorl	%ebx,(%edi)
	addl	$4,%edi
/	xorl	%edx,(%eax)
.L76:
/	decl	cnt
/	jge	..8
.L73:	loop	..8
.L75:
.L67:
.L63:
.L77:
	cmpl	$31,dst32rbit
	je	.L79
.L289:
.L185:
	movl	postloop_mask,%eax
..11:
	movl	%eax,mask
	movl	(%edi),%edx	// dstdata is in %edx from here down.
/	movl	%eax,dstdata
/	movl	mask,%eax
	notl	%eax
/	movl	dstdata,%edx
/	andl	%eax,%edx
	andl	%edx,%eax
	movl	%eax,dstold
	movl	op,%eax
/	cmpl	$3,%eax
/	ja	.L296
/	testl	%eax,%eax
/	jl	.L296
	jmp	*.L297(,%eax,4)
.L47:
	cmpl	$0,fwd
	je	.L81
	movl	dst32lbit,%eax
	cmpl	%eax,src32lbit
	jle	.L82
	movl	src32lbit,%eax
	addl	w,%eax
	cmpl	$32,%eax
	jle	.L82
	movl	(%esi),%edx
	movl	%edx,newS
	movl	src32Lshift,%ecx
	movl	newS,%eax
	addl	$4,%esi
	shll	%cl,%eax
	movl	%eax,savedS
	movl	(%esi),%edx
	movl	%edx,newS
	movl	srcRshift,%ecx
	movl	newS,%eax
	addl	$4,%esi
	shrl	%cl,%eax
	andl	srcRmask,%eax
	orl	savedS,%eax
	movl	%eax,%ebx
	movl	src32Lshift,%ecx
	movl	newS,%eax
	shll	%cl,%eax
	movl	srcRmask,%edx
	notl	%edx
	andl	%edx,%eax
	movl	%eax,savedS
	jmp	.L83
.L82:
	movl	dst32lbit,%eax
	cmpl	%eax,src32lbit
	jg	.L84
	movl	(%esi),%edx
	movl	%edx,newS
	movl	srcRshift,%ecx
	movl	newS,%eax
	addl	$4,%esi
	shrl	%cl,%eax
	andl	srcRmask,%eax
	movl	%eax,%ebx
	movl	src32Lshift,%ecx
	movl	newS,%eax
	shll	%cl,%eax
	movl	srcRmask,%edx
	notl	%edx
	andl	%edx,%eax
	movl	%eax,savedS
	jmp	.L85
.L84:
	movl	(%esi),%edx
	movl	%edx,newS
	movl	src32Lshift,%ecx
	movl	newS,%eax
	addl	$4,%esi
	shll	%cl,%eax
	movl	%eax,%ebx
.L85:
.L83:
	cmpl	$0,src_comp
	je	.L86
/	movl	%ebx,%eax
/	notl	%eax
/	movl	%eax,%ebx
	notl	%ebx		//inserted
.L86:
	movl	dst32lbit,%eax
	addl	w,%eax
	cmpl	$32,%eax
	jle	..1
	movl	preloop_mask,%eax
	movl	%eax,mask
	movl	(%edi),%eax
	movl	%eax,dstdata
	movl	mask,%eax
	notl	%eax
	movl	dstdata,%edx
	andl	%eax,%edx
	movl	%edx,dstold
	movl	op,%eax
/	cmpl	$3,%eax
/	ja	.L94
/	testl	%eax,%eax
/	jl	.L94
	jmp	*.L95(,%eax,4)
.L90:
	movl	%ebx,dstdata
	jmp	.L88
.L91:
	movl	%ebx,%eax
	andl	%eax,dstdata
	jmp	.L88
.L92:
	movl	%ebx,%eax
	orl	%eax,dstdata
	jmp	.L88
.L93:
	movl	%ebx,%eax
	xorl	%eax,dstdata
.L94:
.L88:
	movl	mask,%eax
	andl	%eax,dstdata
	movl	dstold,%eax
	orl	%eax,dstdata
	movl	dstdata,%eax
	movl	%eax,(%edi)
	movl	dst32lbit,%eax
	addl	$4,%edi
	cmpl	%eax,src32lbit
	jne	.L96
	cmpl	$0,src_comp
	jne	.L99
	movl	op,%eax
/	cmpl	$3,%eax
/	ja	.L137
/	testl	%eax,%eax
/	jl	.L137
	jmp	*.L138(,%eax,4)
.L99:
	movl	op,%eax
/	cmpl	$3,%eax
/	ja	.L116
/	testl	%eax,%eax
/	jl	.L116
	jmp	*.L117(,%eax,4)
.L100:
	movl	dstnumL,%eax
	movl	%eax,cnt
.L103:
	decl	cnt
	jl	.L102
	movl	%edi,%eax
	movl	(%esi),%edx
	addl	$4,%edi
	addl	$4,%esi
	notl	%edx
	movl	%edx,(%eax)
	jmp	.L103
.L104:
	movl	dstnumL,%eax
	movl	%eax,cnt
.L107:
	decl	cnt
	jl	.L106
	movl	%edi,%eax
	movl	(%esi),%edx
	addl	$4,%edi
	addl	$4,%esi
	notl	%edx
	andl	%edx,(%eax)
	jmp	.L107
.L108:
	movl	dstnumL,%eax
	movl	%eax,cnt
.L111:
	decl	cnt
	jl	.L110
	movl	%edi,%eax
	movl	(%esi),%edx
	addl	$4,%edi
	addl	$4,%esi
	notl	%edx
	orl	%edx,(%eax)
	jmp	.L111
.L112:
	movl	dstnumL,%eax
	movl	%eax,cnt
.L115:
	decl	cnt
	jl	.L114
	movl	%edi,%eax
	movl	(%esi),%edx
	addl	$4,%edi
	addl	$4,%esi
	notl	%edx
	xorl	%edx,(%eax)
	jmp	.L115
.L121:
	movl	dstnumL,%eax
	movl	%eax,cnt
.L124:
	decl	cnt
	jl	.L123
	movl	%edi,%eax
	movl	%esi,%edx
	movl	(%edx),%ecx
	movl	%ecx,(%eax)
	addl	$4,%edi
	addl	$4,%esi
	jmp	.L124
.L125:
	movl	dstnumL,%eax
	movl	%eax,cnt
.L128:
	decl	cnt
	jl	.L127
	movl	%edi,%eax
	movl	(%esi),%edx
	addl	$4,%edi
	addl	$4,%esi
	andl	%edx,(%eax)
	jmp	.L128
.L129:
	movl	dstnumL,%eax
	movl	%eax,cnt
.L132:
	decl	cnt
	jl	.L131
	movl	%edi,%eax
	movl	(%esi),%edx
	addl	$4,%edi
	addl	$4,%esi
	orl	%edx,(%eax)
	jmp	.L132
.L133:
	movl	dstnumL,%eax
	movl	%eax,cnt
.L136:
	decl	cnt
	jl	.L135
	movl	%edi,%eax
	movl	(%esi),%edx
	addl	$4,%edi
	addl	$4,%esi
	xorl	%edx,(%eax)
	jmp	.L136
.L96:
	cmpl	$0,src_comp
	jne	.L142
	movl	op,%eax
/	cmpl	$3,%eax
/	ja	.L180
/	testl	%eax,%eax
/	jl	.L180
	jmp	*.L181(,%eax,4)
.L142:
	movl	op,%eax
/	cmpl	$3,%eax
/	ja	.L159
/	testl	%eax,%eax
/	jl	.L159
	jmp	*.L160(,%eax,4)
.L143:
	movl	dstnumL,%eax
	movl	%eax,cnt
.L146:
	decl	cnt
	jl	.L145
	movl	(%esi),%edx
	movl	%edx,newS
	movl	srcRshift,%ecx
	movl	newS,%eax
	addl	$4,%esi
	shrl	%cl,%eax
	movl	savedS,%edx
	orl	%eax,%edx
	movl	%edx,%eax
	notl	%eax
	movl	%eax,%ebx
	movl	src32Lshift,%ecx
	movl	newS,%eax
	shll	%cl,%eax
	movl	%eax,savedS
	movl	%ebx,(%edi)
	addl	$4,%edi
	jmp	.L146
.L147:
	movl	dstnumL,%eax
	movl	%eax,cnt
.L150:
	decl	cnt
	jl	.L149
	movl	(%esi),%edx
	movl	%edx,newS
	movl	srcRshift,%ecx
	movl	newS,%eax
	addl	$4,%esi
	shrl	%cl,%eax
	orl	savedS,%eax
	notl	%eax
	movl	%eax,%ebx
	movl	src32Lshift,%ecx
	movl	newS,%eax
	shll	%cl,%eax
	movl	%eax,savedS
	movl	%edi,%eax
	movl	%ebx,%edx
	addl	$4,%edi
	andl	%edx,(%eax)
	jmp	.L150
.L151:
	movl	dstnumL,%eax
	movl	%eax,cnt
.L154:
	decl	cnt
	jl	.L153
	movl	(%esi),%edx
	movl	%edx,newS
	movl	srcRshift,%ecx
	movl	newS,%eax
	addl	$4,%esi
	shrl	%cl,%eax
	orl	savedS,%eax
	notl	%eax
	movl	%eax,%ebx
	movl	src32Lshift,%ecx
	movl	newS,%eax
	shll	%cl,%eax
	movl	%eax,savedS
	movl	%edi,%eax
	movl	%ebx,%edx
	addl	$4,%edi
	orl	%edx,(%eax)
	jmp	.L154
.L155:
	movl	dstnumL,%eax
	movl	%eax,cnt
.L158:
	decl	cnt
	jl	.L157
	movl	(%esi),%edx
	movl	%edx,newS
	movl	srcRshift,%ecx
	movl	newS,%eax
	addl	$4,%esi
	shrl	%cl,%eax
	orl	savedS,%eax
	notl	%eax
	movl	%eax,%ebx
	movl	src32Lshift,%ecx
	movl	newS,%eax
	shll	%cl,%eax
	movl	%eax,savedS
	movl	%edi,%eax
	movl	%ebx,%edx
	addl	$4,%edi
	xorl	%edx,(%eax)
	jmp	.L158
.L164:
	movl	dstnumL,%eax
	movl	%eax,cnt
.L167:
	decl	cnt
	jl	.L166
	movl	(%esi),%edx
	movl	%edx,newS
	movl	srcRshift,%ecx
	movl	newS,%eax
	addl	$4,%esi
	shrl	%cl,%eax
	movl	savedS,%edx
	orl	%eax,%edx
	movl	%edx,%ebx
	movl	src32Lshift,%ecx
	movl	newS,%eax
	shll	%cl,%eax
	movl	%eax,savedS
	movl	%ebx,(%edi)
	addl	$4,%edi
	jmp	.L167
.L168:
	movl	dstnumL,%eax
	movl	%eax,cnt
.L171:
	decl	cnt
	jl	.L170
	movl	(%esi),%edx
	movl	%edx,newS
	movl	srcRshift,%ecx
	movl	newS,%eax
	addl	$4,%esi
	shrl	%cl,%eax
	orl	savedS,%eax
	movl	%eax,%ebx
	movl	src32Lshift,%ecx
	movl	newS,%eax
	shll	%cl,%eax
	movl	%eax,savedS
	movl	%edi,%eax
	movl	%ebx,%edx
	addl	$4,%edi
	andl	%edx,(%eax)
	jmp	.L171
.L172:
	movl	dstnumL,%eax
	movl	%eax,cnt
	jmp	.L175
..9:
	movl	(%esi),%edx
	movl	%edx,newS
	movl	srcRshift,%ecx
	movl	newS,%eax
	addl	$4,%esi
	shrl	%cl,%eax
	orl	savedS,%eax
	movl	%eax,%ebx
	movl	src32Lshift,%ecx
	movl	newS,%eax
	shll	%cl,%eax
	movl	%eax,savedS
	movl	%edi,%eax
	movl	%ebx,%edx
	addl	$4,%edi
	orl	%edx,(%eax)
.L175:
	decl	cnt
	jge	..9
	jmp	.L178
.L176:
	movl	dstnumL,%eax
	movl	%eax,cnt
	jmp	.L179
..10:
	movl	(%esi),%edx
	movl	%edx,newS
	movl	srcRshift,%ecx
	movl	newS,%eax
	addl	$4,%esi
	shrl	%cl,%eax
	orl	savedS,%eax
	movl	%eax,%ebx
	movl	src32Lshift,%ecx
	movl	newS,%eax
	shll	%cl,%eax
	movl	%eax,savedS
	movl	%edi,%eax
	movl	%ebx,%edx
	addl	$4,%edi
	xorl	%edx,(%eax)
.L179:
	decl	cnt
	jge	..10
.L178:
.L170:
.L166:
.L157:
.L153:
.L149:
.L145:
.L159:
.L135:
.L131:
.L127:
.L123:
.L114:
.L110:
.L106:
.L102:
.L116:
.L137:
.L180:
	cmpl	$31,dst32rbit
	je	.L182
	movl	dst32rbit,%eax
	cmpl	%eax,src32rbit
	jg	.L183
	movl	(%esi),%eax
	movl	%eax,newS
	movl	srcRshift,%ecx
	movl	newS,%eax
	shrl	%cl,%eax
	andl	srcRmask,%eax
	orl	savedS,%eax
	movl	%eax,%ebx
	jmp	.L184
..14:
	movl	dst32lbit,%eax
	cmpl	%eax,src32lbit
	jl	.L287
	movl	(%esi),%eax
	movl	%eax,newS
	movl	src32Lshift,%ecx
	movl	newS,%eax
	shll	%cl,%eax
	orl	savedS,%eax
	movl	%eax,%ebx
	jmp	.L288
.L287:
.L183:
	movl	savedS,%ebx
.L288:
.L184:
	cmpl	$0,src_comp
	je	.L185
	movl	%ebx,%eax
	notl	%eax
	movl	%eax,%ebx
	jmp	.L289
.L81:
	movl	dst32rbit,%eax
	cmpl	%eax,src32rbit
	jge	.L186
	movl	src32lbit,%eax
	addl	w,%eax
	movl	dst32lbit,%edx
	incl	%edx
	cmpl	%edx,%eax
	jle	.L186
	movl	%esi,%eax
	subl	$4,%esi
	movl	(%eax),%edx
	movl	%edx,newS
	movl	srcRshift,%ecx
	movl	newS,%eax
	shrl	%cl,%eax
	andl	srcRmask,%eax
	movl	%eax,savedS
	movl	%esi,%eax
	subl	$4,%esi
	movl	(%eax),%edx
	movl	%edx,newS
	movl	src32Lshift,%ecx
	movl	newS,%eax
	shll	%cl,%eax
	orl	savedS,%eax
	movl	%eax,%ebx
	movl	srcRshift,%ecx
	movl	newS,%eax
	shrl	%cl,%eax
	andl	srcRmask,%eax
	movl	%eax,savedS
	jmp	.L187
.L186:
	movl	dst32rbit,%eax
	cmpl	%eax,src32rbit
	jl	.L188
	movl	%esi,%eax
	subl	$4,%esi
	movl	(%eax),%edx
	movl	%edx,newS
	movl	src32Lshift,%ecx
	movl	newS,%eax
	shll	%cl,%eax
	movl	%eax,%ebx
	movl	srcRshift,%ecx
	movl	newS,%eax
	shrl	%cl,%eax
	andl	srcRmask,%eax
	movl	%eax,savedS
	jmp	.L189
.L188:
	movl	%esi,%eax
	subl	$4,%esi
	movl	(%eax),%edx
	movl	%edx,newS
	movl	srcRshift,%ecx
	movl	newS,%eax
	shrl	%cl,%eax
	andl	srcRmask,%eax
	movl	%eax,%ebx
.L189:
.L187:
	cmpl	$0,src_comp
	je	.L190
	movl	%ebx,%eax
	notl	%eax
	movl	%eax,%ebx
.L190:
	movl	dst32lbit,%eax
	addl	w,%eax
	cmpl	$32,%eax
	jg	.L191
..1:
	movl	sdw_mask,%eax
	jmp	..11
.L191:
	movl	preloop_mask,%eax
	movl	%eax,mask
	movl	(%edi),%eax
	movl	%eax,dstdata
	movl	mask,%eax
	notl	%eax
	movl	dstdata,%edx
	andl	%eax,%edx
	movl	%edx,dstold
	movl	op,%eax
/	cmpl	$3,%eax
/	ja	.L198
/	testl	%eax,%eax
/	jl	.L198
	jmp	*.L199(,%eax,4)
.L194:
	movl	%ebx,dstdata
	jmp	.L192
.L195:
	movl	%ebx,%eax
	andl	%eax,dstdata
	jmp	.L192
.L196:
	movl	%ebx,%eax
	orl	%eax,dstdata
	jmp	.L192
.L197:
	movl	%ebx,%eax
	xorl	%eax,dstdata
.L198:
.L192:
	movl	mask,%eax
	andl	%eax,dstdata
	movl	dstold,%eax
	orl	%eax,dstdata
	movl	dstdata,%eax
	movl	%eax,(%edi)
	subl	$4,%edi
	movl	dst32lbit,%eax
	cmpl	%eax,src32lbit
	jne	.L200
	cmpl	$0,src_comp
	jne	.L203
	movl	op,%eax
/	cmpl	$3,%eax
/	ja	.L241
/	testl	%eax,%eax
/	jl	.L241
	jmp	*.L242(,%eax,4)
.L203:
	movl	op,%eax
/	cmpl	$3,%eax
/	ja	.L220
/	testl	%eax,%eax
/	jl	.L220
	jmp	*.L221(,%eax,4)
.L204:
	movl	dstnumL,%eax
	movl	%eax,cnt
.L207:
	decl	cnt
	jl	.L206
	movl	%edi,%eax
	subl	$4,%edi
	movl	%esi,%edx
	subl	$4,%esi
	movl	(%edx),%edx
	notl	%edx
	movl	%edx,(%eax)
	jmp	.L207
.L208:
	movl	dstnumL,%eax
	movl	%eax,cnt
.L211:
	decl	cnt
	jl	.L210
	movl	%edi,%eax
	subl	$4,%edi
	movl	%esi,%edx
	subl	$4,%esi
	movl	(%edx),%edx
	notl	%edx
	andl	%edx,(%eax)
	jmp	.L211
.L212:
	movl	dstnumL,%eax
	movl	%eax,cnt
.L215:
	decl	cnt
	jl	.L214
	movl	%edi,%eax
	subl	$4,%edi
	movl	%esi,%edx
	subl	$4,%esi
	movl	(%edx),%edx
	notl	%edx
	orl	%edx,(%eax)
	jmp	.L215
.L216:
	movl	dstnumL,%eax
	movl	%eax,cnt
.L219:
	decl	cnt
	jl	.L218
	movl	%edi,%eax
	subl	$4,%edi
	movl	%esi,%edx
	subl	$4,%esi
	movl	(%edx),%edx
	notl	%edx
	xorl	%edx,(%eax)
	jmp	.L219
.L225:
	movl	dstnumL,%eax
	movl	%eax,cnt
.L228:
	decl	cnt
	jl	.L227
	movl	%edi,%eax
	subl	$4,%edi
	movl	%esi,%edx
	subl	$4,%esi
	movl	(%edx),%ecx
	movl	%ecx,(%eax)
	jmp	.L228
.L229:
	movl	dstnumL,%eax
	movl	%eax,cnt
.L232:
	decl	cnt
	jl	.L231
	movl	%edi,%eax
	subl	$4,%edi
	movl	%esi,%edx
	subl	$4,%esi
	movl	(%edx),%edx
	andl	%edx,(%eax)
	jmp	.L232
.L233:
	movl	dstnumL,%eax
	movl	%eax,cnt
.L236:
	decl	cnt
	jl	.L235
	movl	%edi,%eax
	subl	$4,%edi
	movl	%esi,%edx
	subl	$4,%esi
	movl	(%edx),%edx
	orl	%edx,(%eax)
	jmp	.L236
.L237:
	movl	dstnumL,%eax
	movl	%eax,cnt
.L240:
	decl	cnt
	jl	.L239
	movl	%edi,%eax
	subl	$4,%edi
	movl	%esi,%edx
	subl	$4,%esi
	movl	(%edx),%edx
	xorl	%edx,(%eax)
	jmp	.L240
.L200:
	cmpl	$0,src_comp
	jne	.L246
	movl	op,%eax
/	cmpl	$3,%eax
/	ja	.L284
/	testl	%eax,%eax
/	jl	.L284
	jmp	*.L285(,%eax,4)
.L246:
	movl	op,%eax
/	cmpl	$3,%eax
/	ja	.L263
/	testl	%eax,%eax
/	jl	.L263
	jmp	*.L264(,%eax,4)
.L247:
	movl	dstnumL,%eax
	movl	%eax,cnt
.L250:
	decl	cnt
	jl	.L249
	movl	%esi,%eax
	subl	$4,%esi
	movl	(%eax),%edx
	movl	%edx,newS
	movl	src32Lshift,%ecx
	movl	newS,%eax
	shll	%cl,%eax
	movl	savedS,%edx
	orl	%eax,%edx
	movl	%edx,%eax
	notl	%eax
	movl	%eax,%ebx
	movl	srcRshift,%ecx
	movl	newS,%eax
	shrl	%cl,%eax
	movl	%eax,savedS
	movl	%edi,%eax
	subl	$4,%edi
	movl	%ebx,(%eax)
	jmp	.L250
.L251:
	movl	dstnumL,%eax
	movl	%eax,cnt
.L254:
	decl	cnt
	jl	.L253
	movl	%esi,%eax
	subl	$4,%esi
	movl	(%eax),%edx
	movl	%edx,newS
	movl	src32Lshift,%ecx
	movl	newS,%eax
	shll	%cl,%eax
	orl	savedS,%eax
	notl	%eax
	movl	%eax,%ebx
	movl	srcRshift,%ecx
	movl	newS,%eax
	shrl	%cl,%eax
	movl	%eax,savedS
	movl	%edi,%eax
	subl	$4,%edi
	movl	%ebx,%edx
	andl	%edx,(%eax)
	jmp	.L254
.L255:
	movl	dstnumL,%eax
	movl	%eax,cnt
.L258:
	decl	cnt
	jl	.L257
	movl	%esi,%eax
	subl	$4,%esi
	movl	(%eax),%edx
	movl	%edx,newS
	movl	src32Lshift,%ecx
	movl	newS,%eax
	shll	%cl,%eax
	orl	savedS,%eax
	notl	%eax
	movl	%eax,%ebx
	movl	srcRshift,%ecx
	movl	newS,%eax
	shrl	%cl,%eax
	movl	%eax,savedS
	movl	%edi,%eax
	subl	$4,%edi
	movl	%ebx,%edx
	orl	%edx,(%eax)
	jmp	.L258
.L259:
	movl	dstnumL,%eax
	movl	%eax,cnt
.L262:
	decl	cnt
	jl	.L261
	movl	%esi,%eax
	subl	$4,%esi
	movl	(%eax),%edx
	movl	%edx,newS
	movl	src32Lshift,%ecx
	movl	newS,%eax
	shll	%cl,%eax
	orl	savedS,%eax
	notl	%eax
	movl	%eax,%ebx
	movl	srcRshift,%ecx
	movl	newS,%eax
	shrl	%cl,%eax
	movl	%eax,savedS
	movl	%edi,%eax
	subl	$4,%edi
	movl	%ebx,%edx
	xorl	%edx,(%eax)
	jmp	.L262
.L268:
	movl	dstnumL,%eax
	movl	%eax,cnt
.L271:
	decl	cnt
	jl	.L270
	movl	%esi,%eax
	subl	$4,%esi
	movl	(%eax),%edx
	movl	%edx,newS
	movl	src32Lshift,%ecx
	movl	newS,%eax
	shll	%cl,%eax
	movl	savedS,%edx
	orl	%eax,%edx
	movl	%edx,%ebx
	movl	srcRshift,%ecx
	movl	newS,%eax
	shrl	%cl,%eax
	movl	%eax,savedS
	movl	%edi,%eax
	subl	$4,%edi
	movl	%ebx,(%eax)
	jmp	.L271
.L272:
	movl	dstnumL,%eax
	movl	%eax,cnt
.L275:
	decl	cnt
	jl	.L274
	movl	%esi,%eax
	subl	$4,%esi
	movl	(%eax),%edx
	movl	%edx,newS
	movl	src32Lshift,%ecx
	movl	newS,%eax
	shll	%cl,%eax
	orl	savedS,%eax
	movl	%eax,%ebx
	movl	srcRshift,%ecx
	movl	newS,%eax
	shrl	%cl,%eax
	movl	%eax,savedS
	movl	%edi,%eax
	subl	$4,%edi
	movl	%ebx,%edx
	andl	%edx,(%eax)
	jmp	.L275
.L276:
	movl	dstnumL,%eax
	movl	%eax,cnt
	jmp	.L279
..12:
	movl	%esi,%eax
	subl	$4,%esi
	movl	(%eax),%edx
	movl	%edx,newS
	movl	src32Lshift,%ecx
	movl	newS,%eax
	shll	%cl,%eax
	orl	savedS,%eax
	movl	%eax,%ebx
	movl	srcRshift,%ecx
	movl	newS,%eax
	shrl	%cl,%eax
	movl	%eax,savedS
	movl	%edi,%eax
	subl	$4,%edi
	movl	%ebx,%edx
	orl	%edx,(%eax)
.L279:
	decl	cnt
	jge	..12
	jmp	.L282
.L280:
	movl	dstnumL,%eax
	movl	%eax,cnt
	jmp	.L283
..13:
	movl	%esi,%eax
	subl	$4,%esi
	movl	(%eax),%edx
	movl	%edx,newS
	movl	src32Lshift,%ecx
	movl	newS,%eax
	shll	%cl,%eax
	orl	savedS,%eax
	movl	%eax,%ebx
	movl	srcRshift,%ecx
	movl	newS,%eax
	shrl	%cl,%eax
	movl	%eax,savedS
	movl	%edi,%eax
	subl	$4,%edi
	movl	%ebx,%edx
	xorl	%edx,(%eax)
.L283:
	decl	cnt
	jge	..13
.L282:
.L274:
.L270:
.L261:
.L257:
.L253:
.L249:
.L263:
.L239:
.L235:
.L231:
.L227:
.L218:
.L214:
.L210:
.L206:
.L220:
.L241:
.L284:
	cmpl	$0,dst32lbit
	jne	..14
	jmp	.L286
.L292:				// dstdata is in %edx from here down
/	movl	%ebx,dstdata
	movl	%ebx,%edx
	jmp	.L290
.L293:
/	movl	%ebx,%eax
/	andl	%eax,dstdata
	andl	%ebx,%edx
	jmp	.L290
.L294:
/	movl	%ebx,%eax
/	orl	%eax,dstdata
	orl	%ebx,%edx
	jmp	.L290
.L295:
/	movl	%ebx,%eax
/	xorl	%eax,dstdata
	xorl	%ebx,%edx
.L296:
.L290:
/	movl	mask,%eax
/	andl	%eax,dstdata
	andl	mask,%edx
/	movl	dstold,%eax
/	orl	%eax,dstdata
/	movl	dstdata,%eax
	orl	dstold,%edx
	movl	%edx,(%edi)
.L286:
.L182:
.L79:
	cmpl	$0,gray
	je	.L298
	cmpl	$0,bbfast
	je	.L299
	movl	dstbpl,%eax
	sarl	$3,%eax
	addl	%eax,OrigDstAddr
	movl	OrigDstAddr,%edi
	jmp	.L300
.L299:
	movl	OrigDstAddr,%edi
	movl	dstbpl,%eax
	addl	%eax,dst32lbit
	movl	dst32lbit,%eax
	sarl	$5,%eax
/	movl	%eax,temp
/	shll	$2,temp
/	movl	temp,%eax
	shll	$2,%eax
	addl	%eax,%edi
	andl	$31,dst32lbit
	movl	dst32lbit,%eax
	addl	w,%eax
	decl	%eax
	andl	$31,%eax
	movl	%eax,dst32rbit
	movl	%edi,OrigDstAddr
	cmpl	$0,dst32lbit
	je	.L301
	movl	$32,%eax
	subl	dst32lbit,%eax
	movl	%eax,%ecx
	movl	$-1,%eax
	shll	%cl,%eax
	notl	%eax
	jmp	.L302
.L301:
	movl	$-1,%eax
.L302:
	movl	%eax,preloop_mask
	movl	$31,%eax
	subl	dst32rbit,%eax
	movl	%eax,%ecx
	movl	$-1,%eax
	shll	%cl,%eax
	movl	%eax,postloop_mask
	movl	preloop_mask,%eax
	andl	postloop_mask,%eax
	movl	%eax,sdw_mask
	movl	dst32lbit,%eax
	addl	w,%eax
	sarl	$5,%eax
	decl	%eax
	movl	%eax,dstnumL
.L300:
	movl	curr_gray_line,%eax
	incl	%eax
	movl	%eax,curr_gray_line
	cmpl	num_gray,%eax
	jl	.L303
	movl	$0,curr_gray_line
	movl	num_gray,%eax
	decl	%eax
	leal	(%eax,%eax),%eax
	subl	%eax,8(%ebp)
	jmp	.L45
.L303:
	addl	$2,8(%ebp)
	jmp	.L45
.L298:
	cmpl	$0,fwd
	je	.L305
	cmpl	$0,bbfast
	je	.L306
	movl	dstbpl,%eax
	sarl	$3,%eax
	addl	%eax,OrigDstAddr
	movl	OrigDstAddr,%edi
	jmp	.L307
.L306:
	movl	OrigDstAddr,%edi
	movl	dstbpl,%eax
	addl	%eax,dst32lbit
	movl	dst32lbit,%eax
	sarl	$5,%eax
/	movl	%eax,temp
/	shll	$2,temp
/	movl	temp,%eax
	shll	$2,%eax
	addl	%eax,%edi
	andl	$31,dst32lbit
	movl	dst32lbit,%eax
	addl	w,%eax
	decl	%eax
	andl	$31,%eax
	movl	%eax,dst32rbit
	movl	%edi,OrigDstAddr
	cmpl	$0,dst32lbit
	je	.L308
	movl	$32,%eax
	subl	dst32lbit,%eax
	movl	%eax,%ecx
	movl	$-1,%eax
	shll	%cl,%eax
	notl	%eax
	jmp	.L309
.L308:
	movl	$-1,%eax
.L309:
	movl	%eax,preloop_mask
	movl	$31,%eax
	subl	dst32rbit,%eax
	movl	%eax,%ecx
	movl	$-1,%eax
	shll	%cl,%eax
	movl	%eax,postloop_mask
	movl	preloop_mask,%eax
	andl	postloop_mask,%eax
	movl	%eax,sdw_mask
	movl	dst32lbit,%eax
	addl	w,%eax
	sarl	$5,%eax
	decl	%eax
	movl	%eax,dstnumL
.L307:
	cmpl	$0,bbfast
	jne	..15
	movl	OrigSrcAddr,%esi
	movl	srcbpl,%eax
	addl	%eax,src32lbit
	movl	src32lbit,%eax
	sarl	$5,%eax
/	movl	%eax,temp
/	shll	$2,temp
/	movl	temp,%eax
	shll	$2,%eax
	addl	%eax,%esi
	andl	$31,src32lbit
	movl	src32lbit,%eax
	addl	w,%eax
	decl	%eax
	andl	$31,%eax
	movl	%eax,src32rbit
	movl	%esi,OrigSrcAddr
	movl	dst32lbit,%eax
	subl	src32lbit,%eax
	andl	$31,%eax
	movl	%eax,srcRshift
	movl	src32lbit,%eax
	subl	dst32lbit,%eax
	andl	$31,%eax
	movl	%eax,src32Lshift
	cmpl	$0,src32Lshift
	je	.L312
	movl	src32Lshift,%ecx
	movl	$-1,%eax
	shll	%cl,%eax
	notl	%eax
	jmp	.L313
.L312:
	movl	$-1,%eax
.L313:
	movl	%eax,srcRmask
	jmp	.L321
.L305:
	cmpl	$0,bbfast
	je	.L314
	movl	dstbpl,%eax
	sarl	$3,%eax
	addl	%eax,OrigDstAddr
	movl	OrigDstAddr,%edi
	jmp	.L315
.L314:
	movl	OrigDstAddr,%edi
	movl	dstbpl,%eax
	addl	%eax,dst32rbit
	jge	.L316
	movl	$31,%eax
	subl	dst32rbit,%eax
	sarl	$5,%eax
/	movl	%eax,temp
/	shll	$2,temp
/	movl	temp,%eax
	shll	$2,%eax
	subl	%eax,%edi
	jmp	.L317
.L316:
	movl	dst32lbit,%eax
	sarl	$5,%eax
/	movl	%eax,temp
/	shll	$2,temp
/	movl	temp,%eax
	shll	$2,%eax
	addl	%eax,%edi
.L317:
	andl	$31,dst32rbit
	movl	dst32rbit,%eax
	subl	w,%eax
	incl	%eax
	andl	$31,%eax
	movl	%eax,dst32lbit
	movl	%edi,OrigDstAddr
	movl	$31,%eax
	subl	dst32rbit,%eax
	movl	%eax,%ecx
	movl	$-1,%eax
	shll	%cl,%eax
	movl	%eax,preloop_mask
	movl	$32,%eax
	subl	dst32lbit,%eax
	movl	%eax,%ecx
	movl	$-1,%eax
	shll	%cl,%eax
	notl	%eax
	movl	%eax,postloop_mask
	movl	preloop_mask,%eax
	andl	postloop_mask,%eax
	movl	%eax,sdw_mask
	movl	w,%eax
	subl	dst32rbit,%eax
	decl	%eax
	jle	.L318
	movl	w,%eax
	subl	dst32rbit,%eax
	decl	%eax
	sarl	$5,%eax
	jmp	.L319
.L318:
	xorl	%eax,%eax
.L319:
	movl	%eax,dstnumL
.L315:
	cmpl	$0,bbfast
	je	.L320
..15:
	movl	srcbpl,%eax
	sarl	$3,%eax
	addl	%eax,OrigSrcAddr
	movl	OrigSrcAddr,%esi
.L321:
.L36:
.L26:
.L45:
	movl	num_lines_remaining,%eax
	decl	num_lines_remaining
	testl	%eax,%eax
	jg	..16
/ASMQ
	movl	-120(%ebp),%ebx
	movl	-116(%ebp),%esi
	movl	-112(%ebp),%edi
/ASMEND0
	leave	
	ret	
.L320:
	movl	OrigSrcAddr,%esi
	movl	srcbpl,%eax
	addl	%eax,src32rbit
	jge	.L322
	movl	$31,%eax
	subl	src32rbit,%eax
	sarl	$5,%eax
/	movl	%eax,temp
	shll	$2,%eax
/	movl	temp,%eax
	subl	%eax,%esi
	jmp	.L323
.L322:
	movl	src32rbit,%eax
	sarl	$5,%eax
/	movl	%eax,temp
	shll	$2,%eax
/	movl	temp,%eax
	addl	%eax,%esi
.L323:
	andl	$31,src32rbit
	movl	src32rbit,%eax
	subl	w,%eax
	incl	%eax
	andl	$31,%eax
	movl	%eax,src32lbit
	movl	dst32lbit,%eax
	subl	src32lbit,%eax
	andl	$31,%eax
	movl	%eax,srcRshift
	movl	src32lbit,%eax
	subl	dst32lbit,%eax
	andl	$31,%eax
	movl	%eax,src32Lshift
	cmpl	$0,src32Lshift
	je	.L324
..4:
	movl	src32Lshift,%ecx
	movl	$-1,%eax
	shll	%cl,%eax
	notl	%eax
	jmp	.L35
.L324:
.L43:
	xorl	%eax,%eax
	jmp	.L325
/FUNCEND

        .data
	.text
