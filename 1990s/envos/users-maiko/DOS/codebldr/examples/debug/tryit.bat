@echo off
rem  TRYIT.BAT - This batch file invokes DB32 using an EXAMPLE.MAC
rem  macro include file that will cause DB32 to load the EXAMPLE
rem  program.  Just type TRYIT to run DB32 with the EXAMPLE program
rem  loaded.  You can also follow the TRYIT with at least three
rem  other options.  For example,  TRYIT NOKR NOFLIP NOAUTOSYM.
rem
  db32 %1 %2 %3 %4 %5 macro(example.mac)
