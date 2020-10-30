/******************************************************************************
* Intel 386/486 C Code Builder(TM) Kit
* Copyright 1991 Intel Corporation.  All Rights Reserved.
*******************************************************************************
*  LIFE.C
* 
*  The Game of Life
*
*  This is a version of British Mathematician John Horton Conway's game of LIFE
*  (as first popularized in Scientific American).  The game consists of a
*  matrix of cells in checkerboard fashion (the rows & columns of a text screen
*  in this implementation).  Each cell can be alive or dead.  Initially, the
*  matrix is randomly populated (the first generation).  Each succeeding gen-
*  eration is determined by the following rules:
*     1. Each cell has 8 neighboring cells (4 diagonally, 4 orthogonally).
*     2. A "live" cell survives to the next generation if it has 2 or 3 live
*        neighbors.  It is said to die from isolation if it has fewer than 2
*        live neighbors, or die from over-population if it has more than 3.
*     3. An empty ("dead") cell gives birth if it has exactly 3 live neighbors.
*
*  The game ends when:
*     1. All cells die.
*     2. A steady-state is reached in which no more births or deaths occur.
*     3. A flip-flop-state occurs in which every OTHER generation is identical.
*     4. Any key is pressed.  This will terminate the program.
*
*  Note that the program cannot detect a repeating pattern that repeats at a
*  frequency less than every other generation.
*
*******************************************************************************
*  This sample program demonstrates the C - ASM interface.  Processing is split
*  between the C 'main()' portion, which handles each game's initialization,
*  and the Assembly 'Life()' portion, which plays each game.
*
*  Within the Assembly routine, several C routines are called to perform
*  higher-level, less time-critical functions.  Additionally, the 'main()'
*  routine also calls an Assembly routine, 'Delay()', which invokes a BIOS
*  interrupt not available in the standard C library.  (It could be called
*  directly from C using the 'int86()' function, of course.)
******************************************************************************/
#include <graph.h>
#include <stdio.h>


/******************************************************************************
*  Defines
******************************************************************************/
#define BYTE      unsigned char
#define PHYS_VID  0xb8000              /* assume COLOR text-mode screen      */

/******************************************************************************
*  VIDEO typedef                       
******************************************************************************/
#pragma noalign (video)                /* standard COLOR text screen format  */
typedef struct video                   
{
   BYTE  ch;                           /* char code (always ' ')             */
   BYTE  attrib;                       /* display attribute (color or 0)     */
} VIDEO;

/******************************************************************************
*  External function prototypes
******************************************************************************/
void  Delay(int msecs);
BYTE  Life(int color, VIDEO *buf1, VIDEO *buf2, BYTE *cmpBuf);

/******************************************************************************
*  Global variables (also referenced in the Assembly code)
******************************************************************************/
int                  numCols;          /* # of cols & rows (from video config*/
int                  numRows;


/******************************************************************************
*  main()
*
*  'main()' processing is as follows:
*     Initializes the random # generator.
*     Sets the screen background color to black.
*     Determines the # of columns & rows in the current video mode.
*     Calls 'Malloc()' to create 3 buffers based on the # of columns and rows.
*     For each new game:
*        Clears the screen.
*        Picks a random color.
*        Fills the buffer with a random 1st generation.  Each cell's position
*           in the buffer is filled with a character byte (ASCII space [' '])
*           and an attribute byte ('color' if "live", 0 if empty ["dead"]).
*        Copies the 1st generation to the screen.
*        Calls the Assembly routine 'Life()' to play the game until it ends or
*           a key is pressed.
*        If the game ended (no key pressed), delay a bit before continuing.
******************************************************************************/
main()
{
   VIDEO               *buf1, *buf2;   /* video image buffers                */
   VIDEO               *bufPtr;        /* temp ptr into 'buf1'               */
   BYTE                *cmpBuf;        /* comparison buffer (2X2 larger)     */  
   int                  col, row;      /* temp loop counters                 */
   BYTE                 color;         /* 1-7 color, shifted left 4 (bkgrnd) */
   struct videoconfig   config;        /* video configuration structure      */
   BYTE                 quit = 0;      /* non-zero when quit desired         */


/******************************************************************************
*  Display some help text
******************************************************************************/
   _clearscreen(_GCLEARSCREEN);
   printf("The Game of Life\n\n"
      "This version of the Game of Life uses the \"standard\" rules to play\n"
      "the game.  The current text mode determines the game's playing size;\n"
      "set your text mode to it's highest resolution before running this\n"
      "game for maximum enjoyment.\n\n"
      "When the current game has ended, a new game will automatically begin\n"
      "after a few seconds.\n\n"
      "To end the program, press any key during the game.\n\n"
      "Please note that the program cannot detect certain repeating patterns.\n"
      "If this happens, press any key to end the program, and then run the\n"
      "program again.\n\n"
      "Press any key to begin playing....");
   getch();

/******************************************************************************
*  Seed the random # generator, set background to black
******************************************************************************/
   srand((unsigned)time(NULL));
   _setbkcolor(0);

/******************************************************************************
*  Get # of cols & rows in current video mode & alloc buffers based on these
******************************************************************************/
   _getvideoconfig(&config);
   numCols = config.numtextcols;
   numRows = config.numtextrows;
   buf1 = (VIDEO *)malloc(numCols * numRows * sizeof(VIDEO));
   buf2 = (VIDEO *)malloc(numCols * numRows * sizeof(VIDEO));
   cmpBuf = (BYTE *)malloc((numCols+2) * (numRows+2));
   if ((buf1 == NULL) || (buf2 == NULL) || (cmpBuf == NULL))
   {
      printf("Insufficient memory; terminating program.\n");
      exit(1);
   }

/******************************************************************************
*  Loop for each new game 
******************************************************************************/
   do
   {
      _clearscreen(_GCLEARSCREEN);

      do                               /* choose random color between 1 - 7  */
         color = rand() & 7;              
      while (color == 0);
      color = color << 4;              /* attrib-byte pos'n for bkgrnd color */

      bufPtr = buf1;
      for (row = 0; row < numRows; row++) /* fill buffer with 1st generation */
      {
         for (col = 0; col < numCols; col++, bufPtr++)
         {
            if ((rand() & 3) == 3)
               bufPtr->attrib = color;
            else
               bufPtr->attrib = 0;
            bufPtr->ch = ' ';    /* ' ' will appear as colored block   */
         }
      }
      memcpy(PHYS_VID, buf1, numCols * numRows * 2);  /* copy 1st gen to scrn*/


      quit = Life(color, buf1, buf2, cmpBuf);
      if (! quit)                      /* keep final generation on screen    */
         Delay(4000);                  /*    for a while (4000msecs = 4secs) */
   }
   while (! quit);

   _clearscreen(_GCLEARSCREEN);
}



