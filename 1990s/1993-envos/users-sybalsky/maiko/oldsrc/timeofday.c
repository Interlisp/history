/* This is G-file @(#) timeofday.c Version 2.2 (4/20/90). copyright Xerox & Fuji Xerox  */
static char *id = "@(#) timeofday.c	2.2 4/20/90";
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
