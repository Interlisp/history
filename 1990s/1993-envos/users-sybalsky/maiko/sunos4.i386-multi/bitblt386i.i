# 1 "../src/bitblt386i.s" 




































































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
	movl	28(%ebp),%eax
	movl	%eax,-4(%ebp)
	movl	40(%ebp),%eax
	notl	%eax
	movl	%eax,-68(%ebp)
	movl	32(%ebp),%eax
	orl	36(%ebp),%eax
	testl	$31,%eax
	jne	.L17
	movl	$1,%eax
	jmp	.L18
.L17:
	xorl	%eax,%eax
.L18:
	movl	%eax,-80(%ebp)
	cmpl	$0,52(%ebp)
	je	.L19
	movl	12(%ebp),%edx
	cmpl	$0,20(%ebp)
	jge	.L20
	movl	$7,%eax
	subl	20(%ebp),%eax
	sarl	$3,%eax
	subl	%eax,%edx
	jmp	..0
.L20:
	movl	20(%ebp),%eax
	sarl	$3,%eax
	addl	%eax,%edx
..0:
/	movl	%edx,-44(%ebp)
	movl	%edx,%eax
	andl	$3,%eax
	movl	%eax,-48(%ebp)
/	movl	-44(%ebp),%eax
/	subl	-48(%ebp),%eax
	subl	%eax,%edx
/	movl	%eax,-52(%ebp)
/	movl	%eax,%edi
	movl	%edx,%edi
/	movl	-48(%ebp),%eax
	leal	(,%eax,8),%eax
	movl	20(%ebp),%edx
	andl	$7,%edx
	addl	%edx,%eax
	movl	%eax,-24(%ebp)
	addl	24(%ebp),%eax
	decl	%eax
	andl	$31,%eax
	movl	%eax,-60(%ebp)
	movl	%edi,-76(%ebp)
	cmpl	$0,-24(%ebp)
	je	.L22
	movl	$32,%ecx
	subl	-24(%ebp),%ecx
/	movl	%eax,%ecx
	movl	$-1,%eax
	shll	%cl,%eax
	notl	%eax
	jmp	.L23
.L22:
	movl	$-1,%eax
.L23:
	movl	%eax,-84(%ebp)
	movl	$31,%edx
	subl	-60(%ebp),%edx
	movl	%edx,%ecx
	movl	$-1,%edx
	shll	%cl,%edx
	movl	%edx,-88(%ebp)
/	movl	-84(%ebp),%eax
/	andl	-88(%ebp),%eax
	andl	%edx,%eax
	movl	%eax,-92(%ebp)
	movl	-24(%ebp),%eax
	addl	24(%ebp),%eax
	sarl	$5,%eax
	decl	%eax
	movl	%eax,-12(%ebp)
	testl	$31,36(%ebp)
	jne	.L24
	movl	$1,%eax
	jmp	.L25
.L24:
	xorl	%eax,%eax
.L25:
	movl	%eax,-80(%ebp)
	movl	16(%ebp),%eax
	andl	$15,%eax
	movl	%eax,-16(%ebp)
	jmp	.L26
..16:
	cmpl	$0,52(%ebp)
	je	.L47
	movl	-16(%ebp),%eax
	subl	-24(%ebp),%eax
	andl	$15,%eax
	movl	%eax,-20(%ebp)
	movl	8(%ebp),%eax
	movzwl	(%eax),%eax
	movl	%eax,%ebx
	shll	$16,%eax
	orl	%eax,%ebx
	movl	-20(%ebp),%ecx
	shll	%cl,%ebx
	movl	%ebx,%eax
	shrl	$16,%eax
/	andl	$65535,%eax
	orl	%eax,%ebx
	cmpl	$0,44(%ebp)
	je	.L48
/	movl	%ebx,%eax
/	notl	%eax
	notl	%ebx
/	movl	%eax,%ebx
.L48:
	movl	-24(%ebp),%eax
	addl	24(%ebp),%eax
	cmpl	$32,%eax
	jle	..1
	movl	-84(%ebp),%eax
	movl	%eax,-40(%ebp)
	movl	(%edi),%eax
	movl	%eax,-36(%ebp)
	movl	-40(%ebp),%eax
	notl	%eax
	movl	-36(%ebp),%edx
	andl	%edx,%eax
	movl	%eax,-32(%ebp)
	movl	48(%ebp),%eax
/	cmpl	$3,%eax
/	ja	.L57
/	testl	%eax,%eax
/	jl	.L57
	jmp	*.L58(,%eax,4)
.L19:
	cmpl	$0,-68(%ebp)
	je	.L27
	cmpl	$0,20(%ebp)
	jge	.L28
	movl	$7,%eax
	subl	20(%ebp),%eax
	sarl	$3,%eax
	movl	12(%ebp),%edx
	subl	%eax,%edx
	jmp	..2
.L28:
	movl	20(%ebp),%eax
	sarl	$3,%eax
	movl	12(%ebp),%edx
	addl	%eax,%edx
..2:
/	movl	%edx,-44(%ebp)
	movl	%edx,%eax
	andl	$3,%eax
/	movl	%eax,-48(%ebp)
/	movl	-44(%ebp),%eax
/	subl	-48(%ebp),%eax
	subl	%eax,%edx
/	movl	%eax,-52(%ebp)
/	movl	%eax,%edi
	movl	%edx,%edi
/	movl	-48(%ebp),%eax
	leal	(,%eax,8),%eax
	movl	20(%ebp),%edx
	andl	$7,%edx
	addl	%edx,%eax
	movl	%eax,-24(%ebp)
	addl	24(%ebp),%eax
	decl	%eax
	andl	$31,%eax
	movl	%eax,-60(%ebp)
	movl	%edi,-76(%ebp)
	cmpl	$0,-24(%ebp)
	je	.L30
	movl	$32,%eax
	subl	-24(%ebp),%eax
	movl	%eax,%ecx
	movl	$-1,%eax
	shll	%cl,%eax
	notl	%eax
	jmp	.L31
.L30:
	movl	$-1,%eax
.L31:
	movl	%eax,-84(%ebp)
	movl	$31,%eax
	subl	-60(%ebp),%eax
	movl	%eax,%ecx
	movl	$-1,%eax
	shll	%cl,%eax
	movl	%eax,-88(%ebp)
	movl	-84(%ebp),%eax
	andl	-88(%ebp),%eax
	movl	%eax,-92(%ebp)
	movl	-24(%ebp),%eax
	addl	24(%ebp),%eax
	sarl	$5,%eax
	decl	%eax
	movl	%eax,-12(%ebp)
	cmpl	$0,16(%ebp)
	jge	.L32
	movl	$7,%eax
	subl	16(%ebp),%eax
	sarl	$3,%eax
	movl	8(%ebp),%edx
	subl	%eax,%edx
	jmp	..3
.L32:
	movl	16(%ebp),%eax
	sarl	$3,%eax
	movl	8(%ebp),%edx
	addl	%eax,%edx
..3:
/	movl	%edx,-44(%ebp)
	movl	%edx,%eax
	andl	$3,%eax
/	movl	%eax,-48(%ebp)
/	movl	-44(%ebp),%eax
/	subl	-48(%ebp),%eax
	subl	%eax,%edx
/	movl	%eax,-52(%ebp)
/	movl	%eax,%esi
	movl	%edx,%esi
