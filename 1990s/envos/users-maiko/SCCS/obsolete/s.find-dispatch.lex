h54373s 00001/00001/00016d D 1.2 89/04/07 13:32:06 shih 2 1c restored lost sccs stringes 00017/00000/00000d D 1.1 88/10/12 17:13:54 krivacic 1 0c date and time created 88/10/12 17:13:54 by krivaciceuUtTI 1D 2/* This is G-file @(#) find-dispatch.lex Version 1.1 (9/20/88). copyright envos & Fuji Xerox  */E 2I 2/* %Z% %M% Version %I% (%G%). copyright envos & Fuji Xerox  */E 2REG	"%"[oilg][0-9]REGOFF	"%"[oilg][0-9]\+\-0x[0-9]LABEL	L[0-9]+LDUB	"\tldub\t["{REG}"],"{REG}LDUB2	"\tldub\t["{REGOFF}"],"{REG}%%{LDUB2}\n\tcmp\t{REG}",255\n\tbgu\t"{LABEL}\n\t\sll\t{REG}",2,"{REG}\n\tset\t	{	char x;	printf("char *dispatch_label = \"");	loop: x=input();	if(x == ','){ printf("\";\n"); return;}	output(x); goto loop;}.*\n	{}E 1