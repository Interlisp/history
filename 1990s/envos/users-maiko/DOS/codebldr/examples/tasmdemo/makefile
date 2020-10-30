#------------------------------------------------------------------------------
# Intel 386/486 C Code Builder(TM) Kit
# Copyright 1991 Intel Corporation.  All Rights Reserved.
#
# Make file for TASM 2.0/2.5 - C Interface example program
#------------------------------------------------------------------------------
default:        life.exe

life.exe:       life.obj life_asm.obj
        icc life.obj life_asm.obj graphics.lib

life.obj:       life.c
        icc /c life.c

life_asm.obj:   life_asm.asm macros.inc
        tasm /c /mx life_asm.asm
#Note:  If you wish to use MASM 5.1, replace the above line with:
#        masm /Mx life_asm.asm;