/	movl	-48(%ebp),%eax
	leal	(,%eax,8),%eax
	movl	16(%ebp),%edx
	andl	$7,%edx
	addl	%edx,%eax
	movl	%eax,-16(%ebp)
	addl	24(%ebp),%eax
	decl	%eax
	andl	$31,%eax
	movl	%eax,-64(%ebp)
	movl	-24(%ebp),%eax
	subl	-16(%ebp),%eax
	andl	$31,%eax
	movl	%eax,-104(%ebp)
	movl	-16(%ebp),%eax
	subl	-24(%ebp),%eax
	andl	$31,%eax
	movl	%eax,-20(%ebp)
	cmpl	$0,-20(%ebp)
	jne	..4
	movl	$-1,%eax
.L325:
.L35:
	movl	%eax,-28(%ebp)
	movl	%esi,-72(%ebp)
	jmp	.L36
.L27:
	movl	20(%ebp),%eax
	addl	24(%ebp),%eax
	decl	%eax
	movl	%eax,-56(%ebp)
	cmpl	$0,-56(%ebp)
	jge	.L37
	movl	$7,%eax
	subl	-56(%ebp),%eax
	sarl	$3,%eax
	movl	12(%ebp),%edx
	subl	%eax,%edx
	jmp	..5
.L37:
	movl	-56(%ebp),%eax
	sarl	$3,%eax
	movl	12(%ebp),%edx
	addl	%eax,%edx
..5:
/	movl	%edx,-44(%ebp)
	movl	%edx,%eax
	andl	$3,%eax
/	movl	%eax,-48(%ebp)
/	movl	-44(%ebp),%eax
/	subl	-48(%ebp),%eax
	subl	%eax,%edx
/	movl	%eax,-52(%ebp)
/	movl	%eax,%edi
	movl	%edx,%edi
/	movl	-48(%ebp),%eax
	leal	(,%eax,8),%eax
	movl	-56(%ebp),%edx
	andl	$7,%edx
	addl	%edx,%eax
	movl	%eax,-60(%ebp)
	subl	24(%ebp),%eax
	incl	%eax
	andl	$31,%eax
	movl	%eax,-24(%ebp)
	movl	%edi,-76(%ebp)
	movl	$31,%eax
	subl	-60(%ebp),%eax
	movl	%eax,%ecx
	movl	$-1,%eax
	shll	%cl,%eax
	movl	%eax,-84(%ebp)
	movl	$32,%eax
	subl	-24(%ebp),%eax
	movl	%eax,%ecx
	movl	$-1,%eax
	shll	%cl,%eax
	notl	%eax
	movl	%eax,-88(%ebp)
	movl	-84(%ebp),%eax
	andl	-88(%ebp),%eax
	movl	%eax,-92(%ebp)
	movl	24(%ebp),%eax
	subl	-60(%ebp),%eax
	decl	%eax
	jle	.L39
	movl	24(%ebp),%eax
	subl	-60(%ebp),%eax
	decl	%eax
	sarl	$5,%eax
	jmp	.L40
.L39:
	xorl	%eax,%eax
.L40:
	movl	%eax,-12(%ebp)
	movl	16(%ebp),%eax
	addl	24(%ebp),%eax
	decl	%eax
	movl	%eax,-56(%ebp)
	cmpl	$0,-56(%ebp)
	jge	.L41
	movl	$7,%eax
	subl	-56(%ebp),%eax
	sarl	$3,%eax
	movl	8(%ebp),%edx
	subl	%eax,%edx
	jmp	..6
.L41:
	movl	-56(%ebp),%eax
	sarl	$3,%eax
	movl	8(%ebp),%edx
	addl	%eax,%edx
..6:
/	movl	%edx,-44(%ebp)
	movl	%edx,%eax
	andl	$3,%eax
/	movl	%eax,-48(%ebp)
/	movl	-44(%ebp),%eax
/	subl	-48(%ebp),%eax
	subl	%eax,%edx
/	movl	%eax,-52(%ebp)
/	movl	%eax,%esi
	movl	%edx,%esi
/	movl	-48(%ebp),%eax
	leal	(,%eax,8),%eax
	movl	-56(%ebp),%edx
	andl	$7,%edx
	addl	%edx,%eax
	movl	%eax,-64(%ebp)
	subl	24(%ebp),%eax
	incl	%eax
	andl	$31,%eax
	movl	%eax,-16(%ebp)
	movl	-24(%ebp),%eax
	subl	-16(%ebp),%eax
	andl	$31,%eax
	movl	%eax,-104(%ebp)
	movl	-16(%ebp),%eax
	subl	-24(%ebp),%eax
	andl	$31,%eax
	movl	%eax,-20(%ebp)
	cmpl	$0,-20(%ebp)
	je	.L43
	jmp	..4
.L53:				// -36(%ebp) is in %edx starting here.
	movl	%ebx,%edx
	jmp	.L51
.L54:
/	movl	%ebx,%eax
/	andl	%eax,-36(%ebp)
	andl	%ebx,%edx
	jmp	.L51
.L55:
/	movl	%ebx,%eax
/	orl	%eax,-36(%ebp)
	orl	%ebx,%edx
	jmp	.L51
.L56:
/	movl	%ebx,%eax
/	xorl	%eax,-36(%ebp)
	xorl	%ebx,%edx
.L57:
.L51:
/	movl	-40(%ebp),%eax
/	andl	%eax,%edx
	andl	-40(%ebp),%edx
/	movl	-32(%ebp),%eax
/	orl	%eax,-36(%ebp)
	orl	-32(%ebp),%edx
/	movl	-36(%ebp),%eax
/	movl	%eax,(%edi) 
	movl	%edx,(%edi)	// end of -36(%ebp) in %edx
	movl	48(%ebp),%eax
	addl	$4,%edi
/	cmpl	$3,%eax
/	ja	.L77
/	testl	%eax,%eax
/	jl	.L77
	movl	-12(%ebp),%ecx	// -108(%ebp) is in %ecx from here down
	inc	%ecx
	jmp	*.L78(,%eax,4)
/.L61:
/	movl	-12(%ebp),%eax
/	movl	%eax,-108(%ebp)
.L64:
/	decl	-108(%ebp)
/	jl	.L63
	movl	%ebx,(%edi)
	addl	$4,%edi
.L61:	loop	.L64
	jmp	.L63
/	jmp	.L64
/.L65:
/	movl	-12(%ebp),%eax
/	movl	%eax,-108(%ebp)
.L68:
/	decl	-108(%ebp)
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
/	movl	-12(%ebp),%eax
/	movl	%eax,-108(%ebp)
/	jmp	.L72
..7:
/	movl	%edi,%eax
/	movl	%ebx,%edx
	orl	%ebx,(%edi)
	addl	$4,%edi
/	orl	%edx,(%eax)
.L72:
.L69:
/	decl	-108(%ebp)
/	jge	..7
	loop	..7
	jmp	.L75
/.L73:
/	movl	-12(%ebp),%eax
/	movl	%eax,-108(%ebp)
/	jmp	.L76
..8:
/	movl	%edi,%eax
/	movl	%ebx,%edx
	xorl	%ebx,(%edi)
	addl	$4,%edi
