/* This is G-file @(#) dummy_entries.h Version 1.1 (3/23/88). copyright Xerox & Fuji Xerox  */
/* 
	dummy_entries.h

	Dummy Entry Points so emulator will link
*/


fixra()		{ error("fixra called"); }

int plus32n(tos, n)	int tos, n;
	{ return(tos + n); }

int sub32(tos_m1, tos) int tos_m1, tos;
	{ return(tos_m1 - tos); }

int plus32(tos_m1, tos) int tos_m1, tos;
	{ return(tos_m1 + tos); }

int sub32n(tos, n)	int tos, n;	
	{ return(tos - n); }

int mpy32(tos_m1, tos) int tos_m1, tos;
	{ return(tos_m1 * tos); }

int rem32(tos_m1, tos) int tos_m1, tos;	
	{ return(tos_m1 % tos); }

int quot32(tos_m1, tos) int tos_m1, tos;
	{ return(tos_m1 / tos); }
