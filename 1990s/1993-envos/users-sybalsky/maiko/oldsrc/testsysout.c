/*
 *	testsysout.c
 */

#include <stdio.h>
#include <sys/file.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>

#include "address68k.h"
#include "lispemul.h"
#include "lisptypes.h"
#include "lispmap.h"
#include "lispglobal.h"
#include "ifpage.h"
#include "dbprint.h"

#define	IFPAGE_ADDRESS	512
#define MBYTE	0x100000 /* 1 Mbyte */
extern int	errno;

char *valloc();

main(argc, argv)
  char* argv[3];
  int argc;
  {
    if (argc != 2) 
      {
	printf("You forgot to supply a file name.");
	return(-1);
      }
    check_sysout(argv[1]);
    exit(0);
  }

check_sysout(sysout_file_name)
char	*sysout_file_name;
{
    int             sysout;	/* SysoutFile descriptor */

    IFPAGE         ifpage;	/* IFPAGE */

    char            errmsg [ 255 ];

    /*
     * first read the IFPAGE(InterfacePage)
     */

    /* open SysoutFile */
    sysout = open(sysout_file_name, O_RDONLY, NULL);
    if (sysout == -1) {
	sprintf( errmsg,
                 "sysout_loader: can't open sysout file: %s",
		 sysout_file_name);
	perror( errmsg );
	exit(-1);
    }
    /* seek to IFPAGE */
    if (lseek(sysout, IFPAGE_ADDRESS, 0) == -1) {
	perror("sysout_loader: can't seek to IFPAGE");
	exit(-1);
    }
    /* reads IFPAGE into scratch_page */
    if (read(sysout, &ifpage, sizeof(IFPAGE)) == -1) {
	perror("sysout_loader: can't read IFPAGE");
	exit(-1);
    }

#ifdef BYTESWAP
    word_swap_page(&ifpage, (3+sizeof(IFPAGE))/4);
#endif
    close(sysout);
    printf("%d", ifpage.minbversion);
}
