/*-------------------------------------------------------------------------
  INFO.C - info screen module of the example program.
--------------------------------------------------------------------------*/
/*--------------------------HISTORY----------------------------------------
09/27/90 - K.Reese & D. Duehren: Made generic.
09/01/89 - Adam Trent: Adapted for use by the DB386 debugger.
08/06/89 - Adam Trent: Adapted for use by the DB960 debugger.
01/10/89 - Adam Trent: Created for the example program.
--------------------------------------------------------------------------*/
/*-------------------------------------------------------------------------
  Bring in the main example program definitions.
--------------------------------------------------------------------------*/
#include "example.h"

/*-------------------------------------------------------------------------
  Externals for the I/O functions.
--------------------------------------------------------------------------*/
#include "exampio.h"

/*-------------------------------------------------------------------------
  Info screen text arrays.
--------------------------------------------------------------------------*/

char *info_example_txt[] = {
 "                       Example Program Overview",
 " ",
 " Use the example program as the object of a debugging tryout session.",
 " That is, use the debugger to 'debug' this program.  This program is a ",
 " menu-driven example that does simple things like show info screens and",
 " dump memory in hex.  The related files follow:",
 "   EXAMPLE.EXE  - Loadable object file for the example program",
 "   EXAMPIO.C    - Source for a small set of I/O functions",
 "   EXAMPIO.H    - Source for external definitions for users of EXAMPIO.C",
 "   EXAMPLE.H    - Source for external definitions used by the example program",
 "   MENU.C       - Source for the main-menu function of the example program",
 "   INFO.C       - Source for menu driven Info screen displays",
 "   BLIMP.C      - Source for function to display a flying blimp",
 "   IO.ASM       - Asm source for low-level I/O functions",
 "   MAKEFILE     - A make file to compile and link the example program",
 "   TRYIT.BAT    - A batch file to run the debugger using EXAMPLE.MAC",
 "   EXAMPLE.MAC  - A macro file that loads EXAMPLE.EXE",
  NULLP
  };

char *info_db386_txt[] = {
 "                            Debugger Overview",
 " ",
 " The debugger is an Intel software debugging tool supporting symbolic,     ",
 " source-level debugging.  It offers an easy-to-learn human interface with  ",
 " pull-down menus and screen windows to show the source code, command lines,",
 " and processor registers.  You can set breakpoints at the source-code level",
 " using a point-and-shoot technique.  You can use the function keys on the  ",
 " PC keyboard to access the most common debugging functions.                ",
 " ",
 " The debugger also offers a powerful command language interface with       ",
 " control constructs for loops and conditionals.                            ",
 " ",
 " Using the debugger, you can browse freely through your source modules,    ",
 " setting breakpoints.  You can browse or you can hyperscope to another     ",
 " module and reference variables and symbols by the program scope in that   ",
 " location.                                                                 ",
 " ",
 " You can inspect the current values of the variables in your program using ",
 " a point-and-shoot technique; and you can also display these values in a   ",
 " Watch window during program execution.  All symbols in the program being  ",
 " debugged are typed, including structures, so you can display structured   ",
 " types and dereference pointers to display structured types.               ",
  NULLP
  };

char *info_tryit_txt[] = {
 " ",
 "                         How to Try Out the Debugger",
 " ",
 " At the DOS prompt, type TRYIT.  The TRYIT batch file invokes the debugger ",
 " and automatically loads the example program.  After invocation, the       ",
 " debugger screen is divided into windows.  The top line is the menu bar.   ",
 " The source file for the main module (menu) of the example program appears ",
 " in the center window with a horizontal bar showing the current execution  ",
 " point.  Use the bottom window to issue commands in the command language.  ",
 " ",
 " Try the following:  Press F1 for help.  Press F2 to turn on the Register  ",
 " window.  To scroll thru the source code, use the Gray + and Gray - keys.  ",
 " The Gray * key returns you home to the current execution point.  Now use  ",
 " F6 to cycle to the Source window.   Then use the cursor pad keys to scroll",
 " through the source.  Press the F7 key to run the program up to the high-  ",
 " lighted line.  Press F8 to step execution through the program one line at ",
 " a time.  Press F9 to set breakpoints and F5 to run the program until a    ",
 " breakpoint is reached.",
 " ",
 " See if you can find the bug in the Hex memory dump routine!  Chapters 2   ",
 " and 3 of the user's guide provide help in finding the bug.",
  NULLP
  };

/*-------------------------------------------------------------------------
  Define the info menu leading text.
--------------------------------------------------------------------------*/
char *infotxt[] = {
 " ",
 " ",
 " ",
 "                    Example Program Info Menu",
 " ",
 " This menu enables you to select and show various information screens on",
 " the example program, on the debugger, and on trying out the debugger by",
 " debugging the example program itself.",
 " ",
  NULLP
  };

/*-------------------------------------------------------------------------
  Define the info menu selection item text lines.
--------------------------------------------------------------------------*/
char *infoitems[] = {
    "Info on this Example Program",
    "Info on the Debugger",
    "Info on How to Try out the Debugger with the Example Program",
    "Exit this Info Menu and Return to Main Menu",
    NULLP
  };

/*-------------------------------------------------------------------------
  Here are the functions to show the info screens.
--------------------------------------------------------------------------*/

void info_example()
{
  showtext((TEXTPTR)info_example_txt);
  pause();
}

void info_db386()
{
  showtext(info_db386_txt);
  pause();
}

void info_tryit()
{
  showtext(info_tryit_txt);
  pause();
}

/*=========================================================================
  Loop in a menu that lets you select and display various info screens.
==========================================================================*/
void info_menu()
{
  int mi;
  int done = FALSE;

  while(!done)                    /* loop in main menu until done */
  {
    /* show menu and get menu item number selected */
    mi = menu_select(infotxt,infoitems);

    switch (mi)
    {
      case MENU_ITEM_ONE:
        info_example();        /* info on the example program */
        break;
      case MENU_ITEM_TWO:
        info_db386();          /* info on the debugger */
        break;
      case MENU_ITEM_THREE:
        info_tryit();          /* info on how to try out the debugger */
        break;
      case MENU_ITEM_FOUR:
      case MENU_EXIT:          /* ESCape key pressed */
        done = TRUE;           /* signal end of this menu loop */
        break;
      default:
        beep();                /* invalid selection, so beep */
        break;
    }
  }
}
