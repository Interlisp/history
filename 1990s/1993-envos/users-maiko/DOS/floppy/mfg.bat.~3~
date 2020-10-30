@ECHO OFF
answer Enter medley key:
del dsk1\emul.zip
copy install.bat dsk1
copy install.bat dsk2
copy install.bat dsk3
copy install.bat dsk4
copy install.bat dsk5

pkzip -a -s%answer% dsk1\emul.zip medley.exe emul.exe
answer Put floppy 1 in drive
echo Put
copy dsk1\*.* a:
answer Put floppy 2 in drive
echo Put
copy dsk2\*.* a:
answer Put floppy 3 in drive
echo Put
copy dsk3\*.* a:
answer Put floppy 4 in drive
echo Put
copy dsk4\*.* a:
answer Put floppy 5 in drive
echo Put
copy dsk5\*.* a:
echo Mfg run complete.