/	xorl	%edx,(%eax)
.L76:
/	decl	-108(%ebp)
/	jge	..8
.L73:	loop	..8
.L75:
.L67:
.L63:
.L77:
	cmpl	$31,-60(%ebp)
	je	.L79
.L289:
.L185:
	movl	-88(%ebp),%eax
..11:
	movl	%eax,-40(%ebp)
	movl	(%edi),%edx	// -36(%ebp) is in %edx from here down.
/	movl	%eax,-36(%ebp)
/	movl	-40(%ebp),%eax
	notl	%eax
/	movl	-36(%ebp),%edx
/	andl	%eax,%edx
	andl	%edx,%eax
	movl	%eax,-32(%ebp)
	movl	48(%ebp),%eax
/	cmpl	$3,%eax
/	ja	.L296
/	testl	%eax,%eax
/	jl	.L296
	jmp	*.L297(,%eax,4)
.L47:
	cmpl	$0,-68(%ebp)
	je	.L81
	movl	-24(%ebp),%eax
	cmpl	%eax,-16(%ebp)
	jle	.L82
	movl	-16(%ebp),%eax
	addl	24(%ebp),%eax
	cmpl	$32,%eax
	jle	.L82
	movl	(%esi),%edx
	movl	%edx,-100(%ebp)
	movl	-20(%ebp),%ecx
	movl	-100(%ebp),%eax
	addl	$4,%esi
	shll	%cl,%eax
	movl	%eax,-96(%ebp)
	movl	(%esi),%edx
	movl	%edx,-100(%ebp)
	movl	-104(%ebp),%ecx
	movl	-100(%ebp),%eax
	addl	$4,%esi
	shrl	%cl,%eax
	andl	-28(%ebp),%eax
	orl	-96(%ebp),%eax
	movl	%eax,%ebx
	movl	-20(%ebp),%ecx
	movl	-100(%ebp),%eax
	shll	%cl,%eax
	movl	-28(%ebp),%edx
	notl	%edx
	andl	%edx,%eax
	movl	%eax,-96(%ebp)
	jmp	.L83
.L82:
	movl	-24(%ebp),%eax
	cmpl	%eax,-16(%ebp)
	jg	.L84
	movl	(%esi),%edx
	movl	%edx,-100(%ebp)
	movl	-104(%ebp),%ecx
	movl	-100(%ebp),%eax
	addl	$4,%esi
	shrl	%cl,%eax
	andl	-28(%ebp),%eax
	movl	%eax,%ebx
	movl	-20(%ebp),%ecx
	movl	-100(%ebp),%eax
	shll	%cl,%eax
	movl	-28(%ebp),%edx
	notl	%edx
	andl	%edx,%eax
	movl	%eax,-96(%ebp)
	jmp	.L85
.L84:
	movl	(%esi),%edx
	movl	%edx,-100(%ebp)
	movl	-20(%ebp),%ecx
	movl	-100(%ebp),%eax
	addl	$4,%esi
	shll	%cl,%eax
	movl	%eax,%ebx
.L85:
.L83:
	cmpl	$0,44(%ebp)
	je	.L86
/	movl	%ebx,%eax
/	notl	%eax
/	movl	%eax,%ebx
	notl	%ebx		//inserted
.L86:
	movl	-24(%ebp),%eax
	addl	24(%ebp),%eax
	cmpl	$32,%eax
	jle	..1
	movl	-84(%ebp),%eax
	movl	%eax,-40(%ebp)
	movl	(%edi),%eax
	movl	%eax,-36(%ebp)
	movl	-40(%ebp),%eax
	notl	%eax
	movl	-36(%ebp),%edx
	andl	%eax,%edx
	movl	%edx,-32(%ebp)
	movl	48(%ebp),%eax
/	cmpl	$3,%eax
/	ja	.L94
/	testl	%eax,%eax
/	jl	.L94
	jmp	*.L95(,%eax,4)
.L90:
	movl	%ebx,-36(%ebp)
	jmp	.L88
.L91:
/	movl	%ebx,%eax
	andl	%ebx,-36(%ebp)
	jmp	.L88
.L92:
/	movl	%ebx,%eax
	orl	%ebx,-36(%ebp)
	jmp	.L88
.L93:
/	movl	%ebx,%eax
	xorl	%ebx,-36(%ebp)
.L94:
.L88:
	movl	-40(%ebp),%edx	/ -36(%ebp) is in %edx from here down
/	andl	%eax,-36(%ebp)
/	movl	-32(%ebp),%eax
/	orl	%eax,-36(%ebp)
/	movl	-36(%ebp),%eax
	andl	-36(%ebp),%edx
	orl	-32(%ebp),%edx
	movl	%edx,-36(%ebp)
	movl	%edx,(%edi)
	movl	-24(%ebp),%eax
	addl	$4,%edi
	cmpl	%eax,-16(%ebp)
	jne	.L96
	cmpl	$0,44(%ebp)
	jne	.L99
	movl	48(%ebp),%eax
/	cmpl	$3,%eax
/	ja	.L137
/	testl	%eax,%eax
/	jl	.L137
	movl	-12(%ebp),%ecx
	incl	%ecx
	jmp	*.L138(,%eax,4)
.L99:
	movl	48(%ebp),%eax
/	cmpl	$3,%eax
/	ja	.L116
/	testl	%eax,%eax
/	jl	.L116
	movl	-12(%ebp),%ecx
	incl	%ecx
	jmp	*.L117(,%eax,4)
/.L100:
/	movl	-12(%ebp),%ecx
/	movl	%eax,-108(%ebp)
.L103:
/	decl	-108(%ebp)
/	jl	.L102
/	movl	%edi,%eax
/	movl	(%esi),%edx
/	addl	$4,%edi
/	addl	$4,%esi
/	notl	%edx
/	movl	%edx,(%eax)
	lodsl
	notl	%eax
	stosl
.L100:
	loop	.L103
	jmp	.L102
/	jmp	.L103
/.L104:
/	movl	-12(%ebp),%ecx
/	movl	%eax,-108(%ebp)
.L107:
/	decl	-108(%ebp)
/	jl	.L106
/	movl	%edi,%eax
/	movl	(%esi),%edx
	lodsl
	notl	%eax
	andl	%eax,(%edi)
	addl	$4,%edi
/	addl	$4,%esi
/	notl	%edx
/	andl	%edx,(%eax)
.L104:
	loop	.L107
	jmp	.L106
/	jmp	.L107
/.L108:
/	movl	-12(%ebp),%ecx
/	movl	%eax,-108(%ebp)
.L111:
/	decl	-108(%ebp)
/	jl	.L110
/	movl	%edi,%eax
/	movl	(%esi),%edx
	lodsl
	notl	%eax
	orl	%eax,(%edi)
	addl	$4,%edi
/	addl	$4,%esi
/	notl	%edx
/	orl	%edx,(%eax)
.L108:
	loop	.L111
	jmp	.L110
/	jmp	.L111
/.L112:
/	movl	-12(%ebp),%ecx
/	movl	%eax,-108(%ebp)
.L115:
/	decl	-108(%ebp)
/	jl	.L114
/	movl	%edi,%eax
/	movl	(%esi),%edx
	lodsl
	notl	%eax
	xorl	%eax,(%edi)
	addl	$4,%edi
/	addl	$4,%esi
/	notl	%edx
/	xorl	%edx,(%eax)
.L112:
	loop	.L115
	jmp	.L114
