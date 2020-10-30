/*-------------------------DESCRIPTION-------------------------------------
  MENU.C - Example debugger program.  This is the main menu module of a 
  multi-module example program.  Use this program while you are learning the
  debugger.  The other separate modules are:  exampio, info, and, blimp.  
  Source files are provided for the demo modules, so you can experiment with
  the smoothness and power of source-level, "point-and-shoot" debugging.
--------------------------------------------------------------------------*/
/*---------------------------HISTORY---------------------------------------
09/27/90 - K.Reese & D. Duehren: Made generic.
09/01/89 - A.Trent: Adapted for use by the DB386 debugger.
08/06/89 - A.Trent: Adapted for use by the DB960 debugger.
01/10/89 - Adam Trent: Created as EXAMPLE program for DB86 debugger.
--------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------
  Bring in the main example program definitions.
--------------------------------------------------------------------------*/
#include "example.h"

/*-------------------------------------------------------------------------
  Bring in external definitions for the screen I/O functions.
--------------------------------------------------------------------------*/
#include "exampio.h"

/*-------------------------------------------------------------------------
  Declare externals to outside functions (to other modules in the EXAMPLE
  program).  blimp and info are the names of two of these modules.
--------------------------------------------------------------------------*/
extern void blimp_fly(void);
extern void info_menu(void);

/*-------------------------------------------------------------------------
  hdump - dump memory in hex starting at (memptr) and going for (numlines) of
  display lines.  Each display line contains 16 hex bytes shown as hex
  and the same 16 bytes shown as ASCII.  A placeholder graphic character is
  used for certain non-printable characters like cr, lf, etc.
    Eg call:  memptr = hdump(memptr,numlines);
--------------------------------------------------------------------------*/
void hdump(ptr,lines)
char *ptr;
int lines;
{
  int i;
  char *p;

  for (;lines != 0;lines--)
  {
    stout(" ");
    haddrout(ptr);
    stout("  ");

    p = ptr;
    for (i=0;i<16;i++,ptr++)
      hbout(*ptr);
    stout("  ");
    for (i=0;i<16;i++,p++)
    {
      if (*p < 0x20) cout(22);
        else cout(*p);
    }
    crlf();
  }
}

/*-------------------------------------------------------------------------
  menu_memdump - ask for start paragraph and dump memory in hex.
--------------------------------------------------------------------------*/
void menu_memdump()
{
  int done = FALSE;
  char *ptr;
  unsigned int key;

  cls();
  stout(" ==== HEX/ASCII Memory Dump ====");
  crlf();
  stout(" Enter 32-Bit Starting Address in Hex.");
  crlf();
  stout(" You must enter all eight hex digits.");
  crlf();
  stout(" (For example, try 00000000 to dump at start of memory): ");
  ptr = inptr();

  while (!done)
  {
    cls();
    stout(" ==== Hexidecimal/ASCII Memory Dump ====");
    crlf();
    hdump(ptr,16);
    crlf();
    stout("     ====  N - Next Screen;  P - Previous Screen;  Q - Quit: ");

    key = 0;
    while (key == 0)
    {
      key = toupper(cin());

      switch (key)
      {
        case 'N':
          ptr += 256;
          break;
        case 'P':
          ptr -= 256;
          break;
        case 'Q':
          done = TRUE;
          break;
        default:
          beep();
          key = 0;
          break;
      }
    }
  }
}

/*-------------------------------------------------------------------------
  Define the main menu welcome text.
--------------------------------------------------------------------------*/
char *maintxt[] = {
   " ",
   " ",
   "              Welcome to the Debugger Example Program!",
   " ",
   " This example program uses several separately compiled and linked",
   " modules that illustrate the debugger's ability to perform source-",
   " level debugging across several different program modules.  The basic",
   " idea is to use this example program itself as the object of a debugger",
   " tryout session.  The names of the modules help to indicate the major",
   " functions of the program that are selected from the main example menu.",
   " The menu module contains the main menu selection functions and the hex",
   " memory dump function. The info module contains functions to select and",
   " display various info screens.  The blimp module contains the function",
   " to fly a blimp on the screen. The exampio module contains primitive I/O",
   " functions.",
   " ",
    NULLP
  };

/*-------------------------------------------------------------------------
  Define the main menu selection item text lines.
--------------------------------------------------------------------------*/
char *mainitems[] = {
    "Show Various Debugger Information Screens",
    "Fly a Blimp",
    "Dump Memory in Hex",
    "Exit this Example Program",
    NULLP
  };

/*------------------------------------------------------------------------
  This is a function that displays the menu items for a menu.
------------------------------------------------------------------------*/
void show_menu_items(textarray)
char *textarray[];
{
  int i;

  for (i=0; textarray[i] != NULLP; i++)
  {
    stout("              ");
    cout(i + 0x31);
    stout(" - ");
    stout(textarray[i]);
    crlf();
  }
}

/*------------------------------------------------------------------------
  This is the main menu function that displays menu text and the menu 
  items and asks the user to press a key to make a selection.  This 
  simple menu function will only handle up to nine selection items.
------------------------------------------------------------------------*/
int menu_select(textarray,itemarray)
char *textarray[];
char *itemarray[];
{
  int key;
  int done = FALSE;

  showtext((TEXTPTR)textarray);
  show_menu_items(itemarray);

  crlf();
  stout("        Press the number of your selection: ");

  while (!done)                   /* loop getting keys until done */
  {
    key = cin();                  /* get one key from user */

    if (key > 0x2f && key < 0x3a)
    {
      cout(key);                  /* echo the key on screen */
      key -= 0x30;                /* convert it to binary number */
      done = TRUE;                /* signal end of keyin loop */
    }
    else
      if (key == ESC_KEY)
      {
        key = MENU_EXIT;
        done = TRUE;                /* signal end of keyin loop */
      }
      else
      {
        beep();                     /* complain about invalid key */
      }
  }

  return(key);                    /* return with item number selected */
}

void main()
{
/*=====================MAIN================================================
  This is the main entry point for the entire example
  program.  If you are viewing this with the debugger,
  try using the Gray - and Gray + keys to scroll the 
  source file in the view window.  Gray * will restore
  the view back to the current execution point 
  (horizontal bar).  The F1 key brings help.  Press 
  Alt-<firstletter> to pull down a menu.
==========================================================================*/
  int mi;
  int done = FALSE;

/*-------------------------------------------------------------------------
  Begin Main Menu Keyin Loop.
--------------------------------------------------------------------------*/
  while(!done)                    /* loop in main menu until done */
  {
    /* get menu item number selected */
    mi = menu_select(maintxt,mainitems);

    switch (mi)
    {
      case MENU_ITEM_ONE:
        info_menu();              /* show example information screens */
        break;
      case MENU_ITEM_TWO:
        blimp_fly();              /* fly a blimp for fun and profit */
        break;
      case MENU_ITEM_THREE:
        menu_memdump();           /* dump memory in hex */
        break;
      case MENU_ITEM_FOUR:
      case MENU_EXIT:          /* ESCape key pressed */
        done = TRUE;           /* exit to the host operating system */
        break;
      default:
        beep();                   /* invalid selection, so beep */
        break;
    }
  }

  dexit();
}
