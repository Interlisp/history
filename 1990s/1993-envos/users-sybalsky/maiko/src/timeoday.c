/* @(#) timeoday.c Version 1.2 (4/23/92). copyright venue & Fuji Xerox  */
static char *id = "@(#) timeoday.c	1.2 4/23/92	(venue & Fuji Xerox)";
#include <sys/time.h>
#include <sys/resource.h>

gettimeofday(time, ptr)
    struct timeval *time;
    int ptr;
{
	struct rusage stats;
	getrusage(RUSAGE_SELF, &stats);
	time->tv_sec = stats.ru_utime.tv_sec;
	time->tv_usec = stats.ru_utime.tv_usec;
}