/	jmp	.L115


/.L121:
/	movl	-12(%ebp),%eax
/	movl	%eax,-108(%ebp)
.L124:
/	decl	-108(%ebp)
/	jl	.L123
/	movl	%edi,%eax
/	movl	%esi,%edx
/	movl	(%edx),%ecx
/	movl	%ecx,(%eax)
/	addl	$4,%edi
/	addl	$4,%esi
	lodsl
	stosl
.L121:
	loop	.L124
	jmp	.L123
/	jmp	.L124

/.L125:
/	movl	-12(%ebp),%eax
/	movl	%eax,-108(%ebp)
.L128:
/	decl	-108(%ebp)
/	jl	.L127
/	movl	%edi,%eax
/	movl	(%esi),%edx
	lodsl
	andl	%eax,(%edi)
	addl	$4,%edi
/	addl	$4,%esi
/	andl	%edx,(%eax)
.L125:
	loop	.L128
	jmp	.L127
/	jmp	.L128

/.L129:
/	movl	-12(%ebp),%eax
/	movl	%eax,-108(%ebp)
.L132:
/	decl	-108(%ebp)
/	jl	.L131
/	movl	%edi,%eax
/	movl	(%esi),%edx
	lodsl
	orl	%eax,(%edi)
	addl	$4,%edi
/	addl	$4,%esi
/	orl	%edx,(%eax)
.L129:
	loop	.L132
	jmp	.L131
/	jmp	.L132

/.L133:
/	movl	-12(%ebp),%eax
/	movl	%eax,-108(%ebp)
.L136:
/	decl	-108(%ebp)
/	jl	.L135
/	movl	%edi,%eax
/	movl	(%esi),%edx
	lodsl
	xorl	%eax,(%edi)
	addl	$4,%edi
/	addl	$4,%esi
/	xorl	%edx,(%eax)
.L133:
	loop	.L136
	jmp	.L135
/	jmp	.L136


.L96:
	movl	-12(%ebp),%ebx
	movl	-104(%ebp),%ecx
	movb	-20(%ebp),%ch
	cmpl	$0,44(%ebp)
	jne	.L142
	movl	48(%ebp),%eax
/	cmpl	$3,%eax
/	ja	.L180
/	testl	%eax,%eax
/	jl	.L180
	jmp	*.L181(,%eax,4)
.L142:
	incl	%ebx
	movl	48(%ebp),%eax
/	cmpl	$3,%eax
/	ja	.L159
/	testl	%eax,%eax
/	jl	.L159
	jmp	*.L160(,%eax,4)
/.L143:
/	movl	-12(%ebp),%eax
/	movl	%eax,-108(%ebp)
.L146:
/	decl	-108(%ebp)
/	jl	.L145
/	movl	(%esi),%edx
/	movl	%edx,-100(%ebp)
	lodsl			/ -100(%ebp) in edx from here down.
/	movl	-104(%ebp),%ecx
/	movl	-100(%ebp),%eax
/	addl	$4,%esi
	movl	%eax,%edx
	shrl	%cl,%eax
/	movl	-96(%ebp),%edx
/	orl	%eax,%edx
	orl	-96(%ebp),%eax
/	movl	%edx,%eax
	notl	%eax
/	movl	%eax,%ebx
/	movl	-20(%ebp),%ecx
/	movl	-100(%ebp),%eax
	xchgb	%cl,%ch
	shll	%cl,%edx
	xchgb	%cl,%ch
	movl	%edx,-96(%ebp)
/	movl	%edx,(%edi)
/	addl	$4,%edi
	stosl
.L143:
	decl	%ebx
	jg	.L146
	jmp	.L145
/	jmp	.L146


/.L147:
/	movl	-12(%ebp),%eax
/	movl	%eax,-108(%ebp)
.L150:
/	decl	-108(%ebp)
/	jl	.L149
/	movl	(%esi),%edx
/	movl	%edx,-100(%ebp)
/	movl	-104(%ebp),%ecx
/	movl	-100(%ebp),%eax
/	addl	$4,%esi
	lodsl
	movl	%eax,%edx
	shrl	%cl,%eax
	orl	-96(%ebp),%eax
	notl	%eax
/	movl	%eax,%ebx
/	movl	-20(%ebp),%ecx
/	movl	-100(%ebp),%eax
	xchgb	%cl,%ch
	shll	%cl,%edx
	xchgb	%cl,%ch
	movl	%edx,-96(%ebp)
/	movl	%edi,%eax
/	movl	%ebx,%edx
/	addl	$4,%edi
	andl	%eax,(%edi)
	addl	$4,%edi
.L147:
	decl	%ebx
	jg	.L150
	jmp	.L149
/	jmp	.L150


/.L151:
/	movl	-12(%ebp),%eax
/	movl	%eax,-108(%ebp)
.L154:
/	decl	-108(%ebp)
/	jl	.L153
/	movl	(%esi),%edx
/	movl	%edx,-100(%ebp)
/	movl	-104(%ebp),%ecx
/	movl	-100(%ebp),%eax
/	addl	$4,%esi
	lodsl
	movl	%eax,%edx
	shrl	%cl,%eax
	orl	-96(%ebp),%eax
	notl	%eax
/	movl	%eax,%ebx
/	movl	-20(%ebp),%ecx
/	movl	-100(%ebp),%eax
	xchgb	%cl,%ch
	shll	%cl,%edx
	xchgb	%cl,%ch
	movl	%edx,-96(%ebp)
/	movl	%edi,%eax
/	movl	%ebx,%edx
/	addl	$4,%edi
	orl	%eax,(%edi)
	addl	$4,%edi
.L151:
	decl	%ebx
	jg	.L154
	jmp	.L153
	jmp	.L154


/.L155:
/	movl	-12(%ebp),%eax
/	movl	%eax,-108(%ebp)
.L158:
/	decl	-108(%ebp)
/	jl	.L157
/	movl	(%esi),%edx
/	movl	%edx,-100(%ebp)
/	movl	-104(%ebp),%ecx
/	movl	-100(%ebp),%eax
/	addl	$4,%esi
	lodsl
	movl	%eax,%edx
	shrl	%cl,%eax
	orl	-96(%ebp),%eax
	notl	%eax
/	movl	%eax,%ebx
/	movl	-20(%ebp),%ecx
/	movl	-100(%ebp),%eax
	xchgb	%cl,%ch
	shll	%cl,%edx
	xchgb	%cl,%ch
	movl	%edx,-96(%ebp)
/	movl	%edi,%eax
/	movl	%ebx,%edx
/	addl	$4,%edi
	xorl	%eax,(%edi)
	addl	$4,%edi
.L155:
	decl	%ebx
	jg	.L158
	jmp	.L157
/	jmp	.L158


.L164:
/	movl	-12(%ebp),%eax
/	movl	%eax,-108(%ebp)
.L167:
	decl	%ebx
	jl	.L166
/	movl	(%esi),%edx
/	movl	%edx,-100(%ebp)
	lodsl
/	movl	-104(%ebp),%ecx
/	movl	-100(%ebp),%eax
/	addl	$4,%esi
	movl	%eax,%edx
	shrl	%cl,%eax
/	movl	-96(%ebp),%edx
/	orl	%eax,%edx
	orl	-96(%ebp),%eax