/******************************************************************************
*  MakeCmpBuf(*cmpBuf)
*
*  This routine creates the buffer used to count neighboring cells.  The
*  buffer contains a copy of the current screen image, wrapped by an extra row
*  and column along the image's perimeter.  (Also, the buffer contains only 1
*  byte per cell - the attribute byte.)  The diagram below illustrates how
*  the buffer is designed, assuming a screen dimension of 3 rows by 4 columns:
*     
*     C  9  A  B  C  9    The numbers refer to consecutive screen locations
*      ÚÄÄÄÄÄÄÄÄÄÄÄÄ¿     (cells).  The boxed area contains the screen image.
*     4³ 1  2  3  4 ³1    The area outside the box allows a cells 8 neighbors
*     8³ 5  6  7  8 ³5    to be easily referenced without concern for the
*     C³ 9  A  B  C ³9    border conditions.
*      ÀÄÄÄÄÄÄÄÄÄÄÄÄÙ
*     4  1  2  3  4  1
*
*  This routine is invoked by the Assembly portion of this program.
*
*  Input:
*     cmpBuf   -  Address of memory used to hold buffer being built.
******************************************************************************/
void  MakeCmpBuf(BYTE *cmpBuf)
{
   BYTE    *bufPtr;
   int      col, row;                  /* temp loop counters                 */
   VIDEO   *vidPtr;


/******************************************************************************
*   Create identical portion of cmpBuf (skipping missing rows & columns)     
******************************************************************************/
   vidPtr = (VIDEO *)PHYS_VID;
   bufPtr = cmpBuf + numCols + 3;
   for (row = 0; row < numRows; row++)
   {
      for (col = 0; col < numCols; col++)
         *bufPtr++ = vidPtr++->attrib;
      bufPtr += 2;
   }

/******************************************************************************
*   Create bottom (missing) row by copying top screen row                    
******************************************************************************/
   vidPtr = (VIDEO *)PHYS_VID;
   bufPtr = cmpBuf + ((numRows + 1) * (numCols + 2));
   for (col = 0; col < numCols; col++)
      *bufPtr++ = vidPtr++->attrib;

/******************************************************************************
*   Create top (missing) row by copying bottom screen row                    
******************************************************************************/
   vidPtr = (VIDEO *)PHYS_VID + ((numRows - 1) * numCols);
   bufPtr = cmpBuf + 1;                /* skip 0th (missing) col of cmpBuf   */
   for (col = 0; col < numCols; col++)
      *bufPtr++ = vidPtr++->attrib;

/******************************************************************************
*   Create leftmost (missing) col by copying rightmost screen column      
******************************************************************************/
   vidPtr = (VIDEO *)PHYS_VID + (numCols - 1);
   bufPtr = cmpBuf + (numCols + 2);    /* skip 0th (missing) row of cmpBuf   */
   for (row = 0; row < numRows; row++, bufPtr += numCols+2, vidPtr += numCols)
      *bufPtr = vidPtr->attrib;

/******************************************************************************
*   Create rightmost (missing) col by copying leftmost screen column      
******************************************************************************/
   vidPtr = (VIDEO *)PHYS_VID;
   bufPtr = cmpBuf + (2*(numCols + 2) - 1);     /* skip 0th (missing) row    */
   for (row = 0; row < numRows; row++, bufPtr += numCols+2, vidPtr += numCols)
      *bufPtr = vidPtr->attrib;

/******************************************************************************
*   Copy screen's bottom,right corner to cmpBuf's top,left                   
******************************************************************************/
   vidPtr = (VIDEO *)PHYS_VID + (numCols*numRows) - 1;
   bufPtr = cmpBuf;
   *bufPtr = vidPtr->attrib;
   
/******************************************************************************
*   Copy screen's bottom,left corner to cmpBuf's top,right                   
******************************************************************************/
   vidPtr -= numCols - 1;
   bufPtr += numCols + 1;
   *bufPtr = vidPtr->attrib;

/******************************************************************************
*   Copy screen's top,right corner to cmpBuf's bottom,left                   
******************************************************************************/
   vidPtr = (VIDEO *)PHYS_VID + numCols - 1;
   bufPtr += (numRows * (numCols + 2)) + 1;
   *bufPtr = vidPtr->attrib;

/******************************************************************************
*   Copy screen's top,left corner to cmpBuf's bottom,right                   
******************************************************************************/
   bufPtr += numCols + 1;              /* advance to bottom, right element   */
   vidPtr = (VIDEO *)PHYS_VID;
   *bufPtr = vidPtr->attrib;
   
}
