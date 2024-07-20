# include "stdio.h"
# define U(x) x
# define NLSTATE yyprevious=YYNEWLINE
# define BEGIN yybgin = yysvec + 1 +
# define INITIAL 0
# define YYLERR yysvec
# define YYSTATE (yyestate-yysvec-1)
# define YYOPTIM 1
# define YYLMAX BUFSIZ
# define output(c) putc(c,yyout)
# define input() (((yytchar=yysptr>yysbuf?U(*--yysptr):getc(yyin))==10?(yylineno++,yytchar):yytchar)==EOF?0:yytchar)
# define unput(c) {yytchar= (c);if(yytchar=='\n')yylineno--;*yysptr++=yytchar;}
# define yymore() (yymorfg=1)
# define ECHO fprintf(yyout, "%s",yytext)
# define REJECT { nstr = yyreject(); goto yyfussy;}
int yyleng; extern char yytext[];
int yymorfg;
extern char *yysptr, yysbuf[];
int yytchar;
FILE *yyin = {stdin}, *yyout = {stdout};
extern int yylineno;
struct yysvf { 
	struct yywork *yystoff;
	struct yysvf *yyother;
	int *yystops;};
struct yysvf *yyestate;
extern struct yysvf yysvec[], *yybgin;
# define YYNEWLINE 10
yylex(){
int nstr; extern int yyprevious;
extern char *dispatch_label;
while((nstr = yylook()) >= 0)
yyfussy: switch(nstr){
case 0:
if(yywrap()) return(0); break;
case 1:
printf(" set %s,", dispatch_label);
break;
case 2:
{
	if (    memcmp(yytext + 5, yytext + 13, 3)
	    ||  memcmp(yytext + 5, yytext + 24, 3)) {REJECT};

	printf(" ldub [%.3s+%.3s+-0x1],%%o1\n",yytext+5, yytext+9);
	printf(" sll %%o1,2,%%o1\n");
	printf(" ld [%%o1+%.3s],%%o1\n",yytext+43);
	printf(" jmp %%o1\n");
	printf("%.16s\n", yytext);
}
break;
case 3:
{
	printf(" sll %%o1,2,%%o1\n");
	printf(" ld [%%o1+%%%.2s],%%o1\n",yytext + 6);
	printf(" jmp %%o1\n");
	printf(" nop\n");
}
break;
case 4:
{
	if (   !memcmp(yytext + 5, yytext + 13, 3)
	    && !memcmp(yytext + 5, yytext + 24, 3)
	    &&  memcmp(yytext + 5, yytext + 29, 3)) {
		printf(" ldub [%.3s+%.3s],%.3s\n%.16s\n",
			 yytext+5,yytext+9,yytext+29,yytext);
	} else
		printf("%s", yytext);
}
break;
case 5:
{
	if (memcmp(yytext+yyleng-strlen(dispatch_label)-1,
			dispatch_label,
			strlen(dispatch_label))) {
		fprintf(stderr, "Label in dispatch changed. Edit disphack.lex");
		fprintf(stderr, " and change '%s' to label", dispatch_label);
		fprintf(stderr, " in last line of \n\n%s\n\n and retry!\n", yytext);
		exit(-1);
	} else if (memcmp(yytext + 12, yytext + 21, 3)) {
		fprintf(stderr, "Odd sequence %s\n", yytext);
	};
	REJECT;
}
break;
case -1:
break;
default:
fprintf(yyout,"bad switch yylook %d",nstr);
} return(0); }
/* end of yylex */
int yyvstop[] = {
0,

4,
0,

3,
0,

1,
0,

5,
0,

2,
0,
0};
# define YYTYPE int
struct yywork { YYTYPE verify, advance; } yycrank[] = {
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	1,3,	12,16,	
15,19,	17,21,	18,22,	0,0,	
0,0,	0,0,	47,51,	51,55,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	16,20,	19,23,	
26,30,	35,39,	0,0,	0,0,	
0,0,	28,32,	31,35,	46,50,	
48,52,	24,28,	24,28,	24,28,	
24,28,	24,28,	24,28,	24,28,	
24,28,	24,28,	24,28,	27,31,	
27,31,	27,31,	27,31,	27,31,	
27,31,	27,31,	27,31,	27,31,	
27,31,	32,36,	34,38,	34,38,	
34,38,	34,38,	34,38,	34,38,	
34,38,	34,38,	34,38,	34,38,	
40,44,	40,44,	40,44,	40,44,	
42,46,	43,47,	44,48,	58,62,	
60,64,	62,66,	64,68,	71,75,	
22,26,	78,82,	82,86,	38,42,	
21,25,	84,88,	3,4,	5,9,	
3,5,	4,8,	6,10,	8,12,	
14,18,	25,29,	92,96,	0,0,	
53,57,	3,6,	3,7,	9,13,	
7,11,	13,17,	29,33,	20,24,	
33,37,	20,24,	10,14,	11,15,	
20,24,	37,41,	23,27,	20,24,	
23,27,	36,40,	30,34,	23,27,	
30,34,	39,43,	23,27,	30,34,	
41,45,	45,49,	30,34,	49,53,	
50,54,	52,56,	50,54,	52,56,	
55,59,	50,54,	52,56,	57,61,	
50,54,	52,56,	54,58,	54,58,	
54,58,	54,58,	54,58,	54,58,	
54,58,	54,58,	54,58,	54,58,	
56,60,	56,60,	56,60,	56,60,	
56,60,	56,60,	56,60,	56,60,	
56,60,	56,60,	59,63,	61,65,	
63,67,	65,69,	66,70,	67,71,	
68,72,	69,73,	70,74,	72,76,	
73,77,	74,78,	75,79,	76,80,	
77,81,	79,83,	80,84,	81,85,	
83,87,	85,89,	86,90,	87,91,	
86,90,	88,92,	89,93,	86,90,	
91,95,	93,97,	86,90,	90,94,	
90,94,	90,94,	90,94,	90,94,	
90,94,	90,94,	90,94,	90,94,	
90,94,	94,98,	95,99,	96,100,	
97,101,	96,100,	98,102,	99,103,	
96,100,	101,105,	102,106,	96,100,	
100,104,	100,104,	100,104,	100,104,	
100,104,	100,104,	100,104,	100,104,	
100,104,	100,104,	103,107,	104,108,	
105,110,	106,111,	107,112,	108,113,	
109,114,	110,115,	111,116,	112,117,	
113,118,	114,119,	115,120,	116,121,	
117,122,	118,123,	119,124,	120,125,	
119,124,	121,126,	122,127,	119,124,	
123,128,	125,130,	119,124,	124,129,	
124,129,	124,129,	124,129,	124,129,	
124,129,	124,129,	124,129,	124,129,	
124,129,	126,131,	127,132,	128,133,	
130,134,	131,135,	132,136,	133,137,	
134,138,	135,139,	136,140,	137,141,	
138,142,	139,143,	140,144,	141,145,	
142,146,	104,109,	143,147,	143,147,	
143,147,	143,147,	143,147,	143,147,	
143,147,	143,147,	143,147,	143,147,	
144,148,	145,149,	146,150,	147,151,	
148,152,	149,153,	150,154,	151,155,	
152,156,	153,157,	154,158,	155,159,	
156,160,	157,161,	158,162,	159,163,	
160,164,	161,165,	162,166,	163,167,	
164,168,	165,169,	166,170,	167,171,	
168,172,	169,173,	170,174,	171,175,	
172,176,	173,177,	174,178,	175,179,	
177,180,	175,179,	177,180,	178,181,	
175,179,	177,180,	181,184,	175,179,	
177,180,	179,182,	179,182,	179,182,	
179,182,	179,182,	179,182,	179,182,	
179,182,	179,182,	179,182,	180,183,	
180,183,	180,183,	180,183,	180,183,	
180,183,	180,183,	180,183,	180,183,	
180,183,	182,185,	183,186,	185,187,	
186,188,	187,189,	188,190,	189,191,	
190,192,	191,193,	192,194,	191,193,	
194,196,	195,197,	191,193,	196,198,	
197,199,	191,193,	193,195,	193,195,	
193,195,	193,195,	193,195,	193,195,	
193,195,	193,195,	193,195,	193,195,	
198,200,	199,201,	200,202,	201,203,	
202,204,	203,205,	204,206,	205,207,	
206,208,	207,209,	208,210,	209,211,	
209,211,	209,211,	209,211,	209,211,	
209,211,	209,211,	209,211,	209,211,	
209,211,	210,212,	211,213,	212,214,	
214,215,	215,216,	216,217,	217,218,	
218,219,	219,220,	220,221,	221,222,	
222,223,	223,224,	224,225,	225,226,	
226,227,	227,228,	228,229,	229,230,	
230,231,	231,232,	232,233,	233,234,	
0,0};
struct yysvf yysvec[] = {
0,	0,	0,
yycrank+1,	0,		0,	
yycrank+0,	yysvec+1,	0,	
yycrank+1,	0,		0,	
yycrank+1,	0,		0,	
yycrank+2,	0,		0,	
yycrank+2,	0,		0,	
yycrank+1,	0,		0,	
yycrank+3,	0,		0,	
yycrank+3,	0,		0,	
yycrank+1,	0,		0,	
yycrank+1,	0,		0,	
yycrank+2,	0,		0,	
yycrank+5,	0,		0,	
yycrank+6,	0,		0,	
yycrank+3,	0,		0,	
yycrank+1,	0,		0,	
yycrank+4,	0,		0,	
yycrank+5,	0,		0,	
yycrank+2,	0,		0,	
yycrank+12,	0,		0,	
yycrank+1,	0,		0,	
yycrank+1,	0,		0,	
yycrank+19,	0,		0,	
yycrank+1,	0,		0,	
yycrank+6,	0,		0,	
yycrank+3,	0,		0,	
yycrank+11,	0,		0,	
yycrank+1,	0,		0,	
yycrank+3,	0,		0,	
yycrank+23,	0,		0,	
yycrank+2,	0,		0,	
yycrank+21,	0,		0,	
yycrank+7,	0,		0,	
yycrank+22,	0,		0,	
yycrank+4,	0,		0,	
yycrank+5,	0,		0,	
yycrank+9,	0,		0,	
yycrank+2,	0,		0,	
yycrank+18,	0,		0,	
yycrank+32,	0,		0,	
yycrank+15,	0,		0,	
yycrank+40,	0,		0,	
yycrank+37,	0,		0,	
yycrank+42,	0,		0,	
yycrank+17,	0,		0,	
yycrank+10,	0,		0,	
yycrank+8,	0,		0,	
yycrank+11,	0,		0,	
yycrank+34,	0,		0,	
yycrank+33,	0,		0,	
yycrank+10,	0,		0,	
yycrank+34,	0,		0,	
yycrank+13,	0,		0,	
yycrank+98,	0,		0,	
yycrank+41,	0,		0,	
yycrank+108,	0,		0,	
yycrank+43,	0,		0,	
yycrank+77,	0,		0,	
yycrank+69,	0,		0,	
yycrank+78,	0,		0,	
yycrank+62,	0,		0,	
yycrank+80,	0,		0,	
yycrank+60,	0,		0,	
yycrank+81,	0,		0,	
yycrank+54,	0,		0,	
yycrank+71,	0,		0,	
yycrank+63,	0,		0,	
yycrank+64,	0,		0,	
yycrank+61,	0,		0,	
yycrank+65,	0,		0,	
yycrank+82,	0,		0,	
yycrank+75,	0,		0,	
yycrank+79,	0,		0,	
yycrank+65,	0,		0,	
yycrank+83,	0,		0,	
yycrank+62,	0,		0,	
yycrank+64,	0,		0,	
yycrank+84,	0,		0,	
yycrank+79,	0,		0,	
yycrank+84,	0,		0,	
yycrank+84,	0,		0,	
yycrank+57,	0,		0,	
yycrank+87,	0,		0,	
yycrank+88,	0,		0,	
yycrank+81,	0,		0,	
yycrank+83,	0,		0,	
yycrank+72,	0,		0,	
yycrank+98,	0,		0,	
yycrank+95,	0,		0,	
yycrank+147,	0,		0,	
yycrank+76,	0,		0,	
yycrank+69,	0,		0,	
yycrank+77,	0,		0,	
yycrank+161,	0,		0,	
yycrank+111,	0,		0,	
yycrank+104,	0,		0,	
yycrank+111,	0,		0,	
yycrank+160,	0,		0,	
yycrank+111,	0,		0,	
yycrank+168,	0,		0,	
yycrank+115,	0,		0,	
yycrank+161,	0,		0,	
yycrank+121,	0,		0,	
yycrank+184,	0,		0,	
yycrank+120,	0,		0,	
yycrank+176,	0,		0,	
yycrank+115,	0,		0,	
yycrank+186,	0,		0,	
yycrank+188,	0,		0,	
yycrank+132,	0,		0,	
yycrank+224,	0,		0,	
yycrank+123,	0,		0,	
yycrank+188,	0,		0,	
yycrank+200,	0,		0,	
yycrank+194,	0,		0,	
yycrank+230,	0,		0,	
yycrank+143,	0,		0,	
yycrank+121,	0,		0,	
yycrank+139,	0,		0,	
yycrank+195,	0,		0,	
yycrank+147,	0,		0,	
yycrank+130,	0,		0,	
yycrank+199,	0,		0,	
yycrank+203,	0,		0,	
yycrank+239,	0,		0,	
yycrank+158,	0,		0,	
yycrank+163,	0,		0,	
yycrank+170,	0,		0,	
yycrank+0,	0,		yyvstop+1,
yycrank+255,	0,		0,	
yycrank+148,	0,		0,	
yycrank+162,	0,		0,	
yycrank+223,	0,		0,	
yycrank+158,	0,		0,	
yycrank+260,	0,		0,	
yycrank+169,	0,		0,	
yycrank+234,	0,		0,	
yycrank+161,	0,		0,	
yycrank+197,	0,		0,	
yycrank+160,	0,		0,	
yycrank+164,	0,		0,	
yycrank+164,	0,		0,	
yycrank+230,	0,		0,	
yycrank+244,	0,		0,	
yycrank+240,	0,		0,	
yycrank+280,	0,		0,	
yycrank+281,	yysvec+143,	0,	
yycrank+242,	0,		0,	
yycrank+283,	0,		0,	
yycrank+285,	0,		0,	
yycrank+286,	0,		0,	
yycrank+286,	0,		0,	
yycrank+288,	0,		0,	
yycrank+189,	0,		0,	
yycrank+184,	0,		0,	
yycrank+291,	0,		0,	
yycrank+192,	0,		0,	
yycrank+191,	0,		0,	
yycrank+195,	0,		0,	
yycrank+194,	0,		0,	
yycrank+194,	0,		0,	
yycrank+188,	0,		0,	
yycrank+199,	0,		0,	
yycrank+197,	0,		0,	
yycrank+191,	0,		0,	
yycrank+301,	0,		0,	
yycrank+302,	0,		0,	
yycrank+200,	0,		0,	
yycrank+304,	0,		0,	
yycrank+277,	0,		0,	
yycrank+278,	0,		0,	
yycrank+306,	0,		0,	
yycrank+280,	0,		0,	
yycrank+207,	0,		0,	
yycrank+216,	0,		0,	
yycrank+0,	0,		yyvstop+3,
yycrank+217,	0,		0,	
yycrank+275,	0,		0,	
yycrank+281,	0,		0,	
yycrank+291,	0,		0,	
yycrank+282,	0,		0,	
yycrank+305,	0,		0,	
yycrank+306,	0,		0,	
yycrank+0,	0,		yyvstop+5,
yycrank+301,	0,		0,	
yycrank+315,	0,		0,	
yycrank+309,	0,		0,	
yycrank+243,	0,		0,	
yycrank+318,	0,		0,	
yycrank+308,	0,		0,	
yycrank+254,	0,		0,	
yycrank+348,	0,		0,	
yycrank+318,	0,		0,	
yycrank+351,	0,		0,	
yycrank+351,	0,		0,	
yycrank+264,	0,		0,	
yycrank+355,	0,		0,	
yycrank+279,	0,		0,	
yycrank+262,	0,		0,	
yycrank+270,	0,		0,	
yycrank+278,	0,		0,	
yycrank+272,	0,		0,	
yycrank+265,	0,		0,	
yycrank+373,	0,		0,	
yycrank+374,	0,		0,	
yycrank+289,	0,		0,	
yycrank+309,	0,		0,	
yycrank+284,	0,		0,	
yycrank+339,	0,		0,	
yycrank+300,	0,		0,	
yycrank+354,	yysvec+209,	0,	
yycrank+284,	0,		0,	
yycrank+0,	0,		yyvstop+7,
yycrank+284,	0,		0,	
yycrank+306,	0,		0,	
yycrank+302,	0,		0,	
yycrank+298,	0,		0,	
yycrank+289,	0,		0,	
yycrank+293,	0,		0,	
yycrank+309,	0,		0,	
yycrank+291,	0,		0,	
yycrank+309,	0,		0,	
yycrank+305,	0,		0,	
yycrank+309,	0,		0,	
yycrank+297,	0,		0,	
yycrank+368,	0,		0,	
yycrank+363,	0,		0,	
yycrank+404,	0,		0,	
yycrank+406,	0,		0,	
yycrank+306,	0,		0,	
yycrank+306,	0,		0,	
yycrank+306,	0,		0,	
yycrank+409,	0,		0,	
yycrank+0,	0,		yyvstop+9,
0,	0,	0};
struct yywork *yytop = yycrank+419;
struct yysvf *yybgin = yysvec+1;
char yymatch[] = {
00  ,01  ,01  ,01  ,01  ,01  ,01  ,01  ,
01  ,01  ,01  ,01  ,01  ,01  ,01  ,01  ,
01  ,01  ,01  ,01  ,01  ,01  ,01  ,01  ,
01  ,01  ,01  ,01  ,01  ,01  ,01  ,01  ,
01  ,01  ,01  ,01  ,01  ,01  ,01  ,01  ,
01  ,01  ,01  ,01  ,01  ,01  ,01  ,01  ,
'0' ,'0' ,'0' ,'0' ,'4' ,'4' ,'4' ,'4' ,
'4' ,'4' ,01  ,01  ,01  ,01  ,01  ,01  ,
01  ,01  ,01  ,01  ,01  ,01  ,01  ,01  ,
01  ,01  ,01  ,01  ,01  ,01  ,01  ,01  ,
01  ,01  ,01  ,01  ,01  ,01  ,01  ,01  ,
01  ,01  ,01  ,01  ,01  ,01  ,01  ,01  ,
01  ,01  ,01  ,01  ,01  ,01  ,01  ,'g' ,
01  ,'g' ,01  ,01  ,'g' ,01  ,01  ,'g' ,
01  ,01  ,01  ,01  ,01  ,01  ,01  ,01  ,
01  ,01  ,01  ,01  ,01  ,01  ,01  ,01  ,
0};
char yyextra[] = {
0,0,0,0,0,0,0,0,
0};
#ifndef lint
static	char ncform_sccsid[] = "@(#)ncform 1.6 88/02/08 SMI"; /* from S5R2 1.2 */
#endif