/	movl	%edx,%ebx
/	movl	-20(%ebp),%ecx
/	movl	-100(%ebp),%eax
	xchgb	%cl,%ch
	shll	%cl,%edx
	xchgb	%cl,%ch
	movl	%edx,-96(%ebp)
/	movl	%ebx,(%edi)
/	addl	$4,%edi
	stosl
	jmp	.L167


.L168:
/	movl	-12(%ebp),%eax
/	movl	%eax,-108(%ebp)
.L171:
	decl	%ebx
	jl	.L170
/	movl	(%esi),%edx
/	movl	%edx,-100(%ebp)
/	movl	-104(%ebp),%ecx
/	movl	-100(%ebp),%eax
/	addl	$4,%esi
	lodsl
	movl	%eax,%edx
	shrl	%cl,%eax
	orl	-96(%ebp),%eax
/	movl	%eax,%ebx
/	movl	-20(%ebp),%ecx
/	movl	-100(%ebp),%eax
	xchgb	%cl,%ch
	shll	%cl,%edx
	xchgb	%cl,%ch
	movl	%edx,-96(%ebp)
/	movl	%edi,%eax
/	movl	%ebx,%edx
	andl	%eax,(%edi)
	addl	$4,%edi
/	andl	%edx,(%edi)
	jmp	.L171
.L172:
	movl	-12(%ebp),%eax
	movl	%eax,-108(%ebp)
	jmp	.L175
..9:
/	movl	(%esi),%edx
/	movl	%edx,-100(%ebp)
/	movl	-104(%ebp),%ecx
/	movl	-100(%ebp),%eax
/	addl	$4,%esi
	lodsl
	movl	%eax,%edx
	shrl	%cl,%eax
	orl	-96(%ebp),%eax
/	movl	%eax,%ebx
/	movl	-20(%ebp),%ecx
/	movl	-100(%ebp),%eax
	xchgb	%cl,%ch
	shll	%cl,%edx
	xchgb	%cl,%ch
	movl	%edx,-96(%ebp)
/	movl	%edi,%eax
/	movl	%ebx,%edx
	orl	%eax,(%edi)
	addl	$4,%edi
.L175:
	decl	-108(%ebp)
	jge	..9
	jmp	.L178
/.L176:
/	movl	-12(%ebp),%eax
/	movl	%eax,-108(%ebp)
/	jmp	.L179
..10:
/	movl	(%esi),%edx
/	movl	%edx,-100(%ebp)
/	movl	-104(%ebp),%ecx
/	movl	-100(%ebp),%eax
/	addl	$4,%esi
	lodsl
	movl	%eax,%edx
	shrl	%cl,%eax
	orl	-96(%ebp),%eax
/	movl	%eax,%ebx
/	movl	-20(%ebp),%ecx
/	movl	-100(%ebp),%eax
	xchgb	%cl,%ch
	shll	%cl,%edx
	xchgb	%cl,%ch
	movl	%edx,-96(%ebp)
/	movl	%edi,%eax
/	movl	%ebx,%edx
	xorl	%eax,(%edi)
	addl	$4,%edi
.L176:
.L179:
	decl	%ebx
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
	cmpl	$31,-60(%ebp)
	je	.L182
	movl	-60(%ebp),%eax
	cmpl	%eax,-64(%ebp)
	jg	.L183
	movl	(%esi),%eax
	movl	%eax,-100(%ebp)
	movl	-104(%ebp),%ecx
	movl	-100(%ebp),%eax
	shrl	%cl,%eax
	andl	-28(%ebp),%eax
	orl	-96(%ebp),%eax
	movl	%eax,%ebx
	jmp	.L184
..14:
	movl	-24(%ebp),%eax
	cmpl	%eax,-16(%ebp)
	jl	.L287
	movl	(%esi),%eax
	movl	%eax,-100(%ebp)
	movl	-20(%ebp),%ecx
/	movl	-100(%ebp),%eax
	shll	%cl,%eax
	orl	-96(%ebp),%eax
	movl	%eax,%ebx
	jmp	.L288
.L287:
.L183:
	movl	-96(%ebp),%ebx
.L288:
.L184:
	cmpl	$0,44(%ebp)
	je	.L185
/	movl	%ebx,%eax
/	notl	%eax
/	movl	%eax,%ebx
	notl	%ebx
	jmp	.L289

.L81:
	movl	-60(%ebp),%eax
	cmpl	%eax,-64(%ebp)
	jge	.L186
	movl	-16(%ebp),%eax
	addl	24(%ebp),%eax
	movl	-24(%ebp),%edx
	incl	%edx
	cmpl	%edx,%eax
	jle	.L186
	movl	%esi,%eax
	subl	$4,%esi
	movl	(%eax),%edx
	movl	%edx,-100(%ebp)
	movl	-104(%ebp),%ecx
	movl	-100(%ebp),%eax
	shrl	%cl,%eax
	andl	-28(%ebp),%eax
	movl	%eax,-96(%ebp)
	movl	%esi,%eax
	subl	$4,%esi
	movl	(%eax),%edx
	movl	%edx,-100(%ebp)
	movl	-20(%ebp),%ecx
	movl	-100(%ebp),%eax
	shll	%cl,%eax
	orl	-96(%ebp),%eax
	movl	%eax,%ebx
	movl	-104(%ebp),%ecx
	movl	-100(%ebp),%eax
	shrl	%cl,%eax
	andl	-28(%ebp),%eax
	movl	%eax,-96(%ebp)
	jmp	.L187
.L186:
	movl	-60(%ebp),%eax
	cmpl	%eax,-64(%ebp)
	jl	.L188
	movl	%esi,%eax
	subl	$4,%esi
	movl	(%eax),%edx
	movl	%edx,-100(%ebp)
	movl	-20(%ebp),%ecx
	movl	-100(%ebp),%eax
	shll	%cl,%eax
	movl	%eax,%ebx
	movl	-104(%ebp),%ecx
	movl	-100(%ebp),%eax
	shrl	%cl,%eax
	andl	-28(%ebp),%eax
	movl	%eax,-96(%ebp)
	jmp	.L189
.L188:
	movl	%esi,%eax
	subl	$4,%esi
	movl	(%eax),%edx
	movl	%edx,-100(%ebp)
	movl	-104(%ebp),%ecx
	movl	-100(%ebp),%ebx
	shrl	%cl,%ebx
	andl	-28(%ebp),%ebx
/	movl	%eax,%ebx
.L189:
.L187:
	cmpl	$0,44(%ebp)
	je	.L190
/	movl	%ebx,%eax
/	notl	%eax
/	movl	%eax,%ebx
	notl	%ebx
.L190:
	movl	-24(%ebp),%eax
	addl	24(%ebp),%eax
	cmpl	$32,%eax
	jg	.L191
..1:
	movl	-92(%ebp),%eax
	jmp	..11
.L191:
	movl	-84(%ebp),%eax
	movl	%eax,-40(%ebp)
	movl	(%edi),%eax
	movl	%eax,-36(%ebp)
	movl	-40(%ebp),%eax
	notl	%eax
	movl	-36(%ebp),%edx
	andl	%eax,%edx
	movl	%edx,-32(%ebp)
	movl	48(%ebp),%eax
/	cmpl	$3,%eax
/	ja	.L198
/	testl	%eax,%eax
/	jl	.L198
	jmp	*.L199(,%eax,4)
