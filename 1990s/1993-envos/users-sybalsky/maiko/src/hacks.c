/* @(#) hacks.c Version 1.3 (4/21/92). copyright venue & Fuji Xerox  */
static char *id = "@(#) hacks.c	1.3 4/21/92	(venue & Fuji Xerox)";
/* These functions are created so that you can split a float into */
/* four integers. The general idea behind these functions is to */
 /* act as a caster between different entitys on the stack */

int pickapart1(i1, i2, i3, i4)
     int i1, i2, i3, i4;
{
  return(i1);
}

int pickapart2(i1, i2, i3, i4)
     int i1, i2, i3, i4;
{
  return(i2);
}

int pickapart3(i1, i2, i3, i4)
     int i1, i2, i3, i4;
{
  return(i3);
}

int pickapart4(i1, i2, i3, i4)
     int i1, i2, i3, i4;
{
  return(i4);
}
