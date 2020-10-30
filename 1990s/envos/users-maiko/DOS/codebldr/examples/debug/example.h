/*-------------------------------------------------------------------------
  EXAMPLE.H  -- Include file for EXAMPLE program.
--------------------------------------------------------------------------*/
/*--------------------------HISTORY----------------------------------------
09/01/89 - A.Trent: Adapted for use by the DB386 debugger.
08/06/89 - A.Trent: Adapted for use by the DB960 debugger.
10/06/88 - Adam Trent: Created as example program for users learning
  how to use the DB86 Source Level Symbolic Debugger.
--------------------------------------------------------------------------*/
/*-------------------------------------------------------------------------
  Boolean logic definitions.
--------------------------------------------------------------------------*/
#define TRUE   1
#define FALSE  0
#define YES    1
#define NO     0
#define ON     1
#define OFF    0

#ifndef NULLP
#define NULLP (char *) 0
#endif

/*-------------------------------------------------------------------------
  Video screen definitions.
--------------------------------------------------------------------------*/
#define SCR_ROWS 25             /* number of rows on screen */
#define SCR_COLS 80             /* number of columns on screen */

/*--------------------------------------------------------------------------
  Keyin ASCII values.
---------------------------------------------------------------------------*/
#define BELL_KEY   0x07
#define CR_KEY     0x0d
#define LF_KEY     0x0a
#define ESC_KEY    0x1b

/*-------------------------------------------------------------------------
  Definitions for menus.
--------------------------------------------------------------------------*/
#define MENU_ITEM_ONE     1
#define MENU_ITEM_TWO     2
#define MENU_ITEM_THREE   3
#define MENU_ITEM_FOUR    4
#define MENU_ITEM_FIVE    5
#define MENU_ITEM_SIX     6
#define MENU_ITEM_SEVEN   7
#define MENU_ITEM_EIGHT   8
#define MENU_ITEM_NINE    9
#define MENU_ITEM_TEN    10
#define MENU_EXIT        11

/*-------------------------------------------------------------------------
  General Macro definitions.
--------------------------------------------------------------------------*/
#ifndef min
#define min(a,b) ((a) <= (b) ? (a) : (b))  /* minimum of two params */
#endif

#ifndef max
#define max(a,b) ((a) >= (b) ? (a) : (b))  /* maximum of two params */
#endif

#define ms_byte(a) (((a) >> 8) & 0x00ff)   /* most significant byte of word */
#define ls_byte(a) ((a) & 0x00ff)          /* least significant byte of word */

/*-------------------------------------------------------------------------
  General typedefs and structures.
--------------------------------------------------------------------------*/
typedef unsigned long ULONG;
typedef char *STRINGPTR;
typedef STRINGPTR *TEXTPTR;

