;******************************************************************************
;* Intel 386/486 C Code Builder(TM) Kit
;* Copyright 1991 Intel Corporation.  All Rights Reserved.
;*
;* Filename:    MACROS.INC
;*****************************************************************************

@True   EQU     1
@False  EQU     0

;***************************************************************************
;*  @Proc  name, [<reg[, reg]...>],[<<arg, typ>[,<arg, typ>]...>]
;*
;*  Defines a C-callable PUBLIC procedure.  Performs the following functions:
;*
;*  a) Makes the name PUBLIC.
;*  b) Delares a NEAR PROC.
;*  c) Saves EBP.
;*  d) Establishes stack frame base (EBP <- ESP).
;*  e) Saves registers (if given).
;*  f) Defines arguments (if given) as [ebp+?].
;*
;*  (Ex:)  @Proc  MyFunc, <ebx, esi, edi>, <<MyArg1, DWORD>, <MyArg2, PTR>>
;*         @Proc  MyFunc,, <<MyArg1, DWORD>>
;*
;*--------------------------------------------------------------------------
;*  @ExitP  [<reg[, reg]...>]
;*
;*  Leaves a routine previously defined using the '@Proc' macro.
;*
;*  a) Cleans up local variables from stack.
;*  b) Restores registers.
;*  c) Restores EBP.
;*  d) Returns ("ret").
;*
;*  (Ex:)  @ExitP  <ebx, esi, edi>
;*
;***************************************************************************    
;*  Notes:
;*      
;*  Every procedure defined using "@Proc" must end with "@ExitP".  Do not
;*  include a "ret" statement in the procedure; jump to a label just before
;*  the "@ExitP" macro.
;*
;*  The register list given with "@ExitP" must match EXACTLY with the list
;*  given with the matching "@Proc" macro.  The registers MUST ALWAYS specify
;*  32-bit registers.
;*
;*  The variable "typ" may be BYTE, WORD, DWORD, or PTR.
;***************************************************************************    
@Proc   MACRO   name, regs, args
        PUBLIC  name
  name  PROC    NEAR
       @arg = 8
       @reg = 0
       @loc = 0
        push    ebp
        mov     ebp,esp
  ifnb <regs>
        @Push   regs
  endif

  irp   x, <args>
    ifnb <x>
        @DefArg x, %(@arg)
    endif
  endm
        ENDM


@ExitP  MACRO   regs
        @ClnStk %@loc
  ifnb <regs>
        @Pop    regs
  endif
        pop     ebp
        ret
        ENDM


;*******************************************************************************
;*  @Local   <<name, typ>[,<name, typ>]...>
;*
;*  Used within a C-callable procedure declared using "@Proc" to define local
;*  (stack) variables.
;*
;*  a) Defines local variables as EQUates to [ebp - ?].
;*
;*  (Ex:)  @Local <<MyLoc1, DWORD>, <MyLoc2, PTR>>
;*         @Local <<MyLoc3, BYTE>
;*         @EndLoc
;*--------------------------------------------------------------------------
;*  @EndLoc
;*
;*  Must be used after the final "@Local" statement within a procedure.
;*
;*  a) Reserves storage for the previously defined "@Local" variables.
;*
;*******************************************************************************
;*  Notes:
;*      
;*  You can only use "@Local" in a procedure defined with "@Proc" and "@ExitP".
;*  ("@ExitP" deallocates the stack storage reserved by "@EndLoc".)
;*      
;*  The variable "typ" may be BYTE, WORD, DWORD, or PTR.  However, all local
;*  variables reserve space as if they were DWORDs, to keep the stack DWORD-
;*  aligned.
;*******************************************************************************
@Local  MACRO   local_list
   irp  x, <local_list>
    ifnb <x>
       @loc = @loc + 4
        @DefLoc x, %(@reg+@loc)
    endif
   endm
        ENDM

@EndLoc MACRO
        @LocStk %@loc
        ENDM

@LocStk MACRO   num_bytes
        sub     esp,num_bytes
        ENDM


;******************************************************************************
;*  @Invoke name, [p1[, p2]...]
;*
;*  Calls a C-callable routine with the parameters specified, if any.
;*
;*  a) Repeat for all parameters given:
;*     1. Push p? (where p? is one of p10,p9..p1).
;*  b) Call the function.
;*  c) Clean up the stack.
;*
;*  (Ex:)  @Invoke  Myfunc, MyParm1, MyParm2
;*
;****************************************************************************** 
;*  Notes:
;*      
;*  All parameters are pushed as DWORD PTRs to keep the stack DWORD-aligned.
;******************************************************************************
@ClnStk MACRO   num_bytes
        add     esp,num_bytes
        ENDM