.L194:
	movl	%ebx,-36(%ebp)
	jmp	.L192
.L195:
	movl	%ebx,%eax
	andl	%eax,-36(%ebp)
	jmp	.L192
.L196:
	movl	%ebx,%eax
	orl	%eax,-36(%ebp)
	jmp	.L192
.L197:
/	movl	%ebx,%eax
	xorl	%ebx,-36(%ebp)
.L198:
.L192:
	movl	-40(%ebp),%eax
	andl	%eax,-36(%ebp)
	movl	-32(%ebp),%eax
	orl	%eax,-36(%ebp)
	movl	-36(%ebp),%eax
	movl	%eax,(%edi)
	subl	$4,%edi
	movl	-24(%ebp),%eax
	cmpl	%eax,-16(%ebp)
	jne	.L200
	cmpl	$0,44(%ebp)
	jne	.L203
	movl	48(%ebp),%eax
/	cmpl	$3,%eax
/	ja	.L241
/	testl	%eax,%eax
/	jl	.L241
	movl	-12(%ebp),%ebx
	jmp	*.L242(,%eax,4)
.L203:
	movl	48(%ebp),%eax
/	cmpl	$3,%eax
/	ja	.L220
/	testl	%eax,%eax
/	jl	.L220
	movl	-12(%ebp),%ebx
	jmp	*.L221(,%eax,4)
.L204:
/	movl	-12(%ebp),%eax
/	movl	%eax,-108(%ebp)
.L207:
	decl	%ebx
	jl	.L206
/	movl	%edi,%eax
/	subl	$4,%edi
/	movl	%esi,%edx
/	subl	$4,%esi
	movl	(%esi),%edx
	notl	%edx
	movl	%edx,(%edi)
	subl	$4,%edi
	subl	$4,%esi
	jmp	.L207
.L208:
/	movl	-12(%ebp),%eax
/	movl	%eax,-108(%ebp)
.L211:
	decl	%ebx
	jl	.L210
/	movl	%edi,%eax
/	subl	$4,%edi
/	movl	%esi,%edx
/	subl	$4,%esi
	movl	(%esi),%edx
	notl	%edx
	andl	%edx,(%edi)
	subl	$4,%edi
	subl	$4,%esi
	jmp	.L211
.L212:
/	movl	-12(%ebp),%eax
/	movl	%eax,-108(%ebp)
.L215:
	decl	%ebx
	jl	.L214
/	movl	%edi,%eax
/	subl	$4,%edi
/	movl	%esi,%edx
/	subl	$4,%esi
	movl	(%esi),%edx
	notl	%edx
	orl	%edx,(%edi)
	subl	$4,%edi
	subl	$4,%esi
	jmp	.L215
.L216:
/	movl	-12(%ebp),%eax
/	movl	%eax,-108(%ebp)
.L219:
	decl	%ebx
	jl	.L218
/	movl	%edi,%eax
/	subl	$4,%edi
/	movl	%esi,%edx
/	subl	$4,%esi
	movl	(%esi),%edx
	notl	%edx
	xorl	%edx,(%edi)
	subl	$4,%edi
	subl	$4,%esi
	jmp	.L219

.L225:
/	movl	-12(%ebp),%eax
/	movl	%eax,-108(%ebp)
.L228:
	decl	%ebx
	jl	.L227
/	movl	%edi,%eax
/	subl	$4,%edi
/	movl	%esi,%edx
/	subl	$4,%esi
	movl	(%esi),%ecx
	movl	%ecx,(%edi)
	subl	$4,%edi
	subl	$4,%esi
	jmp	.L228
.L229:
/	movl	-12(%ebp),%eax
/	movl	%eax,-108(%ebp)
.L232:
	decl	%ebx
	jl	.L231
/	movl	%edi,%eax
/	subl	$4,%edi
/	movl	%esi,%edx
/	subl	$4,%esi
	movl	(%esi),%edx
	andl	%edx,(%edi)
	subl	$4,%edi
	subl	$4,%esi
	jmp	.L232
.L233:
/	movl	-12(%ebp),%eax
/	movl	%eax,-108(%ebp)
.L236:
	decl	%ebx
	jl	.L235
/	movl	%edi,%eax
/	subl	$4,%edi
/	movl	%esi,%edx
/	subl	$4,%esi
	movl	(%esi),%edx
	orl	%edx,(%edi)
	subl	$4,%edi
	subl	$4,%esi
	jmp	.L236
.L237:
/	movl	-12(%ebp),%eax
/	movl	%eax,-108(%ebp)
.L240:
	decl	%ebx
	jl	.L239
/	movl	%edi,%eax
/	subl	$4,%edi
/	movl	%esi,%edx
/	subl	$4,%esi
	movl	(%esi),%edx
	xorl	%edx,(%edi)
	subl	$4,%edi
	subl	$4,%esi
	jmp	.L240
.L200:
	cmpl	$0,44(%ebp)
	jne	.L246
	movl	48(%ebp),%eax
/	cmpl	$3,%eax
/	ja	.L284
/	testl	%eax,%eax
/	jl	.L284
	jmp	*.L285(,%eax,4)
.L246:
	movl	48(%ebp),%eax
/	cmpl	$3,%eax
/	ja	.L263
/	testl	%eax,%eax
/	jl	.L263
	jmp	*.L264(,%eax,4)
.L247:
	movl	-12(%ebp),%eax
	movl	%eax,-108(%ebp)
.L250:
	decl	-108(%ebp)
	jl	.L249
	movl	%esi,%eax
	subl	$4,%esi
	movl	(%eax),%edx
	movl	%edx,-100(%ebp)
	movl	-20(%ebp),%ecx
	movl	-100(%ebp),%eax
	shll	%cl,%eax
	movl	-96(%ebp),%edx
	orl	%eax,%edx
	movl	%edx,%eax
	notl	%eax
	movl	%eax,%ebx
	movl	-104(%ebp),%ecx
	movl	-100(%ebp),%eax
	shrl	%cl,%eax
	movl	%eax,-96(%ebp)
	movl	%edi,%eax
	subl	$4,%edi
	movl	%ebx,(%eax)
	jmp	.L250
.L251:
	movl	-12(%ebp),%eax
	movl	%eax,-108(%ebp)
.L254:
	decl	-108(%ebp)
	jl	.L253
	movl	%esi,%eax
	subl	$4,%esi
	movl	(%eax),%edx
	movl	%edx,-100(%ebp)
	movl	-20(%ebp),%ecx
	movl	-100(%ebp),%eax
	shll	%cl,%eax
	orl	-96(%ebp),%eax
	notl	%eax
	movl	%eax,%ebx
	movl	-104(%ebp),%ecx
	movl	-100(%ebp),%eax
	shrl	%cl,%eax
	movl	%eax,-96(%ebp)
	movl	%edi,%eax
	subl	$4,%edi
	movl	%ebx,%edx
	andl	%edx,(%eax)
	jmp	.L254
.L255:
	movl	-12(%ebp),%eax
	movl	%eax,-108(%ebp)
