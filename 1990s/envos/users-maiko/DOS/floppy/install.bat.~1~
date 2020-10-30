@ECHO OFF
@rem ******************************************************
@rem *                                                    *
@rem *     Medley Installation Batch File                 *
@rem *                                                    *
@rem *                                                    *
@rem *   Copyright (c) 1992-3 Venue. All Rights Reserved. *
@rem *                                                    *
@rem *   Usage:  install [dir]                            *
@rem *                                                    *
@rem *     dir is the optional directory to install       *
@rem *     Medley in.  Default is C:\medley               *
@rem *                                                    *
@rem ******************************************************
@rem
set newdir=C:\MEDLEY
if not "%1" == "" set newdir=%1
echo
echo Medley Installer ver 2.01
echo Copyright (C) 1992-3 Venue.  All Rights Reserved.
echo .
:dirlp
echo Continuing will install Medley on %newdir%.
if not exist %newdir% goto :noms
echo This may destroy old versions of the files there.
:noms
ask -U Is this the right directory? [Y,n]
if ERRORLEVEL 89 goto dirok

answer Directory to install on (e.g. C:\MEDLEY):  
set newdir=%answer%
goto dirlp

:dirok
if exist %newdir% goto direx
echo Creating installation directory %newdir%...
mkdir %newdir% > nul:
echo (done)
:direx

echo copying library to %newdir%...
copy lib.zip/b %newdir% > nul:
copy emul.zip/b %newdir% > nul:
echo (done)

:disk2
echo Please insert diskette #2.
pause
if not exist sysout1.zip goto disk2

echo copying sysout part 1 to %newdir%...
copy sysout1.zip/b %newdir%\sysout1.zip > nul:
echo (done)

:disk3
echo Please insert diskette #3.
pause
if not exist sysout2.zip goto disk3

echo copying sysout part 2 to %newdir%
copy %newdir%\sysout1.zip/b + sysout2.zip %newdir%\sysout.zip > nul:
del %newdir%\sysout1.zip > nul:
echo (done)

:disk4
echo Please insert diskette #4.
pause
if not exist fonts1.zip goto :disk4

echo copying fonts part 1 to %newdir%.
copy fonts1.zip/b %newdir%\fonts1.zip > nul:
echo (done)

:disk5
echo Please insert diskette #5.
pause
if not exist fonts2.zip goto disk5

echo copying fonts part 2 to %newdir%.
copy %newdir%\fonts1.zip/b + fonts2.zip %newdir%\fonts.zip > nul:
copy rooms.zip %newdir%\rooms.zip > nul:
del %newdir%\fonts1.zip > nul:
copy uncomp.exe %newdir% > nul:

answer Please enter the authentication key from your registration card:

echo Uncompressing files...
cd %newdir% > nul:
uncomp -o -s%answer% -d %newdir%\emul.zip %newdir% > nul:
del %newdir%\emul.zip > nul:
uncomp -o -d %newdir%\lib.zip %newdir% > nul:
del %newdir%\lib.zip > nul:
uncomp -o -d %newdir%\sysout.zip %newdir% > nul:
del %newdir%\sysout.zip > nul:
uncomp -o -d %newdir%\fonts.zip %newdir% > nul:
del %newdir%\fonts.zip > nul:
uncomp -o -d %newdir%\rooms.zip %newdir% > nul:
del %newdir%\rooms.zip > nul:
del %newdir%\uncomp.exe

echo Installation complete.
