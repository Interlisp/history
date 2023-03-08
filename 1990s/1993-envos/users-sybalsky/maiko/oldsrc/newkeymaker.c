/* @(#) keymaker.c Version 1.8 (4/20/90). copyright envos & Fuji Xerox  */
/* static char *id = "@(#) keymaker.c	1.8 4/20/90	(envos & Fuji Xerox)"; */

/* =====================================================================
	This function is used to generate copyright protection keys for
	Envos's Maiko software.  It prompts for a machine's host id and
	the software's expiration date before generating a set of 3 keys.

	The external functions called were stored in file 'keylib.o'.

	Creation Date: May, 1988
   ===================================================================== */

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define	GOLDEN_RATIO_HACK			-478700649
#define	floadbyte(number,pos)		((number >> pos) & 0xFFFF)
#define	hash_unhash(number,hashkey)	(number ^ (GOLDEN_RATIO_HACK * (floadbyte(hashkey,16) + floadbyte(hashkey,0)) ))
#define	KEYNUMBERS					3


/*   meaning of symbolic constants used:

		FAILURE1	invalid hostid
		FAILURE2	invalid date entered from terminal
		FAILURE3	can't open logfile in the command line */

#define	FAILURE1					-1
#define	FAILURE2					-2
#define	FAILURE3					-3


unsigned long make_verification();
unsigned long date_integer16();
unsigned long idate();
unsigned long modify();


writeresults( fp, host, expdate, key1, key2, key3, info )
	FILE *fp;
	char *host, *expdate;
	int key1, key2, key3;
	char *info;
    {
	printf("@@host-id: %-14s\n",host);
	printf("@@expiration: %-9s\n",expdate);
	printf("@@key: %8x %8x %8x\n", key1, key2, key3);
	printf("@@doc: %s\n", info);
	printf("---------------------------------------");
    };


main(argc, argv)
	int  argc;
	char *argv[];
 {
	int  logfile = 0;	/* set to 1 if logfile on command line */
	FILE *fp;		/* file pointer for the logfile */
	unsigned long hostid;
	long keyarray[KEYNUMBERS];
	char *hexdigits = {"-0123456789abcdefABCDEF"};
	char s[50], hstr[50], expdate[30], saveexpdate[30], cc;
	char infostring[500];
	char *sptr, *ptr, *digitstring;
	char *hptr = {" "};
	char **hhptr = &hptr;
	int  base = 10;
	int  i,j,c;

   /* == check if user enters logfile name in the command line == */
	if (argc > 1)
		{
			if ((fp = fopen(*++argv,"a")) == NULL)
				{
				printf("\n Can't open %s \n", *argv);
				exit(FAILURE3);
				};
			logfile = 1;
		};

   /* == prompt for machine's host id, verify, then do some modification == */

	printf("\n\nEnter Host ID (starts with 0x if the number is hexidecimal): ");
	gets(s);
	sptr = strtok(s," ");

	/* decide the base */
	if (((ptr = strchr(sptr,'0')) != NULL) &&
	    (*(ptr+1) == 'x' || *(ptr+1) == 'X')) base = 16;

	hostid = strtol(sptr,hhptr,base);

	/* look for syntax error */
	if (**hhptr != '\0')
	  {
		printf("\nInvalid Host ID \n");
		exit(FAILURE1);
	  };

	/* make sure Host ID  is less than 32 bits */
	if (base == 16)
		{	sprintf(hstr, "%x", hostid);
			for (i = 0 ; (cc = *(sptr+i)) != '\0' ; ++i)
				if (isupper(cc)) *(sptr+i) = tolower(cc);
			for (i = 0 ; (cc = *(hstr+i)) != '\0' ; ++i)
				if (isupper(cc)) *(hstr+i) = tolower(cc);
			digitstring = "123456789abcdef";
		}
	  else
		{    sprintf(hstr, "%u", hostid);
			digitstring = "123456789";
		};

	ptr = strpbrk(sptr,digitstring);
	if ((ptr == NULL && *sptr != '0' && *hstr != '0') ||
	    (ptr != NULL && strcmp(ptr,hstr) != 0))
	 {
		printf("\nInvalid Host ID \n");
		exit(FAILURE1);
	  };

	hostid = modify(hostid);

   /* == prompt for the expiration date and validate it == */

	printf("\n\nEnter information string (one line only, below)\n:");
	gets(infostring);

   /* == prompt for the expiration date and validate it == */

	printf("Enter Software Expiration Date (dd-mmm-yy or never): ");
	gets(expdate);
	strcpy(saveexpdate,expdate);

	/* check for 'never' entry */
	if ((expdate[0] == 'N') || (expdate[0] == 'n'))
		{
		    for (i = 0 ; (c = expdate[i]) != '\0' ; ++i)
				if (islower(c)) expdate[i] = toupper(c);

		    if ( strcmp(expdate, "NEVER") == 0)
			  strcpy(expdate, "29-DEC-77");
			  else {
				printf("\nInvalid Software Expiration Date\n");
				exit(FAILURE2);
				};
		};

	/* validate the date */
	if ( idate(expdate) == FAILURE2)
	  {
		printf("\nInvalid Software Expiration Date\n");
		exit(FAILURE2);
	  };

 /* == generate 3 keys == */

	keyarray[0] = hash_unhash(hostid, hostid);
	keyarray[1] = hash_unhash( ((date_integer16(expdate) << 16) | 0), hostid);
	keyarray[2] = make_verification(keyarray[0], keyarray[1]);


  /* == report the results == */

	/* if logfile is open, append the results to the end of the file */
	if (logfile == 1)
	  {
		if (argc > 2)
			{
				fprintf(fp,"\n%s",*++argv);
				printf("\n%s",*argv);
			}
		writeresults( fp, sptr, saveexpdate,
				*keyarray, *(keyarray+1), *(keyarray+2),
				infostring);
		fclose(fp);
	  };
	writeresults( stdout, sptr, saveexpdate,
			*keyarray, *(keyarray+1), *(keyarray+2),
			infostring);
	/* display the results on the terminal */

	exit(0);
}