.L258:
	decl	-108(%ebp)
	jl	.L257
	movl	%esi,%eax
	subl	$4,%esi
	movl	(%eax),%edx
	movl	%edx,-100(%ebp)
	movl	-20(%ebp),%ecx
	movl	-100(%ebp),%eax
	shll	%cl,%eax
	orl	-96(%ebp),%eax
	notl	%eax
	movl	%eax,%ebx
	movl	-104(%ebp),%ecx
	movl	-100(%ebp),%eax
	shrl	%cl,%eax
	movl	%eax,-96(%ebp)
	movl	%edi,%eax
	subl	$4,%edi
	movl	%ebx,%edx
	orl	%edx,(%eax)
	jmp	.L258
.L259:
	movl	-12(%ebp),%eax
	movl	%eax,-108(%ebp)
.L262:
	decl	-108(%ebp)
	jl	.L261
	movl	%esi,%eax
	subl	$4,%esi
	movl	(%eax),%edx
	movl	%edx,-100(%ebp)
	movl	-20(%ebp),%ecx
	movl	-100(%ebp),%eax
	shll	%cl,%eax
	orl	-96(%ebp),%eax
	notl	%eax
	movl	%eax,%ebx
	movl	-104(%ebp),%ecx
	movl	-100(%ebp),%eax
	shrl	%cl,%eax
	movl	%eax,-96(%ebp)
	movl	%edi,%eax
	subl	$4,%edi
	movl	%ebx,%edx
	xorl	%edx,(%eax)
	jmp	.L262
.L268:
	movl	-12(%ebp),%eax
	movl	%eax,-108(%ebp)
.L271:
	decl	-108(%ebp)
	jl	.L270
	movl	%esi,%eax
	subl	$4,%esi
	movl	(%eax),%edx
	movl	%edx,-100(%ebp)
	movl	-20(%ebp),%ecx
	movl	-100(%ebp),%eax
	shll	%cl,%eax
	movl	-96(%ebp),%edx
	orl	%eax,%edx
	movl	%edx,%ebx
	movl	-104(%ebp),%ecx
	movl	-100(%ebp),%eax
	shrl	%cl,%eax
	movl	%eax,-96(%ebp)
	movl	%edi,%eax
	subl	$4,%edi
	movl	%ebx,(%eax)
	jmp	.L271
.L272:
	movl	-12(%ebp),%eax
	movl	%eax,-108(%ebp)
.L275:
	decl	-108(%ebp)
	jl	.L274
	movl	%esi,%eax
	subl	$4,%esi
	movl	(%eax),%edx
	movl	%edx,-100(%ebp)
	movl	-20(%ebp),%ecx
	movl	-100(%ebp),%eax
	shll	%cl,%eax
	orl	-96(%ebp),%eax
	movl	%eax,%ebx
	movl	-104(%ebp),%ecx
	movl	-100(%ebp),%eax
	shrl	%cl,%eax
	movl	%eax,-96(%ebp)
	movl	%edi,%eax
	subl	$4,%edi
	movl	%ebx,%edx
	andl	%edx,(%eax)
	jmp	.L275
.L276:
	movl	-12(%ebp),%eax
	movl	%eax,-108(%ebp)
	jmp	.L279
..12:
	movl	%esi,%eax
	subl	$4,%esi
	movl	(%eax),%edx
	movl	%edx,-100(%ebp)
	movl	-20(%ebp),%ecx
	movl	-100(%ebp),%eax
	shll	%cl,%eax
	orl	-96(%ebp),%eax
	movl	%eax,%ebx
	movl	-104(%ebp),%ecx
	movl	-100(%ebp),%eax
	shrl	%cl,%eax
	movl	%eax,-96(%ebp)
	movl	%edi,%eax
	subl	$4,%edi
	movl	%ebx,%edx
	orl	%edx,(%eax)
.L279:
	decl	-108(%ebp)
	jge	..12
	jmp	.L282
.L280:
	movl	-12(%ebp),%eax
	movl	%eax,-108(%ebp)
	jmp	.L283
..13:
	movl	%esi,%eax
	subl	$4,%esi
	movl	(%eax),%edx
	movl	%edx,-100(%ebp)
	movl	-20(%ebp),%ecx
	movl	-100(%ebp),%eax
	shll	%cl,%eax
	orl	-96(%ebp),%eax
	movl	%eax,%ebx
	movl	-104(%ebp),%ecx
	movl	-100(%ebp),%eax
	shrl	%cl,%eax
	movl	%eax,-96(%ebp)
	movl	%edi,%eax
	subl	$4,%edi
	movl	%ebx,%edx
	xorl	%edx,(%eax)
.L283:
	decl	-108(%ebp)
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
	cmpl	$0,-24(%ebp)
	jne	..14
	jmp	.L286
.L292:				// -36(%ebp) is in %edx from here down
/	movl	%ebx,-36(%ebp)
	movl	%ebx,%edx
	jmp	.L290
.L293:
/	movl	%ebx,%eax
/	andl	%eax,-36(%ebp)
	andl	%ebx,%edx
	jmp	.L290
.L294:
/	movl	%ebx,%eax
/	orl	%eax,-36(%ebp)
	orl	%ebx,%edx
	jmp	.L290
.L295:
/	movl	%ebx,%eax
/	xorl	%eax,-36(%ebp)
	xorl	%ebx,%edx
.L296:
.L290:
/	movl	-40(%ebp),%eax
/	andl	%eax,-36(%ebp)
	andl	-40(%ebp),%edx
/	movl	-32(%ebp),%eax
/	orl	%eax,-36(%ebp)
/	movl	-36(%ebp),%eax
	orl	-32(%ebp),%edx
	movl	%edx,(%edi)
.L286:
.L182:
.L79:
	cmpl	$0,52(%ebp)
	je	.L298
	cmpl	$0,-80(%ebp)
	je	.L299
	movl	36(%ebp),%eax
	sarl	$3,%eax
	addl	%eax,-76(%ebp)
	movl	-76(%ebp),%edi
	jmp	.L300
.L299:
	movl	-76(%ebp),%edi
	movl	36(%ebp),%eax
	addl	%eax,-24(%ebp)
	movl	-24(%ebp),%eax
	sarl	$5,%eax
/	movl	%eax,-8(%ebp)
/	shll	$2,-8(%ebp)
/	movl	-8(%ebp),%eax
	shll	$2,%eax
	addl	%eax,%edi
	andl	$31,-24(%ebp)
	movl	-24(%ebp),%eax
	addl	24(%ebp),%eax
	decl	%eax
	andl	$31,%eax
	movl	%eax,-60(%ebp)
	movl	%edi,-76(%ebp)
	cmpl	$0,-24(%ebp)
	je	.L301
	movl	$32,%eax
	subl	-24(%ebp),%eax
	movl	%eax,%ecx
	movl	$-1,%eax
	shll	%cl,%eax
	notl	%eax
	jmp	.L302
.L301:
	movl	$-1,%eax
.L302:
	movl	%eax,-84(%ebp)
	movl	$31,%eax
	subl	-60(%ebp),%eax
	movl	%eax,%ecx
	movl	$-1,%eax
	shll	%cl,%eax
	movl	%eax,-88(%ebp)
	movl	-84(%ebp),%eax
	andl	-88(%ebp),%eax
	movl	%eax,-92(%ebp)
	movl	-24(%ebp),%eax
	addl	24(%ebp),%eax
	sarl	$5,%eax
	decl	%eax
	movl	%eax,-12(%ebp)