int yylineno =1;
# define YYU(x) x
# define NLSTATE yyprevious=YYNEWLINE
char yytext[YYLMAX];
struct yysvf *yylstate [YYLMAX], **yylsp, **yyolsp;
char yysbuf[YYLMAX];
char *yysptr = yysbuf;
int *yyfnd;
extern struct yysvf *yyestate;
int yyprevious = YYNEWLINE;
yylook(){
	register struct yysvf *yystate, **lsp;
	register struct yywork *yyt;
	struct yysvf *yyz;
	int yych, yyfirst;
	struct yywork *yyr;
# ifdef LEXDEBUG
	int debug;
# endif
	char *yylastch;
	/* start off machines */
# ifdef LEXDEBUG
	debug = 0;
# endif
	yyfirst=1;
	if (!yymorfg)
		yylastch = yytext;
	else {
		yymorfg=0;
		yylastch = yytext+yyleng;
		}
	for(;;){
		lsp = yylstate;
		yyestate = yystate = yybgin;
		if (yyprevious==YYNEWLINE) yystate++;
		for (;;){
# ifdef LEXDEBUG
			if(debug)fprintf(yyout,"state %d\n",yystate-yysvec-1);
# endif
			yyt = yystate->yystoff;
			if(yyt == yycrank && !yyfirst){  /* may not be any transitions */
				yyz = yystate->yyother;
				if(yyz == 0)break;
				if(yyz->yystoff == yycrank)break;
				}
			*yylastch++ = yych = input();
			yyfirst=0;
		tryagain:
# ifdef LEXDEBUG
			if(debug){
				fprintf(yyout,"char ");
				allprint(yych);
				putchar('\n');
				}
# endif
			yyr = yyt;
			if ( (int)yyt > (int)yycrank){
				yyt = yyr + yych;
				if (yyt <= yytop && yyt->verify+yysvec == yystate){
					if(yyt->advance+yysvec == YYLERR)	/* error transitions */
						{unput(*--yylastch);break;}
					*lsp++ = yystate = yyt->advance+yysvec;
					goto contin;
					}
				}
# ifdef YYOPTIM
			else if((int)yyt < (int)yycrank) {		/* r < yycrank */
				yyt = yyr = yycrank+(yycrank-yyt);
# ifdef LEXDEBUG
				if(debug)fprintf(yyout,"compressed state\n");
# endif
				yyt = yyt + yych;
				if(yyt <= yytop && yyt->verify+yysvec == yystate){
					if(yyt->advance+yysvec == YYLERR)	/* error transitions */
						{unput(*--yylastch);break;}
					*lsp++ = yystate = yyt->advance+yysvec;
					goto contin;
					}
				yyt = yyr + YYU(yymatch[yych]);
# ifdef LEXDEBUG
				if(debug){
					fprintf(yyout,"try fall back character ");
					allprint(YYU(yymatch[yych]));
					putchar('\n');
					}
# endif
				if(yyt <= yytop && yyt->verify+yysvec == yystate){
					if(yyt->advance+yysvec == YYLERR)	/* error transition */
						{unput(*--yylastch);break;}
					*lsp++ = yystate = yyt->advance+yysvec;
					goto contin;
					}
				}
			if ((yystate = yystate->yyother) && (yyt= yystate->yystoff) != yycrank){
# ifdef LEXDEBUG
				if(debug)fprintf(yyout,"fall back to state %d\n",yystate-yysvec-1);
# endif
				goto tryagain;
				}
# endif
			else
				{unput(*--yylastch);break;}
		contin:
# ifdef LEXDEBUG
			if(debug){
				fprintf(yyout,"state %d char ",yystate-yysvec-1);
				allprint(yych);
				putchar('\n');
				}
# endif
			;
			}
# ifdef LEXDEBUG
		if(debug){
			fprintf(yyout,"stopped at %d with ",*(lsp-1)-yysvec-1);
			allprint(yych);
			putchar('\n');
			}
# endif
		while (lsp-- > yylstate){
			*yylastch-- = 0;
			if (*lsp != 0 && (yyfnd= (*lsp)->yystops) && *yyfnd > 0){
				yyolsp = lsp;
				if(yyextra[*yyfnd]){		/* must backup */
					while(yyback((*lsp)->yystops,-*yyfnd) != 1 && lsp > yylstate){
						lsp--;
						unput(*yylastch--);
						}
					}
				yyprevious = YYU(*yylastch);
				yylsp = lsp;
				yyleng = yylastch-yytext+1;
				yytext[yyleng] = 0;
# ifdef LEXDEBUG
				if(debug){
					fprintf(yyout,"\nmatch ");
					sprint(yytext);
					fprintf(yyout," action %d\n",*yyfnd);
					}
# endif
				return(*yyfnd++);
				}
			unput(*yylastch);
			}
		if (yytext[0] == 0  /* && feof(yyin) */)
			{
			yysptr=yysbuf;
			return(0);
			}
		yyprevious = yytext[0] = input();
		if (yyprevious>0)
			output(yyprevious);
		yylastch=yytext;
# ifdef LEXDEBUG
		if(debug)putchar('\n');
# endif
		}
	}
yyback(p, m)
	int *p;
{
if (p==0) return(0);
while (*p)
	{
	if (*p++ == m)
		return(1);
	}
return(0);
}
	/* the following are only used in the lex library */
yyinput(){
	return(input());
	}
yyoutput(c)
  int c; {
	output(c);
	}
yyunput(c)
   int c; {
	unput(c);
	}