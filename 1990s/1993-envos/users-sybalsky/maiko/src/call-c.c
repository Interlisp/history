/* @(#) call-c.c Version 1.3 (4/21/92). copyright venue  */
static char *id = "@(#) call-c.c	1.3 4/21/92	(venue)";



/************************************************************************/
/*									*/
/*    F O R E I G N - F U N C T I O N   C A L L   I N T E R F A C E	*/
/*									*/
/*									*/
/*									*/
/************************************************************************/

#include "lispemul.h"


lispPTR call_c_fn(args);
  {
    void() *fn = args[0];
    (*fn)();
    return(NIL);
  }