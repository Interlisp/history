/* optck.c
 *
 * This example is almost same as one shown in
 *	SunOS 4.1 Release Manual: 4.2. Known Problems With SunOS Release 4.1 Products.
 *        
 * Compiling this file with -O or -O2 level and  executing, if assembler optimizes
 * incorrectly, "wrong" message is printed out to stdout.
 *        
 */

int	boothowto = 1;

int
main()
{
	int	unit;

	if (boothowto & 1) {
	      retry:
		unit = -1;
		while (unit == -1) {
			if (unit != -1) {
				printf("wrong");
				exit(1);
			}
			unit = 0;
			foo(&unit);
		}
	} else {
		unit = 0;
		goto retry;
	}
}

foo(unitp)
	int	*unitp;
{
}

