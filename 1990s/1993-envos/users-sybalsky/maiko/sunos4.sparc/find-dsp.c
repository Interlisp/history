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
while((nstr = yylook()) >= 0)
yyfussy: switch(nstr){
case 0:
if(yywrap()) return(0); break;
case 1:
{	char x;
	printf("char *dispatch_label = \"");
	loop: x=input();
	if(x == ','){ printf("\";\n"); return;}
	output(x); goto loop;}
break;
case 2:
{}
break;
case -1:
break;
default:
fprintf(yyout,"bad switch yylook %d",nstr);
} return(0); }
/* end of yylex */
int yyvstop[] = {
0,

2,
0,

2,
0,

1,
0,
0};
# define YYTYPE char
struct yywork { YYTYPE verify, advance; } yycrank[] = {
0,0,	0,0,	1,3,	0,0,	
3,3,	0,0,	16,3,	0,0,	
0,0,	0,0,	1,4,	1,5,	
2,4,	3,5,	9,10,	16,5,	
24,25,	25,26,	29,30,	37,38,	
38,39,	42,43,	45,46,	46,47,	
50,51,	60,61,	61,62,	65,66,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	11,12,	21,22,	
30,31,	51,52,	57,58,	0,0,	
14,15,	20,21,	15,16,	33,34,	
54,55,	1,3,	13,14,	3,3,	
18,19,	16,17,	16,3,	16,3,	
16,3,	16,3,	16,3,	16,3,	
16,3,	16,3,	16,3,	23,24,	
32,33,	32,33,	32,33,	32,33,	
32,33,	32,33,	32,33,	32,33,	
32,33,	32,33,	34,35,	35,36,	
36,37,	43,44,	44,45,	44,45,	
44,45,	44,45,	44,45,	44,45,	
44,45,	44,45,	44,45,	44,45,	
55,56,	56,57,	0,0,	0,0,	
10,11,	0,0,	19,20,	0,0,	
0,0,	0,0,	0,0,	8,9,	
26,27,	6,7,	39,40,	63,64,	
1,3,	12,13,	3,3,	22,23,	
16,3,	4,6,	27,28,	40,41,	
31,32,	28,29,	31,32,	48,49,	
47,48,	31,32,	7,8,	41,42,	
31,32,	17,18,	49,50,	52,53,	
62,63,	52,53,	64,65,	0,0,	
52,53,	0,0,	0,0,	52,53,	
53,54,	53,54,	53,54,	53,54,	
53,54,	53,54,	53,54,	53,54,	
53,54,	53,54,	58,59,	0,0,	
58,59,	0,0,	0,0,	58,59,	
0,0,	0,0,	58,59,	59,60,	
59,60,	59,60,	59,60,	59,60,	
59,60,	59,60,	59,60,	59,60,	
59,60,	0,0,	0,0,	0,0,	
0,0};
struct yysvf yysvec[] = {
0,	0,	0,
yycrank+-1,	0,		0,	
yycrank+-3,	yysvec+1,	0,	
yycrank+-3,	0,		0,	
yycrank+-1,	yysvec+3,	0,	
yycrank+0,	0,		yyvstop+1,
yycrank+-1,	yysvec+3,	0,	
yycrank+-1,	yysvec+3,	0,	
yycrank+-1,	yysvec+3,	0,	
yycrank+-5,	yysvec+1,	0,	
yycrank+-1,	yysvec+3,	0,	
yycrank+-1,	yysvec+3,	0,	
yycrank+-2,	yysvec+3,	0,	
yycrank+-2,	yysvec+3,	0,	
yycrank+-1,	yysvec+3,	0,	
yycrank+-1,	yysvec+3,	0,	
yycrank+-5,	0,		0,	
yycrank+-1,	yysvec+3,	0,	
yycrank+-4,	yysvec+3,	0,	
yycrank+-1,	yysvec+3,	0,	
yycrank+-1,	yysvec+3,	0,	
yycrank+-2,	yysvec+3,	0,	
yycrank+-4,	yysvec+3,	0,	
yycrank+-15,	yysvec+3,	0,	
yycrank+-6,	yysvec+3,	0,	
yycrank+8,	0,		yyvstop+3,
yycrank+1,	0,		0,	
yycrank+1,	0,		0,	
yycrank+1,	0,		0,	
yycrank+9,	0,		0,	
yycrank+3,	0,		0,	
yycrank+9,	0,		0,	
yycrank+16,	0,		0,	
yycrank+3,	0,		0,	
yycrank+24,	0,		0,	
yycrank+22,	0,		0,	
yycrank+23,	0,		0,	
yycrank+9,	0,		0,	
yycrank+11,	0,		0,	
yycrank+4,	0,		0,	
yycrank+8,	0,		0,	
yycrank+2,	0,		0,	
yycrank+12,	0,		0,	
yycrank+1,	0,		0,	
yycrank+30,	0,		0,	
yycrank+12,	yysvec+44,	0,	
yycrank+14,	0,		0,	
yycrank+1,	0,		0,	
yycrank+7,	0,		0,	
yycrank+14,	0,		0,	
yycrank+15,	0,		0,	
yycrank+4,	0,		0,	
yycrank+20,	0,		0,	
yycrank+84,	0,		0,	
yycrank+4,	0,		0,	
yycrank+38,	0,		0,	
yycrank+45,	0,		0,	
yycrank+5,	0,		0,	
yycrank+39,	0,		0,	
yycrank+103,	0,		0,	
yycrank+15,	0,		0,	
yycrank+17,	0,		0,	
yycrank+9,	0,		0,	
yycrank+2,	0,		0,	
yycrank+10,	0,		0,	
yycrank+18,	0,		0,	
yycrank+0,	0,		yyvstop+5,
0,	0,	0};
struct yywork *yytop = yycrank+160;
struct yysvf *yybgin = yysvec+1;
char yymatch[] = {
00  ,01  ,01  ,01  ,01  ,01  ,01  ,01  ,
01  ,01  ,012 ,01  ,01  ,01  ,01  ,01  ,
01  ,01  ,01  ,01  ,01  ,01  ,01  ,01  ,
01  ,01  ,01  ,01  ,01  ,01  ,01  ,01  ,
01  ,01  ,01  ,01  ,01  ,01  ,01  ,01  ,
01  ,01  ,01  ,01  ,01  ,01  ,01  ,01  ,
'0' ,'0' ,'0' ,'0' ,'0' ,'0' ,'0' ,'0' ,
'0' ,'0' ,01  ,01  ,01  ,01  ,01  ,01  ,
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
