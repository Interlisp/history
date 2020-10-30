# ------------------------------------------------------------------------
#  MAKEFILE - This make file governs the necessary compiles and
#    links to make the EXAMPLE.EXE file for debugging with the
#    DB32 protected-mode source-level symbolic debugger.
# ------------------------------------------------------------------------
#

.SUFFIXES:
.SUFFIXES: .obj .c

#

#
#  These are the object files needed to make EXAMPLE.REX
#
objs = exampio.obj menu.obj info.obj blimp.obj io.obj

#
#  To make the loadable file by linking the object files together
#
example.exe: $(objs)
	icc -F -g -xnovm -xregion=512k -e example $(objs)

#
#  To make a .obj object file if the .c source file has changed 
#
.c.obj:
	icc -g -O0 -znoar -c $*.c


