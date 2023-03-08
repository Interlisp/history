/* @(#) usersubrs.c Version 1.8 (6/4/90). copyright Venue & Fuji Xerox  */
static char *id = "@(#) usersubrs.c	1.8 6/4/90	(Venue & Fuji Xerox)";


/************************************************************************/
/*									*/
/*	Copyright 1989, 1990 Venue, Fuji Xerox Co., Ltd, Xerox Corp.	*/
/*									*/
/*	This file is work-product resulting from the Xerox/Venue	*/
/*	Agreement dated 18-August-1989 for support of Medley.		*/
/*									*/
/************************************************************************/


/** User defined subrs here.  Do NOT attempt to use this unless you FULLY
    understand the dependencies of the LDE architecture.                 **/

#define DO_UFN	{return(-1);}

UserSubr(user_subr_index, num_args, args)

int user_subr_index;
int num_args;
int args[28];

{
int result = 0;

/* *** remove the printf when finished debugging your user subr *** */

	printf("debug: case: 0x%x, args: 0x%x\n",user_subr_index, num_args);
	{int i;
	 for (i = 0; i < num_args; i++) printf("debug: arg[%d]: 0x%x\n",i,args[i]);
	};


	switch (user_subr_index) {

		case 0:	 printf("sample UFN\n"); result = args[0]; break;
		default: DO_UFN;
		}

	return(result);
}