@Invoke MACRO   name,p1,p2,p3,p4,p5,p6,p7,p8,p9,p10
       @prm = 0
  irp   x,<p10,p9,p8,p7,p6,p5,p4,p3,p2,p1> 
    ifnb <x>
       @prm = @prm + 4
        push    DWORD PTR x
    endif
  endm
        call    name
        @ClnStk %@prm
        ENDM
          

;******************************************************************************
;*  @Push
;*
;*  Used by the "@Proc" macro to save the register list given.  May be used if
;*  desired as a shorthand for multiple DWORD push statements.
;*  
;*  a) Repeat for all elements given:
;*     1. Update register displacement counter (@reg).
;*     2. Push r? (where r? is one of the r1,r2..r14).
;*
;*  (Ex:)  @Push  ebx, esi, edi
;*
;*--------------------------------------------------------------------------
;*  @Pop
;*
;*  Counterpart of the above "@Push" macro.
;*
;*  a) Repeat for all elements given:
;*     1. Pop r? (where r? is one of the r14,r13..r1).
;*
;*  (Ex:)  @Pop  ebx, esi, edi
;******************************************************************************
@Push   MACRO   r1,r2,r3,r4,r5,r6,r7,r8,r9,r10,r11,r12,r13,r14
  irp   x,<r1,r2,r3,r4,r5,r6,r7,r8,r9,r10,r11,r12,r13,r14> 
    ifnb <x>
       @reg = @reg + 4
        push    x
    endif
  endm
        ENDM

@Pop    MACRO   r1,r2,r3,r4,r5,r6,r7,r8,r9,r10,r11,r12,r13,r14
  irp   x,<r14,r13,r12,r11,r10,r9,r8,r7,r6,r5,r4,r3,r2,r1> 
    ifnb <x>
        pop     x
    endif
  endm
        ENDM


;******************************************************************************
;*  @DefArg
;*
;*  Used by the "@Proc" macro to setup EQUates to a procedure's arguments.  Has
;*  no "standalone" use.
;*
;*  a) Defines variable as [ebp+?].
;*  b) Updates argument displacement counter (@arg).
;*
;*  (Ex:)  @DefArg  MyArg1, DWORD
;******************************************************************************
@DefArg MACRO   name, typ, displ

       @val_typ = @False
 ifidni <typ>,<BYTE>                    ;;Byte
       @val_typ = @True
   name EQU     BYTE PTR [ebp + displ]
       @arg = @arg + 4
 endif

 ifidni <typ>,<WORD>                    ;;Word
       @val_typ = @True
   name EQU     WORD PTR [ebp + displ]
       @arg = @arg + 4
 endif

 ifidni <typ>,<DWORD>                   ;;DWord
       @val_typ = @True
   name EQU     DWORD PTR [ebp + displ]
       @arg = @arg + 4
 endif

 ifidni <typ>,<PTR>                     ;;pointer
       @val_typ = @True
   name EQU     DWORD PTR [ebp + displ]
       @arg = @arg + 4
 endif

 ife   @val_typ
        %OUT    Unknown type typ.
        .ERR
 endif
        ENDM


;******************************************************************************
;* @DefLoc  name, typ           
;*
;*  Used by the "@Local" macro to setup EQUates to the local variables.  Has
;*  no "standalone" use.
;*
;*  a) Update local variable displacement counter (@loc).
;*  b) Define variable as [ebp-?].
;*
;*  (Ex:)  @LocArg  MyLoc1, DWORD
;******************************************************************************
@DefLoc MACRO   name, typ, displ
       @val_typ = @False
 ifidni <typ>,<BYTE>                    ;;Byte
       @val_typ = @True
   name EQU     BYTE PTR [ebp - displ]
 endif

 ifidni <typ>,<WORD>                    ;;Word
       @val_typ = @True
   name EQU     WORD PTR [ebp - displ]
 endif

 ifidni <typ>,<DWORD>                   ;;DWord
       @val_typ = @True
   name EQU     DWORD PTR [ebp - displ]
 endif

 ifidni <typ>,<PTR>                     ;;pointer
       @val_typ = @True
   name EQU     DWORD PTR [ebp - displ]
 endif

 ife   @val_typ
        %OUT    Unknown type typ.
        .ERR
 endif
        ENDM