.L300:
	movl	60(%ebp),%eax
	incl	%eax
	movl	%eax,60(%ebp)
	cmpl	56(%ebp),%eax
	jl	.L303
	movl	$0,60(%ebp)
	movl	56(%ebp),%eax
	decl	%eax
	leal	(%eax,%eax),%eax
	subl	%eax,8(%ebp)
	jmp	.L45
.L303:
	addl	$2,8(%ebp)
	jmp	.L45
.L298:
	cmpl	$0,-68(%ebp)
	je	.L305
	cmpl	$0,-80(%ebp)
	je	.L306
	movl	36(%ebp),%eax
	sarl	$3,%eax
	addl	%eax,-76(%ebp)
	movl	-76(%ebp),%edi
	jmp	.L307
.L306:
	movl	-76(%ebp),%edi
	movl	36(%ebp),%eax
	addl	%eax,-24(%ebp)
	movl	-24(%ebp),%eax
	sarl	$5,%eax
/	movl	%eax,-8(%ebp)
/	shll	$2,-8(%ebp)
/	movl	-8(%ebp),%eax
	shll	$2,%eax
	addl	%eax,%edi
	andl	$31,-24(%ebp)
	movl	-24(%ebp),%eax
	addl	24(%ebp),%eax
	decl	%eax
	andl	$31,%eax
	movl	%eax,-60(%ebp)
	movl	%edi,-76(%ebp)
	cmpl	$0,-24(%ebp)
	je	.L308
	movl	$32,%eax
	subl	-24(%ebp),%eax
	movl	%eax,%ecx
	movl	$-1,%eax
	shll	%cl,%eax
	notl	%eax
	jmp	.L309
.L308:
	movl	$-1,%eax
.L309:
	movl	%eax,-84(%ebp)
	movl	$31,%eax
	subl	-60(%ebp),%eax
	movl	%eax,%ecx
	movl	$-1,%eax
	shll	%cl,%eax
	movl	%eax,-88(%ebp)
	movl	-84(%ebp),%eax
	andl	-88(%ebp),%eax
	movl	%eax,-92(%ebp)
	movl	-24(%ebp),%eax
	addl	24(%ebp),%eax
	sarl	$5,%eax
	decl	%eax
	movl	%eax,-12(%ebp)
.L307:
	cmpl	$0,-80(%ebp)
	jne	..15
	movl	-72(%ebp),%esi
	movl	32(%ebp),%eax
	addl	%eax,-16(%ebp)
	movl	-16(%ebp),%eax
	sarl	$5,%eax
/	movl	%eax,-8(%ebp)
/	shll	$2,-8(%ebp)
/	movl	-8(%ebp),%eax
	shll	$2,%eax
	addl	%eax,%esi
	andl	$31,-16(%ebp)
	movl	-16(%ebp),%eax
	addl	24(%ebp),%eax
	decl	%eax
	andl	$31,%eax
	movl	%eax,-64(%ebp)
	movl	%esi,-72(%ebp)
	movl	-24(%ebp),%eax
	subl	-16(%ebp),%eax
	andl	$31,%eax
	movl	%eax,-104(%ebp)
	movl	-16(%ebp),%eax
	subl	-24(%ebp),%eax
	andl	$31,%eax
	movl	%eax,-20(%ebp)
	cmpl	$0,-20(%ebp)
	je	.L312
	movl	-20(%ebp),%ecx
	movl	$-1,%eax
	shll	%cl,%eax
	notl	%eax
	jmp	.L313
.L312:
	movl	$-1,%eax
.L313:
	movl	%eax,-28(%ebp)
	jmp	.L321
.L305:
	cmpl	$0,-80(%ebp)
	je	.L314
	movl	36(%ebp),%eax
	sarl	$3,%eax
	addl	%eax,-76(%ebp)
	movl	-76(%ebp),%edi
	jmp	.L315
.L314:
	movl	-76(%ebp),%edi
	movl	36(%ebp),%eax
	addl	%eax,-60(%ebp)
	jge	.L316
	movl	$31,%eax
	subl	-60(%ebp),%eax
	sarl	$5,%eax
/	movl	%eax,-8(%ebp)
/	shll	$2,-8(%ebp)
/	movl	-8(%ebp),%eax
	shll	$2,%eax
	subl	%eax,%edi
	jmp	.L317
.L316:
	movl	-24(%ebp),%eax
	sarl	$5,%eax
/	movl	%eax,-8(%ebp)
/	shll	$2,-8(%ebp)
/	movl	-8(%ebp),%eax
	shll	$2,%eax
	addl	%eax,%edi
.L317:
	andl	$31,-60(%ebp)
	movl	-60(%ebp),%eax
	subl	24(%ebp),%eax
	incl	%eax
	andl	$31,%eax
	movl	%eax,-24(%ebp)
	movl	%edi,-76(%ebp)
	movl	$31,%eax
	subl	-60(%ebp),%eax
	movl	%eax,%ecx
	movl	$-1,%eax
	shll	%cl,%eax
	movl	%eax,-84(%ebp)
	movl	$32,%eax
	subl	-24(%ebp),%eax
	movl	%eax,%ecx
	movl	$-1,%eax
	shll	%cl,%eax
	notl	%eax
	movl	%eax,-88(%ebp)
	movl	-84(%ebp),%eax
	andl	-88(%ebp),%eax
	movl	%eax,-92(%ebp)
	movl	24(%ebp),%eax
	subl	-60(%ebp),%eax
	decl	%eax
	jle	.L318
	movl	24(%ebp),%eax
	subl	-60(%ebp),%eax
	decl	%eax
	sarl	$5,%eax
	jmp	.L319
.L318:
	xorl	%eax,%eax
.L319:
	movl	%eax,-12(%ebp)
.L315:
	cmpl	$0,-80(%ebp)
	je	.L320
..15:
	movl	32(%ebp),%eax
	sarl	$3,%eax
	addl	%eax,-72(%ebp)
	movl	-72(%ebp),%esi
.L321:
.L36:
.L26:
.L45:
	movl	-4(%ebp),%eax
	decl	-4(%ebp)
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
	movl	-72(%ebp),%esi
	movl	32(%ebp),%eax
	addl	%eax,-64(%ebp)
	jge	.L322
	movl	$31,%eax
	subl	-64(%ebp),%eax
	sarl	$5,%eax
/	movl	%eax,-8(%ebp)
	shll	$2,%eax
/	movl	-8(%ebp),%eax
	subl	%eax,%esi
	jmp	.L323
.L322:
	movl	-64(%ebp),%eax
	sarl	$5,%eax
/	movl	%eax,-8(%ebp)
	shll	$2,%eax
/	movl	-8(%ebp),%eax
	addl	%eax,%esi
.L323:
	andl	$31,-64(%ebp)
	movl	-64(%ebp),%eax
	subl	24(%ebp),%eax
	incl	%eax
	andl	$31,%eax
	movl	%eax,-16(%ebp)
	movl	-24(%ebp),%eax
	subl	-16(%ebp),%eax
	andl	$31,%eax
	movl	%eax,-104(%ebp)
	movl	-16(%ebp),%eax
	subl	-24(%ebp),%eax
	andl	$31,%eax
	movl	%eax,-20(%ebp)
	cmpl	$0,-20(%ebp)
	je	.L324
..4:
	movl	-20(%ebp),%ecx
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
