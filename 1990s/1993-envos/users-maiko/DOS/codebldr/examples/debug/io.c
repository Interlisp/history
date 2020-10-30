#include <conio.h>

/* IO.C - I/O module for the DB32 example program */


char __getch()
{
	return (getch());
}

void __putch(char out_char)
{
	putch(out_char);
}
